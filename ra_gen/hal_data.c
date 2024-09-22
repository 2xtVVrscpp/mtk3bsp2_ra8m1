/* generated HAL source file - do not edit */
#include "hal_data.h"
/* Macros to tie dynamic ELC links to ADC_TRIGGER_SYNC_ELC option in adc_trigger_t. */
#define ADC_TRIGGER_ADC0        ADC_TRIGGER_SYNC_ELC
#define ADC_TRIGGER_ADC0_B      ADC_TRIGGER_SYNC_ELC
#define ADC_TRIGGER_ADC1        ADC_TRIGGER_SYNC_ELC
#define ADC_TRIGGER_ADC1_B      ADC_TRIGGER_SYNC_ELC
/* Control structure for storing the driver's internal state. */
i3c_instance_ctrl_t g_i3c0_ctrl;

/* Extended configuration for this instance of I3C. */
const i3c_extended_cfg_t g_i3c0_cfg_extend =
        { .bitrate_settings =
        {
        /* Standard Open Drain; Actual Frequency (Hz): 1000000, Actual High Period (ns): 162.5. */
        .stdbr = ((26U << R_I3C0_STDBR_SBRHO_Pos) | (134U << R_I3C0_STDBR_SBRLO_Pos))
        /* Standard Push-Pull; Actual Frequency (Hz): 3333333.3, Actual High Period (ns): 162.5. */
        | ((26U << R_I3C0_STDBR_SBRHP_Pos) | (22U << R_I3C0_STDBR_SBRLP_Pos)) | (0U << R_I3C0_STDBR_DSBRPO_Pos),
          /* Extended Open Drain; Actual Frequency (Hz): 1000000, Actual High Period (ns): 162.5. */
          .extbr = ((26U << R_I3C0_EXTBR_EBRHO_Pos) | (134U << R_I3C0_EXTBR_EBRLO_Pos))
          /* Extended Push-Pull; Actual Frequency (Hz): 3333333.3, Actual High Period (ns): 162.5.  */
          | ((26U << R_I3C0_EXTBR_EBRHP_Pos) | (22U << R_I3C0_EXTBR_EBRLP_Pos)),

          .clock_stalling =
          { .assigned_address_phase_enable = 0,
            .transition_phase_enable = 0,
            .parity_phase_enable = 0,
            .ack_phase_enable = 0,
            .clock_stalling_time = 0, }, },
          .ibi_control.hot_join_acknowledge = 0, .ibi_control.notify_rejected_hot_join_requests = 0, .ibi_control.notify_rejected_mastership_requests =
                  0,
          .ibi_control.notify_rejected_interrupt_requests = 0, .bus_free_detection_time = 7, .bus_available_detection_time =
                  160,
          .bus_idle_detection_time = 160000, .timeout_detection_enable = false, .slave_command_response_info =
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
          .resp_irq = VECTOR_NUMBER_I3C0_RESPONSE,
#if defined(BSP_MCU_GROUP_RA2E2) && BSP_MCU_GROUP_RA2E2
#if (BSP_IRQ_DISABLED) == 1U
    .rcv_irq = VECTOR_NUMBER_I3C0_RCV_STATUS_GROUP3,
#else
    .rcv_irq = VECTOR_NUMBER_I3C0_RCV_STATUS_GROUP5,
#endif
#else
          .rcv_irq = VECTOR_NUMBER_I3C0_RCV_STATUS,
#endif
          .rx_irq = VECTOR_NUMBER_I3C0_RX,
          .tx_irq = VECTOR_NUMBER_I3C0_TX, .ibi_irq = VECTOR_NUMBER_I3C0_IBI, .eei_irq = VECTOR_NUMBER_I3C0_EEI,

          .ipl = (12),
          .eei_ipl = (12), };

/* Configuration for this instance. */
const i3c_cfg_t g_i3c0_cfg =
{ .channel = 0,
  .device_type = I3C_DEVICE_TYPE_MAIN_MASTER,
  .p_callback = g_i3c0_callback,
  .p_context = NULL,
  .p_extend = &g_i3c0_cfg_extend, };

/* Instance structure to use this module. */
const i3c_instance_t g_i3c0 =
{ .p_ctrl = &g_i3c0_ctrl, .p_cfg = &g_i3c0_cfg, .p_api = &g_i3c_on_i3c };
adc_instance_ctrl_t g_adc0_ctrl;
const adc_extended_cfg_t g_adc0_cfg_extend =
{ .add_average_count = ADC_ADD_OFF,
  .clearing = ADC_CLEAR_AFTER_READ_ON,
  .trigger_group_b = ADC_TRIGGER_SYNC_ELC,
  .double_trigger_mode = ADC_DOUBLE_TRIGGER_DISABLED,
  .adc_vref_control = ADC_VREF_CONTROL_VREFH,
  .enable_adbuf = 0,
#if defined(VECTOR_NUMBER_ADC0_WINDOW_A)
    .window_a_irq        = VECTOR_NUMBER_ADC0_WINDOW_A,
#else
  .window_a_irq = FSP_INVALID_VECTOR,
#endif
  .window_a_ipl = (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_ADC0_WINDOW_B)
    .window_b_irq      = VECTOR_NUMBER_ADC0_WINDOW_B,
#else
  .window_b_irq = FSP_INVALID_VECTOR,
#endif
  .window_b_ipl = (BSP_IRQ_DISABLED), };
const adc_cfg_t g_adc0_cfg =
{ .unit = 0, .mode = ADC_MODE_SINGLE_SCAN, .resolution = ADC_RESOLUTION_12_BIT, .alignment =
          (adc_alignment_t) ADC_ALIGNMENT_RIGHT,
  .trigger = ADC_TRIGGER_SOFTWARE, .p_callback = NULL,
  /** If NULL then do not add & */
#if defined(NULL)
    .p_context           = NULL,
#else
  .p_context = &NULL,
#endif
  .p_extend = &g_adc0_cfg_extend,
#if defined(VECTOR_NUMBER_ADC0_SCAN_END)
    .scan_end_irq        = VECTOR_NUMBER_ADC0_SCAN_END,
#else
  .scan_end_irq = FSP_INVALID_VECTOR,
#endif
  .scan_end_ipl = (10),
#if defined(VECTOR_NUMBER_ADC0_SCAN_END_B)
    .scan_end_b_irq      = VECTOR_NUMBER_ADC0_SCAN_END_B,
#else
  .scan_end_b_irq = FSP_INVALID_VECTOR,
#endif
  .scan_end_b_ipl = (BSP_IRQ_DISABLED), };
#if ((0) | (0))
const adc_window_cfg_t g_adc0_window_cfg =
{
    .compare_mask        =  0,
    .compare_mode_mask   =  0,
    .compare_cfg         = (0) | (0) | (0) | (ADC_COMPARE_CFG_EVENT_OUTPUT_OR),
    .compare_ref_low     = 0,
    .compare_ref_high    = 0,
    .compare_b_channel   = (ADC_WINDOW_B_CHANNEL_0),
    .compare_b_mode      = (ADC_WINDOW_B_MODE_LESS_THAN_OR_OUTSIDE),
    .compare_b_ref_low   = 0,
    .compare_b_ref_high  = 0,
};
#endif
const adc_channel_cfg_t g_adc0_channel_cfg =
{ .scan_mask = ADC_MASK_CHANNEL_0 | ADC_MASK_CHANNEL_4 | ADC_MASK_CHANNEL_7 | 0,
  .scan_mask_group_b = 0,
  .priority_group_a = ADC_GROUP_A_PRIORITY_OFF,
  .add_mask = 0,
  .sample_hold_mask = 0,
  .sample_hold_states = 24,
#if ((0) | (0))
    .p_window_cfg        = (adc_window_cfg_t *) &g_adc0_window_cfg,
#else
  .p_window_cfg = NULL,
#endif
        };
/* Instance structure to use this module. */
const adc_instance_t g_adc0 =
{ .p_ctrl = &g_adc0_ctrl, .p_cfg = &g_adc0_cfg, .p_channel_cfg = &g_adc0_channel_cfg, .p_api = &g_adc_on_adc };
void g_hal_init(void)
{
    g_common_init ();
}
