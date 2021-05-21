#ifndef MS1022_TASK_H_
#define MS1022_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	
	#include "ms1022_lib.h"

	//===º¯Êı¶¨Òå
	uint8_t ms1022_spi_task_time_tick_init(MS1022_HandleType* MS1022x, uint32_t(*func_time_tick)(void));
	uint8_t ms1022_spi_task_init(MS1022_HandleType* MS1022x, void(*func_delay_us)(uint32_t us),
		void(*func_delay_ms)(uint32_t ms), uint32_t(*func_time_tick)(void), uint8_t is_hw);
	uint8_t ms1022_spi_task_int_flag_set(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_task_mhw_it_irq_handle(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_task_read_reg(MS1022_HandleType* MS1022x, uint8_t index);
	uint8_t ms1022_spi_task_send_reg(MS1022_HandleType* MS1022x, uint8_t index, uint32_t val);
	uint8_t ms1022_spi_task_send_cmd(MS1022_HandleType* MS1022x, uint8_t cmd);
	uint16_t ms1022_spi_task_read_state(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_task_read_pw1st(MS1022_HandleType* MS1022x, uint8_t isup);
	uint8_t ms1022_spi_task_comm_test(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_task_read_start_temperature(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_task_read_start_temperature_restart(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_task_calibration_resonator(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_task_read_start_tof(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_task_read_start_tof_restart(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_task_get_temperature(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_task_get_flow(MS1022_HandleType* MS1022x);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* MS1022_TASK_H_ */