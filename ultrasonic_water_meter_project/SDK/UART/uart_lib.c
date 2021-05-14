#include "uart_lib.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_lib_send_reset(UART_HandleType* UARTx)
{
	uart_send_reset(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_lib_read_reset(UART_HandleType* UARTx)
{
	uart_read_reset(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t uart_lib_read_end(UART_HandleType* UARTx)
{
	return uart_read_end(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t uart_lib_init(UART_HandleType* UARTx, uint32_t(*func_time_tick)(void))
{
	return uart_init(UARTx, func_time_tick);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_lib_it_irq_read_handle(UART_HandleType* UARTx)
{
	uart_it_irq_read_handle(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_lib_it_irq_read_error_handle(UART_HandleType* UARTx)
{
	uart_it_irq_read_error_handle(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_lib_it_irq_send_handle(UART_HandleType* UARTx)
{
	uart_it_irq_send_handle(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_lib_it_irq_read_handle_one(UART_HandleType* UARTx)
{
	uart_it_irq_read_handle_one(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_lib_it_irq_read_error_handle_one(UART_HandleType* UARTx)
{
	uart_it_irq_read_error_handle_one(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_lib_it_irq_send_handle_one(UART_HandleType* UARTx)
{
	uart_it_irq_send_handle_one(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_lib_it_irq_read_handle_two(UART_HandleType* UARTx)
{
	uart_it_irq_read_handle_two(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_lib_it_irq_read_error_handle_two(UART_HandleType* UARTx)
{
	uart_it_irq_read_error_handle_two(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_lib_it_irq_send_handle_two(UART_HandleType* UARTx)
{
	uart_it_irq_send_handle_two(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_lib_it_irq_read_handle_three(UART_HandleType* UARTx)
{
	uart_it_irq_read_handle_three(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_lib_it_irq_read_error_handle_three(UART_HandleType* UARTx)
{
	uart_it_irq_read_error_handle_three(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_lib_it_irq_send_handle_three(UART_HandleType* UARTx)
{
	uart_it_irq_send_handle_three(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_lib_fill_mode_send_one(UART_HandleType* UARTx, uint8_t *buffer, uint16_t length)
{
	uart_fill_mode_send_one(UARTx, buffer, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_lib_fill_mode_send_two(UART_HandleType* UARTx, uint8_t *buffer, uint16_t length)
{
	uart_fill_mode_send_two(UARTx, buffer, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_lib_fill_mode_send_three(UART_HandleType* UARTx, uint8_t *buffer, uint16_t length)
{
	uart_fill_mode_send_three(UARTx, buffer, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_lib_fill_mode_send(UART_HandleType* UARTx, uint8_t *buffer, uint16_t length)
{
	uart_fill_mode_send(UARTx,buffer,length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////

void uart_lib_fill_mode_send_start_one(UART_HandleType* UARTx)
{
	uart_fill_mode_send_start_one(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_lib_fill_mode_send_start_two(UART_HandleType* UARTx)
{
	uart_fill_mode_send_start_two(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_lib_fill_mode_send_start_three(UART_HandleType* UARTx)
{
	uart_fill_mode_send_start_three(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_lib_fill_mode_send_start(UART_HandleType* UARTx)
{
	uart_fill_mode_send_start(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_lib_printf_log(UART_HandleType* UARTx, char* fmt, va_list args)
{
	uart_printf_log(UARTx, fmt, args);
}