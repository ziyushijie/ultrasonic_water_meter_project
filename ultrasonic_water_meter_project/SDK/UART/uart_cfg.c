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
	UARTx->msg_uart_txd.msg_read_index = 0;
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
	UARTx->msg_uart_rxd.msg_read_index = 0;
	UARTx->msg_uart_rxd.msg_send_index = 0;
	//---清零数据接收的序号
	UARTx->msg_uart_rxd.msg_step = 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 数据接收复位
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t uart_read_end(UART_HandleType* UARTx)
{
	if (UARTx->msg_uart_rxd.msg_step!=0)
	{
		//---判断是否有数据接收的超时动作
		if (TIME_SPAN(UARTx->msg_uart_rxd.msg_f_time_tick(), UARTx->msg_uart_rxd.msg_time_tick)>
			UARTx->msg_uart_rxd.msg_timeout_max)
		{
			//---接收数据的长度
			UARTx->msg_uart_rxd.msg_data_length = UARTx->msg_uart_rxd.msg_read_index;
			//---清零数据接收的序号
			UARTx->msg_uart_rxd.msg_step = 0;
			//---数据接收完成
			UARTx->msg_uart_rxd.msg_state = UART_STATE_OK;
			//---数据接收完成
			return OK_0;
		}
	}
	return ERROR_1;
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
		if (TIME_SPAN(UARTx->msg_uart_txd.msg_f_time_tick(),UARTx->msg_uart_txd.msg_time_record)>
			UARTx->msg_uart_txd.msg_timeout_max)
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
uint8_t uart_init_one(UART_HandleType* UARTx)
{
	uart_config_init_one(UARTx);
	return OK_0;
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
void uart_fill_mode_send_buffer_one(UART_HandleType* UARTx, uint8_t *buffer, uint16_t length)
{

}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t uart_config_init_two(UART_HandleType* UARTx)
{
#ifdef TYPE_UART2
	//---使能外设时钟
	//rl78_sau1_clock(1);
	rl78_perpheral_clock_enable(PERIPHERAL_UART2);
	//---外设运行时钟
	/*SPS0 =	_0002_SAU_CK00_FCLK_2 | 
			_0040_SAU_CK01_FCLK_4;*/
	SPS0 = _0001_SAU_CK00_FCLK_1 |
		_0040_SAU_CK01_FCLK_4;
	//---初始化串口1
	ST0 |=	_0008_SAU_CH3_STOP_TRG_ON | 
			_0004_SAU_CH2_STOP_TRG_ON;   

	STMK1 = 1U;    
	STIF1 = 0U;    
	SRMK1 = 1U;    
	SRIF1 = 0U;    
	SREMK1 = 1U;   
	SREIF1 = 0U;   

	//--->>>中断优先级设置
	//---发送中断优先级
	STPR11 = 1U;
	STPR01 = 1U;
	//---接受中断优先级
	SRPR11 = 1U;
	SRPR01 = 1U;
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
			_0001_SAU_SIRMN_OVCTMN;   
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
	SOL0 |= _0000_SAU_CHANNEL2_NORMAL;       
	//---允许串行通信的输出
	SOE0 |= _0004_SAU_CH2_OUTPUT_ENABLE;   
	
	//---端口复用模式
	//PIOR = 0x04;
	gpio_task_pin_mode_ior_set(GPIOP0, GPIO_PIN_BIT_2);
	/* Set RxD1 pin */
	//PMC4 &= 0xF7U;
	//PM4 |= 0x08U;
	//---数字端口输入输出
	gpio_task_pin_mode_digital(GPIOP4, GPIO_PIN_BIT_3);
	//---输出模式
	gpio_task_pin_mode_input(GPIOP4, GPIO_PIN_BIT_3);
	////---上拉使能
	//gpio_task_pin_mode_pull_up_set(GPIOP4, GPIO_PIN_BIT_3);
	//--->>>设置TX端口
	/* Set TxD1 pin */
	//PMC4 &= 0xFBU;
	//P4 |= 0x04U;
	//PM4 &= 0xFBU;
	//---数字端口输入输出
	gpio_task_pin_mode_digital(GPIOP4, GPIO_PIN_BIT_2);
	//---输出高电平
	gpio_task_pin_set(GPIOP4, GPIO_PIN_BIT_2);
	//---输出模式
	gpio_task_pin_mode_output(GPIOP4, GPIO_PIN_BIT_2);
	//---上拉使能
	gpio_task_pin_mode_pull_up_set(GPIOP4, GPIO_PIN_BIT_2);
#endif
	return OK_0;
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
#ifdef TYPE_UART2
	SO0 |= _0004_SAU_CH2_DATA_OUTPUT_1;
	SOE0 |= _0004_SAU_CH2_OUTPUT_ENABLE;
	//---使能收发
	SS0 |=	_0008_SAU_CH3_START_TRG_ON | 
			_0004_SAU_CH2_START_TRG_ON;   
	
	//---清楚中断标识
	STIF1 = 0U; 
	SRIF1 = 0U; 
	SREIF1 = 0U;
	//---使能中断
	STMK1 = 0U;  
	SRMK1 = 0U;  
	SREMK1 = 0U; 
#endif
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
#ifdef TYPE_UART2
	//---不使能中断
	STMK1 = 1U; 
	SRMK1 = 1U; 
	SREMK1 = 1U;
	//---不是能收发
	ST0 |=  _0008_SAU_CH3_STOP_TRG_ON | 
			_0004_SAU_CH2_STOP_TRG_ON;  
	//---不使能串口输出
	SOE0 &= ~_0004_SAU_CH2_OUTPUT_ENABLE;   
	//---清楚中断标识
	STIF1 = 0U;  
	SRIF1 = 0U;  
	SREIF1 = 0U; 
#endif
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
	uart_wait_send_idle(UARTx);
#ifdef TYPE_UART2
	if (length > UART_TX_SIZE_MAX_TWO)
	{
		length = UART_RX_SIZE_MAX_TWO;
	}
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
	UARTx->msg_uart_txd.msg_time_record=UARTx->msg_uart_txd.msg_f_time_tick();
	//---设置发送状态为发送模式
	UARTx->msg_uart_txd.msg_state= UART_STATE_BUSY;
	//---不使能中断
	STMK1 = 1U;  
	//---清楚中断标识
	STIF1 = 0U; 
	//---发送数据
	TXD1 = UARTx->msg_uart_txd.msg_p_data_buffer[UARTx->msg_uart_txd.msg_read_index];
	UARTx->msg_uart_txd.msg_read_index++;
	//---使能中断
	STMK1 = 0U;
#endif
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
	uart_wait_send_idle(UARTx);
#ifdef TYPE_UART2
	if (UARTx->msg_uart_txd.msg_send_index > UART_TX_SIZE_MAX_TWO)
	{
		UARTx->msg_uart_txd.msg_send_index = UART_RX_SIZE_MAX_TWO;
	}
	//---将数据填充到发送缓存区
	UARTx->msg_uart_txd.msg_data_length = UARTx->msg_uart_txd.msg_send_index;
	UARTx->msg_uart_txd.msg_read_index = 0;
	//---设置发送超时时间
	UARTx->msg_uart_txd.msg_timeout_max =
		(UARTx->msg_uart_txd.msg_data_length + UART_TX_MAX_TIME_TWO)*UART_BYTE_TIME_ONE / UART_MIN_PULSE_WIDTH;
	//---获取时间节点
	UARTx->msg_uart_txd.msg_time_record = UARTx->msg_uart_txd.msg_f_time_tick();
	//---不使能中断
	STMK1 = 1U;   
	//---清楚中断标识
	STIF1 = 0U;
	//---发送数据
	TXD1 = UARTx->msg_uart_txd.msg_p_data_buffer[UARTx->msg_uart_txd.msg_read_index];
	UARTx->msg_uart_txd.msg_read_index++;
	//---设置发送状态为发送模式
	UARTx->msg_uart_txd.msg_state = UART_STATE_BUSY;
	//---使能中断
	STMK1 = 0U;
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_fill_mode_send_buffer_two(UART_HandleType* UARTx, uint8_t *buffer, uint16_t length)
{
#ifdef TYPE_UART2
	if (length>UART_TX_SIZE_MAX_TWO)
	{
		length = UART_RX_SIZE_MAX_TWO;
	}
	//---将数据填充到发送缓存区
	UARTx->msg_uart_txd.msg_data_length = length;
	UARTx->msg_uart_txd.msg_send_index = length;
	UARTx->msg_uart_txd.msg_read_index = 0;
	//---设置发送超时时间
	UARTx->msg_uart_txd.msg_timeout_max =
		(UARTx->msg_uart_txd.msg_data_length + UART_TX_MAX_TIME_TWO)*UART_BYTE_TIME_ONE / UART_MIN_PULSE_WIDTH;
	//---获取时间节点
	UARTx->msg_uart_txd.msg_time_record=UARTx->msg_uart_txd.msg_f_time_tick();
	//---设置发送状态为发送模式
	UARTx->msg_uart_txd.msg_state = UART_STATE_BUSY;
	//---不使能中断
	STMK1 = 1U; 
	//---清楚中断标识
	STIF1 = 0U;
	//---发送数据
	TXD1 = UARTx->msg_uart_txd.msg_p_data_buffer[UARTx->msg_uart_txd.msg_read_index];
	UARTx->msg_uart_txd.msg_read_index++;
	//---使能中断
	STMK1 = 0U; 
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t uart_init_two(UART_HandleType* UARTx)
{	
#ifdef TYPE_UART2
	uart_config_init_two(UARTx);
#if defined(UART_RX_SIZE_MAX_TWO)&&(UART_RX_SIZE_MAX_TWO!=0)
	//---缓存区地址初始化
	UARTx->msg_uart_rxd.msg_p_data_buffer = p_uart_rx_buffer_two;
#endif
#if defined(UART_TX_SIZE_MAX_TWO)&&(UART_TX_SIZE_MAX_TWO!=0)
	//---缓存区地址初始化
	UARTx->msg_uart_txd.msg_p_data_buffer = p_uart_tx_buffer_two;
#endif

	UARTx->msg_uart_rxd.msg_step=0;
	UARTx->msg_uart_rxd.msg_state=UART_STATE_BUSY;
	UARTx->msg_uart_rxd.msg_send_index = 0;
	UARTx->msg_uart_rxd.msg_read_index = 0;
	UARTx->msg_uart_rxd.msg_data_length = 0;
	//---定义接收做大超时时间
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
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t uart_config_init_three(UART_HandleType* UARTx)
{
#ifdef TYPE_UART3
	//---使能外设时钟
	//rl78_sau1_clock(1);
	rl78_perpheral_clock_enable(PERIPHERAL_UART3);
	//---外设运行时钟
	SPS1 = _0001_SAU_CK00_FCLK_1 |
		_0040_SAU_CK01_FCLK_4;
	//---初始化串口1
	ST1 |=	_0002_SAU_CH1_STOP_TRG_ON | 
			_0001_SAU_CH0_STOP_TRG_ON;

	STMK2 = 1U;
	STIF2 = 0U;
	SRMK2 = 1U;
	SRIF2 = 0U;
	SREMK2 = 1U;
	SREIF2 = 0U;

	//--->>>中断优先级设置
	//---发送中断优先级
	STPR12 = 1U;
	STPR02 = 1U;
	//---接受中断优先级
	SRPR12 = 1U;
	SRPR02 = 1U;
	//---接受错误中断优先级
	SREPR12 = 1U;
	SREPR02 = 1U;
	//---<<<中断优先级设置

	//---发送模式配置
	SMR10 = _0020_SAU_SMRMN_INITIALVALUE | 
			_0000_SAU_CLOCK_SELECT_CK00 | 
			_0000_SAU_TRIGGER_SOFTWARE |
			_0002_SAU_MODE_UART | 
			_0000_SAU_TRANSFER_END;
	//---发送传输模式配置
	SCR10 =	_8000_SAU_TRANSMISSION | 
			_0000_SAU_INTSRE_MASK | 
			_0200_SAU_PARITY_EVEN | 
			_0080_SAU_LSB |
			_0010_SAU_STOP_1 | 
			_0007_SAU_LENGTH_8;
	//---发送波特率计算
	SDR10 = _CE00_UART2_TRANSMIT_DIVISOR;
	//---接受引脚噪声滤波器
	NFEN0 |= _10_SAU_RXD2_FILTER_ON;
	//---接受清楚标志位
	SIR11 = _0004_SAU_SIRMN_FECTMN | 
			_0002_SAU_SIRMN_PECTMN | 
			_0001_SAU_SIRMN_OVCTMN;
	//---接受模式配置
	SMR11 = _0020_SAU_SMRMN_INITIALVALUE | 
			_0000_SAU_CLOCK_SELECT_CK00 | 
			_0100_SAU_TRIGGER_RXD | 
			_0000_SAU_EDGE_FALL |
			_0002_SAU_MODE_UART | 
			_0000_SAU_TRANSFER_END;
	//---发送传输模式配置
	SCR11 = _4000_SAU_RECEPTION | 
			_0400_SAU_INTSRE_ENABLE | 
			_0200_SAU_PARITY_EVEN | 
			_0080_SAU_LSB | 
			_0010_SAU_STOP_1 |
			_0007_SAU_LENGTH_8;
	//---发送波特率计算
	SDR11 = _CE00_UART2_RECEIVE_DIVISOR;
	//---发送和接受串行时钟输出为0，串行数据输出为1
	SO1 |= _0001_SAU_CH0_DATA_OUTPUT_1;

	//---发送和接受串行数据直接输出，不是取反输出
	SOL1 |= _0000_SAU_CHANNEL0_NORMAL;
	//---允许串行通信的输出
	SOE1 |= _0001_SAU_CH0_OUTPUT_ENABLE;

	//---端口复用模式
	//PIOR = 0x04;
	//gpio_task_pin_mode_ior_set(GPIOP0, GPIO_PIN_BIT_2);
	/* Set RxD1 pin */
	//PFSEG5 &= 0x7FU;
	//PM0 |= 0x08U;
	//---数字端口输入输出
	gpio_task_pin_mode_digital(GPIOP0, GPIO_PIN_BIT_3);
	//---输入模式
	gpio_task_pin_mode_input(GPIOP0, GPIO_PIN_BIT_3);
	////---上拉使能
	//gpio_task_pin_mode_pull_up_set(GPIOP4, GPIO_PIN_BIT_3);
	//--->>>设置TX端口
	/* Set TxD2 pin */
	//PFSEG6 &= 0xFEU;
	//P0 |= 0x10U;
	//PM0 &= 0xEFU;
	//---数字端口输入输出
	gpio_task_pin_mode_digital(GPIOP0, GPIO_PIN_BIT_4);
	//---输出高电平
	gpio_task_pin_set(GPIOP0, GPIO_PIN_BIT_4);
	//---输出模式
	gpio_task_pin_mode_output(GPIOP0, GPIO_PIN_BIT_4);
	//---上拉使能
	gpio_task_pin_mode_pull_up_set(GPIOP0, GPIO_PIN_BIT_4);
#endif
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 启动串口
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_start_three(UART_HandleType* UARTx)
{
#ifdef TYPE_UART3
	SO1 |= _0001_SAU_CH0_DATA_OUTPUT_1;
	SOE1 |= _0001_SAU_CH0_OUTPUT_ENABLE;
	//---使能收发
	SS1 |=	_0002_SAU_CH1_START_TRG_ON |
			_0001_SAU_CH0_START_TRG_ON;

	//---清楚中断标识
	STIF2 = 0U;
	SRIF2 = 0U;   
	SREIF2 = 0U;   
	//---使能中断
	STMK2 = 0U;
	SRMK2 = 0U;
	SREMK2 = 0U;
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 停止串口
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_stop_three(UART_HandleType* UARTx)
{
#ifdef TYPE_UART3
	//---不使能中断
	STMK2 = 1U;   
	SRMK2 = 1U; 
	SREMK2 = 1U; 
	//---不使能收发
	ST1 |=	_0002_SAU_CH1_STOP_TRG_ON |
			_0001_SAU_CH0_STOP_TRG_ON;
	//---不使能串口输出
	SOE1 &= ~_0001_SAU_CH0_OUTPUT_ENABLE;
	//---清楚中断标识
	STIF2 = 0U;   
	SRIF2 = 0U; 
	SREIF2 = 0U; 
#endif
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
	//---等待上次发送完成
	uart_wait_send_idle(UARTx);
#ifdef TYPE_UART3
	if (length > UART_TX_SIZE_MAX_THREE)
	{
		length = UART_RX_SIZE_MAX_THREE;
	}
	//---将数据填充到发送缓存区
	UARTx->msg_uart_txd.msg_data_length = length;
	UARTx->msg_uart_txd.msg_send_index = length;
	UARTx->msg_uart_txd.msg_read_index = 0;
	//---执行数据拷贝
	memcpy(UARTx->msg_uart_txd.msg_p_data_buffer, buffer, length);
	//---设置发送超时时间
	UARTx->msg_uart_txd.msg_timeout_max =
		(UARTx->msg_uart_txd.msg_data_length + UART_TX_MAX_TIME_THREE)*UART_BYTE_TIME_ONE / UART_MIN_PULSE_WIDTH;
	//---获取时间节点
	UARTx->msg_uart_txd.msg_time_record = UARTx->msg_uart_txd.msg_f_time_tick();
	//---设置发送状态为发送模式
	UARTx->msg_uart_txd.msg_state = UART_STATE_BUSY;
	//---不使能中断
	STMK2 = 1U;
	//---清楚中断标识
	STIF2 = 0U;
	//---发送数据
	TXD2 = UARTx->msg_uart_txd.msg_p_data_buffer[UARTx->msg_uart_txd.msg_read_index];
	UARTx->msg_uart_txd.msg_read_index++;
	//---使能中断
	STMK2 = 0U;
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 直接启动发送，数据已经准备好
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_fill_mode_send_start_three(UART_HandleType* UARTx)
{
	//---等待上次发送完成
	uart_wait_send_idle(UARTx);
#ifdef TYPE_UART3
	if (UARTx->msg_uart_txd.msg_send_index > UART_TX_SIZE_MAX_THREE)
	{
		UARTx->msg_uart_txd.msg_send_index = UART_RX_SIZE_MAX_THREE;
	}
	//---将数据填充到发送缓存区
	UARTx->msg_uart_txd.msg_data_length = UARTx->msg_uart_txd.msg_send_index;
	UARTx->msg_uart_txd.msg_read_index = 0;
	//---设置发送超时时间
	UARTx->msg_uart_txd.msg_timeout_max =
		(UARTx->msg_uart_txd.msg_data_length + UART_TX_MAX_TIME_THREE)*UART_BYTE_TIME_ONE / UART_MIN_PULSE_WIDTH;
	//---获取时间节点
	UARTx->msg_uart_txd.msg_time_record = UARTx->msg_uart_txd.msg_f_time_tick();
	//---不使能中断
	STMK2 = 1U;
	//---清楚中断标识
	STIF2 = 0U;
	//---发送数据
	TXD2 = UARTx->msg_uart_txd.msg_p_data_buffer[UARTx->msg_uart_txd.msg_read_index];
	UARTx->msg_uart_txd.msg_read_index++;
	//---设置发送状态为发送模式
	UARTx->msg_uart_txd.msg_state = UART_STATE_BUSY;
	//---使能中断
	STMK2 = 0U;
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_fill_mode_send_buffer_three(UART_HandleType* UARTx, uint8_t *buffer, uint16_t length)
{
#ifdef TYPE_UART3
	if (length > UART_TX_SIZE_MAX_THREE)
	{
		length = UART_RX_SIZE_MAX_THREE;
	}
	//---将数据填充到发送缓存区
	UARTx->msg_uart_txd.msg_data_length = length;
	UARTx->msg_uart_txd.msg_send_index = length;
	UARTx->msg_uart_txd.msg_read_index = 0;
	//---设置发送超时时间
	UARTx->msg_uart_txd.msg_timeout_max =
		(UARTx->msg_uart_txd.msg_data_length + UART_TX_MAX_TIME_THREE)*UART_BYTE_TIME_ONE / UART_MIN_PULSE_WIDTH;
	//---获取时间节点
	UARTx->msg_uart_txd.msg_time_record = UARTx->msg_uart_txd.msg_f_time_tick();
	//---设置发送状态为发送模式
	UARTx->msg_uart_txd.msg_state = UART_STATE_BUSY;
	//---不使能中断
	STMK2 = 1U;
	//---清楚中断标识
	STIF2 = 0U;
	//---发送数据
	TXD2 = UARTx->msg_uart_txd.msg_p_data_buffer[UARTx->msg_uart_txd.msg_read_index];
	UARTx->msg_uart_txd.msg_read_index++;
	//---使能中断
	STMK2 = 0U;
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t uart_init_three(UART_HandleType* UARTx)
{
#ifdef TYPE_UART3
	uart_config_init_three(UARTx);
#if defined(UART_RX_SIZE_MAX_THREE)&&(UART_RX_SIZE_MAX_THREE!=0)
	//---缓存区地址初始化
	UARTx->msg_uart_rxd.msg_p_data_buffer = p_uart_rx_buffer_three;
#endif
#if defined(UART_TX_SIZE_MAX_THREE)&&(UART_TX_SIZE_MAX_THREE!=0)
	//---缓存区地址初始化
	UARTx->msg_uart_txd.msg_p_data_buffer = p_uart_tx_buffer_three;
#endif

	UARTx->msg_uart_rxd.msg_step = 0;
	UARTx->msg_uart_rxd.msg_state = UART_STATE_BUSY;
	UARTx->msg_uart_rxd.msg_send_index = 0;
	UARTx->msg_uart_rxd.msg_read_index = 0;
	UARTx->msg_uart_rxd.msg_data_length = 0;
	//---定义接收做大超时时间
	UARTx->msg_uart_rxd.msg_timeout_max = UART_BYTE_TIME_ONE * 2;

	UARTx->msg_uart_txd.msg_step = 0;
	UARTx->msg_uart_txd.msg_state = UART_STATE_OK;
	UARTx->msg_uart_txd.msg_send_index = 0;
	UARTx->msg_uart_txd.msg_read_index = 0;
	UARTx->msg_uart_txd.msg_data_length = 0;
	//---启动串口
	uart_start_three(UARTx);
#endif
	return OK_0;
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
#ifdef TYPE_UART1
	//---数据缓存区
	vltuint8_t temp_rx = 0;
	//---判断数据接收是否符合
	if (UARTx->msg_uart_rxd.msg_state == UART_STATE_BUSY)
	{
		//---缓存接收到的数据
		temp_rx = RXD0;
		//---依次接收数据
		switch (UARTx->msg_uart_rxd.msg_step)
		{
			case 0:
			{
				if (UARTx->msg_uart_rxd.msg_read_index != 0)
				{
					UARTx->msg_uart_rxd.msg_read_index = 0;
				}
				//---存储接收的数据
				UARTx->msg_uart_rxd.msg_p_data_buffer[UARTx->msg_uart_rxd.msg_read_index++] = temp_rx;
				//---更新时间节拍
				UARTx->msg_uart_rxd.msg_time_tick = UARTx->msg_uart_rxd.msg_f_time_tick();
				//---记录接收的第一个数据
				UARTx->msg_uart_rxd.msg_time_record = UARTx->msg_uart_rxd.msg_f_time_tick();
				//---执行下一步骤
				UARTx->msg_uart_rxd.msg_step++;
				break;
			}
			case 1:
			{
				//---存储接收到的数据
				UARTx->msg_uart_rxd.msg_p_data_buffer[UARTx->msg_uart_rxd.msg_read_index++] = temp_rx;
				//---更新时间节拍
				UARTx->msg_uart_rxd.msg_time_tick = UARTx->msg_uart_rxd.msg_f_time_tick();
				//---判断数据的接收是否超出缓存区
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
//////函		数:
//////功		能: 接受错误处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_it_irq_read_error_handle_one(UART_HandleType* UARTx)
{
#ifdef TYPE_UART1
	//---数据缓存区
	vltuint8_t temp_rx = 0;
	//---获取收到的数据
	temp_rx = RXD0;
	//---获取错误标识
	UARTx->msg_uart_rxd.msg_send_index = (SSR01 & 0x0007U);
	//---清楚错误标志位
	SSR01 = UARTx->msg_uart_rxd.msg_send_index;
	//---数据发送复位
	uart_read_reset(UARTx);
#endif
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
#ifdef TYPE_UART1
	if (UARTx->msg_uart_txd.msg_send_index != 0)
	{
		//---校验数据发送状态
		if (UARTx->msg_uart_txd.msg_read_index != UARTx->msg_uart_txd.msg_send_index)
		{
			//--->>>数据未发送完成
			TXD0 = UARTx->msg_uart_txd.msg_p_data_buffer[UARTx->msg_uart_txd.msg_read_index];
			UARTx->msg_uart_txd.msg_read_index++;
		}
		else
		{
			//---不使能中断
			STMK0 = 1U;    /* disable INTST1 interrupt */
			//---数据发送复位
			uart_send_reset(UARTx);
		}
	}
	else
	{
		//---不使能中断
		STMK0 = 1U;    /* disable INTST1 interrupt */
		//---数据发送复位
		uart_send_reset(UARTx);
	}
#endif
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
#ifdef TYPE_UART2
	//---数据缓存区
	vltuint8_t temp_rx = 0;
	//---判断数据接收是否符合
	if (UARTx->msg_uart_rxd.msg_state== UART_STATE_BUSY)
	{
		//---缓存接收到的数据
		temp_rx = RXD1;
		//---依次接收数据
		switch (UARTx->msg_uart_rxd.msg_step)
		{
			case 0:
			{
				if (UARTx->msg_uart_rxd.msg_read_index!=0)
				{
					UARTx->msg_uart_rxd.msg_read_index = 0;
				}
				//---存储接收的数据
				UARTx->msg_uart_rxd.msg_p_data_buffer[UARTx->msg_uart_rxd.msg_read_index++] = temp_rx;
				//---更新时间节拍
				UARTx->msg_uart_rxd.msg_time_tick = UARTx->msg_uart_rxd.msg_f_time_tick();
				//---记录接收的第一个数据
				UARTx->msg_uart_rxd.msg_time_record = UARTx->msg_uart_rxd.msg_f_time_tick();
				//---执行下一步骤
				UARTx->msg_uart_rxd.msg_step++;
				break;
			}
			case 1:
			{
				//---存储接收到的数据
				UARTx->msg_uart_rxd.msg_p_data_buffer[UARTx->msg_uart_rxd.msg_read_index++] = temp_rx;
				//---更新时间节拍
				UARTx->msg_uart_rxd.msg_time_tick = UARTx->msg_uart_rxd.msg_f_time_tick();
				//---判断数据的接收是否超出缓存区
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
//////函		数:
//////功		能: 接受错误处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_it_irq_read_error_handle_two(UART_HandleType* UARTx)
{
#ifdef TYPE_UART2
	//---数据缓存区
	vltuint8_t temp_rx = 0;
	//---获取收到的数据
	temp_rx = RXD1;
	//---获取错误标识
	UARTx->msg_uart_rxd.msg_send_index= (SSR03 & 0x0007U);
	//---清楚错误标志位
	SIR03 = UARTx->msg_uart_rxd.msg_send_index;
	//---数据发送复位
	uart_read_reset(UARTx);
#endif
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
#ifdef TYPE_UART2
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
			STMK1 = 1U;    /* disable INTST2 interrupt */
			//---数据发送复位
			uart_send_reset(UARTx);
		}
	}
	else
	{
		//---不使能中断
		STMK1 = 1U;    /* disable INTST2 interrupt */
		//---数据发送复位
		uart_send_reset(UARTx);
	}
#endif
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
#ifdef TYPE_UART3
	//---数据缓存区
	vltuint8_t temp_rx = 0;
	//---判断数据接收是否符合
	if (UARTx->msg_uart_rxd.msg_state == UART_STATE_BUSY)
	{
		//---缓存接收到的数据
		temp_rx = RXD2;
		//---依次接收数据
		switch (UARTx->msg_uart_rxd.msg_step)
		{
			case 0:
			{
				if (UARTx->msg_uart_rxd.msg_read_index != 0)
				{
					UARTx->msg_uart_rxd.msg_read_index = 0;
				}
				//---存储接收的数据
				UARTx->msg_uart_rxd.msg_p_data_buffer[UARTx->msg_uart_rxd.msg_read_index++] = temp_rx;
				//---更新时间节拍
				UARTx->msg_uart_rxd.msg_time_tick = UARTx->msg_uart_rxd.msg_f_time_tick();
				//---执行下一步骤
				UARTx->msg_uart_rxd.msg_step++;
				break;
			}
			case 1:
			{
				//---存储接收到的数据
				UARTx->msg_uart_rxd.msg_p_data_buffer[UARTx->msg_uart_rxd.msg_read_index++] = temp_rx;
				//---更新时间节拍
				UARTx->msg_uart_rxd.msg_time_tick = UARTx->msg_uart_rxd.msg_f_time_tick();
				//---判断数据的接收是否超出缓存区
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
//////函		数:
//////功		能: 接受错误处理
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_it_irq_read_error_handle_three(UART_HandleType* UARTx)
{
#ifdef TYPE_UART3
	//---数据缓存区
	vltuint8_t temp_rx = 0;
	//---获取收到的数据
	temp_rx = RXD2;
	//---获取错误标识
	UARTx->msg_uart_rxd.msg_send_index = (SSR11 & 0x0007U);
	//---清楚错误标志位
	SIR11 = UARTx->msg_uart_rxd.msg_send_index;
	//---数据发送复位
	uart_read_reset(UARTx);
#endif
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
#ifdef TYPE_UART3
	if (UARTx->msg_uart_txd.msg_send_index != 0)
	{
		//---校验数据发送状态
		if (UARTx->msg_uart_txd.msg_read_index != UARTx->msg_uart_txd.msg_send_index)
		{
			//--->>>数据未发送完成
			TXD2 = UARTx->msg_uart_txd.msg_p_data_buffer[UARTx->msg_uart_txd.msg_read_index];
			UARTx->msg_uart_txd.msg_read_index++;
		}
		else
		{
			//---不使能中断
			STMK2 = 1U;    /* disable INTST1 interrupt */
			//---数据发送复位
			uart_send_reset(UARTx);
		}
	}
	else
	{
		//---不使能中断
		STMK2 = 1U;    /* disable INTST1 interrupt */
		//---数据发送复位
		uart_send_reset(UARTx);
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
uint8_t uart_init(UART_HandleType* UARTx, uint32_t(*func_time_tick)(void))
{
	//---注册计数函数
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
	//---端口初始化
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

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: log模式发送数据
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_printf_log_one(UART_HandleType* UARTx, char* fmt, va_list args)
{
#if defined(TYPE_UART1)&&(MODULE_LOG_ENABLE>0)&&(MODULE_LOG_UART_INDEX==2)
	int16_t length = 0;
	//---等待上次发送完成
	uart_wait_send_idle(UARTx);
	//---用于向字符串中打印数据、数据格式用户自定义;返回参数是最终生成字符串的长度
	length = vsnprintf(
		&(UARTx->msg_uart_txd.msg_p_data_buffer[0]),
		UART_TX_SIZE_MAX_ONE, fmt, args);
	//---无数据，返回
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
//////函		数:
//////功		能: log模式发送数据
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_printf_log_two(UART_HandleType* UARTx, char* fmt, va_list args)
{
#if defined(TYPE_UART2)&&(MODULE_LOG_ENABLE>0)&&(MODULE_LOG_UART_INDEX==2)
	int16_t length = 0;
	//---等待上次发送完成
	uart_wait_send_idle(UARTx);
	//---用于向字符串中打印数据、数据格式用户自定义;返回参数是最终生成字符串的长度
	length = vsnprintf(
		&(UARTx->msg_uart_txd.msg_p_data_buffer[0]),
		UART_TX_SIZE_MAX_TWO, fmt, args);
	//---无数据，返回
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
//////函		数:
//////功		能: log模式发送数据
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_printf_log_three(UART_HandleType* UARTx, char* fmt, va_list args)
{
#if defined(TYPE_UART3)&&(MODULE_LOG_ENABLE>0)&&(MODULE_LOG_UART_INDEX==3)
	int16_t length = 0;
	//---等待上次发送完成
	uart_wait_send_idle(UARTx);
	//---用于向字符串中打印数据、数据格式用户自定义;返回参数是最终生成字符串的长度
	length = vsnprintf(
		&(UARTx->msg_uart_txd.msg_p_data_buffer[0]),
		UART_TX_SIZE_MAX_THREE, fmt, args);
	//---无数据，返回
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
//////函		数:
//////功		能: log模式发送数据
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void uart_printf_log(UART_HandleType* UARTx, char* fmt, va_list args)
{
	//---端口初始化
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