#ifndef SYS_TICK_TASK_H_
#define SYS_TICK_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	
	#include "sys_tick_lib.h"
	
	//===????????
	uint8_t sys_tick_task_init(SYS_TICK_HandleType *systickx);
	uint8_t sys_tick_task_it_irq_handle(SYS_TICK_HandleType *systickx);
	uint32_t sys_tick_task_get_inc_ovf(SYS_TICK_HandleType *systickx);
	uint32_t sys_tick_task_get_inc_count(SYS_TICK_HandleType *systickx);
	uint32_t sys_tick_task_get_tick(void);
	uint8_t sys_tick_task_wait_ms(SYS_TICK_HandleType *systickx, uint32_t ms);
	uint8_t sys_tick_task_wait_s(SYS_TICK_HandleType *systickx, uint32_t s);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* SYS_TICK_TASK_H_ */