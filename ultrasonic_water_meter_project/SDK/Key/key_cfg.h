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

	//===����״̬
	#define KEY_BUTTON_PRESS_STATE_CLICK_NONE			0															//---�����޶���
	#define KEY_BUTTON_PRESS_STATE_CLICK_ONE			1															//---��������
	#define KEY_BUTTON_PRESS_STATE_CLICK_TWO			2															//---����˫��
	#define KEY_BUTTON_PRESS_STATE_CLICK_THREE			3															//---��������
	#define KEY_BUTTON_PRESS_STATE_CLICK_FOUR			4															//---�����Ļ�
	#define KEY_BUTTON_PRESS_STATE_CLICK_FIVE			5															//---�������
	#define KEY_BUTTON_PRESS_STATE_CLICK_SIX			6															//---��������
	#define KEY_BUTTON_PRESS_STATE_CLICK_SEVEN			7															//---�����߻�
	#define KEY_BUTTON_PRESS_STATE_CLICK_EIGHT			8															//---�����˻�
	#define KEY_BUTTON_PRESS_STATE_CLICK_NINE			9															//---�����Ż�
	#define KEY_BUTTON_PRESS_STATE_CLICK_TEN			10															//---����ʮ��
	#define KEY_BUTTON_PRESS_STATE_CLICK_LONG			11															//---��������
	#define KEY_BUTTON_PRESS_STATE_CLICK_LONG_LONG		12															//---����������
	#define KEY_BUTTON_PRESS_STATE_CLICK_MAX_NUM		KEY_BUTTON_PRESS_STATE_CLICK_MAX_NUM

	//===�����ȶ�ʱ��
	#define KEY_BUTTON_ACTIVE_TIME_STABLE				(20/KEY_BUTTON_MIN_PULSE_WIDTH)								//---���������ȶ�ʱ��
	#define KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE			(350)														//---����ʱ��
	#define KEY_BUTTON_ACTIVE_TIME_REPEAT_TWO			(KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE+100)						//---˫��ʱ��
	#define KEY_BUTTON_ACTIVE_TIME_REPEAT_THREE			(KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE+200)						//---����ʱ��
	#define KEY_BUTTON_ACTIVE_TIME_REPEAT_FOUR			(KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE+300)						//---�Ļ�ʱ��
	#define KEY_BUTTON_ACTIVE_TIME_REPEAT_FIVR			(KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE+400)						//---���ʱ��
	#define KEY_BUTTON_ACTIVE_TIME_REPEAT_SIX			(KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE+500)						//---����ʱ��
	#define KEY_BUTTON_ACTIVE_TIME_REPEAT_SEVEN			(KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE+600)						//---�߻�ʱ��
	#define KEY_BUTTON_ACTIVE_TIME_REPEAT_EIGHT			(KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE+700)						//---�˻�ʱ��
	#define KEY_BUTTON_ACTIVE_TIME_REPEAT_NINE			(KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE+800)						//---�Ż�ʱ��
	#define KEY_BUTTON_ACTIVE_TIME_REPEAT_TEN			(KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE+900)						//---ʮ��ʱ��
	#define KEY_BUTTON_ACTIVE_TIME_REPEAT_LONG			(KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE+1000)					//---����ʱ��	
	#define KEY_BUTTON_ACTIVE_TIME_REPEAT_LONG_LONG		(KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE+2000)					//---������ʱ��
	#define KEY_BUTTON_ACTIVE_TIME_REPEAT_ERROR			(KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE+20000)					//---��������
	//===����ṹ��
	typedef struct _KEY_PRESS_HandleType			KEY_PRESS_HandleType;
	//===����ָ��ṹ��
	typedef struct _KEY_PRESS_HandleType			* pKEY_PRESS_HandleType;

	//===�ṹ�����
	struct _KEY_PRESS_HandleType
	{
		uint8_t		msg_pin_index;																					//---�˿����

		uint8_t     msg_pin_level_active;
		uint8_t		msg_pin_level_value;																			//---����ֵ
		uint8_t		msg_pin_level_step;																				//---��������
		uint8_t     msg_pin_level_state;																			//---����״̬

		uint8_t     msg_pin_scan_active;																			//---ɨ�輤��
		uint8_t		msg_pin_scan_step;																				//---��������
		uint8_t     msg_pin_scan_state;																				//---����״̬

		uint32_t	msg_pin_level_record;																			//---��ֵ��ʱ
		uint32_t	msg_pin_scan_record;																			//---�������м�ʱ
		uint8_t(*msg_f_pin_level)(uint8_t);																			//---��ֵ
		uint32_t(*msg_f_time_tick)(void);																			//---ʱ�����
	};

	//===����ṹ��
	typedef struct _KEY_HandleType			KEY_HandleType;
	//===����ָ��ṹ��
	typedef struct _KEY_HandleType			* pKEY_HandleType;
	//===�ṹ�����
	struct _KEY_HandleType
	{
		vltuint8_t msg_active;																						//---����ɨ�輤��
#if (KEY_BUTTON_MAX_NUM>1)
		KEY_PRESS_HandleType msg_button[KEY_BUTTON_MAX_NUM];
#else
		KEY_PRESS_HandleType msg_button;
#endif
	};

	#define KEY_TASK_ONE						p_key_one
	#define KEY_TASK_TWO						0
	#define KEY_TASK_THREE						0

	//===�ⲿ���ýӿ�
	extern KEY_HandleType						g_key_one;
	extern pKEY_HandleType						p_key_one;

	//===��������
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