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

#ifndef	_DEV_HAL_UART_H_
#define	_DEV_HAL_UART_H_
/*
 *	hal_uart.h
 *	UART device driver (RA FSP)
*/
/*----------------------------------------------------------------------
 * UART Device
 */
#define DEV_HAL_UART1   0
#define DEV_HAL_UART2   0
#define DEV_HAL_UART3   0
#define DEV_HAL_UART4   0


/*----------------------------------------------------------------------
 * Attribute data
 */
#define TDN_HAL_UART_MODE	(-100)	// UART Mode
#define TDN_HAL_UART_TADR	(-101)	// Target Address
#define TDN_HAL_UART_MAX		(-101)

#define HAL_UART_MODE_CNT	(0)	// UART Mode: Controller mode
#define HAL_UART_MODE_TAR	(1)	// UART Mode: Target mode

/*----------------------------------------------------------------------
 * Device driver initialization and registration
 */

IMPORT ER dev_init_hal_uart( UW unit, sci_b_uart_instance_ctrl_t *huart, const uart_cfg_t *cuart );

/*----------------------------------------------------------------------
 * UART register access support function
 */
EXPORT ER hal_uart_read_reg(ID dd, UW sadr, UW radr, UB *data);
EXPORT ER hal_uart_write_reg(ID dd, UW sadr, UW radr, UB data);

#endif	/* _DEV_HAL_UART_H_ */
