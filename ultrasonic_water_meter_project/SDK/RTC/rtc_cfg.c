#include "rtc_cfg.h"

//===全局变量
RTC_HandleType		g_rtc_one = {0};
pRTC_HandleType		p_rtc_one=&g_rtc_one;

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 设置RTC时间
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t rtc_hw_set_rtctime_one(RTC_HandleType* RTCx, RTC_TimeType Timex)
{
	uint8_t _return = OK_0;
	//---提供可读取实时时钟的输入时钟
	RTCWEN = 1U;
	//---停止计数器，设置计数器的值为读写模式
	RTCC1 |= _01_RTC_COUNTER_PAUSE;

	delay_task_nop(350);
	//---判断计数器读写标志
	if (0U == RWST)
	{
		_return = ERROR_1;
	}
	else
	{
		//---同步拷贝
		memcpy(&RTCx->msg_rtcx, &Timex, sizeof(RTC_TimeType));
		//---同步时间
		SEC = dec_to_bcd(RTCx->msg_rtcx.msg_second);
		MIN = dec_to_bcd(RTCx->msg_rtcx.msg_minute);
		HOUR = dec_to_bcd(RTCx->msg_rtcx.msg_hour);
		WEEK = dec_to_bcd(RTCx->msg_rtcx.msg_week);
		DAY = dec_to_bcd(RTCx->msg_rtcx.msg_day);
		MONTH = dec_to_bcd(RTCx->msg_rtcx.msg_month);
		//---获取年的信息
		YEAR = dec_to_bcd(RTCx->msg_rtcx.msg_year);
		//---运行计数器
		RTCC1 &= (uint8_t)~_01_RTC_COUNTER_PAUSE;
		delay_task_nop(350);
		if (1U == RWST)
		{
			_return = ERROR_2;
		}
	}
	//---停止提供可读取实时时钟的输入时钟
	RTCWEN = 0U;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t rtc_hw_set_rtctime_two(RTC_HandleType* RTCx, RTC_TimeType Timex)
{
	return ERROR_4;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t rtc_hw_set_rtctime_three(RTC_HandleType* RTCx, RTC_TimeType Timex)
{
	return ERROR_4;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 获取RTC时间
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t rtc_hw_get_rtctime_one(RTC_HandleType* RTCx)
{
	uint8_t _return = OK_0;
	//---提供可读取实时时钟的输入时钟
	RTCWEN = 1U;    /* enables input clock supply */
	//---停止计数器，设置计数器的值为读写模式
	RTCC1 |= _01_RTC_COUNTER_PAUSE;

	delay_task_nop(350);
	//---判断计数器读写标志
	if (0U == RWST)
	{
		_return = ERROR_1;
	}
	else
	{
		//---RTC编码是BCD码，需要装换为十进制数据
		RTCx->msg_rtcx.msg_second = bcd_to_dec(SEC);
		RTCx->msg_rtcx.msg_minute = bcd_to_dec(MIN);
		RTCx->msg_rtcx.msg_hour = bcd_to_dec(HOUR);
		RTCx->msg_rtcx.msg_week = bcd_to_dec(WEEK);
		RTCx->msg_rtcx.msg_day = bcd_to_dec(DAY);
		RTCx->msg_rtcx.msg_month = bcd_to_dec(MONTH);
		//---获取年的信息
		_return = bcd_to_dec(YEAR);
		//---校验是否发生世纪的变化
		if (RTCx->msg_rtcx.msg_year > _return)
		{
			RTCx->msg_rtcx.msg_century += 1;
		}
		//---同步年信息
		RTCx->msg_rtcx.msg_year = _return;
		//---计算20xx年信息
		RTCx->msg_rtcx.msg_years = (RTCx->msg_rtcx.msg_century - 1) * 100;
		RTCx->msg_rtcx.msg_years += RTCx->msg_rtcx.msg_year;
		//---恢复返回值
		_return = OK_0;
		//---运行计数器
		RTCC1 &= (uint8_t)~_01_RTC_COUNTER_PAUSE;
		delay_task_nop(350);
		if (1U == RWST)
		{
			_return = ERROR_2;
		}
	}
	//---停止提供可读取实时时钟的输入时钟
	RTCWEN = 0U;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t rtc_hw_get_rtctime_two(RTC_HandleType* RTCx)
{
	return ERROR_3;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t rtc_hw_get_rtctime_three(RTC_HandleType* RTCx)
{
	return ERROR_3;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t rtc_hw_init_one(RTC_HandleType *RTCx, uint32_t(*func_time_tick)(void))
{
	//---提供可读取实时时钟的输入时钟
	RTCWEN = 1U;  
	//---不使能RTC
	RTCE = 0U;     
	//---不使能中断
	RTCMK = 1U;    
	//---清除中断标识
	RTCIF = 0U;    
	//---配置RTC
	RTCC0 = _00_RTC_RTC1HZ_DISABLE | _08_RTC_24HOUR_SYSTEM | _02_RTC_INTRTC_CLOCK_1;
	//---配置中断优先级
	RTCPR1 = 0U;
	RTCPR0 = 1U;
	//---清楚中断标志位
	RTCIF = 0U;
	//---使能中断
	RTCMK = 0U;
	//---使能RTC
	RTCE = 1U;
	//---等待配置生效
	delay_task_nop(5); 
	//---停止提供可读取实时时钟的输入时钟
	RTCWEN = 0U;    /* stops input clock supply */

	//---注册滴答函数
	(func_time_tick != NULL) ?
		(RTCx->msg_f_time_tick = func_time_tick) :
		(RTCx->msg_f_time_tick = sys_tick_task_get_tick);

	rtc_hw_get_rtctime_one(RTCx);

	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t rtc_hw_init_two(RTC_HandleType* RTCx, uint32_t(*func_time_tick)(void))
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
uint8_t rtc_hw_init_three(RTC_HandleType* RTCx, uint32_t(*func_time_tick)(void))
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: RTC中断处理函数
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t rtc_it_irq_handle_one(RTC_HandleType* RTCx)
{
	//---闹钟中断处理函数
	if (1U == WAFG)
	{
		RTCWEN = 1U;
		//---清楚中断标志位
		RTCC1 &= (uint8_t)~_10_RTC_ALARM_MATCH;       
		RTCWEN = 0U;
		//---闹钟中断处理函数
	}

	//---固定周期中断函数
	if (1U == RIFG)
	{
		RTCWEN = 1U;
		//---清楚中断标志位
		RTCC1 &= (uint8_t)~_08_RTC_INTC_GENERATE_FLAG;    
		RTCWEN = 0U;
		//---固定周期中断处理函数

		RTCx->msg_rtc_change = 1;
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
uint8_t rtc_hw_init(RTC_HandleType* RTCx, uint32_t(*func_time_tick)(void))
{
	if ((RTCx != NULL) && (RTCx == RTC_TASK_ONE))
	{
		return rtc_hw_init_one(RTCx, func_time_tick);
	}
	if ((RTCx != NULL) && (RTCx == RTC_TASK_TWO))
	{
		return rtc_hw_init_two(RTCx, func_time_tick);
	}
	if ((RTCx != NULL) && (RTCx == RTC_TASK_THREE))
	{
		return rtc_hw_init_three(RTCx, func_time_tick);
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
uint8_t rtc_hw_set_rtctime(RTC_HandleType* RTCx, RTC_TimeType Timex)
{
	if ((RTCx != NULL) && (RTCx == RTC_TASK_ONE))
	{
		return rtc_hw_set_rtctime_one(RTCx, Timex);
	}
	if ((RTCx != NULL) && (RTCx == RTC_TASK_TWO))
	{
		return rtc_hw_set_rtctime_two(RTCx, Timex);
	}
	if ((RTCx != NULL) && (RTCx == RTC_TASK_THREE))
	{
		return rtc_hw_set_rtctime_three(RTCx, Timex);
	}
	return ERROR_4;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t rtc_hw_get_rtctime(RTC_HandleType* RTCx)
{
	if ((RTCx != NULL) && (RTCx == RTC_TASK_ONE))
	{
		return rtc_hw_get_rtctime_one(RTCx);
	}
	if ((RTCx != NULL) && (RTCx == RTC_TASK_TWO))
	{
		return rtc_hw_get_rtctime_two(RTCx);
	}
	if ((RTCx != NULL) && (RTCx == RTC_TASK_THREE))
	{
		return rtc_hw_get_rtctime_three(RTCx);
	}
	return ERROR_4;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t rtc_time_tick_init(RTC_HandleType* RTCx, uint32_t(*func_time_tick)(void))
{
	//---注册滴答函数
	(func_time_tick != NULL) ?
		(RTCx->msg_f_time_tick = func_time_tick) :
		(RTCx->msg_f_time_tick = sys_tick_task_get_tick);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t rtc_init(RTC_HandleType* RTCx, uint32_t(*func_time_tick)(void),uint8_t ishw)
{
	if (ishw!=0)
	{
		return rtc_hw_init(RTCx, func_time_tick);
	}
	else
	{
		return ERROR_3;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 设置RTC时间
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t rtc_set_rtctime(RTC_HandleType* RTCx, RTC_TimeType Timex, uint8_t ishw)
{
	if (ishw != 0)
	{
		return rtc_hw_set_rtctime(RTCx, Timex);
	}
	else
	{
		return ERROR_3;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 获取RTC时间
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t rtc_get_rtctime(RTC_HandleType* RTCx, uint8_t ishw)
{
	if (ishw != 0)
	{
		return rtc_hw_get_rtctime(RTCx);
	}
	else
	{
		return ERROR_3;
	}
}
