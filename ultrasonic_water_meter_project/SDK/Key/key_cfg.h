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

	//===按键状态
	#define KEY_BUTTON_PRESS_STATE_CLICK_NONE			0															//---按键无动作
	#define KEY_BUTTON_PRESS_STATE_CLICK_ONE			1															//---按键单击
	#define KEY_BUTTON_PRESS_STATE_CLICK_TWO			2															//---按键双击
	#define KEY_BUTTON_PRESS_STATE_CLICK_THREE			3															//---按键三击
	#define KEY_BUTTON_PRESS_STATE_CLICK_FOUR			4															//---按键四击
	#define KEY_BUTTON_PRESS_STATE_CLICK_FIVE			5															//---按键五击
	#define KEY_BUTTON_PRESS_STATE_CLICK_SIX			6															//---按键六击
	#define KEY_BUTTON_PRESS_STATE_CLICK_SEVEN			7															//---按键七击
	#define KEY_BUTTON_PRESS_STATE_CLICK_EIGHT			8															//---按键八击
	#define KEY_BUTTON_PRESS_STATE_CLICK_NINE			9															//---按键九击
	#define KEY_BUTTON_PRESS_STATE_CLICK_TEN			10															//---按键十击
	#define KEY_BUTTON_PRESS_STATE_CLICK_LONG			11															//---按键长击
	#define KEY_BUTTON_PRESS_STATE_CLICK_LONG_LONG		12															//---按键超长击
	#define KEY_BUTTON_PRESS_STATE_CLICK_MAX_NUM		KEY_BUTTON_PRESS_STATE_CLICK_MAX_NUM

	//===按键稳定时间
	#define KEY_BUTTON_ACTIVE_TIME_STABLE				(20/KEY_BUTTON_MIN_PULSE_WIDTH)								//---按键消抖稳定时间
	#define KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE			(350)														//---单击时间
	#define KEY_BUTTON_ACTIVE_TIME_REPEAT_TWO			(KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE+100)						//---双击时间
	#define KEY_BUTTON_ACTIVE_TIME_REPEAT_THREE			(KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE+200)						//---三击时间
	#define KEY_BUTTON_ACTIVE_TIME_REPEAT_FOUR			(KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE+300)						//---四击时间
	#define KEY_BUTTON_ACTIVE_TIME_REPEAT_FIVR			(KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE+400)						//---五击时间
	#define KEY_BUTTON_ACTIVE_TIME_REPEAT_SIX			(KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE+500)						//---六击时间
	#define KEY_BUTTON_ACTIVE_TIME_REPEAT_SEVEN			(KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE+600)						//---七击时间
	#define KEY_BUTTON_ACTIVE_TIME_REPEAT_EIGHT			(KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE+700)						//---八击时间
	#define KEY_BUTTON_ACTIVE_TIME_REPEAT_NINE			(KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE+800)						//---九击时间
	#define KEY_BUTTON_ACTIVE_TIME_REPEAT_TEN			(KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE+900)						//---十击时间
	#define KEY_BUTTON_ACTIVE_TIME_REPEAT_LONG			(KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE+1000)					//---长按时间	
	#define KEY_BUTTON_ACTIVE_TIME_REPEAT_LONG_LONG		(KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE+2000)					//---超长按时间
	#define KEY_BUTTON_ACTIVE_TIME_REPEAT_ERROR			(KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE+20000)					//---按键错误
	//===定义结构体
	typedef struct _KEY_PRESS_HandleType			KEY_PRESS_HandleType;
	//===定义指针结构体
	typedef struct _KEY_PRESS_HandleType			* pKEY_PRESS_HandleType;

	//===结构体变量
	struct _KEY_PRESS_HandleType
	{
		uint8_t		msg_pin_index;																					//---端口序号

		uint8_t     msg_pin_level_active;
		uint8_t		msg_pin_level_value;																			//---按键值
		uint8_t		msg_pin_level_step;																				//---按键步序
		uint8_t     msg_pin_level_state;																			//---按键状态

		uint8_t     msg_pin_scan_active;																			//---扫描激活
		uint8_t		msg_pin_scan_step;																				//---按键步序
		uint8_t     msg_pin_scan_state;																				//---按键状态

		uint32_t	msg_pin_level_record;																			//---键值计时
		uint32_t	msg_pin_scan_record;																			//---按键集中计时
		uint8_t(*msg_f_pin_level)(uint8_t);																			//---键值
		uint32_t(*msg_f_time_tick)(void);																			//---时间节拍
	};

	//===定义结构体
	typedef struct _KEY_HandleType			KEY_HandleType;
	//===定义指针结构体
	typedef struct _KEY_HandleType			* pKEY_HandleType;
	//===结构体变量
	struct _KEY_HandleType
	{
		vltuint8_t msg_active;																						//---按键扫描激活
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
	uint8_t key_pin_level_one(uint8_t index);
	uint8_t key_it_irq_handle_one(KEY_HandleType *KEYx, uint8_t index);

	uint8_t key_time_tick_init(KEY_HandleType* KEYx, uint32_t(*func_time_tick)(void));
	uint8_t key_init(KEY_HandleType* KEYx, uint32_t(*func_time_tick)(void));
	uint8_t key_scan(KEY_HandleType* KEYx);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* KEY_CFG_H_ */