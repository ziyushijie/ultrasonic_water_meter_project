#ifndef AT24CXX_CFG_H_
#define AT24CXX_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	
	#include "complier_lib.h"
	#include "gpio_task.h"
	#include "delay_task.h"
	#include "i2c_task.h"
	#include "hw_config.h"

	//===支持的系列型号
	#define AT24C01										0																//---16PX8B		---16页，每页8字节
	#define AT24C02										1																//---32PX8B		---32页，每页8字节
	#define AT24C04										2																//---32PX16B	---32页，每页16字节
	#define AT24C08										3																//---64PX16B	---64页，每页16字节
	#define AT24C16										4																//---128PX16B	---128页，每页16字节
	#define AT24C32										5																//---128PX32B	---128页，每页32字节
	#define AT24C64										6																//---256PX32B	---256页，每页32字节
	#define AT24C128									7																//---256PX64B	---256页，每页64字节
	#define AT24C256									8																//---512PX64B	---512页，每页64字节
	#define AT24C512									9																//---512PX128B	---512页，每页128字节
	//===定义AT24Cxx的每页直接最大值
	#define	AT24CXX_PAGE_BYTE_SIZE_MAX					128
	//===设备通讯地址
	#define AT24CXX_WADDR								0xA0															//---设备的写地址
	#define AT24CXX_RADDR								0xA1															//---设备的读地址
	//===最大超时时间，避免看门狗复位
	#define AT24CXX_WAIT_MAX_TIME						(800/AT24CXX_MIN_PULSE_WIDTH)
	//===多函数调用的时候，操作状态最多保留的时间，单位ms
	#define AT24CXX_TASK_WAIT_MAX_TIME					(100/AT24CXX_MIN_PULSE_WIDTH)
	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////配置宏定义---结束////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////结构体定义---开始//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	//===结构体定义
	typedef struct _AT24CXX_HandleType					AT24CXX_HandleType;
	//===指针结构体定义
	typedef struct _AT24CXX_HandleType					*pAT24CXX_HandleType;
	//===AT24Cxx的数据结构体
	struct _AT24CXX_HandleType
	{
		I2C_HandleType	msg_i2cx;																						//---使用的I2C

		uint8_t		msg_type;																							//---使用的设备
		uint8_t		msg_page_byte;																						//---每页字节数
		uint16_t	msg_page_num;																						//---页数
#ifndef AT24CXX_ENABLE_DRAM
		uint8_t		msg_page_byte_buffer[AT24CXX_PAGE_BYTE_SIZE_MAX + 1];												//---定义缓存区
#else
		uint8_t		*msg_page_byte_buffer;																				//---指向缓存区的指针
#endif
		void(*msg_f_delay_ms)(uint32_t delay);																			//---毫秒延时函数,编程结束后需要等待5ms
	};

	//===定义的任务函数
	#define AT24CXX_TASK_ONE						p_at24cxx_one
	#define AT24CXX_TASK_TWO						0
	#define AT24CXX_TASK_THREE						0

	//===外部调用接口
	extern AT24CXX_HandleType						g_at24cxx_one;
	extern pAT24CXX_HandleType						p_at24cxx_one;

	//===函数定义
	uint8_t at24cxx_i2c_init_one(AT24CXX_HandleType *AT24Cx);
	uint8_t at24cxx_i2c_init_two(AT24CXX_HandleType *AT24Cx);
	uint8_t at24cxx_i2c_init_three(AT24CXX_HandleType *AT24Cx);
	void at24cxx_i2c_time_tick_init(AT24CXX_HandleType* AT24Cx, uint32_t(*func_time_tick)(void));
	uint8_t at24cxx_i2c_init(AT24CXX_HandleType *AT24Cx,
		void(*func_delay_us)(uint32_t delay),
		void(*func_delay_ms)(uint32_t delay),
		uint32_t(*func_time_tick)(void), uint8_t is_hw_i2c);
	uint8_t at24cxx_i2c_deinit(AT24CXX_HandleType *AT24Cx);
	uint8_t at24cxx_sw_i2c_send_single_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t buffer);
	uint8_t at24cxx_sw_i2c_send_page_byte(AT24CXX_HandleType *AT24Cx, uint16_t page_addr, uint8_t *buffer, uint16_t length);
	uint8_t at24cxx_sw_i2c_read_single_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer);
	uint8_t at24cxx_sw_i2c_read_page_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer, uint16_t length);

	uint8_t at24cxx_i2c_send_single_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t buffer);
	uint8_t at24cxx_i2c_send_page_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer, uint16_t length);
	uint8_t at24cxx_i2c_send_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer, uint16_t length);
	uint8_t at24cxx_i2c_read_single_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer);
	uint8_t at24cxx_i2c_read_page_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer, uint16_t length);
	uint8_t at24cxx_i2c_read_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer, uint16_t length);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* AT24CXX_CFG_H_ */