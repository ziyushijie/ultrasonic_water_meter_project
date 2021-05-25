#ifndef LCD_TASK_H_
#define LCD_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "lcd_lib.h"
	
	//===º¯Êı¶¨Òå
	uint8_t lcd_segment_task_init(void);
	uint8_t lcd_segment_task_enable(void);
	uint8_t lcd_segment_task_disable(void);
	uint8_t lcd_segment_task_clear(void);
	uint8_t lcd_segment_task_show_all(void);
	uint8_t lcd_segment_task_text_title_on(uint16_t text);
	uint8_t lcd_segment_task_unit_title_on(uint16_t unit);
	uint8_t lcd_segment_task_decimal_point(uint16_t index, uint8_t isshow);
	uint8_t lcd_segment_task_data_on(uint16_t index, char dat);
	uint8_t lcd_segment_task_data_off(uint16_t index);
	uint8_t lcd_segment_task_test_enter(void);
	uint8_t lcd_segment_task_test_exit(void);
	uint8_t lcd_segment_task_show_integer(uint32_t dat);
	uint8_t lcd_segment_task_show_float(float dat, uint8_t pnum);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* LCD_TASK_H_ */