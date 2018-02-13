/*
 * timer.c
 *
 *  Created on: 2018Äê2ÔÂ12ÈÕ
 *      Author: delvis
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "global.h"

struct      timer_cfg_t {


    uint16_t    tim_periph_clock;
    uint16_t    period;
    uint16_t    prescaler;
    uint16_t    clock_division;
    uint16_t    counter_mode;
    struct      timer_init_t {

        uint16_t    iqrn;
        uint16_t    preemption_priority;
        uint16_t    sub_priority;

    } irq;
};

struct      timer_t{

    struct timer_t*    self;
    uint32_t    counter;
    struct  timer_cfg_t configure;
    TIM_TypeDef* tim_num;

    void    (*init)( struct timer_t *self );
    void    (*set_time)( struct timer_t *self, uint32 time_val );
    void    (*start)( struct timer_t *self );
    void    (*stop) (struct timer_t *self);
    bool    (*check_status) (struct timer_t *self );
    void    (*clear_interrupt_flag) ( struct timer_t *self );
};


void    timer_init( struct timer_t *self );
void    timer_set_time( struct timer_t *self, uint32 time_val );
void    timer_start( struct timer_t *self );
void    timer_stop( struct timer_t *self );
bool    timer_check_status( struct timer_t *self );
void    timer_clear_interrupt_flag( struct timer_t *self );

#endif /* TIMER_C_ */
