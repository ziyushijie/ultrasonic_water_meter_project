#include "key_lib.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 按键1中断处理函数
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t key_lib_it_irq_handle_one(KEY_HandleType *KEYx, uint8_t index)
{
	return key_it_irq_handle_one(KEYx,index);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t key_lib_time_tick_init(KEY_HandleType* KEYx, uint32_t(*func_time_tick)(void))
{
	return key_time_tick_init(KEYx, func_time_tick);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t key_lib_init(KEY_HandleType* KEYx, uint32_t(*func_time_tick)(void))
{
	return key_init(KEYx, func_time_tick);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t key_lib_scan(KEY_HandleType* KEYx)
{
	return key_scan(KEYx);
}