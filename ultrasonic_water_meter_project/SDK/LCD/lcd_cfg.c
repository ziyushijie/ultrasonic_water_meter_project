#include "lcd_cfg.h"

//===显示文本
uint16_t g_lcd_segment_text = TEXT_NONE;
//===显示单位
uint16_t g_lcd_segment_unit = UNIT_NONE;

//===LCD断码表
//0,1,2,3,4,5,6,7,8,9,A,b,C,d,E,F,i,n,o,r,t,u,-
const uint8_t g_lcd_segment_display_table[23] = {
	0x5F,0x06,0x3D,0x2F,0x66,0x6B,0x7B,0x0E,0x7F,0x6F,
	0x7E,0x73,0x59,0x37,0x79,0x78,0x10,0x32,0x33,0x30,
	0x71,0x13,0x20
};

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 断码液晶LCD初始化
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_init(void)
{
	//===26PIN的LCD的PIN对应的端口信息
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
	
	//---不使能LCD时钟
	LCDON = 0;
	//---外部分压电阻模式，A波形模式，4个时间片，1/3偏压法
	LCDM0 = _00_LCD_DISPLAY_WAVEFORM_A | _0D_LCD_DISPLAY_MODE1;
	LCDM0 |= _00_LCD_VOLTAGE_MODE_EXTERNAL;

	//---配置断码器用到的端口

	//---不使能上拉电阻
	PU1 &= 0xF0;
	PU2 &= 0x3F;
	PU3 &= 0xF0;
	PU5 &= 0x64;
	PU7 &= 0x0E;

	//---设置为输入模式
	POM5 &= 0xE7;
	PIM5 &= 0xF7;

	//---设置端口为数字输入输出
	PMC1 &= 0xF0;
	P1 &= 0xF0;
	PM1 &= 0xF0;

	PMC2 &= 0x3F;
	PM2 &= 0x3F;
	P2 &= 0x3F;

	PM3&= 0xF0;
	P3 &= 0xF0;

	PM3 &= 0xF0;
	P3 &= 0xF0;

	PM5 &= 0x67;
	P5 &= 0x67;

	PM7 &= 0x0E;
	P7 &= 0x0E;

	//---断码控制端口
	PFSEG0 |= 0xF0;
	PFSEG1 |= 0xFF;
	PFSEG2 |= 0xFF;
	PFSEG3 |= 0xBB;
	PFSEG4 |= 0xFF;
	PFSEG5 &= 0x00;
	PFSEG6 &= 0x00;


	//---显示A图形区域
	LCDM1 |= _00_LCD_DISPLAY_PATTERN_A;
	//---限定LCD的时钟频率，过快时钟频率会有虚影，
	LCDC0 = _07_LCD_CLOCK_FSUB_FIL_8;//_05_LCD_CLOCK_FSUB_FIL_6;

	lcd_segment_show_all();

	return lcd_segment_enable();
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 打开显示
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_enable(void)
{
	SCOC = 1;
	LCDON = 1;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 关闭显示
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_disable(void)
{
	SCOC = 0;
	LCDON = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_clear(void)
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
	return OK_0;

}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 显示所有
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_all(void)
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
//////函		数:
//////功		能: 显示功能抬头打开
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_text_title_on(uint16_t text )
{
	if (text!= g_lcd_segment_text)
	{
		lcd_segment_text_title_off(g_lcd_segment_text);
		g_lcd_segment_text = text;
	}
	switch (text)
	{
		case TEXT_ACC:		//---累积
		{
			SEG0 |= 0x08;
			break;
		}
		case TEXT_HEAT:		//---热量
		{
			SEG2 |= 0x08;
			break;
		}
		case TEXT_ACC_HEAT:		//---热量
		{
			SEG0 |= 0x08;
			SEG2 |= 0x08;
			break;
		}
		case TEXT_COOL:		//---冷量
		{
			SEG7 |= 0x08;
			break;
		}
		case TEXT_ACC_COOL:		//---冷量
		{
			SEG0 |= 0x08;
			SEG7 |= 0x08;
			break;
		}
		case TEXT_FLOW:		//---流量
		{
			SEG11 |= 0x08;
			break;
		}
		case TEXT_ACC_FLOW:		//---流量
		{
			SEG0 |= 0x08;
			SEG11 |= 0x08;
			break;
		}
		case TEXT_IWT:		//---进水温度
		{
			SEG16 |= 0x08;
			break;
		}
		case TEXT_OWT:		//---回水温度
		{
			SEG20 |= 0x08;
			break;
		}
		case TEXT_DWT:		//---温差
		{
			SEG33|= 0x08;
			break;
		}
		case TEXT_TEST:		//---检定模式
		{
			SEG38 |= 0x08;
			break;
		}
		case TEXT_ALARM:	//---报警
		{
			SEG37 |= 0x08;
			break;
		}
		case TEXT_POWER:	//---功率
		{
			SEG36 |= 0x08;
			break;
		}
		case TEXT_ADDR:		//---地址
		{
			SEG35 |= 0x08;
			break;
		}
		case TEXT_DATE:		//---日期
		{
			SEG34 |= 0x08;
			break;
		}
		case TEXT_RTC:		//---时间
		{
			SEG33 |= 0x01;
			break;
		}
		case TEXT_ACC_RTC:		//---时间
		{
			SEG0 |= 0x08;
			SEG33 |= 0x01;
			break;
		}
		case TEXT_BATTERY:	//---电池
		{
			SEG33 |= 0x02;
			break;
		}
		default:
		{
			lcd_segment_clear();
			break;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 显示功能抬头关闭
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_text_title_off(uint16_t text)
{
	switch (text)
	{
		case TEXT_NONE:
		{
			break;
		}
		case TEXT_ACC:		//---累积
		{
			SEG0 &= 0xF7;
			break;
		}
		case TEXT_HEAT:		//---热量
		{
			SEG2 &= 0xF7;
			break;
		}
		case TEXT_ACC_HEAT:		//---累积热量
		{
			SEG0 &= 0xF7;
			SEG2 &= 0xF7;
			break;
		}
		case TEXT_COOL:		//---冷量
		{
			SEG7 &= 0xF7;
			break;
		}
		case TEXT_ACC_COOL:		//---累积冷量
		{
			SEG0 &= 0xF7;
			SEG7 &= 0xF7;
			break;
		}
		case TEXT_FLOW:		//---流量
		{
			SEG11 &= 0xF7;
			break;
		}
		case TEXT_ACC_FLOW:		//---累积流量
		{
			SEG0 &= 0xF7;
			SEG11 &= 0xF7;
			break;
		}
		case TEXT_IWT:		//---进水温度
		{
			SEG16 &= 0xF7;
			break;
		}
		case TEXT_OWT:		//---回水温度
		{
			SEG20 &= 0xF7;
			break;
		}
		case TEXT_DWT:		//---温差
		{
			SEG33 &= 0xF7;
			break;
		}
		case TEXT_TEST:		//---检定模式
		{
			SEG38 &= 0xF7;
			break;
		}
		case TEXT_ALARM:	//---报警
		{
			SEG37 &= 0xF7;
			break;
		}
		case TEXT_POWER:	//---功率
		{
			SEG36 &= 0xF7;
			break;
		}
		case TEXT_ADDR:		//---地址
		{
			SEG35 &= 0xF7;
			break;
		}
		case TEXT_DATE:		//---日期
		{
			SEG34 &= 0xF7;
			break;
		}
		case TEXT_RTC:		//---时间
		{
			SEG33 &= 0xF7;
			break;
		}
		case TEXT_ACC_RTC:		//---累积时间
		{
			SEG0 &= 0xF7;
			SEG33 &= 0xF7;
			break;
		}
		case TEXT_BATTERY:	//---电池
		{
			SEG33 &= 0xFD;
			break;
		}
		default:
		{
			lcd_segment_clear();
			break;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 显示单位抬头开启
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_unit_title_on(uint16_t unit)
{
	if (unit != g_lcd_segment_unit)
	{
		lcd_segment_unit_title_off(g_lcd_segment_unit);
		g_lcd_segment_unit = unit;
	}
	//---根据单位类型显示指定的单位
	switch (unit)
	{
		case UNIT_K :		//---显示单位K
		{
			SEG34 |= 0x02;
			break;
		}
		case UNIT_C:		//---显示单位℃
		{
			SEG34 |= 0x04;
			break;
		}
		case UNIT_KW:		//---显示千瓦kW
		{
			SEG35 |= 0x02;
			break;
		}
		case UNIT_KW_D:		//---显示千瓦kW小数点后的点
		{
			SEG35 |= 0x04;
			break;
		}
		case UNIT_KWH:		//---显示千瓦kW.h
		{
			SEG35 |= 0x06;
			SEG36 |= 0x04;
			break;
		}
		case UNIT_KW_H:		//---显示千瓦kW小数点后的h
		{
			SEG36 |= 0x04;
			break;
		}
		case UNIT_MWH:		//---显示兆瓦MW.h
		{
			SEG36 |= 0x02;
			break;
		}
		case UNIT_GJ:		//---显示GJ
		{
			SEG37 |= 0x02;
			break;
		}
		case UNIT_MJ:		//---显示MJ
		{
			SEG37 |= 0x04;
			break;
		}
		case UNIT_GJMJ:		//---显示GJMJ
		{
			SEG37 |= 0x06;
			break;
		}
		case UNIT_M3:		//---显示m3
		{
			SEG38 |= 0x02;
			break;
		}
		case UNIT_M3_H:		//---显示m3小数点后的/h
		{
			SEG38 |= 0x04;
			break;
		}
		case UNIT_M3H:		//---显示m3/h
		{
			SEG38 |= 0x06;
			break;
		}
		default:
		{
			lcd_segment_clear();
			break;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 显示单位抬头关闭
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_unit_title_off(uint16_t unit)
{
	//---根据单位类型显示指定的单位
	switch (unit)
	{
		case UNIT_NONE:
		{
			break;
		}
		case UNIT_K:		//---显示单位K
		{
			SEG34 &= 0xFD;
			break;
		}
		case UNIT_C:		//---显示单位℃
		{
			SEG34 &= 0xFB;
			break;
		}
		case UNIT_KW:		//---显示千瓦kW
		{
			SEG35 &= 0xFD;
			break;
		}
		case UNIT_KW_D:		//---显示千瓦kW小数点后的点
		{
			SEG35 &= 0xFB;
			break;
		}
		case UNIT_KWH:		//---显示千瓦kW.h
		{
			SEG35 &= 0xF9;
			SEG36 &= 0xFB;
			break;
		}
		case UNIT_KW_H:		//---显示千瓦kW小数点后的h
		{
			SEG36 &= 0xFB;
			break;
		}
		case UNIT_MWH:		//---显示兆瓦MW.h
		{
			SEG36 &= 0xFD;
			break;
		}
		case UNIT_GJ:		//---显示GJ
		{
			SEG37 &= 0xFD;
			break;
		}
		case UNIT_MJ:		//---显示MJ
		{
			SEG37 &= 0xFB;
			break;
		}
		case UNIT_GJMJ:		//---显示GJMJ
		{
			SEG37 &= 0xF9;
			break;
		}
		case UNIT_M3:		//---显示m3
		{
			SEG38 &= 0xFD;
			break;
		}
		case UNIT_M3_H:		//---显示m3小数点后的/h
		{
			SEG38 &= 0xFB;
			break;
		}
		case UNIT_M3H:		//---显示m3/h
		{
			SEG38 &= 0xF9;
			break;
		}
		default:
		{
			lcd_segment_clear();
			break;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 在指定位置显示小数点，从左到右
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_decimal_point(uint16_t index, uint8_t isshow)
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
//////函		数:
//////功		能: 在指定位置显示数据开启，从左到右
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_data_on(uint16_t index, char dat )
{
	uint8_t temp_data = 0;
	uint8_t temp_seg = 0;
	switch (dat)
	{
		case 0:
		case '0':
		{
			temp_data = g_lcd_segment_display_table[0];
			break;
		}
		case 1:
		case '1':
		{
			temp_data = g_lcd_segment_display_table[1];
			break;
		}
		case 2:
		case '2':
		{
			temp_data = g_lcd_segment_display_table[2];
			break;
		}
		case 3:
		case '3':
		{
			temp_data = g_lcd_segment_display_table[3];
			break;
		}
		case 4:
		case '4':
		{
			temp_data = g_lcd_segment_display_table[4];
			break;
		}
		case 5:
		case '5':
		{
			temp_data = g_lcd_segment_display_table[5];
			break;
		}
		case 6:
		case '6':
		{
			temp_data = g_lcd_segment_display_table[6];
			break;
		}
		case 7:
		case '7':
		{
			temp_data = g_lcd_segment_display_table[7];
			break;
		}
		case 8:
		case '8':
		{
			temp_data = g_lcd_segment_display_table[8];
			break;
		}
		case 9:
		case '9':
		{
			temp_data = g_lcd_segment_display_table[9];
			break;
		}
		case 10:
		case 'a':
		case 'A':
		{
			temp_data = g_lcd_segment_display_table[10];
			break;
		}
		case 11:
		case 'b':
		case 'B':
		{
			temp_data = g_lcd_segment_display_table[11];
			break;
		}
		case 12:
		case 'c':
		case 'C':
		{
			temp_data = g_lcd_segment_display_table[12];
			break;
		}
		case 13:
		case 'd':
		case 'D':
		{
			temp_data = g_lcd_segment_display_table[13];
			break;
		}
		case 14:
		case 'e':
		case 'E':
		{
			temp_data = g_lcd_segment_display_table[14];
			break;
		}
		case 15:
		case 'f':
		case 'F':
		{
			temp_data = g_lcd_segment_display_table[15];
			break;
		}
		case 'i':
		case 'I':
		{
			temp_data = g_lcd_segment_display_table[16];
			break;
		}
		case 'n':
		case 'N':
		{
			temp_data = g_lcd_segment_display_table[17];
			break;
		}
		case 'o':
		case 'O':
		{
			temp_data = g_lcd_segment_display_table[18];
			break;
		}
		case 'r':
		case 'R':
		{
			temp_data = g_lcd_segment_display_table[19];
			break;
		}
		case 't':
		case 'T':
		{
			temp_data = g_lcd_segment_display_table[20];
			break;
		}
		case 'u':
		case 'U':
		{
			temp_data = g_lcd_segment_display_table[21];
			break;
		}
		case '-':
		{
			temp_data = g_lcd_segment_display_table[22];
			break;
		}
		default:
		{
			return lcd_segment_clear();
			//break;
		}
	}
	//---判断显示内容，从左到右，依次是1,2,3,4,5,6,7,8
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
			lcd_segment_clear();
			break;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 在指定位置显示数据关闭，从左到右
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_data_off(uint16_t index)
{
	//---判断显示内容，从左到右，依次是1,2,3,4,5,6,7,8
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
			lcd_segment_clear();
			break;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 进入标定模式
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_test_enter(void)
{
	BLON = 1;
	SEG38 |= 0x08;
	SEG38 &= 0x7F;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 退出标定模式
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_test_exit(void)
{
	BLON = 0;
	LCDSEL = 0;
	SEG38 &= 0x77;
	return OK_0;
}


//uint8_t temp_dat = 0;
///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 显示整数
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_integer(uint32_t dat)
{
	uint8_t temp_dat = dat / 10000000;
	//temp_dat = dat / 10000000;
	if (temp_dat==0)
	{
		lcd_segment_data_off(1);
	}
	else
	{
		lcd_segment_data_on(1, temp_dat);
	}
	dat %= 10000000;
	temp_dat = dat / 1000000;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(2);
	}
	else
	{
		lcd_segment_data_on(2, temp_dat);
	}
	dat %= 1000000;
	temp_dat = dat / 100000;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(3);
	}
	else
	{
		lcd_segment_data_on(3, temp_dat);
	}
	lcd_segment_decimal_point(3, 0);
	dat %= 100000;
	temp_dat = dat / 10000;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(4);
	}
	else
	{
		lcd_segment_data_on(4, temp_dat);
	}
	lcd_segment_decimal_point(2, 0);
	dat %= 10000;
	temp_dat = dat / 1000;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(5);
	}
	else
	{
		lcd_segment_data_on(5, temp_dat);
	}
	lcd_segment_decimal_point(5, 0);
	dat %= 1000;
	temp_dat = dat / 100;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(6);
	}
	else
	{
		lcd_segment_data_on(6, temp_dat);
	}
	lcd_segment_decimal_point(6, 0);
	dat %= 100;
	temp_dat = dat / 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(7);
	}
	else
	{
		lcd_segment_data_on(7, temp_dat);
	}
	lcd_segment_decimal_point(7, 0);
	temp_dat = dat % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(8);
	}
	else
	{
		lcd_segment_data_on(8, temp_dat);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 显示浮点数,小数点后保留5位
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float_p5f(float dat)
{
	//---强制转换为整数
	uint16_t temp_integer = (uint16_t)dat;
	uint8_t temp_dat = temp_integer / 100;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(1);
	}
	else
	{
		lcd_segment_data_on(1, temp_dat);
	}
	temp_integer %= 100;
	temp_dat = temp_integer / 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(2);
	}
	else
	{
		lcd_segment_data_on(2, temp_dat);
	}
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(3);
	}
	else
	{
		lcd_segment_data_on(3, temp_dat);
	}
	lcd_segment_decimal_point(3, 1);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer= (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on(4, 0);
	}
	else
	{
		lcd_segment_data_on(4, temp_dat);
	}
	lcd_segment_decimal_point(4, 0);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer = (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on(5, 0);
	}
	else
	{
		lcd_segment_data_on(5, temp_dat);
	}
	lcd_segment_decimal_point(5, 0);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer = (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on(6, 0);
	}
	else
	{
		lcd_segment_data_on(6, temp_dat);
	}
	lcd_segment_decimal_point(6, 0);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer = (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on(7, 0);
	}
	else
	{
		lcd_segment_data_on(7, temp_dat);
	}
	lcd_segment_decimal_point(7, 0);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer = (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on(8, 0);
	}
	else
	{
		lcd_segment_data_on(8, temp_dat);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 显示浮点数,小数点后保留4位
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float_p4f(float dat)
{
	//---强制转换为整数
	uint16_t temp_integer = (uint16_t)dat;
	uint8_t temp_dat = temp_integer / 1000;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(1);
	}
	else
	{
		lcd_segment_data_on(1, temp_dat);
	}
	temp_integer %= 1000;
	temp_dat = temp_integer / 100;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(2);
	}
	else
	{
		lcd_segment_data_on(2, temp_dat);
	}
	temp_integer %= 100;
	temp_dat = temp_integer / 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(3);
	}
	else
	{
		lcd_segment_data_on(3, temp_dat);
	}
	lcd_segment_decimal_point(3, 0);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(4);
	}
	else
	{
		lcd_segment_data_on(4, temp_dat);
	}
	lcd_segment_decimal_point(4, 1);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer = (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on(5, 0);
	}
	else
	{
		lcd_segment_data_on(5, temp_dat);
	}
	lcd_segment_decimal_point(5, 0);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer = (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on(6, 0);
	}
	else
	{
		lcd_segment_data_on(6, temp_dat);
	}
	lcd_segment_decimal_point(6, 0);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer = (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on(7, 0);
	}
	else
	{
		lcd_segment_data_on(7, temp_dat);
	}
	lcd_segment_decimal_point(7, 0);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer = (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on(8, 0);
	}
	else
	{
		lcd_segment_data_on(8, temp_dat);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 显示浮点数,小数点后保留3位
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float_p3f(float dat)
{
	//---强制转换为整数
	uint32_t temp_integer = (uint32_t)dat;
	uint8_t temp_dat = temp_integer / 10000;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(1);
	}
	else
	{
		lcd_segment_data_on(1, temp_dat);
	}
	temp_integer %= 10000;
	temp_dat = temp_integer / 1000;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(2);
	}
	else
	{
		lcd_segment_data_on(2, temp_dat);
	}
	temp_integer %= 1000;
	temp_dat = temp_integer / 100;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(3);
	}
	else
	{
		lcd_segment_data_on(3, temp_dat);
	}
	lcd_segment_decimal_point(3, 0);
	temp_integer %= 100;
	temp_dat = temp_integer / 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(4);
	}
	else
	{
		lcd_segment_data_on(4, temp_dat);
	}
	lcd_segment_decimal_point(4, 0);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on(5, 0);
	}
	else
	{
		lcd_segment_data_on(5, temp_dat);
	}
	lcd_segment_decimal_point(5, 1);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer = (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on(6, 0);
	}
	else
	{
		lcd_segment_data_on(6, temp_dat);
	}
	lcd_segment_decimal_point(6, 0);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer = (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on(7, 0);
	}
	else
	{
		lcd_segment_data_on(7, temp_dat);
	}
	lcd_segment_decimal_point(7, 0);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer = (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on(8, 0);
	}
	else
	{
		lcd_segment_data_on(8, temp_dat);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 显示浮点数,小数点后保留2位
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float_p2f(float dat)
{
	//---强制转换为整数
	uint32_t temp_integer = (uint32_t)dat;
	uint8_t temp_dat = temp_integer / 100000;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(1);
	}
	else
	{
		lcd_segment_data_on(1, temp_dat);
	}
	temp_integer %= 100000;
	temp_dat = temp_integer / 10000;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(2);
	}
	else
	{
		lcd_segment_data_on(2, temp_dat);
	}
	temp_integer %= 10000;
	temp_dat = temp_integer / 1000;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(3);
	}
	else
	{
		lcd_segment_data_on(3, temp_dat);
	}
	lcd_segment_decimal_point(3, 0);
	temp_integer %= 1000;
	temp_dat = temp_integer / 100;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(4);
	}
	else
	{
		lcd_segment_data_on(4, temp_dat);
	}
	lcd_segment_decimal_point(4, 0);
	temp_integer %= 100;
	temp_dat = temp_integer / 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(5);
	}
	else
	{
		lcd_segment_data_on(5, temp_dat);
	}
	lcd_segment_decimal_point(5, 0);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on(6, 0);
	}
	else
	{
		lcd_segment_data_on(6, temp_dat);
	}
	lcd_segment_decimal_point(6, 1);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer = (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on(7, 0);
	}
	else
	{
		lcd_segment_data_on(7, temp_dat);
	}
	lcd_segment_decimal_point(7, 0);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer = (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on(8, 0);
	}
	else
	{
		lcd_segment_data_on(8, temp_dat);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 显示浮点数,小数点后保留1位
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float_p1f(float dat)
{
	//---强制转换为整数
	uint32_t temp_integer = (uint32_t)dat;
	uint8_t temp_dat = temp_integer / 1000000;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(1);
	}
	else
	{
		lcd_segment_data_on(1, temp_dat);
	}
	temp_integer %= 1000000;
	temp_dat = temp_integer / 100000;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(2);
	}
	else
	{
		lcd_segment_data_on(2, temp_dat);
	}
	temp_integer %= 100000;
	temp_dat = temp_integer / 10000;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(3);
	}
	else
	{
		lcd_segment_data_on(3, temp_dat);
	}
	lcd_segment_decimal_point(3, 0);
	temp_integer %= 10000;
	temp_dat = temp_integer / 1000;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(4);
	}
	else
	{
		lcd_segment_data_on(4, temp_dat);
	}
	lcd_segment_decimal_point(4, 0);
	temp_integer %= 1000;
	temp_dat = temp_integer / 100;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(5);
	}
	else
	{
		lcd_segment_data_on(5, temp_dat);
	}
	lcd_segment_decimal_point(5, 0);
	temp_integer %= 100;
	temp_dat = temp_integer / 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_off(6);
	}
	else
	{
		lcd_segment_data_on(6, temp_dat);
	}
	lcd_segment_decimal_point(6, 0);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on(7, 0);
	}
	else
	{
		lcd_segment_data_on(7, temp_dat);
	}
	lcd_segment_decimal_point(7,1);
	dat -= temp_integer;
	dat *= 10.0f;
	temp_integer = (uint16_t)(dat);
	temp_dat = temp_integer % 10;
	if (temp_dat == 0)
	{
		lcd_segment_data_on(8, 0);
	}
	else
	{
		lcd_segment_data_on(8, temp_dat);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 显示浮点数，并决定小数点后保留几位小数，依次是1,2,3,4,5位小数
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t lcd_segment_show_float(float dat, uint8_t pnum)
{
	//---判断保留的小数点位数
	switch (pnum)
	{
		case 1:
		{
			lcd_segment_show_float_p1f(dat);
			break;
		}
		case 2:
		{
			lcd_segment_show_float_p2f(dat);
			break;
		}
		case 3:
		{
			lcd_segment_show_float_p3f(dat);
			break;
		}
		case 4:
		{
			lcd_segment_show_float_p4f(dat);
			break;
		}
		case 5:
		{
			lcd_segment_show_float_p5f(dat);
			break;
		}
		default:
		{
			lcd_segment_show_integer(dat);
			break;
		}
	}
	return OK_0;
}