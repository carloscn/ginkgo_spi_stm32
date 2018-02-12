/*
 * timer.c
 *
 *  Created on: 2018Äê2ÔÂ12ÈÕ
 *      Author: delvis
 */

#include "timer.h"

void    timer_init( struct timer_t *self )
{
    TIM_TimeBaseInitTypeDef  timer_cfg;
    NVIC_InitTypeDef ncic_cfg;
    RCC_APB1PeriphClockCmd( self->configure.tim_periph_clock, ENABLE );
    timer_cfg.TIM_Period = self->configure.period;
    timer_cfg.TIM_Prescaler = self->configure.prescaler;
    timer_cfg.TIM_ClockDivision = self->configure.clock_division;
    timer_cfg.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit( self->tim_num , &timer_cfg);
    TIM_ITConfig( self->tim_num , TIM_IT_Update , ENABLE);
    ncic_cfg.NVIC_IRQChannel = self->configure.irq.iqrn;
    ncic_cfg.NVIC_IRQChannelPreemptionPriority = self->configure.irq.preemption_priority;
    ncic_cfg.NVIC_IRQChannelSubPriority = self->configure.irq.sub_priority;
    ncic_cfg.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&ncic_cfg);

}

void    timer_set_time( struct timer_t *self, uint32 time_val )
{

}

void    timer_start( struct timer_t *self )
{
    TIM_Cmd(self->tim_num, ENABLE);
}

void    timer_stop( struct timer_t *self )
{
    TIM_Cmd(self->tim_num, DISABLE);
}

bool    timer_check_status( struct timer_t *self )
{
    if( TIM_GetITStatus( self->tim_num, TIM_IT_Update ) == RESET ) {
        return false;
    }else {
        return true;
    }

}

void    timer_clear_interrupt_flag( struct timer_t *self )
{
    TIM_ClearITPendingBit( self->tim_num, TIM_IT_Update );
}
