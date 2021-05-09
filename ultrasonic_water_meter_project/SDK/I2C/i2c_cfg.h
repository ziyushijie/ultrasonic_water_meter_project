#ifndef I2C_CFG_H_
#define I2C_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	
	#include "complier_lib.h"
	#include "sys_tick_task.h"
	#include "gpio_task.h"
	#include "delay_task.h"
	#include "hw_config.h"

	//===定义结构体
	typedef struct _I2C_HandleType					I2C_HandleType;
	//===定义指针结构体
	typedef	struct _I2C_HandleType					*pI2C_HandleType;
	//===结构定义
	struct _I2C_HandleType
	{
		GPIO_HandleType		msg_gpio_scl;																				//---SCL
		GPIO_HandleType		msg_gpio_sda;																				//---SDA
		uint8_t				msg_hw_mode;																				//---工作模式，默认是软件模拟---0，硬件模式---1
		uint16_t			msg_pluse_width;																			//---脉冲宽度，软件模拟使用
		uint16_t			msg_addr;																					//---设备的地址
		void(*msg_f_delay_us)(uint32_t delay);																			//---延时参数
		uint32_t(*msg_f_time_tick)(void);																				//---用于超时计数
	};

	//===函数定义
	uint8_t i2c_msw_init(I2C_HandleType *I2Cx, void(*func_delay_us)(uint32_t delay), uint32_t(*func_time_tick)(void));
	uint8_t i2c_msw_deinit(I2C_HandleType *I2Cx);
	uint8_t i2c_msw_start(I2C_HandleType *I2Cx);
	uint8_t i2c_msw_stop(I2C_HandleType *I2Cx);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* I2C_CFG_H_ */