#ifndef UART_TASK_H_
#define UART_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "uart_lib.h"

	//===º¯Êý¶¨Òå
	void uart_task_it_irq_read_handle(UART_HandleType* UARTx);
	void uart_task_it_irq_read_error_handle(UART_HandleType* UARTx);
	void uart_task_it_irq_send_handle(UART_HandleType* UARTx);
	void uart_task_it_irq_read_handle_one(UART_HandleType* UARTx);
	void uart_task_it_irq_read_error_handle_one(UART_HandleType* UARTx);
	void uart_task_it_irq_send_handle_one(UART_HandleType* UARTx);
	void uart_task_it_irq_read_handle_two(UART_HandleType* UARTx);
	void uart_task_it_irq_read_error_handle_two(UART_HandleType* UARTx);
	void uart_task_it_irq_send_handle_two(UART_HandleType* UARTx);
	void uart_task_it_irq_read_handle_three(UART_HandleType* UARTx);
	void uart_task_it_irq_read_error_handle_three(UART_HandleType* UARTx);
	void uart_task_it_irq_send_handle_three(UART_HandleType* UARTx);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* UART_TASK_H_ */