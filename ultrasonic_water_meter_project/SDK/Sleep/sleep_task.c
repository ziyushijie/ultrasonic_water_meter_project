#include "sleep_task.h"

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t sleep_task_init(uint32_t(*func_time_tick)(void))
{
	return sleep_lib_init(func_time_tick);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t sleep_task_get(void)
{
	return sleep_lib_get();
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t sleep_task_enter(void)
{
	return sleep_lib_enter();
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t sleep_task_exit(void)
{
	return sleep_lib_exit();
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t sleep_task_wakeup_get(void)
{
	return sleep_lib_wakeup_get();
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t sleep_task_wakeup_set(uint8_t wakeup)
{
	return sleep_lib_wakeup_set(wakeup);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t sleep_task_wakeup_record_set(uint32_t wakeup_record)
{
	return sleep_lib_wakeup_record_set(wakeup_record);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint32_t sleep_task_wakeup_record_get(void)
{
	return sleep_lib_wakeup_record_get();
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t sleep_task_wakeup_exit(uint8_t wakeup)
{
	return sleep_lib_wakeup_exit(wakeup);
}