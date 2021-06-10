#ifndef RTC_LIB_H_
#define RTC_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////

	#include "rtc_cfg.h"

	//===��������
	uint8_t rtc_lib_it_irq_handle_one(RTC_HandleType* RTCx);

	uint8_t rtc_lib_time_tick_init(RTC_HandleType* RTCx, uint32_t(*func_time_tick)(void));
	uint8_t rtc_lib_init(RTC_HandleType* RTCx, uint32_t(*func_time_tick)(void), uint8_t ishw);
	uint8_t rtc_lib_set_rtctime(RTC_HandleType* RTCx, RTC_TimeType Timex, uint8_t ishw);
	uint8_t rtc_lib_get_rtctime(RTC_HandleType* RTCx, uint8_t ishw);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* RTC_LIB_H_ */