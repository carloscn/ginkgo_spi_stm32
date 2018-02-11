// STM32F103   Project.
/****************************************************************************/
/*                                                                          */
/*  @file       : *_led.c                                                   */
/*  @Copyright  : WeiHaochen (p) 2018 MULTIBEANS_ORG All rights reserved.   */
/*  @Revision   : Ver 1.0.                                                  */
/*  @Data       : 2018.02.08 Release.                                       */
/*  @Belong     : PROJECT.                                                  */
/*                                                                          */
/*  **code : (GBK/GB2312) in Windows 10_x64. Keil uVision472 platform.      */
/****************************************************************************/
/*  @Attention:                                                             */
/*  ---------------------------------------------------------------------   */
/*  |    Data    |  Behavior |     Offer     |          Content         |   */
/*  | 2018.02.08 |   create  |DelvisBeans(M) | ceate the document.      |   */
/*  ---------------------------------------------------------------------   */
/*                                                            MULTIBEANS.   */
/****************************************************************************/
#include "global.h"
#include "led.h"


/**
 * \brief    led_init function.
 *
 * \offer    Wei Haochen
 *
 * \param    struct led_t pointer in led.h
 *
 * \return   None.
 *
 *
 * \note     gpio clock -> gpio pin -> init state.
 */
void    led_init( struct led_t* self )
{

    GPIO_InitTypeDef  led_gpio_cfg;

    RCC_APB2PeriphClockCmd(self->hw.led_gpio_clock, ENABLE);

    led_gpio_cfg.GPIO_Pin = self->hw.led_0_pin;
    led_gpio_cfg.GPIO_Mode = GPIO_Mode_Out_PP;
    led_gpio_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( self->hw.led_0_port, &led_gpio_cfg );

    led_gpio_cfg.GPIO_Pin = self->hw.led_1_pin;
    GPIO_Init( self->hw.led_1_port, &led_gpio_cfg );

    GPIO_WriteBit( self->hw.led_0_port , self->hw.led_0_pin,1);
    GPIO_WriteBit( self->hw.led_1_port , self->hw.led_1_pin,1);

}

/**
 * \brief    led_on function.
 *
 * \offer    Wei Haochen
 *
 * \param    struct led_t pointer in led.h
 *
 * \param    enum leds_e led_num in led.h
 *           if you want to light led_0 , transmit the param LED0.
 *
 * \return   None.
 *
 * \note     open the led
 */
void    led_on( struct led_t* self, enum leds_e led_num )
{
    if( led_num == LED0 ) {
        GPIO_WriteBit(self->hw.led_0_port,self->hw.led_0_pin,0);
    }else if( led_num == LED1 ){
        GPIO_WriteBit(self->hw.led_1_port,self->hw.led_1_pin,0);
    }
}

/**
 * \brief    led_off function.
 *
 * \offer    Wei Haochen
 *
 * \param    struct led_t pointer in led.h
 *
 * \param    enum leds_e led_num in led.h
 *           if you want to put off led_0 , transmit the param LED0.
 *
 * \return   None.
 *
 * \note     close the led.
 */
void    led_off( struct led_t* self, enum leds_e led_num )
{
    if( led_num == LED0 ) {
        GPIO_WriteBit(self->hw.led_0_port,self->hw.led_0_pin,1);
    }else if( led_num == LED1 ){
        GPIO_WriteBit(self->hw.led_1_port,self->hw.led_1_pin,1);
    }
}

