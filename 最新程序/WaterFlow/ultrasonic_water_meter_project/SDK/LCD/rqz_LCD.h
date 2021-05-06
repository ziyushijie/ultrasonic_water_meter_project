
#ifndef __RQZ_LCD__H___
#define __RQZ_LCD__H___

//#include "../Drivers/cg_src/r_cg_lcd.h"
#include "r_cg_lcd.h"
#include "r_cg_macrodriver.h"

typedef enum __EN
{
 // 使能显示或者失能显示
 DISABLE = 0,
 ENABLE = 1,
}LCD_EN;

typedef enum LCD_Unit_TUD
{
 /*-- 显示内容的确定 --*/
 
 /*----- 顶部第一排内容，以下数字序号以从左至右 -----*/
 HZ_Summation,  // 累积【1】
 HZ_Heat,       // 热量【2】
 HZ_Cauld,      // 冷量【3】
 HZ_Flow,       // 流量【4】
 HZ_InWater,    // 进水【5】
 HZ_OutWater,   // 回水【6】
 HZ_TemperatureDifference,  // 温差【7】
 
 Unit_K,        // K  【8】
 Unit_Temp_DU,  // ℃  【9】
 
 
 /*----- 底部最后排内容，以下数字序号以从左至右 -----*/
 HZ_TEST,       // 检定【1】
 HZ_BUZZ,       // 报警【2】
 HZ_Power,      // 功率【3】
 HZ_Address,    // 地址【4】
 HZ_Date,       // 日期【5】
 HZ_Time,       // 时间【6】
 Symbol_UnPower,// 电池没电了的符号【7】
 
 /*----- 右侧显示群 -----*/
 
 //可以构成：KW.h
 Unit_KW,       // KW【第2行-1】
 KWh_IS_Dot,    // 显示：KW.h之间的小数点【第2行-2】
 Unit_h,        // h   【第2行-3】
 
 Unit_MW_h,     // MW.h【第3行】
 
 Unit_GJ,       // GJ  【第4行-1】
 Unit_MJ,       // MJ  【第4行-1】
 
 // 可以构成：m3/h
 Unit_MMM,      // m3【第5行-右下角】
 Unit_1h,       // /h【第5行-右下角】

 /*---- 中间段码区域 ----*/
 // 小数点
 Right_Dot1,    // 右侧开始的第1个小数点,保留1位小数时使用
 Right_Dot2,    // 右侧开始的第2个小数点,保留2位小数时使用
 Right_Dot3,    // 右侧开始的第3个小数点,保留3位小数时使用
 Right_Dot4,    // 右侧开始的第4个小数点,保留4位小数时使用
 Right_Dot5,    // 右侧开始的第5个小数点,保留5位小数时使用 
 
 /*----- 特殊外框 -----*/
 Bit5_UD_,      // 位5段码的上下横杠
 Bit6_UD_,      // 位6段码的上下横杠
 BK_RightGraph, // LCD的数字显示的最右侧"半口"符号显示，开口朝左。
 
}LCD_Unit;

typedef enum __LCD_USE_VOID
{

	LCD_USE_0 = 0,// 使用0填补多余未使用的位
	LCD_USE_VOID = 1,  // 使用空字符填补多余未使用的位
	
}LCD_USE_VOID__user;

extern LCD_USE_VOID__user  USER_LCD_USE_FILL;   // 默认使用空字符覆盖保留多余的位长

// 多余位填充;作用域：仅作用于 LCD_Disp_Num 函数。
// 当使用 LCD_Disp_Num()函数时可以直接调用下列宏
#define LCD_USE_VOID_FILL()   USER_LCD_USE_FILL = LCD_USE_VOID   // 空白填充多余位【以空白填充声明但没有使用的位置区域】
#define LCD_USE_0_FILL()      USER_LCD_USE_FILL = LCD_USE_0      // 以0填充多余位【以0填充声明但没有使用的位置区域】

void XY_LCD_Init(void); // 初始化LCD

// 开启显示[要使用显示则必须开显示]
void XY_LCD_DisplayON(void);

// 关闭显示
void XY_LCD_DisplayOFF(void);

void clear_lcd(void); // 清除屏幕所有显示
// 清除LCD-段码部分全灭
void XY_LCD_DisplayClear(void);
void __del_alldot__(void); // 移除小数点;应用场景：整数显示一律不使用小数点

// 显示所有
void XY_LCD_Display_ALL(void);

void LCD_DisplayUnit(LCD_Unit dispSelf,LCD_EN _EN); // 单位显示控制
unsigned char LCD_Disp1ByteBit(unsigned char DispBit,unsigned char Data); // 数值位段显示
void LCD_Disp_String(unsigned char StartPoint,char *Str); // 显示一个字符串【做变化使用时必须在前面加XY_LCD_DisplayClear()函数】
void LCD_Disp_Num(unsigned char StartPoint,long long Disp_VAL,unsigned char Len); // 显示整数
void LCD_Disp_To10Num(unsigned char StartPoint,long long Disp_VAL,unsigned char Len); // 简洁代码，整数显示[整数推荐使使用此方式]
void LCD_Disp_ToHEX(unsigned char StartPoint,unsigned long long Disp_VAL,unsigned char Len);// HEX数显示
void LCD_DoubleDisplayMode1(double FVal,unsigned char IntLen,unsigned char DotLen);// 浮点数显示

//#define MY_print(CONTROL_CHARP,__FCAL)  LCD_DoubleDisplayMode2(__FCAL,0,0)
void LCD_DotLens(unsigned char dotlen);
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
举例：实际请参考手册。.

					    SEG24.3
                      ___________
                     |		     |
                     |	         |
             SEG25.2 |           | SEG24.2
                     |           |
                     |  SEG25.1  |
                     |___________| 
                     |	 	     |
                     |           |
             SEG25.0 |           | SEG24.1
                     |           |
                     |           |
                     |___________|
						SEG24.0      <.>     无效（或单独控制）

*注：高位在前（序号大的代表高位），共阴编码。					 
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/


#endif








