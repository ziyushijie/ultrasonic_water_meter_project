#include "rtc_lib.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t rtc_lib_time_tick_init(RTC_HandleType* RTCx, uint32_t(*func_time_tick)(void))
{
	return rtc_time_tick_init(RTCx, func_time_tick);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t rtc_lib_init(RTC_HandleType* RTCx, uint32_t(*func_time_tick)(void), uint8_t ishw)
{
	return rtc_init(RTCx, func_time_tick, ishw);
}