#include "sleep_task.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t sleep_task_init(uint32_t(*func_time_tick)(void))
{
	return sleep_lib_init(func_time_tick);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t sleep_task_get(void)
{
	return sleep_lib_get();
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t sleep_task_enter(void)
{
	return sleep_lib_enter();
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t sleep_task_exit(void)
{
	return sleep_lib_exit();
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t sleep_task_wakeup_get(void)
{
	return sleep_lib_wakeup_get();
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t sleep_task_wakeup_set(uint8_t wakeup)
{
	return sleep_lib_wakeup_set(wakeup);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t sleep_task_wakeup_record_set(uint32_t wakeup_record)
{
	return sleep_lib_wakeup_record_set(wakeup_record);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint32_t sleep_task_wakeup_record_get(void)
{
	return sleep_lib_wakeup_record_get();
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t sleep_task_wakeup_exit(uint8_t wakeup)
{
	return sleep_lib_wakeup_exit(wakeup);
}