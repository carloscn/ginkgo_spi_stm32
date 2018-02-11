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
/*  @file       : uart.h	                     	                        */
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

#ifndef _UART_H
#define _UART_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

#define							UART_RECV_BUFFER_MAX			256
#define							UART_TX_PORT					GPIOA

struct uart_hw_t{
	
	uint16	rx_pin;
	GPIO_TypeDef	*rx_port;
	uint16	tx_pin;
	GPIO_TypeDef	*tx_port;
	
	uint32			io_clk;
	
	
};

struct uart_config_t {
	
	USART_TypeDef *usart_num;
	uint16	baud_rate;
	uint16	word_length;
	uint16	stop_bits;
	uint16 	parity;
	uint16	hardware_flow_ctrl;
	uint16 	mode;
	
};

struct	uart_t	{

	struct uart_t 			*self;
	struct uart_hw_t 		hw;
	struct uart_config_t 	uart_cfg;
	uint16 uart_rx_count;
	BYTE uart_buffer[UART_RECV_BUFFER_MAX];
	
	void (*init)			(struct uart_t *self);
	void (*write_string)	(struct uart_t *self, BYTE *bytes, uint16 length );
	void (*write_byte)		(struct uart_t *self, BYTE byte);
	void (*read_byte)		(struct uart_t *self, BYTE *byte );
	void (*pin_set)			(struct uart_t *self);
	void (*rx_interrupt)	(struct uart_t *self);
	void (*clear_buffer)	(struct uart_t *self);
	
};


extern void		uart_clear_buffer		( struct uart_t *self );
extern void 	uart_write_string		( struct uart_t *self, BYTE *bytes, uint16 lenght );
extern void		uart_write_byte			( struct uart_t *self, BYTE byte );
extern void		uart_init				( struct uart_t *self );
extern void 	uart_pin_set			( struct uart_t *self );


// Set function:
void UART_UART1_clearBuffer( void );
void UART_UART1_INTERRUPT_Config( void );
void UART_UART1_Config( uint32_t BaudRate );
void UART_UART1_GPIO_Config( void );
void UART_UART1_SendByte( unsigned char Data );
void UART_UART1_InitDevice( void );
// Interrupt function:
void USART1_IRQHandler( void );
// API function:
void API_UART_UART1_SendBuffer( unsigned char *buffer );
void API_UART_UART1_Init( void );
#endif
