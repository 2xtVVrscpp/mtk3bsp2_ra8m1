/*
 *----------------------------------------------------------------------
 *    Device Driver for μT-Kernel 3.0
 *
 *    Copyright (C) 2020-2023 by Ken Sakamura.
 *    This software is distributed under the T-License 2.2.
 *----------------------------------------------------------------------
 *
 *    Released by TRON Forum(http://www.tron.org) at 2023/11.
 *
 *----------------------------------------------------------------------
 */
#include <sys/machine.h>
#include <tk/tkernel.h>
#include <tstdlib.h>

#if USE_SDEV_DRV
#include "uart.h"
#include "../include/dev_def.h"
#if DEV_UART_ENABLE
/*
 *	uart.c
 *	Serial communication driver
*/

/*----------------------------------------------------------------------*/
/* Serial Device driver Control block
 */
#if TK_SUPPORT_MEMLIB

LOCAL T_UART_DCB	*dev_uart_cb[DEV_UART_UNITNM];
#define		get_dcb_mem(unit,a)	(dev_uart_cb[unit]->a)

#else

LOCAL T_UART_DCB	dev_uart_cb[DEV_UART_UNITNM];
#define		get_dcb_mem(unit,a)	(dev_uart_cb[unit].a)

#endif

/*----------------------------------------------------------------------*/
/* Serial device driver low-level interface
 *
 *	Called from a low level interrupt handler.
 */
EXPORT BOOL dev_uart_get_snddat(UW unit, UW *data)
{
	T_UART_BUFF	*p_buff;

	p_buff = &get_dcb_mem(unit, snd_buff);
	if(p_buff->top != p_buff->tail) {
		*data = p_buff->data[p_buff->tail];
		if(++p_buff->tail >= DEVCONF_UART_BUFFSIZE) p_buff->tail = 0;

		if(p_buff->wait_tskid) {
			tk_wup_tsk( p_buff->wait_tskid);
			p_buff->wait_tskid = 0;
		}
		return TRUE;
	} else {
		return FALSE;
	}
}

EXPORT void dev_uart_notify_rcv(UW unit, UW data)
{
	T_UART_BUFF	*p_buff;
	INT		next;

	p_buff = &get_dcb_mem( unit, rcv_buff);
	next = p_buff->top + 1;
	if(next >= DEVCONF_UART_BUFFSIZE) next = 0;
	if(next != p_buff->tail) {
		p_buff->data[p_buff->top] = data;
		p_buff->top = next;
	} else {	
		dev_uart_notify_err( unit, DEV_UART_ERR_ROVR);	/* Buffer over flow */
	}

	if(p_buff->wait_tskid) {
		tk_wup_tsk( p_buff->wait_tskid);
		p_buff->wait_tskid = 0;
	}

}

EXPORT void dev_uart_notify_err(UW unit, UW err)
{
	get_dcb_mem(unit, com_error) |= err;	
}

/*----------------------------------------------------------------------*/
/* Attribute data control
 */

LOCAL ER set_atr_size(T_DEVREQ *req)
{
	switch(req->start) {
	case TDN_EVENT:			/* MBF ID for event notification */
		req->asize = sizeof(ID);
		break;
	case TDN_UART_MODE:		/* Communication mode */
	case TDN_UART_SPEED:		/* Communication speed */
	case TDN_UART_COMERR:		/* Communication Error */
		req->asize = sizeof(UW);
		break;
	case TDN_UART_SNDTMO:		/* Send timeout */
	case TDN_UART_RCVTMO:		/* Receive timeout */
		req->asize = sizeof(TMO);
		break;
	default:
		return E_PAR;
	}
	return E_OK;
}

LOCAL ER read_atr(T_UART_DCB *p_dcb, T_DEVREQ *req)
{
	UINT	imask;
	ER	err;

	err = set_atr_size(req);
	if(err != E_OK) return err;

	if(req->size) {
		switch(req->start) {
		case TDN_EVENT:			/* MBF ID for event notification */
			*(ID*)req->buf = p_dcb->evtmbfid;
			break;
		case TDN_UART_MODE:		/* Communication mode */
			*(UW*)req->buf = p_dcb->com_mode;
			break;
		case TDN_UART_SPEED:		/* Communication speed */
			*(UW*)req->buf = p_dcb->com_speed;
			break;
		case TDN_UART_SNDTMO:		/* Send timeout */
			*(TMO*)req->buf = p_dcb->snd_tmo;
			break;
		case TDN_UART_RCVTMO:		/* Receive timeout */
			*(TMO*)req->buf = p_dcb->rcv_tmo;
			break;
		case TDN_UART_COMERR:		/* Communication Error */
			DI(imask);
			*(UW*)req->buf = p_dcb->com_error;
			p_dcb->com_error = 0;
			EI(imask);
			break;
		case TDN_UART_BREAK:		/* Send Break */
			/* no break */
		default:
			err = E_PAR;
		}
	}
	return err;
}

LOCAL ER write_atr(T_UART_DCB *p_dcb, T_DEVREQ *req)
{
	ER	err;

	err = set_atr_size(req);
	if(err != E_OK) return err;

	if(req->size) {
		switch(req->start) {
		case TDN_EVENT:			/* Message buffer ID for event notification */
			p_dcb->evtmbfid = *(ID*)req->buf;
			break;
		case TDN_UART_MODE:		/* Communication mode */
			p_dcb->com_mode = *(UW*)req->buf;
			err = dev_uart_llctl( p_dcb->unit, LLD_UART_MODE, p_dcb->com_mode);
			break;
		case TDN_UART_SPEED:		/* Communication speed */
			p_dcb->com_speed = *(UW*)req->buf;
			err = dev_uart_llctl( p_dcb->unit, LLD_UART_SPEED, p_dcb->com_speed);
			break;
		case TDN_UART_SNDTMO:		/* Send timeout */
			p_dcb->snd_tmo = *(TMO*)req->buf;
			break;
		case TDN_UART_RCVTMO:		/* Receive timeout */
			p_dcb->rcv_tmo = *(TMO*)req->buf;
			break;
		case TDN_UART_BREAK:		/* Send Break */
			err = dev_uart_llctl( p_dcb->unit, LLD_UART_BREAK, *(UW*)req->buf);
			break;
		default:
			err = E_PAR;
		}
	}
	return err;
}

/*----------------------------------------------------------------------*/
/*　Device-specific data control
 */

LOCAL ER read_data( T_UART_DCB *p_dcb, T_DEVREQ *req)
{
	T_UART_BUFF	*p_buff;
	UW		tail;
	UB		*pd;
	SZ		rsize;
	ER		err;

	p_buff	= &p_dcb->rcv_buff;
	tail	= p_buff->tail;
	pd	= req->buf;
	rsize	= req->size;
	err	= E_OK;

	if(rsize != 0 ) {		/* size != 0 : Receive data */
		while(rsize) {
			DisableInt(p_dcb->intno_rcv);	/* Disable Receive Int. */
			if(p_buff->top != tail) {
				*pd++ = p_buff->data[tail++];
				if(tail >= DEVCONF_UART_BUFFSIZE ) tail = 0;
				p_buff->tail = tail;
				EnableInt(p_dcb->intno_rcv, p_dcb->int_pri);	/* Enable Receive Int. */
				rsize--;
			} else {
				p_buff->wait_tskid = tk_get_tid();
				EnableInt(p_dcb->intno_rcv, p_dcb->int_pri);	/* Enable Receive Int. */
				err = tk_slp_tsk(p_dcb->rcv_tmo);
				if( err != E_OK) break;
			}
		}
		req->asize = req->size - rsize;
	} else {		/* size = 0: Get the number of readable data */
		/* Disable Receive Int. */
		rsize = p_buff->top - p_buff->tail;
		/* Enable Receive Int. */
		if(rsize < 0) {
			rsize += DEVCONF_UART_BUFFSIZE;
		}
		req->asize = rsize;
	}

	return err;
}

LOCAL ER write_data( T_UART_DCB *p_dcb, T_DEVREQ *req)
{
	T_UART_BUFF	*p_buff;
	UW		next;
	UB		*pd;
	INT		ssize;
	ER		err;
	BOOL		s;

	p_buff	= &p_dcb->snd_buff;
	pd	= req->buf;
	ssize	= req->size;
	err	= E_OK;

	if(ssize != 0) {		/* size != 0 : Send data */
		while(ssize) {
			next = p_buff->top + 1;
			if(next >= DEVCONF_UART_BUFFSIZE) next = 0;
			
			DisableInt(p_dcb->intno_snd);	/* Disable Send Int. */
			if(next != p_buff->tail) {
				s = FALSE;
				if(p_buff->top == p_buff->tail) {
					s = (E_OK == dev_uart_llctl( p_dcb->unit, LLD_UART_SEND, *pd));
				}
				if(s) {		/* Successful transmission. */
					pd++;
				} else {	/* FIFO is full. */
					p_buff->data[p_buff->top] = *pd++;
					p_buff->top = next;
				}
				EnableInt(p_dcb->intno_snd, p_dcb->int_pri);	/* Enable Send Int. */
				ssize--;
			} else {
				p_buff->wait_tskid = tk_get_tid();
				EnableInt(p_dcb->intno_snd, p_dcb->int_pri);	/* Enable Send Int. */
				err = tk_slp_tsk(p_dcb->snd_tmo);
				if(err != E_OK) break;
			}
		}
		req->asize = req->size - ssize;
	} else {		/* size = 0: Get the number of writable data */
		DisableInt(p_dcb->intno_snd);			/* Disable Send Int. */
		ssize = p_buff->top - p_buff->tail;
		EnableInt(p_dcb->intno_snd, p_dcb->int_pri);	/* Enable send Int. */
		if(ssize < 0) {
			ssize += DEVCONF_UART_BUFFSIZE;
		}
		req->asize = DEVCONF_UART_BUFFSIZE - ssize;
	}

	return err;
}

/*----------------------------------------------------------------------
 * mSDI I/F function
 */
/*----------------------------------------------------------------------
 * Open device
 */
ER dev_uart_openfn( ID devid, UINT omode, T_MSDI *p_msdi)
{
	T_UART_DCB	*p_dcb;
	ER		err;

	p_dcb = (T_UART_DCB*)p_msdi->dmsdi.exinf;

	/* Device Open operation */
	p_dcb->omode = omode;
	buff_init(&p_dcb->snd_buff);
	buff_init(&p_dcb->rcv_buff);

	err = dev_uart_llctl(p_dcb->unit, LLD_UART_START, 0);

	return err;
}

/*----------------------------------------------------------------------
 * Close Device
 */
ER dev_uart_closefn( ID devid, UINT option, T_MSDI *p_msdi)
{
	T_UART_DCB	*p_dcb;
	ER		err;

	p_dcb = (T_UART_DCB*)(p_msdi->dmsdi.exinf);

	/* Device Close operation */
	err = dev_uart_llctl(p_dcb->unit, LLD_UART_STOP, 0);
	
	return err;
}

/*----------------------------------------------------------------------
 * Read Device
 */
ER dev_uart_readfn( T_DEVREQ *req, T_MSDI *p_msdi)
{
	T_UART_DCB	*p_dcb;
	ER		err;

	p_dcb = (T_UART_DCB*)(p_msdi->dmsdi.exinf);

	if(req->start >= 0) {	// Device specific data
		if( p_dcb->omode & TD_READ ) {
			err = read_data( p_dcb, req);
		} else {
			err = E_OACV;
		}
	} else {		// Device attribute data
		err = read_atr( p_dcb, req);
	}

	return err;
}

/*----------------------------------------------------------------------
 * Write Device
 */
ER dev_uart_writefn( T_DEVREQ *req, T_MSDI *p_msdi)
{
	T_UART_DCB	*p_dcb;
	ER		err;

	p_dcb = (T_UART_DCB*)(p_msdi->dmsdi.exinf);

	if(req->start >= 0) {	// Device specific data
		if( p_dcb->omode & TD_WRITE) {
			err = write_data( p_dcb, req);
		} else {
			err = E_OACV;
		}
	} else {		// Device attribute data
		err = write_atr( p_dcb, req);
	}

	return err;
}

/*----------------------------------------------------------------------
 * Event Device
 */
ER dev_uart_eventfn( INT evttyp, void *evtinf, T_MSDI *p_msdi)
{
	return E_NOSPT;
}

/*----------------------------------------------------------------------
 * Serial communication Device initialization and registration
 */
EXPORT ER dev_init_uart( UW unit )
{
	T_UART_DCB	*p_dcb;
	T_IDEV		idev;
	T_MSDI		*p_msdi;
	T_DMSDI		dmsdi;
	ER		err;
	INT		i;

	if( unit >= DEV_UART_UNITNM) return E_PAR;

#if TK_SUPPORT_MEMLIB
	p_dcb = (T_UART_DCB*)Kmalloc(sizeof(T_UART_DCB));
	if( p_dcb == NULL) return E_NOMEM;
	dev_uart_cb[unit]	= p_dcb;
#else
	p_dcb = &dev_uart_cb[unit];
#endif

	/* Device registration information */
	dmsdi.exinf	= p_dcb;
	dmsdi.drvatr	= 0;			/* Driver attributes */
	dmsdi.devatr	= TDK_UNDEF;		/* Device attributes */
	dmsdi.nsub	= 0;			/* Number of subunits */
	dmsdi.blksz	= 1;			/* Unique data block size (-1 = unknown) */
	dmsdi.openfn	= dev_uart_openfn;
	dmsdi.closefn	= dev_uart_closefn;
	dmsdi.readfn	= dev_uart_readfn;
	dmsdi.writefn	= dev_uart_writefn;
	dmsdi.eventfn	= dev_uart_eventfn;
	
	knl_strcpy( (char*)dmsdi.devnm, DEVCNF_UART_DEVNAME);
	i = knl_strlen(DEVCNF_UART_DEVNAME);
	dmsdi.devnm[i] = (UB)('a' + unit);
	dmsdi.devnm[i+1] = 0;

	err = msdi_def_dev( &dmsdi, &idev, &p_msdi);
	if(err != E_OK) goto err_2;

	p_dcb->unit	= unit;
	p_dcb->evtmbfid	= idev.evtmbfid;

	/* Low-level device initialization */
	err = dev_uart_llinit( p_dcb);
	if(err != E_OK) goto err_1;

	/* Set default value for attribute data */
	p_dcb->com_speed = DEVCNF_UART_SPEED;
	dev_uart_llctl( unit, LLD_UART_SPEED, DEVCNF_UART_SPEED);
	p_dcb->com_mode = DEVCNF_UART_MODE;
	dev_uart_llctl( unit, LLD_UART_MODE, DEVCNF_UART_MODE);
	p_dcb->snd_tmo = DEVCNF_UART_SND_TMO;
	p_dcb->rcv_tmo = DEVCNF_UART_RCV_TMO;

	return E_OK;

err_1:
	msdi_del_dev(p_msdi);
err_2:
	Kfree(p_dcb);
	return err;
}

#endif		/* DEV_UART_ENABLE */
#endif		/* USE_SDEV_DRV */
