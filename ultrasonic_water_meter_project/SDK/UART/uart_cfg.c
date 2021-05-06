#include "uart_cfg.h"

// UART0和UART1对应SAU0
// UART2对应SAU1

#ifdef TYPE_UART1

#if defined(UART_RX_SIZE_MAX_ONE)&&(UART_RX_SIZE_MAX_ONE!=0)
	//===全局变量的定义	
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
	//===全局变量的定义
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
	//===全局变量的定义
	volatile uint8_t g_uart_rx_buffer_three[UART_RX_SIZE_MAX_THREE] = { 0 };
	volatile uint8_t* p_uart_rx_buffer_three = &g_uart_rx_buffer_three[0];
#endif

#if defined(UART_TX_SIZE_MAX_THREE)&&(UART_TX_SIZE_MAX_THREE!=0)
	volatile uint8_t g_uart_tx_buffer_three[UART_TX_SIZE_MAX_THREE] = { 0 };
	volatile uint8_t* p_uart_tx_buffer_three = &g_uart_tx_buffer_three[0];
#endif

#endif

#ifdef TYPE_UART1
	//===全局变量定义
	UART_HandleType  g_uart_one = { 0 };
	pUART_HandleType p_uart_one = &g_uart_one;
#endif

#ifdef TYPE_UART2
	//===全局变量定义
	UART_HandleType  g_uart_two = { 0 };
	pUART_HandleType p_uart_two = &g_uart_two;
#endif

#ifdef TYPE_UART3
	//=== 全局变量定义
	UART_HandleType  g_uart_three = { 0 };
	pUART_HandleType p_uart_three = &g_uart_three;
#endif

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 数据发送复位
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_send_reset(UART_HandleType* UARTx)
{
	UARTx->msg_uart_txd.msg_state = UART_STATE_OK;
	//---数据发送完成
	UARTx->msg_uart_txd.msg_send_index = 0;
	UARTx->msg_uart_txd.msg_send_index = 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 数据接收复位
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_read_reset(UART_HandleType* UARTx)
{
	UARTx->msg_uart_rxd.msg_state = UART_STATE_BUSY;
	//---数据接受完成
	UARTx->msg_uart_rxd.msg_send_index = 0;
	UARTx->msg_uart_rxd.msg_send_index = 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 等待发送空闲
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_wait_send_idle(UART_HandleType* UARTx)
{
	while (1)
	{
		//---校验发送完成
		if (UARTx->msg_uart_txd.msg_state==UART_STATE_OK)
		{
			break;
		}
		//---检查超时
		if (TIME_SPAN(UARTx->msg_uart_txd.msg_f_time_tick(),
			UARTx->msg_uart_txd.msg_time_record)>UARTx->msg_uart_txd.msg_timeout_max)
		{
			break;
		}
		//---喂狗
		WDT_RESET();
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_config_init_one(UART_HandleType* UARTx)
{

}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_init_one(UART_HandleType* UARTx)
{
	uart_config_init_one(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_fill_mode_send_one(UART_HandleType* UARTx, uint8_t *buffer, uint16_t length)
{

}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_fill_mode_send_start_one(UART_HandleType* UARTx)
{

}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_config_init_two(UART_HandleType* UARTx)
{
	//---使能外设时钟
	rl78_sau1_clock(1);
	//---外设运行时钟
	SPS0 = _0002_SAU_CK00_FCLK_2 | _0040_SAU_CK01_FCLK_4;
	//---初始化串口1
	ST0 |= _0008_SAU_CH3_STOP_TRG_ON | _0004_SAU_CH2_STOP_TRG_ON;    /* disable UART1 receive and transmit */
	STMK1 = 1U;    /* disable INTST1 interrupt */
	STIF1 = 0U;    /* clear INTST1 interrupt flag */
	SRMK1 = 1U;    /* disable INTSR1 interrupt */
	SRIF1 = 0U;    /* clear INTSR1 interrupt flag */
	SREMK1 = 1U;   /* disable INTSRE1 interrupt */
	SREIF1 = 0U;   /* clear INTSRE1 interrupt flag */

	//--->>>中断优先级设置
	/* Set INTST1 low priority */
	//---发送中断优先级
	STPR11 = 1U;
	STPR01 = 1U;
	/* Set INTSR1 low priority */
	//---接受中断优先级
	SRPR11 = 1U;
	SRPR01 = 1U;
	/* Set INTSRE1 low priority */
	//---接受错误中断优先级
	SREPR11 = 1U;
	SREPR01 = 1U;
	//---<<<中断优先级设置

	//---发送模式配置
	SMR02 = _0020_SAU_SMRMN_INITIALVALUE | 
			_8000_SAU_CLOCK_SELECT_CK01 | 
			_0000_SAU_TRIGGER_SOFTWARE |
			_0002_SAU_MODE_UART | 
			_0000_SAU_TRANSFER_END;
	//---发送传输模式配置
	SCR02 = _8000_SAU_TRANSMISSION | 
			_0000_SAU_INTSRE_MASK | 
			_0200_SAU_PARITY_EVEN | 
			_0080_SAU_LSB | 
			_0010_SAU_STOP_1 |
			_0007_SAU_LENGTH_8;	
	//---发送波特率计算
	SDR02 = _CE00_UART1_TRANSMIT_DIVISOR;

	//---接受引脚噪声滤波器
	NFEN0 |= _04_SAU_RXD1_FILTER_ON;
	//---接受清楚标志位
	SIR03 = _0004_SAU_SIRMN_FECTMN | 
			_0002_SAU_SIRMN_PECTMN | 
			_0001_SAU_SIRMN_OVCTMN;    /* clear error flag */
	//---接受模式配置
	SMR03 = _0020_SAU_SMRMN_INITIALVALUE | 
			_8000_SAU_CLOCK_SELECT_CK01 | 
			_0100_SAU_TRIGGER_RXD | 
			_0000_SAU_EDGE_FALL |
			_0002_SAU_MODE_UART | 
			_0000_SAU_TRANSFER_END;
	//---发送传输模式配置
	SCR03 = _4000_SAU_RECEPTION | 
			_0400_SAU_INTSRE_ENABLE | 
			_0200_SAU_PARITY_EVEN | 
			_0080_SAU_LSB | 
			_0010_SAU_STOP_1 |
			 _0007_SAU_LENGTH_8;
	//---发送波特率计算
	SDR03 = _CE00_UART1_RECEIVE_DIVISOR;

	//---发送和接受串行时钟输出为0，串行数据输出为1
	SO0 |= _0004_SAU_CH2_DATA_OUTPUT_1;

	//---发送和接受串行数据直接输出，不是取反输出
	SOL0 |= _0000_SAU_CHANNEL2_NORMAL;       /* output level normal */
	//---允许串行通信的输出
	SOE0 |= _0004_SAU_CH2_OUTPUT_ENABLE;    /* enable UART1 output */
	
	//---端口复用模式
	PIOR = 0x04;
	//gpio_task_pin_mode_ior_set(GPIOP1,GPIO_PIN_BIT_2);
//	/* Set RxD1 pin */
//	//PMC4 &= 0xF7U;
//	//PM4 |= 0x08U;
	//---数字端口输入输出
	gpio_task_pin_mode_digital(GPIOP4, GPIO_PIN_BIT_3);
	//---输出模式
	gpio_task_pin_mode_input(GPIOP4, GPIO_PIN_BIT_3);
	////---上拉使能
	//gpio_task_pin_mode_pull_up_set(GPIOP4, GPIO_PIN_BIT_3);
	//--->>>设置TX端口
	//---数字端口输入输出
	gpio_task_pin_mode_digital(GPIOP4, GPIO_PIN_BIT_2);
	//---输出高电平
	gpio_task_pin_set(GPIOP4, GPIO_PIN_BIT_2);
	//---输出模式
	gpio_task_pin_mode_output(GPIOP4, GPIO_PIN_BIT_2);
	//---上拉使能
	gpio_task_pin_mode_pull_up_set(GPIOP4, GPIO_PIN_BIT_2);
	///* Set TxD1 pin */
	//PMC4 &= 0xFBU;
	//P4 |= 0x04U;
	//PM4 &= 0xFBU;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 启动串口
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_start_two(UART_HandleType* UARTx)
{
	SO0 |= _0004_SAU_CH2_DATA_OUTPUT_1;    /* output level normal */
	SOE0 |= _0004_SAU_CH2_OUTPUT_ENABLE;    /* enable UART1 output */
	//---使能收发
	SS0 |=	_0008_SAU_CH3_START_TRG_ON | 
			_0004_SAU_CH2_START_TRG_ON;    /* enable UART1 receive and transmit */
	
	//---清楚中断标识
	STIF1 = 0U;    /* clear INTST1 interrupt flag */
	SRIF1 = 0U;    /* clear INTSR1 interrupt flag */
	SREIF1 = 0U;   /* clear INTSRE1 interrupt flag */
	//---使能中断
	STMK1 = 0U;    /* enable INTST1 interrupt */
	SRMK1 = 0U;    /* enable INTSR1 interrupt */
	SREMK1 = 0U;   /* enable INTSRE1 interrupt */
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 停止串口
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_stop_two(UART_HandleType* UARTx)
{
	//---不使能中断
	STMK1 = 1U;    /* disable INTST1 interrupt */
	SRMK1 = 1U;    /* disable INTSR1 interrupt */
	SREMK1 = 1U;   /* disable INTSRE1 interrupt */
	//---不是能收发
	ST0 |=  _0008_SAU_CH3_STOP_TRG_ON | 
			_0004_SAU_CH2_STOP_TRG_ON;    /* disable UART1 receive and transmit */
	//---不使能串口输出
	SOE0 &= ~_0004_SAU_CH2_OUTPUT_ENABLE;    /* disable UART1 output */
	//---清楚中断标识
	STIF1 = 0U;    /* clear INTST1 interrupt flag */
	SRIF1 = 0U;    /* clear INTSR1 interrupt flag */
	SREIF1 = 0U;   /* clear INTSRE1 interrupt flag */
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_fill_mode_send_two(UART_HandleType* UARTx,uint8_t *buffer,uint16_t length)
{
	//---等待上次发送完成
	//uart_wait_send_idle(UARTx);
	//---将数据填充到发送缓存区
	UARTx->msg_uart_txd.msg_data_length = length;
	UARTx->msg_uart_txd.msg_send_index = length;
	UARTx->msg_uart_txd.msg_read_index =0;
	//---执行数据拷贝
	memcpy(UARTx->msg_uart_txd.msg_p_data_buffer, buffer, length);
	//---设置发送超时时间
	UARTx->msg_uart_txd.msg_timeout_max = 
		(UARTx->msg_uart_txd.msg_data_length + UART_TX_MAX_TIME_TWO)*UART_BYTE_TIME_ONE / UART_MIN_PULSE_WIDTH;
	//---获取时间节点
	//UARTx->msg_uart_txd.msg_time_record=UARTx->msg_uart_txd.msg_f_time_tick();
	//---设置发送状态为发送模式
	UARTx->msg_uart_txd.msg_state= UART_STATE_BUSY;
	//---不使能中断
	STMK1 = 1U;    /* disable INTST1 interrupt */
	//---清楚中断标识
	//STIF1 = 0U;    /* clear INTST1 interrupt flag */
	//---发送数据
	TXD1 = UARTx->msg_uart_txd.msg_p_data_buffer[UARTx->msg_uart_txd.msg_read_index];
	UARTx->msg_uart_txd.msg_read_index++;
	//---使能中断
	STMK1 = 0U;    /* enable INTST1 interrupt */
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 直接启动发送，数据已经准备好
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_fill_mode_send_start_two(UART_HandleType* UARTx)
{
	//---等待上次发送完成
	//---将数据填充到发送缓存区
	UARTx->msg_uart_txd.msg_data_length = UARTx->msg_uart_txd.msg_send_index;
	UARTx->msg_uart_txd.msg_read_index = 0;
	//---设置发送超时时间
	UARTx->msg_uart_txd.msg_timeout_max =
		(UARTx->msg_uart_txd.msg_data_length + UART_TX_MAX_TIME_TWO)*UART_BYTE_TIME_ONE / UART_MIN_PULSE_WIDTH;
	//---获取时间节点
	UARTx->msg_uart_txd.msg_time_record = UARTx->msg_uart_txd.msg_f_time_tick();
	//---不使能中断
	STMK1 = 1U;    /* disable INTST1 interrupt */
	//---清楚中断标识
	STIF1 = 0U;    /* clear INTST1 interrupt flag */
	//---发送数据
	TXD1 = UARTx->msg_uart_txd.msg_p_data_buffer[UARTx->msg_uart_txd.msg_read_index];
	UARTx->msg_uart_txd.msg_read_index++;
	//---设置发送状态为发送模式
	UARTx->msg_uart_txd.msg_state = UART_STATE_BUSY;
	//---使能中断
	STMK1 = 0U;    /* enable INTST1 interrupt */
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_init_two(UART_HandleType* UARTx)
{
	
#ifdef TYPE_UART2
	uart_config_init_two(UARTx);
#if defined(UART_RX_SIZE_MAX_TWO)&&(UART_RX_SIZE_MAX_TWO!=0)
	//---缓存区地址初始化
	UARTx->msg_uart_txd.msg_p_data_buffer = p_uart_tx_buffer_two;
	UARTx->msg_uart_rxd.msg_p_data_buffer = p_uart_rx_buffer_two;
#endif
#if defined(UART_TX_SIZE_MAX_TWO)&&(UART_TX_SIZE_MAX_TWO!=0)
	//---缓存区地址初始化
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
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_config_init_three(UART_HandleType* UARTx)
{

}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_init_three(UART_HandleType* UARTx)
{
	uart_config_init_three(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_fill_mode_send_three(UART_HandleType* UARTx, uint8_t *buffer, uint16_t length)
{

}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_fill_mode_send_start_three(UART_HandleType* UARTx)
{

}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 接受处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_it_irq_read_handle_one(UART_HandleType* UARTx)
{

}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 接受错误处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_it_irq_read_error_handle_one(UART_HandleType* UARTx)
{

}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 发送处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_it_irq_send_handle_one(UART_HandleType* UARTx)
{

}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 接受处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_it_irq_read_handle_two(UART_HandleType* UARTx)
{

}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 接受错误处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_it_irq_read_error_handle_two(UART_HandleType* UARTx)
{

}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 发送处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_it_irq_send_handle_two(UART_HandleType* UARTx)
{
	if (UARTx->msg_uart_txd.msg_send_index!=0)
	{
		//---校验数据发送状态
		if (UARTx->msg_uart_txd.msg_read_index != UARTx->msg_uart_txd.msg_send_index)
		{
			//--->>>数据未发送完成
			TXD1 = UARTx->msg_uart_txd.msg_p_data_buffer[UARTx->msg_uart_txd.msg_read_index];
			UARTx->msg_uart_txd.msg_read_index++;
		}
		else
		{
			//---不使能中断
			STMK1 = 1U;    /* disable INTST1 interrupt */
			//---数据发送复位
			uart_send_reset(UARTx);
		}
	}
	else
	{
		//---不使能中断
		STMK1 = 1U;    /* disable INTST1 interrupt */
		//---数据发送复位
		uart_send_reset(UARTx);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 接受处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_it_irq_read_handle_three(UART_HandleType* UARTx)
{

}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 接受错误处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_it_irq_read_error_handle_three(UART_HandleType* UARTx)
{

}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 发送处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_it_irq_send_handle_three(UART_HandleType* UARTx)
{

}


///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 接受处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_it_irq_read_handle(UART_HandleType* UARTx)
{
	//---端口初始化
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
//////函		数:
//////功		能: 接受错误处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_it_irq_read_error_handle(UART_HandleType* UARTx)
{
	//---端口初始化
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
//////函		数:
//////功		能: 发送处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_it_irq_send_handle(UART_HandleType* UARTx)
{
	//---端口初始化
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
//////函		数:
//////功		能: 填充模式发送处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_fill_mode_send(UART_HandleType* UARTx, uint8_t *buffer, uint16_t length)
{
	//---端口初始化
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
//////函		数:
//////功		能: 填充模式发送处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_fill_mode_send_start(UART_HandleType* UARTx)
{
	//---端口初始化
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