#include "pulse_cfg.h"

//===全局变量定义
PULSE_HandleType					g_pulse_one = {0};
pPULSE_HandleType					p_pulse_one=&g_pulse_one;

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_init_one(PULSE_HandleType* Pulsex, uint32_t(*func_time_tick)(void))
{	
	//--->>>配置端口中断---开始
//	//---不使能中断
//	PMK5 = 1U;   
//	//---清楚中断标志
//	PIF5 = 0U;    
//
//	//---设置中断优先级
//	PPR15 = 0U;
//	PPR05 = 1U;
//
//#if (PULSE_ACTIVE_LEVEL_ONE==ACTIVE_LEVEL_LOW)
//	//---屏蔽上升沿触发中断
//	EGP0 &= ~_20_INTP5_EDGE_RISING_SEL;
//	//---使能下降沿触发中断
//	EGN0 |= _20_INTP5_EDGE_FALLING_SEL;
//#elif (PULSE_ACTIVE_LEVEL_ONE==ACTIVE_LEVEL_HIGH)
//	//---屏蔽下降沿中断允许寄存器
//	EGN0 &= ~_20_INTP5_EDGE_FALLING_SEL;
//	//---使能上升沿触发中断
//	EGP0 |= _20_INTP5_EDGE_RISING_SEL;
//#else
//#error "不支持的触发中断配置!"
//#endif
//	//---设置Key为输入模式且上拉使能
//	gpio_task_pin_mode_input(PULSE_PORT_ONE, PULSE_BIT_ONE);
//#if (PULSE_ACTIVE_LEVEL_ONE==ACTIVE_LEVEL_LOW)
//	gpio_task_pin_mode_pull_up_set(PULSE_PORT_ONE, PULSE_BIT_ONE);
//#endif
//
//	//---清楚中断标志
//	PIF5 = 0U;
//	//---使能中断
//	PMK5 = 0U;

	//--->>>配置端口中断---开始
	//---不使能中断
	PMK7 = 1U;    /* disable INTP7 operation */
	//---清楚中断标志
	PIF7 = 0U;    /* clear INTP7 interrupt flag */

	//---设置中断优先级
	PPR17 = 0U;
	PPR07 = 1U;

	//---设置下降沿触发
#if (PULSE_ACTIVE_LEVEL_ONE==ACTIVE_LEVEL_LOW)
	//---屏蔽上升沿触发中断
	EGP0 &= ~_80_INTP7_EDGE_RISING_SEL;
	//---使能下降沿触发中断
	EGN0 |= _80_INTP7_EDGE_FALLING_SEL;
#elif (PULSE_ACTIVE_LEVEL_ONE==ACTIVE_LEVEL_HIGH)
	//---屏蔽下降沿触发中断
	EGN0 &= ~_80_INTP7_EDGE_FALLING_SEL;
	//---使能上升沿触发中断
	EGP0 |= _80_INTP7_EDGE_RISING_SEL;
#else
	#error "不支持的触发中断配置!"
#endif
	//---设置INT为输入模式且上拉使能
	gpio_task_pin_mode_input(PULSE_PORT_ONE, PULSE_BIT_ONE);

#if (PULSE_ACTIVE_LEVEL_ONE==ACTIVE_LEVEL_LOW)
	gpio_task_pin_mode_pull_up_set(PULSE_PORT_ONE, PULSE_BIT_ONE);
#endif

	//---清楚中断标志
	PIF7 = 0U;
	//---使能中断
	PMK7 = 0U;

	//---激活有效电平
	Pulsex->msg_level_active = PULSE_ACTIVE_LEVEL_ONE;
	//---注册端口电平读取函数
	Pulsex->msg_f_level = pulse_level_one;
	//---注册滴答函数
	(func_time_tick != NULL) ?
		(Pulsex->msg_f_time_tick = func_time_tick) :
		(Pulsex->msg_f_time_tick = sys_tick_task_get_tick);

	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_init_two(PULSE_HandleType* Pulsex, uint32_t(*func_time_tick)(void))
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_init_three(PULSE_HandleType* Pulsex, uint32_t(*func_time_tick)(void))
{

	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_start_one(PULSE_HandleType* Pulsex)
{	
	////---清除中断标识
	//PIF5 = 0U;
	////---使能中断
	//PMK5 = 0U;
	//---清除中断标识
	PIF7 = 0U;
	//---使能中断
	PMK7 = 0U;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_start_two(PULSE_HandleType* Pulsex)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_start_three(PULSE_HandleType* Pulsex)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_stop_one(PULSE_HandleType* Pulsex)
{
	////---不使能中断
	//PMK5 = 1U;
	////---清除中断标识
	//PIF5 = 0U;
	//---不使能中断
	PMK7 = 1U;
	//---清除中断标识
	PIF7 = 0U;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_stop_two(PULSE_HandleType* Pulsex)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_stop_three(PULSE_HandleType* Pulsex)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_rising_edge_one(PULSE_HandleType* Pulsex)
{
	////---屏蔽下降沿触发中断
	//EGN0 &= ~_20_INTP5_EDGE_FALLING_SEL;
	////---使能上升沿触发中断
	//EGP0 |= _20_INTP5_EDGE_RISING_SEL;
	//---屏蔽下降沿触发中断
	EGN0 &= ~_80_INTP7_EDGE_FALLING_SEL;
	//---使能上升沿触发中断
	EGP0 |= _80_INTP7_EDGE_RISING_SEL;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_falling_edge_one(PULSE_HandleType* Pulsex)
{
	////---屏蔽上升沿中断允许寄存器
	//EGP0 &= ~_20_INTP5_EDGE_RISING_SEL;
	////---使能下降沿触发中断
	//EGN0 |= _20_INTP5_EDGE_FALLING_SEL;
	//---屏蔽上升沿触发中断
	EGP0 &= ~_80_INTP7_EDGE_RISING_SEL;
	//---使能下降沿触发中断
	EGN0 |= _80_INTP7_EDGE_FALLING_SEL;
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_level_one(void)
{
	return (uint8_t)((PULSE_PORT_ONE != NULL) ? (PIN_GET_STATE(PULSE_PORT_ONE, PULSE_BIT_ONE)) : 0);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_it_irq_handle_one(PULSE_HandleType* Pulsex)
{
	//---有脉冲输入
	Pulsex->msg_actice = 1;
	//---停止中断功能
	pulse_stop_one(Pulsex);
	//---记录当前的激活周期
	Pulsex->msg_acticve_record = Pulsex->msg_f_time_tick();
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_it_irq_handle_two(PULSE_HandleType* Pulsex)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_it_irq_handle_three(PULSE_HandleType* Pulsex)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 脉冲驱动程序
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_driver_one(PULSE_HandleType* Pulsex)
{
	if (Pulsex->msg_actice!=0)
	{
		if (Pulsex->msg_f_level!=NULL)
		{
			//---获取当前按键状态
			Pulsex->msg_level_value = Pulsex->msg_f_level();
			//---按键步序
			switch (Pulsex->msg_level_step)
			{
				//---检查脉冲变化
				case 0:
				{
					//---校验按键有效性
					if (Pulsex->msg_level_value == Pulsex->msg_level_active)
					{
						//---记录时间
						Pulsex->msg_level_record = Pulsex->msg_f_time_tick();
						//---进入按键消抖
						Pulsex->msg_level_step = 1;
					}
					else
					{
						//---没有按键按下
						Pulsex->msg_level_state = ACTIVE_STATE_DISABLE;
					}
					break;
				}
				//---脉冲消抖处理
				case 1:
				{
					//---校验按键有效性
					if (Pulsex->msg_level_value == Pulsex->msg_level_active)
					{
						//---校验消除抖动时间是否到达
						if (TIME_SPAN(Pulsex->msg_f_time_tick(), Pulsex->msg_level_record) > PULSE_ACTIVE_TIME_STABLE)
						{
							//---记录时间
							Pulsex->msg_level_record = Pulsex->msg_f_time_tick();
							//---按键时间超过了消抖时间，判断按键有效；去判断按键的状态
							Pulsex->msg_level_step = 0;
							//---按键误触信号，重新扫描
							Pulsex->msg_level_state = ACTIVE_STATE_ENABLE;
							//---清零激活状态
							Pulsex->msg_actice = 0;
						}
					}
					else
					{
						//---状态清零，重新扫描按键
						Pulsex->msg_level_step = 0;
						//---按键误触信号，重新扫描
						Pulsex->msg_level_state = ACTIVE_STATE_DISABLE;
					}
					break;
				}
				default:
				{
					//---状态清零，重新扫描按键
					Pulsex->msg_level_step = 0;
					//---按键误触信号，重新扫描
					Pulsex->msg_level_state = ACTIVE_STATE_DISABLE;
					//---清零激活状态
					Pulsex->msg_actice = 0;
					//---继续下一次的技术
					pulse_start_one(Pulsex);
					break;
				}
			}
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_driver_two(PULSE_HandleType* Pulsex)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_driver_three(PULSE_HandleType* Pulsex)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 扫描脉冲变化是否有效
//////输入参	数:
//////输出参	数: 0,计数到脉冲，1，没有计数到脉冲
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_scan_one(PULSE_HandleType* Pulsex)
{
	pulse_driver_one(Pulsex);
	//---判断电平变化是否有效
	if (Pulsex->msg_level_state ==ACTIVE_STATE_ENABLE)
	{
		Pulsex->msg_level_count++;
		//---清零电平有效标识
		Pulsex->msg_level_state = ACTIVE_STATE_DISABLE;
		//---继续下一次的脉冲触发
		pulse_start_one(Pulsex);
		//---返回结果
		return OK_0;
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_scan_two(PULSE_HandleType* Pulsex)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_scan_three(PULSE_HandleType* Pulsex)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_scan(PULSE_HandleType* Pulsex)
{
	if ((Pulsex != NULL) && (Pulsex == PULSE_TASK_ONE))
	{
		return pulse_scan_one(Pulsex);
	}
	if ((Pulsex != NULL) && (Pulsex == PULSE_TASK_TWO))
	{
		return pulse_scan_two(Pulsex);
	}
	if ((Pulsex != NULL) && (Pulsex == PULSE_TASK_THREE))
	{
		return pulse_scan_three(Pulsex);
	}
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_time_tick_init(PULSE_HandleType* Pulsex, uint32_t(*func_time_tick)(void))
{
	//---注册滴答函数
	(func_time_tick != NULL) ?
		(Pulsex->msg_f_time_tick = func_time_tick) :
		(Pulsex->msg_f_time_tick = sys_tick_task_get_tick);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_init(PULSE_HandleType* Pulsex, uint32_t(*func_time_tick)(void))
{
	if ((Pulsex != NULL) && (Pulsex == PULSE_TASK_ONE))
	{
		return pulse_init_one(Pulsex,func_time_tick);
	}
	if ((Pulsex != NULL) && (Pulsex == PULSE_TASK_TWO))
	{
		return pulse_init_two(Pulsex,func_time_tick);
	}
	if ((Pulsex != NULL) && (Pulsex == PULSE_TASK_THREE))
	{
		return pulse_init_three(Pulsex,func_time_tick);
	}
	return ERROR_2;
}
