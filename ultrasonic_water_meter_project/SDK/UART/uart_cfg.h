#ifndef UART_CFG_H_
#define UART_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	
	#include "complier_lib.h"
	#include "sys_tick_task.h"
	#include "hw_config.h"
	#include "gpio_task.h"

	//===���ݽṹ��
	typedef struct _UART_HandleType				UART_HandleType;
	typedef struct _UART_HandleType				* pUART_HandleType;
	
	//===���ݽṹ��
	typedef struct _UART_DataType				UART_DataType;
	typedef struct _UART_DataType				* pUART_DataType;
	struct _UART_DataType
	{
		vltuint8_t								msg_step;																//---ִ�в����
		vltuint8_t								msg_state;																//---��ǰ״̬
		vltuint16_t								msg_send_index;															//---д���
		vltuint16_t								msg_read_index;															//---�����
		vltuint16_t								msg_data_length;														//---���ݳ���
		vltuint32_t								msg_time_tick;															//---��ʱʱ�����
		vltuint32_t								msg_time_record;														//---��ʱʱ���¼ʱ��
		vltuint32_t								msg_timeout_max;														//---���ʱʱ��
		vltuint8_t								* msg_p_data_buffer;													//---���ݻ�����
		uint32_t(*msg_f_time_tick)(void);																				//---���ڳ�ʱ����
	};
	//===�������ݶ���
	struct _UART_HandleType
	{
		UART_DataType							msg_uart_txd;															//---���;��
		UART_DataType							msg_uart_rxd;															//---���վ��
	};


	#define UART_STATE_OK							0																	//---���ڿ���״̬
	#define UART_STATE_BUSY							1																	//---����æµ״̬	
	#define UART_STATE_ERROR						2																	//---���ڴ���״̬
	#define UART_STATE_END							3																	//---�������״̬
	#define UART_STATE_TIMEOUT						4																	//---���ڳ�ʱ״̬
	
	//===�ⲿ���ýӿ�
#ifdef TYPE_UART1
	extern UART_HandleType							g_uart_one;
	extern pUART_HandleType							p_uart_one;
#endif
#ifdef TYPE_UART2
	extern UART_HandleType							g_uart_two;
	extern pUART_HandleType							p_uart_two;
#endif
#ifdef TYPE_UART3
	extern UART_HandleType							g_uart_three;
	extern pUART_HandleType							p_uart_three;
#endif

	//===�ⲿ���ñ���
#ifdef TYPE_UART1

#if defined(UART_RX_SIZE_MAX_ONE)&&(UART_RX_SIZE_MAX_ONE!=0)
	//===ȫ�ֱ����Ķ���
	extern volatile uint8_t g_uart_rx_buffer_one[UART_RX_SIZE_MAX_ONE];
	extern volatile uint8_t* p_uart_rx_buffer_one;
#endif

#if defined(UART_TX_SIZE_MAX_ONE)&&(UART_TX_SIZE_MAX_ONE!=0)
	extern volatile uint8_t g_uart_tx_buffer_one[UART_TX_SIZE_MAX_ONE];
	extern volatile uint8_t* p_uart_tx_buffer_one;
#endif

#endif

#ifdef TYPE_UART2

#if defined(UART_RX_SIZE_MAX_TWO)&&(UART_RX_SIZE_MAX_TWO!=0)
	//===ȫ�ֱ����Ķ���
	extern volatile uint8_t g_uart_rx_buffer_two[UART_RX_SIZE_MAX_TWO];
	extern volatile uint8_t* p_uart_rx_buffer_two;
#endif

#if defined(UART_TX_SIZE_MAX_TWO)&&(UART_TX_SIZE_MAX_TWO!=0)
	extern volatile uint8_t g_uart_tx_buffer_two[UART_TX_SIZE_MAX_TWO];
	extern volatile uint8_t* p_uart_tx_buffer_two;
#endif

#endif

#ifdef TYPE_UART3

#if defined(UART_RX_SIZE_MAX_THREE)&&(UART_RX_SIZE_MAX_THREE!=0)
	//===ȫ�ֱ����Ķ���
	extern volatile uint8_t g_uart_rx_buffer_three[UART_RX_SIZE_MAX_THREE];
	extern volatile uint8_t* p_uart_rx_buffer_three;
#endif

#if defined(UART_TX_SIZE_MAX_THREE)&&(UART_TX_SIZE_MAX_THREE!=0)
	extern volatile uint8_t g_uart_tx_buffer_three[UART_TX_SIZE_MAX_THREE];
	extern volatile uint8_t* p_uart_tx_buffer_three;
#endif

#endif

//===�����������
#ifdef TYPE_UART1
	#define UART_TASK_ONE						p_uart_one																//---UART1������
#endif
#ifdef TYPE_UART2
	#define UART_TASK_TWO						p_uart_two																//---UART2������
#endif
#ifdef TYPE_UART3
	#define UART_TASK_THREE						p_uart_three															//---UART3������
#endif

	//===��������
	void uart_send_reset(UART_HandleType* UARTx);
	void uart_read_reset(UART_HandleType* UARTx);
	uint8_t uart_read_end(UART_HandleType* UARTx);

	uint8_t uart_init_one(UART_HandleType* UARTx);
	uint8_t uart_init_two(UART_HandleType* UARTx);
	uint8_t uart_init_three(UART_HandleType* UARTx);
	uint8_t uart_init(UART_HandleType* UARTx, uint32_t(*func_time_tick)(void));
	
	void uart_it_irq_read_handle_one(UART_HandleType* UARTx);
	void uart_it_irq_read_handle_two(UART_HandleType* UARTx);
	void uart_it_irq_read_handle(UART_HandleType* UARTx);
	void uart_it_irq_read_handle_three(UART_HandleType* UARTx);
	
	void uart_it_irq_read_error_handle(UART_HandleType* UARTx);
	void uart_it_irq_read_error_handle_one(UART_HandleType* UARTx);
	void uart_it_irq_read_error_handle_two(UART_HandleType* UARTx);
	void uart_it_irq_read_error_handle_three(UART_HandleType* UARTx);
	
	void uart_it_irq_send_handle_one(UART_HandleType* UARTx);
	void uart_it_irq_send_handle_two(UART_HandleType* UARTx);
	void uart_it_irq_send_handle(UART_HandleType* UARTx);
	void uart_it_irq_send_handle_three(UART_HandleType* UARTx);
	
	void uart_fill_mode_send_one(UART_HandleType* UARTx, uint8_t *buffer, uint16_t length);
	void uart_fill_mode_send_two(UART_HandleType* UARTx, uint8_t *buffer, uint16_t length);
	void uart_fill_mode_send_three(UART_HandleType* UARTx, uint8_t *buffer, uint16_t length);
	void uart_fill_mode_send(UART_HandleType* UARTx, uint8_t *buffer, uint16_t length);
	
	void uart_fill_mode_send_start_one(UART_HandleType* UARTx);
	void uart_fill_mode_send_start_two(UART_HandleType* UARTx);
	void uart_fill_mode_send_start_three(UART_HandleType* UARTx);
	void uart_fill_mode_send_start(UART_HandleType* UARTx);

	void uart_printf_log(UART_HandleType* UARTx, char* fmt, va_list args);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* UART_CFG_H_ */