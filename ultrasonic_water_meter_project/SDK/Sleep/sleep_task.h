#ifndef SLEEP_TASK_H_
#define SLEEP_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "sleep_lib.h"
	
	
	//===º¯Êý¶¨Òå
	uint8_t sleep_task_init(uint32_t(*func_time_tick)(void));
	uint8_t sleep_task_get(void);
	uint8_t sleep_task_enter(void);
	uint8_t sleep_task_exit(void);
	uint8_t sleep_task_wakeup_get(void);
	uint8_t sleep_task_wakeup_set(uint8_t wakeup);
	uint8_t sleep_task_wakeup_record_set(uint32_t wakeup_record);
	uint32_t sleep_task_wakeup_record_get(void);
	uint8_t sleep_task_wakeup_exit(uint8_t wakeup);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* SLEEP_TASK_H_ */