#ifndef UART_LIB_H_
#define UART_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "uart_cfg.h"

	//===º¯Êý¶¨Òå
	void uart_lib_send_reset(UART_HandleType* UARTx);
	void uart_lib_read_reset(UART_HandleType* UARTx);
	uint8_t uart_lib_read_end(UART_HandleType* UARTx);
	uint8_t uart_lib_init(UART_HandleType* UARTx, uint32_t(*func_time_tick)(void));
	
	void uart_lib_it_irq_read_handle_one(UART_HandleType* UARTx);
	void uart_lib_it_irq_read_handle_two(UART_HandleType* UARTx);
	void uart_lib_it_irq_read_handle_three(UART_HandleType* UARTx);
	void uart_lib_it_irq_read_handle(UART_HandleType* UARTx);
	
	void uart_lib_it_irq_read_error_handle_one(UART_HandleType* UARTx);
	void uart_lib_it_irq_read_error_handle_two(UART_HandleType* UARTx);
	void uart_lib_it_irq_read_error_handle_three(UART_HandleType* UARTx);
	void uart_lib_it_irq_read_error_handle(UART_HandleType* UARTx);
	
	void uart_lib_it_irq_send_handle_one(UART_HandleType* UARTx);
	void uart_lib_it_irq_send_handle_two(UART_HandleType* UARTx);
	void uart_lib_it_irq_send_handle_three(UART_HandleType* UARTx);
	void uart_lib_it_irq_send_handle(UART_HandleType* UARTx);
	
	
	void uart_lib_fill_mode_send_one(UART_HandleType* UARTx, uint8_t *buffer, uint16_t length);
	void uart_lib_fill_mode_send_two(UART_HandleType* UARTx, uint8_t *buffer, uint16_t length);
	void uart_lib_fill_mode_send_three(UART_HandleType* UARTx, uint8_t *buffer, uint16_t length);
	void uart_lib_fill_mode_send(UART_HandleType* UARTx, uint8_t *buffer, uint16_t length);
	
	void uart_lib_fill_mode_send_start_one(UART_HandleType* UARTx);
	void uart_lib_fill_mode_send_start_two(UART_HandleType* UARTx);
	void uart_lib_fill_mode_send_start_three(UART_HandleType* UARTx);
	void uart_lib_fill_mode_send_start(UART_HandleType* UARTx);
	
	void uart_lib_printf_log(UART_HandleType* UARTx, char* fmt, va_list args);


	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* UART_LIB_H_ */