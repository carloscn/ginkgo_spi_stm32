
#include "global.h"
#include "ad9833.h"

void 	ad9833_delay_us( struct ad9833_t *self,
						 uint32 time) 
{
	SysTick->LOAD	=	72 * time;
	SysTick->CTRL	=	0x00000005;
	while( !( SysTick->CTRL & 0x00010000 ) );
	SysTick->CTRL	=	0x00000004;
}

void	ad9833_set_register_value( struct 	ad9833_t *self, 	
								   uint16 	reg_value )
{
	uint16	data[5] 	=	{ 0x03, 0x00, 0x00 };
	
	data[1]		=	( uint16 )( ( reg_value & 0xFF00 ) >> 8 );
	data[2]		=	( uint16 )( ( reg_value & 0x00FF ) >> 0 );
	self->hw.ex_spi->write( self->hw.ex_spi, data, 2 );
}


void	ad9833_init( struct	 ad9833_t *self )
{
	self->hw.ex_spi->init( self->hw.ex_spi );
	self->set_register_value( self, AD9833_REG_CMD | AD9833_RESET );
}

void	ad9833_reset( struct ad9833_t *self )
{
	self->set_register_value( self, AD9833_REG_CMD | AD9833_RESET );
}

void	ad9833_clear_reset( struct ad9833_t *self ) 
{
	self->set_register_value( self, AD9833_REG_CMD );
}

void	ad9833_set_frequency( struct ad9833_t *self, 
							  uint16 reg,  
	uint32 val )
{	
	uint16	freq_high	=	reg;
	uint16	freq_low	=	reg;
	
	freq_high	|=	( val & 0xFFFC000 ) >>	14;
	freq_low	|=	( val & 0x3FFF );
	
	self->set_register_value( self, AD9833_B28 );
	self->set_register_value( self, freq_high );
	self->set_register_value( self, freq_low );

}


void	ad9833_set_phase( struct ad9833_t *self, 
						  uint16 reg, 
						  uint16 val )
{
	uint16	phase	=	reg;
	phase	|=	val;
	self->set_register_value( self, phase );
}

void	ad9833_setup_para( struct ad9833_t *self, 
						   uint32 freq_value, 
						   uint16 phase_value, 
						   enum ad9833_wavetype_t wave_type )
{
	uint16	val	=	0;
	val	=	freq_value | phase_value | wave_type;
	self->set_register_value( self, val );
}

void	ad9833_set_wave( struct ad9833_t *self, enum ad9833_wavetype_t wave_type )
{
	self->set_register_value( self, wave_type );
}





