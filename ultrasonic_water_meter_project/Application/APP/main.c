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

uint8_t temp_buffer[4] = { 0 };

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
	//---初始化时钟输出/蜂鸣器输出
	rl78_pclbuz_init();
	//---启动时钟输出
	rl78_pclbuz_start(0);
	//---滴答节拍初始化
	sys_tick_task_init(SYS_TICK_TASK_ONE);
	//---GPIO初始化
	gpio_task_init(app_get_tick);
	//---CRC初始化
	crc_task_init(app_get_tick);
	//---串口初始化
	uart_task_init(UART_TASK_TWO, app_get_tick);
	//---eeprom存储器初始化
	at24cxx_task_i2c_init(AT24CXX_TASK_ONE,delay_task_us,delay_task_ms,app_get_tick,AT24CXX_ENABLE_HW_I2C_ONE);
	//---TDC芯片初始化
	ms1022_spi_task_init(MS1022_TASK_ONE, delay_task_us, delay_task_ms, app_get_tick,1);
	////---调试端口定义
	//PFSEG3 &= ~(1 << 2);
	//P4 |= _20_Pn5_OUTPUT_1;
	//PM4 &= ~(1<<5);
	//gpio_task_pin_mode_output(GPIOP4, GPIO_PIN_BIT_5);
	//---使能中断
	SEI();
	at24cxx_task_i2c_read_byte(AT24CXX_TASK_ONE, 0, temp_buffer, 4);
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
	//app_log("ultrasonic water meter\r\n");
	//uart_task_fill_mode_send_two(UART_TASK_TWO,"123\r\n",5);
	ms1022_spi_task_send_cmd(MS1022_TASK_ONE, 0x50);
	ms1022_spi_task_send_cmd(MS1022_TASK_ONE, 0x50);
	ms1022_spi_task_read_reg_state(MS1022_TASK_ONE);
	while (1)
	{
		//gpio_task_pin_toggle(GPIOP4, GPIO_PIN_BIT_5);
		//P4_bit.no5=0;
		//delay_task_us(100);
		//P4_bit.no5^=1;
		//---检查是否收到数据
		if (uart_task_read_end(UART_TASK_TWO)==OK_0)
		{
			uart_task_fill_mode_send_two(UART_TASK_TWO,
				UART_TASK_TWO->msg_uart_rxd.msg_p_data_buffer,
				UART_TASK_TWO->msg_uart_rxd.msg_data_length);
			//---复位接收，等待下次数据的到来
			uart_task_read_reset(UART_TASK_TWO);
		}
		WDT_RESET();
	}
}