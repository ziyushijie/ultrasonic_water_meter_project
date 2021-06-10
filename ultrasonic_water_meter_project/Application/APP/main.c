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

///////////////////////////////////////////////////////////////////////////////
//////函		数: 
//////功		能: 应用使用的秒节拍
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint32_t app_get_second(void)
{
	return calc_rtc_second(&(RTC_TASK_ONE->msg_rtcx));
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
	//---使能中断
	SEI();
	//---根据配置字选择时钟
	rl78_init((uint8_t)USER_OPT_BYTE);
	//---初始化时钟输出/蜂鸣器输出
	//rl78_pclbuz_init();
	//---启动时钟输出
	//rl78_pclbuz_start(0);
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
	//---按键初始化
	key_task_init(KEY_TASK_ONE, app_get_tick);
	//---RTC时钟初始化
	//rtc_task_init(RTC_TASK_ONE, app_get_tick, 1);
	////---调试端口定义
	//PFSEG3 &= ~(1 << 2);
	//P4 |= _20_Pn5_OUTPUT_1;
	//PM4 &= ~(1<<5);
	//---清除显示
	lcd_segment_task_clear(LCD_TASK_ONE);
	//---清零显示
	lcd_segment_task_show_integer(LCD_TASK_ONE,0,1);
	//---休眠模式初始化
	sleep_task_init(app_get_tick);
	//---喂狗
	WDT_RESET();
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
	//---??è??????￡ê?
	sleep_task_enter();
	uint32_t cnt_flow = app_get_tick();
	uint32_t cnt_temp = app_get_tick();
	app_log("超声波热量表调试\r\n");
	
	//---主循环任务
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
		//---按键扫描
		key_task_scan(KEY_TASK_ONE);
		//---按键功能检查
#if (KEY_BUTTON_MAX_NUM<=1)
		//---校验按键是否有效
		if (KEY_TASK_ONE->msg_button.msg_pin_scan_active == ACTIVE_STATE_ENABLE)
		{
			KEY_TASK_ONE->msg_button.msg_pin_scan_active = ACTIVE_STATE_DISABLE;
			//---液晶菜单功能选择
		}
#endif
		////---判断唤醒方式
		//if (sleep_task_wakeup_get()!= SLEEP_WAKEUP_NONE)
		//{
		//	//---更新时间
		//}
		////---进入休眠模式
		//sleep_task_enter();
		if (TIME_SPAN(app_get_tick(), cnt_flow) > 1000)
		{
			//---获取流量信息
			ms1022_spi_task_get_flow(MS1022_TASK_ONE);
			//---更新节拍信息
			cnt_flow = app_get_tick();
		}
		//---喂狗
		WDT_RESET();
	}
}