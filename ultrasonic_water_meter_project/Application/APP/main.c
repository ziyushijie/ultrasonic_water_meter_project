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

uint8_t temp_buffer[4] = { 0 };

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: Ӧ�ó�ʼ������
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void app_init(void)
{
	//---��ֹ�ж�
	CLI();
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
	uart_task_init(UART_TASK_TWO, app_get_tick);
	//---eeprom�洢����ʼ��
	at24cxx_task_i2c_init(AT24CXX_TASK_ONE,delay_task_us,delay_task_ms,app_get_tick,AT24CXX_ENABLE_HW_I2C_ONE);
	//---TDCоƬ��ʼ��
	ms1022_spi_task_init(MS1022_TASK_ONE, delay_task_us, delay_task_ms, app_get_tick,1);
	////---���Զ˿ڶ���
	//PFSEG3 &= ~(1 << 2);
	//P4 |= _20_Pn5_OUTPUT_1;
	//PM4 &= ~(1<<5);
	//gpio_task_pin_mode_output(GPIOP4, GPIO_PIN_BIT_5);
	//---ʹ���ж�
	SEI();
	at24cxx_task_i2c_read_byte(AT24CXX_TASK_ONE, 0, temp_buffer, 4);
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
		//---����Ƿ��յ�����
		if (uart_task_read_end(UART_TASK_TWO)==OK_0)
		{
			uart_task_fill_mode_send_two(UART_TASK_TWO,
				UART_TASK_TWO->msg_uart_rxd.msg_p_data_buffer,
				UART_TASK_TWO->msg_uart_rxd.msg_data_length);
			//---��λ���գ��ȴ��´����ݵĵ���
			uart_task_read_reset(UART_TASK_TWO);
		}
		WDT_RESET();
	}
}