#ifndef INCLUDE_SPI_H_
#define INCLUDE_SPI_H_

#include "stm32f10x.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_gpio.h"
#include "global.h"


#define					SPI_CONFIG_MODE_MASTER					0x00
#define					SPI_CONFIG_MODE_SLAVER					0x01
#define					SPI_CONFIG_PHASE_HALF_DELAY				0x02
#define					SPI_CONFIG_PHASE_NO_DELAY				0x03
#define					SPI_CONFIG_POL_HIGH						0x04
#define					SPI_CONFIG_POL_LOW						0x05

/**
 * \brief    struct spi_hw_t details.
 *
 * \offer    Wei Haochen
 *
 * \param    GPIO_TypeDef   *spi_port;
 *           [Configure STM32 SPI/GPIO function.]
 *           _______
 *           Example 1:______________________________________________
 *           -> GPIO_Init(self->hw.spi_port, &GPIO_InitStructure);
 *
 * \params   uint16 mosi_pin,clk_pin,etc...
 *           [spi function pins of GPIO]
 *           _______
 *           Example 1:______________________________________________
 *           -> GPIO_InitStructure.GPIO_Pin = self->hw.mosi_pin;
 *
 * \param    uint16 spi_sys_clock;
 *           [Configure SPI clock.]
 *           _______
 *           Example 1:______________________________________________
 *           -> self->hw.spi_sys_clock = RCC_APB1Periph_SPI2;
 *           -> RCC_APB2PeriphClockCmd(self->hw.spi_sys_clock,ENABLE);
 *                     ____       ___________
 * \note     include the spi hardware options using in STM32 SPI/GPIO configure.
 *           This structure is not used alone and structure defined in struct spi_t;
 */
struct	spi_hw_t {

	GPIO_TypeDef	*port;
	uint16		mosi_pin;
	uint16		miso_pin;
	uint16		clk_pin;
	uint16		ce_pin;
<<<<<<< HEAD
	uint16      periph_clock;
	uint16      gpio_clock;
=======
	uint16      sys_clock;
>>>>>>> 0be73c22922dcb0bc3a5d374333c16d7f7a097b1
};

/**
 * \brief    struct spi_config_t details.
 *
 * \offer    Wei Haochen
 *
 * \params   the structure includes all of SPI protocol parameters.
 *           * spi clock rate.
 *           * spi mode : master / slaver.
 *           * spi phase and delay half.
 *           * spi direction: this is stm32 configure parameter.
 *             details on spi_init function.
 *           * spi bytes
 *           * spi first bit: MSB or LSB.
 *                     ____       ___________
 * \note     include the spi configrue options using in STM32 SPI/GPIO configure.
 *           This structure is not used alone and structure defined in struct spi_t;
 */
struct spi_config_t {
	
	SPI_TypeDef	 *num;
	uint32	clk;
	uint16	mode;
	uint16 	pol;
	uint16	phase;
	uint16  direction;
	struct 	spi_format {
		uint16	char_num;
		uint16	first_bit;
	} format;
	struct      spi_init_t {

	    uint16_t    iqrn;
	    uint16_t    preemption_priority;
	    uint16_t    sub_priority;

	} irq;

};

/**
 * \brief   -struct spi_t details.
 *
 * \offer   -Wei Haochen
 *
 * \param   -struct spi_hw_t hw;
 *           [stm32 SPI hardware options.]
 *           [detail on struct spi_hw_t defined;]
 *
 * \param   -struct spi_config_t spi_cfg;
 *           [stm32 SPI configure options.]
 *           [detail on struct spi_config_t defined;]
 *
 * \param   -struct spi_t    *self;
 *           [self list operation pointer.]
 *
 * \params  -pointer functions
 *           [You can find real define in spi.c document]
 *           [In the external initial function in the main.c document,
 *            the pointer function and the entity function to establish contact.]
 *
 * \note    -the struct spi_t need define in the main.c documents.
 *           As a handle of SPI operator.
 */
struct	spi_t {

	struct spi_hw_t	hw;
	struct spi_t *self;
	struct spi_config_t spi_cfg;
	
	void	(*init)				( struct spi_t *self);
	void	(*pin_set)			( struct spi_t *self);
	void	(*read)				( struct spi_t *self, 	uint16 *read_val );
	void	(*write )			( struct spi_t *self, uint16 *vals, uint16 length );

};

extern void	ex_spi_pin_set( struct spi_t *self );
extern void	ex_spi_write( struct spi_t *self, uint16 *vals, uint16 length );
extern void	ex_spi_read( struct spi_t *self, uint16 *read_val );
extern void ex_spi_init( struct spi_t *self );


#endif
