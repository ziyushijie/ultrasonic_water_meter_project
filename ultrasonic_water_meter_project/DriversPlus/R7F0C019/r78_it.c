#include "rl78_it.h"

#ifdef TYPE_UART1
//===串口0的中断处理函数
//---发送中断处理
#pragma interrupt uart_interrupt_send_one(vect=INTST0)
//---接受中断处理
#pragma interrupt uart_interrupt_receive_one(vect=INTSR0)
//---错误中断处理
#pragma interrupt uart_interrupt_receive_error_one(vect=INTSRE0)


///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 串口0接受中断处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
static void __near uart_interrupt_receive_one(void)
{
	uart_task_it_irq_read_handle_one(UART_TASK_ONE);
	SEI();
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 串口0接受错误中断处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
static void __near uart_interrupt_receive_error_one(void)
{
	uart_task_it_irq_read_error_handle_one(UART_TASK_ONE);
	SEI();
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 串口0发送中断处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
static void __near uart_interrupt_send_one(void)
{
	uart_task_it_irq_send_handle_one(UART_TASK_ONE);
	SEI();
}
#endif

#ifdef TYPE_UART2
//===串口1的中断处理函数
//---发送中断处理
#pragma interrupt uart_interrupt_send_two(vect=INTST1)
//---接受中断处理
#pragma interrupt uart_interrupt_receive_two(vect=INTSR1)
//---错误中断处理
#pragma interrupt uart_interrupt_receive_error_two(vect=INTSRE1)


///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 串口1接受中断处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
static void __near uart_interrupt_receive_two(void)
{
	uart_task_it_irq_read_handle_two(UART_TASK_TWO);
	SEI();
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 串口1接受错误中断处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
static void __near uart_interrupt_receive_error_two(void)
{
	uart_task_it_irq_read_error_handle_two(UART_TASK_TWO);
	SEI();
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 串口1发送中断处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
static void __near uart_interrupt_send_two(void)
{
	uart_task_it_irq_send_handle_two(UART_TASK_TWO);
	SEI();
}

#endif

#ifdef TYPE_UART3

//===串口3的中断处理函数
//---发送中断处理
#pragma interrupt uart_interrupt_send_three(vect=INTST2)
//---接受中断处理
#pragma interrupt uart_interrupt_receive_three(vect=INTSR2)
//---错误中断处理
#pragma interrupt uart_interrupt_receive_error_three(vect=INTSRE2)

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 串口2接受中断处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
static void __near uart_interrupt_receive_three(void)
{
	uart_task_it_irq_read_handle_three(UART_TASK_THREE);
	SEI();
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 串口2接受错误中断处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
static void __near uart_interrupt_receive_error_three(void)
{
	uart_task_it_irq_read_error_handle_three(UART_TASK_THREE);
	SEI();
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 串口2发送中断处理
//////输入参	数:
//////输出参	数: 
//////说		明:
//////////////////////////////////////////////////////////////////////////////
static void __near uart_interrupt_send_three(void)
{
	uart_task_it_irq_send_handle_three(UART_TASK_THREE);
	SEI();
}

#endif


#pragma region 滴答定时器

#pragma interrupt sys_tick_interrupt(vect=INTTM02)

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 滴答定时器中断处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
static void __near sys_tick_interrupt(void)
{
	//---滴答定时器中断处理函数
	sys_tick_task_it_irq_handle(SYS_TICK_TASK_ONE);
	SEI();
}

#pragma endregion

#pragma region MS1022中断处理

#pragma interrupt ms1022_interrupt_flag(vect=INTP7)
#pragma interrupt ms1022_interrupt_spi(vect=INTCSI00)

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: ms1022的中断端口标识处理 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
static void __near ms1022_interrupt_flag(void)
{
	ms1022_spi_task_it_irq_handle_int_flag(MS1022_TASK_ONE);
	SEI();
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: ms1022的spi的中断处理函数
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
static void __near ms1022_interrupt_spi(void)
{
	ms1022_spi_task_mhw_it_irq_handle(MS1022_TASK_ONE);
	SEI();
}

#pragma endregion

#pragma region 按键中断处理

#pragma interrupt key_interrupt_one(vect=INTP0)

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 按键中断处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
static void __near key_interrupt_one(void)
{
	key_task_it_irq_handle_one(KEY_TASK_ONE,0);
	SEI();
}

#pragma endregion

#pragma region 看门狗中断处理

#pragma interrupt wdt_interrupt(vect=INTWDTI)

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 看门狗中断处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
static void __near wdt_interrupt(void)
{
	wdt_task_it_irq_handle();
	SEI();
}

#pragma endregion

#pragma region 脉冲中断处理

#pragma interrupt pulse_interrupt_one(vect=INTP5)

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 按键中断处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
static void __near pulse_interrupt_one(void)
{
	pulse_task_it_irq_handle_one(PULSE_TASK_ONE);
	SEI();
}

#pragma endregion


