// STM32F103   Project.
/****************************************************************************/
/*                                                                          */
/*  @file       : *_Main.c                                                  */
/*  @Copyright  : WeiHaochen (p) 2018 MULTIBEANS_ORG All rights reserved. 	*/
/*  @Revision   : Ver 1.0.                                                  */
/*  @Data       : 2018.01.21 Release.                                       */
/*  @Github     : https://github.com/lifimlt/ginkgo_spi_stm32.git           */
/*  @Belong     : PROJECT.                                                  */
/*                                                                          */
/*  **code : (GBK/GB2312) in Windows 10_x64. Keil uVision472 platform.      */
/****************************************************************************/
/*  @Attention:                                                             */
/*  ---------------------------------------------------------------------   */
/*  |    Data    |  Behavior |     Offer     |          Content         |   */
/*  | 2018.01.21 |   create  |DelvisBeans(M) | ceate the document.      |   */
/*  ---------------------------------------------------------------------   */
/*                                                            MULTIBEANS.   */
/****************************************************************************/
/***
 *
 *                                ,%%%%%%%%,
 *                              ,%%/\%%%%/\%%
 *                             ,%%%\c "" J/%%%
 *                    %.       %%%%/ o  o \%%%
 *                     `%%.     %%%%    _  |%%%
 *                     `%%     `%%%%(__Y__)%%'
 *                     //       ;%%%%`\-/%%%'
 *                    ((       /  `%%%%%%%'
 *                     \\    .'          |
 *                      \\  /       \  | |
 *                       \\/         ) | |
 *                        \         /_ | |__
 *                        (___________))))))) Carlos Lopez. (Wei Haochen)
 *
 * \brief   This project about spi on STM32 drivers 8 channels AD7606 of
 *          ADI company.
 *
 * \License  THIS FILE IS PART OF MULTIBEANS PROJECT ;
 *           all of the files  - The core part of the project;
 *           THIS PROGRAM IS FREE SOFTWARE, JUST NEED GPL 3.0 LICENSE;
 *           YOU SHOULD HAVE RECEIVED A COPY OF WTFPL LICENSE, IF NOT,
 *           MULTIBEANS WILL TAKE APPROPRIATE MEASURES.
 *
 *           * You can download the license on our Github. ->
 *           * -> https://github.com/multibeans  <-
 *           * Copyright (c) 2013-2018 MULTIBEANS ORG. http://www.mltbns.top/
 *           * Copyright (c) 2018 Wei Haochen.  Email: carlos@mltbns.top
 *
 *  \note    void.
 */


#include 	"global.h"
#include    "stdio.h"

void    LED_INIT( struct led_t *led );

struct 	ad9833_t	ad9833_dev, *ad9833_dev_handle;
struct	spi_t		ad9833_spi, *ad9833_spi_handle;
struct  led_t       led_dev,    *led_dev_handle;
struct  spi_t       test_spi;
struct  timer_t     timer, *timer_handle;

uint16_t            rom[256] = {0};






/**
 * \brief    This function is AD7606 start convst
 *
 * \offer    Wei Haochen
 *
 * \param    struct ad7606_t (in ad9833.h document)
 *
 * \return   None.
 *
 *               ____       __________________
 * \note  covst_a    \_____/
 *               ____       __________________
 *        covst_b    \_____/
 *                   |<--->|
 *                     5us
 */
int main(void)
{
    SystemInit();


    NVIC_Configuration();
    led_dev_handle      =   &led_dev;
    ad9833_dev_handle   =   &ad9833_dev;
    ad9833_spi_handle   =   &ad9833_spi;
    timer_handle        =   &timer;


    //AD9833_INIT( ad9833_dev_handle, ad9833_spi_handle );
    SPI_INIT( &test_spi );
    LED_INIT(led_dev_handle);
    TIMER_INIT( timer_handle );
    timer.start(timer_handle);
    while(1) {


        test_spi.write( &test_spi, rom, 256 );



    }
}

void    TIM3_IRQHandler( void )
{
    if( timer_handle->check_status(timer_handle) == true ) {


        if( timer_handle->counter %5 == 0 ) {
            led_dev_handle->on( led_dev_handle, LED0 );
            led_dev_handle->on( led_dev_handle, LED1 );

        }
        if( timer_handle->counter %5 == 3 )  {
            led_dev_handle->off(led_dev_handle, LED0 );
            led_dev_handle->off(led_dev_handle, LED1 );
        }

        timer.counter   ++;
        timer.clear_interrupt_flag( timer_handle );

    }else {
        return;
    }

}


void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    /* Configure and enable ADC interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void	AD9833_INIT( struct ad9833_t *dev, struct spi_t *spi )
{

    SPI_INIT( spi );
    dev->hw.ex_spi	=	spi;
    dev->hw.sdi_pin	=	AD9833_STM32_SPI_PIN_SDI;
    dev->hw.clk_pin	=	AD9833_STM32_SPI_PIN_CLK;
    dev->hw.fsy_pin	=	AD9833_STM32_SPI_PIN_FSYNC;

    dev->init_device								=	&ad9833_init;
    dev->reset_device								=	&ad9833_reset;
    dev->clear_reset_device							=	&ad9833_clear_reset;
    dev->set_register_value							=	&ad9833_set_register_value;
    dev->set_frequency								=	&ad9833_set_frequency;
    dev->set_phase									=	&ad9833_set_phase;
    dev->set_wave									=	&ad9833_set_wave;
    dev->setup_device_para							=	&ad9833_setup_para;
    dev->delay_us									=	&ad9833_delay_us;
    dev->init_device( dev );


}

void    SPI_INIT( struct spi_t *spi_handle )
{
    spi_handle->spi_cfg.num         =   SPI2;
    /*
     * Set spi hardware parameters.
     * -> Do not care about the pin correspondence, because it is using a peripheral SPI.
     * */

    if( spi_handle->spi_cfg.num ==  SPI1) {
        spi_handle->hw.periph_clock     =   RCC_APB2Periph_SPI1;
        spi_handle->hw.gpio_clock       =   RCC_APB2Periph_GPIOA;
        spi_handle->hw.clk_pin          =   GPIO_Pin_5;
        spi_handle->hw.miso_pin         =   GPIO_Pin_6;
        spi_handle->hw.mosi_pin         =   GPIO_Pin_7;
        spi_handle->hw.ce_pin           =   0;
        spi_handle->hw.port             =   GPIOA;
    }else if( spi_handle->spi_cfg.num == SPI2 ) {
        spi_handle->hw.periph_clock     =   RCC_APB1Periph_SPI2 ;
        spi_handle->hw.gpio_clock       =   RCC_APB2Periph_GPIOB;
        spi_handle->hw.clk_pin          =   GPIO_Pin_13;
        spi_handle->hw.miso_pin         =   GPIO_Pin_14;
        spi_handle->hw.mosi_pin         =   GPIO_Pin_15;
        spi_handle->hw.ce_pin           =   0;
        spi_handle->hw.port             =   GPIOB;
    }

    /*
     * Set SPI properties.
     *
     *      SPI_CLK_OUTOFPHASE  - Clock is Delayed by half clock cycle.
     *      SPI_CLK_POL_HIGH    - Clock is High Before and after data transfer.
     *
     *      Example:
     *      MCLK____________      ____      ___.....
     *                      \____/    \____/
     *                  _________  ________
     *      MISO______ /         \/        \___.....
     *                 \_________/\________/
     *                  MSB(D15) .............> LSB(D01)
     * */
    spi_handle->spi_cfg.format.char_num     =   SPI_DataSize_16b;
    spi_handle->spi_cfg.format.first_bit    =   SPI_FirstBit_MSB;
    spi_handle->spi_cfg.direction           =   SPI_Direction_2Lines_FullDuplex;
    spi_handle->spi_cfg.pol                 =   SPI_CPOL_High;
    spi_handle->spi_cfg.phase               =   SPI_CPHA_2Edge;
    spi_handle->spi_cfg.mode                =   SPI_Mode_Master;
    spi_handle->spi_cfg.clk                 =   SPI_BaudRatePrescaler_16;

    spi_handle->init                    =   &ex_spi_init;
    spi_handle->pin_set                 =   &ex_spi_pin_set;
    spi_handle->write                   =   &ex_spi_write;
    spi_handle->read                    =   &ex_spi_read;


    spi_handle->init( spi_handle );

}

void	GINKGO_INIT( struct spi_t *spi ) 
{


}

void    LED_INIT( struct led_t *led )
{
    led->hw.led_0_pin           =   GPIO_Pin_8;
    led->hw.led_0_port          =   GPIOA;
    led->hw.led_1_pin           =   GPIO_Pin_2;
    led->hw.led_1_port          =   GPIOD;
    led->hw.led_gpio_clock      =   RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD;

    led->init                   =   &led_init;
    led->on                     =   &led_on;
    led->off                    =   &led_off;

    led->init( led );
}


void    TIMER_INIT( struct timer_t *timer_handle )
{

    timer_handle->tim_num                   =   TIM3;
    timer_handle->configure.tim_periph_clock    =   RCC_APB1Periph_TIM3;
    timer_handle->configure.period          =   999;
    timer_handle->configure.prescaler       =   7199;
    timer_handle->configure.clock_division  =   0;
    timer_handle->configure.counter_mode    =   TIM_CounterMode_Up;
    timer_handle->configure.irq.iqrn        =   TIM3_IRQn;
    timer_handle->configure.irq.preemption_priority =   0;
    timer_handle->configure.irq.sub_priority        =   3;
    timer_handle->counter   =   0;

    timer_handle->init  =   &timer_init;
    timer_handle->start =   &timer_start;
    timer_handle->stop  =   &timer_stop;
    timer_handle->set_time  =   &timer_set_time;
    timer_handle->check_status      =   &timer_check_status;
    timer_handle->clear_interrupt_flag  =   &timer_clear_interrupt_flag;

    timer_handle->init( timer_handle );
}




/**
 * \brief    This function is delay time for SYSTEM.
 *
 * \offer    Wei Haochen
 *
 * \param    struct ad7606_t (in ad9833.h document)
 *
 * \return   None.
 *
 *               ____       __________________
 * \note  covst_a    \_____/
 *               ____       __________________
 *        covst_b    \_____/
 *                   |<--->|
 *                     5us
 */
void    DELAY_US( uint32 delay )
{
    SysTick->LOAD   =   72 * delay;
    SysTick->CTRL   =   0x00000005;
    while( !( SysTick->CTRL & 0x00010000 ) );
    SysTick->CTRL   =   0x00000004;
}


void    DELAY_MS( uint32 delay )
{
    for( ; delay > 0; delay-- )
        DELAY_US( 1000 );
}


