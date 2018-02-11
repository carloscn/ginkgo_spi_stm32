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
***/
// STM32   Project.                                            			GitLab
/****************************************************************************/
/*                                                                          */
/*  @file       : signals.c	                     	                        */
/*  @Copyright  : Powered by MULTIBEANS ORG rights reserved.                */
/*  @Revision   : Ver 1.0.                                                  */
/*  @Data       : 2017.09.25 Release.                                       */
/*  @Belong     : EDU class.                                                */
/*  @Git        :        */
/*  **code : (GB2312/GBK) in Windows 10 x64. Keil   Vision4 platform.	    */
/****************************************************************************/
/*  @Attention:                                                             */
/*  ---------------------------------------------------------------------   */
/*  |    Data    |  Behavior |     Offer      |          Content         |  */
/*  | 2017.09.25 |   create  |Carlos Lopez(M) | ceate the document.      |  */
/*  ---------------------------------------------------------------------   */
/*  Email: carlos@mltbns.top                                  MULTIBEANS.   */
/****************************************************************************/

#include "stm32f10x.h"
#include "global.h"
#include "signals.h"

#pragma pack(4)
static unsigned int *phaseSequenceRom;
#pragma pack(4)
static unsigned int *chuSequenceRom;
#pragma pack(4)
static unsigned int *pnRom;

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
void SIGNAL_SetSignalFrequency( unsigned short channel,float flt_freq )
{
    // The
    const float             flt_ad9833_para = 268.435456;          // 2^32/10^6
    const unsigned short    us_ad9833_extern_oscillator_freq = 10; // unit : MHz
    unsigned long           ul_ad9833_freq = flt_freq * ( flt_ad9833_para / us_ad9833_extern_oscillator_freq );

    API_AD9833_SetFrequency( channel, ul_ad9833_freq );
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
void SIGNAL_SetSignalPhase( unsigned short channel, unsigned short phase_value )
{
    API_AD9833_SetPhase( channel, phase_value );
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
void API_SIGNAL_SendSignalSequence( unsigned short *signalData, unsigned short signalLength )
{

}
