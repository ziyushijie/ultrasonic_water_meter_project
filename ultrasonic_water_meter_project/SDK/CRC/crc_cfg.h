#ifndef CRC_CFG_H_
#define CRC_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "hw_config.h"
	#include "sys_tick_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////���ò���---��ʼ////////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	//===����ʹ�õ�CRCУ�鷽��
	//#define CRC_ENABLE_CRC32																							//---CRC32У�鷽ʽ
	//#define CRC_ENABLE_CRC16																							//---CRC16У�鷽ʽ
	//#define CRC_ENABLE_CRC8																								//---CRC8У�鷽ʽ
	#define CRC_ENABLE_CHECK_SUM																						//---У���У�鷽ʽ
#ifdef CRC
	#define CRC_ENABLE_CRC32_HW	
#endif

	#define CRC_CHECK_SUM_TYPE_NONE			0
	#define CRC_CHECK_SUM_TYPE_NORMAL		(CRC_CHECK_SUM_TYPE_NONE+1)
	#define CRC_CHECK_SUM_TYPE_SPECIAL		(CRC_CHECK_SUM_TYPE_NORMAL+1)

	//===CRC8У�鷽ʽ������
	#define CRC8_TABLE_07H					0x07																		//---CRC8У�鷽ʽ�Ļ���������0x07
	#define CRC8_TABLE_31H					0x31																		//---CRC8У�鷽ʽ�Ļ���������0x31
	#define CRC8_TABLE_5EH					0x5E																		//---CRC8У�鷽ʽ�Ļ���������0x5E
	#define CRC8_TABLE_9BH					0x9B																		//---CRC8У�鷽ʽ�Ļ���������0x5E
	#define CRC8_TABLE_39H					0x39																		//---CRC8У�鷽ʽ�Ļ���������0x5E
	#define CRC8_TABLE_D5H					0xD4																		//---CRC8У�鷽ʽ�Ļ���������0x5E
	#define CRC8_TABLE_1DH					0x1D																		//---CRC8У�鷽ʽ�Ļ���������0x5E
	#define CRC8_TABLE_2FH					0x2F																		//---CRC8У�鷽ʽ�Ļ���������0x5E

	#define CRC8_TYPE_NONE					0
	#define CRC8_TYPE_TABLE_07H				(CRC8_TYPE_NONE+1)
	#define CRC8_TYPE_TABLE_ITU				(CRC8_TYPE_TABLE_07H+1)
	#define CRC8_TYPE_TABLE_ROHC			(CRC8_TYPE_TABLE_ITU+1)
	#define CRC8_TYPE_TABLE_31H				(CRC8_TYPE_TABLE_ROHC+1)
	#define CRC8_TYPE_TABLE_MAXIM			(CRC8_TYPE_TABLE_31H+1)
	#define CRC8_TYPE_TABLE_5EH				(CRC8_TYPE_TABLE_MAXIM+1)
	#define CRC8_TYPE_TABLE_9BH				(CRC8_TYPE_TABLE_5EH+1)
	#define CRC8_TYPE_TABLE_WCDMA			(CRC8_TYPE_TABLE_9BH+1)
	#define CRC8_TYPE_TABLE_CDMA200			(CRC8_TYPE_TABLE_WCDMA+1)
	#define CRC8_TYPE_TABLE_39H				(CRC8_TYPE_TABLE_CDMA200+1)
	#define CRC8_TYPE_TABLE_DARC			(CRC8_TYPE_TABLE_39H+1)
	#define CRC8_TYPE_TABLE_D5H				(CRC8_TYPE_TABLE_DARC+1)
	#define CRC8_TYPE_TABLE_DVBS2			(CRC8_TYPE_TABLE_D5H+1)
	#define CRC8_TYPE_TABLE_1DH				(CRC8_TYPE_TABLE_DVBS2+1)
	#define CRC8_TYPE_TABLE_EBU				(CRC8_TYPE_TABLE_1DH+1)
	#define CRC8_TYPE_TABLE_ICODE			(CRC8_TYPE_TABLE_EBU+1)
	#define CRC8_TYPE_TABLE_2FH				(CRC8_TYPE_TABLE_ICODE+1)


	#define CRC8_ENABLE_TABLE_07H
	#define CRC8_ENABLE_TABLE_31H
	#define CRC8_ENABLE_TABLE_5EH

	#define CRC8_ENABLE_TABLE_9BH
	#define CRC8_ENABLE_TABLE_39H
	#define CRC8_ENABLE_TABLE_D5H
	#define CRC8_ENABLE_TABLE_1DH
	#define CRC8_ENABLE_TABLE_2FH	

	//===CRC16У�鷽ʽ������
	#define CRC16_TABLE_1021H				0x1021																		//---CRC16У�鷽ʽ�Ļ���������0x1021
	#define CRC16_TABLE_A001H				0xA001																		//---CRC16У�鷽ʽ�Ļ���������0xA001
	#define CRC16_TABLE_8005H				0x8005										 								//---CRC16У�鷽ʽ�Ļ���������0x8005
	#define CRC16_TABLE_3D65H				0x3D65										 								//---CRC16У�鷽ʽ�Ļ���������0x8005
	#define CRC16_TABLE_RTU					CRC16_TABLE_A001H

	//===CRC16��У�鷽ʽ����
	#define CRC16_TYPE_NONE					0																			//---��CRC
	#define CRC16_TYPE_TABLE_1021H			(CRC16_TYPE_NONE+1)															//---CRC�����ʼֵΪ0
	#define CRC16_TYPE_TABLE_1021H_0		(CRC16_TYPE_TABLE_1021H+1)													//---CRC�����ʼֵΪ0
	#define CRC16_TYPE_TABLE_1021H_1		(CRC16_TYPE_TABLE_1021H_0+1)												//---CRC�����ʼֵΪFFFF
	#define	CRC16_TYPE_CCITT				(CRC16_TYPE_TABLE_1021H_1+1)												//---CRCѭ������
	#define	CRC16_TYPE_TABLE_CCITT			(CRC16_TYPE_CCITT+1)															//---CRCѭ������
	#define	CRC16_TYPE_CCITT_FALSE			(CRC16_TYPE_TABLE_CCITT+1)													//---CRCѭ������
	#define	CRC16_TYPE_TABLE_CCITT_FALSE	(CRC16_TYPE_CCITT_FALSE+1)													//---CRCѭ������
	#define	CRC16_TYPE_XMODEM				(CRC16_TYPE_TABLE_CCITT_FALSE+1)												//---CRCѭ������
	#define	CRC16_TYPE_TABLE_XMODEM			(CRC16_TYPE_XMODEM+1)														//---CRCѭ������
	#define	CRC16_TYPE_X25					(CRC16_TYPE_TABLE_XMODEM+1)													//---CRCѭ������
	#define	CRC16_TYPE_TABLE_X25			(CRC16_TYPE_X25+1)															//---CRCѭ������
	#define	CRC16_TYPE_MODBUS				(CRC16_TYPE_TABLE_X25+1)													//---CRCѭ������
	#define	CRC16_TYPE_TABLE_MODBUS			(CRC16_TYPE_MODBUS+1)														//---CRCѭ������
	#define	CRC16_TYPE_IBM					(CRC16_TYPE_TABLE_MODBUS+1)													//---CRCѭ������
	#define	CRC16_TYPE_TABLE_IBM			(CRC16_TYPE_IBM+1)															//---CRCѭ������
	#define	CRC16_TYPE_MAXIM				(CRC16_TYPE_TABLE_IBM+1)													//---CRCѭ������
	#define	CRC16_TYPE_TABLE_MAXIM			(CRC16_TYPE_MAXIM+1)														//---CRCѭ������
	#define	CRC16_TYPE_USB					(CRC16_TYPE_TABLE_MAXIM+1)													//---CRCѭ������
	#define	CRC16_TYPE_TABLE_USB			(CRC16_TYPE_USB+1)															//---CRCѭ������
	#define CRC16_TYPE_RTU					(CRC16_TYPE_TABLE_USB+1)													//---CRC������
	#define CRC16_TYPE_TABLE_RTU			(CRC16_TYPE_RTU+1)															//---CRC������,��ʼֵΪ0

	#define CRC16_TYPE_DNP					(CRC16_TYPE_TABLE_RTU+1)													//---CRCѭ������
	#define CRC16_TYPE_TABLE_DNP			(CRC16_TYPE_DNP+1)	

	#define CRC16_TYPE_TABLE_A001H			(CRC16_TYPE_TABLE_DNP+1)													//---CRC�����㣬��ʼֵΪ0
	#define CRC16_TYPE_TABLE_A001H_0		(CRC16_TYPE_TABLE_A001H+1)													//---CRC�����㣬��ʼֵΪ0
	#define CRC16_TYPE_TABLE_A001H_1		(CRC16_TYPE_TABLE_A001H_0+1)												//---CRC�����㣬��ʼֵΪFFFF
	#define CRC16_TYPE_TABLE_8005H			(CRC16_TYPE_TABLE_A001H_1+1)												//---CRC�����㣬��ʼֵΪ0
	#define CRC16_TYPE_TABLE_8005H_0		(CRC16_TYPE_TABLE_8005H+1)													//---CRC�����㣬��ʼֵΪ0
	#define CRC16_TYPE_TABLE_8005H_1		(CRC16_TYPE_TABLE_8005H_0+1)												//---CRC�����㣬��ʼֵΪFFFF
	#define CRC16_TYPE_TABLE_RTU_0			(CRC16_TYPE_TABLE_8005H_1+1)												//---CRC������,��ʼֵΪ0
	#define CRC16_TYPE_TABLE_RTU_1			(CRC16_TYPE_TABLE_RTU_0+1)													//---CRC�����㣬��ʼֵΪFFFF

	//===CRC16��У�鷽ʽ��ʹ�ܲ���
	#define CRC16_ENABLE_TABLE_1021H	
	#define	CRC16_ENABLE_CITT			
	#define	CRC16_ENABLE_CITT_FALSE	
	#define	CRC16_ENABLE_XMODE		
	#define	CRC16_ENABLE_X25			
	#define	CRC16_ENABLE_MODBUS		
	#define	CRC16_ENABLE_IBM			
	#define	CRC16_ENABLE_MAXIM		
	#define	CRC16_ENABLE_USB			
	#define CRC16_ENABLE_RTU			
	#define CRC16_ENABLE_DNP			
	#define CRC16_ENABLE_TABLE_A001H	
	#define CRC16_ENABLE_TABLE_8005H	
	#define CRC16_ENABLE_TABLE_RTU	

	//===CRC32��У�鷽ʽ����
	#define CRC32_TYPE_NONE					0																			//---��CRC
	#define CRC32_TYPE_MPEG_2				(CRC32_TYPE_NONE+1)															//---CRC�����ʼֵΪ0
	#define CRC32_TYPE_TABLE_MPEG_2			(CRC32_TYPE_MPEG_2+1)														//---CRC�����ʼֵΪ0
	#define CRC32_TYPE_ISO_HDLC				(CRC32_TYPE_TABLE_MPEG_2+1)													//---CRC�����ʼֵΪ0
	#define CRC32_TYPE_TABLE_ISO_HDLC		(CRC32_TYPE_ISO_HDLC+1)														//---CRC�����ʼֵΪ0
	#define CRC32_TYPE_STM32				(CRC32_TYPE_TABLE_ISO_HDLC+1)												//---CRC�����ʼֵΪ0
	#define CRC32_TYPE_TABLE_STM32			(CRC32_TYPE_STM32+1)														//---CRC�����ʼֵΪ0

	#define	CRC32_ENABLE_MPEG_2
	#define	CRC32_ENABLE_ISO_HDLC
	#define	CRC32_ENABLE_STM32

	#define CRC_WAIT_MAX_TIME				(800/CRC_MIN_PULSE_WIDTH)

	//===�ṹ�嶨��
	typedef struct _CRC_HandleType		CRC_HandleType;
	//===ָ��ṹ�嶨��
	typedef struct _CRC_HandleType		*pCRC_HandleType;
	//===AT24Cxx�����ݽṹ��
	struct _CRC_HandleType
	{
		uint32_t msg_length;																							//---crc��������ݳ���
		uint32_t msg_crc;																								//---crc����ֵ
	};

	//===�ṹ�嶨��
	typedef struct _MY_CRC_HandleType		MY_CRC_HandleType;
	//===ָ��ṹ�嶨��
	typedef struct _MY_CRC_HandleType		*pMY_HandleType;
	//===CRC�����ݽṹ��
	struct _MY_CRC_HandleType
	{
		uint16_t msg_type_crc32;																						//--CRC32����
		uint16_t msg_type_crc16;																						//--CRC16����
		uint16_t msg_type_crc8;																							//--CRC8����
		uint16_t msg_type_check_sum;																					//--У�������
		uint32_t(*msg_f_crc32_type)(uint16_t, uint8_t*, uint32_t);
		uint16_t(*msg_f_crc16_type)(uint16_t, uint8_t*, uint32_t);
		uint8_t(*msg_f_crc8_type)(uint16_t, uint8_t*, uint32_t);
		uint8_t(*msg_f_check_sum_type)(uint16_t, uint8_t*, uint32_t);
	};

	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////���ò���---����////////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////

	//===��������
	void	 crc_time_tick_init(uint32_t(*func_time_tick)(void));
	void	 crc_init(uint32_t(*func_time_tick)(void));
	void	 crc_deinit(void);
	uint8_t	 crc_enable(void);
	uint32_t crc_crc32_crc(uint8_t *buffer, uint32_t length);
	uint32_t crc_crc32_type(uint16_t type, uint8_t* buffer, uint32_t length);
	uint16_t crc_crc16_table(uint16_t crcSeed, uint16_t crc, uint8_t* buffer, uint32_t length);
	uint8_t  crc_crc8_table(uint8_t crcSeed,uint8_t crc, uint8_t *buffer, uint32_t length);
	uint8_t	 crc_crc8_type(uint16_t type, uint8_t* buffer, uint32_t length);
	uint8_t  crc_check_sum_normal(uint8_t *buffer, uint32_t length);
	uint8_t  crc_check_sum_normal_pos(uint8_t* buffer, uint16_t pos, uint32_t length);
	uint8_t  crc_check_sum_special(uint8_t* buffer, uint32_t length);
	uint8_t  crc_check_sum_special_pos(uint8_t* buffer, uint16_t pos, uint32_t length);
	uint8_t  crc_check_sum_type(uint16_t type, uint8_t* buffer, uint32_t length);
	uint16_t crc_crc16_type(uint16_t type, uint8_t* buffer, uint32_t length);
	uint16_t crc_crc16_table_seed_data(uint16_t crcSeed, uint16_t crc_data, uint8_t* buffer, uint32_t length);
	void	 my_crc_init(MY_CRC_HandleType * CRCx, uint32_t(*func_time_tick)(void));

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* CRC_CFG_H_ */