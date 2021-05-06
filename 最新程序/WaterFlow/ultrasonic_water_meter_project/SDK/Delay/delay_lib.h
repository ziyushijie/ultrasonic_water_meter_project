#ifndef DELAY_LIB_H_
#define DELAY_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////


#include "config.h"
#include "delay_cfg.h"

// ����������ʱ����׼ȷ��ʱ������ @8MHZ

void XY_Delay(unsigned long xtime); // ��ʱ-���Գ���ʱ

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

// ��ʱ��Χ[10us,655.35ms];�м���ʱ���׼��10us;����Ӧ����ȡֵ��Χ:[1,65535]
void SET_Delay_us(unsigned int _10us_Xus); // 10us * Xus
void Delay_ms(unsigned int xms);  // Լ1ms~65535ms׼ȷ��ʱ


//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* DELAY_LIB_H_ */