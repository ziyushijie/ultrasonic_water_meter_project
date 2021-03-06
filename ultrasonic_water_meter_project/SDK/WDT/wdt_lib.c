#include "wdt_lib.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void wdt_lib_init(void)
{
	wdt_init();
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 复位设备
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void wdt_lib_restart(void)
{
	wdt_restart();
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 看门狗中断处理函数
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t wdt_lib_it_irq_handle(void)
{
	return wdt_it_irq_handle();
}
