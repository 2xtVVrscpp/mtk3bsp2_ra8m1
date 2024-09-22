/* generated vector header file - do not edit */
#ifndef VECTOR_DATA_H
#define VECTOR_DATA_H
#ifdef __cplusplus
        extern "C" {
        #endif
/* Number of interrupts allocated */
#ifndef VECTOR_DATA_IRQ_COUNT
#define VECTOR_DATA_IRQ_COUNT    (7)
#endif
/* ISR prototypes */
void adc_scan_end_isr(void);
void i3c_rcv_isr(void);
void i3c_resp_isr(void);
void i3c_rx_isr(void);
void i3c_tx_isr(void);
void i3c_ibi_isr(void);
void i3c_eei_isr(void);

#if __has_include("r_ioport.h")
        /* Vector table allocations */
        #define VECTOR_NUMBER_ADC0_SCAN_END ((IRQn_Type) 0) /* ADC0 SCAN END (End of A/D scanning operation) */
        #define ADC0_SCAN_END_IRQn          ((IRQn_Type) 0) /* ADC0 SCAN END (End of A/D scanning operation) */
        #define VECTOR_NUMBER_I3C0_RCV_STATUS ((IRQn_Type) 1) /* I3C0 RCV STATUS (Receive status buffer full) */
        #define I3C0_RCV_STATUS_IRQn          ((IRQn_Type) 1) /* I3C0 RCV STATUS (Receive status buffer full) */
        #define VECTOR_NUMBER_I3C0_RESPONSE ((IRQn_Type) 2) /* I3C0 RESPONSE (Response status buffer full) */
        #define I3C0_RESPONSE_IRQn          ((IRQn_Type) 2) /* I3C0 RESPONSE (Response status buffer full) */
        #define VECTOR_NUMBER_I3C0_RX ((IRQn_Type) 3) /* I3C0 RX (Receive) */
        #define I3C0_RX_IRQn          ((IRQn_Type) 3) /* I3C0 RX (Receive) */
        #define VECTOR_NUMBER_I3C0_TX ((IRQn_Type) 4) /* I3C0 TX (Transmit) */
        #define I3C0_TX_IRQn          ((IRQn_Type) 4) /* I3C0 TX (Transmit) */
        #define VECTOR_NUMBER_I3C0_IBI ((IRQn_Type) 5) /* I3C0 IBI (IBI status buffer full) */
        #define I3C0_IBI_IRQn          ((IRQn_Type) 5) /* I3C0 IBI (IBI status buffer full) */
        #define VECTOR_NUMBER_I3C0_EEI ((IRQn_Type) 6) /* I3C0 EEI (Error) */
        #define I3C0_EEI_IRQn          ((IRQn_Type) 6) /* I3C0 EEI (Error) */
        #endif

#ifdef __cplusplus
        }
        #endif
#endif /* VECTOR_DATA_H */
