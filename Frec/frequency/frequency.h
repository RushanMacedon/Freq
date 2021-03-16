#ifndef FREQUENCY_H_
#define FREQUENCY_H_

#include <stdint.h>
#include "nrf_drv_timer.h"

typedef struct
{
    uint32_t pin_number;
}freq_t;
extern freq_t p_t;


void freq_init(freq_t *);
void freq_timer_start(uint32_t);
void freq_timer_stop(void);
 #endif
