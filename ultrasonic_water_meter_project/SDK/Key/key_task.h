#ifndef KEY_TASK_H_
#define KEY_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "key_lib.h"
	
	//===????????
	uint8_t key_task_it_irq_handle_one(KEY_HandleType *KEYx,uint8_t index);
	uint8_t key_task_time_tick_init(KEY_HandleType* KEYx, uint32_t(*func_time_tick)(void));
	uint8_t key_task_init(KEY_HandleType* KEYx, uint32_t(*func_time_tick)(void));
	uint8_t key_task_scan(KEY_HandleType* KEYx);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* KEY_TASK_H_ */