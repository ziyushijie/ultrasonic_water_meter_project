#include "lcd_lib.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_lib_time_tick_init(LCD_HandleType* LCDx, uint32_t(*func_time_tick)(void))
{
	return lcd_segment_time_tick_init(LCDx, func_time_tick);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_lib_init(LCD_HandleType* LCDx, uint32_t(*func_time_tick)(void))
{
	return lcd_segment_init(LCDx, func_time_tick);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_lib_enable(LCD_HandleType* LCDx)
{
	return lcd_segment_enable(LCDx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_lib_disable(LCD_HandleType* LCDx)
{
	return lcd_segment_disable(LCDx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_lib_clear(LCD_HandleType* LCDx)
{
	return lcd_segment_clear(LCDx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_lib_show_all(LCD_HandleType* LCDx)
{
	return lcd_segment_show_all(LCDx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_lib_text_title_on(LCD_HandleType* LCDx,uint16_t text)
{
	return lcd_segment_text_title_on(LCDx, text);
}


///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_lib_unit_title_on(LCD_HandleType* LCDx, uint16_t unit)
{
	return lcd_segment_unit_title_on(LCDx, unit);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_lib_decimal_point(LCD_HandleType* LCDx, uint16_t index, uint8_t isshow)
{
	return lcd_segment_decimal_point(LCDx, index, isshow);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_lib_data_on(LCD_HandleType* LCDx, uint16_t index, char dat)
{
	return lcd_segment_data_on(LCDx, index, dat);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_lib_data_off(LCD_HandleType* LCDx, uint16_t index)
{
	return lcd_segment_data_off(LCDx, index);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_lib_test_enter(LCD_HandleType* LCDx)
{
	return lcd_segment_test_enter(LCDx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_lib_test_exit(LCD_HandleType* LCDx)
{
	return lcd_segment_test_exit(LCDx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_lib_show_integer(LCD_HandleType* LCDx, uint32_t dat, uint8_t isfill)
{
	return lcd_segment_show_integer(LCDx, dat,isfill);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_lib_show_float(LCD_HandleType* LCDx, float dat, uint8_t pnum)
{
	return lcd_segment_show_float(LCDx, dat,pnum);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_lib_show_diff_temperature(LCD_HandleType* LCDx, float temperature, uint8_t positive, uint8_t istestmode)
{
	return lcd_segment_show_diff_temperature(LCDx, temperature, positive, istestmode);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_lib_show_temperature(LCD_HandleType* LCDx, float temperature, uint8_t isin, uint8_t istestmode)
{
	return lcd_segment_show_temperature(LCDx, temperature, isin, istestmode);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_lib_show_diff_time(LCD_HandleType* LCDx, float time, uint8_t istestmode)
{
	return lcd_segment_show_diff_time(LCDx, time, istestmode);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_lib_show_time(LCD_HandleType* LCDx, float time, uint8_t isup, uint8_t istestmode)
{
	return lcd_segment_show_time(LCDx, time, isup, istestmode);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_lib_show_flow_volume(LCD_HandleType* LCDx, float flowvolume, uint8_t istestmode)
{
	return lcd_segment_show_flow_volume(LCDx, flowvolume, istestmode);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_lib_show_flow_speed(LCD_HandleType* LCDx, float flowspeed, uint8_t istestmode)
{
	return lcd_segment_show_flow_speed(LCDx, flowspeed, istestmode);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_lib_show_date(LCD_HandleType* LCDx, RTC_TimeType* rtcx) 
{
	return lcd_segment_show_date(LCDx, rtcx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_lib_show_rtc(LCD_HandleType* LCDx, RTC_TimeType *rtcx)
{
	return lcd_segment_show_rtc(LCDx, rtcx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_lib_show_acc_rtc(LCD_HandleType* LCDx, uint32_t accrtc)
{
	return lcd_segment_show_acc_rtc(LCDx, accrtc);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_lib_show_power(LCD_HandleType* LCDx, float power, uint8_t istestmode)
{
	return lcd_segment_show_power(LCDx, power,istestmode);
}
