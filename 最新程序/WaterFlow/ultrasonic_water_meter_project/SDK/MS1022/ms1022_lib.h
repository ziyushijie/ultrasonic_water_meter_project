#ifndef MS1022_LIB_H_
#define MS1022_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////

#include "ms1022_cfg.h"
#include "math.h"
#include "config.h"
#include "gpio_lib.h"

// �ο�����ֵΪ���ֵ����˴��ھ�̬���
#ifndef MS1022_CH3_REF_RES_1000
#define MS1022_CH3_REF_RES_1000   1000u   // ͨ��3�ο����� 1Kŷķ
#endif

#ifndef MS1022_CH4_REF_RES_1400  
#define MS1022_CH4_REF_RES_1400   1400u   // ͨ��4�ο����� 1.4Kŷķ
#endif

// �ҵĲ���ԭ�򣬸߲����ʿ��ٲ���������ټ��㡣����������Խ�����Խ������
#define TEMP_SAMP_NUM     6u     // �¶Ȳ����������ã�������ƽ���˲�


// ���������������4�Σ�ͨ����Ҫ����6��
#define FLOW_SAMP_NUM     40u     // ���������������ã�ʵ���������ٲ��ܵ���4�Σ�һ��10�ε�����
// ��ֵ��2��������С���ܲ�������
#define DEL_ARRAY_NUM     (FLOW_SAMP_NUM / 4u)    // ��������ֵҪ��ͷȥβ�ĸ���
// �������ü��
#if ((DEL_ARRAY_NUM + DEL_ARRAY_NUM + 2) > FLOW_SAMP_NUM)
#error "���ô���[MS1022_lib.h]������� DEL_ARRAY_NUM ����ͷȥβ���ò�������ȷ��"
#endif



/***********************�� �¶ȴ�����״̬�͹���-ORG �� *******************************/
// �� extern __Get_Temperature  Get_TEMP; �ж�ȡ
// ʹ�÷����� Get_TEMP.PT1000_STATE.����
// ����״̬
#define MS1022_TempMeasure_OK        0u   // �¶Ȳ����ɹ�
#define MS1022_TempMeasure_Fail      1u   // �¶Ȳ���ʧ�ܣ�[��ʱ]

// �¶ȴ�����״̬:ֻ�ܱ� PT1000_STATE �ṹ����á�
#define MS1022_Temp_Normal  		 1u   // �¶ȴ���������
#define MS1022_Temp_Open    		 2u   // �¶ȴ�������·����
#define MS1022_Temp_Short   		 3u   // �¶ȴ�������·����


/********************************�� END �� ****************************************/

typedef struct __get_temperature__   // �����¶Ȳ������
{
	
	float Temperature_In;  // �����¶ȡ�RED��
	float Temperature_Out; // �����¶ȡ�BLUE��
	float Temperature_Diff;// �¶Ȳ� = ��ˮ�¶� - ��ˮ�¶�
	struct __PT1000_Measure_State__
	{
		unsigned char PT1000_Red_In : 3; // �����¶ȴ�������·���·״̬
		unsigned char PT1000_BLUE_Out : 3; // �����¶ȴ�������·���·״̬
		unsigned char PT1000_MeasureSTA : 2; // �����Ƿ�ɹ���
		
	}PT1000_STATE;  // PT1000�¶ȴ�����״̬
	
}__Get_Temperature; // ���� Get_Temperature() ����֮�������Чʹ��

extern __Get_Temperature  Get_TEMP; // �����¶�ֵ[Read,�û������¶Ȳ�����������ܶ�ȡ]


typedef struct __get_time__
{
	
	double Forward_Time; // �������ʱ��@us
	double Reverse_Time; // �������ʱ��@us
	
//  /-------------------------------\
//	| Time_Diff > 0 | Time_Diff < 0 |
//	|---------------|---------------|
//	|  ����us��		|	����us)	|
//	\-------------------------------/

	double Time_Diff;    // ���������ʱ���@us
	
	unsigned int flow_status; // ����������״ֵ̬
	
}__Get_Time; // ��������ز�������

extern __Get_Time	 Get_Time;   // ʱ����ز���

typedef struct __get_flow_heat__
{
	
	double flow_speed;  // ����=������/Сʱ
	double flow_sum;    // �ۻ�����=������
	double current_heat;// ��ǰ����
	float  sum_heat;    // �ۻ�����
	
}__Get_FlowHeat;// ������������ز���.........

extern __Get_FlowHeat  Get_FlowHeat;

// ������ز���........



/*------------------------------------------------------------
*********** ˵�� **********************************************
* ���豸�˿����������
* RSTN:�͵�ƽ��λ�źţ�P14 [�������]
* SSN :Ƭѡ�źţ��͵�ƽ��Ч����P15 [�������]
* SCK:�����豸ͬ��ʱ���źţ�P16 [�������]
* SO(MISO):��������ӻ������P17 [��������]
* SI(MOSI):��������ӻ����룺P00 [�������]
*
* ACLK:32KHZʱ�������P07 [�������]---------Ӧ������Ϊ���룺��δ����
* INT:MS1022�ж�����ܽţ�P02  [MCU��Ӧ�ж���·���룺INT7]-�͵�ƽ��Ч
-------------------------------------------------------------*/
//-------------------------------------- MS1022��ش������Ĺ��ϻ����ֵ��ʶ -----------------




// ������������Ϣ��ʾ

/*============================ �ܽŶ��� ======================================================================*/

#define OUT_MS1022_RSTN      GPIO(1,4) //P1_bit.no4    // ��λ�ź�
#define OUT_MS1022_SSN       GPIO(1,5) //P1_bit.no5    // Ƭѡ�ź�
//#define OUT_MS1022_SCK     P1_bit.no6    // ͬ��ʱ���ź�
//#define OUT_MS1022_MOSI    P0_bit.no0    // �������
//#define IN_MS1022_MISO     P1_bit.no7    // ��������

//#define OUT_MS1022_ACLK      GPIO(0,7)// P0_bit.no7    // ģ��ģʽʱ32KHZʱ��---------Ӧ������Ϊ����
//#define IN_MS1022_INT      P0_bit.no2    // �жϲ�ѯ�ܽš������ж��źš�

///*===================== [ �������� ] ======================================================================*/

#define WRITE_BasicAddr      0x80      // д���ַ�Ļ���ַ[24bit��32bit]
#define READ_BasicAddr       0xB0      // �����ַ�Ļ���ַ[8bit��16bit��32bit]

#define READ_ID              0xB7      // ��ȡID [56λID]

									   // ����Ĵ�����һ�� 8 λ�Ĺ̶��������Ĵ��������� 1 λΪ�������� 7 λΪС����
#define READ_PW1ST           0xB8      // �����ȵĲ�����ֵ,�̶������������� 1 λΪ����- (����Ϊ8λ)

#define CFGReg_To_EEPROM     0xC0      // д���üĴ����� EEPROM
#define EEPROM_To_CFGReg     0xF0      // �� EEPROM ���ݴ������üĴ�����
#define EEPROM_and_Reg_SJMP  0xC6 	   // �� EEPROM �����üĴ������ݽ��бȽ�
#define MS1022_INIT          0x70      // ��ʼ��
#define POWER_On_Reset       0x50      // �ϵ縴λ

#define RES_0				 0XB0      // ��������� 1,�̶���������16 λ�������֣�16 λС�����֡�32bit��
#define RES_1				 0XB1      // ��������� 2,�̶���������16 λ�������֣�16 λС�����֡�32bit��
#define RES_2				 0XB2      // ��������� 3,�̶���������16 λ�������֣�16 λС�����֡�32bit��
#define RES_3				 0XB3      // ��������� 4,�̶���������16 λ�������֣�16 λС�����֡�32bit��

#define STAT                 0XB4      // ״̬�Ĵ�����16bit��

#define REG_1                0XB5      // ��ʾд�Ĵ��� 1 �еĸ� 8 λ,��������ͨ�š�8bit��

/*--- ���¼���������������ֲ��26ҳ���� [ORG]---------------------------------------------------------------------------------*/
#define START_TOF            0x01      // ����һ��ʱ�����
#define START_TEMP           0x02      // ���ᴥ��һ���¶Ȳ���
#define START_Cal_Resonator  0x03      // ���ᴥ��һ�ζ��ڸ��پ����У׼����
#define START_Cal_TDC        0x04      // ���������������������ο�ʱ������
#define START_TOF_Restart    0x05      // ����µĲ����뽫���� Start_TOF ����,�ֱ��������������ʱ�����������ʱ�������һ��
#define START_TEMP_Restart   0x06      // ��������뽫�������¶Ȳ��� Start_Temp ����
/*---------------------  [END] ----------------------------------------------------------------------------------------*/

//********** ״̬����Ƚϱ�־ *******************************************************
// ���״̬�Ĵ�����ȡ��ֵʹ�ü���[���б�ʶ���ǡ�1������״̬�Ĵ����е�λ��]
#define EEPROM_eq_CREG      0x8000     // ��ʾ���üĴ����е������Ƿ��� EEPROM ����ͬ; 1 = ��ͬ
#define EEPROM_DED          0x4000     // ��δ�����.�� EEPROM ���� 2 �����ܹ������Ĵ������; 1 = 2 ������
#define EEPROM_Error        0x2000     // �� EEPROM ����һ�������ұ�����; 1 = ����
#define Error_short         0x1000     // ��ʾ�����¶ȴ�����Ϊ��· ;1 = ��·
#define Error_open          0x0800     // ��ʾ�����¶ȴ�����Ϊ��·; 1 = ��·
#define Timeout_Precounter  0x0400     // ��ʾ������Χ 2 �� 14 λ��ֵ�����������; 1 = ���
#define Timeout_TDC         0x0200     // ��ʾ TDC ������Ԫ���; 1 = ���

#define of_hits_Ch_2        0x01C0     // ��ʾ�� channel 2 ��¼�µĵڼ���������
#define of_hits_Ch_1        0x0038     // ��ʾ�� channel 1 ��¼�µĵڼ���������

#define Pointer_result_register 0x0003 // ָ��ָ����һ���ս���Ĵ�����ַ

// ��ȡ״̬
#define get_EEPROM_eq_CREG 	    (MS1022_Read_STAT() & EEPROM_eq_CREG)
#define get_EEPROM_DED    	    (MS1022_Read_STAT() & EEPROM_DED)
#define get_EEPROM_Error        (MS1022_Read_STAT() & EEPROM_Error)
#define get_Error_short         (MS1022_Read_STAT() & Error_short)
#define get_Error_open		    (MS1022_Read_STAT() & Error_open)
#define get_Timeout_Precounter  (MS1022_Read_STAT() & Timeout_Precounter)
#define get_Timeout_TDC  		(MS1022_Read_STAT() & Timeout_TDC)

// ��ʾ�� channel 1,2 ��¼�µĵڼ���������   0000 0001 1100 0000
#define get_of_hits_Ch_1        ((MS1022_Read_STAT() & of_hits_Ch_1) >> 6u)
#define get_of_hits_Ch_2        ((MS1022_Read_STAT() & of_hits_Ch_2) >> 6u)

// ��ȡָ��ָ����һ���ս���Ĵ�����ַ
#define get_Point_res_reg		(MS1022_Read_STAT() & Pointer_result_register)

/*---------------------  [END] ----------------------------------------------------------------------------------------*/


void MS1022_Delay_us(unsigned int Xus); // us����ʱ

void HanderSPI_Interface_Init(void);// ��ʼ��Ӳ��SPI�ӿ�

void RubbleSort(float array[],unsigned char len); // ð���㷨-С��
void ULong_RubbleSort(unsigned long *Array,unsigned char Len); //ð��- ����

// ����ƽ���˲�
unsigned long tab_long_average(unsigned long* indata,unsigned char len);// ����ƽ��ֵ
float tab_float_average(float* input_value,unsigned char len);// ����ƽ��ֵ

/*############################### ��ORG��################################################################*/
// array:���飬variable:������len:���鳤�ȣ�del_array��Ҫ��ͷȥβ�ĸ���,average_output:���ֵ
#define ARRAY_AVERAGE(array,variable,len,del_array_len,average_output)  do{				\
																						\
average_output = 0u;	 																\
FOREACH(variable,0u + del_array_len,len - del_array_len,1u)ORG	 						\
average_output += array[variable];    						    					    \
END								     						     						\
average_output /= (double)(len - del_array_len - del_array_len); 					    \
}while(0u)
/*################################ ��END��##############################################################*/

void MS1022_RESET(void); // ��λ

void MS1022_SPI_ENABLE(void); // ʹ��Ƭѡ
void MS1022_SPI_DISABLE(void); // ʧ��Ƭѡ

void MS1022_Init(void); // ��ʼ������
void MS1022_Read_ID(unsigned char *buff_x); // ��ID[56bit = 7byte * 8bit]

void SPI_MS1022_Write(unsigned char W_Data); // д�ֽ�
unsigned char SPI_MS1022_Read(void); // ���ֽ�

void SPI_MS1022_Write4Byte(unsigned long W_Data); // SPIд32λ����
unsigned long SPI_MS1022_Read4Byte(void); // SPI��32λ����

void MS1022_Write_Reg(unsigned char RegNum,unsigned long RegData); // д�Ĵ���[32bit]
unsigned long MS1022_Read_Reg(unsigned char RegNum); // ���Ĵ���[32bit]

void MS1022_Transfer_Ask(unsigned char MS1022_OPCODE,unsigned char *buff_x,unsigned char LengthByte);// 
void MS1022_Transfer_Data(unsigned char *Rec_Data,unsigned char Length); // ��MS1022���ͻ�������

void SET_CMD(unsigned char Cmd_1Byte);// ��������

// �ȴ���������ж�
/*################################## �ȴ������жϡ�ORG��####################################*/
#define Wait_InterruptSucceed(err,err_MaxVal,__InterruptFlag)  do{						  \
																						  \
	while( !__InterruptFlag ){  														  \
																						  \
	if(++err > err_MaxVal){																  \
		__InterruptFlag = 0u;															  \
		err = 0u;									                                   	  \
		break;	     																      \
		}																				  \
    NOP();																				  \
    }																					  \
		__InterruptFlag = 0u;															  \
}while(0u)
/*################################## �ȴ������жϡ�END��####################################*/

/*--------------------------- ��ݲ������� ------------------------------*/

//#define SPI_SET_Idle()  OUT_MS1022_MOSI = OUT_MS1022_SCK = 0   // �������߿���״̬---��SPI_Init()�Ĺ���һ��
 
#define CMD_INIT() 		SPI_MS1022_Write(MS1022_INIT) // ��ʼ������
#define CMD_TOF()  		SPI_MS1022_Write(START_TOF)   // ����һ��ʱ�����
//#define CMD_TOF_TOW() 	SPI_MS1022_Write(START_TOF_Restart)  // �����������θ��Բ���һ��

//#define ACLK_ON() OUT_MS1022_ACLK = 1   // ����ACLK�ܽ�
//#define ACLK_OFF() OUT_MS1022_ACLK = 0   // �ر�ACLK�ܽ�

// �˲������Խ��͹���
#define  ON_MS1022_FOSC() MS1022_Write_Reg(0,0xF347E810)  // �����������ò���
#define OFF_MS1022_FOSC() MS1022_Write_Reg(0,0x0303e810) // �رվ���

#define UP_MODE() 		MS1022_Write_Reg(5,0x30000005)  // ��������
#define DOWN_MODE() 	MS1022_Write_Reg(5,0x50000005)  // ��������
//#define UP_DOWN_MODE()  MS1022_Write_Reg(5,0x90000005)  // ����������

#define MS1022_Power_On_Reset() SPI_MS1022_Write(POWER_On_Reset) // �ϵ縴λ

#define Start_Temp() MS1022_Transfer_Ask(START_TEMP,0u,0u)  // ����һ���¶Ȳ���

/*------------------------ �û����ܺ��� ------------------------------------*/

unsigned char MS1022_Read_REG_1(void); // ��д�Ĵ��� 1 �еĸ� 8 λ,��������ͨ��
unsigned char MS1022_Read_PWM1ST(void); // PW1ST
unsigned int  MS1022_Read_STAT(void); // ��״̬�Ĵ���
unsigned long MS1022_Timecheck(void); // ʱ��У��
double Get_CLK_ref(void); // ��ȡʱ������

void Get_Temperature(void); //�¶Ȳ���
void Get_Flow(void);		// ��ȡ����

extern unsigned int MS1022_STA_REG; // ״̬�Ĵ���ֵ��ִ�в�������Ч��

	
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* MS1022_LIB_H_ */