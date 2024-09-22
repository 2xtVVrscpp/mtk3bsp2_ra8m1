/* generated vector source file - do not edit */
#include "bsp_api.h"
/* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
#if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = sci_b_uart_rxi_isr, /* SCI0 RXI (Receive data full) */
            [1] = sci_b_uart_txi_isr, /* SCI0 TXI (Transmit data empty) */
            [2] = sci_b_uart_tei_isr, /* SCI0 TEI (Transmit end) */
            [3] = sci_b_uart_eri_isr, /* SCI0 ERI (Receive error) */
            [4] = i3c_rcv_isr, /* I3C0 RCV STATUS (Receive status buffer full) */
            [5] = i3c_resp_isr, /* I3C0 RESPONSE (Response status buffer full) */
            [6] = i3c_rx_isr, /* I3C0 RX (Receive) */
            [7] = i3c_tx_isr, /* I3C0 TX (Transmit) */
            [8] = i3c_ibi_isr, /* I3C0 IBI (IBI status buffer full) */
            [9] = i3c_eei_isr, /* I3C0 EEI (Error) */
        };
        #if BSP_FEATURE_ICU_HAS_IELSR
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] =
        {
            [0] = BSP_PRV_VECT_ENUM(EVENT_SCI0_RXI,GROUP0), /* SCI0 RXI (Receive data full) */
            [1] = BSP_PRV_VECT_ENUM(EVENT_SCI0_TXI,GROUP1), /* SCI0 TXI (Transmit data empty) */
            [2] = BSP_PRV_VECT_ENUM(EVENT_SCI0_TEI,GROUP2), /* SCI0 TEI (Transmit end) */
            [3] = BSP_PRV_VECT_ENUM(EVENT_SCI0_ERI,GROUP3), /* SCI0 ERI (Receive error) */
            [4] = BSP_PRV_VECT_ENUM(EVENT_I3C0_RCV_STATUS,GROUP4), /* I3C0 RCV STATUS (Receive status buffer full) */
            [5] = BSP_PRV_VECT_ENUM(EVENT_I3C0_RESPONSE,GROUP5), /* I3C0 RESPONSE (Response status buffer full) */
            [6] = BSP_PRV_VECT_ENUM(EVENT_I3C0_RX,GROUP6), /* I3C0 RX (Receive) */
            [7] = BSP_PRV_VECT_ENUM(EVENT_I3C0_TX,GROUP7), /* I3C0 TX (Transmit) */
            [8] = BSP_PRV_VECT_ENUM(EVENT_I3C0_IBI,GROUP0), /* I3C0 IBI (IBI status buffer full) */
            [9] = BSP_PRV_VECT_ENUM(EVENT_I3C0_EEI,GROUP1), /* I3C0 EEI (Error) */
        };
        #endif
        #endif
