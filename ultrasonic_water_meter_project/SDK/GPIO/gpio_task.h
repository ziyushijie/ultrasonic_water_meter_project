#ifndef GPIO_TASK_H_
#define GPIO_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "gpio_lib.h"
	
	//===º¯Êý¶¨Òå
	void gpio_task_init(uint32_t(*func_time_tick)(void));
	void gpio_task_time_tick_init(uint32_t(*func_time_tick)(void));
	void gpio_task_pin_mode_input(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_task_pin_mode_output(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_task_pin_mode_pull_up_set(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_task_pin_mode_pull_up_reset(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_task_pin_mode_input_normal(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_task_pin_mode_input_ttl(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_task_pin_mode_output_normal(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_task_pin_mode_output_od(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_task_pin_mode_digital(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_task_pin_mode_analog(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_task_pin_mode_ior_set(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_task_pin_mode_ior_reset(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_task_pin_set(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_task_set(GPIO_HandleType* gpiox);
	void gpio_task_pin_reset(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_task_reset(GPIO_HandleType* gpiox);
	void gpio_task_pin_toggle(GPIO_TypeDef* gpiox, uint32_t pin);
	void gpio_task_toggle(GPIO_HandleType* gpiox);
	uint32_t gpio_task_pin_read(GPIO_TypeDef* gpiox, uint32_t pin);
	uint32_t gpio_task_read(GPIO_HandleType* gpiox);
	void gpio_task_set_wait_time(GPIO_HandleType* gpiox, uint32_t waittime);
	void gpio_task_reset_wait_time(GPIO_HandleType* gpiox, uint32_t waittime);
	void gpio_task_toggle_wait_time(GPIO_HandleType* gpiox, uint32_t waittime);
	uint8_t gpio_task_read_level_wait_time(GPIO_HandleType* gpiox, uint8_t highlevel, uint32_t waittime);
	
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* gpiox_TASK_H_ */
