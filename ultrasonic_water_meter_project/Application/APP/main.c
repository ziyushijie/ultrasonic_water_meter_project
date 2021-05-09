#include "main.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 	可变参数的重写printf函数
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////	
void app_log(char *fmt,...)
{
	va_list args;
	va_start(args, fmt);
#if (MODULE_LOG_ENABLE>0)

#if (MODULE_LOG_UART_INDEX==1)&&defined(TYPE_UART1)
	uart_task_printf_log(UART_TASK_ONE, fmt, args);
#elif (MODULE_LOG_UART_INDEX==2)&&defined(TYPE_UART2)
	uart_task_printf_log(UART_TASK_TWO, fmt, args);
#elif (MODULE_LOG_UART_INDEX==3)&&defined(TYPE_UART3)
	uart_task_printf_log(UART_TASK_THREE, fmt, args);
#endif

#endif
	va_end(args);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 	可变参数的重写printf函数
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////	
void app_log_args(char *fmt, va_list args)
{
#if (MODULE_LOG_ENABLE>0)

#if (MODULE_LOG_UART_INDEX==1)&&defined(TYPE_UART1)
	uart_task_printf_log(UART_TASK_ONE, fmt, args);
#elif (MODULE_LOG_UART_INDEX==2)&&defined(TYPE_UART2)
	uart_task_printf_log(UART_TASK_TWO, fmt, args);
#elif (MODULE_LOG_UART_INDEX==3)&&defined(TYPE_UART3)
	uart_task_printf_log(UART_TASK_THREE, fmt, args);
#endif

#endif
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 硬件初始化函数，会在启动文件中调用
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void hdwinit(void)
{
	//---禁止中断
	CLI();
	//---时钟初始化
	rl78_clock_init();
	//---端口配置
	rl78_port_init();
}


///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 应用使用的抵达节拍
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint32_t app_get_tick(void)
{
	return sys_tick_task_get_inc_count(SYS_TICK_TASK_ONE);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 应用初始化函数
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void app_init(void)
{
	//---禁止中断
	CLI();
	//---根据配置字选择时钟
	rl78_init((uint8_t)USER_OPT_BYTE);
	//---滴答节拍初始化
	sys_tick_task_init(SYS_TICK_TASK_ONE);
	//---GPIO初始化
	gpio_task_init(app_get_tick);
	//---CRC初始化
	crc_task_init(app_get_tick);
	//---串口初始化
	uart_task_init(UART_TASK_TWO, app_get_tick);
	//uart_task_fill_mode_send_two(UART_TASK_TWO,"123\r\n",5);
	//R_UART1_Send("123\r\n",5);
	////---调试端口定义
	//PFSEG3 &= ~(1 << 2);
	//P4 |= _20_Pn5_OUTPUT_1;
	//PM4 &= ~(1<<5);
	gpio_task_pin_mode_output(GPIOP4, GPIO_PIN_BIT_5);
	//---使能中断
	SEI();
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void main(void)
{
	app_init();
	//LOG_VA_ARGS("ultrasonic water meter\r\n");
	while (1)
	{
		gpio_task_pin_toggle(GPIOP4, GPIO_PIN_BIT_5);
		delay_task_us(100);
		WDT_RESET();
	}
}