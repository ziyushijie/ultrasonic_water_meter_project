#ifndef RL78_IT_H_
#define RL78_IT_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	//// 所有的中断处理函数的入口和中断函数
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "hw_config.h"
	#include "sys_tick_task.h"
	#include "uart_task.h"
	#include "gpio_task.h"
	#include "ms1022_task.h"
	#include "key_task.h"
	#include "pulse_task.h"
	#include "wdt_task.h"


	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* RL78_IT_H_ */