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

#ifndef	_DEV_HAL_USB_H_
#define	_DEV_HAL_USB_H_
/*
 *	hal_uart.h
 *	USB device driver (RA FSP)
*/
/*----------------------------------------------------------------------
 * USB Device
 */
#define DEV_HAL_USB1   0
#define DEV_HAL_USB2   1
#define DEV_HAL_USB3   2
#define DEV_HAL_USB4   3

/*----------------------------------------------------------------------
 * Attribute data
 */
#define TDN_HAL_USB_MODE	(-100)	// USB Mode
#define TDN_HAL_USB_TADR	(-101)	// Target Address
#define TDN_HAL_USB_MAX		(-101)

#define HAL_USB_MODE_CNT	(0)	// USB Mode: Controller mode
#define HAL_USB_MODE_TAR	(1)	// USB Mode: Target mode

/*----------------------------------------------------------------------
 * Device driver initialization and registration
 */

IMPORT ER dev_init_hal_usb( UW unit, usb_instance_ctrl_t *husb, const usb_cfg_t *cuart );

/*----------------------------------------------------------------------
 * USB register access support function
 */
EXPORT ER hal_usb_read_reg(ID dd, UW sadr, UW radr, UB *data);
EXPORT ER hal_usb_write_reg(ID dd, UW sadr, UW radr, UB data);

/*----------------------------------------------------------------------
 * USB register access support function
 */

#endif	/* _DEV_HAL_USB_H_ */
