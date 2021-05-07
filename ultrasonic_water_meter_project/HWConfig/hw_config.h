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
#endif
	///////////////LOG��Ϣ�Ļ�������---����/////////////////////////////////////////////////
	
	///////////////SysTick��Ϣ�Ļ�������---��ʼ/////////////////////////////////////////////////
	//===Ĭ�ϵ���Сϵͳ����,��λ��ms��ϵͳ���ĵ���Сֵ��1ms������ͨ�������޸ģ�������1��������
	#define	SYS_TICK_MIN_PULSE_WIDTH		10
	#define SYS_MIN_PULSE_WIDTH				SYS_TICK_MIN_PULSE_WIDTH
	///////////////SysTick��Ϣ�Ļ�������---����/////////////////////////////////////////////////

	///////////////CRC��Ϣ�Ļ�������---��ʼ/////////////////////////////////////////////////
	#define CRC_MIN_PULSE_WIDTH				SYS_MIN_PULSE_WIDTH
	///////////////CRC��Ϣ�Ļ�������---����/////////////////////////////////////////////////

	///////////////GPIO��Ϣ�Ļ�������---��ʼ/////////////////////////////////////////////////
	#define GPIO_MIN_PULSE_WIDTH			SYS_MIN_PULSE_WIDTH
	///////////////GPIO��Ϣ�Ļ�������---����/////////////////////////////////////////////////

	///////////////UART��Ϣ�Ļ�������---��ʼ/////////////////////////////////////////////////
	//#define TYPE_UART1
	#define TYPE_UART2
	#define TYPE_UART3

	#define UART_MIN_PULSE_WIDTH			SYS_MIN_PULSE_WIDTH
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
	//===>>>����3�ĳ�ʼ��---����//////////////////////////////////////////////////////////

	///////////////UART��Ϣ�Ļ�������---����/////////////////////////////////////////////////
	
	
	//////////////////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*HW_CONFIG_H_ */
