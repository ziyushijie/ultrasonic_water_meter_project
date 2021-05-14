#ifndef SPI_TASK_H_
#define SPI_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "spi_lib.h"

	//===º¯Êý¶¨Òå
	uint8_t spi_task_time_tick_init(SPI_HandleType* SPIx, uint32_t(*func_time_tick)(void));
	uint8_t spi_task_init(SPI_HandleType* SPIx, void(*func_delay_us)(uint32_t delay), uint32_t(*func_time_tick)(void));
	uint8_t spi_task_mhw_gpio_init(SPI_HandleType* SPIx);
	uint8_t spi_task_msw_gpio_init(SPI_HandleType* SPIx);
	uint8_t spi_task_gpio_deinit(SPI_HandleType* SPIx, uint8_t is_init_ss);

	uint8_t spi_task_msw_send_msb_byte(SPI_HandleType* SPIx, uint8_t val, uint8_t polarity);
	uint8_t spi_task_msw_read_msb_byte(SPI_HandleType* SPIx, uint8_t* pval, uint8_t polarity);
	uint8_t spi_task_msw_msb_byte(SPI_HandleType* SPIx, uint8_t val, uint8_t *pcmd);
	uint8_t spi_task_msw_send_msb_byte_buffer(SPI_HandleType* SPIx, uint8_t *pval, uint16_t length);
	uint8_t spi_task_msw_read_msb_byte_buffer(SPI_HandleType* SPIx, uint8_t* pval, uint16_t length);
	uint8_t spi_task_msw_msb_byte_buffer(SPI_HandleType* SPIx, uint8_t *pval, uint8_t *pcmd, uint16_t length);
	uint8_t spi_task_msw_send_msb_word(SPI_HandleType* SPIx, uint16_t val, uint8_t polarity);
	uint8_t spi_task_msw_read_msb_word(SPI_HandleType* SPIx, uint16_t* pval, uint8_t polarity);
	uint8_t spi_task_msw_send_msb_word_buffer(SPI_HandleType* SPIx, uint16_t *pval, uint16_t length);
	uint8_t spi_task_msw_read_msb_word_buffer(SPI_HandleType* SPIx, uint16_t *pval, uint16_t length);
	uint8_t spi_task_msw_msb_word_cmd(SPI_HandleType* SPIx, uint16_t val, uint16_t *pcmd);
	uint8_t spi_task_msw_msb_word(SPI_HandleType* SPIx, uint16_t val, uint16_t *pcmd);
	uint8_t spi_task_msw_msb_word_buffer(SPI_HandleType* SPIx, uint16_t *pval, uint16_t *pcmd, uint16_t length);

	uint8_t spi_task_msw_send_lsb_byte(SPI_HandleType* SPIx, uint8_t val, uint8_t polarity);
	uint8_t spi_task_msw_read_lsb_byte(SPI_HandleType* SPIx, uint8_t* pval, uint8_t polarity);
	uint8_t spi_task_msw_lsb_byte(SPI_HandleType* SPIx, uint8_t val, uint8_t *pcmd);
	uint8_t spi_task_msw_send_lsb_byte_buffer(SPI_HandleType* SPIx, uint8_t *pval, uint16_t length);
	uint8_t spi_task_msw_read_lsb_byte_buffer(SPI_HandleType* SPIx, uint8_t* pval, uint16_t length);
	uint8_t spi_task_msw_lsb_byte_buffer(SPI_HandleType* SPIx, uint8_t *pval, uint8_t *pcmd, uint16_t length);
	uint8_t spi_task_msw_send_lsb_word(SPI_HandleType* SPIx, uint16_t val, uint8_t polarity);
	uint8_t spi_task_msw_read_lsb_word(SPI_HandleType* SPIx, uint16_t* pval, uint8_t polarity);
	uint8_t spi_task_msw_send_lsb_word_buffer(SPI_HandleType* SPIx, uint16_t *pval, uint16_t length);
	uint8_t spi_task_msw_read_lsb_word_buffer(SPI_HandleType* SPIx, uint16_t *pval, uint16_t length);
	uint8_t spi_task_msw_lsb_word_cmd(SPI_HandleType* SPIx, uint16_t val, uint16_t *pcmd);
	uint8_t spi_task_msw_lsb_word(SPI_HandleType* SPIx, uint16_t val, uint16_t *pcmd);
	uint8_t spi_task_msw_lsb_word_buffer(SPI_HandleType* SPIx, uint16_t *pval, uint16_t *pcmd, uint16_t length);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* RTC_TASK_H_ */