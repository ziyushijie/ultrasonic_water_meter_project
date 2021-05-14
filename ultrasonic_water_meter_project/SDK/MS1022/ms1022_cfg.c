#include "ms1022_cfg.h"

//===变量定义
MS1022_HandleType						g_ms1022_one = { 0 };
pMS1022_HandleType						p_ms1022_one = &g_ms1022_one;

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_time_tick_init(MS1022_HandleType* MS1022x, uint32_t(*func_time_tick)(void))
{
	//---注册滴答函数
	(func_time_tick != NULL) ?
		(MS1022x->msg_f_time_tick = func_time_tick,MS1022x->msg_spix.msg_f_time_tick= func_time_tick) :
		(MS1022x->msg_f_time_tick = sys_tick_task_get_tick, MS1022x->msg_spix.msg_f_time_tick = sys_tick_task_get_tick);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_init(MS1022_HandleType* MS1022x, void(*func_delay_us)(uint32_t us), 
	void(*func_delay_ms)(uint32_t ms), uint32_t(*func_time_tick)(void))
{
	//---us延时函数
	(func_delay_us != NULL) ?
		(MS1022x->msg_spix.msg_f_delay_us = func_delay_us) :
		(MS1022x->msg_spix.msg_f_delay_us = delay_task_us);
	//---ms延时函数
	(func_delay_us != NULL) ?
		(MS1022x->msg_f_delay_ms = func_delay_ms) :
		(MS1022x->msg_f_delay_ms = delay_task_ms);
	//---注册滴答函数
	(func_time_tick != NULL) ?
		(MS1022x->msg_f_time_tick = func_time_tick, MS1022x->msg_spix.msg_f_time_tick = func_time_tick) :
		(MS1022x->msg_f_time_tick = sys_tick_task_get_tick, MS1022x->msg_spix.msg_f_time_tick = sys_tick_task_get_tick);
	return OK_0;
}