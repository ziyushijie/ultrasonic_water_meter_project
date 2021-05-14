#ifndef MS1022_CFG_H_
#define MS1022_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	
	#include "complier_lib.h"
	#include "gpio_task.h"
	#include "delay_task.h"
	#include "sys_tick_task.h"
	#include "hw_config.h"
	#include "spi_task.h"

	//===定义结构体
	typedef struct _MS1022_HandleType					MS1022_HandleType;
	//===定义指针结构体
	typedef	struct _MS1022_HandleType					*pMS1022_HandleType;
	//===结构定义
	struct _MS1022_HandleType
	{

		SPI_HandleType msg_spix;																						//---使用的spi接口

		void(*msg_f_delay_ms)(uint32_t delay);																			//---延时参数
		uint32_t(*msg_f_time_tick)(void);																				//---用于超时计数
	};

	#define MS1022_TASK_ONE							p_ms1022_one
	#define MS1022_TASK_TWO							0
	#define MS1022_TASK_THREE						0

	//===外部调用接口
	extern MS1022_HandleType						g_ms1022_one;
	extern pMS1022_HandleType						p_ms1022_one;
	
	//===函数定义
	uint8_t ms1022_time_tick_init(MS1022_HandleType* MS1022x, uint32_t(*func_time_tick)(void));
	uint8_t ms1022_init(MS1022_HandleType* MS1022x, void(*func_delay_us)(uint32_t us),
		void(*func_delay_ms)(uint32_t ms), uint32_t(*func_time_tick)(void));

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* MS1022_CFG_H_ */