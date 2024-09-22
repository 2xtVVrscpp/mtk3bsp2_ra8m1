/* generated HAL header file - do not edit */
#ifndef HAL_DATA_H_
#define HAL_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_i3c.h"
#include "r_sci_b_uart.h"
#include "r_uart_api.h"
FSP_HEADER
/** I3C on I3C Instance. */
extern const i3c_instance_t g_i3c0;

/** Access the I3C instance using these structures when calling API functions directly (::p_api is not used). */
extern i3c_instance_ctrl_t g_i3c0_ctrl;
extern const i3c_cfg_t g_i3c0_cfg;

#ifndef g_i3c0_callback
void g_i3c0_callback(i3c_callback_args_t const *const p_args);
#endif
/** UART on SCI Instance. */
extern const uart_instance_t g_uart0;

/** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_b_uart_instance_ctrl_t g_uart0_ctrl;
extern const uart_cfg_t g_uart0_cfg;
extern const sci_b_uart_extended_cfg_t g_uart0_cfg_extend;

#ifndef NULL
void NULL(uart_callback_args_t *p_args);
#endif
void hal_entry(void);
void g_hal_init(void);
FSP_FOOTER
#endif /* HAL_DATA_H_ */
