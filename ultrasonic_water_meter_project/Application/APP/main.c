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
	
#if (MODULE_LOG_ENABLE>0)
	va_list args;
	va_start(args, fmt);
#if (MODULE_LOG_UART_INDEX==1)&&defined(TYPE_UART1)
	uart_task_printf_log(UART_TASK_ONE, fmt, args);
#elif (MODULE_LOG_UART_INDEX==2)&&defined(TYPE_UART2)
	uart_task_printf_log(UART_TASK_TWO, fmt, args);
#elif (MODULE_LOG_UART_INDEX==3)&&defined(TYPE_UART3)
	uart_task_printf_log(UART_TASK_THREE, fmt, args);
#endif
	va_end(args);
#endif
	
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
	//---使能中断
	SEI();
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

uint8_t lcd_index = 0;

const uint8_t g_lcd_segment_display_data_table[23]=
{
	0,1,2,3,4,5,6,7,8,9,'A','b','C','d','E','F','i','n','o','r','t','u','-'
};

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 应用初始化函数
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void app_init(void)
{
	//---使能中断
	SEI();
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
#ifdef TYPE_UART2
	uart_task_init(UART_TASK_TWO, app_get_tick);
#endif
	//---串口初始化
#ifdef TYPE_UART3
	uart_task_init(UART_TASK_THREE, app_get_tick);
#endif
	//---eeprom存储器初始化
	at24cxx_task_i2c_init(AT24CXX_TASK_ONE, delay_task_us, delay_task_ms, app_get_tick, AT24CXX_I2C_ENABLE_HW_ONE);
	//---TDC芯片初始化
	ms1022_spi_task_init(MS1022_TASK_ONE, delay_task_us, delay_task_ms, app_get_tick, MS1022_SPI_ENABLE_HW_ONE);
	//---断码液晶显示
	lcd_segment_task_init(LCD_TASK_ONE,app_get_tick);
	////---调试端口定义
	//PFSEG3 &= ~(1 << 2);
	//P4 |= _20_Pn5_OUTPUT_1;
	//PM4 &= ~(1<<5);
	//gpio_task_pin_mode_output(GPIOP4, GPIO_PIN_BIT_5);
	//at24cxx_task_i2c_read_byte(AT24CXX_TASK_ONE, 0, temp_buffer, 4);
	//lcd_segment_task_show_all();
	for (lcd_index=0;lcd_index<14;lcd_index++)
	{
		lcd_segment_task_text_title_on(LCD_TASK_ONE,lcd_index);
		delay_task_ms(10);
	}
	lcd_segment_task_clear(LCD_TASK_ONE);
	for (lcd_index = 0; lcd_index < 14; lcd_index++)
	{
		lcd_segment_task_unit_title_on(LCD_TASK_ONE,lcd_index);
		delay_task_ms(10);
	}

	//for (lcd_index = 0; lcd_index < 23; lcd_index++)
	//{
	//	lcd_segment_task_data_on(1, g_lcd_segment_display_data_table[lcd_index]);
	//	delay_task_ms(10);
	//}
	lcd_segment_task_show_integer(LCD_TASK_ONE,1,1);
	/*for (lcd_index=0;lcd_index<4;lcd_index++)
	{
		SEG0 |= (1 << lcd_index);
		delay_task_ms(10);
		SEG0 &= 0xF0;
	}*/
	lcd_segment_task_show_float(LCD_TASK_ONE,070.54321,5);
	delay_task_ms(10);
	/*
	lcd_segment_task_show_float(876.54321, 4);
	delay_task_ms(10);
	lcd_segment_task_show_float(876.54321, 3);
	delay_task_ms(10);
	lcd_segment_task_show_float(876.54321, 2);
	delay_task_ms(10);
	lcd_segment_task_show_float(876.54321, 1);
	delay_task_ms(10);*/
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
	uint32_t cnt_flow = app_get_tick();
	uint32_t cnt_temp = app_get_tick();
	//ms1022_spi_task_calibration_resonator(MS1022_TASK_ONE);
	//ms1022_spi_task_read_start_temperature_restart(MS1022_TASK_ONE);
	while (1)
	{
#ifdef TYPE_UART2
		//---检查是否收到数据
		if (uart_task_read_end(UART_TASK_TWO)==OK_0)
		{
			uart_task_fill_mode_send(UART_TASK_TWO,
				UART_TASK_TWO->msg_uart_rxd.msg_p_data_buffer,
				UART_TASK_TWO->msg_uart_rxd.msg_data_length);
			//---复位接收，等待下次数据的到来
			uart_task_read_reset(UART_TASK_TWO);
		}
#endif
#ifdef TYPE_UART3
		if (uart_task_read_end(UART_TASK_THREE) == OK_0)
		{
			uart_task_fill_mode_send(UART_TASK_THREE,
				UART_TASK_THREE->msg_uart_rxd.msg_p_data_buffer,
				UART_TASK_THREE->msg_uart_rxd.msg_data_length);
			//---复位接收，等待下次数据的到来
			uart_task_read_reset(UART_TASK_THREE);
		}
#endif
		/*
		if (TIME_SPAN(app_get_tick(), cnt_flow) >3000)
		{
			//UART_TASK_TWO->msg_uart_rxd.msg_p_data_buffer[0]=0xFE;
			//UART_TASK_TWO->msg_uart_rxd.msg_p_data_buffer[1] = 0xFE;
			//UART_TASK_TWO->msg_uart_rxd.msg_p_data_buffer[2] = 0xFE;

			//UART_TASK_TWO->msg_uart_rxd.msg_p_data_buffer[3] = 0x68;
			//UART_TASK_TWO->msg_uart_rxd.msg_p_data_buffer[4] = 0x55;
			//UART_TASK_TWO->msg_uart_rxd.msg_p_data_buffer[5] = 0xAA;
			//UART_TASK_TWO->msg_uart_rxd.msg_p_data_buffer[6] = 0xAA;
			//UART_TASK_TWO->msg_uart_rxd.msg_p_data_buffer[7] = 0xAA;
			//UART_TASK_TWO->msg_uart_rxd.msg_p_data_buffer[8] = 0xAA;
			//UART_TASK_TWO->msg_uart_rxd.msg_p_data_buffer[9] = 0xAA;
			//UART_TASK_TWO->msg_uart_rxd.msg_p_data_buffer[10] = 0xAA;
			//UART_TASK_TWO->msg_uart_rxd.msg_p_data_buffer[11] = 0xAA;

			//UART_TASK_TWO->msg_uart_rxd.msg_p_data_buffer[12] = 0x23;
			//UART_TASK_TWO->msg_uart_rxd.msg_p_data_buffer[13] = 0x04;

			//UART_TASK_TWO->msg_uart_rxd.msg_p_data_buffer[14] = 0x81;
			//UART_TASK_TWO->msg_uart_rxd.msg_p_data_buffer[15] = 0x0A;

			//UART_TASK_TWO->msg_uart_rxd.msg_p_data_buffer[16] = 0x01;
			//UART_TASK_TWO->msg_uart_rxd.msg_p_data_buffer[17] = 0x00;

			//UART_TASK_TWO->msg_uart_rxd.msg_p_data_buffer[18] = 0x16;
			//UART_TASK_TWO->msg_uart_rxd.msg_p_data_buffer[19] = 0x16;

			//uart_task_fill_mode_send_two(UART_TASK_TWO,
			//	UART_TASK_TWO->msg_uart_rxd.msg_p_data_buffer,
			//	20);
			////---复位接收，等待下次数据的到来
			//uart_task_read_reset(UART_TASK_TWO);
			//---获取流量信息
			ms1022_spi_task_get_flow(MS1022_TASK_ONE);
			//---更新节拍信息
			cnt_flow = app_get_tick();
		}
		if (TIME_SPAN(app_get_tick(), cnt_temp) > 5000)
		{
			//---获取进出水口的温度
			ms1022_spi_task_get_temperature(MS1022_TASK_ONE);
			//---更新节拍信息
			cnt_temp = app_get_tick();
		}
		*/
		WDT_RESET();
	}
}