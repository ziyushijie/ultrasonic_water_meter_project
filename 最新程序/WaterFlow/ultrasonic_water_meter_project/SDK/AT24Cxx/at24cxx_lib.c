
//#include "AT24C16.h"
//#include "stdlib.h"

//__CONVERT__  CONVERT;   


//void AT24C16_Init(void)
//{
//	R_IICA0_Create();
//}

//static void AT24C16_Delay(unsigned int XTime)
//{
//	while(XTime--);
//}


///*------------------------------------------------------------
//* �������ƣ�AT24C16_SendData
//* ����˵��������д���ֽ�����
//* �������룺StartAddr����ʼ��ַ
//		  Data��Ҫ�洢������ָ��
//		  Length��Ҫд������ݳ���
//* �����������
//* �������ͣ���
//-------------------------------------------------------------*/
//void AT24C16_SendData(u16 StartAddr,u8 *const Data,u8 Length)
//{
//	u8 ADDR_H = (u8)(StartAddr >> 8); // �õ���8λ��ַ
//	u8 ADDR_L = (u8)StartAddr; // �õ���8λ��ַ
	
//	u8 *p = (u8*)malloc(Length+1);  // ������̬������
//	short int i = 0;
	
//	for(i = 1;i <= Length+1; i++) // ��������
//	{
//		*(p+i) = Data[i-1];
//	}
//	p[0] = ADDR_L;  // ���ֽڴ洢������8λ�������ַ
	
//	R_IICA0_Master_Send(AT24Cxx_Address + (ADDR_H << 1),p,Length,200);// while�ڲ������յȴ�200��
//	AT24C16_Delay(8000); // д���ݣ�����ʱ�������6ms
//	free(p);  // �ͷŶ�̬����ռ�
//}


///*------------------------------------------------------------
//* �������ƣ�AT24C16_ReadData
//* ����˵�������������ֽ�����
//* �������룺StartAddr����ʼ��ַ
//		  Data�����������ɴ�ӳ���ȥ
//		  Length��Ҫ��ȡ�����ݳ���
//* �����������
//* �������ͣ���
//-------------------------------------------------------------*/
//void AT24C16_ReadData(u16 StartAddr,u8 *const Data,u8 Length) // ��ȡ����
//{
//	u8 ADDR_H = (u8)(StartAddr >> 8); // �õ���8λ��ַ
//	u8 ADDR_L = (u8)StartAddr; // �õ���8λ��ַ
	
//	R_IICA0_Master_Send(AT24Cxx_Address + (ADDR_H << 1),&ADDR_L,1,200); // Ҫ��ȡ�Ŀ�ʼ��Ԫ��ַ
//	AT24C16_Delay(500); // �������ʱ
//	R_IICA0_Master_Receive(AT24Cxx_Address,Data,Length,200); // ������
//	AT24C16_Delay(500); // �������ʱ
//}


///*------------------------------------------------------------
//* �������ƣ�Write_IntData
//* ����˵�������泤��������
//* �������룺StartAddr����ʼ��ַ
//		  SaveData��Ҫ���������
//* �����������
//* �������ͣ���
//-------------------------------------------------------------*/
//void Write_IntData(short int StartAddr,long int SaveData)
//{
//	CONVERT.ToLInt = SaveData;
//	AT24C16_SendData(StartAddr,CONVERT.To8Byte,8u); // save's data
//}

///*------------------------------------------------------------
//* �������ƣ�Read_IntData
//* ����˵������ȡ����������
//* �������룺StartAddr����ʼ��ַ
//* ��������������ĳ���������
//* �������ͣ���
//-------------------------------------------------------------*/
//long int Read_IntData(short int StartAddr)
//{
//	AT24C16_ReadData(StartAddr,CONVERT.To8Byte,8u); // read data
//	return CONVERT.ToLInt;
//}
