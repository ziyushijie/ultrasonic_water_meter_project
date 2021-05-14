#ifndef SPI_CFG_H_
#define SPI_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	
	#include "complier_lib.h"
	#include "sys_tick_task.h"
	#include "hw_config.h"
	#include "gpio_task.h"
	#include "delay_task.h"

	//===定义结构体
	typedef struct _SPI_HandleType					SPI_HandleType;
	//===定义指针结构体
	typedef	struct _SPI_HandleType					*pSPI_HandleType;
	//===结构定义
	struct _SPI_HandleType
	{
		vltuint8_t			msg_state;																					//---工作状态，默认是空闲状态---0，工作状态---1
		uint8_t				msg_hw_mode;																				//---工作模式，默认是软件模拟---0，硬件模式---1
		uint8_t				msg_cpol;																					//---时钟极性，0---时钟空闲为低电平；1---时钟空闲为高电平
		uint8_t				msg_cpha;																					//---时钟相位，0---时钟的第一个上升或则下降沿数据被采样；1----时钟的第二个上升或则下降沿数据被采样
		uint16_t			msg_data_count;																				//---数据收发的个数
		uint16_t			msg_pulse_width;																			//---脉冲宽度，软件模拟使用
		GPIO_HandleType		msg_gpio_mosi;																				//---MOSI
		GPIO_HandleType		msg_gpio_miso;																				//---MISO
		GPIO_HandleType		msg_gpio_sck;																				//---SCK
		GPIO_HandleType		msg_gpio_cs;																				//---CS
		uint8_t	*			msg_p_send_data_buffer;																		//---发送8Bit数据指针
		uint8_t*			msg_p_read_data_buffer;																		//---接收8Bit数据指针
		void(*msg_f_delay_us)(uint32_t delay);																			//---延时参数
		uint32_t(*msg_f_time_tick)(void);																				//---用于超时计数
	};

	//===函数定义
	uint8_t spi_time_tick_init(SPI_HandleType* SPIx, uint32_t(*func_time_tick)(void));
	uint8_t spi_init(SPI_HandleType* SPIx, void(*func_delay_us)(uint32_t delay), uint32_t(*func_time_tick)(void));
	uint8_t spi_mhw_gpio_init(SPI_HandleType* SPIx);
	uint8_t spi_msw_gpio_init(SPI_HandleType* SPIx);
	uint8_t spi_gpio_deinit(SPI_HandleType* SPIx, uint8_t is_init_ss);

	uint8_t spi_msw_send_msb_byte(SPI_HandleType* SPIx, uint8_t val, uint8_t polarity);
	uint8_t spi_msw_read_msb_byte(SPI_HandleType* SPIx, uint8_t* pval, uint8_t polarity);
	uint8_t spi_msw_msb_byte(SPI_HandleType* SPIx, uint8_t val, uint8_t *pcmd);
	uint8_t spi_msw_send_msb_byte_buffer(SPI_HandleType* SPIx, uint8_t *pval, uint16_t length);
	uint8_t spi_msw_read_msb_byte_buffer(SPI_HandleType* SPIx, uint8_t* pval, uint16_t length);
	uint8_t spi_msw_msb_byte_buffer(SPI_HandleType* SPIx, uint8_t *pval, uint8_t *pcmd, uint16_t length);
	uint8_t spi_msw_send_msb_word(SPI_HandleType* SPIx, uint16_t val, uint8_t polarity);
	uint8_t spi_msw_read_msb_word(SPI_HandleType* SPIx, uint16_t* pval, uint8_t polarity);
	uint8_t spi_msw_send_msb_word_buffer(SPI_HandleType* SPIx, uint16_t *pval, uint16_t length);
	uint8_t spi_msw_read_msb_word_buffer(SPI_HandleType* SPIx, uint16_t *pval, uint16_t length);
	uint8_t spi_msw_msb_word_cmd(SPI_HandleType* SPIx, uint16_t val, uint16_t *pcmd);
	uint8_t spi_msw_msb_word(SPI_HandleType* SPIx, uint16_t val, uint16_t *pcmd);
	uint8_t spi_msw_msb_word_buffer(SPI_HandleType* SPIx, uint16_t *pval, uint16_t *pcmd, uint16_t length);

	uint8_t spi_msw_send_lsb_byte(SPI_HandleType* SPIx, uint8_t val, uint8_t polarity);
	uint8_t spi_msw_read_lsb_byte(SPI_HandleType* SPIx, uint8_t* pval, uint8_t polarity);
	uint8_t spi_msw_lsb_byte(SPI_HandleType* SPIx, uint8_t val, uint8_t *pcmd);
	uint8_t spi_msw_send_lsb_byte_buffer(SPI_HandleType* SPIx, uint8_t *pval, uint16_t length);
	uint8_t spi_msw_read_lsb_byte_buffer(SPI_HandleType* SPIx, uint8_t* pval, uint16_t length);
	uint8_t spi_msw_lsb_byte_buffer(SPI_HandleType* SPIx, uint8_t *pval, uint8_t *pcmd, uint16_t length);
	uint8_t spi_msw_send_lsb_word(SPI_HandleType* SPIx, uint16_t val, uint8_t polarity);
	uint8_t spi_msw_read_lsb_word(SPI_HandleType* SPIx, uint16_t* pval, uint8_t polarity);
	uint8_t spi_msw_send_lsb_word_buffer(SPI_HandleType* SPIx, uint16_t *pval, uint16_t length);
	uint8_t spi_msw_read_lsb_word_buffer(SPI_HandleType* SPIx, uint16_t *pval, uint16_t length);
	uint8_t spi_msw_lsb_word_cmd(SPI_HandleType* SPIx, uint16_t val, uint16_t *pcmd);
	uint8_t spi_msw_lsb_word(SPI_HandleType* SPIx, uint16_t val, uint16_t *pcmd);
	uint8_t spi_msw_lsb_word_buffer(SPI_HandleType* SPIx, uint16_t *pval, uint16_t *pcmd, uint16_t length);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* SPI_CFG_H_ */