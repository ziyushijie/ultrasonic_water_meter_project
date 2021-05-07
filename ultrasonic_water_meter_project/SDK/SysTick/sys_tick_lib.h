#ifndef SYS_TICK_LIB_H_
#define SYS_TICK_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "sys_tick_cfg.h"
	
	//===º¯Êý¶¨Òå
	uint8_t sys_tick_lib_init(SYS_TICK_HandleType *systickx);
	uint8_t sys_tick_lib_init(SYS_TICK_HandleType *systickx);
	uint8_t sys_tick_lib_it_irq_handle(SYS_TICK_HandleType *systickx);
	uint32_t sys_tick_lib_get_inc_ovf(SYS_TICK_HandleType *systickx);
	uint32_t sys_tick_lib_get_inc_count(SYS_TICK_HandleType *systickx);
	uint32_t sys_tick_lib_get_tick(void);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* SYS_TICK_LIB_H_ */