// STM32F103   Project.
/****************************************************************************/
/*                                                                          */
/*  @file       : *_Main.c                                                  */
/*  @Copyright  : WeiHaochen (p) 2018 MULTIBEANS_ORG All rights reserved. 	*/
/*  @Revision   : Ver 1.0.                                                  */
/*  @Data       : 2018.01.21 Release.                                       */
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

struct 	ad9833_t	ad9833_dev;
struct	spi_t		spi_ad9833;
struct 	spi_t		spi_ginkgo;
struct  led_t       led_dev, *led_dev_handle;

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
void	DELAY_US( uint32 delay )
{
    SysTick->LOAD	=	72 * delay;
    SysTick->CTRL	=	0x00000005;
    while( !( SysTick->CTRL & 0x00010000 ) );
    SysTick->CTRL	=	0x00000004;
}

void	DELAY_MS( uint32 delay )
{
    for( ; delay > 0; delay-- )
        DELAY_US( 1000 );
}
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
    RCC_Configuration();
    NVIC_Configuration();
    led_dev_handle  =   &led_dev;
    LED_INIT(led_dev_handle);
    printf("nihao \n");
    while(1)
    {

        led_dev_handle->on( &led_dev, LED0 );
        led_dev_handle->on( &led_dev, LED1 );
        DELAY_MS(40);
        led_dev_handle->off( &led_dev, LED0 );
        led_dev_handle->off( &led_dev, LED1 );
        DELAY_MS(4050);
    }
}


/***************************************************************************//**
 * @brief Init the uarts for STM32 in this project.  by Carlos.
 *
 * @param data - void
 *               - enable the uarts ths GPIO as function port.
 *               - Initializes the interrupt of recv.
 * @param bytesNumber - Number of bytes to write.
 *
 * @return void.
 *******************************************************************************/
void RCC_Configuration(void)
{
    /* Enable system clocks ------------------------------------------------*/
    ErrorStatus HSEStartUpStatus;
    RCC_DeInit();																					// System clock reset.
    RCC_HSEConfig( RCC_HSE_ON );																	// Open the HSE clock.
    HSEStartUpStatus = RCC_WaitForHSEStartUp();														// Wait for HSE clock.
    if( HSEStartUpStatus == SUCCESS ) {																// If the HSE time consuming normal.

        FLASH_PrefetchBufferCmd( FLASH_PrefetchBuffer_Enable );										// Enable flash reader buffer.
        FLASH_SetLatency( FLASH_Latency_2 );														// Flash wait state.
        RCC_HCLKConfig( RCC_SYSCLK_Div1 );															// HCLK = SYSCLK = 72.0MHz
        RCC_PCLK2Config( RCC_HCLK_Div1 );															// PCLK2 = HCLK = 72.0MHz
        RCC_PCLK1Config( RCC_HCLK_Div2 );															// PCLK1 = HCLK/2 = 36.0MHz

        RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);
        RCC_PLLCmd(ENABLE);																			// Enable PLL

        while( RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET );										// Wait till PLL is ready.
        RCC_SYSCLKConfig( RCC_SYSCLKSource_PLLCLK );												// Select PLL as system clock source.
        while( RCC_GetSYSCLKSource() != 0x08 );														// Wait till PLL is used as system clock source.
    }

    // notice :
    // If there is as "RCC_ADCCLKConfig( RCC_PCLK2_Div6 )" peripheral clock.
    // So, the ADCLK = PCLK2 / 6 = 12MHz.

    /* Enable peripheral clocks ------------------------------------------------*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD, ENABLE);
    /* Enable DMA1 and DMA2 clocks */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 | RCC_AHBPeriph_DMA2, ENABLE);
    /* Enable ADC1, ADC2, ADC3 and GPIOC clocks */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_ADC2 |
                           RCC_APB2Periph_ADC3 | RCC_APB2Periph_GPIOC, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 , ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1   , ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB ,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
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
    dev->hw.ex_spi	=	spi;
    dev->hw.sdi_pin	=	AD9833_STM32_SPI_PIN_SDI;
    dev->hw.clk_pin	=	AD9833_STM32_SPI_PIN_CLK;
    dev->hw.fsy_pin	=	AD9833_STM32_SPI_PIN_FSYNC;

    dev->hw.ex_spi->spi_cfg.spi_num					=	AD9833_STM32_SPI_1;
    dev->hw.ex_spi->spi_cfg.spi_clk 				=	SPI_BaudRatePrescaler_2;
    dev->hw.ex_spi->spi_cfg.spi_mode				=	SPI_Mode_Master;
    dev->hw.ex_spi->spi_cfg.spi_phase				=	SPI_CPHA_1Edge;
    dev->hw.ex_spi->spi_cfg.spi_pol					=	SPI_CPOL_High;
    dev->hw.ex_spi->spi_cfg.format.spi_char_num		=	16;
    dev->hw.ex_spi->spi_cfg.format.spi_first_bit	=	SPI_FirstBit_MSB;

    dev->hw.ex_spi->spi_init						=	&ex_spi_init;
    dev->hw.ex_spi->spi_pin_set						=	&ex_spi_pin_set;
    dev->hw.ex_spi->spi_write						=	&ex_spi_write;
    dev->hw.ex_spi->spi_read						=	&ex_spi_read;

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

void	GINKGO_INIT( struct spi_t *spi ) 
{
    spi->spi_cfg.spi_num							=	SPI2;

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





