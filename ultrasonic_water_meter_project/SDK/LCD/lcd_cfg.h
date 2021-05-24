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
	}text_title_on;

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
	}unit_title_on;


	uint8_t lcd_segment_init(void);
	uint8_t lcd_segment_enable(void);
	uint8_t lcd_segment_disable(void);
	uint8_t lcd_segment_clear(void);
	uint8_t lcd_segment_show_all(void);
	uint8_t lcd_segment_text_title_on(uint16_t text);
	uint8_t lcd_segment_text_title_off(uint16_t text);
	uint8_t lcd_segment_unit_title_on(uint16_t unit);
	uint8_t lcd_segment_unit_title_off(uint16_t unit);
	uint8_t lcd_segment_decimal_point(uint16_t index, uint8_t isshow);
	uint8_t lcd_segment_data_on(uint16_t index, char dat);
	uint8_t lcd_segment_data_off(uint16_t index);
	uint8_t lcd_segment_test_enter(void);
	uint8_t lcd_segment_test_exit(void);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* LCD_CFG_H_ */