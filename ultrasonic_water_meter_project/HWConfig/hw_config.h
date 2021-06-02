#ifndef HW_CONFIG_H_
#define HW_CONFIG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////

	///////////////����汾�Ļ�������---��ʼ/////////////////////////////////////////////////
	#define UWM_SW_VERSION1					0
	#define UWM_SW_VERSION2					0
	#define UWM_SW_VERSION3					1
	///////////////����汾�Ļ�������---����/////////////////////////////////////////////////
	
	///////////////LOG��Ϣ�Ļ�������---��ʼ/////////////////////////////////////////////////
	#define MODULE_LOG_ENABLE				1
	#define MODULE_LOG_UART_INDEX			2
	//===LOGģ��
#if (MODULE_LOG_ENABLE>0)
	#define MODULE_LOG_GPIO					0
	#define MODULE_LOG_I2C					0
	#define MODULE_LOG_SPI					0
	#define MODULE_LOG_AT24CXX				0
	#define MODULE_LOG_MS1022				0
	#define MODULE_LOG_KEY_BUTTON			1
#endif
	///////////////LOG��Ϣ�Ļ�������---����/////////////////////////////////////////////////
	
	///////////////SysTick��Ϣ�Ļ�������---��ʼ/////////////////////////////////////////////////
	//===Ĭ�ϵ���Сϵͳ����,��λ��ms��ϵͳ���ĵ���Сֵ��1ms������ͨ�������޸ģ�������1��������
	#define	SYS_TICK_MIN_PULSE_WIDTH		1
	//===��С������ms
	#define SYS_MIN_PULSE_WIDTH				SYS_TICK_MIN_PULSE_WIDTH
	///////////////SysTick��Ϣ�Ļ�������---����/////////////////////////////////////////////////

	///////////////CRC��Ϣ�Ļ�������---��ʼ/////////////////////////////////////////////////
	//===��С������ms
	#define CRC_MIN_PULSE_WIDTH				SYS_MIN_PULSE_WIDTH
	///////////////CRC��Ϣ�Ļ�������---����/////////////////////////////////////////////////

	///////////////GPIO��Ϣ�Ļ�������---��ʼ/////////////////////////////////////////////////
	//===��С������ms
	#define GPIO_MIN_PULSE_WIDTH			SYS_MIN_PULSE_WIDTH
	//===���ȴ�ʱ��ms
	#define GPIO_MAX_WAIT_TIME				(4/GPIO_MIN_PULSE_WIDTH)
	///////////////GPIO��Ϣ�Ļ�������---����/////////////////////////////////////////////////

	///////////////SPI��Ϣ�Ļ�������---��ʼ/////////////////////////////////////////////////
	//===�������ģ��SPI
	//#define SPI_EBABLE_SW
	//===��С������ms
	#define SPI_MIN_PULSE_WIDTH				SYS_MIN_PULSE_WIDTH
	//===���ȴ�ʱ��ms
	#define SPI_MAX_WAIT_TIME				(4/GPIO_MIN_PULSE_WIDTH)
	///////////////SPI��Ϣ�Ļ�������---����/////////////////////////////////////////////////

	///////////////I2C��Ϣ�Ļ�������---��ʼ/////////////////////////////////////////////////
	//===����I2C�Ķ˿�Ϊ��©ģʽ
	//#define I2C_GPIO_MODE_OD			
	///////////////GPIO��Ϣ�Ļ�������---����/////////////////////////////////////////////////

	///////////////UART��Ϣ�Ļ�������---��ʼ/////////////////////////////////////////////////
	//#define TYPE_UART1
	#define TYPE_UART2
	#define TYPE_UART3

	//===��С������ms
	#define UART_MIN_PULSE_WIDTH			SYS_MIN_PULSE_WIDTH
	//===��������Сƫ��
	#define UART_BASE_SIZE_OFFSET			0

	//===>>>����1�ĳ�ʼ��---��ʼ//////////////////////////////////////////////////////////
	//===���ճ�ʱʱ�䣬��λms
	#define UART_RX_MAX_TIME_ONE			100
	//===���ͳ�ʱʱ�䣬��λms
	#define UART_TX_MAX_TIME_ONE			100
	//===ͨѶ������
	#define UART_BAUD_RATE_ONE				2400
	//===���ֽڵķ��ͻ��߽��ܵ�ʱ��
	#define UART_BYTE_TIME_ONE				((10000/UART_BAUD_RATE_ONE)+1)
	//---��������Ƿ���ż��
	#if ((UART_BYTE_TIME_ONE%UART_MIN_PULSE_WIDTH)!=0)
		#undef UART_BYTE_TIME_ONE
		#define UART_BYTE_TIME_ONE			((10000/UART_BAUD_RATE_ONE)+1+UART_MIN_PULSE_WIDTH)
	#endif
	//===���建�����Ĵ�С
	#define UART_RX_BASE_SIZE_ONE			98//1800
	#define UART_TX_BASE_SIZE_ONE			UART_RX_BASE_SIZE_ONE	
	//===���ջ�����
	#define UART_RX_SIZE_MAX_ONE			(UART_RX_BASE_SIZE_ONE+UART_BASE_SIZE_OFFSET)
	//===���ͻ�����
	#define UART_TX_SIZE_MAX_ONE			(UART_TX_BASE_SIZE_ONE+UART_BASE_SIZE_OFFSET)
	//===>>>����1�ĳ�ʼ��---����//////////////////////////////////////////////////////////

	//===>>>����2�ĳ�ʼ��---��ʼ//////////////////////////////////////////////////////////
	//===���ճ�ʱʱ�䣬��λms
	#define UART_RX_MAX_TIME_TWO			100
	//===���ͳ�ʱʱ�䣬��λms
	#define UART_TX_MAX_TIME_TWO			100
	//===ͨѶ������
	#define UART_BAUD_RATE_TWO				2400
	//===���ֽڵķ��ͻ��߽��ܵ�ʱ��
	#define UART_BYTE_TIME_TWO				((10000/UART_BAUD_RATE_TWO)+1)
	//---��������Ƿ���ż��
	#if ((UART_BYTE_TIME_TWO%UART_MIN_PULSE_WIDTH)!=0)
		#undef UART_BYTE_TIME_TWO
		#define UART_BYTE_TIME_TWO			((10000/UART_BAUD_RATE_TWO)+1+UART_MIN_PULSE_WIDTH)
	#endif
	//===���建�����Ĵ�С
	#define UART_RX_BASE_SIZE_TWO			274//1800
	#define UART_TX_BASE_SIZE_TWO			UART_RX_BASE_SIZE_TWO	
	//===���ջ�����
	#define UART_RX_SIZE_MAX_TWO			(UART_RX_BASE_SIZE_TWO+UART_BASE_SIZE_OFFSET)
	//===���ͻ�����
	#define UART_TX_SIZE_MAX_TWO			(UART_TX_BASE_SIZE_TWO+UART_BASE_SIZE_OFFSET)
	//===>>>����2�ĳ�ʼ��---����//////////////////////////////////////////////////////////

	//===>>>����3�ĳ�ʼ��---��ʼ//////////////////////////////////////////////////////////
	//===���ճ�ʱʱ�䣬��λms
	#define UART_RX_MAX_TIME_THREE			100
	//===���ͳ�ʱʱ�䣬��λms
	#define UART_TX_MAX_TIME_THREE			100
	//===ͨѶ������
	#define UART_BAUD_RATE_THREE			2400
	//===���ֽڵķ��ͻ��߽��ܵ�ʱ��
	#define UART_BYTE_TIME_THREE			((10000/UART_BAUD_RATE_THREE)+1)
	//---��������Ƿ���ż��
	#if ((UART_BYTE_TIME_THREE%UART_MIN_PULSE_WIDTH)!=0)
		#undef UART_BYTE_TIME_THREE
		#define UART_BYTE_TIME_THREE		((10000/UART_BAUD_RATE_THREE)+1+UART_MIN_PULSE_WIDTH)
	#endif
	//===���建�����Ĵ�С
	#define UART_RX_BASE_SIZE_THREE			96//1800
	#define UART_TX_BASE_SIZE_THREE			UART_RX_BASE_SIZE_THREE	
	//===���ջ�����
	#define UART_RX_SIZE_MAX_THREE			(UART_RX_BASE_SIZE_THREE+UART_BASE_SIZE_OFFSET)
	//===���ͻ�����
	#define UART_TX_SIZE_MAX_THREE			(UART_TX_BASE_SIZE_THREE+UART_BASE_SIZE_OFFSET)
	//===<<<����3�ĳ�ʼ��---����//////////////////////////////////////////////////////////

	///////////////UART��Ϣ�Ļ�������---����/////////////////////////////////////////////////
	
	
	///////////////AT24CXX��Ϣ�Ļ�������---��ʼ/////////////////////////////////////////////////
	//===��С������ms
	#define AT24CXX_MIN_PULSE_WIDTH			SYS_MIN_PULSE_WIDTH

	//===>>>EEPROM1�ĳ�ʼ��---��ʼ//////////////////////////////////////////////////////////
	//===�洢оƬ�ĵ�ID����
	#define AT24CXX_CHIP_TYPE_ONE									AT24C16
	//===���豸��д��ַ���ڲ����Զ�ת������ַ��ֻ֧��7λ��ַ���豸
	#define AT24CXX_WRITE_ADDR_ONE									0xA0
	//===ʹ��IOģ��I2CЭ��ʹ�ö���һ������Ŀ�ȣ���Сֵ��0
	#define AT24CXX_I2C_PLUSE_WIDTH_ONE								0
	//===I2Cʹ�õ�ģʽ��0---���ģ�⣬1---Ӳ���˿�
	#define AT24CXX_I2C_ENABLE_HW_ONE								0
	//===SCL�˿�
	#define AT24CXX_I2C_SCL_PORT_ONE								GPIOP4
	#define AT24CXX_I2C_SCL_BIT_ONE									GPIO_PIN_BIT_5
	//===SDA�˿�
	#define AT24CXX_I2C_SDA_PORT_ONE								GPIOP4
	#define AT24CXX_I2C_SDA_BIT_ONE									GPIO_PIN_BIT_4
	//===<<<EEPROM1�ĳ�ʼ��---����//////////////////////////////////////////////////////////
	
	///////////////AT24CXX��Ϣ�Ļ�������---����/////////////////////////////////////////////////

	///////////////MS1022��Ϣ�Ļ�������---��ʼ/////////////////////////////////////////////////	
	//===��С������ms
	#define MS1022_MIN_PULSE_WIDTH			SYS_MIN_PULSE_WIDTH
	//===����MS1022�Ĺ���������ʱ��
	#define MS1022_HSE_CLOK_MHZ				4.0f
	//===��ʱMS1022ʱ�ӵķ�Ƶ����1�ǲ�������2��2��Ƶ��3��4��4��Ƶ
	#define MS1022_CLKHSDIV_PRE				1
	//===����ÿ��ʱ�����ڵĿ�ȣ���λ��us
	#define MS1022_HSE_CLOCK_MIN_WIDTH		(1.0f/MS1022_HSE_CLOK_MHZ)
	//===�������������������С�����ȣ���λ��us
	#define MS1022_DIV_FIRE_MIN_WIDTH		4.0f
	//===�����¶Ȳɼ�ʹ����PT1000����PT100
	#define MS1022_ENABLE_PT1000			
	//===ͨ��3�Ӳ��������ֵ����λ��ŷķ
	#define MS1022_PT_RTD_REF1				1000
	//===ͨ��4�Ӳ��������ֵ����λ��ŷķ
	#define MS1022_PT_RTD_REF2				1400

	//===>>>TDC1�ĳ�ʼ��---��ʼ//////////////////////////////////////////////////////////
	//===SPIʹ�õ�ģʽ��0---���ģ�⣬1---Ӳ���˿�
#ifdef SPI_EBABLE_SW
	#define MS1022_SPI_ENABLE_HW_ONE								1
#else
	#define MS1022_SPI_ENABLE_HW_ONE								1 
#endif
	//===SS�˿�
	#define MS1022_SPI_CS_PORT_ONE									GPIOP1
	#define MS1022_SPI_CS_BIT_ONE									GPIO_PIN_BIT_5
	//===SCK�˿�
	#define MS1022_SPI_SCK_PORT_ONE									GPIOP1
	#define MS1022_SPI_SCK_BIT_ONE									GPIO_PIN_BIT_6

	//===MISO�˿�
	#define MS1022_SPI_MISO_PORT_ONE								GPIOP1
	#define MS1022_SPI_MISO_BIT_ONE									GPIO_PIN_BIT_7
	//===MOSI�˿�
	#define MS1022_SPI_MOSI_PORT_ONE								GPIOP0
	#define MS1022_SPI_MOSI_BIT_ONE									GPIO_PIN_BIT_0

	//===RST�˿�
	#define MS1022_RST_PORT_ONE										GPIOP1
	#define MS1022_RST_BIT_ONE										GPIO_PIN_BIT_4

	//===INT�˿�
	#define MS1022_INT_PORT_ONE										GPIOP0
	#define MS1022_INT_BIT_ONE										GPIO_PIN_BIT_2

	
	//===<<<TDC1�ĳ�ʼ��---����//////////////////////////////////////////////////////////
	
	///////////////MS1022��Ϣ�Ļ�������---����/////////////////////////////////////////////////

	///////////////������Ϣ�Ļ�������---��ʼ/////////////////////////////////////////////////	
	//===��С����ֵ
	#define KEY_BUTTON_MIN_PULSE_WIDTH								SYS_MIN_PULSE_WIDTH
	
	//===����֧�ֵİ�������
	#define KEY_BUTTON_MAX_NUM										2
	//===����1�˿�	
	#define KEY_BUTTON_PORT_ONE_K1									GPIOP13
	//===����1�˿ں�	
	#define KEY_BUTTON_BIT_ONE_K1									GPIO_PIN_BIT_7
	//===����1�˿ڼ����ƽ
	#define KEY_BUTTON_ACTIVE_LEVEL_ONE_K1							ACTIVE_LEVEL_LOW
	//===����1�������е�����
	#define KEY_BUTTON_INDEX_ONE_K1									0

	///////////////������Ϣ�Ļ�������---����/////////////////////////////////////////////////

	///////////////RTC��Ϣ�Ļ�������---��ʼ/////////////////////////////////////////////////	
	//===��С����ֵ����λ��ms
	#define RTC_MIN_PULSE_WIDTH										SYS_MIN_PULSE_WIDTH
	//===����������ʱ�������ʱ��Ľ��ĵ���С���壬��λ��10ms�������1ms�����32λ�����ݻᷢ���������
	#define RTC_YEAR_MIN_PULSE_WIDTH								10

	///////////////������Ϣ�Ļ�������---����/////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*HW_CONFIG_H_ */
