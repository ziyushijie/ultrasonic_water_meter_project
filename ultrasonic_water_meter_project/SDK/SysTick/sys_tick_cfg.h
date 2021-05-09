#ifndef SYS_TICK_CFG_H_
#define SYS_TICK_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "hw_config.h"
	
	//===定义结构体	
	typedef struct _SYS_TICK_HandleType					SYS_TICK_HandleType;
	//===定义指针结构体
	typedef struct _SYS_TICK_HandleType					*pSYS_TICK_HandleType;
	//===结构体定义
	//struct _SYS_TICK_HandleType
	struct _SYS_TICK_HandleType
	{
		vltuint32_t				msg_inc_count;																		//---递加计数器
		vltuint32_t				msg_dec_count;																		//---递减计数器
		vltuint32_t				msg_inc_ovf;																		//---递加计数器溢出
	};

	//===当前计数器寄存器的值
	#define SYS_TICK_REG_VAL							(TCR02)
	//===滴答定时器的加载值
	#define SYS_TICK_REG_LOAD							(TDR02)

	#define SYS_TICK_TASK_ONE						p_sys_tick_one
	#define SYS_TICK_TASK_TWO						0
	#define SYS_TICK_TASK_THREE						0

	//===外部调用接口
	extern SYS_TICK_HandleType						g_sys_tick_one;
	extern pSYS_TICK_HandleType						p_sys_tick_one;

	//===函数定义
	uint8_t sys_tick_init(SYS_TICK_HandleType *systickx);
	void sys_tick_enable(void);
	void sys_tick_disable(void);
	uint8_t sys_tick_it_irq_handle(SYS_TICK_HandleType *systickx);
	uint32_t sys_tick_get_inc_ovf(SYS_TICK_HandleType *systickx);
	uint32_t sys_tick_get_inc_count(SYS_TICK_HandleType *systickx);
	uint32_t sys_tick_get_tick(void);
	uint8_t sys_tick_wait_ms(SYS_TICK_HandleType *systickx, uint32_t ms);
	uint8_t sys_tick_wait_s(SYS_TICK_HandleType *systickx, uint32_t s);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* SYS_TICK_CFG_H_ */