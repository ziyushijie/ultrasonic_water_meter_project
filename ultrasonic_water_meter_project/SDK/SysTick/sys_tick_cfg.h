#ifndef SYS_TICK_CFG_H_
#define SYS_TICK_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "hw_config.h"
	
	//===����ṹ��	
	typedef struct _SYS_TICK_HandleType					SYS_TICK_HandleType;
	//===����ָ��ṹ��
	typedef struct _SYS_TICK_HandleType					*pSYS_TICK_HandleType;
	//===�ṹ�嶨��
	//struct _SYS_TICK_HandleType
	struct _SYS_TICK_HandleType
	{
		vltuint32_t				msg_inc_count;																		//---�ݼӼ�����
		vltuint32_t				msg_dec_count;																		//---�ݼ�������
		vltuint32_t				msg_inc_ovf;																		//---�ݼӼ��������
	};

	//===��ǰ�������Ĵ�����ֵ
	#define SYS_TICK_REG_VAL							(TCR02)
	//===�δ�ʱ���ļ���ֵ
	#define SYS_TICK_REG_LOAD							(TDR02)

	#define SYS_TICK_TASK_ONE						p_sys_tick_one
	#define SYS_TICK_TASK_TWO						0
	#define SYS_TICK_TASK_THREE						0

	//===�ⲿ���ýӿ�
	extern SYS_TICK_HandleType						g_sys_tick_one;
	extern pSYS_TICK_HandleType						p_sys_tick_one;

	//===��������
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