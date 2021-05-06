#include "uart_cfg.h"

// UART0��UART1��ӦSAU0
// UART2��ӦSAU1

#ifdef TYPE_UART1

#if defined(UART_RX_SIZE_MAX_ONE)&&(UART_RX_SIZE_MAX_ONE!=0)
	//===ȫ�ֱ����Ķ���	
	volatile uint8_t g_uart_rx_buffer_one[UART_RX_SIZE_MAX_ONE] = { 0 };
	volatile uint8_t* p_uart_rx_buffer_one = &g_uart_rx_buffer_one[0];
#endif

#if defined(UART_TX_SIZE_MAX_ONE)&&(UART_TX_SIZE_MAX_ONE!=0)
	volatile uint8_t g_uart_tx_buffer_one[UART_TX_SIZE_MAX_ONE] = { 0 };
	volatile uint8_t* p_uart_tx_buffer_one = &g_uart_tx_buffer_one[0];
#endif

#endif

#ifdef TYPE_UART2

#if defined(UART_RX_SIZE_MAX_TWO)&&(UART_RX_SIZE_MAX_TWO!=0)
	//===ȫ�ֱ����Ķ���
	volatile uint8_t g_uart_rx_buffer_two[UART_RX_SIZE_MAX_TWO] = { 0 };
	volatile uint8_t* p_uart_rx_buffer_two = &g_uart_rx_buffer_two[0];
#endif

#if defined(UART_TX_SIZE_MAX_TWO)&&(UART_TX_SIZE_MAX_TWO!=0)
	volatile uint8_t g_uart_tx_buffer_two[UART_TX_SIZE_MAX_TWO] = { 0 };
	volatile uint8_t* p_uart_tx_buffer_two = &g_uart_tx_buffer_two[0];
#endif

#endif

#ifdef TYPE_UART3

#if defined(UART_RX_SIZE_MAX_THREE)&&(UART_RX_SIZE_MAX_THREE!=0)
	//===ȫ�ֱ����Ķ���
	volatile uint8_t g_uart_rx_buffer_three[UART_RX_SIZE_MAX_THREE] = { 0 };
	volatile uint8_t* p_uart_rx_buffer_three = &g_uart_rx_buffer_three[0];
#endif

#if defined(UART_TX_SIZE_MAX_THREE)&&(UART_TX_SIZE_MAX_THREE!=0)
	volatile uint8_t g_uart_tx_buffer_three[UART_TX_SIZE_MAX_THREE] = { 0 };
	volatile uint8_t* p_uart_tx_buffer_three = &g_uart_tx_buffer_three[0];
#endif

#endif

#ifdef TYPE_UART1
	//===ȫ�ֱ�������
	UART_HandleType  g_uart_one = { 0 };
	pUART_HandleType p_uart_one = &g_uart_one;
#endif

#ifdef TYPE_UART2
	//===ȫ�ֱ�������
	UART_HandleType  g_uart_two = { 0 };
	pUART_HandleType p_uart_two = &g_uart_two;
#endif

#ifdef TYPE_UART3
	//=== ȫ�ֱ�������
	UART_HandleType  g_uart_three = { 0 };
	pUART_HandleType p_uart_three = &g_uart_three;
#endif

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ���ݷ��͸�λ
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_send_reset(UART_HandleType* UARTx)
{
	UARTx->msg_uart_txd.msg_state = UART_STATE_OK;
	//---���ݷ������
	UARTx->msg_uart_txd.msg_send_index = 0;
	UARTx->msg_uart_txd.msg_send_index = 0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ���ݽ��ո�λ
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_read_reset(UART_HandleType* UARTx)
{
	UARTx->msg_uart_rxd.msg_state = UART_STATE_BUSY;
	//---���ݽ������
	UARTx->msg_uart_rxd.msg_send_index = 0;
	UARTx->msg_uart_rxd.msg_send_index = 0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: �ȴ����Ϳ���
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_wait_send_idle(UART_HandleType* UARTx)
{
	while (1)
	{
		//---У�鷢�����
		if (UARTx->msg_uart_txd.msg_state==UART_STATE_OK)
		{
			break;
		}
		//---��鳬ʱ
		if (TIME_SPAN(UARTx->msg_uart_txd.msg_f_time_tick(),
			UARTx->msg_uart_txd.msg_time_record)>UARTx->msg_uart_txd.msg_timeout_max)
		{
			break;
		}
		//---ι��
		WDT_RESET();
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_config_init_one(UART_HandleType* UARTx)
{

}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_init_one(UART_HandleType* UARTx)
{
	uart_config_init_one(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_fill_mode_send_one(UART_HandleType* UARTx, uint8_t *buffer, uint16_t length)
{

}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_fill_mode_send_start_one(UART_HandleType* UARTx)
{

}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_config_init_two(UART_HandleType* UARTx)
{
	//---ʹ������ʱ��
	rl78_sau1_clock(1);
	//---��������ʱ��
	SPS0 = _0002_SAU_CK00_FCLK_2 | _0040_SAU_CK01_FCLK_4;
	//---��ʼ������1
	ST0 |= _0008_SAU_CH3_STOP_TRG_ON | _0004_SAU_CH2_STOP_TRG_ON;    /* disable UART1 receive and transmit */
	STMK1 = 1U;    /* disable INTST1 interrupt */
	STIF1 = 0U;    /* clear INTST1 interrupt flag */
	SRMK1 = 1U;    /* disable INTSR1 interrupt */
	SRIF1 = 0U;    /* clear INTSR1 interrupt flag */
	SREMK1 = 1U;   /* disable INTSRE1 interrupt */
	SREIF1 = 0U;   /* clear INTSRE1 interrupt flag */

	//--->>>�ж����ȼ�����
	/* Set INTST1 low priority */
	//---�����ж����ȼ�
	STPR11 = 1U;
	STPR01 = 1U;
	/* Set INTSR1 low priority */
	//---�����ж����ȼ�
	SRPR11 = 1U;
	SRPR01 = 1U;
	/* Set INTSRE1 low priority */
	//---���ܴ����ж����ȼ�
	SREPR11 = 1U;
	SREPR01 = 1U;
	//---<<<�ж����ȼ�����

	//---����ģʽ����
	SMR02 = _0020_SAU_SMRMN_INITIALVALUE | 
			_8000_SAU_CLOCK_SELECT_CK01 | 
			_0000_SAU_TRIGGER_SOFTWARE |
			_0002_SAU_MODE_UART | 
			_0000_SAU_TRANSFER_END;
	//---���ʹ���ģʽ����
	SCR02 = _8000_SAU_TRANSMISSION | 
			_0000_SAU_INTSRE_MASK | 
			_0200_SAU_PARITY_EVEN | 
			_0080_SAU_LSB | 
			_0010_SAU_STOP_1 |
			_0007_SAU_LENGTH_8;	
	//---���Ͳ����ʼ���
	SDR02 = _CE00_UART1_TRANSMIT_DIVISOR;

	//---�������������˲���
	NFEN0 |= _04_SAU_RXD1_FILTER_ON;
	//---���������־λ
	SIR03 = _0004_SAU_SIRMN_FECTMN | 
			_0002_SAU_SIRMN_PECTMN | 
			_0001_SAU_SIRMN_OVCTMN;    /* clear error flag */
	//---����ģʽ����
	SMR03 = _0020_SAU_SMRMN_INITIALVALUE | 
			_8000_SAU_CLOCK_SELECT_CK01 | 
			_0100_SAU_TRIGGER_RXD | 
			_0000_SAU_EDGE_FALL |
			_0002_SAU_MODE_UART | 
			_0000_SAU_TRANSFER_END;
	//---���ʹ���ģʽ����
	SCR03 = _4000_SAU_RECEPTION | 
			_0400_SAU_INTSRE_ENABLE | 
			_0200_SAU_PARITY_EVEN | 
			_0080_SAU_LSB | 
			_0010_SAU_STOP_1 |
			 _0007_SAU_LENGTH_8;
	//---���Ͳ����ʼ���
	SDR03 = _CE00_UART1_RECEIVE_DIVISOR;

	//---���ͺͽ��ܴ���ʱ�����Ϊ0�������������Ϊ1
	SO0 |= _0004_SAU_CH2_DATA_OUTPUT_1;

	//---���ͺͽ��ܴ�������ֱ�����������ȡ�����
	SOL0 |= _0000_SAU_CHANNEL2_NORMAL;       /* output level normal */
	//---������ͨ�ŵ����
	SOE0 |= _0004_SAU_CH2_OUTPUT_ENABLE;    /* enable UART1 output */
	
	//---�˿ڸ���ģʽ
	PIOR = 0x04;
	//gpio_task_pin_mode_ior_set(GPIOP1,GPIO_PIN_BIT_2);
//	/* Set RxD1 pin */
//	//PMC4 &= 0xF7U;
//	//PM4 |= 0x08U;
	//---���ֶ˿��������
	gpio_task_pin_mode_digital(GPIOP4, GPIO_PIN_BIT_3);
	//---���ģʽ
	gpio_task_pin_mode_input(GPIOP4, GPIO_PIN_BIT_3);
	////---����ʹ��
	//gpio_task_pin_mode_pull_up_set(GPIOP4, GPIO_PIN_BIT_3);
	//--->>>����TX�˿�
	//---���ֶ˿��������
	gpio_task_pin_mode_digital(GPIOP4, GPIO_PIN_BIT_2);
	//---����ߵ�ƽ
	gpio_task_pin_set(GPIOP4, GPIO_PIN_BIT_2);
	//---���ģʽ
	gpio_task_pin_mode_output(GPIOP4, GPIO_PIN_BIT_2);
	//---����ʹ��
	gpio_task_pin_mode_pull_up_set(GPIOP4, GPIO_PIN_BIT_2);
	///* Set TxD1 pin */
	//PMC4 &= 0xFBU;
	//P4 |= 0x04U;
	//PM4 &= 0xFBU;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��������
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_start_two(UART_HandleType* UARTx)
{
	SO0 |= _0004_SAU_CH2_DATA_OUTPUT_1;    /* output level normal */
	SOE0 |= _0004_SAU_CH2_OUTPUT_ENABLE;    /* enable UART1 output */
	//---ʹ���շ�
	SS0 |=	_0008_SAU_CH3_START_TRG_ON | 
			_0004_SAU_CH2_START_TRG_ON;    /* enable UART1 receive and transmit */
	
	//---����жϱ�ʶ
	STIF1 = 0U;    /* clear INTST1 interrupt flag */
	SRIF1 = 0U;    /* clear INTSR1 interrupt flag */
	SREIF1 = 0U;   /* clear INTSRE1 interrupt flag */
	//---ʹ���ж�
	STMK1 = 0U;    /* enable INTST1 interrupt */
	SRMK1 = 0U;    /* enable INTSR1 interrupt */
	SREMK1 = 0U;   /* enable INTSRE1 interrupt */
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ֹͣ����
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_stop_two(UART_HandleType* UARTx)
{
	//---��ʹ���ж�
	STMK1 = 1U;    /* disable INTST1 interrupt */
	SRMK1 = 1U;    /* disable INTSR1 interrupt */
	SREMK1 = 1U;   /* disable INTSRE1 interrupt */
	//---�������շ�
	ST0 |=  _0008_SAU_CH3_STOP_TRG_ON | 
			_0004_SAU_CH2_STOP_TRG_ON;    /* disable UART1 receive and transmit */
	//---��ʹ�ܴ������
	SOE0 &= ~_0004_SAU_CH2_OUTPUT_ENABLE;    /* disable UART1 output */
	//---����жϱ�ʶ
	STIF1 = 0U;    /* clear INTST1 interrupt flag */
	SRIF1 = 0U;    /* clear INTSR1 interrupt flag */
	SREIF1 = 0U;   /* clear INTSRE1 interrupt flag */
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_fill_mode_send_two(UART_HandleType* UARTx,uint8_t *buffer,uint16_t length)
{
	//---�ȴ��ϴη������
	//uart_wait_send_idle(UARTx);
	//---��������䵽���ͻ�����
	UARTx->msg_uart_txd.msg_data_length = length;
	UARTx->msg_uart_txd.msg_send_index = length;
	UARTx->msg_uart_txd.msg_read_index =0;
	//---ִ�����ݿ���
	memcpy(UARTx->msg_uart_txd.msg_p_data_buffer, buffer, length);
	//---���÷��ͳ�ʱʱ��
	UARTx->msg_uart_txd.msg_timeout_max = 
		(UARTx->msg_uart_txd.msg_data_length + UART_TX_MAX_TIME_TWO)*UART_BYTE_TIME_ONE / UART_MIN_PULSE_WIDTH;
	//---��ȡʱ��ڵ�
	//UARTx->msg_uart_txd.msg_time_record=UARTx->msg_uart_txd.msg_f_time_tick();
	//---���÷���״̬Ϊ����ģʽ
	UARTx->msg_uart_txd.msg_state= UART_STATE_BUSY;
	//---��ʹ���ж�
	STMK1 = 1U;    /* disable INTST1 interrupt */
	//---����жϱ�ʶ
	//STIF1 = 0U;    /* clear INTST1 interrupt flag */
	//---��������
	TXD1 = UARTx->msg_uart_txd.msg_p_data_buffer[UARTx->msg_uart_txd.msg_read_index];
	UARTx->msg_uart_txd.msg_read_index++;
	//---ʹ���ж�
	STMK1 = 0U;    /* enable INTST1 interrupt */
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ֱ���������ͣ������Ѿ�׼����
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_fill_mode_send_start_two(UART_HandleType* UARTx)
{
	//---�ȴ��ϴη������
	//---��������䵽���ͻ�����
	UARTx->msg_uart_txd.msg_data_length = UARTx->msg_uart_txd.msg_send_index;
	UARTx->msg_uart_txd.msg_read_index = 0;
	//---���÷��ͳ�ʱʱ��
	UARTx->msg_uart_txd.msg_timeout_max =
		(UARTx->msg_uart_txd.msg_data_length + UART_TX_MAX_TIME_TWO)*UART_BYTE_TIME_ONE / UART_MIN_PULSE_WIDTH;
	//---��ȡʱ��ڵ�
	UARTx->msg_uart_txd.msg_time_record = UARTx->msg_uart_txd.msg_f_time_tick();
	//---��ʹ���ж�
	STMK1 = 1U;    /* disable INTST1 interrupt */
	//---����жϱ�ʶ
	STIF1 = 0U;    /* clear INTST1 interrupt flag */
	//---��������
	TXD1 = UARTx->msg_uart_txd.msg_p_data_buffer[UARTx->msg_uart_txd.msg_read_index];
	UARTx->msg_uart_txd.msg_read_index++;
	//---���÷���״̬Ϊ����ģʽ
	UARTx->msg_uart_txd.msg_state = UART_STATE_BUSY;
	//---ʹ���ж�
	STMK1 = 0U;    /* enable INTST1 interrupt */
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_init_two(UART_HandleType* UARTx)
{
	
#ifdef TYPE_UART2
	uart_config_init_two(UARTx);
#if defined(UART_RX_SIZE_MAX_TWO)&&(UART_RX_SIZE_MAX_TWO!=0)
	//---��������ַ��ʼ��
	UARTx->msg_uart_txd.msg_p_data_buffer = p_uart_tx_buffer_two;
	UARTx->msg_uart_rxd.msg_p_data_buffer = p_uart_rx_buffer_two;
#endif
#if defined(UART_TX_SIZE_MAX_TWO)&&(UART_TX_SIZE_MAX_TWO!=0)
	//---��������ַ��ʼ��
	UARTx->msg_uart_txd.msg_p_data_buffer = p_uart_tx_buffer_two;
	UARTx->msg_uart_rxd.msg_p_data_buffer = p_uart_rx_buffer_two;
#endif

	UARTx->msg_uart_rxd.msg_step=0;
	UARTx->msg_uart_rxd.msg_state=UART_STATE_BUSY;
	UARTx->msg_uart_rxd.msg_send_index = 0;
	UARTx->msg_uart_rxd.msg_read_index = 0;
	UARTx->msg_uart_rxd.msg_data_length = 0;

	UARTx->msg_uart_txd.msg_step = 0;
	UARTx->msg_uart_txd.msg_state = UART_STATE_OK;
	UARTx->msg_uart_txd.msg_send_index = 0;
	UARTx->msg_uart_txd.msg_read_index = 0;
	UARTx->msg_uart_txd.msg_data_length = 0;
	uart_start_two(UARTx);
#endif
	
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_config_init_three(UART_HandleType* UARTx)
{

}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_init_three(UART_HandleType* UARTx)
{
	uart_config_init_three(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_fill_mode_send_three(UART_HandleType* UARTx, uint8_t *buffer, uint16_t length)
{

}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_fill_mode_send_start_three(UART_HandleType* UARTx)
{

}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ���ܴ���
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_it_irq_read_handle_one(UART_HandleType* UARTx)
{

}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ���ܴ�����
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_it_irq_read_error_handle_one(UART_HandleType* UARTx)
{

}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ���ʹ���
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_it_irq_send_handle_one(UART_HandleType* UARTx)
{

}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ���ܴ���
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_it_irq_read_handle_two(UART_HandleType* UARTx)
{

}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ���ܴ�����
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_it_irq_read_error_handle_two(UART_HandleType* UARTx)
{

}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ���ʹ���
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_it_irq_send_handle_two(UART_HandleType* UARTx)
{
	if (UARTx->msg_uart_txd.msg_send_index!=0)
	{
		//---У�����ݷ���״̬
		if (UARTx->msg_uart_txd.msg_read_index != UARTx->msg_uart_txd.msg_send_index)
		{
			//--->>>����δ�������
			TXD1 = UARTx->msg_uart_txd.msg_p_data_buffer[UARTx->msg_uart_txd.msg_read_index];
			UARTx->msg_uart_txd.msg_read_index++;
		}
		else
		{
			//---��ʹ���ж�
			STMK1 = 1U;    /* disable INTST1 interrupt */
			//---���ݷ��͸�λ
			uart_send_reset(UARTx);
		}
	}
	else
	{
		//---��ʹ���ж�
		STMK1 = 1U;    /* disable INTST1 interrupt */
		//---���ݷ��͸�λ
		uart_send_reset(UARTx);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ���ܴ���
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_it_irq_read_handle_three(UART_HandleType* UARTx)
{

}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ���ܴ�����
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_it_irq_read_error_handle_three(UART_HandleType* UARTx)
{

}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ���ʹ���
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_it_irq_send_handle_three(UART_HandleType* UARTx)
{

}


///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ���ܴ���
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_it_irq_read_handle(UART_HandleType* UARTx)
{
	//---�˿ڳ�ʼ��
#ifdef TYPE_UART1
	if ((UARTx != NULL) && (UARTx == UART_TASK_ONE))
	{
		uart_it_irq_read_handle_one(UARTx);
		return;
	}
#endif
#ifdef TYPE_UART2
	if ((UARTx != NULL) && (UARTx == UART_TASK_TWO))
	{
		uart_it_irq_read_handle_two(UARTx);
		return;
	}
#endif
#ifdef TYPE_UART3
	if ((UARTx != NULL) && (UARTx == UART_TASK_THREE))
	{
		uart_it_irq_read_handle_three(UARTx);
		return;
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ���ܴ�����
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_it_irq_read_error_handle(UART_HandleType* UARTx)
{
	//---�˿ڳ�ʼ��
#ifdef TYPE_UART1
	if ((UARTx != NULL) && (UARTx == UART_TASK_ONE))
	{
		uart_it_irq_read_error_handle_one(UARTx);
		return;
	}
#endif
#ifdef TYPE_UART2
	if ((UARTx != NULL) && (UARTx == UART_TASK_TWO))
	{
		uart_it_irq_read_error_handle_two(UARTx);
		return;
	}
#endif
#ifdef TYPE_UART3
	if ((UARTx != NULL) && (UARTx == UART_TASK_THREE))
	{
		uart_it_irq_read_error_handle_three(UARTx);
		return;
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ���ʹ���
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_it_irq_send_handle(UART_HandleType* UARTx)
{
	//---�˿ڳ�ʼ��
#ifdef TYPE_UART1
	if ((UARTx != NULL) && (UARTx == UART_TASK_ONE))
	{
		uart_it_irq_send_handle_one(UARTx);
		return;
	}
#endif
#ifdef TYPE_UART2
	if ((UARTx != NULL) && (UARTx == UART_TASK_TWO))
	{
		uart_it_irq_send_handle_two(UARTx);
		return;
	}
#endif
#ifdef TYPE_UART3
	if ((UARTx != NULL) && (UARTx == UART_TASK_THREE))
	{
		uart_it_irq_send_handle_three(UARTx);
		return;
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ���ģʽ���ʹ���
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_fill_mode_send(UART_HandleType* UARTx, uint8_t *buffer, uint16_t length)
{
	//---�˿ڳ�ʼ��
#ifdef TYPE_UART1
	if ((UARTx != NULL) && (UARTx == UART_TASK_ONE))
	{
		uart_fill_mode_send_one(UARTx, buffer, length);
		return;
	}
#endif
#ifdef TYPE_UART2
	if ((UARTx != NULL) && (UARTx == UART_TASK_TWO))
	{
		uart_fill_mode_send_two(UARTx,buffer,length);
		return;
	}
#endif
#ifdef TYPE_UART3
	if ((UARTx != NULL) && (UARTx == UART_TASK_THREE))
	{
		uart_fill_mode_send_three(UARTx, buffer, length);
		return;
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ���ģʽ���ʹ���
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_fill_mode_send_start(UART_HandleType* UARTx)
{
	//---�˿ڳ�ʼ��
#ifdef TYPE_UART1
	if ((UARTx != NULL) && (UARTx == UART_TASK_ONE))
	{
		uart_fill_mode_send_start_one(UARTx);
		return;
	}
#endif
#ifdef TYPE_UART2
	if ((UARTx != NULL) && (UARTx == UART_TASK_TWO))
	{
		uart_fill_mode_send_start_two(UARTx);
		return;
	}
#endif
#ifdef TYPE_UART3
	if ((UARTx != NULL) && (UARTx == UART_TASK_THREE))
	{
		uart_fill_mode_send_start_three(UARTx);
		return;
	}
#endif
}