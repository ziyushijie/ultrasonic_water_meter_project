#include "ms1022_cfg.h"

//===��������
MS1022_HandleType						g_ms1022_one = { 0 };
pMS1022_HandleType						p_ms1022_one = &g_ms1022_one;

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_time_tick_init(MS1022_HandleType* MS1022x, uint32_t(*func_time_tick)(void))
{
	//---ע��δ���
	(func_time_tick != NULL) ?
		(MS1022x->msg_f_time_tick = func_time_tick,MS1022x->msg_spix.msg_f_time_tick= func_time_tick) :
		(MS1022x->msg_f_time_tick = sys_tick_task_get_tick, MS1022x->msg_spix.msg_f_time_tick = sys_tick_task_get_tick);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_init(MS1022_HandleType* MS1022x, void(*func_delay_us)(uint32_t us), 
	void(*func_delay_ms)(uint32_t ms), uint32_t(*func_time_tick)(void))
{
	//---us��ʱ����
	(func_delay_us != NULL) ?
		(MS1022x->msg_spix.msg_f_delay_us = func_delay_us) :
		(MS1022x->msg_spix.msg_f_delay_us = delay_task_us);
	//---ms��ʱ����
	(func_delay_us != NULL) ?
		(MS1022x->msg_f_delay_ms = func_delay_ms) :
		(MS1022x->msg_f_delay_ms = delay_task_ms);
	//---ע��δ���
	(func_time_tick != NULL) ?
		(MS1022x->msg_f_time_tick = func_time_tick, MS1022x->msg_spix.msg_f_time_tick = func_time_tick) :
		(MS1022x->msg_f_time_tick = sys_tick_task_get_tick, MS1022x->msg_spix.msg_f_time_tick = sys_tick_task_get_tick);
	return OK_0;
}