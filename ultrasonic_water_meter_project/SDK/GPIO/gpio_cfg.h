#ifndef GPIO_CFG_H_
#define GPIO_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "sys_tick_task.h"
	#include "hw_config.h"
	#include "log_cfg.h"

	//===端口置位
	#define PIN_OUT_1(	gpio, index )						gpio_pin_set( gpio, index )	
	#define GPIO_OUT_1(	gpio)								gpio_set( gpio )	

	//===端口取反
	#define PIN_OUT_0(	gpio, index )						gpio_pin_reset( gpio, index )	
	#define GPIO_OUT_0( gpio )								gpio_reset( gpio )	

	//===端口取反
	#define PIN_OUT_C(	gpio, index )						gpio_pin_toggle( gpio, index )	
	#define GPIO_OUT_C( gpio)								gpio_toggle( gpio )	

	//===读取电平状态
	#define PIN_GET_STATE(	gpio, index )					gpio_pin_read( gpio, index )	
	#define GPIO_GET_STATE( gpio)							gpio_read( gpio )	
			
	//===定义结构体
	typedef struct _GPIO_HandleType							GPIO_HandleType;
	//===指针结构体
	typedef	struct _GPIO_HandleType							*pGPIO_HandleType;
	//===结构体类型
	struct _GPIO_HandleType
	{
		GPIO_TypeDef	*msg_p_port;																					//---端口
		uint32_t		msg_bit;																						//---序号
	};
	
	//===函数定义
	void gpio_init(uint32_t(*func_time_tick)(void));
	void gpio_time_tick_init(uint32_t(*func_time_tick)(void));
	void gpio_pin_mode_input(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_pin_mode_output(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_pin_mode_pull_up_set(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_pin_mode_pull_up_reset(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_pin_mode_input_normal(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_pin_mode_input_ttl(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_pin_mode_output_normal(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_pin_mode_output_od(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_pin_mode_digital(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_pin_mode_analog(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_pin_mode_ior_set(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_pin_mode_ior_reset(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_pin_set(GPIO_TypeDef* gpiox,uint32_t pin);
	void gpio_set(GPIO_HandleType* gpiox);
	void gpio_pin_reset(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_reset(GPIO_HandleType* gpiox);
	void gpio_pin_toggle(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_toggle(GPIO_HandleType* gpiox);
	uint32_t gpio_pin_read(GPIO_TypeDef * gpiox,uint32_t pin);
	uint32_t gpio_read(GPIO_HandleType* gpiox);
	void gpio_set_wait_time(GPIO_HandleType* gpiox, uint32_t waittime);
	void gpio_reset_wait_time(GPIO_HandleType* gpiox, uint32_t waittime);
	void gpio_toggle_wait_time(GPIO_HandleType* gpiox, uint32_t waittime);
	uint8_t gpio_read_level_wait_time(GPIO_HandleType* gpiox, uint8_t highlevel, uint32_t waittime);
	uint8_t gpio_read_level_wait(GPIO_HandleType* gpiox, uint8_t highlevel);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* gpiox_CFG_H_ */