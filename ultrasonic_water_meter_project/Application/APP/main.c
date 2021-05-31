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

uint8_t lcd_index = 0;

const uint8_t g_lcd_segment_display_data_table[23]=
{
	0,1,2,3,4,5,6,7,8,9,'A','b','C','d','E','F','i','n','o','r','t','u','-'
};

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
	rl78_pclbuz_init();
	//---����ʱ�����
	rl78_pclbuz_start(0);
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
	////---���Զ˿ڶ���
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
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
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
			////---��λ���գ��ȴ��´����ݵĵ���
			//uart_task_read_reset(UART_TASK_TWO);
			//---��ȡ������Ϣ
			ms1022_spi_task_get_flow(MS1022_TASK_ONE);
			//---���½�����Ϣ
			cnt_flow = app_get_tick();
		}
		if (TIME_SPAN(app_get_tick(), cnt_temp) > 5000)
		{
			//---��ȡ����ˮ�ڵ��¶�
			ms1022_spi_task_get_temperature(MS1022_TASK_ONE);
			//---���½�����Ϣ
			cnt_temp = app_get_tick();
		}
		*/
		WDT_RESET();
	}
}