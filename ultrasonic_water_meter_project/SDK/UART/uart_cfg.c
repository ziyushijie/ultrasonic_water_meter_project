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
	UARTx->msg_uart_txd.msg_read_index = 0;
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
	UARTx->msg_uart_rxd.msg_read_index = 0;
	UARTx->msg_uart_rxd.msg_send_index = 0;
	//---�������ݽ��յ����
	UARTx->msg_uart_rxd.msg_step = 0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ���ݽ��ո�λ
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t uart_read_end(UART_HandleType* UARTx)
{
	if (UARTx->msg_uart_rxd.msg_step!=0)
	{
		//---�ж��Ƿ������ݽ��յĳ�ʱ����
		if (TIME_SPAN(UARTx->msg_uart_rxd.msg_f_time_tick(), UARTx->msg_uart_rxd.msg_time_tick)>
			UARTx->msg_uart_rxd.msg_timeout_max)
		{
			//---�������ݵĳ���
			UARTx->msg_uart_rxd.msg_data_length = UARTx->msg_uart_rxd.msg_read_index;
			//---�������ݽ��յ����
			UARTx->msg_uart_rxd.msg_step = 0;
			//---���ݽ������
			UARTx->msg_uart_rxd.msg_state = UART_STATE_OK;
			//---���ݽ������
			return OK_0;
		}
	}
	return ERROR_1;
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
		if (TIME_SPAN(UARTx->msg_uart_txd.msg_f_time_tick(),UARTx->msg_uart_txd.msg_time_record)>
			UARTx->msg_uart_txd.msg_timeout_max)
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
uint8_t uart_init_one(UART_HandleType* UARTx)
{
	uart_config_init_one(UARTx);
	return OK_0;
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
void uart_fill_mode_send_buffer_one(UART_HandleType* UARTx, uint8_t *buffer, uint16_t length)
{

}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t uart_config_init_two(UART_HandleType* UARTx)
{
#ifdef TYPE_UART2
	//---ʹ������ʱ��
	//rl78_sau1_clock(1);
	rl78_perpheral_clock_enable(PERIPHERAL_UART2);
	//---��������ʱ��
	/*SPS0 =	_0002_SAU_CK00_FCLK_2 | 
			_0040_SAU_CK01_FCLK_4;*/
	SPS0 = _0001_SAU_CK00_FCLK_1 |
		_0040_SAU_CK01_FCLK_4;
	//---��ʼ������1
	ST0 |=	_0008_SAU_CH3_STOP_TRG_ON | 
			_0004_SAU_CH2_STOP_TRG_ON;   

	STMK1 = 1U;    
	STIF1 = 0U;    
	SRMK1 = 1U;    
	SRIF1 = 0U;    
	SREMK1 = 1U;   
	SREIF1 = 0U;   

	//--->>>�ж����ȼ�����
	//---�����ж����ȼ�
	STPR11 = 1U;
	STPR01 = 1U;
	//---�����ж����ȼ�
	SRPR11 = 1U;
	SRPR01 = 1U;
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
			_0001_SAU_SIRMN_OVCTMN;   
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
	SOL0 |= _0000_SAU_CHANNEL2_NORMAL;       
	//---������ͨ�ŵ����
	SOE0 |= _0004_SAU_CH2_OUTPUT_ENABLE;   
	
	//---�˿ڸ���ģʽ
	//PIOR = 0x04;
	gpio_task_pin_mode_ior_set(GPIOP0, GPIO_PIN_BIT_2);
	/* Set RxD1 pin */
	//PMC4 &= 0xF7U;
	//PM4 |= 0x08U;
	//---���ֶ˿��������
	gpio_task_pin_mode_digital(GPIOP4, GPIO_PIN_BIT_3);
	//---���ģʽ
	gpio_task_pin_mode_input(GPIOP4, GPIO_PIN_BIT_3);
	////---����ʹ��
	//gpio_task_pin_mode_pull_up_set(GPIOP4, GPIO_PIN_BIT_3);
	//--->>>����TX�˿�
	/* Set TxD1 pin */
	//PMC4 &= 0xFBU;
	//P4 |= 0x04U;
	//PM4 &= 0xFBU;
	//---���ֶ˿��������
	gpio_task_pin_mode_digital(GPIOP4, GPIO_PIN_BIT_2);
	//---����ߵ�ƽ
	gpio_task_pin_set(GPIOP4, GPIO_PIN_BIT_2);
	//---���ģʽ
	gpio_task_pin_mode_output(GPIOP4, GPIO_PIN_BIT_2);
	//---����ʹ��
	gpio_task_pin_mode_pull_up_set(GPIOP4, GPIO_PIN_BIT_2);
#endif
	return OK_0;
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
#ifdef TYPE_UART2
	SO0 |= _0004_SAU_CH2_DATA_OUTPUT_1;
	SOE0 |= _0004_SAU_CH2_OUTPUT_ENABLE;
	//---ʹ���շ�
	SS0 |=	_0008_SAU_CH3_START_TRG_ON | 
			_0004_SAU_CH2_START_TRG_ON;   
	
	//---����жϱ�ʶ
	STIF1 = 0U; 
	SRIF1 = 0U; 
	SREIF1 = 0U;
	//---ʹ���ж�
	STMK1 = 0U;  
	SRMK1 = 0U;  
	SREMK1 = 0U; 
#endif
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
#ifdef TYPE_UART2
	//---��ʹ���ж�
	STMK1 = 1U; 
	SRMK1 = 1U; 
	SREMK1 = 1U;
	//---�������շ�
	ST0 |=  _0008_SAU_CH3_STOP_TRG_ON | 
			_0004_SAU_CH2_STOP_TRG_ON;  
	//---��ʹ�ܴ������
	SOE0 &= ~_0004_SAU_CH2_OUTPUT_ENABLE;   
	//---����жϱ�ʶ
	STIF1 = 0U;  
	SRIF1 = 0U;  
	SREIF1 = 0U; 
#endif
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
	uart_wait_send_idle(UARTx);
#ifdef TYPE_UART2
	if (length > UART_TX_SIZE_MAX_TWO)
	{
		length = UART_RX_SIZE_MAX_TWO;
	}
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
	UARTx->msg_uart_txd.msg_time_record=UARTx->msg_uart_txd.msg_f_time_tick();
	//---���÷���״̬Ϊ����ģʽ
	UARTx->msg_uart_txd.msg_state= UART_STATE_BUSY;
	//---��ʹ���ж�
	STMK1 = 1U;  
	//---����жϱ�ʶ
	STIF1 = 0U; 
	//---��������
	TXD1 = UARTx->msg_uart_txd.msg_p_data_buffer[UARTx->msg_uart_txd.msg_read_index];
	UARTx->msg_uart_txd.msg_read_index++;
	//---ʹ���ж�
	STMK1 = 0U;
#endif
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
	uart_wait_send_idle(UARTx);
#ifdef TYPE_UART2
	if (UARTx->msg_uart_txd.msg_send_index > UART_TX_SIZE_MAX_TWO)
	{
		UARTx->msg_uart_txd.msg_send_index = UART_RX_SIZE_MAX_TWO;
	}
	//---��������䵽���ͻ�����
	UARTx->msg_uart_txd.msg_data_length = UARTx->msg_uart_txd.msg_send_index;
	UARTx->msg_uart_txd.msg_read_index = 0;
	//---���÷��ͳ�ʱʱ��
	UARTx->msg_uart_txd.msg_timeout_max =
		(UARTx->msg_uart_txd.msg_data_length + UART_TX_MAX_TIME_TWO)*UART_BYTE_TIME_ONE / UART_MIN_PULSE_WIDTH;
	//---��ȡʱ��ڵ�
	UARTx->msg_uart_txd.msg_time_record = UARTx->msg_uart_txd.msg_f_time_tick();
	//---��ʹ���ж�
	STMK1 = 1U;   
	//---����жϱ�ʶ
	STIF1 = 0U;
	//---��������
	TXD1 = UARTx->msg_uart_txd.msg_p_data_buffer[UARTx->msg_uart_txd.msg_read_index];
	UARTx->msg_uart_txd.msg_read_index++;
	//---���÷���״̬Ϊ����ģʽ
	UARTx->msg_uart_txd.msg_state = UART_STATE_BUSY;
	//---ʹ���ж�
	STMK1 = 0U;
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_fill_mode_send_buffer_two(UART_HandleType* UARTx, uint8_t *buffer, uint16_t length)
{
#ifdef TYPE_UART2
	if (length>UART_TX_SIZE_MAX_TWO)
	{
		length = UART_RX_SIZE_MAX_TWO;
	}
	//---��������䵽���ͻ�����
	UARTx->msg_uart_txd.msg_data_length = length;
	UARTx->msg_uart_txd.msg_send_index = length;
	UARTx->msg_uart_txd.msg_read_index = 0;
	//---���÷��ͳ�ʱʱ��
	UARTx->msg_uart_txd.msg_timeout_max =
		(UARTx->msg_uart_txd.msg_data_length + UART_TX_MAX_TIME_TWO)*UART_BYTE_TIME_ONE / UART_MIN_PULSE_WIDTH;
	//---��ȡʱ��ڵ�
	UARTx->msg_uart_txd.msg_time_record=UARTx->msg_uart_txd.msg_f_time_tick();
	//---���÷���״̬Ϊ����ģʽ
	UARTx->msg_uart_txd.msg_state = UART_STATE_BUSY;
	//---��ʹ���ж�
	STMK1 = 1U; 
	//---����жϱ�ʶ
	STIF1 = 0U;
	//---��������
	TXD1 = UARTx->msg_uart_txd.msg_p_data_buffer[UARTx->msg_uart_txd.msg_read_index];
	UARTx->msg_uart_txd.msg_read_index++;
	//---ʹ���ж�
	STMK1 = 0U; 
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t uart_init_two(UART_HandleType* UARTx)
{	
#ifdef TYPE_UART2
	uart_config_init_two(UARTx);
#if defined(UART_RX_SIZE_MAX_TWO)&&(UART_RX_SIZE_MAX_TWO!=0)
	//---��������ַ��ʼ��
	UARTx->msg_uart_rxd.msg_p_data_buffer = p_uart_rx_buffer_two;
#endif
#if defined(UART_TX_SIZE_MAX_TWO)&&(UART_TX_SIZE_MAX_TWO!=0)
	//---��������ַ��ʼ��
	UARTx->msg_uart_txd.msg_p_data_buffer = p_uart_tx_buffer_two;
#endif

	UARTx->msg_uart_rxd.msg_step=0;
	UARTx->msg_uart_rxd.msg_state=UART_STATE_BUSY;
	UARTx->msg_uart_rxd.msg_send_index = 0;
	UARTx->msg_uart_rxd.msg_read_index = 0;
	UARTx->msg_uart_rxd.msg_data_length = 0;
	//---�����������ʱʱ��
	UARTx->msg_uart_rxd.msg_timeout_max = UART_BYTE_TIME_ONE * 2;

	UARTx->msg_uart_txd.msg_step = 0;
	UARTx->msg_uart_txd.msg_state = UART_STATE_OK;
	UARTx->msg_uart_txd.msg_send_index = 0;
	UARTx->msg_uart_txd.msg_read_index = 0;
	UARTx->msg_uart_txd.msg_data_length = 0;
	uart_start_two(UARTx);
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t uart_config_init_three(UART_HandleType* UARTx)
{
#ifdef TYPE_UART3
	//---ʹ������ʱ��
	//rl78_sau1_clock(1);
	rl78_perpheral_clock_enable(PERIPHERAL_UART3);
	//---��������ʱ��
	SPS1 = _0001_SAU_CK00_FCLK_1 |
		_0040_SAU_CK01_FCLK_4;
	//---��ʼ������1
	ST1 |=	_0002_SAU_CH1_STOP_TRG_ON | 
			_0001_SAU_CH0_STOP_TRG_ON;

	STMK2 = 1U;
	STIF2 = 0U;
	SRMK2 = 1U;
	SRIF2 = 0U;
	SREMK2 = 1U;
	SREIF2 = 0U;

	//--->>>�ж����ȼ�����
	//---�����ж����ȼ�
	STPR12 = 1U;
	STPR02 = 1U;
	//---�����ж����ȼ�
	SRPR12 = 1U;
	SRPR02 = 1U;
	//---���ܴ����ж����ȼ�
	SREPR12 = 1U;
	SREPR02 = 1U;
	//---<<<�ж����ȼ�����

	//---����ģʽ����
	SMR10 = _0020_SAU_SMRMN_INITIALVALUE | 
			_0000_SAU_CLOCK_SELECT_CK00 | 
			_0000_SAU_TRIGGER_SOFTWARE |
			_0002_SAU_MODE_UART | 
			_0000_SAU_TRANSFER_END;
	//---���ʹ���ģʽ����
	SCR10 =	_8000_SAU_TRANSMISSION | 
			_0000_SAU_INTSRE_MASK | 
			_0200_SAU_PARITY_EVEN | 
			_0080_SAU_LSB |
			_0010_SAU_STOP_1 | 
			_0007_SAU_LENGTH_8;
	//---���Ͳ����ʼ���
	SDR10 = _CE00_UART2_TRANSMIT_DIVISOR;
	//---�������������˲���
	NFEN0 |= _10_SAU_RXD2_FILTER_ON;
	//---���������־λ
	SIR11 = _0004_SAU_SIRMN_FECTMN | 
			_0002_SAU_SIRMN_PECTMN | 
			_0001_SAU_SIRMN_OVCTMN;
	//---����ģʽ����
	SMR11 = _0020_SAU_SMRMN_INITIALVALUE | 
			_0000_SAU_CLOCK_SELECT_CK00 | 
			_0100_SAU_TRIGGER_RXD | 
			_0000_SAU_EDGE_FALL |
			_0002_SAU_MODE_UART | 
			_0000_SAU_TRANSFER_END;
	//---���ʹ���ģʽ����
	SCR11 = _4000_SAU_RECEPTION | 
			_0400_SAU_INTSRE_ENABLE | 
			_0200_SAU_PARITY_EVEN | 
			_0080_SAU_LSB | 
			_0010_SAU_STOP_1 |
			_0007_SAU_LENGTH_8;
	//---���Ͳ����ʼ���
	SDR11 = _CE00_UART2_RECEIVE_DIVISOR;
	//---���ͺͽ��ܴ���ʱ�����Ϊ0�������������Ϊ1
	SO1 |= _0001_SAU_CH0_DATA_OUTPUT_1;

	//---���ͺͽ��ܴ�������ֱ�����������ȡ�����
	SOL1 |= _0000_SAU_CHANNEL0_NORMAL;
	//---������ͨ�ŵ����
	SOE1 |= _0001_SAU_CH0_OUTPUT_ENABLE;

	//---�˿ڸ���ģʽ
	//PIOR = 0x04;
	//gpio_task_pin_mode_ior_set(GPIOP0, GPIO_PIN_BIT_2);
	/* Set RxD1 pin */
	//PFSEG5 &= 0x7FU;
	//PM0 |= 0x08U;
	//---���ֶ˿��������
	gpio_task_pin_mode_digital(GPIOP0, GPIO_PIN_BIT_3);
	//---����ģʽ
	gpio_task_pin_mode_input(GPIOP0, GPIO_PIN_BIT_3);
	////---����ʹ��
	//gpio_task_pin_mode_pull_up_set(GPIOP4, GPIO_PIN_BIT_3);
	//--->>>����TX�˿�
	/* Set TxD2 pin */
	//PFSEG6 &= 0xFEU;
	//P0 |= 0x10U;
	//PM0 &= 0xEFU;
	//---���ֶ˿��������
	gpio_task_pin_mode_digital(GPIOP0, GPIO_PIN_BIT_4);
	//---����ߵ�ƽ
	gpio_task_pin_set(GPIOP0, GPIO_PIN_BIT_4);
	//---���ģʽ
	gpio_task_pin_mode_output(GPIOP0, GPIO_PIN_BIT_4);
	//---����ʹ��
	gpio_task_pin_mode_pull_up_set(GPIOP0, GPIO_PIN_BIT_4);
#endif
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��������
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_start_three(UART_HandleType* UARTx)
{
#ifdef TYPE_UART3
	SO1 |= _0001_SAU_CH0_DATA_OUTPUT_1;
	SOE1 |= _0001_SAU_CH0_OUTPUT_ENABLE;
	//---ʹ���շ�
	SS1 |=	_0002_SAU_CH1_START_TRG_ON |
			_0001_SAU_CH0_START_TRG_ON;

	//---����жϱ�ʶ
	STIF2 = 0U;
	SRIF2 = 0U;   
	SREIF2 = 0U;   
	//---ʹ���ж�
	STMK2 = 0U;
	SRMK2 = 0U;
	SREMK2 = 0U;
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ֹͣ����
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_stop_three(UART_HandleType* UARTx)
{
#ifdef TYPE_UART3
	//---��ʹ���ж�
	STMK2 = 1U;   
	SRMK2 = 1U; 
	SREMK2 = 1U; 
	//---��ʹ���շ�
	ST1 |=	_0002_SAU_CH1_STOP_TRG_ON |
			_0001_SAU_CH0_STOP_TRG_ON;
	//---��ʹ�ܴ������
	SOE1 &= ~_0001_SAU_CH0_OUTPUT_ENABLE;
	//---����жϱ�ʶ
	STIF2 = 0U;   
	SRIF2 = 0U; 
	SREIF2 = 0U; 
#endif
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
	//---�ȴ��ϴη������
	uart_wait_send_idle(UARTx);
#ifdef TYPE_UART3
	if (length > UART_TX_SIZE_MAX_THREE)
	{
		length = UART_RX_SIZE_MAX_THREE;
	}
	//---��������䵽���ͻ�����
	UARTx->msg_uart_txd.msg_data_length = length;
	UARTx->msg_uart_txd.msg_send_index = length;
	UARTx->msg_uart_txd.msg_read_index = 0;
	//---ִ�����ݿ���
	memcpy(UARTx->msg_uart_txd.msg_p_data_buffer, buffer, length);
	//---���÷��ͳ�ʱʱ��
	UARTx->msg_uart_txd.msg_timeout_max =
		(UARTx->msg_uart_txd.msg_data_length + UART_TX_MAX_TIME_THREE)*UART_BYTE_TIME_ONE / UART_MIN_PULSE_WIDTH;
	//---��ȡʱ��ڵ�
	UARTx->msg_uart_txd.msg_time_record = UARTx->msg_uart_txd.msg_f_time_tick();
	//---���÷���״̬Ϊ����ģʽ
	UARTx->msg_uart_txd.msg_state = UART_STATE_BUSY;
	//---��ʹ���ж�
	STMK2 = 1U;
	//---����жϱ�ʶ
	STIF2 = 0U;
	//---��������
	TXD2 = UARTx->msg_uart_txd.msg_p_data_buffer[UARTx->msg_uart_txd.msg_read_index];
	UARTx->msg_uart_txd.msg_read_index++;
	//---ʹ���ж�
	STMK2 = 0U;
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ֱ���������ͣ������Ѿ�׼����
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_fill_mode_send_start_three(UART_HandleType* UARTx)
{
	//---�ȴ��ϴη������
	uart_wait_send_idle(UARTx);
#ifdef TYPE_UART3
	if (UARTx->msg_uart_txd.msg_send_index > UART_TX_SIZE_MAX_THREE)
	{
		UARTx->msg_uart_txd.msg_send_index = UART_RX_SIZE_MAX_THREE;
	}
	//---��������䵽���ͻ�����
	UARTx->msg_uart_txd.msg_data_length = UARTx->msg_uart_txd.msg_send_index;
	UARTx->msg_uart_txd.msg_read_index = 0;
	//---���÷��ͳ�ʱʱ��
	UARTx->msg_uart_txd.msg_timeout_max =
		(UARTx->msg_uart_txd.msg_data_length + UART_TX_MAX_TIME_THREE)*UART_BYTE_TIME_ONE / UART_MIN_PULSE_WIDTH;
	//---��ȡʱ��ڵ�
	UARTx->msg_uart_txd.msg_time_record = UARTx->msg_uart_txd.msg_f_time_tick();
	//---��ʹ���ж�
	STMK2 = 1U;
	//---����жϱ�ʶ
	STIF2 = 0U;
	//---��������
	TXD2 = UARTx->msg_uart_txd.msg_p_data_buffer[UARTx->msg_uart_txd.msg_read_index];
	UARTx->msg_uart_txd.msg_read_index++;
	//---���÷���״̬Ϊ����ģʽ
	UARTx->msg_uart_txd.msg_state = UART_STATE_BUSY;
	//---ʹ���ж�
	STMK2 = 0U;
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_fill_mode_send_buffer_three(UART_HandleType* UARTx, uint8_t *buffer, uint16_t length)
{
#ifdef TYPE_UART3
	if (length > UART_TX_SIZE_MAX_THREE)
	{
		length = UART_RX_SIZE_MAX_THREE;
	}
	//---��������䵽���ͻ�����
	UARTx->msg_uart_txd.msg_data_length = length;
	UARTx->msg_uart_txd.msg_send_index = length;
	UARTx->msg_uart_txd.msg_read_index = 0;
	//---���÷��ͳ�ʱʱ��
	UARTx->msg_uart_txd.msg_timeout_max =
		(UARTx->msg_uart_txd.msg_data_length + UART_TX_MAX_TIME_THREE)*UART_BYTE_TIME_ONE / UART_MIN_PULSE_WIDTH;
	//---��ȡʱ��ڵ�
	UARTx->msg_uart_txd.msg_time_record = UARTx->msg_uart_txd.msg_f_time_tick();
	//---���÷���״̬Ϊ����ģʽ
	UARTx->msg_uart_txd.msg_state = UART_STATE_BUSY;
	//---��ʹ���ж�
	STMK2 = 1U;
	//---����жϱ�ʶ
	STIF2 = 0U;
	//---��������
	TXD2 = UARTx->msg_uart_txd.msg_p_data_buffer[UARTx->msg_uart_txd.msg_read_index];
	UARTx->msg_uart_txd.msg_read_index++;
	//---ʹ���ж�
	STMK2 = 0U;
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t uart_init_three(UART_HandleType* UARTx)
{
#ifdef TYPE_UART3
	uart_config_init_three(UARTx);
#if defined(UART_RX_SIZE_MAX_THREE)&&(UART_RX_SIZE_MAX_THREE!=0)
	//---��������ַ��ʼ��
	UARTx->msg_uart_rxd.msg_p_data_buffer = p_uart_rx_buffer_three;
#endif
#if defined(UART_TX_SIZE_MAX_THREE)&&(UART_TX_SIZE_MAX_THREE!=0)
	//---��������ַ��ʼ��
	UARTx->msg_uart_txd.msg_p_data_buffer = p_uart_tx_buffer_three;
#endif

	UARTx->msg_uart_rxd.msg_step = 0;
	UARTx->msg_uart_rxd.msg_state = UART_STATE_BUSY;
	UARTx->msg_uart_rxd.msg_send_index = 0;
	UARTx->msg_uart_rxd.msg_read_index = 0;
	UARTx->msg_uart_rxd.msg_data_length = 0;
	//---�����������ʱʱ��
	UARTx->msg_uart_rxd.msg_timeout_max = UART_BYTE_TIME_ONE * 2;

	UARTx->msg_uart_txd.msg_step = 0;
	UARTx->msg_uart_txd.msg_state = UART_STATE_OK;
	UARTx->msg_uart_txd.msg_send_index = 0;
	UARTx->msg_uart_txd.msg_read_index = 0;
	UARTx->msg_uart_txd.msg_data_length = 0;
	//---��������
	uart_start_three(UARTx);
#endif
	return OK_0;
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
#ifdef TYPE_UART1
	//---���ݻ�����
	vltuint8_t temp_rx = 0;
	//---�ж����ݽ����Ƿ����
	if (UARTx->msg_uart_rxd.msg_state == UART_STATE_BUSY)
	{
		//---������յ�������
		temp_rx = RXD0;
		//---���ν�������
		switch (UARTx->msg_uart_rxd.msg_step)
		{
			case 0:
			{
				if (UARTx->msg_uart_rxd.msg_read_index != 0)
				{
					UARTx->msg_uart_rxd.msg_read_index = 0;
				}
				//---�洢���յ�����
				UARTx->msg_uart_rxd.msg_p_data_buffer[UARTx->msg_uart_rxd.msg_read_index++] = temp_rx;
				//---����ʱ�����
				UARTx->msg_uart_rxd.msg_time_tick = UARTx->msg_uart_rxd.msg_f_time_tick();
				//---��¼���յĵ�һ������
				UARTx->msg_uart_rxd.msg_time_record = UARTx->msg_uart_rxd.msg_f_time_tick();
				//---ִ����һ����
				UARTx->msg_uart_rxd.msg_step++;
				break;
			}
			case 1:
			{
				//---�洢���յ�������
				UARTx->msg_uart_rxd.msg_p_data_buffer[UARTx->msg_uart_rxd.msg_read_index++] = temp_rx;
				//---����ʱ�����
				UARTx->msg_uart_rxd.msg_time_tick = UARTx->msg_uart_rxd.msg_f_time_tick();
				//---�ж����ݵĽ����Ƿ񳬳�������
				if (UARTx->msg_uart_rxd.msg_read_index > UART_RX_SIZE_MAX_ONE)
				{
					UARTx->msg_uart_rxd.msg_read_index = 0;
				}
				break;
			}
			default:
			{
				break;
			}
		}
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
void uart_it_irq_read_error_handle_one(UART_HandleType* UARTx)
{
#ifdef TYPE_UART1
	//---���ݻ�����
	vltuint8_t temp_rx = 0;
	//---��ȡ�յ�������
	temp_rx = RXD0;
	//---��ȡ�����ʶ
	UARTx->msg_uart_rxd.msg_send_index = (SSR01 & 0x0007U);
	//---��������־λ
	SSR01 = UARTx->msg_uart_rxd.msg_send_index;
	//---���ݷ��͸�λ
	uart_read_reset(UARTx);
#endif
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
#ifdef TYPE_UART1
	if (UARTx->msg_uart_txd.msg_send_index != 0)
	{
		//---У�����ݷ���״̬
		if (UARTx->msg_uart_txd.msg_read_index != UARTx->msg_uart_txd.msg_send_index)
		{
			//--->>>����δ�������
			TXD0 = UARTx->msg_uart_txd.msg_p_data_buffer[UARTx->msg_uart_txd.msg_read_index];
			UARTx->msg_uart_txd.msg_read_index++;
		}
		else
		{
			//---��ʹ���ж�
			STMK0 = 1U;    /* disable INTST1 interrupt */
			//---���ݷ��͸�λ
			uart_send_reset(UARTx);
		}
	}
	else
	{
		//---��ʹ���ж�
		STMK0 = 1U;    /* disable INTST1 interrupt */
		//---���ݷ��͸�λ
		uart_send_reset(UARTx);
	}
#endif
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
#ifdef TYPE_UART2
	//---���ݻ�����
	vltuint8_t temp_rx = 0;
	//---�ж����ݽ����Ƿ����
	if (UARTx->msg_uart_rxd.msg_state== UART_STATE_BUSY)
	{
		//---������յ�������
		temp_rx = RXD1;
		//---���ν�������
		switch (UARTx->msg_uart_rxd.msg_step)
		{
			case 0:
			{
				if (UARTx->msg_uart_rxd.msg_read_index!=0)
				{
					UARTx->msg_uart_rxd.msg_read_index = 0;
				}
				//---�洢���յ�����
				UARTx->msg_uart_rxd.msg_p_data_buffer[UARTx->msg_uart_rxd.msg_read_index++] = temp_rx;
				//---����ʱ�����
				UARTx->msg_uart_rxd.msg_time_tick = UARTx->msg_uart_rxd.msg_f_time_tick();
				//---��¼���յĵ�һ������
				UARTx->msg_uart_rxd.msg_time_record = UARTx->msg_uart_rxd.msg_f_time_tick();
				//---ִ����һ����
				UARTx->msg_uart_rxd.msg_step++;
				break;
			}
			case 1:
			{
				//---�洢���յ�������
				UARTx->msg_uart_rxd.msg_p_data_buffer[UARTx->msg_uart_rxd.msg_read_index++] = temp_rx;
				//---����ʱ�����
				UARTx->msg_uart_rxd.msg_time_tick = UARTx->msg_uart_rxd.msg_f_time_tick();
				//---�ж����ݵĽ����Ƿ񳬳�������
				if (UARTx->msg_uart_rxd.msg_read_index>UART_RX_SIZE_MAX_TWO)
				{
					UARTx->msg_uart_rxd.msg_read_index = 0;
				}
				break;
			}
			default:
			{
				break;
			}
		}
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
void uart_it_irq_read_error_handle_two(UART_HandleType* UARTx)
{
#ifdef TYPE_UART2
	//---���ݻ�����
	vltuint8_t temp_rx = 0;
	//---��ȡ�յ�������
	temp_rx = RXD1;
	//---��ȡ�����ʶ
	UARTx->msg_uart_rxd.msg_send_index= (SSR03 & 0x0007U);
	//---��������־λ
	SIR03 = UARTx->msg_uart_rxd.msg_send_index;
	//---���ݷ��͸�λ
	uart_read_reset(UARTx);
#endif
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
#ifdef TYPE_UART2
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
			STMK1 = 1U;    /* disable INTST2 interrupt */
			//---���ݷ��͸�λ
			uart_send_reset(UARTx);
		}
	}
	else
	{
		//---��ʹ���ж�
		STMK1 = 1U;    /* disable INTST2 interrupt */
		//---���ݷ��͸�λ
		uart_send_reset(UARTx);
	}
#endif
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
#ifdef TYPE_UART3
	//---���ݻ�����
	vltuint8_t temp_rx = 0;
	//---�ж����ݽ����Ƿ����
	if (UARTx->msg_uart_rxd.msg_state == UART_STATE_BUSY)
	{
		//---������յ�������
		temp_rx = RXD2;
		//---���ν�������
		switch (UARTx->msg_uart_rxd.msg_step)
		{
			case 0:
			{
				if (UARTx->msg_uart_rxd.msg_read_index != 0)
				{
					UARTx->msg_uart_rxd.msg_read_index = 0;
				}
				//---�洢���յ�����
				UARTx->msg_uart_rxd.msg_p_data_buffer[UARTx->msg_uart_rxd.msg_read_index++] = temp_rx;
				//---����ʱ�����
				UARTx->msg_uart_rxd.msg_time_tick = UARTx->msg_uart_rxd.msg_f_time_tick();
				//---ִ����һ����
				UARTx->msg_uart_rxd.msg_step++;
				break;
			}
			case 1:
			{
				//---�洢���յ�������
				UARTx->msg_uart_rxd.msg_p_data_buffer[UARTx->msg_uart_rxd.msg_read_index++] = temp_rx;
				//---����ʱ�����
				UARTx->msg_uart_rxd.msg_time_tick = UARTx->msg_uart_rxd.msg_f_time_tick();
				//---�ж����ݵĽ����Ƿ񳬳�������
				if (UARTx->msg_uart_rxd.msg_read_index > UART_RX_SIZE_MAX_THREE)
				{
					UARTx->msg_uart_rxd.msg_read_index = 0;
				}
				break;
			}
			default:
			{
				break;
			}
		}
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
void uart_it_irq_read_error_handle_three(UART_HandleType* UARTx)
{
#ifdef TYPE_UART3
	//---���ݻ�����
	vltuint8_t temp_rx = 0;
	//---��ȡ�յ�������
	temp_rx = RXD2;
	//---��ȡ�����ʶ
	UARTx->msg_uart_rxd.msg_send_index = (SSR11 & 0x0007U);
	//---��������־λ
	SIR11 = UARTx->msg_uart_rxd.msg_send_index;
	//---���ݷ��͸�λ
	uart_read_reset(UARTx);
#endif
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
#ifdef TYPE_UART3
	if (UARTx->msg_uart_txd.msg_send_index != 0)
	{
		//---У�����ݷ���״̬
		if (UARTx->msg_uart_txd.msg_read_index != UARTx->msg_uart_txd.msg_send_index)
		{
			//--->>>����δ�������
			TXD2 = UARTx->msg_uart_txd.msg_p_data_buffer[UARTx->msg_uart_txd.msg_read_index];
			UARTx->msg_uart_txd.msg_read_index++;
		}
		else
		{
			//---��ʹ���ж�
			STMK2 = 1U;    /* disable INTST1 interrupt */
			//---���ݷ��͸�λ
			uart_send_reset(UARTx);
		}
	}
	else
	{
		//---��ʹ���ж�
		STMK2 = 1U;    /* disable INTST1 interrupt */
		//---���ݷ��͸�λ
		uart_send_reset(UARTx);
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
uint8_t uart_init(UART_HandleType* UARTx, uint32_t(*func_time_tick)(void))
{
	//---ע���������
	if (func_time_tick != NULL)
	{
		UARTx->msg_uart_txd.msg_f_time_tick = func_time_tick;
		UARTx->msg_uart_rxd.msg_f_time_tick = func_time_tick;
	}
	else
	{
		UARTx->msg_uart_txd.msg_f_time_tick = sys_tick_task_get_tick;
		UARTx->msg_uart_rxd.msg_f_time_tick = sys_tick_task_get_tick;
	}
	//---�˿ڳ�ʼ��
#ifdef TYPE_UART1
	if ((UARTx != NULL) && (UARTx == UART_TASK_ONE))
	{
		uart_init_one(UARTx);
		return OK_0;
	}
#endif
#ifdef TYPE_UART2
	if ((UARTx != NULL) && (UARTx == UART_TASK_TWO))
	{
		uart_init_two(UARTx);
		return OK_0;
	}
#endif
#ifdef TYPE_UART3
	if ((UARTx != NULL) && (UARTx == UART_TASK_THREE))
	{
		uart_init_three(UARTx);
		return OK_0;
	}
#endif
	return ERROR_1;
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

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: logģʽ��������
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_printf_log_one(UART_HandleType* UARTx, char* fmt, va_list args)
{
#if defined(TYPE_UART1)&&(MODULE_LOG_ENABLE>0)&&(MODULE_LOG_UART_INDEX==2)
	int16_t length = 0;
	//---�ȴ��ϴη������
	uart_wait_send_idle(UARTx);
	//---�������ַ����д�ӡ���ݡ����ݸ�ʽ�û��Զ���;���ز��������������ַ����ĳ���
	length = vsnprintf(
		&(UARTx->msg_uart_txd.msg_p_data_buffer[0]),
		UART_TX_SIZE_MAX_ONE, fmt, args);
	//---�����ݣ�����
	if ((length == 0) || (length < 0))
	{
		return;
	}
	if (length > UART_TX_SIZE_MAX_ONE)
	{
		length = UART_TX_SIZE_MAX_ONE;
	}
	uart_fill_mode_send_buffer_one(UARTx, UARTx->msg_uart_txd.msg_p_data_buffer, length);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: logģʽ��������
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_printf_log_two(UART_HandleType* UARTx, char* fmt, va_list args)
{
#if defined(TYPE_UART2)&&(MODULE_LOG_ENABLE>0)&&(MODULE_LOG_UART_INDEX==2)
	int16_t length = 0;
	//---�ȴ��ϴη������
	uart_wait_send_idle(UARTx);
	//---�������ַ����д�ӡ���ݡ����ݸ�ʽ�û��Զ���;���ز��������������ַ����ĳ���
	length = vsnprintf(
		&(UARTx->msg_uart_txd.msg_p_data_buffer[0]),
		UART_TX_SIZE_MAX_TWO, fmt, args);
	//---�����ݣ�����
	if ((length == 0) || (length < 0))
	{
		return;
	}
	if (length>UART_TX_SIZE_MAX_TWO)
	{
		length = UART_TX_SIZE_MAX_TWO;
	}
	uart_fill_mode_send_buffer_two(UARTx, UARTx->msg_uart_txd.msg_p_data_buffer, length);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: logģʽ��������
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_printf_log_three(UART_HandleType* UARTx, char* fmt, va_list args)
{
#if defined(TYPE_UART3)&&(MODULE_LOG_ENABLE>0)&&(MODULE_LOG_UART_INDEX==3)
	int16_t length = 0;
	//---�ȴ��ϴη������
	uart_wait_send_idle(UARTx);
	//---�������ַ����д�ӡ���ݡ����ݸ�ʽ�û��Զ���;���ز��������������ַ����ĳ���
	length = vsnprintf(
		&(UARTx->msg_uart_txd.msg_p_data_buffer[0]),
		UART_TX_SIZE_MAX_THREE, fmt, args);
	//---�����ݣ�����
	if ((length == 0) || (length < 0))
	{
		return;
	}
	if (length > UART_TX_SIZE_MAX_THREE)
	{
		length = UART_TX_SIZE_MAX_THREE;
	}
	uart_fill_mode_send_buffer_three(UARTx, UARTx->msg_uart_txd.msg_p_data_buffer, length);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: logģʽ��������
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void uart_printf_log(UART_HandleType* UARTx, char* fmt, va_list args)
{
	//---�˿ڳ�ʼ��
#ifdef TYPE_UART1
	if ((UARTx != NULL) && (UARTx == UART_TASK_ONE))
	{
		uart_printf_log_one(UARTx, fmt, args);
		return;
	}
#endif
#ifdef TYPE_UART2
	if ((UARTx != NULL) && (UARTx == UART_TASK_TWO))
	{
		uart_printf_log_two(UARTx,fmt,args);
		return;
	}
#endif
#ifdef TYPE_UART3
	if ((UARTx != NULL) && (UARTx == UART_TASK_THREE))
	{
		uart_printf_log_three(UARTx, fmt, args);
		return;
	}
#endif
}