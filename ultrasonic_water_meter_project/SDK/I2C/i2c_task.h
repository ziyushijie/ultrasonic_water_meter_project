#ifndef I2C_TASK_H_
#define I2C_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "i2c_lib.h"

	//===????????
	uint8_t i2c_task_msw_init(I2C_HandleType *I2Cx, void(*func_delay_us)(uint32_t delay), uint32_t(*func_time_handle)(void));
	uint8_t i2c_task_msw_deinit(I2C_HandleType *I2Cx);
	uint8_t i2c_task_msw_start(I2C_HandleType *I2Cx, uint8_t is_write);
	uint8_t i2c_task_msw_stop(I2C_HandleType *I2Cx);
	uint8_t i2c_task_msw_read_ack(I2C_HandleType *I2Cx);
	uint8_t i2c_task_msw_send_ack(I2C_HandleType *I2Cx, uint8_t is_nack);
	uint8_t i2c_task_msw_send_byte(I2C_HandleType *I2Cx, uint8_t buffer);
	uint8_t i2c_task_msw_send_word(I2C_HandleType *I2Cx, uint16_t buffer);
	uint8_t i2c_task_msw_read_byte(I2C_HandleType *I2Cx);
	uint8_t i2c_task_msw_send_cmd(I2C_HandleType *I2Cx, uint8_t cmd, uint8_t is_start, uint8_t is_stop);
	uint8_t i2c_task_msw_data_send(I2C_HandleType *I2Cx, uint8_t *buffer, int16_t length);
	uint8_t i2c_task_msw_data_read(I2C_HandleType *I2Cx, uint8_t *buffer, int16_t length);
	uint8_t i2c_task_master_deinit(I2C_HandleType* I2Cx);
	void i2c_task_time_tick_init(I2C_HandleType* I2Cx, uint32_t(*func_time_handle)(void));
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* I2C_TASK_H_ */