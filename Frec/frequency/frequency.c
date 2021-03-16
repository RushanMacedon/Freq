#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "nrf_drv_timer.h"
#include "bsp.h"
#include "app_error.h"
#include "frequency.h"

const nrf_drv_timer_t TIMER_FREQ = NRF_DRV_TIMER_INSTANCE(0);
nrf_drv_timer_config_t timer_cfg;
void timer_led_event_handler(nrf_timer_event_t event_type, void* p_context)
{
 
  
    switch (event_type)
    {
        case NRF_TIMER_EVENT_COMPARE0:
            nrf_gpio_pin_toggle(p_t.pin_number);
            break;

        default:
            //Do nothing.
            break;
    }
}

void freq_init(freq_t *p_t)
{
   nrf_gpio_cfg_output(p_t->pin_number);
     nrf_drv_timer_config_t timer_cfgd = {                                                                               \
    .frequency          = (nrf_timer_frequency_t)TIMER_DEFAULT_CONFIG_FREQUENCY,\
    .mode               = (nrf_timer_mode_t)TIMER_DEFAULT_CONFIG_MODE,          \
    .bit_width          = (nrf_timer_bit_width_t)TIMER_DEFAULT_CONFIG_BIT_WIDTH,\
    .interrupt_priority = TIMER_DEFAULT_CONFIG_IRQ_PRIORITY,                    \
    .p_context          = NULL                                                  \
};
   timer_cfg = timer_cfgd;  
}

void freq_timer_start(uint32_t frequency)
 {
    uint32_t time_us = 1000000/(2*frequency); 
    uint32_t time_ticks;
    uint32_t err_code = NRF_SUCCESS;
    
    err_code = nrf_drv_timer_init(&TIMER_FREQ, &timer_cfg, timer_led_event_handler);
    APP_ERROR_CHECK(err_code);
    time_ticks = nrf_drv_timer_us_to_ticks(&TIMER_FREQ, time_us);

    nrf_drv_timer_extended_compare(
         &TIMER_FREQ, NRF_TIMER_CC_CHANNEL0, time_ticks, NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, true);

    nrf_drv_timer_enable(&TIMER_FREQ);
 }     
 
  void freq_timer_stop(void)
 {
     nrf_drv_timer_disable(&TIMER_FREQ);
     nrf_drv_timer_uninit(&TIMER_FREQ);
 }
 
 