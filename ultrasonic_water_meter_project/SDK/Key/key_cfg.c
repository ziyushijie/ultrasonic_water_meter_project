#include "key_cfg.h"

//===全局变量定义
KEY_HandleType		g_key_one = {0};
pKEY_HandleType		p_key_one=&g_key_one;

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 初始化按键1
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t key_init_one(KEY_HandleType* KEYx,uint32_t(*func_time_tick)(void))
{
#if (KEY_BUTTON_MAX_NUM > 1)
	uint8_t button_index = 0;
	for (button_index=0;button_index<KEY_BUTTON_MAX_NUM;button_index++)
	{
		//---注册端口电平读取函数
		KEYx->msg_button[button_index].msg_f_pin_level = key_pin_level_one;
		//---注册滴答函数
		(func_time_tick != NULL) ?
			(KEYx->msg_button[button_index].msg_f_time_tick = func_time_tick) :
			(KEYx->msg_button[button_index].msg_f_time_tick = sys_tick_task_get_tick);
		//---按键激活状态和序号
		switch (button_index)
		{
			case 0:
			{
				KEYx->msg_button[button_index].msg_pin_index = KEY_BUTTON_INDEX_ONE_K1;
				//---激活有效电平
				KEYx->msg_button[button_index].msg_pin_level_active = KEY_BUTTON_ACTIVE_LEVEL_ONE_K1;
				break;
			}
			case 1:
			{
				KEYx->msg_button[button_index].msg_pin_index = 1;
				//---激活有效电平
				KEYx->msg_button[button_index].msg_pin_level_active = KEY_BUTTON_ACTIVE_LEVEL_ONE_K1;
				break;
			}
			case 2:
			{
				break;
			}
			case 3:
			{
				break;
			}
			default:
				break;
		}
	}
#else
	//--->>>配置端口中断---开始
	//---不使能中断
	PMK0 = 1U;
	//---清楚中断标志
	PIF0 = 0U;

	//---设置中断优先级
	PPR10 = 0U;
	PPR00 = 1U;

#if (KEY_BUTTON_ACTIVE_LEVEL_ONE_K1==ACTIVE_LEVEL_LOW)
	//---屏蔽上升沿触发中断
	EGP0 &= ~_01_INTP0_EDGE_RISING_SEL;
	//---使能下降沿触发中断
	EGN0 |= _01_INTP0_EDGE_FALLING_SEL;
#elif (KEY_BUTTON_ACTIVE_LEVEL_ONE_K1==ACTIVE_LEVEL_HIGH)
	//---屏蔽下降沿触发中断
	EGN0 &=~ _01_INTP0_EDGE_FALLING_SEL;
	//---使能上升沿触发中断
	EGP0 |= _01_INTP0_EDGE_RISING_SEL;
#else
	#error "不支持的触发中断配置!"
#endif
	//---设置Key为输入模式且上拉使能
	gpio_task_pin_mode_input(KEY_BUTTON_PORT_ONE_K1, KEY_BUTTON_BIT_ONE_K1);
#if (KEY_BUTTON_ACTIVE_LEVEL_ONE_K1==ACTIVE_LEVEL_LOW)
	gpio_task_pin_mode_pull_up_set(KEY_BUTTON_PORT_ONE_K1, KEY_BUTTON_BIT_ONE_K1);
#endif
	//---清楚中断标志
	PIF0 = 0U;
	//---使能中断
	PMK0 = 0U;

	KEYx->msg_button.msg_pin_index = KEY_BUTTON_INDEX_ONE_K1;
	//---激活有效电平
	KEYx->msg_button.msg_pin_level_active = KEY_BUTTON_ACTIVE_LEVEL_ONE_K1;
	//---注册端口电平读取函数
	KEYx->msg_button.msg_f_pin_level = key_pin_level_one;
	//---注册滴答函数
	(func_time_tick != NULL) ?
		(KEYx->msg_button.msg_f_time_tick = func_time_tick) :
		(KEYx->msg_button.msg_f_time_tick = sys_tick_task_get_tick);
#endif

	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t key_init_two(KEY_HandleType* KEYx, uint32_t(*func_time_tick)(void))
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
uint8_t key_init_three(KEY_HandleType* KEYx, uint32_t(*func_time_tick)(void))
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 启动按键1中断
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t key_start_one(KEY_HandleType* KEYx,uint8_t index)
{
#if (KEY_BUTTON_MAX_NUM > 1)
	return ERROR_1;
#else
	//---清除中断标识
	PIF0 = 0U;    
	//---使能中断
	PMK0 = 0U;    
	return OK_0;
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 停止按键1中断
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t key_stop_one(KEY_HandleType* KEYx,uint8_t index)
{
#if (KEY_BUTTON_MAX_NUM > 1)
	return ERROR_1;
#else
	//---使能中断
	PMK0 = 1U;    
	//---清除中断标识
	PIF0 = 0U;   
	return OK_0;
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t key_rising_edge_one(KEY_HandleType* KEYx,uint8_t index)
{
#if (KEY_BUTTON_MAX_NUM > 1)
	return ERROR_1;
#else
	//---屏蔽下降沿中断允许寄存器
	EGN0 &= ~_01_INTP0_EDGE_FALLING_SEL;
	//---使能上升沿触发中断
	EGP0 |= _01_INTP0_EDGE_RISING_SEL;
	return OK_0;
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t key_falling_edge_one(KEY_HandleType* KEYx, uint8_t index)
{
#if (KEY_BUTTON_MAX_NUM > 1)
	return ERROR_1;
#else
	//---屏蔽上升沿中断允许寄存器
	EGP0 &= ~_01_INTP0_EDGE_RISING_SEL;
	//---使能下降沿触发中断
	EGN0 |= _01_INTP0_EDGE_FALLING_SEL;
	return OK_0;
#endif
}


///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t key_pin_level_one(uint8_t index)
{
#if (KEY_BUTTON_MAX_NUM>1)
	uint8_t _return = ERROR_FF;
	//---判断是哪个按键
	switch (index)
	{
		case 0:
		{
			_return = (uint8_t)((KEY_BUTTON_PORT_ONE_K1 != NULL) ? (PIN_GET_STATE(KEY_BUTTON_PORT_ONE_K1, KEY_BUTTON_BIT_ONE_K1)) : 0);
			break;
		}
		case 1:
		{
			break;
		}
		case 2:
		{
			break;
		}
		default:
		{
			break;
		}
	}
	return _return;
#else
	return (uint8_t)((KEY_BUTTON_PORT_ONE_K1 != NULL) ? (PIN_GET_STATE(KEY_BUTTON_PORT_ONE_K1, KEY_BUTTON_BIT_ONE_K1)) : 0);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t key_it_irq_handle_one(KEY_HandleType *KEYx, uint8_t index)
{
	//---停止按键中断
	key_stop_one(KEYx,index);
	//---标注有按键按下
#if (KEY_BUTTON_MAX_NUM>1)
	return ERROR_1;
#else
	KEYx->msg_active = 1;
	return OK_0;
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 按键按下驱动
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t key_driver_one(KEY_PRESS_HandleType* KEYx)
{
	if (KEYx->msg_f_pin_level!=NULL)
	{
		//---获取当前按键状态
		KEYx->msg_pin_level_value = KEYx->msg_f_pin_level(KEYx->msg_pin_index);
		//---按键步序
		switch (KEYx->msg_pin_level_step)
		{
			//---判断有无按键按下
			case 0:
			{
				//---校验按键有效性
				if (KEYx->msg_pin_level_value== KEYx->msg_pin_level_active)
				{
					//---记录时间
					KEYx->msg_pin_level_record = KEYx->msg_f_time_tick();
					//---进入按键消抖
					KEYx->msg_pin_level_step = 1;
				}
				else
				{
					//---没有按键按下
					KEYx->msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
				}
				break;
			}
			//---按键消抖动
			case 1:
			{
				//---校验按键有效性
				if (KEYx->msg_pin_level_value == KEYx->msg_pin_level_active)
				{
					if (TIME_SPAN(KEYx->msg_f_time_tick(), KEYx->msg_pin_level_record)> KEY_BUTTON_ACTIVE_TIME_STABLE)
					{
						//---记录时间
						KEYx->msg_pin_level_record = KEYx->msg_f_time_tick();
						//---按键时间超过了消抖时间，判断按键有效；去判断按键的状态
						KEYx->msg_pin_level_step = 2;
					}
				}
				else
				{
					//---状态清零，重新扫描按键
					KEYx->msg_pin_level_step = 0;
					//---按键误触信号，重新扫描
					KEYx->msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
				}
				break;
			}
			//---判断单击还是长击
			case 2:
			{
				//---校验按键有效性
				if (KEYx->msg_pin_level_value != KEYx->msg_pin_level_active)
				{
					//---按键释放，按键有效状态是单击
					KEYx->msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_ONE;
					//---状态归0，继续扫描按键
					KEYx->msg_pin_level_step = 0;
				}
				else
				{
					//---按键时间超出设定的长按时间
					if (TIME_SPAN(KEYx->msg_f_time_tick(), KEYx->msg_pin_level_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_LONG)
					{
						//---按键有效状态是长按,接下来判断是不是超长击
						KEYx->msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_LONG;
						//---按键时间超过了消抖时间，判断按键有效；去判断按键的状态
						KEYx->msg_pin_level_step = 3;
					}
				}
				break;
			}
			//---判断长击还是超长击中
			case 3:
			{
				//---校验按键有效性
				if (KEYx->msg_pin_level_value != KEYx->msg_pin_level_active)
				{
					//---按键释放，按键有效状态是长击
					KEYx->msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_LONG;
					//---状态归零，继续扫描按键
					KEYx->msg_pin_level_step = 0;
					//---长击事件
#if (MODULE_LOG_KEY_BUTTON>0)
					LOG_VA_ARGS("按键:长击\r\n");
#endif
				}
				else
				{
					//---按键时间超出设定的长按时间
					if (TIME_SPAN(KEYx->msg_f_time_tick(), KEYx->msg_pin_level_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_LONG_LONG)
					{
						//---按键有效状态是长按
						KEYx->msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_LONG_LONG;
						//---按键时间超过了消抖时间，判断按键有效；去判断按键的状态
						KEYx->msg_pin_level_step = 4;
						//---超长击事件
#if (MODULE_LOG_KEY_BUTTON>0)
						LOG_VA_ARGS("按键:超长击\r\n");
#endif
					}
				}
				break;
			}
			//---超长按键
			case 4:
			{
				if (KEYx->msg_pin_level_value == KEYx->msg_pin_level_active)
				{
					//---记录时间
					KEYx->msg_pin_level_record = KEYx->msg_f_time_tick();
					//---状态归零，继续扫描按键
					KEYx->msg_pin_level_step = 5;
					//---错误事件
				}
				else
				{
					//---状态归零，继续扫描按键
					KEYx->msg_pin_level_step = 0;
				}
				break;
			}
			//---按键错误
			case 5:
			{
				if (KEYx->msg_pin_level_value == KEYx->msg_pin_level_active)
				{
					//---按键时间超出设定的错误时间
					if (TIME_SPAN(KEYx->msg_f_time_tick(), KEYx->msg_pin_level_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_ERROR)
					{
						//---按键有效状态是长按
						KEYx->msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
						//---状态归零，继续扫描按键
						KEYx->msg_pin_level_step = 6;
						//---超长击事件
#if (MODULE_LOG_KEY_BUTTON>0)
						LOG_VA_ARGS("按键:错误\r\n");
#endif
					}
				}
				else
				{
					//---状态归零，继续扫描按键
					KEYx->msg_pin_level_step = 0;
				}
			}
			//---错误退出
			case 6:
			{
				if (KEYx->msg_pin_level_value != KEYx->msg_pin_level_active)
				{
					//---按键有效状态是长按
					KEYx->msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
					//---状态归零，继续扫描按键
					KEYx->msg_pin_level_step = 0;
					//---超长击事件
#if (MODULE_LOG_KEY_BUTTON>0)
					LOG_VA_ARGS("按键:恢复\r\n");
#endif
				}
				break;
			}
			default:
			{	
				//---状态归零，继续扫描按键
				KEYx->msg_pin_level_step = 0;
				break;
			}
		}
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
uint8_t key_scan_one(KEY_HandleType* KEYx)
{
#if (KEY_BUTTON_MAX_NUM>1)
	uint8_t button_index = 0;
	for (button_index=0;button_index< KEY_BUTTON_MAX_NUM;button_index++)
	{
		//---获取按键状态
		key_press_driver_one(&(KEYx->msg_button[button_index]));
		//---扫描状态轮训
		switch (KEYx->msg_button[button_index].msg_pin_scan_step)
		{
			//---检查有效按键
			case 0:
			{
				if (KEYx->msg_button[button_index].msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
				{
					//---单击操作，不马上返回键值，判断是不是双击
					KEYx->msg_button[button_index].msg_pin_scan_record = KEYx->msg_button[button_index].msg_f_time_tick();
					//---下一状态
					KEYx->msg_button[button_index].msg_pin_scan_step = 1;
					//---单击操作
					KEYx->msg_button[button_index].msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_ONE;
				}
				else
				{
					//---直接返回键值
					KEYx->msg_button[button_index].msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
					//---返回状态0，等待新的有效按键
					KEYx->msg_button[button_index].msg_pin_scan_step = 0;
				}
				break;
			}
			//---校验单击
			case 1:
			{
				if (KEYx->msg_button[button_index].msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
				{
					//---单击操作，不马上返回键值，判断是不是双击
					KEYx->msg_button[button_index].msg_pin_scan_record = KEYx->msg_button[button_index].msg_f_time_tick();
					//---下一状态
					KEYx->msg_button[button_index].msg_pin_scan_step = 2;
				}
				else
				{
					//---判断是否超过时间间隔
					if (TIME_SPAN(KEYx->msg_button[button_index].msg_f_time_tick(),
						KEYx->msg_button[button_index].msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE)
					{
						//---按键有效
						KEYx->msg_button[button_index].msg_pin_scan_active = ACTIVE_STATE_ENABLE;
						//---返回有效按键状态为单击
						KEYx->msg_button[button_index].msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
						//---单击操作
						KEYx->msg_button[button_index].msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_ONE;
						//---返回状态0，等待新的有效按键
						KEYx->msg_button[button_index].msg_pin_scan_step = 0;
						//---执行单击操作
#if (MODULE_LOG_KEY_BUTTON>0)
						LOG_VA_ARGS("按键%d:单击\r\n",button_index+1);
#endif
					}
				}
				break;
			}
			//---校验双击
			case 2:
			{
				if (KEYx->msg_button[button_index].msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
				{
					//---单击操作，不马上返回键值，判断是不是双击
					KEYx->msg_button[button_index].msg_pin_scan_record = KEYx->msg_button[button_index].msg_f_time_tick();
					//---下一状态
					KEYx->msg_button[button_index].msg_pin_scan_step = 3;
				}
				else
				{
					//---判断是否超过时间间隔
					if (TIME_SPAN(KEYx->msg_button[button_index].msg_f_time_tick(),
						KEYx->msg_button[button_index].msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_TWO)
					{
						//---按键有效
						KEYx->msg_button[button_index].msg_pin_scan_active = ACTIVE_STATE_ENABLE;
						//---返回有效按键状态为双击
						KEYx->msg_button[button_index].msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
						//---双击操作
						KEYx->msg_button[button_index].msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_TWO;
						//---返回状态0，等待新的有效按键
						KEYx->msg_button[button_index].msg_pin_scan_step = 0;
						//---执行双击操作
#if (MODULE_LOG_KEY_BUTTON>0)
						LOG_VA_ARGS("按键%d:双击\r\n", button_index + 1);
#endif
					}
				}
				break;
			}
			//---校验三击
			case 3:
			{
				if (KEYx->msg_button[button_index].msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
				{
					//---单击操作，不马上返回键值，判断是不是双击
					KEYx->msg_button[button_index].msg_pin_scan_record = KEYx->msg_button[button_index].msg_f_time_tick();
					//---下一状态
					KEYx->msg_button[button_index].msg_pin_scan_step = 4;
				}
				else
				{
					//---判断是否超过时间间隔
					if (TIME_SPAN(KEYx->msg_button[button_index].msg_f_time_tick(),
						KEYx->msg_button[button_index].msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_THREE)
					{
						//---按键有效
						KEYx->msg_button[button_index].msg_pin_scan_active = ACTIVE_STATE_ENABLE;
						//---返回有效按键状态为双击
						KEYx->msg_button[button_index].msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
						//---双击操作
						KEYx->msg_button[button_index].msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_THREE;
						//---返回状态0，等待新的有效按键
						KEYx->msg_button[button_index].msg_pin_scan_step = 0;
						//---执行三击操作
#if (MODULE_LOG_KEY_BUTTON>0)
						LOG_VA_ARGS("按键%d:三击\r\n", button_index + 1);
#endif
					}
				}
				break;
			}
			//---校验四击
			case 4:
			{
				if (KEYx->msg_button[button_index].msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
				{
					//---单击操作，不马上返回键值，判断是不是双击
					KEYx->msg_button[button_index].msg_pin_scan_record = KEYx->msg_button[button_index].msg_f_time_tick();
					//---下一状态
					KEYx->msg_button[button_index].msg_pin_scan_step = 5;
				}
				else
				{
					//---判断是否超过时间间隔
					if (TIME_SPAN(KEYx->msg_button[button_index].msg_f_time_tick(),
						KEYx->msg_button[button_index].msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_FOUR)
					{
						//---按键有效
						KEYx->msg_button[button_index].msg_pin_scan_active = ACTIVE_STATE_ENABLE;
						//---返回有效按键状态为双击
						KEYx->msg_button[button_index].msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
						//---双击操作
						KEYx->msg_button[button_index].msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_FOUR;
						//---返回状态0，等待新的有效按键
						KEYx->msg_button[button_index].msg_pin_scan_step = 0;
						//---执行四击操作
#if (MODULE_LOG_KEY_BUTTON>0)
						LOG_VA_ARGS("按键%d:四击\r\n", button_index + 1);
#endif
					}
				}
				break;
			}
			//---校验五击
			case 5:
			{
				if (KEYx->msg_button[button_index].msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
				{
					//---单击操作，不马上返回键值，判断是不是双击
					KEYx->msg_button[button_index].msg_pin_scan_record = KEYx->msg_button[button_index].msg_f_time_tick();
					//---下一状态
					KEYx->msg_button[button_index].msg_pin_scan_step = 6;
				}
				else
				{
					//---判断是否超过时间间隔
					if (TIME_SPAN(KEYx->msg_button[button_index].msg_f_time_tick(),
						KEYx->msg_button[button_index].msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_FIVR)
					{
						//---按键有效
						KEYx->msg_button[button_index].msg_pin_scan_active = ACTIVE_STATE_ENABLE;
						//---返回有效按键状态为双击
						KEYx->msg_button[button_index].msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
						//---双击操作
						KEYx->msg_button[button_index].msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_FIVE;
						//---返回状态0，等待新的有效按键
						KEYx->msg_button[button_index].msg_pin_scan_step = 0;
						//---执行五击操作
#if (MODULE_LOG_KEY_BUTTON>0)
						LOG_VA_ARGS("按键%d:五击\r\n", button_index + 1);
#endif
					}
				}
				break;
			}
			//---校验六击
			case 6:
			{
				if (KEYx->msg_button[button_index].msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
				{
					//---单击操作，不马上返回键值，判断是不是双击
					KEYx->msg_button[button_index].msg_pin_scan_record = KEYx->msg_button[button_index].msg_f_time_tick();
					//---下一状态
					KEYx->msg_button[button_index].msg_pin_scan_step = 7;
				}
				else
				{
					//---判断是否超过时间间隔
					if (TIME_SPAN(KEYx->msg_button[button_index].msg_f_time_tick(),
						KEYx->msg_button[button_index].msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_SIX)
					{
						//---按键有效
						KEYx->msg_button[button_index].msg_pin_scan_active = ACTIVE_STATE_ENABLE;
						//---返回有效按键状态为双击
						KEYx->msg_button[button_index].msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
						//---双击操作
						KEYx->msg_button[button_index].msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_SIX;
						//---返回状态0，等待新的有效按键
						KEYx->msg_button[button_index].msg_pin_scan_step = 0;
						//---执行六击操作
#if (MODULE_LOG_KEY_BUTTON>0)
						LOG_VA_ARGS("按键%d:六击\r\n", button_index + 1);
#endif
					}
				}
				break;
			}
			//---校验七击
			case 7:
			{
				if (KEYx->msg_button[button_index].msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
				{
					//---单击操作，不马上返回键值，判断是不是双击
					KEYx->msg_button[button_index].msg_pin_scan_record = KEYx->msg_button[button_index].msg_f_time_tick();
					//---下一状态
					KEYx->msg_button[button_index].msg_pin_scan_step = 8;
				}
				else
				{
					//---判断是否超过时间间隔
					if (TIME_SPAN(KEYx->msg_button[button_index].msg_f_time_tick(),
						KEYx->msg_button[button_index].msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_SEVEN)
					{
						//---按键有效
						KEYx->msg_button[button_index].msg_pin_scan_active = ACTIVE_STATE_ENABLE;
						//---返回有效按键状态为双击
						KEYx->msg_button[button_index].msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
						//---双击操作
						KEYx->msg_button[button_index].msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_SEVEN;
						//---返回状态0，等待新的有效按键
						KEYx->msg_button[button_index].msg_pin_scan_step = 0;
						//---执行七击操作
#if (MODULE_LOG_KEY_BUTTON>0)
						LOG_VA_ARGS("按键%d:七击\r\n", button_index + 1);
#endif
					}
				}
				break;
			}
			//---校验八击
			case 8:
			{
				if (KEYx->msg_button[button_index].msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
				{
					//---单击操作，不马上返回键值，判断是不是双击
					KEYx->msg_button[button_index].msg_pin_scan_record = KEYx->msg_button[button_index].msg_f_time_tick();
					//---下一状态
					KEYx->msg_button[button_index].msg_pin_scan_step = 9;
				}
				else
				{
					//---判断是否超过时间间隔
					if (TIME_SPAN(KEYx->msg_button[button_index].msg_f_time_tick(),
						KEYx->msg_button[button_index].msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_EIGHT)
					{
						//---按键有效
						KEYx->msg_button[button_index].msg_pin_scan_active = ACTIVE_STATE_ENABLE;
						//---返回有效按键状态为双击
						KEYx->msg_button[button_index].msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
						//---双击操作
						KEYx->msg_button[button_index].msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_EIGHT;
						//---返回状态0，等待新的有效按键
						KEYx->msg_button[button_index].msg_pin_scan_step = 0;
						//---执行八击操作
#if (MODULE_LOG_KEY_BUTTON>0)
						LOG_VA_ARGS("按键%d:八击\r\n", button_index + 1);
#endif
					}
				}
				break;
			}
			//---校验九击
			case 9:
			{
				if (KEYx->msg_button[button_index].msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
				{
					//---单击操作，不马上返回键值，判断是不是双击
					KEYx->msg_button[button_index].msg_pin_scan_record = KEYx->msg_button[button_index].msg_f_time_tick();
					//---下一状态
					KEYx->msg_button[button_index].msg_pin_scan_step = 10;
				}
				else
				{
					//---判断是否超过时间间隔
					if (TIME_SPAN(KEYx->msg_button[button_index].msg_f_time_tick(),
						KEYx->msg_button[button_index].msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_NINE)
					{
						//---按键有效
						KEYx->msg_button[button_index].msg_pin_scan_active = ACTIVE_STATE_ENABLE;
						//---返回有效按键状态为双击
						KEYx->msg_button[button_index].msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
						//---双击操作
						KEYx->msg_button[button_index].msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_NINE;
						//---返回状态0，等待新的有效按键
						KEYx->msg_button[button_index].msg_pin_scan_step = 0;
						//---执行九击操作
#if (MODULE_LOG_KEY_BUTTON>0)
						LOG_VA_ARGS("按键%d:九击\r\n", button_index + 1);
#endif
					}
				}
				break;
			}
			//---校验十击
			case 10:
			{
				if (KEYx->msg_button[button_index].msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
				{
					//---单击操作，不马上返回键值，判断是不是双击
					KEYx->msg_button[button_index].msg_pin_scan_record = KEYx->msg_button[button_index].msg_f_time_tick();
					//---下一状态
					KEYx->msg_button[button_index].msg_pin_scan_step = 11;
				}
				else
				{
					//---判断是否超过时间间隔
					if (TIME_SPAN(KEYx->msg_button[button_index].msg_f_time_tick(),
						KEYx->msg_button[button_index].msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_TEN)
					{
						//---按键有效
						KEYx->msg_button[button_index].msg_pin_scan_active = ACTIVE_STATE_ENABLE;
						//---返回有效按键状态为双击
						KEYx->msg_button[button_index].msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
						//---双击操作
						KEYx->msg_button[button_index].msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_TEN;
						//---返回状态0，等待新的有效按键
						KEYx->msg_button[button_index].msg_pin_scan_step = 0;
						//---执行十击操作
#if (MODULE_LOG_KEY_BUTTON>0)
						LOG_VA_ARGS("按键%d:十击\r\n", button_index + 1);
#endif
					}
				}
				break;
			}
			//---结束
			case 11:
			default:
			{
				//---单击操作，不马上返回键值，判断是不是双击
				KEYx->msg_button[button_index].msg_pin_scan_record = KEYx->msg_button[button_index].msg_f_time_tick();
				//---返回有效按键状态为无效
				KEYx->msg_button[button_index].msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
				//---双击操作
				KEYx->msg_button[button_index].msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
				//---按键有效
				KEYx->msg_button[button_index].msg_pin_scan_active = ACTIVE_STATE_DISABLE;
				//---返回状态0，等待新的有效按键
				KEYx->msg_button[button_index].msg_pin_scan_step = 0;
				//---执行按键无效操作
				break;
			}
		}
	}
#else
	//---获取按键状态
	key_driver_one(&(KEYx->msg_button));
	//---扫描状态轮训
	switch (KEYx->msg_button.msg_pin_scan_step)
	{
		//---检查有效按键
		case 0:
		{
			if (KEYx->msg_button.msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
			{
				//---单击操作，不马上返回键值，判断是不是双击
				KEYx->msg_button.msg_pin_scan_record = KEYx->msg_button.msg_f_time_tick();
				//---下一状态
				KEYx->msg_button.msg_pin_scan_step = 1;
				//---单击操作
				KEYx->msg_button.msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_ONE;
			}
			else
			{
				//---直接返回键值
				KEYx->msg_button.msg_pin_level_state= KEY_BUTTON_PRESS_STATE_CLICK_NONE;
				//---返回状态0，等待新的有效按键
				KEYx->msg_button.msg_pin_scan_step = 0;
			}
			break;
		}
		//---校验单击
		case 1:
		{
			if (KEYx->msg_button.msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
			{
				//---单击操作，不马上返回键值，判断是不是双击
				KEYx->msg_button.msg_pin_scan_record = KEYx->msg_button.msg_f_time_tick();
				//---下一状态
				KEYx->msg_button.msg_pin_scan_step = 2;
			}
			else
			{
				//---判断是否超过时间间隔
				if (TIME_SPAN(KEYx->msg_button.msg_f_time_tick(),
					KEYx->msg_button.msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE)
				{
					//---按键有效
					KEYx->msg_button.msg_pin_scan_active = ACTIVE_STATE_ENABLE;
					//---返回有效按键状态为单击
					KEYx->msg_button.msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
					//---单击操作
					KEYx->msg_button.msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_ONE;
					//---返回状态0，等待新的有效按键
					KEYx->msg_button.msg_pin_scan_step = 0;
					//---执行单击操作
#if (MODULE_LOG_KEY_BUTTON>0)
					LOG_VA_ARGS("按键:单击\r\n");
#endif
				}
			}
			break;
		}
		//---校验双击
		case 2:
		{
			if (KEYx->msg_button.msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
			{
				//---单击操作，不马上返回键值，判断是不是双击
				KEYx->msg_button.msg_pin_scan_record = KEYx->msg_button.msg_f_time_tick();
				//---下一状态
				KEYx->msg_button.msg_pin_scan_step = 3;
			}
			else
			{
				//---判断是否超过时间间隔
				if (TIME_SPAN(KEYx->msg_button.msg_f_time_tick(),
					KEYx->msg_button.msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_TWO)
				{
					//---按键有效
					KEYx->msg_button.msg_pin_scan_active = ACTIVE_STATE_ENABLE;
					//---返回有效按键状态为双击
					KEYx->msg_button.msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
					//---双击操作
					KEYx->msg_button.msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_TWO;
					//---返回状态0，等待新的有效按键
					KEYx->msg_button.msg_pin_scan_step = 0;
					//---执行双击操作
#if (MODULE_LOG_KEY_BUTTON>0)
					LOG_VA_ARGS("按键:双击\r\n");
#endif
				}
			}
			break;
		}
		//---校验三击
		case 3:
		{
			if (KEYx->msg_button.msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
			{
				//---单击操作，不马上返回键值，判断是不是双击
				KEYx->msg_button.msg_pin_scan_record = KEYx->msg_button.msg_f_time_tick();
				//---下一状态
				KEYx->msg_button.msg_pin_scan_step = 4;
			}
			else
			{
				//---判断是否超过时间间隔
				if (TIME_SPAN(KEYx->msg_button.msg_f_time_tick(),
					KEYx->msg_button.msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_THREE)
				{
					//---按键有效
					KEYx->msg_button.msg_pin_scan_active = ACTIVE_STATE_ENABLE;
					//---返回有效按键状态为双击
					KEYx->msg_button.msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
					//---双击操作
					KEYx->msg_button.msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_THREE;
					//---返回状态0，等待新的有效按键
					KEYx->msg_button.msg_pin_scan_step = 0;
					//---执行三击操作
#if (MODULE_LOG_KEY_BUTTON>0)
					LOG_VA_ARGS("按键:三击\r\n");
#endif
				}
			}
			break;
		}
		//---校验四击
		case 4:
		{
			if (KEYx->msg_button.msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
			{
				//---单击操作，不马上返回键值，判断是不是双击
				KEYx->msg_button.msg_pin_scan_record = KEYx->msg_button.msg_f_time_tick();
				//---下一状态
				KEYx->msg_button.msg_pin_scan_step = 5;
			}
			else
			{
				//---判断是否超过时间间隔
				if (TIME_SPAN(KEYx->msg_button.msg_f_time_tick(),
					KEYx->msg_button.msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_FOUR)
				{
					//---按键有效
					KEYx->msg_button.msg_pin_scan_active = ACTIVE_STATE_ENABLE;
					//---返回有效按键状态为双击
					KEYx->msg_button.msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
					//---双击操作
					KEYx->msg_button.msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_FOUR;
					//---返回状态0，等待新的有效按键
					KEYx->msg_button.msg_pin_scan_step = 0;
					//---执行四击操作
#if (MODULE_LOG_KEY_BUTTON>0)
					LOG_VA_ARGS("按键:四击\r\n");
#endif
				}
			}
			break;
		}
		//---校验五击
		case 5:
		{
			if (KEYx->msg_button.msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
			{
				//---单击操作，不马上返回键值，判断是不是双击
				KEYx->msg_button.msg_pin_scan_record = KEYx->msg_button.msg_f_time_tick();
				//---下一状态
				KEYx->msg_button.msg_pin_scan_step = 6;
			}
			else
			{
				//---判断是否超过时间间隔
				if (TIME_SPAN(KEYx->msg_button.msg_f_time_tick(),
					KEYx->msg_button.msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_FIVR)
				{
					//---按键有效
					KEYx->msg_button.msg_pin_scan_active = ACTIVE_STATE_ENABLE;
					//---返回有效按键状态为双击
					KEYx->msg_button.msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
					//---双击操作
					KEYx->msg_button.msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_FIVE;
					//---返回状态0，等待新的有效按键
					KEYx->msg_button.msg_pin_scan_step = 0;
					//---执行五击操作
#if (MODULE_LOG_KEY_BUTTON>0)
					LOG_VA_ARGS("按键:五击\r\n");
#endif
				}
			}
			break;
		}
		//---校验六击
		case 6:
		{
			if (KEYx->msg_button.msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
			{
				//---单击操作，不马上返回键值，判断是不是双击
				KEYx->msg_button.msg_pin_scan_record = KEYx->msg_button.msg_f_time_tick();
				//---下一状态
				KEYx->msg_button.msg_pin_scan_step = 7;
			}
			else
			{
				//---判断是否超过时间间隔
				if (TIME_SPAN(KEYx->msg_button.msg_f_time_tick(),
					KEYx->msg_button.msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_SIX)
				{
					//---按键有效
					KEYx->msg_button.msg_pin_scan_active = ACTIVE_STATE_ENABLE;
					//---返回有效按键状态为双击
					KEYx->msg_button.msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
					//---双击操作
					KEYx->msg_button.msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_SIX;
					//---返回状态0，等待新的有效按键
					KEYx->msg_button.msg_pin_scan_step = 0;
					//---执行六击操作
#if (MODULE_LOG_KEY_BUTTON>0)
					LOG_VA_ARGS("按键:六击\r\n");
#endif
				}
			}
			break;
		}
		//---校验七击
		case 7:
		{
			if (KEYx->msg_button.msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
			{
				//---单击操作，不马上返回键值，判断是不是双击
				KEYx->msg_button.msg_pin_scan_record = KEYx->msg_button.msg_f_time_tick();
				//---下一状态
				KEYx->msg_button.msg_pin_scan_step = 8;
			}
			else
			{
				//---判断是否超过时间间隔
				if (TIME_SPAN(KEYx->msg_button.msg_f_time_tick(),
					KEYx->msg_button.msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_SEVEN)
				{
					//---按键有效
					KEYx->msg_button.msg_pin_scan_active = ACTIVE_STATE_ENABLE;
					//---返回有效按键状态为双击
					KEYx->msg_button.msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
					//---双击操作
					KEYx->msg_button.msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_SEVEN;
					//---返回状态0，等待新的有效按键
					KEYx->msg_button.msg_pin_scan_step = 0;
					//---执行七击操作
#if (MODULE_LOG_KEY_BUTTON>0)
					LOG_VA_ARGS("按键:七击\r\n");
#endif
				}
			}
			break;
		}
		//---校验八击
		case 8:
		{
			if (KEYx->msg_button.msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
			{
				//---单击操作，不马上返回键值，判断是不是双击
				KEYx->msg_button.msg_pin_scan_record = KEYx->msg_button.msg_f_time_tick();
				//---下一状态
				KEYx->msg_button.msg_pin_scan_step = 9;
			}
			else
			{
				//---判断是否超过时间间隔
				if (TIME_SPAN(KEYx->msg_button.msg_f_time_tick(),
					KEYx->msg_button.msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_EIGHT)
				{
					//---按键有效
					KEYx->msg_button.msg_pin_scan_active = ACTIVE_STATE_ENABLE;
					//---返回有效按键状态为双击
					KEYx->msg_button.msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
					//---双击操作
					KEYx->msg_button.msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_EIGHT;
					//---返回状态0，等待新的有效按键
					KEYx->msg_button.msg_pin_scan_step = 0;
					//---执行八击操作
#if (MODULE_LOG_KEY_BUTTON>0)
					LOG_VA_ARGS("按键:八击\r\n");
#endif
				}
			}
			break;
		}
		//---校验九击
		case 9:
		{
			if (KEYx->msg_button.msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
			{
				//---单击操作，不马上返回键值，判断是不是双击
				KEYx->msg_button.msg_pin_scan_record = KEYx->msg_button.msg_f_time_tick();
				//---下一状态
				KEYx->msg_button.msg_pin_scan_step = 10;
			}
			else
			{
				//---判断是否超过时间间隔
				if (TIME_SPAN(KEYx->msg_button.msg_f_time_tick(),
					KEYx->msg_button.msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_NINE)
				{
					//---按键有效
					KEYx->msg_button.msg_pin_scan_active = ACTIVE_STATE_ENABLE;
					//---返回有效按键状态为双击
					KEYx->msg_button.msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
					//---双击操作
					KEYx->msg_button.msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_NINE;
					//---返回状态0，等待新的有效按键
					KEYx->msg_button.msg_pin_scan_step = 0;
					//---执行九击操作
#if (MODULE_LOG_KEY_BUTTON>0)
					LOG_VA_ARGS("按键:九击\r\n");
#endif
				}
			}
			break;
		}
		//---校验十击
		case 10:
		{
			if (KEYx->msg_button.msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
			{
				//---单击操作，不马上返回键值，判断是不是双击
				KEYx->msg_button.msg_pin_scan_record = KEYx->msg_button.msg_f_time_tick();
				//---下一状态
				KEYx->msg_button.msg_pin_scan_step = 11;
			}
			else
			{
				//---判断是否超过时间间隔
				if (TIME_SPAN(KEYx->msg_button.msg_f_time_tick(),
					KEYx->msg_button.msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_TEN)
				{
					//---按键有效
					KEYx->msg_button.msg_pin_scan_active = ACTIVE_STATE_ENABLE;
					//---返回有效按键状态为双击
					KEYx->msg_button.msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
					//---双击操作
					KEYx->msg_button.msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_TEN;
					//---返回状态0，等待新的有效按键
					KEYx->msg_button.msg_pin_scan_step = 0;
					//---执行十击操作
#if (MODULE_LOG_KEY_BUTTON>0)
					LOG_VA_ARGS("按键:十击\r\n");
#endif
				}
			}
			break;
		}
		//---结束
		case 11:
		default:
		{	
			//---单击操作，不马上返回键值，判断是不是双击
			KEYx->msg_button.msg_pin_scan_record = KEYx->msg_button.msg_f_time_tick();
			//---返回有效按键状态为无效
			KEYx->msg_button.msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
			//---双击操作
			KEYx->msg_button.msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
			//---按键有效
			KEYx->msg_button.msg_pin_scan_active = ACTIVE_STATE_DISABLE;
			//---返回状态0，等待新的有效按键
			KEYx->msg_button.msg_pin_scan_step = 0;
			//---执行按键无效操作
			break;
		}
	}
	//---检验按键有效，判断是否使能中断
	if (KEYx->msg_button.msg_pin_scan_active == ACTIVE_STATE_ENABLE)
	{
		//---重新启动按键
		key_start_one(KEYx, 0);
	}
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t key_scan_two(KEY_HandleType* KEYx)
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
uint8_t key_scan_three(KEY_HandleType* KEYx)
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
uint8_t key_time_tick_init(KEY_HandleType* KEYx, uint32_t(*func_time_tick)(void))
{
#if (KEY_BUTTON_MAX_NUM>1)
	
#else
	//---注册滴答函数
	(func_time_tick != NULL) ?
		(KEYx->msg_button.msg_f_time_tick = func_time_tick) :
		(KEYx->msg_button.msg_f_time_tick = sys_tick_task_get_tick);
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t key_init(KEY_HandleType* KEYx, uint32_t(*func_time_tick)(void))
{
	if ((KEYx != NULL) && (KEYx == KEY_TASK_ONE))
	{
		return key_init_one(KEYx, func_time_tick);
	}
	if ((KEYx != NULL) && (KEYx == KEY_TASK_TWO))
	{
		return key_init_two(KEYx, func_time_tick);
	}
	if ((KEYx != NULL) && (KEYx ==KEY_TASK_THREE))
	{
		return key_init_three(KEYx, func_time_tick);
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
uint8_t key_scan(KEY_HandleType* KEYx)
{
	if ((KEYx != NULL) && (KEYx == KEY_TASK_ONE))
	{
		return key_scan_one(KEYx);
	}
	if ((KEYx != NULL) && (KEYx == KEY_TASK_TWO))
	{
		return key_scan_two(KEYx);
	}
	if ((KEYx != NULL) && (KEYx == KEY_TASK_THREE))
	{
		return key_scan_three(KEYx);
	}
	return ERROR_2;
}
