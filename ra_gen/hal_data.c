/* generated HAL source file - do not edit */
#include "hal_data.h"
/* Control structure for storing the driver's internal state. */
i3c_instance_ctrl_t g_i3c0_ctrl;

/* Extended configuration for this instance of I3C. */
const i3c_extended_cfg_t g_i3c0_cfg_extend =
        { .bitrate_settings =
        {
        /* Standard Open Drain; Actual Frequency (Hz): 1000000, Actual High Period (ns): 150. Error: The Standard Open Drain High Period is off by more than 10%. */
        .stdbr = ((3U << R_I3C0_STDBR_SBRHO_Pos) | (17U << R_I3C0_STDBR_SBRLO_Pos))
        /* Standard Push-Pull; Actual Frequency (Hz): 3333333.3, Actual High Period (ns): 150. Error: The Standard Push-Pull High Period is off by more than 10%. */
        | ((3U << R_I3C0_STDBR_SBRHP_Pos) | (3U << R_I3C0_STDBR_SBRLP_Pos)) | (0U << R_I3C0_STDBR_DSBRPO_Pos),
          /* Extended Open Drain; Actual Frequency (Hz): 1000000, Actual High Period (ns): 150. Error: The Extended Open Drain High Period is off by more than 10%. */
          .extbr = ((3U << R_I3C0_EXTBR_EBRHO_Pos) | (17U << R_I3C0_EXTBR_EBRLO_Pos))
          /* Extended Push-Pull; Actual Frequency (Hz): 3333333.3, Actual High Period (ns): 150. Error: The Extended Push-Pull High Period is off by more than 10%.  */
          | ((3U << R_I3C0_EXTBR_EBRHP_Pos) | (3U << R_I3C0_EXTBR_EBRLP_Pos)),

          .clock_stalling =
          { .assigned_address_phase_enable = 0,
            .transition_phase_enable = 0,
            .parity_phase_enable = 0,
            .ack_phase_enable = 0,
            .clock_stalling_time = 0, }, },
          .ibi_control.hot_join_acknowledge = 0, .ibi_control.notify_rejected_hot_join_requests = 0, .ibi_control.notify_rejected_mastership_requests =
                  0,
          .ibi_control.notify_rejected_interrupt_requests = 0, .bus_free_detection_time = 1, .bus_available_detection_time =
                  20,
          .bus_idle_detection_time = 20000, .timeout_detection_enable = false, .slave_command_response_info =
          { .inband_interrupt_enable = false,
            .mastership_request_enable = 0,
            .hotjoin_request_enable = false,
            .activity_state = I3C_ACTIVITY_STATE_ENTAS0,
            .write_length = 65535,
            .read_length = 65535,
            .ibi_payload_length = 0,
            .write_data_rate = I3C_DATA_RATE_SETTING_2MHZ,
            .read_data_rate = I3C_DATA_RATE_SETTING_2MHZ,
            .clock_data_turnaround = I3C_CLOCK_DATA_TURNAROUND_8NS,
            .read_turnaround_time_enable = false,
            .read_turnaround_time = 0,
            .oscillator_frequency = 0,
            .oscillator_inaccuracy = 0, },
          .resp_irq = VECTOR_NUMBER_I3C0_RESPONSE, .rcv_irq = VECTOR_NUMBER_I3C0_RCV_STATUS, .rx_irq =
                  VECTOR_NUMBER_I3C0_RX,
          .tx_irq = VECTOR_NUMBER_I3C0_TX, .ibi_irq = VECTOR_NUMBER_I3C0_IBI, .eei_irq = VECTOR_NUMBER_I3C0_EEI,

          .ipl = (12),
          .eei_ipl = (12), };

/* Configuration for this instance. */
const i3c_cfg_t g_i3c0_cfg =
{ .channel = 0, .device_type = I3C_DEVICE_TYPE_SLAVE, .p_callback = g_i3c0_callback, .p_context = NULL, .p_extend =
          &g_i3c0_cfg_extend, };

/* Instance structure to use this module. */
const i3c_instance_t g_i3c0 =
{ .p_ctrl = &g_i3c0_ctrl, .p_cfg = &g_i3c0_cfg, .p_api = &g_i3c_on_i3c };
sci_b_uart_instance_ctrl_t g_uart0_ctrl;

sci_b_baud_setting_t g_uart0_baud_setting =
        {
        /* Baud rate calculated with 1.725% error. */.baudrate_bits_b.abcse = 0,
          .baudrate_bits_b.abcs = 0, .baudrate_bits_b.bgdm = 1, .baudrate_bits_b.cks = 0, .baudrate_bits_b.brr = 31, .baudrate_bits_b.mddr =
                  (uint8_t) 256,
          .baudrate_bits_b.brme = false };

/** UART extended configuration for UARTonSCI HAL driver */
const sci_b_uart_extended_cfg_t g_uart0_cfg_extend =
{ .clock = SCI_B_UART_CLOCK_INT, .rx_edge_start = SCI_B_UART_START_BIT_FALLING_EDGE, .noise_cancel =
          SCI_B_UART_NOISE_CANCELLATION_DISABLE,
  .rx_fifo_trigger = SCI_B_UART_RX_FIFO_TRIGGER_MAX, .p_baud_setting = &g_uart0_baud_setting, .flow_control =
          SCI_B_UART_FLOW_CONTROL_RTS,
#if 0xFF != 0xFF
                .flow_control_pin       = BSP_IO_PORT_FF_PIN_0xFF,
                #else
  .flow_control_pin = (bsp_io_port_pin_t) UINT16_MAX,
#endif
  .rs485_setting =
  { .enable = SCI_B_UART_RS485_DISABLE,
    .polarity = SCI_B_UART_RS485_DE_POLARITY_HIGH,
    .assertion_time = 1,
    .negation_time = 1, } };

/** UART interface configuration */
const uart_cfg_t g_uart0_cfg =
{ .channel = 0, .data_bits = UART_DATA_BITS_8, .parity = UART_PARITY_OFF, .stop_bits = UART_STOP_BITS_1, .p_callback =
          NULL,
  .p_context = NULL, .p_extend = &g_uart0_cfg_extend,
#define RA_NOT_DEFINED (1)
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
  .p_transfer_tx = NULL,
#else
                .p_transfer_tx       = &RA_NOT_DEFINED,
#endif
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
  .p_transfer_rx = NULL,
#else
                .p_transfer_rx       = &RA_NOT_DEFINED,
#endif
#undef RA_NOT_DEFINED
  .rxi_ipl = (12),
  .txi_ipl = (12), .tei_ipl = (12), .eri_ipl = (12),
#if defined(VECTOR_NUMBER_SCI0_RXI)
                .rxi_irq             = VECTOR_NUMBER_SCI0_RXI,
#else
  .rxi_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SCI0_TXI)
                .txi_irq             = VECTOR_NUMBER_SCI0_TXI,
#else
  .txi_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SCI0_TEI)
                .tei_irq             = VECTOR_NUMBER_SCI0_TEI,
#else
  .tei_irq = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SCI0_ERI)
                .eri_irq             = VECTOR_NUMBER_SCI0_ERI,
#else
  .eri_irq = FSP_INVALID_VECTOR,
#endif
        };

/* Instance structure to use this module. */
const uart_instance_t g_uart0 =
{ .p_ctrl = &g_uart0_ctrl, .p_cfg = &g_uart0_cfg, .p_api = &g_uart_on_sci_b };
void g_hal_init(void)
{
    g_common_init ();
}
