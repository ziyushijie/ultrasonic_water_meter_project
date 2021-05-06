#include "ms1022_lib.h"
#include "delay_lib.h"
#include "r_cg_intp.h"
#include "math.h"
#include "r_cg_pclbuz.h"

extern _Bool MS1022_Interrupt_FLAG; // MS1022�жϱ�־���ж�Ϊ1��
extern _Bool SPI_BUSY_RX; // SPI������ɱ�־���ж�Ϊ0��
extern _Bool SPI_BUSY_TX; // SPI������ɱ�־���ж�Ϊ0��

unsigned int MS1022_STA_REG = 0x0000; // ����״̬�Ĵ���ֵ��һ���ڲ������ȡʹ�á�

__Get_Temperature  Get_TEMP; // �����¶�ֵ
__Get_Time	 Get_Time;   // ʱ����ز���
__Get_FlowHeat  Get_FlowHeat;	 // ����������ز���

static float Count_Temper_Rt(float input_PoRes); // ͨ����ֵ�������϶�

// ��ʼ��Ӳ��SPI�ӿ�
void HanderSPI_Interface_Init(void){
	
	//R_SAU0_Create(); // �����ӿ�
	R_CSI00_Start(); // ����
	
	// 32.768KHZ���----ACLK
	R_PCLBUZ0_Create();
	R_PCLBUZ0_Start();

	R_INTC_Create();
    R_INTC7_Start();  // MS1022�жϹܽ�����
	
}


/*-----------------------------------------------------------------
* �������ƣ�MS1022_Delay_us
* ����˵����MS1022����ʹ�õľ�ȷ��ʱ
* �������룺Xus��ʱʱ�䣻ȡֵ��Χ:[1,65535]��ֻ����10��������
* �����������
* �������ͣ�ֱ��ʹ�� SET_Delay_us ����ԭ�ͻ��׼ȷ����Ϊ����Ҳ����ִ��ʱ�䡣
-----------------------------------------------------------------*/
void MS1022_Delay_us(unsigned int Xus)
{
	
	unsigned int Temp_delay = Xus / 10; // ������ʱʱ��
	SET_Delay_us(Temp_delay);
	
}

/*------------------------------------------------------------
* �������ƣ�MS1022_RESET
* ����˵����MS1022������λ
* �����������
* �������ͣ�ϵͳ�ϵ縴λ��������500us
-------------------------------------------------------------*/
void MS1022_RESET(void)
{

	OUT_MS1022_RSTN = 0;
	MS1022_Delay_us(100); 
	OUT_MS1022_RSTN = 1;
	
	MS1022_Delay_us(600); // >500us
}

/*------------------------------------------------------------
* �������ƣ�MS1022_SPI_ENABLE
* ����˵����MS1022��SPIͨѶ����
* �����������
* �������ͣ�ʹ��Ƭѡ
-------------------------------------------------------------*/
void MS1022_SPI_ENABLE(void)
{
	NOP();NOP();NOP();NOP();NOP();
	OUT_MS1022_SSN = 0u;
	NOP();NOP();NOP();NOP();NOP();
}

/*------------------------------------------------------------
* �������ƣ�MS1022_SPI_DISABLE
* ����˵����MS1022��SPIͨѶ�رգ�0-1-0
* �����������
* �������ͣ�ʧ��Ƭѡ
-------------------------------------------------------------*/
void MS1022_SPI_DISABLE(void)
{
	OUT_MS1022_SSN = 0u;
	NOP();NOP();NOP();NOP();NOP();
	OUT_MS1022_SSN = 1u;
	NOP();NOP();NOP();NOP();NOP();
	MS1022_Delay_us(1);
	OUT_MS1022_SSN = 0u;
	NOP();NOP();NOP();NOP();NOP();	
}


/*------------------------------------------------------------
* �������ƣ�SPI_MS1022_Write
* ����˵����SPIд�ֽ�
* �������룺W_Data Ҫд�������
* �����������
* �������ͣ����ݴӸ�λ��ʼ����
-------------------------------------------------------------*/
void SPI_MS1022_Write(unsigned char W_Data)
{
	unsigned char temp_data = W_Data;
	
	SPI_BUSY_TX = 1;
	
	R_CSI00_Send_Receive(&temp_data,1u,0u); // ����1byte����
	
	while(SPI_BUSY_TX); // �ȴ��������
}


/*------------------------------------------------------------
* �������ƣ�SPI_MS1022_Read
* ����˵����SPI���ֽ�
* �������룺��
* �����������ȡ��һ�ֽ�����
* �������ͣ����ݴӸ�λ��ʼ����
-------------------------------------------------------------*/
unsigned char SPI_MS1022_Read(void)
{

	unsigned char Temp_Data = 0x00;

	SPI_BUSY_RX = SPI_BUSY_TX = 1; 
	
	R_CSI00_Send_Receive(0u,1u,&Temp_Data); // ����1byte����
	
	//while(SPI_BUSY_RX || SPI_BUSY_TX); // �ȴ��������
	while(SPI_BUSY_RX); // �ȴ��������
	
	return Temp_Data;
	
}


/*------------------------------------------------------------
* �������ƣ�SPI_MS1022_Write4Byte
* ����˵����SPIд4�ֽ�
* �������룺W_Data Ҫд�������
* �����������
* �������ͣ����ݴӸ�λ��ʼ����
-------------------------------------------------------------*/
void SPI_MS1022_Write4Byte(unsigned long W_Data)
{
	short i;
	
	for(i = 3;i >= 0; i--)
	{
		
		SPI_MS1022_Write(W_Data >> (i << 3));
		 
	}
	
}


/*------------------------------------------------------------
* �������ƣ�SPI_MS1022_Read4Byte
* ����˵����SPI���ֽ�
* �������룺��
* �����������ȡ��һ�ֽ�����
* �������ͣ����ݴӸ�λ��ʼ����
-------------------------------------------------------------*/
unsigned long SPI_MS1022_Read4Byte(void)
{

	unsigned char i;
	unsigned long Temp_Data = 0x00000000;

	for(i = 0;i < 4; i++)
	{
		Temp_Data |= SPI_MS1022_Read();
		Temp_Data <<= 8;
	}

	return Temp_Data;
	
}

/*------------------------------------------------------------
* �������ƣ�MS1022_Init
* ����˵����MS1022������ʼ��
* �������룺RegNum �Ĵ����ţ�0��1~7��RegData ���Ĵ�����д������
		  RegData32λ����
* �����������
* �������ͣ���
* �������ܣ�д�Ĵ���
-------------------------------------------------------------*/
void MS1022_Write_Reg(unsigned char RegNum,unsigned long RegData)
{
	
	MS1022_SPI_ENABLE();  // ʹ��Ƭѡ
	
	SPI_MS1022_Write(WRITE_BasicAddr | RegNum);  // Ŀ��Ĵ��� [ �ڻ���ַ���ۼ�ѡ��Ĵ��� ]
	SPI_MS1022_Write4Byte(RegData); // �Ĵ�������
	
	MS1022_SPI_DISABLE(); // ʧ��Ƭѡ
}

/*------------------------------------------------------------
* �������ƣ�Read_Reg
* �������룺RegNum �Ĵ����� 0-7
		  ReadData �Ĵ�������
* �����������
* �������ͣ���
* �������ܣ����Ĵ���
-------------------------------------------------------------*/
unsigned long MS1022_Read_Reg(unsigned char RegNum)
{
    unsigned long ReadData = 0;
	
	MS1022_SPI_ENABLE();
	
	SPI_MS1022_Write(READ_BasicAddr | RegNum); // �ڻ���ַ���ۼ�ѡ��Ĵ���
	ReadData = SPI_MS1022_Read4Byte();
	
	MS1022_SPI_DISABLE();
	
	return ReadData;
}

/*------------------------------------------------------------
* �������ƣ�MS1022_Transfer
* ����˵������MS1022���Ͳ�������
* �������룺MS1022_OPCODE : ������
*         LengthByte �� ��ȡ�����ֽڳ���
* ���������buff_x �����ݻ�����
* �������ͣ����ֻ��������ʱ�����˲�����Ĳ����������������ȫ����Ϊ0
-------------------------------------------------------------*/
void MS1022_Transfer_Ask(unsigned char MS1022_OPCODE,unsigned char *buff_x,unsigned char LengthByte)
{
	
	unsigned char i;
	
	MS1022_SPI_ENABLE(); // Ƭѡ
	
	SPI_MS1022_Write(MS1022_OPCODE); // ���Ͳ�����
	
	if(0u != LengthByte)  // ��� LengthByte = 0 ��ʾֻ�ǵ����ķ��Ͳ����룬������ȡ����
	for(i = 0; i < LengthByte;i++){
		*buff_x++ = SPI_MS1022_Read();
	}
	
	MS1022_SPI_DISABLE(); // �ر�Ƭѡ 
}

/*----------------------------------------------------------------------
* �������ƣ�MS1022_Transfer_Data
* ����˵������MS1022�������ݻ����ڵ� Length ���ֽ�����(��������MS1022���ڲ��Ĵ���)
* �������룺MS1022_OPCODE : ������
*         LengthByte �� ���������ֽڳ���
* ���������buff_x �������ݻ�����
* �������ͣ� 
-----------------------------------------------------------------------*/
void MS1022_Transfer_Data(unsigned char *Rec_Data,unsigned char Length)
{
	
	unsigned char i = 0;
	MS1022_SPI_ENABLE(); // Ƭѡ
	
	for(i = 0;i < Length; i++){
	SPI_MS1022_Write(*(Rec_Data + i));
	}
	
	MS1022_SPI_DISABLE(); // �ر�Ƭѡ 
	
}

/*--------------------------------------------------------------------
// �������ܣ���ȡ����ID
// �������ƣ�MS1022_Read_ID
// �������룺��
// ���������7���ֽڵ�����ID
// �������ͣ���ȡ����ID[56bit = 7byte * 8bit]
// 			ʵ���Ƕ�ȡ7���Ĵ��������8λ������EEPROM����
---------------------------------------------------------------------*/
void MS1022_Read_ID(unsigned char *buff_x)
{
	MS1022_Transfer_Ask(READ_ID,buff_x,7u); // ������ȡID
}

/*--------------------------------------------------------------------
// �������ܣ���ʾд�Ĵ��� 1 �еĸ� 8 λ,��������ͨ��
// �������ƣ�MS1022_Read_REG_1
// �������룺��
// ���������1���ֽ�
// �������ͣ���������ͨ��;���ֲ�22ҳ��2.���Ĵ���
---------------------------------------------------------------------*/
unsigned char MS1022_Read_REG_1(void)
{
	unsigned char temp = 0x00;
	
	MS1022_SPI_ENABLE(); // Ƭѡ
	MS1022_Delay_us(20); // 20us
	
	SPI_MS1022_Write(REG_1); // ����ͨѶ��ask
	temp = SPI_MS1022_Read();
	
	MS1022_Delay_us(20); // 20us
	MS1022_SPI_DISABLE(); // ʧ��Ƭѡ
	
	return temp;
	
}

/*--------------------------------------------------------------------
// �������ܣ������ȵĲ�����ֵ,�̶������������� 1 λΪ����
// �������ƣ�MS1022_Read_PWM1ST
// �������룺��
// ���������1���ֽ�
// �������ͣ���������ͨ��;���ֲ�22ҳ��2.���Ĵ���
---------------------------------------------------------------------*/
unsigned char MS1022_Read_PWM1ST(void)
{
	unsigned char temp = 0x00;
	
	MS1022_SPI_ENABLE(); // Ƭѡ
	MS1022_Delay_us(20); // 20us
	
	SPI_MS1022_Write(READ_PW1ST); // PW1ST ask
	temp = SPI_MS1022_Read();
	
	MS1022_Delay_us(20); // 20us
	MS1022_SPI_DISABLE(); // ʧ��Ƭѡ
	
	return temp;
}


/*--------------------------------------------------------------------
// �������ܣ���״̬�Ĵ���
// �������ƣ�MS1022_Read_STAT
// �������룺��
// ���������16bit,��λ��ǰ: res_state 
// �������ͣ���������ͨ��;���ֲ�22ҳ��2.���Ĵ���
---------------------------------------------------------------------*/
unsigned int MS1022_Read_STAT(void)
{
	unsigned int res_state = 0x0000;
	
	MS1022_SPI_ENABLE(); // Ƭѡ
	
	SPI_MS1022_Write(STAT); // STAT ask
	
	res_state = SPI_MS1022_Read();
	res_state = (res_state << 8) | SPI_MS1022_Read();
	
	MS1022_SPI_DISABLE(); // ʧ��Ƭѡ 
	
	return res_state;
	
}



///*--------------------------------------------------------------------
//// �������ܣ���ȡ����ʱ��У������
//// �������ƣ�MS1022_Read_ID
//// �������룺��
//// ���������7���ֽڵ�����ID
//// �������ͣ���ȡ����ID[56bit = 7byte * 8bit]
//// 			ʵ���Ƕ�ȡ7���Ĵ��������8λ������EEPROM����
//---------------------------------------------------------------------*/
//unsigned char Get_CLK_x(float *g_factor_value)                              
//{
//    unsigned char ret = 0;
//    unsigned long factor_unit;    
//	unsigned char SPI_Buf[4] = { 0 };
	
	
//	MS1022_Transfer_Ask(MS1022_INIT, NULL, 0);         //TDC_GP22���ٳ�ʼ��  
//    MS1022_Transfer_Ask(START_Cal_Resonator, NULL, 0); //�������پ���У׼����

//    MS1022_Transfer_Ask(READ_BasicAddr, SPI_Buf, 4);           //��GP22����Ĵ���0(���پ���У׼�������)32bit���ݵ�SPI_Buf/��λ�ڵ�һλ

//	factor_unit = SPI_Buf[0];
//    factor_unit = (factor_unit << 8) | SPI_Buf[1];
//    factor_unit = (factor_unit << 8) | SPI_Buf[2];
//    factor_unit = (factor_unit << 8) | SPI_Buf[3];
	
//    *g_factor_value = (float)(factor_unit)/65536;          //16λ����λ16С��λ
//    *g_factor_value = 244.140625 / (*g_factor_value * 0.25);   //������پ���У��ϵ��(8�������32768HZ��У��ϵ��)
	
//    return ret;
//}


/*------------------------------------------------------------
* �������ƣ�MS1022_Init
* ����˵����MS1022������ʼ��
* �������룺��
* �����������
* �������ͣ���
-------------------------------------------------------------*/
void MS1022_Init(void)
{
//	DBG_SendString("MS1022�����ʼ�������Ե�...\r\n");
//	HanderSPI_Interface_Init();  // Ӳ���ӿ���س�ʼ��
	
	MS1022_RESET(); // оƬϵͳ��λ
	MS1022_SPI_ENABLE(); // Ƭѡ
	
	// 1-��ʼ������-�����ƣ�
	SPI_MS1022_Write(POWER_On_Reset);  // �ϵ縴λ
	
	MS1022_Delay_us(800);//700us�ȴ������ȶ�
	MS1022_Read_STAT();
	MS1022_Write_Reg(0,0xF347E810);                 //����MS1022���üĴ���0 
	MS1022_Write_Reg(1,0x21444012);                 //����MS1022���üĴ���1
	MS1022_Write_Reg(6,0xCEC06006);                 //����MS1022���üĴ���6��ģ��ģʽ��
	//MS1022_Write_Reg(6,0x4EC06006);                 //����MS1022���üĴ���6������ģʽ��

    // 3-���������ã����ƣ�
	MS1022_Write_Reg(2,0xA01F14A0);                 //����MS1022���üĴ���2
	MS1022_Write_Reg(3,0x08000000);                 //����MS1022���üĴ���3
	MS1022_Write_Reg(4,0x20000000);                 //����MS1022���üĴ���4
	MS1022_Write_Reg(5,0x50000005);       	      	//����MS1022���üĴ���5������ģʽ��
	
	// �ٲ���
	Get_Temperature();
	Get_Flow();
	
	MS1022_SPI_DISABLE(); // �ر�Ƭѡ
	
}


	/*------------------------------------------------------------
* �������ƣ�Get_Temperature
* ����˵��������PT1000����ͨ�����¶�ֵ
* �������룺��
* ���������PT1000����������״̬�Ͳ������
* �������ͣ���
-------------------------------------------------------------*/
void Get_Temperature(void) //�¶Ȳ���
{
	unsigned int err_time = 0L; // ��ʱʱ�� , ����״̬
	unsigned char SamplingNum; // ��������
	unsigned long temper_val[4] = { 0.0f };  // �����ȡ���¶�ֵ

	float temper_red[TEMP_SAMP_NUM] = { 0.0f };// N�β������¶�ֵ-red
	float temper_blue[TEMP_SAMP_NUM] = { 0.0f };// N�β������¶�ֵ-blue	
	float temper_temp = 0.0f; 
	float temper_red1,temper_red2; 
	float temper_blue1,temper_blue2;
	
	ON_MS1022_FOSC(); // ������
	
	Get_TEMP.PT1000_STATE.PT1000_MeasureSTA = MS1022_TempMeasure_OK; // Ĭ��״̬�����ɹ�
	MS1022_SPI_ENABLE();

	// ��ʼ���¶�����

	SET_CMD(POWER_On_Reset); // 0x50
	MS1022_Delay_us(800);//700us�ȴ������ȶ�
	MS1022_Write_Reg(0,0xf347e810);
	MS1022_Write_Reg(1,0x21444012);
	MS1022_Write_Reg(6,0xcec06006);
	
	for(SamplingNum = 0;SamplingNum < TEMP_SAMP_NUM;SamplingNum++){ // ������6��,������ƽ���˲�����

	MS1022_SPI_ENABLE();
	SET_CMD(MS1022_INIT); // 0x70��ʼ��
	SET_CMD(START_TEMP); // 0x02,����һ���¶Ȳ���	
	MS1022_Delay_us(800);//700us�ȴ������ȶ�
	
	MS1022_STA_REG = MS1022_Read_STAT(); // ��ȡ״̬�Ĵ���������Ӵ˾�
	
	while(!MS1022_Interrupt_FLAG)  // �ȴ��ж�
	{
		if(++err_time > 1000U){
			Get_TEMP.PT1000_STATE.PT1000_MeasureSTA = MS1022_TempMeasure_Fail; // ��־��ʱ����ʧ�ܣ�
			break; 
		}
	}
	MS1022_Interrupt_FLAG = 0; // ����жϱ�־
	
	// ��ȡ������4��ͨ��ֵ
	temper_val[0] = MS1022_Read_Reg(0);
	temper_val[1] = MS1022_Read_Reg(1);
	temper_val[2] = MS1022_Read_Reg(2);
	temper_val[3] = MS1022_Read_Reg(3);
	
	// ��ɫ�¶�̽ͷ
	temper_temp = (float)(temper_val[0]) / temper_val[2];
	temper_red1 = temper_temp * MS1022_CH3_REF_RES_1000;  // ͨ��3�ο�����	
	temper_temp = (float)temper_val[0] / temper_val[3];
	temper_red2 = temper_temp * MS1022_CH4_REF_RES_1400;  // ͨ��4�ο�����
	
	// ��ɫ�¶�̽ͷ
	temper_temp  = (float)temper_val[1] / temper_val[2];
	temper_blue1 = temper_temp * MS1022_CH3_REF_RES_1000;
	temper_temp  = (float)temper_val[1] / temper_val[3];
	temper_blue2 = temper_temp * MS1022_CH4_REF_RES_1400;

	temper_red[SamplingNum] = (temper_red1 + temper_red2) / 2.0f;
	temper_blue[SamplingNum] = (temper_blue1 + temper_blue2) / 2.0f;

	}	

	OFF_MS1022_FOSC(); // �رվ���
	
	// ����ƽ��ֵ�˲�
	for(SamplingNum = 0u,temper_red1 = temper_blue1 = 0.0f;SamplingNum < TEMP_SAMP_NUM;SamplingNum++){
		temper_red1 += temper_red[SamplingNum];
		temper_blue1 += temper_blue[SamplingNum];
	}

	temper_red1 /= TEMP_SAMP_NUM;
	temper_blue1 /= TEMP_SAMP_NUM;
	
	// �¶�ֵ����
	temper_red1 = Count_Temper_Rt(temper_red1);
	temper_blue1 = Count_Temper_Rt(temper_blue1);

	// �����¶�ֵ
	Get_TEMP.Temperature_In = temper_red1;// RED
	Get_TEMP.Temperature_Out = temper_blue1;// BLUE

	// �¶�У׼...........
	
	// PT1000����������״̬ʶ����
	if((int)Get_TEMP.Temperature_In < -50){  // �����¶ȴ�������·����
	
		Get_TEMP.PT1000_STATE.PT1000_Red_In = MS1022_Temp_Short;
		
	}else if((int)Get_TEMP.Temperature_In > 300){ // �����¶ȴ�������·����
		
	    Get_TEMP.PT1000_STATE.PT1000_Red_In = MS1022_Temp_Open;
	
	}else{  // �����¶ȴ���������
		
	    Get_TEMP.PT1000_STATE.PT1000_Red_In = MS1022_Temp_Normal;
		
	}
	
	if((int)Get_TEMP.Temperature_Out < -50){  // �����¶ȴ�������·����
	
		Get_TEMP.PT1000_STATE.PT1000_BLUE_Out = MS1022_Temp_Short;
		
	}else if((int)Get_TEMP.Temperature_Out > 300){ // �����¶ȴ�������·����
		
	    Get_TEMP.PT1000_STATE.PT1000_BLUE_Out = MS1022_Temp_Open;
	
	}else{  // �����¶ȴ���������
		
	    Get_TEMP.PT1000_STATE.PT1000_BLUE_Out = MS1022_Temp_Normal;
		
	}	
	
	MS1022_SPI_DISABLE(); 
		
	// �ж��¶ȴ�����״̬������ֱ���жϻ������¶�ֵ��
	// �ٸ���PT1000�Ĳ�����Χ�ǣ�-50 ~ 300 ���϶ȣ�����ж�����ֵ��ȡ������Χ�������ޡ�
	// ʹ�ô˷�ʽ�жϵĺô��ǿ���׼ȷ��λ��ĳ���¶ȴ�������״̬�����������׷�������
	// ��·���¶�ֵ < -50 : ʵ��Ϊ -247���϶�
	// ��·���¶�ֵ > 300:ʵ��Ϊ 3398263 ���϶�
	//Get_TEMP.PT1000_STATE.PT1000_MeasureSTA = MS1022_TempMeasure_OK; // ��־�����¶ȳɹ�
	
	
	// �����²� = ��ˮ�¶� - ��ˮ�¶�
	Get_TEMP.Temperature_Diff = Get_TEMP.Temperature_Out - Get_TEMP.Temperature_In;
	
}

/*------------------------------------------------------------
* �������ƣ�Count_Temper_Rt
* ����˵�������ݲ�������ֵ�����¶�ֵ�����϶ȣ�
* �������룺input_PoRes:��������ֵ
* ������������϶�
* �������ͣ���
-------------------------------------------------------------*/
static float Count_Temper_Rt(float input_PoRes)
{
	long double temp_e3 = 8e-10 * input_PoRes * input_PoRes * input_PoRes; // 3����
	long double temp_e2 = 7e-6 * input_PoRes * input_PoRes; // 2����
	long double temp = 0;
	float temperature = 0;
	
    temp = -247.01f + 0.2393f * input_PoRes + temp_e2 + temp_e3; //���㵱ǰ���ݲο����������δ���в������¶�
	temperature = temp;
	return temperature;
}

// ð������--������
void RubbleSort(float array[],unsigned char len)   // ��С��������
{
    unsigned char i,j,k;
    float temp;
    for( i = 0;i < len - 1;i++ )
    {
        k = i;
        for( j = i + 1;j < len;j++ )
        {
            if(array[j] < array[k])             
            k=j;
        }
		// ����
        temp = array[k];
        array[k] = array[i];
        array[i] = temp;
    }
}

void ULong_RubbleSort(unsigned long *Array,unsigned char Len){
    unsigned char i,j,k;
    unsigned long temp;
	
    for( i = 0;i < Len - 1;i++ )
    {
        k = i;
        for( j = i + 1;j < Len;j++ )
        {
            if(Array[j] < Array[k])             
            k=j;
        }
		// ����
        temp = Array[k];
        Array[k] = Array[i];
        Array[i] = temp;
    }
}


// ��������
void SET_CMD(unsigned char Cmd_1Byte)
{
		MS1022_SPI_ENABLE();
		SPI_MS1022_Write(Cmd_1Byte);
		MS1022_SPI_DISABLE();
}

// ����ƽ��ֵ
unsigned long tab_long_average(unsigned long* indata,unsigned char len){

	unsigned long resualt = 0;
	unsigned char i = 0;
	for(i = 0;i < len;i++){
		
		resualt += (*indata)++;
	}
	return (unsigned long)((float)resualt / len);
	
}

// ����ƽ��ֵ
float tab_float_average(float* input_value,unsigned char len)
{
	unsigned char i = 0;
	double resualt = 0.0f;
	
	for(i = 0;i < len;i++){
		
		resualt += input_value[i];
	}
	return (float)(resualt / len);
}

//��ȡ����ʱ��У������
double Get_CLK_ref(void)                              
{
    unsigned int ret = 0;
    unsigned long factor_unit = 0UL;
	double g_factor_value = 0.0f;  
	
	SET_CMD(MS1022_INIT); // 0x70��ʼ��
    SET_CMD(START_Cal_Resonator); //�������پ���У׼����
	//MS1022_Interrupt_FLAG
	Wait_InterruptSucceed(ret,500u,MS1022_Interrupt_FLAG);// �ȴ������ж���ɲ��Զ������־

	//��GP22����Ĵ���0(���پ���У׼�������)32bit���ݵ�SPI_Buf/��λ�ڵ�һλ
	factor_unit = MS1022_Read_Reg(0);

	g_factor_value = (double)(factor_unit) / 65536.0f;          //16λ����λ16С��λ
    g_factor_value = 244.140625 / (g_factor_value * 0.25);   //������پ���У��ϵ��(8�������32768HZ��У��ϵ��)

	return g_factor_value;
}


/*------------------------------------------------------------
* �������ƣ�Get_Flow
* ����˵��������õ��õ����Ρ����β�������ʱ�䣨us����ʱ��
* �������룺��
* �����������
* �������ͣ����ֵ�� typedef struct __get_time__ �� Get_Time�С�
-------------------------------------------------------------*/
void Get_Flow(void)
{
	unsigned int err_time = 0x0000;  // ��ʱʱ��
	unsigned char samping_n = 0;  // ���������ۼӱ���
	
	// ���Σ�����ز�����ֵ2���ۼӺ�
	unsigned long sum_up_0_val[FLOW_SAMP_NUM] = { 0 };
	unsigned long sum_up_1_val[FLOW_SAMP_NUM] = { 0 };
	unsigned long sum_up_2_val[FLOW_SAMP_NUM] = { 0 };
	// ���Σ�����ز�����ֵ2���ۼӺ�
	unsigned long sum_down_0_val[FLOW_SAMP_NUM] = { 0 };
	unsigned long sum_down_1_val[FLOW_SAMP_NUM] = { 0 };
	unsigned long sum_down_2_val[FLOW_SAMP_NUM] = { 0 };

	// ����
	double up_time_0 = 0,up_time_1 = 0,up_time_2 = 0;
	double down_time_0 = 0,down_time_1 = 0,down_time_2 = 0;
	
	// ����������ʼ������
	SET_CMD(POWER_On_Reset); // 0x50
	MS1022_Delay_us(800);//700us�ȴ������ȶ�	
	
	/*----- �ҵ����� ---------------*/ 
//	MS1022_Write_Reg(0,0xf347e800);
//	MS1022_Write_Reg(1,0x21444001);
//	MS1022_Write_Reg(2,0xa01f3802);
//	MS1022_Write_Reg(3,0x08000003);//
//	MS1022_Write_Reg(4,0x20000004);
//	MS1022_Write_Reg(5,0x30000005);	
//	MS1022_Write_Reg(6,0xcec06006);// Ӧ�ó��������������ģ��ģʽ����Ҫ32KHZ�ź����롣
//	//MS1022_Write_Reg(6,0x4ec06006);// ����ģʽ
	
	/*------------ ���ˣ������� --------------*/
	MS1022_Write_Reg(0,0xf347e800);	//Я����������
	MS1022_Write_Reg(1,0x21444001);	
	MS1022_Write_Reg(2,0xa01e0002);	
	MS1022_Write_Reg(3,0xf8510303);	
	MS1022_Write_Reg(4,0x20004f04);	
	MS1022_Write_Reg(5,0x30000005);	
	MS1022_Write_Reg(6,0xcec06006);	
	
	// ������ʱ�����
	FOREACH(samping_n,0u,FLOW_SAMP_NUM,1u)ORG       // ������ʼ
			
/*================ [��һ�β�������] ================================*/

	MS1022_Write_Reg(5,0x30000005);  // ���β���ģʽ
	SET_CMD(MS1022_INIT); // 0x70��ʼ��
	SET_CMD(START_TOF); // 0x01	
	SET_Delay_us(50);  // �ȴ�MS1022׼��
	
	Get_Time.flow_status = MS1022_Read_STAT(); // ��״̬
	
	Wait_InterruptSucceed(err_time,50u,MS1022_Interrupt_FLAG);// �ȴ������ж���ɲ��Զ������־

	SET_CMD(MS1022_INIT); // 0x70��ʼ��
	SET_CMD(START_TOF); // 0x01	
	SET_Delay_us(50);  // �ȴ�MS1022׼��
	
	Get_Time.flow_status = MS1022_Read_STAT(); // ��״̬
	
	Wait_InterruptSucceed(err_time,50u,MS1022_Interrupt_FLAG);// �ȴ������ж���ɲ��Զ������־

	SET_CMD(MS1022_INIT); // 0x70��ʼ��
	SET_CMD(START_TOF); // 0x01	
	SET_Delay_us(50);  // �ȴ�MS1022׼��
	
	Get_Time.flow_status = MS1022_Read_STAT(); // ��״̬
	
	Wait_InterruptSucceed(err_time,50u,MS1022_Interrupt_FLAG);// �ȴ������ж���ɲ��Զ������־
	
	// ��ȡ3���ز������ʱ��ֵ
	sum_up_0_val[samping_n] = MS1022_Read_Reg(0);
	sum_up_1_val[samping_n] = MS1022_Read_Reg(1);
	sum_up_2_val[samping_n] = MS1022_Read_Reg(2);
	
/*================ [�ڶ��β�������] ================================*/

	MS1022_Write_Reg(5,0x50000005);// ����ģʽ����
	SET_CMD(MS1022_INIT); // 0x70��ʼ��
	SET_CMD(START_TOF); // 0x01	
	SET_Delay_us(50);  // �ȴ�MS1022׼��

	Get_Time.flow_status = MS1022_Read_STAT(); // ��״̬
	
	Wait_InterruptSucceed(err_time,50u,MS1022_Interrupt_FLAG);// �ȴ������ж���ɲ��Զ������־
	
	// ��ȡ3���ز������ʱ��ֵ
	sum_down_0_val[samping_n] = MS1022_Read_Reg(0);
	sum_down_1_val[samping_n] = MS1022_Read_Reg(1);
	sum_down_2_val[samping_n] = MS1022_Read_Reg(2);

	END // n�β����������
	
	OFF_MS1022_FOSC(); // �ر�MS1022�����
	
	// ð��
	ULong_RubbleSort(sum_up_0_val,FLOW_SAMP_NUM); // ���ε�1���ز���β���ֵ����
	ULong_RubbleSort(sum_up_1_val,FLOW_SAMP_NUM); // ���ε�2���ز���β���ֵ����
	ULong_RubbleSort(sum_up_2_val,FLOW_SAMP_NUM); // ���ε�3���ز���β���ֵ����

	ULong_RubbleSort(sum_down_0_val,FLOW_SAMP_NUM); // ���ε�1���ز���β���ֵ����
	ULong_RubbleSort(sum_down_1_val,FLOW_SAMP_NUM); // ���ε�2���ز���β���ֵ����
	ULong_RubbleSort(sum_down_2_val,FLOW_SAMP_NUM); // ���ε�3���ز���β���ֵ����	
	
	// ��������---����ƽ��ֵ����
	// ����ز�������ʱ��
	ARRAY_AVERAGE(sum_up_0_val,samping_n,FLOW_SAMP_NUM,DEL_ARRAY_NUM,up_time_0);// ��һ���ز�ƽ��ֵ
	ARRAY_AVERAGE(sum_up_1_val,samping_n,FLOW_SAMP_NUM,DEL_ARRAY_NUM,up_time_1);// �ڶ����ز�ƽ��ֵ
	ARRAY_AVERAGE(sum_up_2_val,samping_n,FLOW_SAMP_NUM,DEL_ARRAY_NUM,up_time_2);// �������ز�ƽ��ֵ
//	Get_Time.Forward_Time = (up_time_0 + up_time_1 + up_time_2) / 3.0f / 65536.0f / 4.0f; // �õ�����ʱ��
	Get_Time.Forward_Time = (up_time_0 + up_time_1 + up_time_2) / 786432.0f; // �õ�����ʱ��
	
	// ����ز�������ʱ��
	ARRAY_AVERAGE(sum_down_0_val,samping_n,FLOW_SAMP_NUM,DEL_ARRAY_NUM,down_time_0);// ��һ���ز�ƽ��ֵ
	ARRAY_AVERAGE(sum_down_1_val,samping_n,FLOW_SAMP_NUM,DEL_ARRAY_NUM,down_time_1);// �ڶ����ز�ƽ��ֵ
	ARRAY_AVERAGE(sum_down_2_val,samping_n,FLOW_SAMP_NUM,DEL_ARRAY_NUM,down_time_2);// �������ز�ƽ��ֵ
//	Get_Time.Reverse_Time = (down_time_0 + down_time_1 + down_time_2) / 3.0f / 65536.0f / 4.0f; // �õ�����ʱ��
	Get_Time.Reverse_Time = (down_time_0 + down_time_1 + down_time_2) / 786432.0f; // �õ�����ʱ��

	Get_Time.Time_Diff = Get_Time.Forward_Time - Get_Time.Reverse_Time; // ʱ���
	
	// ���������� ʱ�ӽ������¶ȶ�������Ӱ�졢�ֶ����Խ�����
	Get_CLK_ref();
	// ������������
	#define VOICE_SPEED_C   1400.0f  // m/s	----- �����е�������ˮ�е��ٶ�
	#define WATER_PIPE_L    0.006f   // m   ----- ����������·������
	
	Get_FlowHeat.flow_speed = (double)(pow(VOICE_SPEED_C,2U) * Get_Time.Time_Diff / 1000000.0f) / (WATER_PIPE_L * sqrt(2));
	Get_FlowHeat.flow_speed /= 36.0f; // m3/h
	
	#undef  VOICE_SPEED_C
	#undef  WATER_PIPE_L
	
	// ��������
	// ���¶�
	// ��������
	
	// y = 1.3363x - 14.254

//	if(Get_FlowHeat.flow_speed > )
//	Get_FlowHeat.flow_speed = 1.3363f * Get_FlowHeat.flow_speed - 14.254f;
	// Get_FlowHeat.flow_speed = ((Get_Time.Time_Diff / (Get_Time.Forward_Time * Get_Time.Reverse_Time)) / 1000000.0f / 3600.0f) * (0.06 / sqrt(2));
}




