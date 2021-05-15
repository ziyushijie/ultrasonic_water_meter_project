#ifndef MS1022_CFG_H_
#define MS1022_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	
	#include "complier_lib.h"
	#include "gpio_task.h"
	#include "delay_task.h"
	#include "sys_tick_task.h"
	#include "hw_config.h"
	#include "spi_task.h"

	//===最大等待时间
	#define MS1022_WAIT_FLAG_MAX_TIME					(100/MS1022_MIN_PULSE_WIDTH)
	#define MS1022_WAIT_IDLE_MAX_TIME					(200/MS1022_MIN_PULSE_WIDTH)
	//===数据缓存区大小
	#define MS1022_DATA_BUFFER_MAX_SIZE					5

	//===读地址
	#define MS1022_READ_ADDR_MASK						0xB0
	//===写地址
	#define MS1022_SEND_ADDR_MASK						0x80
	//===读取ID信息
	#define MS1022_READ_ID								0xB7
	//===读取PWIST,脉冲宽度的测量比值
	#define MS1022_READ_PW1ST							0xB8
	//===读取状态寄存器器
	#define MS1022_READ_STATE							0xB4
	//===通信测试功能
	#define MS1022_COMM_TEST							0xB5

	//===定义结构体
	typedef struct _MS1022_HandleType					MS1022_HandleType;
	//===定义指针结构体
	typedef	struct _MS1022_HandleType					*pMS1022_HandleType;
	//===结构定义
//#pragma pack
	struct _MS1022_HandleType
	{
		SPI_HandleType  msg_spix;																						//---使用的spi接口
		GPIO_HandleType	msg_gpio_rst;																					//---MOSI

		vltuint8_t msg_int_flag;																						//---中断标识信息
		vltuint8_t msg_send_data_buffer[MS1022_DATA_BUFFER_MAX_SIZE];													//---发送数据缓存区
		vltuint8_t msg_read_data_buffer[MS1022_DATA_BUFFER_MAX_SIZE];													//---接收数据缓存区
		
		void(*msg_f_delay_ms)(uint32_t delay);																			//---延时参数
		uint32_t(*msg_f_time_tick)(void);																				//---用于超时计数
	};
//#pragma unpack

	#define MS1022_TASK_ONE							p_ms1022_one
	#define MS1022_TASK_TWO							0
	#define MS1022_TASK_THREE						0

	//===外部调用接口
	extern MS1022_HandleType						g_ms1022_one;
	extern pMS1022_HandleType						p_ms1022_one;
	
	//===函数定义
	uint8_t ms1022_spi_time_tick_init(MS1022_HandleType* MS1022x, uint32_t(*func_time_tick)(void));
	uint8_t ms1022_spi_init(MS1022_HandleType* MS1022x, void(*func_delay_us)(uint32_t us),
		void(*func_delay_ms)(uint32_t ms), uint32_t(*func_time_tick)(void), uint8_t is_hw);
	uint8_t ms1022_spi_rst(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_int_flag_set(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_int_flag_clear(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_int_flag_wait(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_mhw_it_irq_handle(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_read_reg(MS1022_HandleType* MS1022x, uint8_t index);
	uint8_t ms1022_spi_send_reg(MS1022_HandleType* MS1022x, uint8_t index, uint32_t val);
	uint8_t ms1022_spi_send_cmd(MS1022_HandleType* MS1022x, uint8_t cmd);
	uint8_t ms1022_spi_read_reg_state(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_read_reg_pw1st(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_comm_test(MS1022_HandleType* MS1022x);
				  
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* MS1022_CFG_H_ */