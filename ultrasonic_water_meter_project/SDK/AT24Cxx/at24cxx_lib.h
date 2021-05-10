#ifndef AT24CXX_LIB_H_
#define AT24CXX_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "at24cxx_cfg.h"
		
	//===º¯Êý¶¨Òå
	void at24cxx_lib_i2c_time_tick_init(AT24CXX_HandleType* AT24Cx, uint32_t(*func_time_tick)(void));
	uint8_t at24cxx_lib_i2c_init(AT24CXX_HandleType *AT24Cx,
		void(*func_delay_us)(uint32_t delay),
		void(*func_delay_ms)(uint32_t delay),
		uint32_t(*func_time_tick)(void), uint8_t is_hw_i2c);
	uint8_t at24cxx_lib_i2c_deinit(AT24CXX_HandleType *AT24Cx);
	uint8_t at24cxx_lib_sw_i2c_send_single_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t buffer);
	uint8_t at24cxx_lib_sw_i2c_send_page_byte(AT24CXX_HandleType *AT24Cx, uint16_t page_addr, uint8_t *buffer, uint16_t length);
	uint8_t at24cxx_lib_sw_i2c_read_single_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer);
	uint8_t at24cxx_lib_sw_i2c_read_page_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer, uint16_t length);

	uint8_t at24cxx_lib_i2c_send_single_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t buffer);
	uint8_t at24cxx_lib_i2c_send_page_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer, uint16_t length);
	uint8_t at24cxx_lib_i2c_send_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer, uint16_t length);
	uint8_t at24cxx_lib_i2c_read_single_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer);
	uint8_t at24cxx_lib_i2c_read_page_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer, uint16_t length);
	uint8_t at24cxx_lib_i2c_read_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer, uint16_t length);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* AT24CXX_LIB_H_ */