#ifndef WDT_CFG_H_
#define WDT_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	
	#include "complier_lib.h"
	#include "sys_tick_task.h"
	#include "hw_config.h"

	//===��������
	void wdt_init(void);
	void wdt_restart(void);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* WDT_CFG_H_ */