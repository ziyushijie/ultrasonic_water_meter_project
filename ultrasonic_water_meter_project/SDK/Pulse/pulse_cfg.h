#ifndef PULSE_CFG_H_
#define PULSE_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	
	#include "complier_lib.h"
	#include "sys_tick_task.h"
	#include "hw_config.h"
	#include "gpio_task.h"

	//===���弤���ȶ�ʱ��
	#define PULSE_ACTIVE_TIME_STABLE			(20/PULSE_MIN_PULSE_WIDTH)

	//===����ṹ��
	typedef struct _PULSE_HandleType			PULSE_HandleType;
	//===����ָ��ṹ��
	typedef struct _PULSE_HandleType			* pPULSE_HandleType;
	//===�ṹ�����
	struct _PULSE_HandleType
	{
		vltuint8_t  msg_actice;					//---����״̬

		uint8_t     msg_level_active;			//---�����ƽ
		uint8_t		msg_level_value;			//---��ǰֵ��ƽ
		uint8_t		msg_level_step;				//---��ƽ����
		uint8_t     msg_level_state;			//---��ƽ״̬

		uint16_t    msg_level_count;			//---��ƽ����

		uint32_t	msg_level_record;			//---��ֵ��ʱ
		uint32_t	msg_acticve_record;			//---�����ʱ
		uint8_t(*msg_f_level)(void);			//---��ֵ
		uint32_t(*msg_f_time_tick)(void);		//---ʱ�����

	};

	#define PULSE_TASK_ONE						p_pulse_one
	#define PULSE_TASK_TWO						0
	#define PULSE_TASK_THREE					0

	//===�ⲿ���ýӿ�
	extern PULSE_HandleType						g_pulse_one;
	extern pPULSE_HandleType					p_pulse_one;

	//===��������
	uint8_t pulse_level_one(void);
	uint8_t pulse_it_irq_handle_one(PULSE_HandleType* Pulsex);

	uint8_t pulse_scan(PULSE_HandleType* Pulsex);
	uint8_t pulse_time_tick_init(PULSE_HandleType* Pulsex, uint32_t(*func_time_tick)(void));
	uint8_t pulse_init(PULSE_HandleType* Pulsex, uint32_t(*func_time_tick)(void));
	
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* PULSE_CFG_H_ */