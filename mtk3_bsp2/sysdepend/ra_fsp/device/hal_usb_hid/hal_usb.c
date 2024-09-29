/*
 *----------------------------------------------------------------------
 *    micro T-Kernel 3.0 BSP 2.0
 *
 *    Copyright (C) 2023-2024 by Ken Sakamura.
 *    This software is distributed under the T-License 2.1.
 *----------------------------------------------------------------------
 *
 *    Released by TRON Forum(http://www.tron.org) at 2024/03.
 *
 *----------------------------------------------------------------------
 */
#include <sys/machine.h>
#include <config_bsp/ra_fsp/config_bsp.h>

#ifdef MTKBSP_RAFSP
#if DEVCNF_USE_HAL_USB

#include <stdlib.h>

#include <tk/tkernel.h>
#include <tk/device.h>

#include <sysdepend/ra_fsp/cpu_status.h>
#include <mtkernel/kernel/knlinc/tstdlib.h>
#include <mtkernel/device/common/drvif/msdrvif.h>
#include <sysdepend/ra_fsp/device/hal_usb_hid/hal_usb.h>
#include <sysdepend/ra_fsp/device/hal_usb_hid/hal_usb_cnf.h>
#include <sysdepend/ra_fsp/device/hal_usb_hid/hal_usb_userif.h>

/*
 *	hal_usb.c
 *	USB device driver (RA FSP)
*/

/*---------------------------------------------------------------------*/
/*USB Device driver Control block
 */
typedef struct {
    usb_ctrl_t         *husb;     // USB handle
    const usb_cfg_t             *cusb;     // USB config
    ID                          devid;      // Device ID
    UW                          unit;       // Unit no
    ER                          err;        // Error code that occurred during interrupt processing
    ID                          evtmbfid;   // MBF ID for event notification
} T_HAL_USB_DCB;

/* Interrupt detection flag */
LOCAL ID	id_flgid_read;

EXPORT ID id_usb_read_flg;
EXPORT T_CFLG cfg_usb_read_flg  = {
            .flgatr     = TA_TFIFO | TA_WMUL,
            .iflgptn    = 0,
};

#if TK_SUPPORT_MEMLIB
LOCAL T_HAL_USB_DCB	*dev_usb_cb[DEV_HAL_USB_UNITNM];
#define		get_dcb_ptr(unit)	(dev_usb_cb[unit])
#else
LOCAL T_HAL_USB_DCB	dev_usb_cb[DEV_HAL_USB_UNITNM];
#define		get_dcb_ptr(unit)	(&dev_USB_cb[unit])
#endif

LOCAL ER dev_usb_vbus( T_HAL_USB_DCB *p_dcb, uint16_t state);
LOCAL ER dev_get_pdev_addr( T_HAL_USB_DCB *p_dcb, uint8_t* device_address);
LOCAL ER dev_usb_suspendfn( T_HAL_USB_DCB *p_dcb);
LOCAL ER dev_usb_resumefn( T_HAL_USB_DCB *p_dcb);
LOCAL ER dev_usb_addrsetfn( T_HAL_USB_DCB *p_dcb, uint8_t* p_buf, uint8_t device_address);

/*---------------------------------------------------------------------*/
/*Device-specific data control
 */

/* HAL Callback functions */
void HAL_USB_Callback(usb_callback_args_t *p_args)
{
    T_HAL_USB_DCB  *p_dcb;
    uint8_t device_address;
    uint8_t buff[100];

    ENTER_TASK_INDEPENDENT

    p_dcb = (T_HAL_USB_DCB*)p_args->p_context;

	switch(p_args->event) {
	    case USB_STATUS_POWERED:            ///< Powered State

	    case USB_STATUS_DEFAULT:                ///< Default State
	        dev_usb_vbus(p_dcb, USB_ON);
	        dev_get_pdev_addr(p_dcb, &device_address);
	        dev_usb_addrsetfn(p_dcb, buff, device_address);
	        break;
	    case USB_STATUS_ADDRESS:                ///< Address State
	    case USB_STATUS_CONFIGURED:             ///< Configured State
	    case USB_STATUS_SUSPEND:                ///< Suspend State
	        dev_usb_suspendfn(p_dcb);
	        break;
	    case USB_STATUS_RESUME:                 ///< Resume State
	        dev_usb_resumefn(p_dcb);
	        break;
	    case USB_STATUS_DETACH:                 ///< Detach State
	    case USB_STATUS_REQUEST:               ///< Request State
	    case USB_STATUS_REQUEST_COMPLETE:      ///< Request Complete State
	    case USB_STATUS_READ_COMPLETE:          ///< Read Complete State
	    case USB_STATUS_WRITE_COMPLETE:         ///< Write Complete State
	    case USB_STATUS_BC:                     ///< battery Charge State
	    case USB_STATUS_OVERCURRENT:            ///< Over Current state
	    case USB_STATUS_NOT_SUPPORT:            ///< Device Not Support
	    case USB_STATUS_NONE:                   ///< None Status
	    case USB_STATUS_MSC_CMD_COMPLETE:       ///< MSC_CMD Complete

		default:
			p_dcb->err = E_IO;
			break;
	}
	LEAVE_TASK_INDEPENDENT
}


LOCAL ER read_data(T_HAL_USB_DCB *p_dcb, T_DEVREQ *req)
{
	UINT		wflgptn, rflgptn;
	ER		err;
	fsp_err_t	fsp_err;

	wflgptn = 1 << p_dcb->unit;
	tk_clr_flg(id_flgid_read, ~wflgptn);

	/* call hal code */
	fsp_err = R_USB_Read(p_dcb->husb, (UB*)req->buf, req->size, USB_CLASS_HHID);

	if (fsp_err != FSP_SUCCESS) return E_IO;
	/* ---------- */

	err = tk_wai_flg(id_flgid_read, wflgptn, TWF_ANDW | TWF_BITCLR, &rflgptn, DEV_HAL_USB_TMOUT);
	if(err >= E_OK) {
		err = p_dcb->err;
		if(err >= E_OK) req->asize = req->size;
	}

	return err;
}

LOCAL ER write_data(T_HAL_USB_DCB *p_dcb, T_DEVREQ *req)
{	
	UINT		wflgptn, rflgptn;
	ER		err;
	fsp_err_t	fsp_err;

	wflgptn = 1 << p_dcb->unit;
	/* call hal code */
	fsp_err = R_USB_Write(p_dcb->husb, (UB*)req->buf, req->size, USB_CLASS_HHID);
    if (fsp_err != FSP_SUCCESS) return E_IO;
	/* ---------- */

	err = tk_wai_flg(id_flgid_read, wflgptn, TWF_ANDW | TWF_BITCLR, &rflgptn, DEV_HAL_USB_TMOUT);
	if(err >= E_OK) {
		err = p_dcb->err;
		if(err >= E_OK) req->asize = req->size;
	}

	return err;
}

/*----------------------------------------------------------------------
 * mSDI I/F function
 */
/*
 * Open device
 */
LOCAL ER dev_usb_openfn( ID devid, UINT omode, T_MSDI *msdi)
{
	T_HAL_USB_DCB	*p_dcb;
	fsp_err_t	fsp_err;

	p_dcb = (T_HAL_USB_DCB*)(msdi->dmsdi.exinf);
	if(p_dcb->husb == NULL) return E_IO;

	fsp_err = R_USB_Open(p_dcb->husb, p_dcb->cusb);
	if(fsp_err != FSP_SUCCESS) return E_IO;

//	fsp_err = R_SCI_B_USB_CallbackSet(p_dcb->husb, HAL_USB_Callback, p_dcb, NULL);
//	if(fsp_err != FSP_SUCCESS) return E_IO;

	return E_OK;
}

/*
 * Close Device
 */
LOCAL ER dev_usb_closefn( ID devid, UINT option, T_MSDI *msdi)
{
    T_HAL_USB_DCB  *p_dcb;
    fsp_err_t   fsp_err;

    p_dcb = (T_HAL_USB_DCB*)(msdi->dmsdi.exinf);
    if(p_dcb->husb == NULL) return E_IO;
    fsp_err = R_USB_Close(p_dcb->husb);
    if(fsp_err != FSP_SUCCESS) return E_IO;

	return E_OK;
}

/*
 * Read Device
 */
LOCAL ER dev_usb_readfn( T_DEVREQ *req, T_MSDI *p_msdi)
{
	T_HAL_USB_DCB	*p_dcb;
	ER		err = E_OK;

	p_dcb = (T_HAL_USB_DCB*)(p_msdi->dmsdi.exinf);
	if(p_dcb->husb == NULL) return E_IO;

	if(req->start >= 0) {
		err = read_data( p_dcb, req);	// Device specific data
	}
	return err;
}

/*
 * Write Device
 */
LOCAL ER dev_usb_writefn( T_DEVREQ *req, T_MSDI *p_msdi)
{
	T_HAL_USB_DCB	*p_dcb;
	ER		err = E_OK;

	p_dcb = (T_HAL_USB_DCB*)(p_msdi->dmsdi.exinf);
	if(p_dcb->husb == NULL) return E_IO;

	if(req->start >= 0) {
		err = write_data( p_dcb, req);	// Device specific data
	}
	return err;
}

/*
 * Event Device
 */
LOCAL ER dev_usb_eventfn( INT evttyp, void *evtinf, T_MSDI *msdi)
{
	return E_NOSPT;
}

LOCAL ER dev_usb_start( T_HAL_USB_DCB *p_dcb){
    fsp_err_t   fsp_err;

    if(p_dcb->husb == NULL) return E_IO;
    fsp_err = R_USB_VbusSet(p_dcb->husb, USB_ON);
    if (fsp_err != FSP_SUCCESS) return E_IO;

    return fsp_err;
}

LOCAL ER dev_usb_stop( T_HAL_USB_DCB *p_dcb){
    fsp_err_t   fsp_err = FSP_SUCCESS;

    if(p_dcb->husb == NULL) return E_IO;
    fsp_err = R_USB_VbusSet(p_dcb->husb, USB_OFF);
    if (fsp_err != FSP_SUCCESS) return E_IO;

    return fsp_err;
}

LOCAL ER dev_usb_vbus( T_HAL_USB_DCB *p_dcb, uint16_t state) {
    fsp_err_t   fsp_err;

    if(state == USB_ON){
        fsp_err = dev_usb_start(p_dcb);
    }else{
        fsp_err = dev_usb_stop(p_dcb);
    }
    if (fsp_err != FSP_SUCCESS) return E_IO;

    return fsp_err;
}

LOCAL ER dev_get_pdev_addr( T_HAL_USB_DCB *p_dcb, uint8_t* device_address){
    ER      err = E_OK;

    if(p_dcb->husb == NULL) return E_IO;
    err = R_USB_DeviceAddressGet (p_dcb->husb, device_address);

    return err;
}

LOCAL ER dev_usb_suspendfn( T_HAL_USB_DCB *p_dcb){
    ER      err = E_OK;

    if(p_dcb->husb == NULL) return E_IO;
    err = R_USB_Suspend(p_dcb->husb);

    return err;
}

LOCAL ER dev_usb_resumefn( T_HAL_USB_DCB *p_dcb){
    ER      err = E_OK;

    if(p_dcb->husb == NULL) return E_IO;
    err = R_USB_Suspend(p_dcb->husb);

    return err;
}

LOCAL ER dev_usb_addrsetfn( T_HAL_USB_DCB *p_dcb, uint8_t* p_buf, uint8_t device_address){
    ER      err = E_OK;
    usb_setup_t setup;
    setup.request_type   = USB_HOST_TO_DEV;
    setup.request_value  = USB_GET_DESCRIPTOR;
    setup.request_index  = 0;             /* wIndex:Interface */
    setup.request_length = 0;             /* wLength:Zero */

    if(p_dcb->husb == NULL) return E_IO;
    err = R_USB_HostControlTransfer (p_dcb->husb, &setup, p_buf, device_address);

    return err;
}

/*----------------------------------------------------------------------
 * Device driver initialization and registration
 */
EXPORT ER dev_init_hal_usb( UW unit, usb_instance_ctrl_t *husb, const usb_cfg_t *cusb)
{
	T_HAL_USB_DCB  *p_dcb;
	T_IDEV          idev;
	T_MSDI          *p_msdi;
	T_DMSDI         dmsdi;
	ER              err;
	INT             i;

	if( unit >= DEV_HAL_USB_UNITNM) return E_PAR;

#if TK_SUPPORT_MEMLIB
	p_dcb = (T_HAL_USB_DCB*)Kmalloc(sizeof(T_HAL_USB_DCB));
	if( p_dcb == NULL) return E_NOMEM;
	dev_usb_cb[unit]	= p_dcb;
#else
	p_dcb = &dev_usb_cb[unit];
#endif

	// inform the status to app_main
	id_usb_read_flg = tk_cre_flg(&cfg_usb_read_flg);
	if(id_usb_read_flg <= E_OK) {
	        err = (ER)id_usb_read_flg;
	        goto err_1;
	    }

	/* Device registration information */
	dmsdi.exinf     = p_dcb;
	dmsdi.drvatr    = 0;                    /* Driver attributes */
	dmsdi.devatr    = TDK_UNDEF;            /* Device attributes */
	dmsdi.nsub      = 0;                    /* Number of sub units */
	dmsdi.blksz     = 1;                    /* Unique data block size (-1 = unknown) */
	dmsdi.openfn    = dev_usb_openfn;
	dmsdi.closefn   = dev_usb_closefn;
	dmsdi.readfn    = dev_usb_readfn;
	dmsdi.writefn   = dev_usb_writefn;
	dmsdi.eventfn   = dev_usb_eventfn;
	
	knl_strcpy( (char*)dmsdi.devnm, DEVNAME_HAL_USB);
	i = knl_strlen(DEVNAME_HAL_USB);
	dmsdi.devnm[i] = (UB)('a' + unit);
	dmsdi.devnm[i+1] = 0;

	err = msdi_def_dev( &dmsdi, &idev, &p_msdi);
	if(err != E_OK) goto err_1;

	p_dcb->husb	= husb;
	p_dcb->cusb	= cusb;
	p_dcb->devid	= p_msdi->devid;
	p_dcb->unit	= unit;
	p_dcb->evtmbfid	= idev.evtmbfid;

	return E_OK;

err_1:
#if TK_SUPPORT_MEMLIB
	Kfree(p_dcb);
#endif
	return err;
}

#endif		/* DEVCNF_USE_HAL_USB */
#endif		/* MTKBSP_RAFSP */
