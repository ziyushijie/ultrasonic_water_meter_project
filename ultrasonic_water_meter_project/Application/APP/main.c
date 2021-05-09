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
	//---�δ���ĳ�ʼ��
	sys_tick_task_init(SYS_TICK_TASK_ONE);
	//---GPIO��ʼ��
	gpio_task_init(app_get_tick);
	//---CRC��ʼ��
	crc_task_init(app_get_tick);
	//---���ڳ�ʼ��
	uart_task_init(UART_TASK_TWO, app_get_tick);
	//uart_task_fill_mode_send_two(UART_TASK_TWO,"123\r\n",5);
	//R_UART1_Send("123\r\n",5);
	////---���Զ˿ڶ���
	//PFSEG3 &= ~(1 << 2);
	//P4 |= _20_Pn5_OUTPUT_1;
	//PM4 &= ~(1<<5);
	gpio_task_pin_mode_output(GPIOP4, GPIO_PIN_BIT_5);
	//---ʹ���ж�
	SEI();
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
	while (1)
	{
		gpio_task_pin_toggle(GPIOP4, GPIO_PIN_BIT_5);
		delay_task_us(100);
		WDT_RESET();
	}
}