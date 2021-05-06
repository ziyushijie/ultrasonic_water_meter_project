#ifndef DELAY_LIB_H_
#define DELAY_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////


#include "config.h"
#include "delay_cfg.h"

// 下列所有延时函数准确延时条件： @8MHZ

void XY_Delay(unsigned long xtime); // 延时-粗略长延时

// @10us 
#define __10us_DELAY__()										 \
{																 \
															   	 \
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP(); \
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP(); \
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP(); \
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP(); \
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP(); \
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP(); \
} 

//void XY_Delay_10us(void); // @10us

// 延时范围[10us,655.35ms];中间间隔时间基准是10us;即对应输入取值范围:[1,65535]
void SET_Delay_us(unsigned int _10us_Xus); // 10us * Xus
void Delay_ms(unsigned int xms);  // 约1ms~65535ms准确延时


//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* DELAY_LIB_H_ */