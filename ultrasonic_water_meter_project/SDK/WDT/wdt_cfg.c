#include "wdt_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void wdt_init(void)
{
 	//---屏蔽中断
    WDTIMK = 1U;  
    //---清楚中断标识
    WDTIIF = 0U;  
    
    //---设置中断优先级
    WDTIPR1 = 1U;
    WDTIPR0 = 1U;
   
    //---使能中断
    WDTIMK = 0U; 
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 复位设备
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void wdt_restart(void)
{
	WDTE = 0xACU;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 看门狗中断处理函数
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t wdt_it_irq_handle(void)
{
    return OK_0;
}