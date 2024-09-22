/* generated vector source file - do not edit */
#include "bsp_api.h"
/* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
#if VECTOR_DATA_IRQ_COUNT > 0
        #if __has_include("r_ioport.h")
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = adc_scan_end_isr, /* ADC0 SCAN END (End of A/D scanning operation) */
            [1] = i3c_rcv_isr, /* I3C0 RCV STATUS (Receive status buffer full) */
            [2] = i3c_resp_isr, /* I3C0 RESPONSE (Response status buffer full) */
            [3] = i3c_rx_isr, /* I3C0 RX (Receive) */
            [4] = i3c_tx_isr, /* I3C0 TX (Transmit) */
            [5] = i3c_ibi_isr, /* I3C0 IBI (IBI status buffer full) */
            [6] = i3c_eei_isr, /* I3C0 EEI (Error) */
        };
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] =
        {
            [0] = BSP_PRV_IELS_ENUM(EVENT_ADC0_SCAN_END), /* ADC0 SCAN END (End of A/D scanning operation) */
            [1] = BSP_PRV_IELS_ENUM(EVENT_I3C0_RCV_STATUS), /* I3C0 RCV STATUS (Receive status buffer full) */
            [2] = BSP_PRV_IELS_ENUM(EVENT_I3C0_RESPONSE), /* I3C0 RESPONSE (Response status buffer full) */
            [3] = BSP_PRV_IELS_ENUM(EVENT_I3C0_RX), /* I3C0 RX (Receive) */
            [4] = BSP_PRV_IELS_ENUM(EVENT_I3C0_TX), /* I3C0 TX (Transmit) */
            [5] = BSP_PRV_IELS_ENUM(EVENT_I3C0_IBI), /* I3C0 IBI (IBI status buffer full) */
            [6] = BSP_PRV_IELS_ENUM(EVENT_I3C0_EEI), /* I3C0 EEI (Error) */
        };
        #elif __has_include("r_ioport_b.h")
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_IRQ_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
            [BSP_PRV_IELS_ENUM(ADC0_SCAN_END)] = adc_scan_end_isr, /* ADC0 SCAN END (End of A/D scanning operation) */
            [BSP_PRV_IELS_ENUM(I3C0_RCV_STATUS)] = i3c_rcv_isr, /* I3C0 RCV STATUS (Receive status buffer full) */
            [BSP_PRV_IELS_ENUM(I3C0_RESPONSE)] = i3c_resp_isr, /* I3C0 RESPONSE (Response status buffer full) */
            [BSP_PRV_IELS_ENUM(I3C0_RX)] = i3c_rx_isr, /* I3C0 RX (Receive) */
            [BSP_PRV_IELS_ENUM(I3C0_TX)] = i3c_tx_isr, /* I3C0 TX (Transmit) */
            [BSP_PRV_IELS_ENUM(I3C0_IBI)] = i3c_ibi_isr, /* I3C0 IBI (IBI status buffer full) */
            [BSP_PRV_IELS_ENUM(I3C0_EEI)] = i3c_eei_isr, /* I3C0 EEI (Error) */
        };
        #endif
        #endif
