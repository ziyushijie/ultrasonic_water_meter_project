#ifndef GPIO_TASK_H_
#define GPIO_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "gpio_lib.h"
	
	//===��������
	void gpio_task_init(uint32_t(*func_time_tick)(void));
	void gpio_task_time_tick_init(uint32_t(*func_time_tick)(void));
	void gpio_task_pin_mode_input(GPIO_TypeDef* gpio, uint32_t pin);
	void gpio_task_pin_mode_output(GPIO_TypeDef* gpio, uint32_t pin);
	void gpio_task_pin_mode_pull_up_set(GPIO_TypeDef* gpio, uint32_t pin);
	void gpio_task_pin_mode_pull_up_reset(GPIO_TypeDef* gpio, uint32_t pin);
	void gpio_task_pin_mode_input_normal(GPIO_TypeDef* gpio, uint32_t pin);
	void gpio_task_pin_mode_input_ttl(GPIO_TypeDef* gpio, uint32_t pin);
	void gpio_task_pin_mode_output_normal(GPIO_TypeDef* gpio, uint32_t pin);
	void gpio_task_pin_mode_output_od(GPIO_TypeDef* gpio, uint32_t pin);
	void gpio_task_pin_mode_digital(GPIO_TypeDef* gpio, uint32_t pin);
	void gpio_task_pin_mode_analog(GPIO_TypeDef* gpio, uint32_t pin);
	void gpio_task_pin_mode_ior_set(GPIO_TypeDef* gpio, uint32_t pin);
	void gpio_task_pin_mode_ior_reset(GPIO_TypeDef* gpio, uint32_t pin);
	void gpio_task_pin_set(GPIO_TypeDef* gpio, uint32_t pin);
	void gpio_task_set(GPIO_HandleType* gpio);
	void gpio_task_pin_reset(GPIO_TypeDef* gpio, uint32_t pin);
	void gpio_task_reset(GPIO_HandleType* gpio);
	void gpio_task_pin_toggle(GPIO_TypeDef* gpio, uint32_t pin);
	void gpio_task_toggle(GPIO_HandleType* gpio);
	uint32_t gpio_task_pin_read(GPIO_TypeDef* gpio, uint32_t pin);
	uint32_t gpio_task_read(GPIO_HandleType* gpio);
	void gpio_task_set_wait_time(GPIO_HandleType* gpio, uint32_t waittime);
	void gpio_task_reset_wait_time(GPIO_HandleType* gpio, uint32_t waittime);
	void gpio_task_toggle_wait_time(GPIO_HandleType* gpio, uint32_t waittime);
	uint8_t gpio_task_read_level_wait_time(GPIO_HandleType* gpio, uint8_t highlevel, uint32_t waittime);
	
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* GPIO_TASK_H_ */