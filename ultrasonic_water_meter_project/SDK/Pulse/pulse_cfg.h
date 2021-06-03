#ifndef PULSE_CFG_H_
#define PULSE_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	
	#include "complier_lib.h"
	#include "sys_tick_task.h"
	#include "hw_config.h"
	#include "gpio_task.h"

	//===脉冲激活稳定时间
	#define PULSE_ACTIVE_TIME_STABLE			(20/PULSE_MIN_PULSE_WIDTH)

	//===定义结构体
	typedef struct _PULSE_HandleType			PULSE_HandleType;
	//===定义指针结构体
	typedef struct _PULSE_HandleType			* pPULSE_HandleType;
	//===结构体变量
	struct _PULSE_HandleType
	{
		vltuint8_t  msg_actice;					//---激活状态

		uint8_t     msg_level_active;			//---激活电平
		uint8_t		msg_level_value;			//---当前值电平
		uint8_t		msg_level_step;				//---电平步序
		uint8_t     msg_level_state;			//---电平状态

		uint16_t    msg_level_count;			//---电平计数

		uint32_t	msg_level_record;			//---键值计时
		uint32_t	msg_acticve_record;			//---激活记时
		uint8_t(*msg_f_level)(void);			//---键值
		uint32_t(*msg_f_time_tick)(void);		//---时间节拍

	};

	#define PULSE_TASK_ONE						p_pulse_one
	#define PULSE_TASK_TWO						0
	#define PULSE_TASK_THREE					0

	//===外部调用接口
	extern PULSE_HandleType						g_pulse_one;
	extern pPULSE_HandleType					p_pulse_one;

	//===函数定义
	uint8_t pulse_level_one(void);
	uint8_t pulse_it_irq_handle_one(PULSE_HandleType* Pulsex);

	uint8_t pulse_scan(PULSE_HandleType* Pulsex);
	uint8_t pulse_time_tick_init(PULSE_HandleType* Pulsex, uint32_t(*func_time_tick)(void));
	uint8_t pulse_init(PULSE_HandleType* Pulsex, uint32_t(*func_time_tick)(void));
	
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* PULSE_CFG_H_ */