#ifndef INCLUDE_AD9833_H_
#define INCLUDE_AD9833_H_


#include "type.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

/* Registers */
#define 					AD9833_REG_CMD					(0 << 14)
#define 					AD9833_REG_FREQ0				(1 << 14)
#define 					AD9833_REG_FREQ1				(2 << 14)
#define 					AD9833_REG_PHASE0				(6 << 13)
#define 					AD9833_REG_PHASE1				(7 << 13)

/* Command Control Bits */
#define           			AD9833_B28			         	(1 << 13)
#define          			AD9833_HLB			         	(1 << 12)
#define           			AD9833_FSEL0		          	(0 << 11)
#define           			AD9833_FSEL1		          	(1 << 11)
#define           			AD9833_PSEL0		          	(0 << 10)
#define           			AD9833_PSEL1		          	(1 << 10)
#define           			AD9833_PIN_SW		         	(1 << 9)
#define           			AD9833_RESET		          	(1 << 8)
#define          	 		AD9833_SLEEP1		         	(1 << 7)
#define           			AD9833_SLEEP12		          	(1 << 6)
#define           			AD9833_OPBITEN		          	(1 << 5)
#define           			AD9833_SIGN_PIB		         	(1 << 4)
#define           			AD9833_DIV2			          	(1 << 3)
#define           			AD9833_MODE			          	(1 << 1)

#define           			AD9833_OUT_SINUS	         	((0 << 5) | (0 << 1) | (0 << 3))
#define           			AD9833_OUT_TRIANGLE	          	((0 << 5) | (1 << 1) | (0 << 3))
#define           			AD9833_OUT_MSB		          	((1 << 5) | (0 << 1) | (1 << 3))
#define           			AD9833_OUT_MSB2		         	((1 << 5) | (0 << 1) | (0 << 3))

#define						AD9833_STM32_SPI_PIN_FSYNC		GPIO_Pin_15
#define						AD9833_STM32_SPI_PIN_CLK		GPIO_Pin_14
#define						AD9833_STM32_SPI_PIN_SDI		GPIO_Pin_13
#define						AD9833_STM32_SPI_1				SPI1						

enum ad9833_wavetype_t{
	
    SIN = AD9833_OUT_SINUS , 
	SQU = AD9833_OUT_MSB,
	TRI = AD9833_OUT_TRIANGLE

};

struct ad9833_hw_t {
	
	uint16	clk_pin;
	uint16	sdi_pin;
	uint16	fsy_pin;
	struct 	spi_t	*ex_spi;

};


struct ad9833_t {

    struct ad9833_t *self;
	struct ad9833_hw_t hw;
    enum ad9833_wavetype_t wave_type;

    u16 delay;

	void (*init_device)			( struct 	ad9833_t *self );
	void (*reset_device)		( struct 	ad9833_t *self );
	void (*delay_us)			( struct 	ad9833_t *self,  	uint32 time);
	void (*clear_reset_device)	( struct 	ad9833_t *self );
	void (*set_register_value)	( struct 	ad9833_t *self, 	uint16 reg_value );
	void (*set_frequency)		( struct 	ad9833_t *self, 	uint16 reg, uint32 freq_value);
	void (*set_phase)			( struct 	ad9833_t *self,		uint16 reg, uint16 phase_value );
	void (*set_wave)			( struct 	ad9833_t *self,		enum ad9833_wavetype_t wave_type );
	void (*setup_device_para )	( struct 	ad9833_t *self,		uint32 freq_value, uint16 phase_value, enum ad9833_wavetype_t wave_type);
};

extern void	ad9833_set_wave				( struct ad9833_t *self, 
										  enum ad9833_wavetype_t wave_type );

extern void	ad9833_setup_para			( struct ad9833_t *self, 
										  uint32 freq_value, 
										  uint16 phase_value, 
										  enum ad9833_wavetype_t wave_type );

extern void	ad9833_set_phase			( struct ad9833_t *self, 
										  uint16 reg, 
										  uint16 val );

extern void	ad9833_set_frequency		( struct ad9833_t *self, 
										  uint16 reg,  
										  uint32 val );

extern void	ad9833_clear_reset			( struct ad9833_t *self ); 

extern void	ad9833_reset				( struct ad9833_t *self );

extern void	ad9833_init					( struct ad9833_t *self );

extern void	ad9833_set_register_value	( struct ad9833_t *self, 	
										  uint16 reg_value );
										  
extern void ad9833_delay_us				( struct ad9833_t *self,
										  uint32 time);
#endif
