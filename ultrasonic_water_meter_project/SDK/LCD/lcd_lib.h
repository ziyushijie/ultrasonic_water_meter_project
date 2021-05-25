#ifndef LCD_LIB_H_
#define LCD_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "lcd_cfg.h"

	//===º¯Êý¶¨Òå
	uint8_t lcd_segment_lib_init(void);
	uint8_t lcd_segment_lib_enable(void);
	uint8_t lcd_segment_lib_disable(void);
	uint8_t lcd_segment_lib_clear(void);
	uint8_t lcd_segment_lib_show_all(void);
	uint8_t lcd_segment_lib_text_title_on(uint16_t text);
	uint8_t lcd_segment_lib_unit_title_on(uint16_t unit);
	uint8_t lcd_segment_lib_decimal_point(uint16_t index, uint8_t isshow);
	uint8_t lcd_segment_lib_data_on(uint16_t index, char dat);
	uint8_t lcd_segment_lib_data_off(uint16_t index);
	uint8_t lcd_segment_lib_test_enter(void);
	uint8_t lcd_segment_lib_test_exit(void);
	uint8_t lcd_segment_lib_show_integer(uint32_t dat);
	uint8_t lcd_segment_lib_show_float(float dat, uint8_t pnum);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* LCD_LIB_H_ */