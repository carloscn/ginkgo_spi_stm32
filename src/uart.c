// STM32   Project.                                            			GitLab
/****************************************************************************/
/*                                                                          */
/*  @file       : uart.c	                     	                        */
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

#include "global.h"
#include "uart.h"


void 	uart_pin_set( struct uart_t *self )
{
	GPIO_InitTypeDef io_cfg;
	
	io_cfg.GPIO_Pin		=	self->hw.rx_pin;
	io_cfg.GPIO_Mode	=	GPIO_Mode_IN_FLOATING;
	io_cfg.GPIO_Speed	=	self->hw.io_clk;
	GPIO_Init(self->hw.rx_port, &io_cfg );
	
	io_cfg.GPIO_Pin		=	self->hw.tx_pin;
	io_cfg.GPIO_Mode	=	GPIO_Mode_AF_PP;
	io_cfg.GPIO_Speed	=	self->hw.io_clk;
	GPIO_Init(self->hw.tx_port, &io_cfg );
	
		
}

void	uart_init( struct uart_t *self )
{
	USART_InitTypeDef	uart_cfg;

	uart_cfg.USART_BaudRate				=	self->uart_cfg.baud_rate;
	uart_cfg.USART_WordLength			=	self->uart_cfg.word_length;
	uart_cfg.USART_HardwareFlowControl	=	self->uart_cfg.hardware_flow_ctrl;
	uart_cfg.USART_StopBits				=	self->uart_cfg.stop_bits;
	uart_cfg.USART_Mode					=	self->uart_cfg.mode;
	uart_cfg.USART_Parity				=	self->uart_cfg.parity;
	USART_Init( self->uart_cfg.usart_num, &uart_cfg );
	USART_ITConfig( self->uart_cfg.usart_num, USART_IT_RXNE, ENABLE );
	USART_ITConfig( self->uart_cfg.usart_num, USART_IT_TXE, ENABLE );
	USART_ClearFlag( self->uart_cfg.usart_num, USART_FLAG_TXE  );
}

void	uart_write_byte( struct uart_t *self, BYTE byte )
{
	while(!USART_GetFlagStatus( self->uart_cfg.usart_num ,USART_FLAG_TXE));	 
	USART_SendData( self->uart_cfg.usart_num, byte );		
 
}

void 	uart_write_string( struct uart_t *self, BYTE *bytes, uint16 length )
{
	uint16 i;
	for( i = 0; i < length; i++ ) {
		self->write_byte( self, *(bytes + i) );				 
	}
}

void	uart_clear_buffer( struct uart_t *self )
{
	uint16 i;
	for( i = 0;	i < UART_RECV_BUFFER_MAX; i++ ) {
		*( self->uart_buffer + i) = '\0';
	}
	self->uart_rx_count	=	0;
	
}










static uint16_t uartInterruptCount = 0;
unsigned char uartBuffer[50] = {0};

bool 	global_uartDataReadyFlag = true;
bool    UART1InfoFlag = false;

const unsigned char UART1_at_reset_cmd[]    =   {"AT+RESET\r\n"};
const unsigned char UART1_at_roleo_cmd[]    =   {"AT+ROLE1\r\n"};
const unsigned char UART1_at_inq_cmd[]      =   {"AT+INQ\r\n" };
const unsigned char UART1_at_conn_cmd[]     =   {"AT+CONN1\r\n"};

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
void UART_UART1_InitDevice( void )
{
	UART_UART1_GPIO_Config();
	UART_UART1_Config(9600);
	UART_UART1_INTERRUPT_Config();
}
void API_UART_UART1_Init( void )
{
    UART_UART1_InitDevice();
}


/***************************************************************************//**
 * @brief Writes data to SPI.
 *
 * @param data - Write data buffer:
 *               - first byte is the chip select number;
 *               - from the second byte onwards are located data bytes to write.
 * @param bytesNumber - Number of bytes to write.
 *
 * @return Number of written bytes.
*******************************************************************************/
void UART_UART1_SendByte( unsigned char Data )
{
	while(!USART_GetFlagStatus(USART1,USART_FLAG_TXE));	  //USART_GetFlagStatus：得到发送状态位
	//USART_FLAG_TXE:发送寄存器为空 1：为空；0：忙状态
	USART_SendData(USART1,Data);						  //发送一个字符
}

/***************************************************************************//**
 * @brief Writes data to SPI.
 *
 * @param data - Write data buffer:
 *               - first byte is the chip select number;
 *               - from the second byte onwards are located data bytes to write.
 * @param bytesNumber - Number of bytes to write.
 *
 * @return Number of written bytes.
*******************************************************************************/
void API_UART_UART1_SendBuffer( unsigned char *buffer )
{
	uint8_t i = 0;
	while( *(buffer + i) != '\0' ) {
		UART_UART1_SendByte( *(buffer + i) );
		i++;
	}
}

/***************************************************************************//**
 * @brief Writes data to SPI.
 *
 * @param data - Write data buffer:
 *               - first byte is the chip select number;
 *               - from the second byte onwards are located data bytes to write.
 * @param bytesNumber - Number of bytes to write.
 *
 * @return Number of written bytes.
*******************************************************************************/
void UART_UART1_GPIO_Config( void )
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
/***************************************************************************//**
 * @brief Writes data to SPI.
 *
 * @param data - Write data buffer:
 *               - first byte is the chip select number;
 *               - from the second byte onwards are located data bytes to write.
 * @param bytesNumber - Number of bytes to write.
 *
 * @return Number of written bytes.
*******************************************************************************/
void UART_UART1_Config( uint32_t BaudRate )
{
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate            = BaudRate ;
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;
	USART_InitStructure.USART_Parity              = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART1, ENABLE);

}

/***************************************************************************//**
 * @brief Writes data to SPI.
 *
 * @param data - Write data buffer:
 *               - first byte is the chip select number;
 *               - from the second byte onwards are located data bytes to write.
 * @param bytesNumber - Number of bytes to write.
 *
 * @return Number of written bytes.
*******************************************************************************/
void UART_UART1_INTERRUPT_Config( void )
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/***************************************************************************//**
 * @brief Writes data to SPI.
 *
 * @param data - Write data buffer:
 *               - first byte is the chip select number;
 *               - from the second byte onwards are located data bytes to write.
 * @param bytesNumber - Number of bytes to write.
 *
 * @return Number of written bytes.
*******************************************************************************/
unsigned char keyLightAdjustCmd;
void USART1_IRQHandler( void )
{

	uint16_t checkSum = 0;
	uint16_t dataLength = 0;
	uint16_t i = 0,j = 0;

	if( USART_GetITStatus(USART1,USART_IT_RXNE) != RESET ) {
		USART_ClearITPendingBit(USART1,USART_IT_RXNE); //清除中断标志
		uartBuffer[ uartInterruptCount ] = USART_ReceiveData(USART1);
		uartInterruptCount ++;
		/* Rec the blueeteeth AT instructions */
#if FALSE
		while( j <= uartInterruptCount ) {
			j ++;
			if( ( (uartBuffer[ j - 1 ] == 'O') && (uartBuffer[ j ] == 'K') ) ||
					((uartBuffer[j - 1] == '+' )  && ( uartBuffer[ j ] == 'C' )  )) {
				UART1InfoFlag = TRUE;
				uartInterruptCount = 0;
				j = 0;
				clearBuffer();
			}
			if( ( (uartBuffer[ j - 1 ] == '!') && (uartBuffer[ j ] == '@') ) ||
					((uartBuffer[j - 1] == '#' )  && ( uartBuffer[ j ] == '$' )  )) {
				UART1InfoFlag = TRUE;
				uartInterruptCount = 0;
				j = 0;
				clearBuffer();
			}
			/* Rec The cmd. */
			if( uartBuffer[ j-1 ] == 0xCC && uartBuffer[ j ] == 0xDD ) {              // Recieved end of data.
				if( (uartBuffer[ 0 ] == 0xAA && uartBuffer[ 1 ] == 0xBB) ||
						( uartBuffer[ 0 ] == 0xEE && uartBuffer[ 1 ] == 0xFF ) ) {
					/* Check checksum value. */
					dataLength = uartBuffer[2];
					for( i = 0; i < dataLength + 3; i++ ) {
						checkSum = checkSum ^ uartBuffer[i];
					}
					if( checkSum == uartBuffer[ uartInterruptCount - 3 ] ) {
						global_uartDataReadyFlag = TRUE;
						keyLightAdjustCmd = uartBuffer[3];
					}
				}
				uartInterruptCount = 0;
				j = 0;
				clearBuffer();
			}
			/* Rec the key command. */
		}/* End of the While(..).. */
#endif
		if( uartInterruptCount >= 50 ) {
			uartInterruptCount = 0;
		}

	}
}

/***************************************************************************//**
 * @brief Writes data to SPI.
 *
 * @param data - Write data buffer:
 *               - first byte is the chip select number;
 *               - from the second byte onwards are located data bytes to write.
 * @param bytesNumber - Number of bytes to write.
 *
 * @return Number of written bytes.
*******************************************************************************/
void UART_UART1_clearBuffer( void )
{
	uint16_t i = 0;
	for( i = 0; i < 50; i++ ) {
		uartBuffer[i] = 0x00;
	}
}





/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
End:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
