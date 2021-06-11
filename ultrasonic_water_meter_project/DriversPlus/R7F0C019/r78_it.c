#include "rl78_it.h"

#ifdef TYPE_UART1
//===����0���жϴ�����
//---�����жϴ���
#pragma interrupt uart_interrupt_send_one(vect=INTST0)
//---�����жϴ���
#pragma interrupt uart_interrupt_receive_one(vect=INTSR0)
//---�����жϴ���
#pragma interrupt uart_interrupt_receive_error_one(vect=INTSRE0)


///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����0�����жϴ���
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
static void __near uart_interrupt_receive_one(void)
{
	uart_task_it_irq_read_handle_one(UART_TASK_ONE);
	SEI();
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����0���ܴ����жϴ���
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
static void __near uart_interrupt_receive_error_one(void)
{
	uart_task_it_irq_read_error_handle_one(UART_TASK_ONE);
	SEI();
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����0�����жϴ���
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
static void __near uart_interrupt_send_one(void)
{
	uart_task_it_irq_send_handle_one(UART_TASK_ONE);
	SEI();
}
#endif

#ifdef TYPE_UART2
//===����1���жϴ�����
//---�����жϴ���
#pragma interrupt uart_interrupt_send_two(vect=INTST1)
//---�����жϴ���
#pragma interrupt uart_interrupt_receive_two(vect=INTSR1)
//---�����жϴ���
#pragma interrupt uart_interrupt_receive_error_two(vect=INTSRE1)


///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����1�����жϴ���
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
static void __near uart_interrupt_receive_two(void)
{
	uart_task_it_irq_read_handle_two(UART_TASK_TWO);
	SEI();
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����1���ܴ����жϴ���
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
static void __near uart_interrupt_receive_error_two(void)
{
	uart_task_it_irq_read_error_handle_two(UART_TASK_TWO);
	SEI();
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����1�����жϴ���
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
static void __near uart_interrupt_send_two(void)
{
	uart_task_it_irq_send_handle_two(UART_TASK_TWO);
	SEI();
}

#endif

#ifdef TYPE_UART3

//===����3���жϴ�����
//---�����жϴ���
#pragma interrupt uart_interrupt_send_three(vect=INTST2)
//---�����жϴ���
#pragma interrupt uart_interrupt_receive_three(vect=INTSR2)
//---�����жϴ���
#pragma interrupt uart_interrupt_receive_error_three(vect=INTSRE2)

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����2�����жϴ���
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
static void __near uart_interrupt_receive_three(void)
{
	uart_task_it_irq_read_handle_three(UART_TASK_THREE);
	SEI();
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����2���ܴ����жϴ���
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
static void __near uart_interrupt_receive_error_three(void)
{
	uart_task_it_irq_read_error_handle_three(UART_TASK_THREE);
	SEI();
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����2�����жϴ���
//////�����	��:
//////�����	��: 
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
static void __near uart_interrupt_send_three(void)
{
	uart_task_it_irq_send_handle_three(UART_TASK_THREE);
	SEI();
}

#endif

#pragma region �δ�ʱ��

#pragma interrupt sys_tick_interrupt(vect=INTTM02)

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: �δ�ʱ���жϴ���
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
static void __near sys_tick_interrupt(void)
{
	//---�δ�ʱ���жϴ�����
	sys_tick_task_it_irq_handle(SYS_TICK_TASK_ONE);
	SEI();
}

#pragma endregion

#pragma region MS1022�жϴ���

#pragma interrupt ms1022_interrupt_flag(vect=INTP7)
#pragma interrupt ms1022_interrupt_spi(vect=INTCSI00)

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ms1022���ж϶˿ڱ�ʶ���� 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
static void __near ms1022_interrupt_flag(void)
{
	//---�ж��ж�ִ�й��ܣ��ڽ�������ģʽ��ù��ܱ�ӳ�䵽���ڽ���������
	if (sleep_task_get()!=0)
	{
		sleep_task_wakeup_exit(SLEEP_WAKEUP_MBUS_UART);
	}
	else
	{
		ms1022_spi_task_it_irq_handle_int_flag(MS1022_TASK_ONE);
	}
	SEI();
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ms1022��spi���жϴ�����
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
static void __near ms1022_interrupt_spi(void)
{
	ms1022_spi_task_mhw_it_irq_handle(MS1022_TASK_ONE);
	SEI();
}

#pragma endregion

#pragma region �����жϴ���

#pragma interrupt key_interrupt_one(vect=INTP0)

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: �����жϴ���
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
static void __near key_interrupt_one(void)
{
	if (sleep_task_get() != 0)
	{
		sleep_task_wakeup_exit(SLEEP_WAKEUP_KEY);
	}
	key_task_it_irq_handle_one(KEY_TASK_ONE,0);
	SEI();
}

#pragma endregion

#pragma region ���Ź��жϴ���

#pragma interrupt wdt_interrupt(vect=INTWDTI)

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ���Ź��жϴ���
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
static void __near wdt_interrupt(void)
{
	wdt_task_it_irq_handle();
	//---�ж��Ƿ�Ϊ����ģʽ
	if (sleep_task_get() != 0)
	{
		sleep_task_wakeup_exit(SLEEP_WAKEUP_WDT);
	}
	SEI();
}

#pragma endregion

#pragma region �����жϴ���

#pragma interrupt pulse_interrupt_one(vect=INTP5)

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: �����жϴ���
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
static void __near pulse_interrupt_one(void)
{
	if (sleep_task_get() != 0)
	{
		sleep_task_wakeup_exit(SLEEP_WAKEUP_KEY);
	}
	pulse_task_it_irq_handle_one(PULSE_TASK_ONE);
	SEI();
}

#pragma endregion

#pragma region ���⴮�ڣ��жϻ��ѹ���

#pragma interrupt irda_wake_up_interrupt_one(vect=INTP1)

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: �����жϴ���
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
static void __near irda_wake_up_interrupt_one(void)
{
	if (sleep_task_get() != 0)
	{
		sleep_task_wakeup_exit(SLEEP_WAKEUP_IRDA_UART);
	}
	SEI();
}

#pragma endregion


#pragma region RTC�жϴ�����

#pragma interrupt rtc_interrupt_one(vect=INTRTC)

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 12λ�����ʱ�������ж�
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
static void __near rtc_interrupt_one(void)
{
	if (sleep_task_get() != 0)
	{
		sleep_task_wakeup_exit(SLEEP_WAKEUP_RTC);
	}
	//---�жϴ�����
	rtc_task_it_irq_handle_one(RTC_TASK_ONE);
	SEI();
}

#pragma endregion


