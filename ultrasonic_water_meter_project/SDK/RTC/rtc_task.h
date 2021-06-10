#ifndef RTC_TASK_H_
#define RTC_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "rtc_lib.h"

	//===º¯Êý¶¨Òå
	uint8_t rtc_task_it_irq_handle_one(RTC_HandleType* RTCx);

	uint8_t rtc_task_time_tick_init(RTC_HandleType* RTCx, uint32_t(*func_time_tick)(void));
	uint8_t rtc_task_init(RTC_HandleType* RTCx, uint32_t(*func_time_tick)(void), uint8_t ishw);
	uint8_t rtc_task_set_rtctime(RTC_HandleType* RTCx, RTC_TimeType Timex, uint8_t ishw);
	uint8_t rtc_task_get_rtctime(RTC_HandleType* RTCx, uint8_t ishw);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* RTC_TASK_H_ */