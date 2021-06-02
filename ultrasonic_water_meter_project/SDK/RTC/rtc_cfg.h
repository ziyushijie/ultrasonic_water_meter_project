#ifndef RTC_CFG_H_
#define RTC_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	
	#include "complier_lib.h"
	#include "sys_tick_task.h"
	#include "hw_config.h"

	//===�ṹ�嶨��
	typedef struct _RTC_HandleType				RTC_HandleType;
	//===����ָ��ṹ��
	typedef struct _RTC_HandleType				* pRTC_HandleType;
	//===�������RTCʱ��
	struct _RTC_HandleType
	{
		RTC_TimeType	msg_rtcx;																						//---ʹ�õ�RTC
		uint32_t(*msg_f_time_tick)(void);																				//---���ڳ�ʱ����
	};

	#define RTC_TASK_ONE						p_rtc_one
	#define RTC_TASK_TWO						0
	#define RTC_TASK_THREE						0

	//===�ⲿ���ýӿ�
	extern RTC_HandleType						g_rtc_one;
	extern pRTC_HandleType						p_rtc_one;

	//===��������
	uint8_t rtc_time_tick_init(RTC_HandleType* RTCx, uint32_t(*func_time_tick)(void));
	uint8_t rtc_init(RTC_HandleType* RTCx, uint32_t(*func_time_tick)(void), uint8_t ishw);


	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* RTC_CFG_H_ */