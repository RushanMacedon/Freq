

typedef struct
{
    uint32_t pin_number;
}Freq;

Freq p_t;
nrf_drv_timer_config_t timer_cfg;
 Freq p_t = {
        .pin_number = 17UL,
    };