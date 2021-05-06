
#ifndef __RQZ_LCD__H___
#define __RQZ_LCD__H___

//#include "../Drivers/cg_src/r_cg_lcd.h"
#include "r_cg_lcd.h"
#include "r_cg_macrodriver.h"

typedef enum __EN
{
 // ʹ����ʾ����ʧ����ʾ
 DISABLE = 0,
 ENABLE = 1,
}LCD_EN;

typedef enum LCD_Unit_TUD
{
 /*-- ��ʾ���ݵ�ȷ�� --*/
 
 /*----- ������һ�����ݣ�������������Դ������� -----*/
 HZ_Summation,  // �ۻ���1��
 HZ_Heat,       // ������2��
 HZ_Cauld,      // ������3��
 HZ_Flow,       // ������4��
 HZ_InWater,    // ��ˮ��5��
 HZ_OutWater,   // ��ˮ��6��
 HZ_TemperatureDifference,  // �²7��
 
 Unit_K,        // K  ��8��
 Unit_Temp_DU,  // ��  ��9��
 
 
 /*----- �ײ���������ݣ�������������Դ������� -----*/
 HZ_TEST,       // �춨��1��
 HZ_BUZZ,       // ������2��
 HZ_Power,      // ���ʡ�3��
 HZ_Address,    // ��ַ��4��
 HZ_Date,       // ���ڡ�5��
 HZ_Time,       // ʱ�䡾6��
 Symbol_UnPower,// ���û���˵ķ��š�7��
 
 /*----- �Ҳ���ʾȺ -----*/
 
 //���Թ��ɣ�KW.h
 Unit_KW,       // KW����2��-1��
 KWh_IS_Dot,    // ��ʾ��KW.h֮���С���㡾��2��-2��
 Unit_h,        // h   ����2��-3��
 
 Unit_MW_h,     // MW.h����3�С�
 
 Unit_GJ,       // GJ  ����4��-1��
 Unit_MJ,       // MJ  ����4��-1��
 
 // ���Թ��ɣ�m3/h
 Unit_MMM,      // m3����5��-���½ǡ�
 Unit_1h,       // /h����5��-���½ǡ�

 /*---- �м�������� ----*/
 // С����
 Right_Dot1,    // �Ҳ࿪ʼ�ĵ�1��С����,����1λС��ʱʹ��
 Right_Dot2,    // �Ҳ࿪ʼ�ĵ�2��С����,����2λС��ʱʹ��
 Right_Dot3,    // �Ҳ࿪ʼ�ĵ�3��С����,����3λС��ʱʹ��
 Right_Dot4,    // �Ҳ࿪ʼ�ĵ�4��С����,����4λС��ʱʹ��
 Right_Dot5,    // �Ҳ࿪ʼ�ĵ�5��С����,����5λС��ʱʹ�� 
 
 /*----- ������� -----*/
 Bit5_UD_,      // λ5��������º��
 Bit6_UD_,      // λ6��������º��
 BK_RightGraph, // LCD��������ʾ�����Ҳ�"���"������ʾ�����ڳ���
 
}LCD_Unit;

typedef enum __LCD_USE_VOID
{

	LCD_USE_0 = 0,// ʹ��0�����δʹ�õ�λ
	LCD_USE_VOID = 1,  // ʹ�ÿ��ַ������δʹ�õ�λ
	
}LCD_USE_VOID__user;

extern LCD_USE_VOID__user  USER_LCD_USE_FILL;   // Ĭ��ʹ�ÿ��ַ����Ǳ��������λ��

// ����λ���;�����򣺽������� LCD_Disp_Num ������
// ��ʹ�� LCD_Disp_Num()����ʱ����ֱ�ӵ������к�
#define LCD_USE_VOID_FILL()   USER_LCD_USE_FILL = LCD_USE_VOID   // �հ�������λ���Կհ����������û��ʹ�õ�λ������
#define LCD_USE_0_FILL()      USER_LCD_USE_FILL = LCD_USE_0      // ��0������λ����0���������û��ʹ�õ�λ������

void XY_LCD_Init(void); // ��ʼ��LCD

// ������ʾ[Ҫʹ����ʾ����뿪��ʾ]
void XY_LCD_DisplayON(void);

// �ر���ʾ
void XY_LCD_DisplayOFF(void);

void clear_lcd(void); // �����Ļ������ʾ
// ���LCD-���벿��ȫ��
void XY_LCD_DisplayClear(void);
void __del_alldot__(void); // �Ƴ�С����;Ӧ�ó�����������ʾһ�ɲ�ʹ��С����

// ��ʾ����
void XY_LCD_Display_ALL(void);

void LCD_DisplayUnit(LCD_Unit dispSelf,LCD_EN _EN); // ��λ��ʾ����
unsigned char LCD_Disp1ByteBit(unsigned char DispBit,unsigned char Data); // ��ֵλ����ʾ
void LCD_Disp_String(unsigned char StartPoint,char *Str); // ��ʾһ���ַ��������仯ʹ��ʱ������ǰ���XY_LCD_DisplayClear()������
void LCD_Disp_Num(unsigned char StartPoint,long long Disp_VAL,unsigned char Len); // ��ʾ����
void LCD_Disp_To10Num(unsigned char StartPoint,long long Disp_VAL,unsigned char Len); // �����룬������ʾ[�����Ƽ�ʹʹ�ô˷�ʽ]
void LCD_Disp_ToHEX(unsigned char StartPoint,unsigned long long Disp_VAL,unsigned char Len);// HEX����ʾ
void LCD_DoubleDisplayMode1(double FVal,unsigned char IntLen,unsigned char DotLen);// ��������ʾ

//#define MY_print(CONTROL_CHARP,__FCAL)  LCD_DoubleDisplayMode2(__FCAL,0,0)
void LCD_DotLens(unsigned char dotlen);
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
������ʵ����ο��ֲᡣ.

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
						SEG24.0      <.>     ��Ч���򵥶����ƣ�

*ע����λ��ǰ����Ŵ�Ĵ����λ�����������롣					 
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/


#endif








