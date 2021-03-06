#include "sys_tick_cfg.h"

//===变量定义
SYS_TICK_HandleType			g_sys_tick_one = { 0 };
pSYS_TICK_HandleType		p_sys_tick_one = &g_sys_tick_one;

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 滴答初始化函数
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t sys_tick_init(SYS_TICK_HandleType *systickx)
{
	rl78_perpheral_clock_enable(PERIPHERAL_TIMER);
	//---支持的输入时钟
#if (SYS_TICK_MIN_PULSE_WIDTH<=8)
	TPS0 =	_0000_TAU_CKM0_fCLK_0 | 
			_0000_TAU_CKM1_fCLK_0 | 
			_0000_TAU_CKM2_fCLK_1 | 
			_0000_TAU_CKM3_fCLK_8;
#else
	TPS0 =	_0003_TAU_CKM0_fCLK_3 | 
			_0000_TAU_CKM1_fCLK_0 | 
			_0000_TAU_CKM2_fCLK_1 | 
			_0000_TAU_CKM3_fCLK_8;
#endif
	//---停止通道2
	TT0 |= _0004_TAU_CH2_STOP_TRG_ON;
	//---不使能中断
	TMMK02 = 1U;    
	//---清楚中断标志位
	TMIF02 = 0U;    
	
	//---中断优先级配置
	TMPR102 = 1U;
	TMPR002 = 1U;

	//---时钟选择CKM0.
	TMR02 = _0000_TAU_CLOCK_SELECT_CKM0 |
			_0000_TAU_CLOCK_MODE_CKS |
			_0000_TAU_COMBINATION_SLAVE |
			_0000_TAU_TRIGGER_SOFTWARE |
			_0000_TAU_MODE_INTERVAL_TIMER |
			_0001_TAU_START_INT_USED;

	//---配置时钟的选择
#if (SYS_TICK_MIN_PULSE_WIDTH<=8)
	//---系统节拍定义
#if (SYS_TICK_MIN_PULSE_WIDTH==1)
	TDR02 = (SYS_CLOCK_KHZ - 1);
#elif (SYS_TICK_MIN_PULSE_WIDTH==2)
	TDR02 = (SYS_CLOCK_KHZ * 2 - 1);
#elif (SYS_TICK_MIN_PULSE_WIDTH==4)
	TDR02 = (SYS_CLOCK_KHZ * 4 - 1);
#elif (SYS_TICK_MIN_PULSE_WIDTH==8)&&(SYS_CLOCK_KHZ<=8000UL)
	TDR02 = (SYS_CLOCK_KHZ * 8 - 1);
#else
	#error "不支持的滴答节拍配置!\r\n"
#endif

#else

	//---系统节拍定义
#if (SYS_TICK_MIN_PULSE_WIDTH==1)
	TDR02 = (SYS_CLOCK_KHZ/8 - 1);
#elif (SYS_TICK_MIN_PULSE_WIDTH==2)
	TDR02 = (SYS_CLOCK_KHZ * 2 /8- 1);
#elif (SYS_TICK_MIN_PULSE_WIDTH==4)
	TDR02 = (SYS_CLOCK_KHZ * 4/8 - 1);
#elif (SYS_TICK_MIN_PULSE_WIDTH==8)
	TDR02 = (SYS_CLOCK_KHZ * 8/8 - 1);
#elif (SYS_TICK_MIN_PULSE_WIDTH==10)
	TDR02 = (10000 - 1);
#else
	#error "不支持的滴答节拍配置!\r\n"
#endif

#endif

	TOM0 &= ~_0004_TAU_CH2_OUTPUT_COMBIN;
	TOL0 &= ~_0004_TAU_CH2_OUTPUT_LEVEL_L;
	TO0 &= ~_0004_TAU_CH2_OUTPUT_VALUE_1;
	TOE0 &= ~_0004_TAU_CH2_OUTPUT_ENABLE;
	//---使能滴答定时器
	sys_tick_enable();
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 系统滴答使能
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void sys_tick_enable(void)
{
	//---使能定时器
	TS0 |= _0004_TAU_CH2_START_TRG_ON;
	//---清楚中断标志位
	TMIF02 = 0U;  
	//---使能中断
	TMMK02 = 0U;    /* enable INTTM02 interrupt */
	
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 系统滴答不使能
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void sys_tick_disable(void)
{
	//---不使能中断
	TMMK02 = 1U;  
	//---清楚中断标志位
	TMIF02 = 0U;   
	//---使能定时器
	TT0 |= _0004_TAU_CH2_STOP_TRG_ON;

}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 中断滴答任务函数
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t sys_tick_it_irq_handle(SYS_TICK_HandleType *systickx)
{
	//--->>>递加计数器，用于系统节拍
	systickx->msg_inc_count++;
	if (systickx->msg_inc_count==0)
	{
		//---溢出标志位
		systickx->msg_inc_ovf++;
	}
	//---<<<递加计数器，用于系统节拍

	//--->>>递减计数器，用于ms
	if (systickx->msg_dec_count!=0)
	{
		systickx->msg_dec_count--;
	}
	//---<<<递减计数器，用于ms

	//--->>>任务队列，用于简单的任务执行
	
	//---<<<任务队列，用于简单的任务执行
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 获取递增计数器的溢出
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint32_t sys_tick_get_inc_ovf(SYS_TICK_HandleType *systickx)
{
	return systickx->msg_inc_ovf;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 获取递增计数器的值
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint32_t sys_tick_get_inc_count(SYS_TICK_HandleType *systickx)
{
	return (systickx->msg_inc_count + 0);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 获取递增计数器的值
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint32_t sys_tick_get_tick(void)
{
	return sys_tick_get_inc_count(SYS_TICK_TASK_ONE);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 获取延时等待
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t sys_tick_wait_us(uint32_t us)
{
	//---计算计数值
	uint32_t ticks = ((us * SYS_CLOCK_MHZ));
	//---计数值
	uint32_t told = SYS_TICK_REG_VAL;
	uint32_t tnow = 0;
	uint32_t tcnt = 0;
	//---装载值
	uint32_t tload = SYS_TICK_REG_LOAD;
	//---判断是不是超出界限
	if (us < 1001)
	{
		while (1)
		{
			tnow = SYS_TICK_REG_VAL;
			//---计数器为递减计数器
			if (tnow < told)
			{
				tcnt += (told - tnow);
			}
			else
			{
				tcnt += (tload - tnow + told);
			}
			told = tnow;
			if (tcnt >= ticks)
			{
				break;
			}
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 获取延时等待
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t sys_tick_wait_ms(SYS_TICK_HandleType *systickx,uint32_t ms)
{
	//---计算要滴答的时间
	uint32_t ticks = SYS_TICK_REG_VAL+1;
	//---计算要延时的us时间
	uint32_t us_delay = (ticks / SYS_CLOCK_MHZ);
	//---如果时间在1us的误差内，放弃
	if ((us_delay>1)&&(us_delay<1000))
	{
		sys_tick_wait_us(us_delay);
		//---ms中断计数减小
		ms -= 1;
		//---剩下的延时时间，强制装换，避免为负数
		ticks = (uint32_t)(1000 - us_delay - 10);
	}
	//---要延时的时间
	systickx->msg_dec_count = ms;
	//---等待时间到达
	while (systickx->msg_dec_count != 0)
	{
		WDT_RESET();
	}
	//---如果时间在1us的误差内，放弃
	if ((ticks > 1) && (ticks < 1000))
	{
		//---完成拆分1ms之后要完成的计数值
		sys_tick_wait_us(ticks);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 获取延时等待
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t sys_tick_wait_s(SYS_TICK_HandleType *systickx, uint32_t s)
{
	//---要延时的时间
	systickx->msg_dec_count = s*1000;
	//---等待时间到达
	while (systickx->msg_dec_count != 0)
	{
		WDT_RESET();
	}
	return OK_0;
}