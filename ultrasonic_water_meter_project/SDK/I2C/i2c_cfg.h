#ifndef I2C_CFG_H_
#define I2C_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	
	#include "complier_lib.h"
	#include "sys_tick_task.h"
	#include "gpio_task.h"
	#include "delay_task.h"
	#include "hw_config.h"

	//===����ṹ��
	typedef struct _I2C_HandleType					I2C_HandleType;
	//===����ָ��ṹ��
	typedef	struct _I2C_HandleType					*pI2C_HandleType;
	//===�ṹ����
	struct _I2C_HandleType
	{
		GPIO_HandleType		msg_gpio_scl;																				//---SCL
		GPIO_HandleType		msg_gpio_sda;																				//---SDA
		uint8_t				msg_hw_mode;																				//---����ģʽ��Ĭ�������ģ��---0��Ӳ��ģʽ---1
		uint16_t			msg_pluse_width;																			//---�����ȣ����ģ��ʹ��
		uint16_t			msg_addr;																					//---�豸�ĵ�ַ
		void(*msg_f_delay_us)(uint32_t delay);																			//---��ʱ����
		uint32_t(*msg_f_time_tick)(void);																				//---���ڳ�ʱ����
	};

	//===��������
	uint8_t i2c_msw_init(I2C_HandleType *I2Cx, void(*func_delay_us)(uint32_t delay), uint32_t(*func_time_tick)(void));
	uint8_t i2c_msw_deinit(I2C_HandleType *I2Cx);
	uint8_t i2c_msw_start(I2C_HandleType *I2Cx);
	uint8_t i2c_msw_stop(I2C_HandleType *I2Cx);
	uint8_t i2c_msw_ack(I2C_HandleType *I2Cx);
	uint8_t i2c_msw_nack(I2C_HandleType *I2Cx);
	uint8_t i2c_msw_read_ack(I2C_HandleType *I2Cx);
	uint8_t i2c_msw_wait_ack(I2C_HandleType *I2Cx);
	uint8_t i2c_msw_send_ack(I2C_HandleType *I2Cx, uint8_t is_nack);
	uint8_t i2c_msw_send_byte(I2C_HandleType *I2Cx, uint8_t buffer);
	uint8_t i2c_msw_send_word(I2C_HandleType *I2Cx, uint16_t buffer);
	uint8_t i2c_msw_read_byte(I2C_HandleType *I2Cx);
	uint8_t i2c_msw_check_device(I2C_HandleType *I2Cx);
	uint8_t i2c_msw_send_cmd(I2C_HandleType *I2Cx, uint8_t cmd, uint8_t is_start, uint8_t is_stop);
	uint8_t i2c_master_deinit(I2C_HandleType* I2Cx);
	void i2c_time_tick_init(I2C_HandleType* I2Cx, uint32_t(*func_time_tick)(void));
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* I2C_CFG_H_ */