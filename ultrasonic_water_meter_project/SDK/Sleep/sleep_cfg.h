#ifndef SLEEP_CFG_H_
#define SLEEP_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "hw_config.h"
	#include "gpio_task.h"
	#include "sys_tick_task.h"

	//===唤醒方式
	#define SLEEP_WAKEUP_NONE			0x00			//---无唤醒
	#define SLEEP_WAKEUP_KEY			0x01			//---按键唤醒
	#define SLEEP_WAKEUP_MBUS_UART		0x02			//---MBUS协议唤醒
	#define SLEEP_WAKEUP_IRDA_UART		0x03			//---IRDA协议唤醒
	#define SLEEP_WAKEUP_WDT			0x04			//---看门狗唤醒
	#define SLEEP_WAKEUP_RTC			0x05			//---RT固定周期唤醒

	//===定义结构体
	typedef struct _SLEEP_HandleType	SLEEP_HandleType;
	//===定义指针结构体
	typedef struct _SLEEP_HandleType	* pSLEEP_HandleType;

	//===结构体变量
	struct _SLEEP_HandleType
	{
		vltuint8_t msg_mode;									//---休眠模式，0-- - 运行模式；1-- - 休眠模式
		vltuint8_t msg_wakeup;									//---唤醒模式:0，无休眠，1-- - 按键中断；2-- - 串口中断
		uint32_t   msg_wakeup_record;							//---唤醒时间
		uint32_t(*msg_f_time_tick)(void);						//---时间节拍
	};
	
	//===函数定义
	uint8_t sleep_init(uint32_t(*func_time_tick)(void));
	uint8_t sleep_get(void);
	uint8_t sleep_enter(void);
	uint8_t sleep_exit(void);
	uint8_t sleep_wakeup_get(void);
	uint8_t sleep_wakeup_set(uint8_t wakeup);
	uint8_t sleep_wakeup_record_set(uint32_t wakeup_record);
	uint32_t sleep_wakeup_record_get(void);
	uint8_t sleep_wakeup_exit(uint8_t wakeup);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* SLEEP_CFG_H_ */