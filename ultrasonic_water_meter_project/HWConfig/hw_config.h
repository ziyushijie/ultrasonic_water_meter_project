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
	#define MODULE_LOG_KEY_BUTTON			1
#endif
	///////////////LOG信息的基本配置---结束/////////////////////////////////////////////////
	
	///////////////SysTick信息的基本配置---开始/////////////////////////////////////////////////
	//===默认的最小系统节拍,单位是ms，系统节拍的最小值是1ms，可以通过这里修改，必须是1的整数倍
	#define	SYS_TICK_MIN_PULSE_WIDTH		1
	//===最小脉冲宽度ms
	#define SYS_MIN_PULSE_WIDTH				SYS_TICK_MIN_PULSE_WIDTH
	///////////////SysTick信息的基本配置---结束/////////////////////////////////////////////////

	///////////////CRC信息的基本配置---开始/////////////////////////////////////////////////
	//===最小脉冲宽度ms
	#define CRC_MIN_PULSE_WIDTH				SYS_MIN_PULSE_WIDTH
	///////////////CRC信息的基本配置---结束/////////////////////////////////////////////////

	///////////////GPIO信息的基本配置---开始/////////////////////////////////////////////////
	//===最小脉冲宽度ms
	#define GPIO_MIN_PULSE_WIDTH			SYS_MIN_PULSE_WIDTH
	//===最大等待时间ms
	#define GPIO_MAX_WAIT_TIME				(4/GPIO_MIN_PULSE_WIDTH)
	///////////////GPIO信息的基本配置---结束/////////////////////////////////////////////////

	///////////////SPI信息的基本配置---开始/////////////////////////////////////////////////
	//===允许软件模拟SPI
	//#define SPI_EBABLE_SW
	//===最小脉冲宽度ms
	#define SPI_MIN_PULSE_WIDTH				SYS_MIN_PULSE_WIDTH
	//===最大等待时间ms
	#define SPI_MAX_WAIT_TIME				(4/GPIO_MIN_PULSE_WIDTH)
	///////////////SPI信息的基本配置---结束/////////////////////////////////////////////////

	///////////////I2C信息的基本配置---开始/////////////////////////////////////////////////
	//===配置I2C的端口为开漏模式
	//#define I2C_GPIO_MODE_OD			
	///////////////GPIO信息的基本配置---结束/////////////////////////////////////////////////

	///////////////UART信息的基本配置---开始/////////////////////////////////////////////////
	//#define TYPE_UART1
	#define TYPE_UART2
	#define TYPE_UART3

	//===最小脉冲宽度ms
	#define UART_MIN_PULSE_WIDTH			SYS_MIN_PULSE_WIDTH
	//===缓存区大小偏置
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
	//===<<<串口3的初始化---结束//////////////////////////////////////////////////////////

	///////////////UART信息的基本配置---结束/////////////////////////////////////////////////
	
	
	///////////////AT24CXX信息的基本配置---开始/////////////////////////////////////////////////
	//===最小脉冲宽度ms
	#define AT24CXX_MIN_PULSE_WIDTH			SYS_MIN_PULSE_WIDTH

	//===>>>EEPROM1的初始化---开始//////////////////////////////////////////////////////////
	//===存储芯片的的ID类型
	#define AT24CXX_CHIP_TYPE_ONE									AT24C16
	//===从设备的写地址，内部会自动转换读地址，只支持7位地址的设备
	#define AT24CXX_WRITE_ADDR_ONE									0xA0
	//===使用IO模拟I2C协议使用定义一个脉冲的宽度，最小值是0
	#define AT24CXX_I2C_PLUSE_WIDTH_ONE								0
	//===I2C使用的模式，0---软件模拟，1---硬件端口
	#define AT24CXX_I2C_ENABLE_HW_ONE								0
	//===SCL端口
	#define AT24CXX_I2C_SCL_PORT_ONE								GPIOP4
	#define AT24CXX_I2C_SCL_BIT_ONE									GPIO_PIN_BIT_5
	//===SDA端口
	#define AT24CXX_I2C_SDA_PORT_ONE								GPIOP4
	#define AT24CXX_I2C_SDA_BIT_ONE									GPIO_PIN_BIT_4
	//===<<<EEPROM1的初始化---结束//////////////////////////////////////////////////////////
	
	///////////////AT24CXX信息的基本配置---结束/////////////////////////////////////////////////

	///////////////MS1022信息的基本配置---开始/////////////////////////////////////////////////	
	//===最小脉冲宽度ms
	#define MS1022_MIN_PULSE_WIDTH			SYS_MIN_PULSE_WIDTH
	//===定义MS1022的工作主晶振时钟
	#define MS1022_HSE_CLOK_MHZ				4.0f
	//===定时MS1022时钟的分频数，1是不分屏，2是2分频，3和4是4分频
	#define MS1022_CLKHSDIV_PRE				1
	//===计算每个时钟周期的宽度，单位是us
	#define MS1022_HSE_CLOCK_MIN_WIDTH		(1.0f/MS1022_HSE_CLOK_MHZ)
	//===换能器的驱动脉冲的最小脉冲宽度，单位是us
	#define MS1022_DIV_FIRE_MIN_WIDTH		4.0f
	//===定义温度采集使用是PT1000还是PT100
	#define MS1022_ENABLE_PT1000			
	//===通道3接铂电阻的阻值，单位是欧姆
	#define MS1022_PT_RTD_REF1				1000
	//===通道4接铂电阻的阻值，单位是欧姆
	#define MS1022_PT_RTD_REF2				1400

	//===>>>TDC1的初始化---开始//////////////////////////////////////////////////////////
	//===SPI使用的模式，0---软件模拟，1---硬件端口
#ifdef SPI_EBABLE_SW
	#define MS1022_SPI_ENABLE_HW_ONE								1
#else
	#define MS1022_SPI_ENABLE_HW_ONE								1 
#endif
	//===SS端口
	#define MS1022_SPI_CS_PORT_ONE									GPIOP1
	#define MS1022_SPI_CS_BIT_ONE									GPIO_PIN_BIT_5
	//===SCK端口
	#define MS1022_SPI_SCK_PORT_ONE									GPIOP1
	#define MS1022_SPI_SCK_BIT_ONE									GPIO_PIN_BIT_6

	//===MISO端口
	#define MS1022_SPI_MISO_PORT_ONE								GPIOP1
	#define MS1022_SPI_MISO_BIT_ONE									GPIO_PIN_BIT_7
	//===MOSI端口
	#define MS1022_SPI_MOSI_PORT_ONE								GPIOP0
	#define MS1022_SPI_MOSI_BIT_ONE									GPIO_PIN_BIT_0

	//===RST端口
	#define MS1022_RST_PORT_ONE										GPIOP1
	#define MS1022_RST_BIT_ONE										GPIO_PIN_BIT_4

	//===INT端口
	#define MS1022_INT_PORT_ONE										GPIOP0
	#define MS1022_INT_BIT_ONE										GPIO_PIN_BIT_2

	
	//===<<<TDC1的初始化---结束//////////////////////////////////////////////////////////
	
	///////////////MS1022信息的基本配置---结束/////////////////////////////////////////////////

	///////////////按键信息的基本配置---开始/////////////////////////////////////////////////	
	//===最小脉冲值
	#define KEY_BUTTON_MIN_PULSE_WIDTH								SYS_MIN_PULSE_WIDTH
	
	//===定义支持的按键个数
	#define KEY_BUTTON_MAX_NUM										2
	//===按键1端口	
	#define KEY_BUTTON_PORT_ONE_K1									GPIOP13
	//===按键1端口号	
	#define KEY_BUTTON_BIT_ONE_K1									GPIO_PIN_BIT_7
	//===按键1端口激活电平
	#define KEY_BUTTON_ACTIVE_LEVEL_ONE_K1							ACTIVE_LEVEL_LOW
	//===按键1在数组中的索引
	#define KEY_BUTTON_INDEX_ONE_K1									0

	///////////////按键信息的基本配置---结束/////////////////////////////////////////////////

	///////////////RTC信息的基本配置---开始/////////////////////////////////////////////////	
	//===最小脉冲值，单位是ms
	#define RTC_MIN_PULSE_WIDTH										SYS_MIN_PULSE_WIDTH
	//===根据年月日时分秒计算时间的节拍的最小脉冲，单位是10ms；如果是1ms，最大32位的数据会发生溢出操作
	#define RTC_YEAR_MIN_PULSE_WIDTH								10

	///////////////按键信息的基本配置---结束/////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*HW_CONFIG_H_ */
