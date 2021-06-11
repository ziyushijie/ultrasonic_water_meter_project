#include "rtc_cfg.h"

//===ȫ�ֱ���
RTC_HandleType		g_rtc_one = {0};
pRTC_HandleType		p_rtc_one=&g_rtc_one;

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����RTCʱ��
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t rtc_hw_set_rtctime_one(RTC_HandleType* RTCx, RTC_TimeType Timex)
{
	uint8_t _return = OK_0;
	//---�ṩ�ɶ�ȡʵʱʱ�ӵ�����ʱ��
	RTCWEN = 1U;
	//---ֹͣ�����������ü�������ֵΪ��дģʽ
	RTCC1 |= _01_RTC_COUNTER_PAUSE;

	delay_task_nop(350);
	//---�жϼ�������д��־
	if (0U == RWST)
	{
		_return = ERROR_1;
	}
	else
	{
		//---ͬ������
		memcpy(&RTCx->msg_rtcx, &Timex, sizeof(RTC_TimeType));
		//---ͬ��ʱ��
		SEC = dec_to_bcd(RTCx->msg_rtcx.msg_second);
		MIN = dec_to_bcd(RTCx->msg_rtcx.msg_minute);
		HOUR = dec_to_bcd(RTCx->msg_rtcx.msg_hour);
		WEEK = dec_to_bcd(RTCx->msg_rtcx.msg_week);
		DAY = dec_to_bcd(RTCx->msg_rtcx.msg_day);
		MONTH = dec_to_bcd(RTCx->msg_rtcx.msg_month);
		//---��ȡ�����Ϣ
		YEAR = dec_to_bcd(RTCx->msg_rtcx.msg_year);
		//---���м�����
		RTCC1 &= (uint8_t)~_01_RTC_COUNTER_PAUSE;
		delay_task_nop(350);
		if (1U == RWST)
		{
			_return = ERROR_2;
		}
	}
	//---ֹͣ�ṩ�ɶ�ȡʵʱʱ�ӵ�����ʱ��
	RTCWEN = 0U;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t rtc_hw_set_rtctime_two(RTC_HandleType* RTCx, RTC_TimeType Timex)
{
	return ERROR_4;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t rtc_hw_set_rtctime_three(RTC_HandleType* RTCx, RTC_TimeType Timex)
{
	return ERROR_4;
}


///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ȡRTCʱ��
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t rtc_hw_get_rtctime_one(RTC_HandleType* RTCx)
{
	uint8_t _return = OK_0;
	//---�ṩ�ɶ�ȡʵʱʱ�ӵ�����ʱ��
	RTCWEN = 1U;    /* enables input clock supply */
	//---ֹͣ�����������ü�������ֵΪ��дģʽ
	RTCC1 |= _01_RTC_COUNTER_PAUSE;

	delay_task_nop(350);
	//---�жϼ�������д��־
	if (0U == RWST)
	{
		_return = ERROR_1;
	}
	else
	{
		//---RTC������BCD�룬��Ҫװ��Ϊʮ��������
		RTCx->msg_rtcx.msg_second = bcd_to_dec(SEC);
		RTCx->msg_rtcx.msg_minute = bcd_to_dec(MIN);
		RTCx->msg_rtcx.msg_hour = bcd_to_dec(HOUR);
		RTCx->msg_rtcx.msg_week = bcd_to_dec(WEEK);
		RTCx->msg_rtcx.msg_day = bcd_to_dec(DAY);
		RTCx->msg_rtcx.msg_month = bcd_to_dec(MONTH);
		//---��ȡ�����Ϣ
		_return = bcd_to_dec(YEAR);
		//---У���Ƿ������͵ı仯
		if (RTCx->msg_rtcx.msg_year > _return)
		{
			RTCx->msg_rtcx.msg_century += 1;
		}
		//---ͬ������Ϣ
		RTCx->msg_rtcx.msg_year = _return;
		//---����20xx����Ϣ
		RTCx->msg_rtcx.msg_years = (RTCx->msg_rtcx.msg_century - 1) * 100;
		RTCx->msg_rtcx.msg_years += RTCx->msg_rtcx.msg_year;
		//---�ָ�����ֵ
		_return = OK_0;
		//---���м�����
		RTCC1 &= (uint8_t)~_01_RTC_COUNTER_PAUSE;
		delay_task_nop(350);
		if (1U == RWST)
		{
			_return = ERROR_2;
		}
	}
	//---ֹͣ�ṩ�ɶ�ȡʵʱʱ�ӵ�����ʱ��
	RTCWEN = 0U;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t rtc_hw_get_rtctime_two(RTC_HandleType* RTCx)
{
	return ERROR_3;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t rtc_hw_get_rtctime_three(RTC_HandleType* RTCx)
{
	return ERROR_3;
}


///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t rtc_hw_init_one(RTC_HandleType *RTCx, uint32_t(*func_time_tick)(void))
{
	//---�ṩ�ɶ�ȡʵʱʱ�ӵ�����ʱ��
	RTCWEN = 1U;  
	//---��ʹ��RTC
	RTCE = 0U;     
	//---��ʹ���ж�
	RTCMK = 1U;    
	//---����жϱ�ʶ
	RTCIF = 0U;    
	//---����RTC
	RTCC0 = _00_RTC_RTC1HZ_DISABLE | _08_RTC_24HOUR_SYSTEM | _02_RTC_INTRTC_CLOCK_1;
	//---�����ж����ȼ�
	RTCPR1 = 0U;
	RTCPR0 = 1U;
	//---����жϱ�־λ
	RTCIF = 0U;
	//---ʹ���ж�
	RTCMK = 0U;
	//---ʹ��RTC
	RTCE = 1U;
	//---�ȴ�������Ч
	delay_task_nop(5); 
	//---ֹͣ�ṩ�ɶ�ȡʵʱʱ�ӵ�����ʱ��
	RTCWEN = 0U;    /* stops input clock supply */

	//---ע��δ���
	(func_time_tick != NULL) ?
		(RTCx->msg_f_time_tick = func_time_tick) :
		(RTCx->msg_f_time_tick = sys_tick_task_get_tick);

	//---ȡ��������---������---__DATE__===Jul 03 2018
	//---һ��
	if (__DATE__[2] == 'n')
	{
		if (__DATE__[0] == 'a')
		{
			//---һ��
			RTCx->msg_rtcx.msg_month = 1;
		}
		else
		{
			//---����
			RTCx->msg_rtcx.msg_month = 6;
		}
	}
	//--����
	else if (__DATE__[2] == 'b')
	{
		RTCx->msg_rtcx.msg_month = 2;
	}
	else if (__DATE__[2] == 'r')
	{
		if (__DATE__[0] == 'M')
		{
			//---����
			RTCx->msg_rtcx.msg_month = 3;
		}
		else
		{
			//---����
			RTCx->msg_rtcx.msg_month = 4;
		}
	}
	else if (__DATE__[2] == 'y')
	{
		//---����
		RTCx->msg_rtcx.msg_month = 5;
	}
	else if (__DATE__[2] == 'l')
	{
		//---����
		RTCx->msg_rtcx.msg_month = 7;
	}
	else if (__DATE__[2] == 'g')
	{
		//---����
		RTCx->msg_rtcx.msg_month = 8;
	}
	else if (__DATE__[2] == 'p')
	{
		//---����
		RTCx->msg_rtcx.msg_month = 9;
	}
	else if (__DATE__[2] == 't')
	{
		//---ʮ��
		RTCx->msg_rtcx.msg_month = 10;
	}
	else if (__DATE__[2] == 'v')
	{
		//---ʮһ��
		RTCx->msg_rtcx.msg_month = 11;
	}
	else if (__DATE__[2] == 'c')
	{
		//---ʮ����
		RTCx->msg_rtcx.msg_month = 12;
	}
	else
	{
		//---Ĭ����һ��
		RTCx->msg_rtcx.msg_month = 1;
	}
	//---��
	if (__DATE__[9] == 0x20)
	{
		RTCx->msg_rtcx.msg_year = (uint8_t)((__DATE__[10] - '0'));
	}
	else
	{
		RTCx->msg_rtcx.msg_year = (uint8_t)((__DATE__[9] - '0') * 10 + (__DATE__[10] - '0'));
	}
	//---��
	if (__DATE__[4] == 0x20)
	{
		RTCx->msg_rtcx.msg_day = (uint8_t)(__DATE__[5] - '0');
	}
	else
	{
		RTCx->msg_rtcx.msg_day = (uint8_t)((__DATE__[4] - '0') * 10 + (__DATE__[5] - '0'));
	}
	//---����
	if (__DATE__[7] == 0x20)
	{
		RTCx->msg_rtcx.msg_century = (uint8_t)((__DATE__[8] - '0') + 1);
	}
	else
	{
		RTCx->msg_rtcx.msg_century = (uint8_t)((__DATE__[7] - '0') * 10 + (__DATE__[8] - '0') + 1);
	}

	//---��������Ϣ
	RTCx->msg_rtcx.msg_years = (RTCx->msg_rtcx.msg_century - 1);
	RTCx->msg_rtcx.msg_years *= 100;
	RTCx->msg_rtcx.msg_years += RTCx->msg_rtcx.msg_year;
	//---��������
	RTCx->msg_rtcx.msg_week = calc_rtc_week(&(RTCx->msg_rtcx));

	//---ȡ��������---ʱ����---__TIME__=06:17:05
	//---ʱ
	if (__TIME__[0] == 0x20)
	{
		RTCx->msg_rtcx.msg_hour = (uint8_t)(__TIME__[1] - '0');
	}
	else
	{
		RTCx->msg_rtcx.msg_hour = (uint8_t)((__TIME__[0] - '0') * 10 + (__TIME__[1] - '0'));
	}

	////---��Сʱת��Ϊ0ʱ��ʱ��
	//if (RTCx->msg_rtcx.msg_hour >= 8)
	//{
	//	RTCx->msg_rtcx.msg_hour -= 8;
	//}
	//else
	//{
	//	RTCx->msg_rtcx.msg_hour += 15;
	//}

	//---��
	if (__TIME__[3] == 0x20)
	{
		RTCx->msg_rtcx.msg_minute = (uint8_t)(__TIME__[4] - '0');
	}
	else
	{
		RTCx->msg_rtcx.msg_minute = (uint8_t)((__TIME__[3] - '0') * 10 + (__TIME__[4] - '0'));
	}
	//---��
	if (__TIME__[6] == 0x20)
	{
		RTCx->msg_rtcx.msg_second = (uint8_t)(__TIME__[7] - '0');
	}
	else
	{
		RTCx->msg_rtcx.msg_second = (uint8_t)((__TIME__[6] - '0') * 10 + (__TIME__[7] - '0'));
	}
	////---ʱ�䳬ǰ
	//RTCx->msg_rtcx.msg_minute += 2;
	//if (RTCx->msg_rtcx.msg_minute > 60)
	//{
	//	RTCx->msg_rtcx.msg_minute -= 60;
	//	RTCx->msg_rtcx.msg_hour += 1;
	//}
	RTCx->msg_rtcx.msg_format_24h = 1;
	//---����ʱ��
	rtc_hw_set_rtctime_one(RTCx,RTCx->msg_rtcx);
	//---��ȡʱ��
	rtc_hw_get_rtctime_one(RTCx);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t rtc_hw_init_two(RTC_HandleType* RTCx, uint32_t(*func_time_tick)(void))
{
	return ERROR_1;
}


///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t rtc_hw_init_three(RTC_HandleType* RTCx, uint32_t(*func_time_tick)(void))
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: RTC�жϴ�����
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t rtc_it_irq_handle_one(RTC_HandleType* RTCx)
{
	//---�����жϴ�����
	if (1U == WAFG)
	{
		RTCWEN = 1U;
		//---����жϱ�־λ
		RTCC1 &= (uint8_t)~_10_RTC_ALARM_MATCH;       
		RTCWEN = 0U;
		//---�����жϴ�����
	}

	//---�̶������жϺ���
	if (1U == RIFG)
	{
		RTCWEN = 1U;
		//---����жϱ�־λ
		RTCC1 &= (uint8_t)~_08_RTC_INTC_GENERATE_FLAG;    
		RTCWEN = 0U;
		//---�̶������жϴ�����

		RTCx->msg_rtc_change = 1;
	}

	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
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
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
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
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
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
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t rtc_time_tick_init(RTC_HandleType* RTCx, uint32_t(*func_time_tick)(void))
{
	//---ע��δ���
	(func_time_tick != NULL) ?
		(RTCx->msg_f_time_tick = func_time_tick) :
		(RTCx->msg_f_time_tick = sys_tick_task_get_tick);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
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
//////��		��:
//////��		��: ����RTCʱ��
//////�����	��:
//////�����	��:
//////˵		��:
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
//////��		��:
//////��		��: ��ȡRTCʱ��
//////�����	��:
//////�����	��:
//////˵		��:
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
