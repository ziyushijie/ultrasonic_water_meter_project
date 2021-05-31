#ifndef KEY_CFG_H_
#define KEY_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	
	#include "complier_lib.h"
	#include "sys_tick_task.h"
	#include "hw_config.h"
	#include "gpio_task.h"

	//===定义结构体
	typedef struct _KEY_PRESS_HandleType			KEY_PRESS_HandleType;
	//===定义指针结构体
	typedef struct _KEY_PRESS_HandleType			* pKEY_PRESS_HandleType;

	//===结构体变量
	struct _KEY_PRESS_HandleType
	{
		uint32_t	msg_pin_level_record;																			//---键值计时
		uint32_t	msg_pin_click_record;																			//---按键集中计时
		uint8_t(*msg_f_pin_level)(void);																			//---键值
		uint32_t(*msg_f_time_tick)(void);																			//---时间节拍
	};

	//===定义结构体
	typedef struct _KEY_HandleType			KEY_HandleType;
	//===定义指针结构体
	typedef struct _KEY_HandleType			* pKEY_HandleType;
	//===结构体变量
	struct _KEY_HandleType
	{
#if (KEY_BUTTON_MAX_NUM>1)
		KEY_PRESS_HandleType msg_button[KEY_BUTTON_MAX_NUM];
#else
		KEY_PRESS_HandleType msg_button;
#endif
	};

	#define KEY_TASK_ONE						p_key_one
	#define KEY_TASK_TWO						0
	#define KEY_TASK_THREE						0

	//===外部调用接口
	extern KEY_HandleType						g_key_one;
	extern pKEY_HandleType						p_key_one;

	//===函数定义
	uint8_t key_it_irq_one(KEY_HandleType *KEYx);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* KEY_CFG_H_ */