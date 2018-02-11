
#include "global.h"
#include "spi.h"

void	ex_spi_pin_set( struct spi_t *self )
{
	GPIO_InitTypeDef	io_cfg;
	//io_cfg.GPIO_Pin 	= 	self->hw.mosi_pin;
	io_cfg.GPIO_Mode	= 	GPIO_Mode_AF_PP;
	io_cfg.GPIO_Speed	=	GPIO_Speed_50MHz;
	GPIO_Init( GPIOB, &io_cfg );
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
    /**
     *      SPI_CLK_OUTOFPHASE  - Clock is Delayed by half clock cycle.
     *      SPI_CLK_POL_HIGH    - Clock is High Before and after data transfer.
     *
     *      Example:
     *      MCLK____________      ____      ___.....
     *                      \____/    \____/
     *                  _________  ________
     *      MISO______ /         \/        \___.....
     *                 \_________/\________/
     *					MSB(D15) .............> LSB(D01)
     * */
		
	SPI_InitTypeDef		spi_cfg;
	spi_cfg.SPI_Direction			=	self->spi_cfg.spi_direction;
	spi_cfg.SPI_Mode				=	self->spi_cfg.spi_mode;
	spi_cfg.SPI_CPOL				=	self->spi_cfg.spi_pol;
	spi_cfg.SPI_CPHA				=	self->spi_cfg.spi_phase;
	spi_cfg.SPI_NSS				    =	SPI_NSS_Soft;
	spi_cfg.SPI_BaudRatePrescaler	=	self->spi_cfg.spi_clk;
	spi_cfg.SPI_CRCPolynomial		=	7;
	SPI_Init( self->spi_cfg.spi_num, &spi_cfg );
	SPI_Cmd( self->spi_cfg.spi_num, ENABLE );
}


void	ex_spi_read( struct spi_t *self, uint16 *read_val )
{
	while( SPI_I2S_GetFlagStatus( self->spi_cfg.spi_num,SPI_I2S_FLAG_TXE ) == RESET );
	SPI_I2S_SendData( self->spi_cfg.spi_num, 0xFFFF );
	while( SPI_I2S_GetFlagStatus( self->spi_cfg.spi_num,SPI_I2S_FLAG_RXNE ) == RESET );
	
	*read_val	=	SPI_I2S_ReceiveData( self->spi_cfg.spi_num );
}



void	ex_spi_write( struct spi_t *self, uint16 *vals, uint16 length )
{
	uint16 i;
	for( i = 0; i < length; i++ ) {
		while( SPI_I2S_GetFlagStatus( self->spi_cfg.spi_num,SPI_I2S_FLAG_TXE ) == RESET );
		SPI_I2S_SendData( self->spi_cfg.spi_num, *(vals+i) & 0xFFFF );
	}
}





