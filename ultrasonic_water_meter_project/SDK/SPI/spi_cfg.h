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

	//===����ṹ��
	typedef struct _SPI_HandleType					SPI_HandleType;
	//===����ָ��ṹ��
	typedef	struct _SPI_HandleType					*pSPI_HandleType;
	//===�ṹ����
	struct _SPI_HandleType
	{
		vltuint8_t			msg_state;																					//---����״̬��Ĭ���ǿ���״̬---0������״̬---1
		uint8_t				msg_hw_mode;																				//---����ģʽ��Ĭ�������ģ��---0��Ӳ��ģʽ---1
		uint8_t				msg_cpol;																					//---ʱ�Ӽ��ԣ�0---ʱ�ӿ���Ϊ�͵�ƽ��1---ʱ�ӿ���Ϊ�ߵ�ƽ
		uint8_t				msg_cpha;																					//---ʱ����λ��0---ʱ�ӵĵ�һ�����������½������ݱ�������1----ʱ�ӵĵڶ������������½������ݱ�����
		uint16_t			msg_data_count;																				//---�����շ��ĸ���
		uint16_t			msg_pulse_width;																			//---�����ȣ����ģ��ʹ��
		GPIO_HandleType		msg_gpio_mosi;																				//---MOSI
		GPIO_HandleType		msg_gpio_miso;																				//---MISO
		GPIO_HandleType		msg_gpio_sck;																				//---SCK
		GPIO_HandleType		msg_gpio_cs;																				//---CS
		uint8_t	*			msg_p_send_data_buffer;																		//---����8Bit����ָ��
		uint8_t*			msg_p_read_data_buffer;																		//---����8Bit����ָ��
		void(*msg_f_delay_us)(uint32_t delay);																			//---��ʱ����
		uint32_t(*msg_f_time_tick)(void);																				//---���ڳ�ʱ����
	};

	//===��������
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