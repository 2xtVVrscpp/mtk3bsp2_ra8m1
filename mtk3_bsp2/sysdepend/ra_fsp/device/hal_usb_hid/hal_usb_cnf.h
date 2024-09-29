/*
 *----------------------------------------------------------------------
 *    micro T-Kernel 3.0 BSP 2.0
 *
 *    Copyright (C) 2023-2024 by Ken Sakamura.
 *    This software is distributed under the T-License 2.1.
 *----------------------------------------------------------------------
 *
 *    Released by TRON Forum(http://www.tron.org) at 2024/02.
 *
 *----------------------------------------------------------------------
 */

/*
 *	hal_uart_cnf.h
 *	USB device driver (RA FSP)
 *		Device configuration file
 */
#ifndef	_DEV_HAL_USB_CNF_H_
#define	_DEV_HAL_USB_CNF_H_

#define DEVNAME_HAL_USB		"husb"
#define DEV_HAL_USB_TMOUT	(500)

#define DEV_HAL_USB_UNITNM	(4)	// Number of USB units (max 26)

#endif	/* _DEV_HAL_USB_CNF_H_ */
