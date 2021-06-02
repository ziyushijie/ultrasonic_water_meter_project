#ifndef COMPLIER_LIB_H_
#define COMPLIER_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_cfg.h"
	//////////////////////////////////////////////////////////////////////////////////////
	
	//===º¯Êý¶¨Òå
	uint8_t  hex_to_bcd(uint8_t hex);
	uint8_t  hex_to_ascii(uint8_t hex);
	uint8_t  ascii_to_hex(uint8_t hex);
	uint8_t  bcd_to_dec(uint8_t bcd);
	uint8_t  dec_to_bcd(uint8_t dec);
	uint8_t  asc_sort_byte(uint8_t *buffer, uint16_t length);
	uint8_t  asc_sort_word(uint16_t *buffer, uint16_t length);
	uint8_t  asc_sort_double_word(uint32_t* buffer, uint16_t length);
	uint8_t  asc_sort_float(float* buffer, uint16_t length);
	uint8_t  desc_sort_byte(uint8_t *buffer, uint16_t length);
	uint8_t  desc_sort_word(uint16_t *buffer, uint16_t length);
	uint8_t  desc_sort_float(float *buffer, uint16_t length);
	uint16_t calc_avg_word_from_index(uint16_t *buffer, uint16_t length, uint16_t index);
	uint16_t calc_avg_word(uint16_t *buffer, uint16_t length);
	uint8_t  calc_avg_byte_from_index(uint8_t *buffer, uint16_t length, uint16_t index);
	uint16_t calc_avg_byte(uint8_t *buffer, uint16_t length);
	float    calc_avg_float(float*buffer, uint16_t length);
	uint32_t calc_avg_double_word_from_index(uint32_t* buffer, uint16_t length, uint16_t index);
	uint8_t  compare_byte_to_byte(uint8_t *p1, uint8_t *p2, uint16_t length);
	uint8_t  compare_byte_to_byte_from_index(uint8_t *p1, uint8_t *p2, uint16_t index, uint16_t length);
	uint8_t  compare_word_to_word(uint16_t *p1, uint16_t *p2, uint16_t length);
	uint8_t  compare_word_to_word_from_index(uint16_t *p1, uint16_t *p2, uint16_t index, uint16_t length);
	uint8_t	 compare_byte(uint8_t* p1, uint8_t buffer, uint16_t length);
	uint8_t  compare_word(uint16_t* p1, uint16_t buffer, uint16_t length);
	uint8_t  compare_double_word(uint32_t* p1, uint32_t buffer, uint16_t length);
	uint8_t  invert_uint8(uint8_t* buffer);
	uint8_t  swap_bit_uint8(uint8_t val);
	uint16_t invert_uint16(uint16_t* buffer);
	uint8_t  my_str_cmp(uint8_t* src, uint8_t* des, uint16_t length);
	uint8_t  my_str_cmp_index(uint8_t* src, uint8_t* des, uint16_t length, uint16_t* index);
 	uint8_t  ascii_to_utf8_byte(uint8_t ascii, uint8_t is_low_case);
	void ascii_to_utf8_array(uint8_t* ascii, uint8_t* utf8, uint16_t length, uint8_t is_low_case);
	char* my_itoa(int val, char* s,uint16_t* length, int radix);
	char* my_str_n_str(const char* src, const char* des, uint32_t length);
	uint8_t calc_rtc_week(RTC_TimeType* RTCx);
	uint16_t calc_rtc_year_day(RTC_TimeType* RTCx);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*COMPLIER_LIB_H */
