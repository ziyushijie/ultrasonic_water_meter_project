#ifndef DELAY_LIB_H_
#define DELAY_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "delay_cfg.h"


	//===????????
	void delay_lib_nop(uint32_t cnt);
	void delay_lib_us(uint32_t us);
	void delay_lib_ms(uint32_t ms);
	void delay_lib_s(uint32_t s);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* DELAY_LIB_H_ */