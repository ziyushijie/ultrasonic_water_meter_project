#ifndef LCD_CFG_H_
#define LCD_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	
	#include "complier_lib.h"
	#include "sys_tick_task.h"
	#include "hw_config.h"
	#include "gpio_task.h"

	//===26PIN��LCD��PIN��Ӧ�Ķ˿���Ϣ
	//PIN1----COM0
	//PIN2----COM1
	//PIN3----COM2
	//PIN4----COM3
	//PIN5----S0--------SEG0
	//PIN6----S1--------SEG1
	//PIN7----S2--------SEG2
	//PIN8----S3--------SEG3
	//PIN9----S7--------SEG7
	//PIN10---S8--------SEG8
	//PIN11---S11-------SEG11
	//PIN12---S12-------SEG12
	//PIN13---S16-------SEG16
	//PIN14---S17-------SEG17
	//PIN15---S18-------SEG18
	//PIN16---S19-------SEG19
	//PIN17---S20-------SEG20
	//PIN18---S21-------SEG21
	//PIN19---S22-------SEG22
	//PIN20---S23-------SEG23
	//PIN21---S33-------SEG33
	//PIN22---S34-------SEG34
	//PIN23---S35-------SEG35
	//PIN24---S36-------SEG36
	//PIN25---S37-------SEG37
	//PIN26---S38-------SEG38
	
	//===�ı�����
	typedef enum
	{
		TEXT_NONE=0,
		TEXT_ACC ,		//---�ۻ�
		TEXT_HEAT,		//---����
		TEXT_ACC_HEAT,	//---�ۻ�����
		TEXT_COOL,		//---����
		TEXT_ACC_COOL,	//---�ۻ�����
		TEXT_FLOW,		//---����
		TEXT_ACC_FLOW,	//---�ۻ�����
		TEXT_IWT ,		//---��ˮ�¶�
		TEXT_OWT ,		//---��ˮ�¶�
		TEXT_DWT ,		//---�²�
		TEXT_TEST ,		//---�춨ģʽ
		TEXT_ALARM ,	//---����
		TEXT_POWER ,	//---����
		TEXT_ADDR ,		//---��ַ
		TEXT_DATE ,		//---����
		TEXT_RTC,		//---ʱ��
		TEXT_ACC_RTC,	//---�ۻ�ʱ��
		TEXT_BATTERY ,	//---���
	}TEXT_TITTLE;

	//===��Ԫ����
	typedef enum
	{
		UNIT_NONE = 0,
		UNIT_K,		//---��ʾ��λK
		UNIT_C,		//---��ʾ��λ��
		UNIT_KW,	//---��ʾǧ��kW
		UNIT_KW_D,  //---��ʾǧ��kWС�����ĵ�
		UNIT_KWH,   //---��ʾǧ��kW.h
		UNIT_KW_H,  //---��ʾ����kWС������h
		UNIT_MWH,   //---��ʾ����MW.h
		UNIT_GJ,    //---��ʾGJ
		UNIT_MJ,    //---��ʾMJ
		UNIT_GJMJ,  //---��ʾGJMJ
		UNIT_M3,    //---��ʾm3
		UNIT_M3_H,  //---��ʾm3С������h
		UNIT_M3H,   //---��ʾm3/h
	}UNIT_TITTLE;

	//===����ṹ��
	typedef struct _LCD_HandleType			LCD_HandleType;
	//===����ָ��ṹ��
	typedef struct _LCD_HandleType			* pLCD_HandleType;
	//===�ṹ�����
	struct _LCD_HandleType
	{
		uint8_t msg_backlight;					//---��ʾ����
		uint16_t msg_text;						//---��ʾ�ı�
		uint16_t msg_unit;						//---��ʾ��λ
		uint32_t msg_backlight_record;			//---�����¼
		uint32_t(*msg_f_time_tick)(void);		//---ʱ�����
	};

	#define LCD_TASK_ONE						p_lcd_one
	#define LCD_TASK_TWO						0
	#define LCD_TASK_THREE						0

	//===�ⲿ���ýӿ�
	extern LCD_HandleType						g_lcd_one;
	extern pLCD_HandleType						p_lcd_one;
	
	//===��������
	uint8_t lcd_segment_time_tick_init(LCD_HandleType* LCDx, uint32_t(*func_time_tick)(void));
	uint8_t lcd_segment_init(LCD_HandleType *LCDx, uint32_t(*func_time_tick)(void));

	uint8_t lcd_segment_enable_one(LCD_HandleType *LCDx);
	uint8_t lcd_segment_enable_two(LCD_HandleType *LCDx);
	uint8_t lcd_segment_enable_three(LCD_HandleType *LCDx);
	uint8_t lcd_segment_enable(LCD_HandleType *LCDx);
	uint8_t lcd_segment_disable_one(LCD_HandleType *LCDx);
	uint8_t lcd_segment_disable_two(LCD_HandleType *LCDx);
	uint8_t lcd_segment_disable_three(LCD_HandleType *LCDx);
	uint8_t lcd_segment_disable(LCD_HandleType *LCDx);

	uint8_t lcd_segment_clear_one(LCD_HandleType* LCDx);
	uint8_t lcd_segment_clear_two(LCD_HandleType* LCDx);
	uint8_t lcd_segment_clear_three(LCD_HandleType* LCDx);
	uint8_t lcd_segment_clear(LCD_HandleType *LCDx);

	uint8_t lcd_segment_show_all_one(LCD_HandleType* LCDx);
	uint8_t lcd_segment_show_all_two(LCD_HandleType* LCDx);
	uint8_t lcd_segment_show_all_three(LCD_HandleType* LCDx);
	uint8_t lcd_segment_show_all(LCD_HandleType *LCDx);

	uint8_t lcd_segment_text_title_on_one(LCD_HandleType* LCDx, uint16_t text);
	uint8_t lcd_segment_text_title_on_two(LCD_HandleType* LCDx, uint16_t text);
	uint8_t lcd_segment_text_title_on_three(LCD_HandleType* LCDx, uint16_t text);
	uint8_t lcd_segment_text_title_on(LCD_HandleType *LCDx,uint16_t text);

	uint8_t lcd_segment_text_title_off_one(LCD_HandleType* LCDx, uint16_t text);
	uint8_t lcd_segment_text_title_off_two(LCD_HandleType* LCDx, uint16_t text);
	uint8_t lcd_segment_text_title_off_three(LCD_HandleType* LCDx, uint16_t text);
	uint8_t lcd_segment_text_title_off(LCD_HandleType *LCDx, uint16_t text);

	uint8_t lcd_segment_unit_title_on_one(LCD_HandleType* LCDx, uint16_t unit);
	uint8_t lcd_segment_unit_title_on_two(LCD_HandleType* LCDx, uint16_t unit);
	uint8_t lcd_segment_unit_title_on_three(LCD_HandleType* LCDx, uint16_t unit);
	uint8_t lcd_segment_unit_title_on(LCD_HandleType *LCDx, uint16_t unit);

	uint8_t lcd_segment_unit_title_off_one(LCD_HandleType* LCDx, uint16_t unit);
	uint8_t lcd_segment_unit_title_off_two(LCD_HandleType* LCDx, uint16_t unit);
	uint8_t lcd_segment_unit_title_off_three(LCD_HandleType* LCDx, uint16_t unit);
	uint8_t lcd_segment_unit_title_off(LCD_HandleType* LCDx, uint16_t unit);

	uint8_t lcd_segment_decimal_point_one(LCD_HandleType* LCDx, uint16_t index, uint8_t isshow);
	uint8_t lcd_segment_decimal_point_two(LCD_HandleType* LCDx, uint16_t index, uint8_t isshow);
	uint8_t lcd_segment_decimal_point_three(LCD_HandleType* LCDx, uint16_t index, uint8_t isshow);
	uint8_t lcd_segment_decimal_point(LCD_HandleType *LCDx, uint16_t index, uint8_t isshow);

	uint8_t lcd_segment_data_on_one(LCD_HandleType* LCDx, uint16_t index, char dat);
	uint8_t lcd_segment_data_on_two(LCD_HandleType* LCDx, uint16_t index, char dat);
	uint8_t lcd_segment_data_on_three(LCD_HandleType* LCDx, uint16_t index, char dat);
	uint8_t lcd_segment_data_on(LCD_HandleType* LCDx, uint16_t index, char dat);

	uint8_t lcd_segment_data_off_one(LCD_HandleType* LCDx, uint16_t index);
	uint8_t lcd_segment_data_off_two(LCD_HandleType* LCDx, uint16_t index);
	uint8_t lcd_segment_data_off_three(LCD_HandleType* LCDx, uint16_t index);
	uint8_t lcd_segment_data_off(LCD_HandleType* LCDx, uint16_t index);


	uint8_t lcd_segment_test_enter_one(LCD_HandleType* LCDx);
	uint8_t lcd_segment_test_enter_two(LCD_HandleType* LCDx);
	uint8_t lcd_segment_test_enter_three(LCD_HandleType* LCDx);
	uint8_t lcd_segment_test_enter(LCD_HandleType* LCDx);
	
	uint8_t lcd_segment_test_exit_one(LCD_HandleType* LCDx);
	uint8_t lcd_segment_test_exit_two(LCD_HandleType* LCDx);
	uint8_t lcd_segment_test_exit_three(LCD_HandleType* LCDx);
	uint8_t lcd_segment_test_exit(LCD_HandleType* LCDx);

	uint8_t lcd_segment_show_integer_one(LCD_HandleType* LCDx, uint32_t dat, uint8_t isfill);
	uint8_t lcd_segment_show_integer_two(LCD_HandleType* LCDx, uint32_t dat, uint8_t isfill);
	uint8_t lcd_segment_show_integer_three(LCD_HandleType* LCDx, uint32_t dat, uint8_t isfill);
	uint8_t lcd_segment_show_integer(LCD_HandleType* LCDx, uint32_t dat, uint8_t isfill);

	uint8_t lcd_segment_show_float_one(LCD_HandleType* LCDx, float dat, uint8_t pnum);
	uint8_t lcd_segment_show_float_two(LCD_HandleType* LCDx, float dat, uint8_t pnum);
	uint8_t lcd_segment_show_float_three(LCD_HandleType* LCDx, float dat, uint8_t pnum);
	uint8_t lcd_segment_show_float(LCD_HandleType *LCDx, float dat,uint8_t pnum);

	uint8_t lcd_segment_show_diff_temperature_one(LCD_HandleType* LCDx, float temperature, uint8_t positive, uint8_t istestmode);
	uint8_t lcd_segment_show_diff_temperature_two(LCD_HandleType* LCDx, float temperature, uint8_t positive, uint8_t istestmode);
	uint8_t lcd_segment_show_diff_temperature_three(LCD_HandleType* LCDx, float temperature, uint8_t positive, uint8_t istestmode);
	uint8_t lcd_segment_show_diff_temperature(LCD_HandleType* LCDx, float temperature, uint8_t positive, uint8_t istestmode);

	uint8_t lcd_segment_show_temperature_one(LCD_HandleType* LCDx, float temperature, uint8_t isin, uint8_t istestmode);
	uint8_t lcd_segment_show_temperature_two(LCD_HandleType* LCDx, float temperature, uint8_t isin, uint8_t istestmode);
	uint8_t lcd_segment_show_temperature_three(LCD_HandleType* LCDx, float temperature, uint8_t isin, uint8_t istestmode);
	uint8_t lcd_segment_show_temperature(LCD_HandleType* LCDx, float temperature, uint8_t isin, uint8_t istestmode);

	uint8_t lcd_segment_show_diff_time_one(LCD_HandleType* LCDx, float time, uint8_t istestmode);
	uint8_t lcd_segment_show_diff_time_two(LCD_HandleType* LCDx, float time, uint8_t istestmode);
	uint8_t lcd_segment_show_diff_time_three(LCD_HandleType* LCDx, float time, uint8_t istestmode);
	uint8_t lcd_segment_show_diff_time(LCD_HandleType* LCDx, float time, uint8_t istestmode);

	uint8_t lcd_segment_show_time_one(LCD_HandleType* LCDx, float time, uint8_t isup, uint8_t istestmode);
	uint8_t lcd_segment_show_time_two(LCD_HandleType* LCDx, float time, uint8_t isup, uint8_t istestmode);
	uint8_t lcd_segment_show_time_three(LCD_HandleType* LCDx, float time, uint8_t isup, uint8_t istestmode);
	uint8_t lcd_segment_show_time(LCD_HandleType* LCDx, float time, uint8_t isup, uint8_t istestmode);

	uint8_t lcd_segment_show_flow_volume_one(LCD_HandleType* LCDx, float flowvolume, uint8_t istestmode);
	uint8_t lcd_segment_show_flow_volume_two(LCD_HandleType* LCDx, float flowvolume, uint8_t istestmode);
	uint8_t lcd_segment_show_flow_volume_three(LCD_HandleType* LCDx, float flowvolume, uint8_t istestmode);
	uint8_t lcd_segment_show_flow_volume(LCD_HandleType* LCDx, float flowvolume, uint8_t istestmode);

	uint8_t lcd_segment_show_flow_speed_one(LCD_HandleType* LCDx, float flowspeed, uint8_t istestmode);
	uint8_t lcd_segment_show_flow_speed_two(LCD_HandleType* LCDx, float flowspeed, uint8_t istestmode);
	uint8_t lcd_segment_show_flow_speed_three(LCD_HandleType* LCDx, float flowspeed, uint8_t istestmode);
	uint8_t lcd_segment_show_flow_speed(LCD_HandleType* LCDx, float flowspeed, uint8_t istestmode);

	uint8_t lcd_segment_show_addr_one(LCD_HandleType* LCDx, uint32_t addr);
	uint8_t lcd_segment_show_addr_two(LCD_HandleType* LCDx, uint32_t addr);
	uint8_t lcd_segment_show_addr_three(LCD_HandleType* LCDx, uint32_t addr);
	uint8_t lcd_segment_show_addr(LCD_HandleType* LCDx, uint32_t addr);

	uint8_t lcd_segment_show_date_one(LCD_HandleType* LCDx, RTC_TimeType* rtcx);
	uint8_t lcd_segment_show_date_two(LCD_HandleType* LCDx, RTC_TimeType* rtcx);
	uint8_t lcd_segment_show_date_three(LCD_HandleType* LCDx, RTC_TimeType* rtcx);
	uint8_t lcd_segment_show_date(LCD_HandleType* LCDx, RTC_TimeType* rtcx);

	uint8_t lcd_segment_show_rtc_one(LCD_HandleType* LCDx, RTC_TimeType* rtcx);
	uint8_t lcd_segment_show_rtc_two(LCD_HandleType* LCDx, RTC_TimeType* rtcx);
	uint8_t lcd_segment_show_rtc_three(LCD_HandleType* LCDx, RTC_TimeType* rtcx);
	uint8_t lcd_segment_show_rtc(LCD_HandleType* LCDx, RTC_TimeType* rtcx);
	
	uint8_t lcd_segment_show_acc_rtc_one(LCD_HandleType* LCDx, uint32_t accrtc);
	uint8_t lcd_segment_show_acc_rtc_two(LCD_HandleType* LCDx, uint32_t accrtc);
	uint8_t lcd_segment_show_acc_rtc_three(LCD_HandleType* LCDx, uint32_t accrtc);
	uint8_t lcd_segment_show_acc_rtc(LCD_HandleType* LCDx, uint32_t accrtc);

	uint8_t lcd_segment_show_power_one(LCD_HandleType* LCDx, float power, uint8_t istestmode);
	uint8_t lcd_segment_show_power_two(LCD_HandleType* LCDx, float power, uint8_t istestmode);
	uint8_t lcd_segment_show_power_three(LCD_HandleType* LCDx, float power, uint8_t istestmode);
	uint8_t lcd_segment_show_power(LCD_HandleType* LCDx, float power, uint8_t istestmode);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* LCD_CFG_H_ */