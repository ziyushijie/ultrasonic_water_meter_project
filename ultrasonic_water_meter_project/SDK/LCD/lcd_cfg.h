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

	//===26PIN的LCD的PIN对应的端口信息
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
	
	//===文本标题
	typedef enum
	{
		TEXT_NONE=0,
		TEXT_ACC ,		//---累积
		TEXT_HEAT,		//---热量
		TEXT_ACC_HEAT,	//---累积热量
		TEXT_COOL,		//---冷量
		TEXT_ACC_COOL,	//---累积冷量
		TEXT_FLOW,		//---流量
		TEXT_ACC_FLOW,	//---累积流量
		TEXT_IWT ,		//---进水温度
		TEXT_OWT ,		//---回水温度
		TEXT_DWT ,		//---温差
		TEXT_TEST ,		//---检定模式
		TEXT_ALARM ,	//---报警
		TEXT_POWER ,	//---功率
		TEXT_ADDR ,		//---地址
		TEXT_DATE ,		//---日期
		TEXT_RTC,		//---时间
		TEXT_ACC_RTC,	//---累积时间
		TEXT_BATTERY ,	//---电池
	}text_title_on;

	//===单元标题
	typedef enum
	{
		UNIT_NONE = 0,
		UNIT_K,		//---显示单位K
		UNIT_C,		//---显示单位℃
		UNIT_KW,	//---显示千瓦kW
		UNIT_KW_D,  //---显示千瓦kW小数点后的点
		UNIT_KWH,   //---显示千瓦kW.h
		UNIT_KW_H,  //---显示兆瓦kW小数点后的h
		UNIT_MWH,   //---显示兆瓦MW.h
		UNIT_GJ,    //---显示GJ
		UNIT_MJ,    //---显示MJ
		UNIT_GJMJ,  //---显示GJMJ
		UNIT_M3,    //---显示m3
		UNIT_M3_H,  //---显示m3小数点后的h
		UNIT_M3H,   //---显示m3/h
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