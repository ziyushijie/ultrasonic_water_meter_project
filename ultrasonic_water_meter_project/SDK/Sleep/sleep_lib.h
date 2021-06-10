#ifndef SLEEP_LIB_H_
#define SLEEP_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "sleep_cfg.h"

	//===º¯Êý¶¨Òå
	uint8_t sleep_lib_init(uint32_t(*func_time_tick)(void));
	uint8_t sleep_lib_get(void);
	uint8_t sleep_lib_enter(void);
	uint8_t sleep_lib_exit(void);
	uint8_t sleep_lib_wakeup_get(void);
	uint8_t sleep_lib_wakeup_set(uint8_t wakeup);
	uint8_t sleep_lib_wakeup_record_set(uint32_t wakeup_record);
	uint32_t sleep_lib_wakeup_record_get(void);
	uint8_t sleep_lib_wakeup_exit(uint8_t wakeup);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* SLEEP_LIB_H_ */