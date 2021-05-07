#ifndef LOG_CFG_H_
#define LOG_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "hw_config.h"
	
//	#define LOG_VA_ARGS(fmt,...)				log_printf(fmt,##__VA_ARGS__)											//---可变参数的重写printf函数
//	#define LOG_ARRAY(buffer,length,new_line)	log_printf_array(buffer,length,new_line)								//---数组模式的重写printf函数
//	#define LOG_STRING(buffer,length,new_line)	log_printf_string(buffer,length,new_line)	
	
	void LOG_VA_ARGS(char*fmt,...);
	void log_printf(char* fmt, ...);
	void log_printf_array(uint8_t* buffer, uint16_t length,uint8_t is_new_line);
	void log_printf_string(uint8_t* buffer, uint16_t length,uint8_t is_new_line);
	
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* LOG_CFG_H_ */