#include "lcd_cfg.h"

////===��ʾ�ı�
//uint16_t g_lcd_segment_text = TEXT_NONE;
////===��ʾ��λ
//uint16_t g_lcd_segment_unit = UNIT_NONE;
////===ʹ��״̬��0---��ʹ�ܣ�1---ʹ��
//uint8_t g_lcd_segment_enable = 1;

//===ȫ�ֱ�������
LCD_HandleType				g_lcd_one = {0};
pLCD_HandleType				p_lcd_one=&g_lcd_one;

//===LCD�����
//0,1,2,3,4,5,6,7,8,9,A,b,C,d,E,F,i,n,o,r,t,u,-
const uint8_t g_lcd_segment_display_table_one[23] = {
	0x5F,0x06,0x3D,0x2F,0x66,0x6B,0x7B,0x0E,0x7F,0x6F,
	0x7E,0x73,0x59,0x37,0x79,0x78,0x10,0x32,0x33,0x30,
	0x71,0x13,0x20
};

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_init_one(LCD_HandleType *LCDx, uint32_t(*func_time_tick)(void))
{
	//===26PIN��LCD��PIN��Ӧ�Ķ˿���Ϣ
	//PIN1----COM0
	//PIN2----COM1
	//PIN3----COM2
	//PIN4----COM3
	//PIN5----S0--------SEG0
	//PIN6----S1--------SEG1
	//PIN7----S2--------SEG2
	//PIN8----S3--------SEG3
	//PIN9----S7--------SEG7----P53
	//PIN10---S8--------SEG8----P54
	//PIN11---S11-------SEG11---P57
	//PIN12---S12-------SEG12---P70
	//PIN13---S16-------SEG16---P74
	//PIN14---S17-------SEG17---P75
	//PIN15---S18-------SEG18---P76
	//PIN16---S19-------SEG19---P77
	//PIN17---S20-------SEG20---P30
	//PIN18---S21-------SEG21---P31
	//PIN19---S22-------SEG22---P32
	//PIN20---S23-------SEG23---P33
	//PIN21---S33-------SEG33---P26
	//PIN22---S34-------SEG34---P27
	//PIN23---S35-------SEG35---P10
	//PIN24---S36-------SEG36---P11
	//PIN25---S37-------SEG37---P12
	//PIN26---S38-------SEG38---P13

	//---��ʹ��LCDʱ��
	LCDON = 0;
	//---�ⲿ��ѹ����ģʽ��A����ģʽ��4��ʱ��Ƭ��1/3ƫѹ��
	LCDM0 = _00_LCD_DISPLAY_WAVEFORM_A | _0D_LCD_DISPLAY_MODE1;
	LCDM0 |= _00_LCD_VOLTAGE_MODE_EXTERNAL;

	//---���ö������õ��Ķ˿�

	//---��ʹ����������
	PU1 &= 0xF0;
	PU2 &= 0x3F;
	PU3 &= 0xF0;
	PU5 &= 0x64;
	PU7 &= 0x0E;

	//---����Ϊ����ģʽ
	POM5 &= 0xE7;
	PIM5 &= 0xF7;

	//---���ö˿�Ϊ�����������
	PMC1 &= 0xF0;
	P1 &= 0xF0;
	PM1 &= 0xF0;

	PMC2 &= 0x3F;
	PM2 &= 0x3F;
	P2 &= 0x3F;

	PM3 &= 0xF0;
	P3 &= 0xF0;

	PM3 &= 0xF0;
	P3 &= 0xF0;

	PM5 &= 0x67;
	P5 &= 0x67;

	PM7 &= 0x0E;
	P7 &= 0x0E;

	//---������ƶ˿�
	PFSEG0 |= 0xF0;
	PFSEG1 |= 0xFF;
	PFSEG2 |= 0xFF;
	PFSEG3 |= 0xBB;
	PFSEG4 |= 0xFF;
	PFSEG5 &= 0x00;
	PFSEG6 &= 0x00;


	//---��ʾAͼ������
	LCDM1 |= _00_LCD_DISPLAY_PATTERN_A;
	//---�޶�LCD��ʱ��Ƶ�ʣ�����ʱ��Ƶ�ʻ�����Ӱ��
	LCDC0 = _07_LCD_CLOCK_FSUB_FIL_8;//_05_LCD_CLOCK_FSUB_FIL_6;

	//---ע��δ���
	(func_time_tick != NULL) ?
		(LCDx->msg_f_time_tick = func_time_tick) :
		(LCDx->msg_f_time_tick = sys_tick_task_get_tick);

	LCDx->msg_text = TEXT_NONE;
	LCDx->msg_unit = UNIT_NONE;

	lcd_segment_show_all_one(LCDx);
	return lcd_segment_enable_one(LCDx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_init_two(LCD_HandleType *LCDx, uint32_t(*func_time_tick)(void))
{
	lcd_segment_show_all_two(LCDx);
	return lcd_segment_enable_two(LCDx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_init_three(LCD_HandleType *LCDx, uint32_t(*func_time_tick)(void))
{
	lcd_segment_show_all_three(LCDx);
	return lcd_segment_enable_three(LCDx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_time_tick_init(LCD_HandleType* LCDx, uint32_t(*func_time_tick)(void))
{
	//---ע��δ���
	(func_time_tick != NULL) ?
		(LCDx->msg_f_time_tick = func_time_tick) :
		(LCDx->msg_f_time_tick = sys_tick_task_get_tick);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����Һ��LCD��ʼ��
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_init(LCD_HandleType* LCDx, uint32_t(*func_time_tick)(void))
{
	if ((LCDx!=NULL)&&(LCDx== LCD_TASK_ONE))
	{
		return lcd_segment_init_one(LCDx,func_time_tick);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_TWO))
	{
		return lcd_segment_init_two(LCDx,func_time_tick);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_THREE))
	{
		return lcd_segment_init_three(LCDx,func_time_tick);
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_enable_one(LCD_HandleType *LCDx)
{
	SCOC = 1;
	LCDON = 1;
	LCDx->msg_backlight = 1;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_enable_two(LCD_HandleType *LCDx)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_enable_three(LCD_HandleType *LCDx)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����ʾ
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_enable(LCD_HandleType *LCDx)
{
	if ((LCDx != NULL) && (LCDx == LCD_TASK_ONE))
	{
		return lcd_segment_enable_one(LCDx);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_TWO))
	{
		return lcd_segment_enable_two(LCDx);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_THREE))
	{
		return lcd_segment_enable_three(LCDx);
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_disable_one(LCD_HandleType *LCDx)
{
	SCOC = 0;
	LCDON = 0;
	LCDx->msg_backlight = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_disable_two(LCD_HandleType *LCDx)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_disable_three(LCD_HandleType *LCDx)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: �ر���ʾ
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_disable(LCD_HandleType *LCDx)
{
	if ((LCDx != NULL) && (LCDx == LCD_TASK_ONE))
	{
		return lcd_segment_disable_one(LCDx);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_TWO))
	{
		return lcd_segment_disable_two(LCDx);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_THREE))
	{
		return lcd_segment_disable_three(LCDx);
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_clear_one(LCD_HandleType* LCDx)
{
	SEG0 = 0xF0;
	SEG1 = 0xF0;
	SEG2 = 0xF0;
	SEG3 = 0xF0;
	SEG7 = 0xF0;
	SEG8 = 0xF0;

	SEG11 = 0xF0;
	SEG12 = 0xF0;

	SEG16 = 0xF0;
	SEG17 = 0xF0;
	SEG18 = 0xF0;
	SEG19 = 0xF0;
	SEG20 = 0xF0;
	SEG21 = 0xF0;
	SEG22 = 0xF0;
	SEG23 = 0xF0;

	SEG33 = 0xF0;
	SEG34 = 0xF0;
	SEG35 = 0xF0;
	SEG36 = 0xF0;
	SEG37 = 0xF0;
	SEG38 = 0xF0;

	LCDx->msg_text = TEXT_NONE;
	LCDx->msg_unit = UNIT_NONE;

	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_clear_two(LCD_HandleType* LCDx)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_clear_three(LCD_HandleType* LCDx)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_clear(LCD_HandleType *LCDx)
{
	if ((LCDx != NULL) && (LCDx == LCD_TASK_ONE))
	{
		return lcd_segment_clear_one(LCDx);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_TWO))
	{
		return lcd_segment_clear_two(LCDx);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_THREE))
	{
		return lcd_segment_clear_three(LCDx);
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_all_one(LCD_HandleType* LCDx)
{
	SEG0 = 0x0F;
	SEG1 = 0x0F;
	SEG2 = 0x0F;
	SEG3 = 0x0F;
	SEG7 = 0x0F;
	SEG8 = 0x0F;

	SEG11 = 0x0F;
	SEG12 = 0x0F;

	SEG16 = 0x0F;
	SEG17 = 0x0F;
	SEG18 = 0x0F;
	SEG19 = 0x0F;
	SEG20 = 0x0F;
	SEG21 = 0x0F;
	SEG22 = 0x0F;
	SEG23 = 0x0F;

	SEG33 = 0x0F;
	SEG34 = 0x0F;
	SEG35 = 0x0F;
	SEG36 = 0x0F;
	SEG37 = 0x0F;
	SEG38 = 0x0F;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_all_two(LCD_HandleType* LCDx)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_all_three(LCD_HandleType* LCDx)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ʾ����
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_all(LCD_HandleType *LCDx)
{
	if ((LCDx != NULL) && (LCDx == LCD_TASK_ONE))
	{
		return lcd_segment_show_all_one(LCDx);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_TWO))
	{
		return lcd_segment_show_all_two(LCDx);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_THREE))
	{
		return lcd_segment_show_all_three(LCDx);
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ʾ����̧ͷ��
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_text_title_on_one(LCD_HandleType *LCDx, uint16_t text )
{
	if (text!= LCDx->msg_text)
	{
		lcd_segment_text_title_off_one(LCDx,LCDx->msg_text);
		LCDx->msg_text = text;
	}
	switch (text)
	{
		case TEXT_ACC:		//---�ۻ�
		{
			SEG0 |= 0x08;
			break;
		}
		case TEXT_HEAT:		//---����
		{
			SEG2 |= 0x08;
			break;
		}
		case TEXT_ACC_HEAT:		//---����
		{
			SEG0 |= 0x08;
			SEG2 |= 0x08;
			break;
		}
		case TEXT_COOL:		//---����
		{
			SEG7 |= 0x08;
			break;
		}
		case TEXT_ACC_COOL:		//---����
		{
			SEG0 |= 0x08;
			SEG7 |= 0x08;
			break;
		}
		case TEXT_FLOW:		//---����
		{
			SEG11 |= 0x08;
			break;
		}
		case TEXT_ACC_FLOW:		//---����
		{
			SEG0 |= 0x08;
			SEG11 |= 0x08;
			break;
		}
		case TEXT_IWT:		//---��ˮ�¶�
		{
			SEG16 |= 0x08;
			break;
		}
		case TEXT_OWT:		//---��ˮ�¶�
		{
			SEG20 |= 0x08;
			break;
		}
		case TEXT_DWT:		//---�²�
		{
			SEG33|= 0x08;
			break;
		}
		case TEXT_TEST:		//---�춨ģʽ
		{
			SEG38 |= 0x08;
			break;
		}
		case TEXT_ALARM:	//---����
		{
			SEG37 |= 0x08;
			break;
		}
		case TEXT_POWER:	//---����
		{
			SEG36 |= 0x08;
			break;
		}
		case TEXT_ADDR:		//---��ַ
		{
			SEG35 |= 0x08;
			break;
		}
		case TEXT_DATE:		//---����
		{
			SEG34 |= 0x08;
			break;
		}
		case TEXT_RTC:		//---ʱ��
		{
			SEG33 |= 0x01;
			break;
		}
		case TEXT_ACC_RTC:		//---ʱ��
		{
			SEG0 |= 0x08;
			SEG33 |= 0x01;
			break;
		}
		case TEXT_BATTERY:	//---���
		{
			SEG33 |= 0x02;
			break;
		}
		default:
		{
			lcd_segment_clear_one(LCDx);
			break;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_text_title_on_two(LCD_HandleType* LCDx, uint16_t text)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_text_title_on_three(LCD_HandleType* LCDx, uint16_t text)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_text_title_on(LCD_HandleType* LCDx, uint16_t text)
{
	if ((LCDx != NULL) && (LCDx == LCD_TASK_ONE))
	{
		return lcd_segment_text_title_on_one(LCDx,text);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_TWO))
	{
		return lcd_segment_text_title_on_two(LCDx, text);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_THREE))
	{
		return lcd_segment_text_title_on_three(LCDx, text);
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ʾ����̧ͷ�ر�
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_text_title_off_one(LCD_HandleType *LCDx, uint16_t text)
{
	switch (text)
	{
		case TEXT_NONE:
		{
			break;
		}
		case TEXT_ACC:		//---�ۻ�
		{
			SEG0 &= 0xF7;
			break;
		}
		case TEXT_HEAT:		//---����
		{
			SEG2 &= 0xF7;
			break;
		}
		case TEXT_ACC_HEAT:		//---�ۻ�����
		{
			SEG0 &= 0xF7;
			SEG2 &= 0xF7;
			break;
		}
		case TEXT_COOL:		//---����
		{
			SEG7 &= 0xF7;
			break;
		}
		case TEXT_ACC_COOL:		//---�ۻ�����
		{
			SEG0 &= 0xF7;
			SEG7 &= 0xF7;
			break;
		}
		case TEXT_FLOW:		//---����
		{
			SEG11 &= 0xF7;
			break;
		}
		case TEXT_ACC_FLOW:		//---�ۻ�����
		{
			SEG0 &= 0xF7;
			SEG11 &= 0xF7;
			break;
		}
		case TEXT_IWT:		//---��ˮ�¶�
		{
			SEG16 &= 0xF7;
			break;
		}
		case TEXT_OWT:		//---��ˮ�¶�
		{
			SEG20 &= 0xF7;
			break;
		}
		case TEXT_DWT:		//---�²�
		{
			SEG33 &= 0xF7;
			break;
		}
		case TEXT_TEST:		//---�춨ģʽ
		{
			SEG38 &= 0xF7;
			break;
		}
		case TEXT_ALARM:	//---����
		{
			SEG37 &= 0xF7;
			break;
		}
		case TEXT_POWER:	//---����
		{
			SEG36 &= 0xF7;
			break;
		}
		case TEXT_ADDR:		//---��ַ
		{
			SEG35 &= 0xF7;
			break;
		}
		case TEXT_DATE:		//---����
		{
			SEG34 &= 0xF7;
			break;
		}
		case TEXT_RTC:		//---ʱ��
		{
			SEG33 &= 0xF7;
			break;
		}
		case TEXT_ACC_RTC:		//---�ۻ�ʱ��
		{
			SEG0 &= 0xF7;
			SEG33 &= 0xF7;
			break;
		}
		case TEXT_BATTERY:	//---���
		{
			SEG33 &= 0xFD;
			break;
		}
		default:
		{
			lcd_segment_clear_one(LCDx);
			break;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_text_title_off_two(LCD_HandleType* LCDx, uint16_t text)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_text_title_off_three(LCD_HandleType* LCDx, uint16_t text)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_text_title_off(LCD_HandleType* LCDx, uint16_t text)
{
	if ((LCDx != NULL) && (LCDx == LCD_TASK_ONE))
	{
		return lcd_segment_text_title_off_one(LCDx, text);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_TWO))
	{
		return lcd_segment_text_title_off_two(LCDx, text);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_THREE))
	{
		return lcd_segment_text_title_off_three(LCDx, text);
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ʾ��λ̧ͷ����
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_unit_title_on_one(LCD_HandleType *LCDx, uint16_t unit)
{
	if (unit != LCDx->msg_unit)
	{
		lcd_segment_unit_title_off_one(LCDx, LCDx->msg_unit);
		LCDx->msg_unit = unit;
	}
	//---���ݵ�λ������ʾָ���ĵ�λ
	switch (unit)
	{
		case UNIT_K :		//---��ʾ��λK
		{
			SEG34 |= 0x02;
			break;
		}
		case UNIT_C:		//---��ʾ��λ��
		{
			SEG34 |= 0x04;
			break;
		}
		case UNIT_KW:		//---��ʾǧ��kW
		{
			SEG35 |= 0x02;
			break;
		}
		case UNIT_KW_D:		//---��ʾǧ��kWС�����ĵ�
		{
			SEG35 |= 0x04;
			break;
		}
		case UNIT_KWH:		//---��ʾǧ��kW.h
		{
			SEG35 |= 0x06;
			SEG36 |= 0x04;
			break;
		}
		case UNIT_KW_H:		//---��ʾǧ��kWС������h
		{
			SEG36 |= 0x04;
			break;
		}
		case UNIT_MWH:		//---��ʾ����MW.h
		{
			SEG36 |= 0x02;
			break;
		}
		case UNIT_GJ:		//---��ʾGJ
		{
			SEG37 |= 0x02;
			break;
		}
		case UNIT_MJ:		//---��ʾMJ
		{
			SEG37 |= 0x04;
			break;
		}
		case UNIT_GJMJ:		//---��ʾGJMJ
		{
			SEG37 |= 0x06;
			break;
		}
		case UNIT_M3:		//---��ʾm3
		{
			SEG38 |= 0x02;
			break;
		}
		case UNIT_M3_H:		//---��ʾm3С������/h
		{
			SEG38 |= 0x04;
			break;
		}
		case UNIT_M3H:		//---��ʾm3/h
		{
			SEG38 |= 0x06;
			break;
		}
		default:
		{
			lcd_segment_clear_one(LCDx);
			break;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_unit_title_on_two(LCD_HandleType* LCDx, uint16_t unit)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_unit_title_on_three(LCD_HandleType* LCDx, uint16_t unit)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_unit_title_on(LCD_HandleType* LCDx, uint16_t unit)
{
	if ((LCDx != NULL) && (LCDx == LCD_TASK_ONE))
	{
		return lcd_segment_unit_title_on_one(LCDx, unit);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_TWO))
	{
		return lcd_segment_unit_title_on_two(LCDx, unit);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_THREE))
	{
		return lcd_segment_unit_title_on_three(LCDx, unit);
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ʾ��λ̧ͷ�ر�
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_unit_title_off_one(LCD_HandleType *LCDx, uint16_t unit)
{
	//---���ݵ�λ������ʾָ���ĵ�λ
	switch (unit)
	{
		case UNIT_NONE:
		{
			break;
		}
		case UNIT_K:		//---��ʾ��λK
		{
			SEG34 &= 0xFD;
			break;
		}
		case UNIT_C:		//---��ʾ��λ��
		{
			SEG34 &= 0xFB;
			break;
		}
		case UNIT_KW:		//---��ʾǧ��kW
		{
			SEG35 &= 0xFD;
			break;
		}
		case UNIT_KW_D:		//---��ʾǧ��kWС�����ĵ�
		{
			SEG35 &= 0xFB;
			break;
		}
		case UNIT_KWH:		//---��ʾǧ��kW.h
		{
			SEG35 &= 0xF9;
			SEG36 &= 0xFB;
			break;
		}
		case UNIT_KW_H:		//---��ʾǧ��kWС������h
		{
			SEG36 &= 0xFB;
			break;
		}
		case UNIT_MWH:		//---��ʾ����MW.h
		{
			SEG36 &= 0xFD;
			break;
		}
		case UNIT_GJ:		//---��ʾGJ
		{
			SEG37 &= 0xFD;
			break;
		}
		case UNIT_MJ:		//---��ʾMJ
		{
			SEG37 &= 0xFB;
			break;
		}
		case UNIT_GJMJ:		//---��ʾGJMJ
		{
			SEG37 &= 0xF9;
			break;
		}
		case UNIT_M3:		//---��ʾm3
		{
			SEG38 &= 0xFD;
			break;
		}
		case UNIT_M3_H:		//---��ʾm3С������/h
		{
			SEG38 &= 0xFB;
			break;
		}
		case UNIT_M3H:		//---��ʾm3/h
		{
			SEG38 &= 0xF9;
			break;
		}
		default:
		{
			lcd_segment_clear_one(LCDx);
			break;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_unit_title_off_two(LCD_HandleType* LCDx, uint16_t unit)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_unit_title_off_three(LCD_HandleType* LCDx, uint16_t unit)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_unit_title_off(LCD_HandleType* LCDx, uint16_t unit)
{
	if ((LCDx != NULL) && (LCDx == LCD_TASK_ONE))
	{
		return lcd_segment_unit_title_off_one(LCDx, unit);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_TWO))
	{
		return lcd_segment_unit_title_off_two(LCDx, unit);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_THREE))
	{
		return lcd_segment_unit_title_off_three(LCDx, unit);
	}
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ָ��λ����ʾС���㣬������
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_decimal_point_one(LCD_HandleType *LCDx, uint16_t index, uint8_t isshow)
{
	switch (index)
	{
		case 3:
		{
			(isshow != 0) ? (SEG38 |= 0x01) : (SEG38 &= 0xFE);
			break;
		}
		case 4:
		{
			(isshow != 0) ? (SEG37 |= 0x01) : (SEG37 &= 0xFE);
			break;
		}
		case 5:
		{
			(isshow != 0) ? (SEG36 |= 0x01) : (SEG36 &= 0xFE);
			break;
		}
		case 6:
		{
			(isshow != 0) ? (SEG35 |= 0x01) : (SEG35 &= 0xFE);
			break;
		}
		case 7:
		{
			(isshow != 0) ? (SEG34 |= 0x01) : (SEG34 &= 0xFE);
			break;
		}
		default:
		{
			SEG38 &= 0xFE;
			SEG37 &= 0xFE;
			SEG36 &= 0xFE;
			SEG35 &= 0xFE;
			SEG34 &= 0xFE;
			break;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_decimal_point_two(LCD_HandleType* LCDx, uint16_t index, uint8_t isshow)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_decimal_point_three(LCD_HandleType* LCDx, uint16_t index, uint8_t isshow)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_decimal_point(LCD_HandleType* LCDx, uint16_t index, uint8_t isshow)
{
	if ((LCDx != NULL) && (LCDx == LCD_TASK_ONE))
	{
		return lcd_segment_decimal_point_one(LCDx, index,isshow);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_TWO))
	{
		return lcd_segment_decimal_point_two(LCDx, index, isshow);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_THREE))
	{
		return lcd_segment_decimal_point_three(LCDx, index, isshow);
	}
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ָ��λ����ʾ���ݿ�����������
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_data_on_one(LCD_HandleType *LCDx, uint16_t index, char dat )
{
	uint8_t temp_data = 0;
	uint8_t temp_seg = 0;
	switch (dat)
	{
		case 0:
		case '0':
		{
			temp_data = g_lcd_segment_display_table_one[0];
			break;
		}
		case 1:
		case '1':
		{
			temp_data = g_lcd_segment_display_table_one[1];
			break;
		}
		case 2:
		case '2':
		{
			temp_data = g_lcd_segment_display_table_one[2];
			break;
		}
		case 3:
		case '3':
		{
			temp_data = g_lcd_segment_display_table_one[3];
			break;
		}
		case 4:
		case '4':
		{
			temp_data = g_lcd_segment_display_table_one[4];
			break;
		}
		case 5:
		case '5':
		{
			temp_data = g_lcd_segment_display_table_one[5];
			break;
		}
		case 6:
		case '6':
		{
			temp_data = g_lcd_segment_display_table_one[6];
			break;
		}
		case 7:
		case '7':
		{
			temp_data = g_lcd_segment_display_table_one[7];
			break;
		}
		case 8:
		case '8':
		{
			temp_data = g_lcd_segment_display_table_one[8];
			break;
		}
		case 9:
		case '9':
		{
			temp_data = g_lcd_segment_display_table_one[9];
			break;
		}
		case 10:
		case 'a':
		case 'A':
		{
			temp_data = g_lcd_segment_display_table_one[10];
			break;
		}
		case 11:
		case 'b':
		case 'B':
		{
			temp_data = g_lcd_segment_display_table_one[11];
			break;
		}
		case 12:
		case 'c':
		case 'C':
		{
			temp_data = g_lcd_segment_display_table_one[12];
			break;
		}
		case 13:
		case 'd':
		case 'D':
		{
			temp_data = g_lcd_segment_display_table_one[13];
			break;
		}
		case 14:
		case 'e':
		case 'E':
		{
			temp_data = g_lcd_segment_display_table_one[14];
			break;
		}
		case 15:
		case 'f':
		case 'F':
		{
			temp_data = g_lcd_segment_display_table_one[15];
			break;
		}
		case 'i':
		case 'I':
		{
			temp_data = g_lcd_segment_display_table_one[16];
			break;
		}
		case 'n':
		case 'N':
		{
			temp_data = g_lcd_segment_display_table_one[17];
			break;
		}
		case 'o':
		case 'O':
		{
			temp_data = g_lcd_segment_display_table_one[18];
			break;
		}
		case 'r':
		case 'R':
		{
			temp_data = g_lcd_segment_display_table_one[19];
			break;
		}
		case 't':
		case 'T':
		{
			temp_data = g_lcd_segment_display_table_one[20];
			break;
		}
		case 'u':
		case 'U':
		{
			temp_data = g_lcd_segment_display_table_one[21];
			break;
		}
		case '-':
		{
			temp_data = g_lcd_segment_display_table_one[22];
			break;
		}
		default:
		{
			return lcd_segment_clear(LCDx);
			//break;
		}
	}
	//---�ж���ʾ���ݣ������ң�������1,2,3,4,5,6,7,8
	switch (index)
	{
		case 1:
		{
			SEG1 &= 0xF0;
			SEG0 &= 0xF8;
			SEG1 |= (temp_data & 0x0F);
			SEG0 |= ((temp_data >> 4) & 0x07);
			break;
		}
		case 2:
		{
			SEG3 &= 0xF0;
			SEG2 &= 0xF8;
			SEG3 |= (temp_data & 0x0F);
			SEG2 |= ((temp_data >> 4) & 0x07);
			break;
		}
		case 3:
		{
			SEG8 &= 0xF0;
			SEG7 &= 0xF8;
			SEG8 |= (temp_data & 0x0F);
			SEG7 |= ((temp_data >> 4) & 0x07);
			break;
		}
		case 4:
		{
			SEG12 &= 0xF0;
			SEG11 &= 0xF8;
			SEG12 |= (temp_data & 0x0F);
			SEG11 |= ((temp_data >> 4) & 0x07);
			break;
		}
		case 5:
		{
			SEG17 &= 0xF0;
			SEG16 &= 0xF8;
			SEG17 |= (temp_data & 0x0F);
			SEG16 |= ((temp_data >> 4) & 0x07);
			break;
		}
		case 6:
		{
			SEG19 &= 0xF0;
			SEG18 &= 0xF8;
			SEG19 |= (temp_data & 0x0F);
			SEG18 |= ((temp_data >> 4) & 0x07);
			break;
		}
		case 7:
		{
			SEG21 &= 0xF0;
			SEG20 &= 0xF8;
			SEG21 |= (temp_data & 0x0F);
			SEG20 |= ((temp_data >> 4) & 0x07);
			break;
		}
		case 8:
		{
			SEG23 &= 0xF0;
			SEG22 &= 0xF8;
			SEG23 |= (temp_data & 0x0F);
			SEG22 |= ((temp_data >> 4) & 0x07);
			break;
		}
		default:
		{
			lcd_segment_clear(LCDx);
			break;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_data_on_two(LCD_HandleType* LCDx, uint16_t index, char dat)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_data_on_three(LCD_HandleType* LCDx, uint16_t index, char dat)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_data_on(LCD_HandleType* LCDx, uint16_t index, char dat)
{
	if ((LCDx != NULL) && (LCDx == LCD_TASK_ONE))
	{
		return lcd_segment_data_on_one(LCDx, index, dat);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_TWO))
	{
		return lcd_segment_data_on_two(LCDx, index, dat);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_THREE))
	{
		return lcd_segment_data_on_three(LCDx, index, dat);
	}
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ָ��λ����ʾ���ݹرգ�������
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_data_off_one(LCD_HandleType *LCDx, uint16_t index)
{
	//---�ж���ʾ���ݣ������ң�������1,2,3,4,5,6,7,8
	switch (index)
	{
		case 1:
		{
			SEG1 &= 0xF0;
			SEG0 &= 0xF8;
			break;
		}
		case 2:
		{
			SEG3 &= 0xF0;
			SEG2 &= 0xF8;
			break;
		}
		case 3:
		{
			SEG8 &= 0xF0;
			SEG7 &= 0xF8;
			break;
		}
		case 4:
		{
			SEG12 &= 0xF0;
			SEG11 &= 0xF8;
			break;
		}
		case 5:
		{
			SEG17 &= 0xF0;
			SEG16 &= 0xF8;
			break;
		}
		case 6:
		{
			SEG19 &= 0xF0;
			SEG18 &= 0xF8;
			break;
		}
		case 7:
		{
			SEG21 &= 0xF0;
			SEG20 &= 0xF8;
			break;
		}
		case 8:
		{
			SEG23 &= 0xF0;
			SEG22 &= 0xF8;
			break;
		}
		default:
		{
			lcd_segment_clear(LCDx);
			break;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_data_off_two(LCD_HandleType* LCDx, uint16_t index)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_data_off_three(LCD_HandleType* LCDx, uint16_t index)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_data_off(LCD_HandleType* LCDx, uint16_t index)
{
	if ((LCDx != NULL) && (LCDx == LCD_TASK_ONE))
	{
		return lcd_segment_data_off_one(LCDx, index);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_TWO))
	{
		return lcd_segment_data_off_two(LCDx, index);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_THREE))
	{
		return lcd_segment_data_off_three(LCDx, index);
	}
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����궨ģʽ
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_test_enter_one(LCD_HandleType *LCDx)
{
	BLON = 1;
	SEG38 |= 0x08;
	SEG38 &= 0x7F;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_test_enter_two(LCD_HandleType* LCDx)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_test_enter_three(LCD_HandleType* LCDx)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_test_enter(LCD_HandleType* LCDx)
{
	if ((LCDx != NULL) && (LCDx == LCD_TASK_ONE))
	{
		return lcd_segment_test_enter_one(LCDx);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_TWO))
	{
		return lcd_segment_test_enter_two(LCDx);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_THREE))
	{
		return lcd_segment_test_enter_three(LCDx);
	}
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: �˳��궨ģʽ
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_test_exit_one(LCD_HandleType *LCDx)
{
	BLON = 0;
	LCDSEL = 0;
	SEG38 &= 0x77;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_test_exit_two(LCD_HandleType* LCDx)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_test_exit_three(LCD_HandleType* LCDx)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_test_exit(LCD_HandleType* LCDx)
{
	if ((LCDx != NULL) && (LCDx == LCD_TASK_ONE))
	{
		return lcd_segment_test_exit_one(LCDx);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_TWO))
	{
		return lcd_segment_test_exit_two(LCDx);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_THREE))
	{
		return lcd_segment_test_exit_three(LCDx);
	}
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ʾ���������ж�0�Ƿ����
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_integer_one(LCD_HandleType *LCDx, uint32_t dat, uint8_t isfill)
{
	uint8_t temp_dat = dat / 10000000;
	//temp_dat = dat / 10000000;
	uint8_t dat_flag = 0;
	//---�ж�Һ���Ƿ�ر���ʾ��

	if (temp_dat==0)
	{
		if (isfill!=0)
		{
			lcd_segment_data_on_one(LCDx, 1, 0);
		}
		else
		{
			lcd_segment_data_off_one(LCDx, 1);
		}
	
	}
	else
	{
		dat_flag = 1;
		lcd_segment_data_on_one(LCDx, 1, temp_dat);
	}
	dat %= 10000000;
	temp_dat = dat / 1000000;
	if ((temp_dat == 0)&&(dat_flag==0))
	{
		if (isfill != 0)
		{
			lcd_segment_data_on_one(LCDx, 2, 0);
		}
		else
		{
			lcd_segment_data_off_one(LCDx, 2);
		}
	}
	else
	{
		dat_flag = 1;
		lcd_segment_data_on_one(LCDx, 2, temp_dat);
	}
	dat %= 1000000;
	temp_dat = dat / 100000;
	if ((temp_dat == 0) && (dat_flag == 0))
	{
		if (isfill != 0)
		{
			lcd_segment_data_on_one(LCDx, 3, 0);
		}
		else
		{
			lcd_segment_data_off_one(LCDx, 3);
		}
	}
	else
	{
		dat_flag = 1;
		lcd_segment_data_on_one(LCDx, 3, temp_dat);
	}
	lcd_segment_decimal_point_one(LCDx, 3, 0);
	dat %= 100000;
	temp_dat = dat / 10000;
	if ((temp_dat == 0) && (dat_flag == 0))
	{
		if (isfill != 0)
		{
			lcd_segment_data_on_one(LCDx, 4, 0);
		}
		else
		{
			lcd_segment_data_off_one(LCDx, 4);
		}
	}
	else
	{
		dat_flag = 1;
		lcd_segment_data_on_one(LCDx, 4, temp_dat);
	}
	lcd_segment_decimal_point_one(LCDx, 4, 0);
	dat %= 10000;
	temp_dat = dat / 1000;
	if ((temp_dat == 0) && (dat_flag == 0))
	{
		if (isfill != 0)
		{
			lcd_segment_data_on_one(LCDx, 5, 0);
		}
		else
		{
			lcd_segment_data_off_one(LCDx, 5);
		}
	}
	else
	{
		dat_flag = 1;
		lcd_segment_data_on_one(LCDx, 5, temp_dat);
	}
	lcd_segment_decimal_point_one(LCDx, 5, 0);
	dat %= 1000;
	temp_dat = dat / 100;
	if ((temp_dat == 0) && (dat_flag == 0))
	{
		if (isfill != 0)
		{
			lcd_segment_data_on_one(LCDx, 6, 0);
		}
		else
		{
			lcd_segment_data_off_one(LCDx, 6);
		}
	}
	else
	{
		dat_flag = 1;
		lcd_segment_data_on_one(LCDx, 6, temp_dat);
	}
	lcd_segment_decimal_point_one(LCDx, 6, 0);
	dat %= 100;
	temp_dat = dat / 10;
	if ((temp_dat == 0) && (dat_flag == 0))
	{
		if (isfill != 0)
		{
			lcd_segment_data_on_one(LCDx, 7, 0);
		}
		else
		{
			lcd_segment_data_off_one(LCDx, 7);
		}
	}
	else
	{
		dat_flag = 1;
		lcd_segment_data_on_one(LCDx, 7, temp_dat);
	}
	lcd_segment_decimal_point_one(LCDx, 7, 0);
	temp_dat = dat % 10;
	if ((temp_dat == 0) && (dat_flag == 0))
	{
		if (isfill != 0)
		{
			lcd_segment_data_on_one(LCDx, 8, 0);
		}
		else
		{
			lcd_segment_data_off_one(LCDx, 8);
		}
	}
	else
	{
		dat_flag = 1;
		lcd_segment_data_on_one(LCDx, 8, temp_dat);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_integer_two(LCD_HandleType* LCDx, uint32_t dat, uint8_t isfill)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_integer_three(LCD_HandleType* LCDx, uint32_t dat, uint8_t isfill)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_integer(LCD_HandleType* LCDx, uint32_t dat, uint8_t isfill)
{
	if ((LCDx != NULL) && (LCDx == LCD_TASK_ONE))
	{
		return lcd_segment_show_integer_one(LCDx,dat,isfill);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_TWO))
	{
		return lcd_segment_show_integer_two(LCDx, dat, isfill);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_THREE))
	{
		return lcd_segment_show_integer_three(LCDx, dat, isfill);
	}
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ʾ������,С�������5λ
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float_p5f_one(LCD_HandleType *LCDx, float dat)
{
	//---ǿ��ת��Ϊ����
	uint16_t temp_integer = (uint16_t)dat;
	uint8_t temp_dat = temp_integer / 100;
	uint8_t dat_flag = 0;
	if (temp_dat == 0)
	{
		lcd_segment_data_off_one(LCDx, 1);
	}
	else
	{
		dat_flag = 1;
		lcd_segment_data_on_one(LCDx, 1, temp_dat);
	}
	temp_integer %= 100;
	temp_dat = temp_integer / 10;
	if ((temp_dat == 0)&&(dat_flag==0))
	{
		lcd_segment_data_off_one(LCDx, 2);
	}
	else
	{
		dat_flag = 1;
		lcd_segment_data_on_one(LCDx, 2, temp_dat);
	}
	temp_dat = temp_integer % 10;
	if ((temp_dat == 0) && (dat_flag == 0))
	{
		lcd_segment_data_off_one(LCDx, 3);
	}
	else
	{
		dat_flag = 1;
		lcd_segment_data_on_one(LCDx, 3, temp_dat);
	}
	lcd_segment_decimal_point_one(LCDx, 3, 1);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer= (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on_one(LCDx, 4, 0);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 4, temp_dat);
	}
	lcd_segment_decimal_point_one(LCDx, 4, 0);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer = (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on_one(LCDx, 5, 0);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 5, temp_dat);
	}
	lcd_segment_decimal_point_one(LCDx, 5, 0);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer = (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on_one(LCDx, 6, 0);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 6, temp_dat);
	}
	lcd_segment_decimal_point_one(LCDx, 6, 0);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer = (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on_one(LCDx, 7, 0);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 7, temp_dat);
	}
	lcd_segment_decimal_point_one(LCDx, 7, 0);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer = (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on_one(LCDx, 8, 0);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 8, temp_dat);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float_p5f_two(LCD_HandleType* LCDx, float dat)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float_p5f_three(LCD_HandleType* LCDx, float dat)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float_p5f(LCD_HandleType* LCDx, float dat)
{
	if ((LCDx != NULL) && (LCDx == LCD_TASK_ONE))
	{
		return lcd_segment_show_float_p5f_one(LCDx, dat);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_TWO))
	{
		return lcd_segment_show_float_p5f_two(LCDx, dat);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_THREE))
	{
		return lcd_segment_show_float_p5f_three(LCDx, dat);
	}
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ʾ������,С�������4λ
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float_p4f_one(LCD_HandleType *LCDx, float dat)
{
	//---ǿ��ת��Ϊ����
	uint16_t temp_integer = (uint16_t)dat;
	uint8_t temp_dat = temp_integer / 1000;
	uint8_t dat_flag = 0;
	if (temp_dat == 0)
	{
		lcd_segment_data_off_one(LCDx, 1);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 1, temp_dat);
	}
	temp_integer %= 1000;
	temp_dat = temp_integer / 100;
	if (temp_dat == 0)
	{
		lcd_segment_data_off_one(LCDx, 2);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 2, temp_dat);
	}
	temp_integer %= 100;
	temp_dat = temp_integer / 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_off_one(LCDx, 3);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 3, temp_dat);
	}
	lcd_segment_decimal_point_one(LCDx, 3, 0);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_off_one(LCDx, 4);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 4, temp_dat);
	}
	lcd_segment_decimal_point_one(LCDx, 4, 1);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer = (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on_one(LCDx, 5, 0);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 5, temp_dat);
	}
	lcd_segment_decimal_point_one(LCDx, 5, 0);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer = (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on_one(LCDx, 6, 0);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 6, temp_dat);
	}
	lcd_segment_decimal_point_one(LCDx, 6, 0);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer = (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on_one(LCDx, 7, 0);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 7, temp_dat);
	}
	lcd_segment_decimal_point_one(LCDx, 7, 0);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer = (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on_one(LCDx, 8, 0);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 8, temp_dat);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float_p4f_two(LCD_HandleType* LCDx, float dat)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float_p4f_three(LCD_HandleType* LCDx, float dat)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float_p4f(LCD_HandleType* LCDx, float dat)
{
	if ((LCDx != NULL) && (LCDx == LCD_TASK_ONE))
	{
		return lcd_segment_show_float_p4f_one(LCDx, dat);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_TWO))
	{
		return lcd_segment_show_float_p4f_two(LCDx, dat);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_THREE))
	{
		return lcd_segment_show_float_p4f_three(LCDx, dat);
	}
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ʾ������,С�������3λ
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float_p3f_one(LCD_HandleType *LCDx, float dat)
{
	//---ǿ��ת��Ϊ����
	uint32_t temp_integer = (uint32_t)dat;
	uint8_t temp_dat = temp_integer / 10000;
	uint8_t dat_flag = 0;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(LCDx, 1);
	}
	else
	{
		lcd_segment_data_on(LCDx, 1, temp_dat);
	}
	temp_integer %= 10000;
	temp_dat = temp_integer / 1000;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(LCDx, 2);
	}
	else
	{
		lcd_segment_data_on(LCDx, 2, temp_dat);
	}
	temp_integer %= 1000;
	temp_dat = temp_integer / 100;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(LCDx, 3);
	}
	else
	{
		lcd_segment_data_on(LCDx, 3, temp_dat);
	}
	lcd_segment_decimal_point(LCDx, 3, 0);
	temp_integer %= 100;
	temp_dat = temp_integer / 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(LCDx, 4);
	}
	else
	{
		lcd_segment_data_on(LCDx, 4, temp_dat);
	}
	lcd_segment_decimal_point(LCDx, 4, 0);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on(LCDx, 5, 0);
	}
	else
	{
		lcd_segment_data_on(LCDx, 5, temp_dat);
	}
	lcd_segment_decimal_point(LCDx, 5, 1);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer = (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on(LCDx, 6, 0);
	}
	else
	{
		lcd_segment_data_on(LCDx, 6, temp_dat);
	}
	lcd_segment_decimal_point(LCDx, 6, 0);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer = (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on(LCDx, 7, 0);
	}
	else
	{
		lcd_segment_data_on(LCDx, 7, temp_dat);
	}
	lcd_segment_decimal_point(LCDx, 7, 0);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer = (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on(LCDx, 8, 0);
	}
	else
	{
		lcd_segment_data_on(LCDx, 8, temp_dat);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float_p3f_two(LCD_HandleType* LCDx, float dat)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float_p3f_three(LCD_HandleType* LCDx, float dat)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float_p3f(LCD_HandleType* LCDx, float dat)
{
	if ((LCDx != NULL) && (LCDx == LCD_TASK_ONE))
	{
		return lcd_segment_show_float_p3f_one(LCDx, dat);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_TWO))
	{
		return lcd_segment_show_float_p3f_two(LCDx, dat);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_THREE))
	{
		return lcd_segment_show_float_p3f_three(LCDx, dat);
	}
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ʾ������,С�������2λ
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float_p2f_one(LCD_HandleType *LCDx, float dat)
{
	//---ǿ��ת��Ϊ����
	uint32_t temp_integer = (uint32_t)dat;
	uint8_t temp_dat = temp_integer / 100000;
	uint8_t dat_flag = 0;
	if (temp_dat == 0)
	{
		lcd_segment_data_off_one(LCDx, 1);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 1, temp_dat);
	}
	temp_integer %= 100000;
	temp_dat = temp_integer / 10000;
	if (temp_dat == 0)
	{
		lcd_segment_data_off_one(LCDx, 2);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 2, temp_dat);
	}
	temp_integer %= 10000;
	temp_dat = temp_integer / 1000;
	if (temp_dat == 0)
	{
		lcd_segment_data_off_one(LCDx, 3);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 3, temp_dat);
	}
	lcd_segment_decimal_point_one(LCDx, 3, 0);
	temp_integer %= 1000;
	temp_dat = temp_integer / 100;
	if (temp_dat == 0)
	{
		lcd_segment_data_off_one(LCDx, 4);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 4, temp_dat);
	}
	lcd_segment_decimal_point_one(LCDx, 4, 0);
	temp_integer %= 100;
	temp_dat = temp_integer / 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_off_one(LCDx, 5);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 5, temp_dat);
	}
	lcd_segment_decimal_point_one(LCDx, 5, 0);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on_one(LCDx, 6, 0);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 6, temp_dat);
	}
	lcd_segment_decimal_point_one(LCDx, 6, 1);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer = (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on_one(LCDx, 7, 0);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 7, temp_dat);
	}
	lcd_segment_decimal_point_one(LCDx, 7, 0);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer = (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on_one(LCDx, 8, 0);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 8, temp_dat);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float_p2f_two(LCD_HandleType* LCDx, float dat)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float_p2f_three(LCD_HandleType* LCDx, float dat)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float_p2f(LCD_HandleType* LCDx, float dat)
{
	if ((LCDx != NULL) && (LCDx == LCD_TASK_ONE))
	{
		return lcd_segment_show_float_p2f_one(LCDx, dat);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_TWO))
	{
		return lcd_segment_show_float_p2f_two(LCDx, dat);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_THREE))
	{
		return lcd_segment_show_float_p2f_three(LCDx, dat);
	}
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ʾ������,С�������1λ
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float_p1f_one(LCD_HandleType *LCDx, float dat)
{
	//---ǿ��ת��Ϊ����
	uint32_t temp_integer = (uint32_t)dat;
	uint8_t temp_dat = temp_integer / 1000000;
	uint8_t dat_flag = 0;
	if (temp_dat == 0)
	{
		lcd_segment_data_off_one(LCDx, 1);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 1, temp_dat);
	}
	temp_integer %= 1000000;
	temp_dat = temp_integer / 100000;
	if (temp_dat == 0)
	{
		lcd_segment_data_off_one(LCDx, 2);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 2, temp_dat);
	}
	temp_integer %= 100000;
	temp_dat = temp_integer / 10000;
	if (temp_dat == 0)
	{
		lcd_segment_data_off_one(LCDx, 3);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 3, temp_dat);
	}
	lcd_segment_decimal_point_one(LCDx, 3, 0);
	temp_integer %= 10000;
	temp_dat = temp_integer / 1000;
	if (temp_dat == 0)
	{
		lcd_segment_data_off_one(LCDx, 4);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 4, temp_dat);
	}
	lcd_segment_decimal_point_one(LCDx, 4, 0);
	temp_integer %= 1000;
	temp_dat = temp_integer / 100;
	if (temp_dat == 0)
	{
		lcd_segment_data_off_one(LCDx, 5);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 5, temp_dat);
	}
	lcd_segment_decimal_point_one(LCDx, 5, 0);
	temp_integer %= 100;
	temp_dat = temp_integer / 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_off_one(LCDx, 6);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 6, temp_dat);
	}
	lcd_segment_decimal_point_one(LCDx, 6, 0);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on_one(LCDx, 7, 0);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 7, temp_dat);
	}
	lcd_segment_decimal_point_one(LCDx, 7,1);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer = (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on_one(LCDx, 8, 0);
	}
	else
	{
		lcd_segment_data_on_one(LCDx, 8, temp_dat);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float_p1f_two(LCD_HandleType* LCDx, float dat)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float_p1f_three(LCD_HandleType* LCDx, float dat)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float_p1f(LCD_HandleType* LCDx, float dat)
{
	if ((LCDx != NULL) && (LCDx == LCD_TASK_ONE))
	{
		return lcd_segment_show_float_p1f_one(LCDx, dat);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_TWO))
	{
		return lcd_segment_show_float_p1f_two(LCDx, dat);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_THREE))
	{
		return lcd_segment_show_float_p1f_three(LCDx, dat);
	}
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ʾ��������������С���������λС����������1,2,3,4,5λС��
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float_one(LCD_HandleType *LCDx, float dat, uint8_t pnum)
{
	//---�жϱ�����С����λ��
	switch (pnum)
	{
		case 1:
		{
			lcd_segment_show_float_p1f_one(LCDx, dat);
			break;
		}
		case 2:
		{
			lcd_segment_show_float_p2f_one(LCDx, dat);
			break;
		}
		case 3:
		{
			lcd_segment_show_float_p3f_one(LCDx, dat);
			break;
		}
		case 4:
		{
			lcd_segment_show_float_p4f_one(LCDx, dat);
			break;
		}
		case 5:
		{
			lcd_segment_show_float_p5f_one(LCDx, dat);
			break;
		}
		default:
		{
			lcd_segment_show_integer_one(LCDx, dat,0);
			break;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float_two(LCD_HandleType* LCDx, float dat, uint8_t pnum)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float_three(LCD_HandleType* LCDx, float dat, uint8_t pnum) 
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float(LCD_HandleType* LCDx, float dat, uint8_t pnum)
{
	if ((LCDx != NULL) && (LCDx == LCD_TASK_ONE))
	{
		return lcd_segment_show_float_one(LCDx, dat, pnum);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_TWO))
	{
		return lcd_segment_show_float_two(LCDx, dat, pnum);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_THREE))
	{
		return lcd_segment_show_float_three(LCDx, dat, pnum);
	}
	return ERROR_2;
}
///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ʾ�¶Ȳ����2λС�������ж��Ƿ��Ը���ģʽ��ʾ
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_diff_temperature_one(LCD_HandleType *LCDx, float temperature, uint8_t positive,uint8_t istestmode)
{
	//---��ʾ�²����
	lcd_segment_text_title_on_one(LCDx, TEXT_DWT);
	//---��ʾ�²�ֵ
	if (istestmode != 0)
	{
		lcd_segment_show_float_p4f_one(LCDx, temperature);
		istestmode = 2;
	}
	else
	{
		lcd_segment_show_float_p2f_one(LCDx, temperature);
		istestmode = 0;
	}
	//---У���Ƿ��Ǹ���
	if (positive!=0)
	{
		if (temperature<10.0f)
		{
			lcd_segment_data_on_one(LCDx, 5-istestmode, '-');
		}
		else
		{
			lcd_segment_data_on_one(LCDx, 4-istestmode, '-');
		}
	}
	//---��ʾ�²λK
	lcd_segment_unit_title_on_one(LCDx, UNIT_K);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_diff_temperature_two(LCD_HandleType* LCDx, float temperature, uint8_t positive, uint8_t istestmode)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_diff_temperature_three(LCD_HandleType* LCDx, float temperature, uint8_t positive, uint8_t istestmode)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_diff_temperature(LCD_HandleType* LCDx, float temperature, uint8_t positive, uint8_t istestmode)
{
	if ((LCDx != NULL) && (LCDx == LCD_TASK_ONE))
	{
		return lcd_segment_show_diff_temperature_one(LCDx, temperature, positive, istestmode);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_TWO))
	{
		return lcd_segment_show_diff_temperature_two(LCDx, temperature, positive, istestmode);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_THREE))
	{
		return lcd_segment_show_diff_temperature_three(LCDx, temperature, positive, istestmode);
	}
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ʾˮ�£�����2λС�������ж��ǽ�ˮ�¶Ⱥ��³�ˮ�¶�
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_temperature_one(LCD_HandleType *LCDx, float temperature, uint8_t isin, uint8_t istestmode)
{
	//---��ʾ�¶ȱ���
	lcd_segment_text_title_on_one(LCDx, ((isin!=0)? TEXT_IWT: TEXT_OWT));
	//---��ʾ�²�ֵ
	if (istestmode!=0)
	{
		lcd_segment_show_float_p4f_one(LCDx, temperature);
	}
	else
	{
		lcd_segment_show_float_p2f_one(LCDx, temperature);
	}
	//---��ʾ�¶ȵ�λC
	lcd_segment_unit_title_on_one(LCDx, UNIT_C);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_temperature_two(LCD_HandleType* LCDx, float temperature, uint8_t isin, uint8_t istestmode)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_temperature_three(LCD_HandleType* LCDx, float temperature, uint8_t isin, uint8_t istestmode)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_temperature(LCD_HandleType* LCDx, float temperature, uint8_t isin, uint8_t istestmode)
{
	if ((LCDx != NULL) && (LCDx == LCD_TASK_ONE))
	{
		return lcd_segment_show_temperature_one(LCDx, temperature, isin, istestmode);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_TWO))
	{
		return lcd_segment_show_temperature_two(LCDx, temperature, isin, istestmode);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_THREE))
	{
		return lcd_segment_show_temperature_three(LCDx, temperature, isin, istestmode);
	}
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ʾ���������ж��ǲ��ǲ���ģʽ
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_flow_one(LCD_HandleType *LCDx, float flow,uint8_t istestmode)
{
	//---��ʾ�¶ȱ���
	lcd_segment_text_title_on_one(LCDx, TEXT_FLOW);
	//---��ʾ�²�ֵ
	if (istestmode != 0)
	{
		lcd_segment_show_float_p4f_one(LCDx, flow);
	}
	else
	{
		lcd_segment_show_float_p2f_one(LCDx, flow);
	}
	//---��ʾ������λm3/h
	lcd_segment_unit_title_on_one(LCDx, UNIT_M3H);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_flow_two(LCD_HandleType* LCDx, float flow, uint8_t istestmode)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_flow_three(LCD_HandleType* LCDx, float flow, uint8_t istestmode)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_flow(LCD_HandleType* LCDx, float flow, uint8_t istestmode)
{
	if ((LCDx != NULL) && (LCDx == LCD_TASK_ONE))
	{
		return lcd_segment_show_flow_one(LCDx, flow, istestmode);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_TWO))
	{
		return lcd_segment_show_flow_two(LCDx, flow, istestmode);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_THREE))
	{
		return lcd_segment_show_flow_three(LCDx, flow, istestmode);
	}
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ʾ��ַ��Ϣ
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_addr_one(LCD_HandleType *LCDx, uint32_t addr)
{
	//---��ʾ��ַ����
	lcd_segment_text_title_on_one(LCDx, TEXT_ADDR);
	//---��ʾ��ַ��Ϣ
	lcd_segment_show_integer_one(LCDx, addr,0);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_addr_two(LCD_HandleType* LCDx, uint32_t addr)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_addr_three(LCD_HandleType* LCDx, uint32_t addr)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_addr(LCD_HandleType* LCDx, uint32_t addr)
{
	if ((LCDx != NULL) && (LCDx == LCD_TASK_ONE))
	{
		return lcd_segment_show_addr_one(LCDx, addr);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_TWO))
	{
		return lcd_segment_show_addr_two(LCDx, addr);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_THREE))
	{
		return lcd_segment_show_addr_three(LCDx, addr);
	}
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ʾʱ����Ϣ
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_rtc_one(LCD_HandleType *LCDx, RTC_TimeType *rtcx)
{
	//---��ʾʱ�����
	lcd_segment_text_title_on_one(LCDx, TEXT_RTC);
	//---��ʾʱ����Ϣ
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_rtc_two(LCD_HandleType* LCDx, RTC_TimeType* rtcx)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_rtc_three(LCD_HandleType* LCDx, RTC_TimeType* rtcx)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_rtc(LCD_HandleType* LCDx, RTC_TimeType* rtcx)
{
	if ((LCDx != NULL) && (LCDx == LCD_TASK_ONE))
	{
		return lcd_segment_show_rtc_one(LCDx, rtcx);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_TWO))
	{
		return lcd_segment_show_rtc_two(LCDx, rtcx);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_THREE))
	{
		return lcd_segment_show_rtc_three(LCDx, rtcx);
	}
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: �ۻ�ʱ��
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_acc_rtc_one(LCD_HandleType *LCDx, uint32_t accrtc)
{
	//---��ʾʱ�����
	lcd_segment_text_title_on_one(LCDx, TEXT_ACC_RTC);
	//---�ۻ�ʱ��
	lcd_segment_show_integer_one(LCDx, accrtc,0);
	//---��ʾʱ�䵥λh
	lcd_segment_unit_title_on_one(LCDx, UNIT_KW_H);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_acc_rtc_two(LCD_HandleType* LCDx, uint32_t accrtc)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_acc_rtc_three(LCD_HandleType* LCDx, uint32_t accrtc)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_acc_rtc(LCD_HandleType* LCDx, uint32_t accrtc)
{
	if ((LCDx != NULL) && (LCDx == LCD_TASK_ONE))
	{
		return lcd_segment_show_acc_rtc_one(LCDx, accrtc);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_TWO))
	{
		return lcd_segment_show_acc_rtc_two(LCDx, accrtc);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_THREE))
	{
		return lcd_segment_show_acc_rtc_three(LCDx, accrtc);
	}
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ʾ����
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_power_one(LCD_HandleType *LCDx, float power, uint8_t istestmode)
{
	//---��ʾ�¶ȱ���
	lcd_segment_text_title_on_one(LCDx, TEXT_POWER);
	//---��ʾ�²�ֵ
	if (istestmode != 0)
	{
		lcd_segment_show_float_p4f_one(LCDx, power);
	}
	else
	{
		lcd_segment_show_float_p2f_one(LCDx, power);
	}
	//---��ʾ������λm3/h
	lcd_segment_unit_title_on_one(LCDx, UNIT_KW);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_power_two(LCD_HandleType* LCDx, float power, uint8_t istestmode)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_power_three(LCD_HandleType* LCDx, float power, uint8_t istestmode)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_power(LCD_HandleType* LCDx, float power, uint8_t istestmode)
{
	if ((LCDx != NULL) && (LCDx == LCD_TASK_ONE))
	{
		return lcd_segment_show_power_one(LCDx, power,istestmode);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_TWO))
	{
		return lcd_segment_show_power_two(LCDx, power,istestmode);
	}
	if ((LCDx != NULL) && (LCDx == LCD_TASK_THREE))
	{
		return lcd_segment_show_power_three(LCDx, power,istestmode);
	}
	return ERROR_2;
}