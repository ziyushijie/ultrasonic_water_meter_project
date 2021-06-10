 #include "main.h"

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 	�ɱ��������дprintf����
//////�����	��:
//////�����	��:
//////˵		��:
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
//////��		��:
//////��		��: 	�ɱ��������дprintf����
//////�����	��:
//////�����	��:
//////˵		��:
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
//////��		��:
//////��		��: Ӳ����ʼ�����������������ļ��е���
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void hdwinit(void)
{
	//---��ֹ�ж�
	CLI();
	//---ʱ�ӳ�ʼ��
	rl78_clock_init();
	//---�˿�����
	rl78_port_init();
	//---ʹ���ж�
	SEI();
}


///////////////////////////////////////////////////////////////////////////////
//////��		��: 
//////��		��: Ӧ��ʹ�õĵִ����
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint32_t app_get_tick(void)
{
	return sys_tick_task_get_inc_count(SYS_TICK_TASK_ONE);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��: 
//////��		��: Ӧ��ʹ�õ������
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint32_t app_get_second(void)
{
	return calc_rtc_second(&(RTC_TASK_ONE->msg_rtcx));
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: Ӧ�ó�ʼ������
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void app_init(void)
{
	//---ʹ���ж�
	SEI();
	//---����������ѡ��ʱ��
	rl78_init((uint8_t)USER_OPT_BYTE);
	//---��ʼ��ʱ�����/���������
	//rl78_pclbuz_init();
	//---����ʱ�����
	//rl78_pclbuz_start(0);
	//---�δ���ĳ�ʼ��
	sys_tick_task_init(SYS_TICK_TASK_ONE);
	//---GPIO��ʼ��
	gpio_task_init(app_get_tick);
	//---CRC��ʼ��
	crc_task_init(app_get_tick);
	
	//---���ڳ�ʼ��
#ifdef TYPE_UART2
	uart_task_init(UART_TASK_TWO, app_get_tick);
#endif
	//---���ڳ�ʼ��
#ifdef TYPE_UART3
	uart_task_init(UART_TASK_THREE, app_get_tick);
#endif
	//---eeprom�洢����ʼ��
	at24cxx_task_i2c_init(AT24CXX_TASK_ONE, delay_task_us, delay_task_ms, app_get_tick, AT24CXX_I2C_ENABLE_HW_ONE);
	//---TDCоƬ��ʼ��
	ms1022_spi_task_init(MS1022_TASK_ONE, delay_task_us, delay_task_ms, app_get_tick, MS1022_SPI_ENABLE_HW_ONE);
	//---����Һ����ʾ
	lcd_segment_task_init(LCD_TASK_ONE,app_get_tick);
	//---������ʼ��
	key_task_init(KEY_TASK_ONE, app_get_tick);
	//---RTCʱ�ӳ�ʼ��
	//rtc_task_init(RTC_TASK_ONE, app_get_tick, 1);
	////---���Զ˿ڶ���
	//PFSEG3 &= ~(1 << 2);
	//P4 |= _20_Pn5_OUTPUT_1;
	//PM4 &= ~(1<<5);
	//---�����ʾ
	lcd_segment_task_clear(LCD_TASK_ONE);
	//---������ʾ
	lcd_segment_task_show_integer(LCD_TASK_ONE,0,1);
	//---����ģʽ��ʼ��
	sleep_task_init(app_get_tick);
	//---ι��
	WDT_RESET();
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void main(void)
{
	app_init();
	//---??��??????�꨺?
	sleep_task_enter();
	uint32_t cnt_flow = app_get_tick();
	uint32_t cnt_temp = app_get_tick();
	app_log("���������������\r\n");
	
	//---��ѭ������
	while (1)
	{
#ifdef TYPE_UART2
		//---����Ƿ��յ�����
		if (uart_task_read_end(UART_TASK_TWO)==OK_0)
		{
			uart_task_fill_mode_send(UART_TASK_TWO,
				UART_TASK_TWO->msg_uart_rxd.msg_p_data_buffer,
				UART_TASK_TWO->msg_uart_rxd.msg_data_length);
			//---��λ���գ��ȴ��´����ݵĵ���
			uart_task_read_reset(UART_TASK_TWO);
		}
#endif
#ifdef TYPE_UART3
		if (uart_task_read_end(UART_TASK_THREE) == OK_0)
		{
			uart_task_fill_mode_send(UART_TASK_THREE,
				UART_TASK_THREE->msg_uart_rxd.msg_p_data_buffer,
				UART_TASK_THREE->msg_uart_rxd.msg_data_length);
			//---��λ���գ��ȴ��´����ݵĵ���
			uart_task_read_reset(UART_TASK_THREE);
		}
#endif
		//---����ɨ��
		key_task_scan(KEY_TASK_ONE);
		//---�������ܼ��
#if (KEY_BUTTON_MAX_NUM<=1)
		//---У�鰴���Ƿ���Ч
		if (KEY_TASK_ONE->msg_button.msg_pin_scan_active == ACTIVE_STATE_ENABLE)
		{
			KEY_TASK_ONE->msg_button.msg_pin_scan_active = ACTIVE_STATE_DISABLE;
			//---Һ���˵�����ѡ��
		}
#endif
		////---�жϻ��ѷ�ʽ
		//if (sleep_task_wakeup_get()!= SLEEP_WAKEUP_NONE)
		//{
		//	//---����ʱ��
		//}
		////---��������ģʽ
		//sleep_task_enter();
		if (TIME_SPAN(app_get_tick(), cnt_flow) > 1000)
		{
			//---��ȡ������Ϣ
			ms1022_spi_task_get_flow(MS1022_TASK_ONE);
			//---���½�����Ϣ
			cnt_flow = app_get_tick();
		}
		//---ι��
		WDT_RESET();
	}
}