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
#if DEVCNF_USE_HAL_UART

#include <stdlib.h>

#include <tk/tkernel.h>
#include <tk/device.h>

#include <sysdepend/ra_fsp/cpu_status.h>
#include <mtkernel/kernel/knlinc/tstdlib.h>
#include <mtkernel/device/common/drvif/msdrvif.h>
#include "hal_uart_cnf.h"

/*
 *	hal_uart.c
 *	UART device driver (RA FSP)
*/

/*---------------------------------------------------------------------*/
/*UART Device driver Control block
 */
typedef struct {
    sci_b_uart_instance_ctrl_t                 *huart;     // UART handle
    const uart_cfg_t            *cuart;     // UART config
    ID                          devid;      // Device ID
    UW                          unit;       // Unit no
    ER                          err;        // Error code that occurred during interrupt processing
    ID                          evtmbfid;   // MBF ID for event notification
} T_HAL_UART_DCB;

/* Interrupt detection flag */
LOCAL ID	id_flgid;
LOCAL T_CFLG	id_flg	= {
			.flgatr		= TA_TFIFO | TA_WMUL,
			.iflgptn	= 0,
};

#if TK_SUPPORT_MEMLIB
LOCAL T_HAL_UART_DCB	*dev_uart_cb[DEV_HAL_UART_UNITNM];
#define		get_dcb_ptr(unit)	(dev_uart_cb[unit])
#else
LOCAL T_HAL_UART_DCB	dev_uart_cb[DEV_HAL_UART_UNITNM];
#define		get_dcb_ptr(unit)	(&dev_UART_cb[unit])
#endif

/*---------------------------------------------------------------------*/
/*Device-specific data control
 */

/* HAL Callback functions */
void HAL_UART_Callback(uart_callback_args_t *p_args)
{
	T_HAL_UART_DCB	*p_dcb;

	ENTER_TASK_INDEPENDENT

	p_dcb = (T_HAL_UART_DCB*)p_args->p_context;
	tk_set_flg(id_flgid, 1<< p_dcb->unit);

	switch(p_args->event) {
		case UART_EVENT_TX_COMPLETE:
		case UART_EVENT_RX_COMPLETE:
			p_dcb->err = E_OK;
			break;
		default:
			p_dcb->err = E_IO;
			break;
	}

	LEAVE_TASK_INDEPENDENT
}


LOCAL ER read_data(T_HAL_UART_DCB *p_dcb, T_DEVREQ *req)
{
	UINT		wflgptn, rflgptn;
	ER		err;
	fsp_err_t	fsp_err;

	wflgptn = 1 << p_dcb->unit;
	tk_clr_flg(id_flgid, ~wflgptn);

	/* call hal code */
	fsp_err = R_SCI_B_UART_Read(p_dcb->huart, (UB*)req->buf, req->size);
	if (fsp_err != FSP_SUCCESS) return E_IO;
	/* ---------- */

	err = tk_wai_flg(id_flgid, wflgptn, TWF_ANDW | TWF_BITCLR, &rflgptn, DEV_HAL_UART_TMOUT);
	if(err >= E_OK) {
		err = p_dcb->err;
		if(err >= E_OK) req->asize = req->size;
	}

	return err;
}

LOCAL ER write_data(T_HAL_UART_DCB *p_dcb, T_DEVREQ *req)
{	
	UINT		wflgptn, rflgptn;
	ER		err;
	fsp_err_t	fsp_err;

	wflgptn = 1 << p_dcb->unit;
	tk_clr_flg(id_flgid, ~wflgptn);

	/* call hal code */
	fsp_err = R_SCI_B_UART_Write(p_dcb->huart, (UB*)req->buf, req->size);
    if (fsp_err != FSP_SUCCESS) return E_IO;
	/* ---------- */

	err = tk_wai_flg(id_flgid, wflgptn, TWF_ANDW | TWF_BITCLR, &rflgptn, DEV_HAL_UART_TMOUT);
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
LOCAL ER dev_uart_openfn( ID devid, UINT omode, T_MSDI *msdi)
{
	T_HAL_UART_DCB	*p_dcb;
	fsp_err_t	fsp_err;

	p_dcb = (T_HAL_UART_DCB*)(msdi->dmsdi.exinf);
	if(p_dcb->huart == NULL) return E_IO;

	fsp_err = R_SCI_B_UART_Open(p_dcb->huart, p_dcb->cuart);
	if(fsp_err != FSP_SUCCESS) return E_IO;

	fsp_err = R_SCI_B_UART_CallbackSet(p_dcb->huart, HAL_UART_Callback, p_dcb, NULL);
	if(fsp_err != FSP_SUCCESS) return E_IO;

	return E_OK;
}

/*
 * Close Device
 */
LOCAL ER dev_uart_closefn( ID devid, UINT option, T_MSDI *msdi)
{
    T_HAL_UART_DCB  *p_dcb;
    fsp_err_t   fsp_err;

    p_dcb = (T_HAL_UART_DCB*)(msdi->dmsdi.exinf);
    if(p_dcb->huart == NULL) return E_IO;

    fsp_err = R_SCI_B_UART_Close(p_dcb->huart);
    if(fsp_err != FSP_SUCCESS) return E_IO;

	return E_OK;
}

/*
 * Read Device
 */
LOCAL ER dev_uart_readfn( T_DEVREQ *req, T_MSDI *p_msdi)
{
	T_HAL_UART_DCB	*p_dcb;
	ER		err = E_OK;

	p_dcb = (T_HAL_UART_DCB*)(p_msdi->dmsdi.exinf);
	if(p_dcb->huart == NULL) return E_IO;

	if(req->start >= 0) {
		err = read_data( p_dcb, req);	// Device specific data
	}
	return err;
}

/*
 * Write Device
 */
LOCAL ER dev_uart_writefn( T_DEVREQ *req, T_MSDI *p_msdi)
{
	T_HAL_UART_DCB	*p_dcb;
	ER		err = E_OK;

	p_dcb = (T_HAL_UART_DCB*)(p_msdi->dmsdi.exinf);
	if(p_dcb->huart == NULL) return E_IO;

	if(req->start >= 0) {
		err = write_data( p_dcb, req);	// Device specific data
	}
	return err;
}

/*
 * Event Device
 */
LOCAL ER dev_uart_eventfn( INT evttyp, void *evtinf, T_MSDI *msdi)
{
	return E_NOSPT;
}

/*----------------------------------------------------------------------
 * Device driver initialization and registration
 */
EXPORT ER dev_init_hal_uart( UW unit, sci_b_uart_instance_ctrl_t *huart, const uart_cfg_t *cuart)
{
	T_HAL_UART_DCB  *p_dcb;
	T_IDEV          idev;
	T_MSDI          *p_msdi;
	T_DMSDI         dmsdi;
	ER              err;
	INT             i;

	if( unit >= DEV_HAL_UART_UNITNM) return E_PAR;

#if TK_SUPPORT_MEMLIB
	p_dcb = (T_HAL_UART_DCB*)Kmalloc(sizeof(T_HAL_UART_DCB));
	if( p_dcb == NULL) return E_NOMEM;
	dev_uart_cb[unit]	= p_dcb;
#else
	p_dcb = &dev_uart_cb[unit];
#endif

	id_flgid = tk_cre_flg(&id_flg);
	if(id_flgid <= E_OK) {
		err = (ER)id_flgid;
		goto err_1;
	}

	/* Device registration information */
	dmsdi.exinf     = p_dcb;
	dmsdi.drvatr    = 0;                    /* Driver attributes */
	dmsdi.devatr    = TDK_UNDEF;            /* Device attributes */
	dmsdi.nsub      = 0;                    /* Number of sub units */
	dmsdi.blksz     = 1;                    /* Unique data block size (-1 = unknown) */
	dmsdi.openfn    = dev_uart_openfn;
	dmsdi.closefn   = dev_uart_closefn;
	dmsdi.readfn    = dev_uart_readfn;
	dmsdi.writefn   = dev_uart_writefn;
	dmsdi.eventfn   = dev_uart_eventfn;
	
	knl_strcpy( (char*)dmsdi.devnm, DEVNAME_HAL_UART);
	i = knl_strlen(DEVNAME_HAL_UART);
	dmsdi.devnm[i] = (UB)('a' + unit);
	dmsdi.devnm[i+1] = 0;

	err = msdi_def_dev( &dmsdi, &idev, &p_msdi);
	if(err != E_OK) goto err_1;

	p_dcb->huart	= huart;
	p_dcb->cuart	= cuart;
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

#endif		/* DEVCNF_USE_HAL_UART */
#endif		/* MTKBSP_RAFSP */
