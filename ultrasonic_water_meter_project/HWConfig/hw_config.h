#ifndef HW_CONFIG_H_
#define HW_CONFIG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////

	///////////////软件版本的基本配置---开始/////////////////////////////////////////////////
	#define UWM_SW_VERSION1					0
	#define UWM_SW_VERSION2					0
	#define UWM_SW_VERSION3					1
	///////////////软件版本的基本配置---结束/////////////////////////////////////////////////
	
	///////////////LOG信息的基本配置---开始/////////////////////////////////////////////////
	#define MODULE_LOG_ENABLE				1
	#define MODULE_LOG_UART_INDEX			2
	//===LOG模块
#if (MODULE_LOG_ENABLE>0)
	#define MODULE_LOG_GPIO					0
	#define MODULE_LOG_I2C					0
	#define MODULE_LOG_SPI					0
	#define MODULE_LOG_AT24CXX				0
	#define MODULE_LOG_MS1022				0
#endif
	///////////////LOG信息的基本配置---结束/////////////////////////////////////////////////
	
	///////////////SysTick信息的基本配置---开始/////////////////////////////////////////////////
	//===默认的最小系统节拍,单位是ms，系统节拍的最小值是1ms，可以通过这里修改，必须是1的整数倍
	#define	SYS_TICK_MIN_PULSE_WIDTH		10
	#define SYS_MIN_PULSE_WIDTH				SYS_TICK_MIN_PULSE_WIDTH
	///////////////SysTick信息的基本配置---结束/////////////////////////////////////////////////

	///////////////CRC信息的基本配置---开始/////////////////////////////////////////////////
	#define CRC_MIN_PULSE_WIDTH				SYS_MIN_PULSE_WIDTH
	///////////////CRC信息的基本配置---结束/////////////////////////////////////////////////

	///////////////GPIO信息的基本配置---开始/////////////////////////////////////////////////
	#define GPIO_MIN_PULSE_WIDTH			SYS_MIN_PULSE_WIDTH
	///////////////GPIO信息的基本配置---结束/////////////////////////////////////////////////

	///////////////UART信息的基本配置---开始/////////////////////////////////////////////////
	//#define TYPE_UART1
	#define TYPE_UART2
	#define TYPE_UART3

	#define UART_MIN_PULSE_WIDTH			SYS_MIN_PULSE_WIDTH
	#define UART_BASE_SIZE_OFFSET			0

	//===>>>串口1的初始化---开始//////////////////////////////////////////////////////////
	//===接收超时时间，单位ms
	#define UART_RX_MAX_TIME_ONE			100
	//===发送超时时间，单位ms
	#define UART_TX_MAX_TIME_ONE			100
	//===通讯波特率
	#define UART_BAUD_RATE_ONE				2400
	//===单字节的发送或者接受的时间
	#define UART_BYTE_TIME_ONE				((10000/UART_BAUD_RATE_ONE)+1)
	//---检查数据是否是偶数
	#if ((UART_BYTE_TIME_ONE%UART_MIN_PULSE_WIDTH)!=0)
		#undef UART_BYTE_TIME_ONE
		#define UART_BYTE_TIME_ONE			((10000/UART_BAUD_RATE_ONE)+1+UART_MIN_PULSE_WIDTH)
	#endif
	//===定义缓存区的大小
	#define UART_RX_BASE_SIZE_ONE			98//1800
	#define UART_TX_BASE_SIZE_ONE			UART_RX_BASE_SIZE_ONE	
	//===接收缓存区
	#define UART_RX_SIZE_MAX_ONE			(UART_RX_BASE_SIZE_ONE+UART_BASE_SIZE_OFFSET)
	//===发送缓存区
	#define UART_TX_SIZE_MAX_ONE			(UART_TX_BASE_SIZE_ONE+UART_BASE_SIZE_OFFSET)
	//===>>>串口1的初始化---结束//////////////////////////////////////////////////////////

	//===>>>串口2的初始化---开始//////////////////////////////////////////////////////////
	//===接收超时时间，单位ms
	#define UART_RX_MAX_TIME_TWO			100
	//===发送超时时间，单位ms
	#define UART_TX_MAX_TIME_TWO			100
	//===通讯波特率
	#define UART_BAUD_RATE_TWO				2400
	//===单字节的发送或者接受的时间
	#define UART_BYTE_TIME_TWO				((10000/UART_BAUD_RATE_TWO)+1)
	//---检查数据是否是偶数
	#if ((UART_BYTE_TIME_TWO%UART_MIN_PULSE_WIDTH)!=0)
		#undef UART_BYTE_TIME_TWO
		#define UART_BYTE_TIME_TWO			((10000/UART_BAUD_RATE_TWO)+1+UART_MIN_PULSE_WIDTH)
	#endif
	//===定义缓存区的大小
	#define UART_RX_BASE_SIZE_TWO			274//1800
	#define UART_TX_BASE_SIZE_TWO			UART_RX_BASE_SIZE_TWO	
	//===接收缓存区
	#define UART_RX_SIZE_MAX_TWO			(UART_RX_BASE_SIZE_TWO+UART_BASE_SIZE_OFFSET)
	//===发送缓存区
	#define UART_TX_SIZE_MAX_TWO			(UART_TX_BASE_SIZE_TWO+UART_BASE_SIZE_OFFSET)
	//===>>>串口2的初始化---结束//////////////////////////////////////////////////////////

	//===>>>串口3的初始化---开始//////////////////////////////////////////////////////////
	//===接收超时时间，单位ms
	#define UART_RX_MAX_TIME_THREE			100
	//===发送超时时间，单位ms
	#define UART_TX_MAX_TIME_THREE			100
	//===通讯波特率
	#define UART_BAUD_RATE_THREE			2400
	//===单字节的发送或者接受的时间
	#define UART_BYTE_TIME_THREE			((10000/UART_BAUD_RATE_THREE)+1)
	//---检查数据是否是偶数
	#if ((UART_BYTE_TIME_THREE%UART_MIN_PULSE_WIDTH)!=0)
		#undef UART_BYTE_TIME_THREE
		#define UART_BYTE_TIME_THREE		((10000/UART_BAUD_RATE_THREE)+1+UART_MIN_PULSE_WIDTH)
	#endif
	//===定义缓存区的大小
	#define UART_RX_BASE_SIZE_THREE			96//1800
	#define UART_TX_BASE_SIZE_THREE			UART_RX_BASE_SIZE_THREE	
	//===接收缓存区
	#define UART_RX_SIZE_MAX_THREE			(UART_RX_BASE_SIZE_THREE+UART_BASE_SIZE_OFFSET)
	//===发送缓存区
	#define UART_TX_SIZE_MAX_THREE			(UART_TX_BASE_SIZE_THREE+UART_BASE_SIZE_OFFSET)
	//===>>>串口3的初始化---结束//////////////////////////////////////////////////////////

	///////////////UART信息的基本配置---结束/////////////////////////////////////////////////
	
	
	//////////////////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*HW_CONFIG_H_ */
