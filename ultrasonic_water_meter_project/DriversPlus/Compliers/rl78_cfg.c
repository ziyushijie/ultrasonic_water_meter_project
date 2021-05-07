﻿#include "rl78_cfg.h"

//===系统时钟的时钟
volatile uint32_t g_system_core_clock=1000000UL;
//===外部调用函数
extern void delay_task_nop(uint32_t cnt);

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: RL78系列单片机的时钟选择
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void rl78_init(uint8_t opt)
{
	switch ((opt&0x0F))
	{
		case 0x00:
		{
			g_system_core_clock = 24000000UL;
			break;
		}
		case 0x09:
		{
			g_system_core_clock = 16000000UL;
			break;
		}
		case 0x01:
		{
			g_system_core_clock = 12000000UL;
			break;
		}
		case 0x0A:
		{
			g_system_core_clock = 8000000UL;
			break;
		}
		case 0x02:
		{
			g_system_core_clock = 6000000UL;
			break;
		}
		case 0x0B:
		{
			g_system_core_clock = 4000000UL;
			break;
		}
		case 0x03:
		{
			g_system_core_clock = 3000000UL;
			break;
		}
		case 0x0C:
		{
			g_system_core_clock = 2000000UL;
			break;
		}
		case 0x0D:
		{
			g_system_core_clock = 1000000UL;
			break;
		}
		default:
		{	
			//#error "RL78系列系统时钟配置错误!";
			break;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: RL78系列单片机的端口配置,配置端口默认为IO
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void rl78_port_init(void)
{
	PFSEG0 = _30_PFSEG0_DEFAULT;
	PFSEG1 = _E6_PFSEG1_DEFAULT;
	PFSEG2 = 0x00;
	PFSEG3 = _BB_PFSEG3_DEFAULT;
	PFSEG4 = _03_PFSEG4_DEFAULT;
	PFSEG5 = 0x00;
	PFSEG6 = 0x00;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 清楚复位标识
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void rl78_clear_reset_flag(void)
{
	uint8_t temp = RESF;
	temp = PORSR;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 系统时钟初始化
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void rl78_clock_init(void)
{
	//PIOR = 0x0CU;
	//---清楚复位标志
	rl78_clear_reset_flag();
	//---时钟运行模式控制寄存器CMC
	////---主时钟内部时钟，副时钟外部晶振且是低功耗震荡；主时钟评率低于10MHz
	//CMC = _00_CGC_HISYS_PORT | _10_CGC_SUB_OSC | _00_CGC_SUBMODE_LOW;
	////---系统时钟控制寄存器
	//CKC = 0x00;
	////---X1振荡电路停止，XT1振荡电路运行，高速内部振荡器运行
	//CSC = _80_CGC_HISYS_STOP;


	/* Set fMX */
	CMC = _00_CGC_HISYS_PORT | _10_CGC_SUB_OSC | _02_CGC_SUBMODE_NORMAL;
	MSTOP = 1U;
	/* Set fMAIN */
	MCM0 = 0U;
	/* Set fSUB */
	XTSTOP = 0U;

	//---延时等待时钟稳定
	delay_task_nop(50);
	////---副系统时钟提供模式控制寄存器
	//OSMC = _00_CGC_SUBINHALT_ON | _00_CGC_RTC_IT_LCD_CLK_FSUB;
	////---非法存储器存取检测控制寄存器
	//IAWCTL = 0x00;

	OSMC = _00_CGC_SUBINHALT_ON | _00_CGC_RTC_IT_LCD_CLK_FSUB;
	/* Set fCLK */
	CSS = 0U;
	/* Set fIH */
	HIOSTOP = 0U;

	//R_PORT_Create(); // IO¶Ë¿ÚÅäÖÃ

}


///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void rl78_adc_clock(uint8_t enable)
{
	if (enable!=0)
	{
		ADCEN = 1;
	}
	else
	{
		ADCEN = 0;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void rl78_i2c1_clock(uint8_t enable)
{
	if (enable != 0)
	{
		IICA0EN = 1;
	}
	else
	{
		IICA0EN = 0;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
#ifdef IICA1EN
void rl78_i2c2_clock(uint8_t enable)
{
	if (enable != 0)
	{
		IICA1EN = 1;
	}
	else
	{
		IICA1EN = 0;
	}
}
#endif

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void rl78_sau1_clock(uint8_t enable)
{
	if (enable != 0)
	{
		SAU0EN = 1;
	}
	else
	{
		SAU0EN = 0;
	}
	delay_task_nop(5);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void rl78_sau2_clock(uint8_t enable)
{
	if (enable != 0)
	{
		SAU1EN = 1;
	}
	else
	{
		SAU1EN = 0;
	}
	delay_task_nop(5);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 外设时钟使能
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void rl78_perpheral_clock_enable(uint8_t perpheral)
{
	switch (perpheral)
	{
		case PERIPHERAL_TIMER:
		{
			TAU0EN = 1;
			break;
		}
		case PERIPHERAL_UART1	:
		{
			SAU0EN = 1;
			break;
		}
		case PERIPHERAL_UART2: 
		{
			SAU0EN = 1;
			break;
		}
		case PERIPHERAL_UART3: 
		{
			SAU1EN = 1;
			break;
		}
		case PERIPHERAL_I2C1:
		{
			IICA0EN = 1;
			break;
		}
		case PERIPHERAL_I2C2:
		{
			IICA0EN = 1;
			break;
		}
		case PERIPHERAL_ADC:
		{
			ADCEN = 1;
			break;
		}
		case PERIPHERAL_RTC:
		{
			RTCWEN = 1;
			break;
		}
		default:
		{	
			break;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 外设时钟不使能
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void rl78_perpheral_clock_disable(uint8_t perpheral)
{
	switch (perpheral)
	{
		case PERIPHERAL_TIMER:
		{
			TAU0EN = 0;
			break;
		}
		case PERIPHERAL_UART1:
		{
			SAU0EN = 0;
			break;
		}
		case PERIPHERAL_UART2:
		{
			SAU0EN = 0;
			break;
		}
		case PERIPHERAL_UART3:
		{
			SAU1EN = 0;
			break;
		}
		case PERIPHERAL_I2C1:
		{
			IICA0EN = 0;
			break;
		}
		case PERIPHERAL_I2C2:
		{
#ifdef IICA1EN
			IICA1EN = 0;
#endif
			break;
		}
		case PERIPHERAL_ADC:
		{
			ADCEN = 0;
			break;
		}
		case PERIPHERAL_RTC:
		{
			RTCWEN = 0;
			break;
		}
		default:
		{
			break;
		}
	}
}