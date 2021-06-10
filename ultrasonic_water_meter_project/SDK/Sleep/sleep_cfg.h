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

	//===���ѷ�ʽ
	#define SLEEP_WAKEUP_NONE			0x00			//---�޻���
	#define SLEEP_WAKEUP_KEY			0x01			//---��������
	#define SLEEP_WAKEUP_MBUS_UART		0x02			//---MBUSЭ�黽��
	#define SLEEP_WAKEUP_IRDA_UART		0x03			//---IRDAЭ�黽��
	#define SLEEP_WAKEUP_WDT			0x04			//---���Ź�����
	#define SLEEP_WAKEUP_RTC			0x05			//---RT�̶����ڻ���

	//===����ṹ��
	typedef struct _SLEEP_HandleType	SLEEP_HandleType;
	//===����ָ��ṹ��
	typedef struct _SLEEP_HandleType	* pSLEEP_HandleType;

	//===�ṹ�����
	struct _SLEEP_HandleType
	{
		vltuint8_t msg_mode;									//---����ģʽ��0-- - ����ģʽ��1-- - ����ģʽ
		vltuint8_t msg_wakeup;									//---����ģʽ:0�������ߣ�1-- - �����жϣ�2-- - �����ж�
		uint32_t   msg_wakeup_record;							//---����ʱ��
		uint32_t(*msg_f_time_tick)(void);						//---ʱ�����
	};
	
	//===��������
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