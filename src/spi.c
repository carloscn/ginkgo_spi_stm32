
#include "spi.h"

void	ex_spi_pin_set( struct spi_t *self )
{
	GPIO_InitTypeDef	io_cfg;
	RCC_APB2PeriphClockCmd(self->hw.sys_clock, ENABLE);
	io_cfg.GPIO_Pin     =   self->hw.mosi_pin | self->hw.mosi_pin | self->hw.clk_pin;
	io_cfg.GPIO_Mode	= 	GPIO_Mode_AF_PP;
	io_cfg.GPIO_Speed	=	GPIO_Speed_50MHz;
	GPIO_Init( self->hw.port, &io_cfg );
}

/**
 * \brief    This function is AD7606 start convst
 *
 * \offer    Wei Haochen
 *
 * \param    struct ad9833_t (in ad9833.h document)
 *
 * \return   None.
 *
 *               ____       _____
 * \note  MCLK       \_____/     \_____...
 *                   |<--------->|     f_clk_max = 31.25MHz
 *                      min:32ns
 */

void 	ex_spi_init( struct spi_t *self )
{
		
	SPI_InitTypeDef		spi_cfg;
	self->pin_set( self );

	spi_cfg.SPI_Direction			=	self->spi_cfg.direction;
	spi_cfg.SPI_Mode				=	self->spi_cfg.mode;
	spi_cfg.SPI_CPOL				=	self->spi_cfg.pol;
	spi_cfg.SPI_CPHA				=	self->spi_cfg.phase;
	spi_cfg.SPI_NSS				    =	SPI_NSS_Soft;
	spi_cfg.SPI_BaudRatePrescaler	=	self->spi_cfg.clk;
	spi_cfg.SPI_CRCPolynomial		=	7;
    spi_cfg.SPI_DataSize            =   self->spi_cfg.format.char_num;
    spi_cfg.SPI_FirstBit            =   self->spi_cfg.format.first_bit;
    spi_cfg.SPI_BaudRatePrescaler   =   self->spi_cfg.clk;
    /*
     * Set SPI clock register:
     * *SPI_BaudRatePrescaler_2     :  (SPI 36M@sys 72M)
     * *SPI_BaudRatePrescaler_8     :  (SPI 9M@sys 72M)
     * *SPI_BaudRatePrescaler_16    :  (SPI 4.5M@sys 72M)
     * *SPI_BaudRatePrescaler_256   :  (SPI 281.25K@sys 72M)
     *
    self->spi_cfg.num->CR1   &=      0xFFC7;
    self->spi_cfg.num->CR1   |=      self->spi_cfg.clk;
    self->spi_cfg.num->CR1   |=      1 << 6;
    */

	SPI_Init( self->spi_cfg.num, &spi_cfg );
	SPI_Cmd( self->spi_cfg.num, ENABLE );
	SPI_I2S_SendData( self->spi_cfg.num, 0xFFFF );
}


void	ex_spi_read( struct spi_t *self, uint16 *read_val )
{
	while( SPI_I2S_GetFlagStatus( self->spi_cfg.num,SPI_I2S_FLAG_TXE ) == RESET );
	SPI_I2S_SendData( self->spi_cfg.num, 0xFFFF );
	while( SPI_I2S_GetFlagStatus( self->spi_cfg.num,SPI_I2S_FLAG_RXNE ) == RESET );
	
	*read_val	=	SPI_I2S_ReceiveData( self->spi_cfg.num );
}



void	ex_spi_write( struct spi_t *self, uint16 *vals, uint16 length )
{
	uint16 i;
	for( i = 0; i < length; i++ ) {
		while( SPI_I2S_GetFlagStatus( self->spi_cfg.num,SPI_I2S_FLAG_TXE ) == RESET );
		SPI_I2S_SendData( self->spi_cfg.num, *(vals+i) & 0xFFFF );
	}
}





