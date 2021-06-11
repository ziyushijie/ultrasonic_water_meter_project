#ifndef LCD_LIB_H_
#define LCD_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "lcd_cfg.h"

	//===º¯Êý¶¨Òå
	uint8_t lcd_segment_lib_time_tick_init(LCD_HandleType* LCDx, uint32_t(*func_time_tick)(void));
	uint8_t lcd_segment_lib_init(LCD_HandleType* LCDx, uint32_t(*func_time_tick)(void));
	uint8_t lcd_segment_lib_enable(LCD_HandleType* LCDx);
	uint8_t lcd_segment_lib_disable(LCD_HandleType* LCDx);
	uint8_t lcd_segment_lib_clear(LCD_HandleType* LCDx);
	uint8_t lcd_segment_lib_show_all(LCD_HandleType* LCDx);
	uint8_t lcd_segment_lib_text_title_on(LCD_HandleType* LCDx, uint16_t text);
	uint8_t lcd_segment_lib_unit_title_on(LCD_HandleType* LCDx, uint16_t unit);
	uint8_t lcd_segment_lib_decimal_point(LCD_HandleType* LCDx, uint16_t index, uint8_t isshow);
	uint8_t lcd_segment_lib_data_on(LCD_HandleType* LCDx, uint16_t index, char dat);
	uint8_t lcd_segment_lib_data_off(LCD_HandleType* LCDx, uint16_t index);
	uint8_t lcd_segment_lib_test_enter(LCD_HandleType* LCDx);
	uint8_t lcd_segment_lib_test_exit(LCD_HandleType* LCDx);
	uint8_t lcd_segment_lib_show_integer(LCD_HandleType* LCDx, uint32_t dat, uint8_t isfill);
	uint8_t lcd_segment_lib_show_float(LCD_HandleType* LCDx, float dat, uint8_t pnum);

	uint8_t lcd_segment_lib_show_diff_temperature(LCD_HandleType* LCDx, float temperature, uint8_t positive, uint8_t istestmode);
	uint8_t lcd_segment_lib_show_temperature(LCD_HandleType* LCDx, float temperature, uint8_t isin, uint8_t istestmode);
	uint8_t lcd_segment_lib_show_diff_time(LCD_HandleType* LCDx, float time, uint8_t istestmode);
	uint8_t lcd_segment_lib_show_time(LCD_HandleType* LCDx, float time, uint8_t isup, uint8_t istestmode);
	uint8_t lcd_segment_lib_show_flow_volume(LCD_HandleType* LCDx, float flowvolume, uint8_t istestmode);
	uint8_t lcd_segment_lib_show_flow_speed(LCD_HandleType* LCDx, float flowspeed, uint8_t istestmode);
	uint8_t lcd_segment_lib_show_date(LCD_HandleType* LCDx, RTC_TimeType* rtcx);
	uint8_t lcd_segment_lib_show_rtc(LCD_HandleType* LCDx, RTC_TimeType *rtcx);
	uint8_t lcd_segment_lib_show_acc_rtc(LCD_HandleType* LCDx, uint32_t accrtc);
	uint8_t lcd_segment_lib_show_power(LCD_HandleType* LCDx, float power, uint8_t istestmode);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* LCD_LIB_H_ */