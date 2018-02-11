// STM32F103   Project.
/****************************************************************************/
/*                                                                          */
/*  @file       : *_led.h                                                   */
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

#ifndef LED_H_
#define LED_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"


enum leds_e{
    LED0,LED1
};

/**
 * \brief    struct led_hw_t details.
 *
 * \offer    Wei Haochen
 *
 * \param    uint16_t led_x_pin:
 *           [Configure STM32 GPIO function.]
 *           [you should give the value in the external initial function.]
 *           _______
 *           Example:_______________________________
 *           -> GPIO_InitTypeDef  GPIO_InitStructure;
 *           -> GPIO_InitStructure.GPIO_Pin = self->hw.led_x_pin;
 *
 * \param    GPIO_TypeDef *led_x_port:
 *           [Configure STM32 GPIO function.]
 *           _______
 *           Example 1:______________________________________________
 *           -> GPIO_Init(self->hw.led_0_port, &GPIO_InitStructure);
 *           and Example 2:
 *           -> GPIO_SetBits( self->hw.led_0_port,self->hw.led_0_pin);
 *           -> GPIO_ResetBits( self->hw.led_0_port,self->hw.led_0_pin);
 *
 * \param    uint32_t    led_gpio_clock;:
 *           [Configure STM32 GPIO RCC clock function.]
 *           [You should give the value in the external initial function.]
 *           _______
 *           Example:______________________________________________________________
 *           -> self->hw.led_gpio_clock = RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD;
 *           -> RCC_APB2PeriphClockCmd(self->hw.led_gpio_clock, ENABLE);
 *                     ____       ___________
 * \note     include the led hardware options using in STM32 GPIO configure.
 *           This structure is not used alone and structure defined in struct led_t;
 */
typedef struct led_hw_t {

    uint16_t    led_0_pin;
    GPIO_TypeDef    *led_0_port;

    uint16_t    led_1_pin;
    GPIO_TypeDef    *led_1_port;

    uint32_t    led_gpio_clock;

} LED_HW, *PLED_HW ;


/**
 * \brief    struct led_t details.
 *
 * \offer    Wei Haochen
 *
 * \param    LED_HW hw;
 *           [stm32 GPIO options.]
 *           [detail on struct led_hw_t defined;]
 *
 * \param    enum leds_e led_num;
 *           [STM32 board have total of two leds, define enum type expressed.]
 *
 * \param    struct led_t    *self;
 *           [self list operation pointer.]
 *
 * \params   pointer functions
 *           [You can find real define in led.c document]
 *           [In the external initial function in the main.c document,
 *            the pointer function and the entity function to establish contact.]
 *
 * \note     the struct led_t need define in the main.c documents.
 */
typedef  struct led_t {

    LED_HW  hw;
    enum    leds_e led_num;
    struct led_t    *self;

    void    (*init)( struct led_t *self );
    void    (*on)( struct led_t *self, enum leds_e led_num );
    void    (*off)( struct led_t *self, enum leds_e led_num );

} LED, *PLED;


extern void     led_off( PLED self, enum leds_e led_num );
extern void     led_on( PLED self, enum leds_e led_num );
extern void     led_init( PLED self );

#endif /* LED_H_ */
