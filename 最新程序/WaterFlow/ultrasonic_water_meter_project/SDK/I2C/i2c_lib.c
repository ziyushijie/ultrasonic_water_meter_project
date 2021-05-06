#include "i2c_lib.h"


////����C51����ʱ����(1us/5us)
//void Delay(bit IF_Delay)
//{
//}

//void I2C_start(void)  //��ʼ�ź�
//{	
//	sda=1; 
//	scl=1;
//	Delay(Delay_5us);
//	sda=0;
//	Delay(Delay_5us);
//	scl=0;	
//	Delay(Delay_1us);
//}

//void I2C_stop()   //ֹͣ
//{	
//	scl=0;
//	sda=0;
//Delay(Delay_5us);
//	scl=1;
//Delay(Delay_5us);
//	sda=1;
//Delay(Delay_1us);
//}

//void I2C_ASK()  //Ӧ��
//{
//	sda = 0;
//	scl=1;
//	Delay(Delay_5us);
//	Delay(Delay_5us);
//	scl=0;
//	sda = 1;
//	Delay(Delay_5us);
//	sda = 0;
//}

//void I2C_notASK()//��Ӧ��
//{
//	sda=1;
//	Delay(Delay_5us);
//	Delay(Delay_5us);
//	scl=1;
//	Delay(Delay_5us);
//	Delay(Delay_5us);
//	scl=0;	
//}

//void I2C_wbyte(uchar date)	  //дһ���ֽ�
//{
//	uchar i,temp;
//	temp=date;
//	for(i=0;i<8;i++)
//	{
//		temp=temp<<1;
//		scl=0;
//		sda=CY;
//		Delay(Delay_5us);//��ʱ����4.7us �������ݱ仯
//		scl=1;
//		Delay(Delay_5us);//��ʱ����4.7us �������ݴ���

//	}
//	scl=0;
//	Delay(Delay_1us);
//}

//uchar I2C_rbyte()	  //��һ���ֽ�
//{
//	uchar i,k;
//	sda = 1;
//	for(i=0;i<8;i++)
//	{
//		scl=1;
//		Delay(Delay_5us);	
//		k=(k<<1)|sda;
//		Delay(Delay_5us);
//		scl=1;
//		Delay(Delay_5us);
//		scl = 0;
//		sda=1;
//		Delay(Delay_5us);
//	}
//		scl=0;
//	return k;
//}

///*
//����:�洢��������(д����)
//EEPROM_Address:������ַ
//Address:�洢��Ԫ��ַ
//_data:����
//*/
//void WriteData(uchar EEPROM_Address,uchar Address,uchar _data)
//{
//	I2C_start();
//	I2C_wbyte(EEPROM_Address+0);//������ַ
//	I2C_ASK();//˭��˭��
//	I2C_wbyte(Address);//�ӻ��ӵ�ַ
//	I2C_ASK();		
//	I2C_wbyte(_data);
//	I2C_ASK();
//	I2C_stop();
//	delay2(20);//�����ȶ� (�����ʱ����Ҫ >= 3ms)
//}
///*
//����:��ȡ������Ԫ������
//���������
//EEPROM_Address:������ַ
//Address:�洢��Ԫ��ַ(24c02:0~255)
//����ֵ���ӵ�Ԫ��ȡ��������
//*/
//uchar ReadData(uchar EEPROM_Address,uchar Address)
//{
//	uchar _data = 0;
//	I2C_start();
//	I2C_wbyte(EEPROM_Address+0); //��������ַ  ��������
//	I2C_ASK();//Ӧ��λ
//	I2C_wbyte(Address);//�ӻ��洢��Ԫ��ַ
//	I2C_ASK();//Ӧ��λ
//	I2C_start();//α�������������ݴ��䷽��
//	I2C_wbyte(EEPROM_Address+1);	//�ӻ���ַ  ��������
//	I2C_ASK();//Ӧ��λ
//	_data=I2C_rbyte();//��ȡ����
//	I2C_notASK();//����Ӧ��
//	I2C_stop();
//	return _data;
//}
///*
//����:�����������򵥸��洢��EEPROM��Ԫ��ַ��
//���������
//EEPROM_Address:������ַ
//Address:�洢��Ԫ��ַ(24c02:0~255)
//_data:���洢��������ָ��ĵ�ַ(���ݿ��:8bit)
//bnum:�ӵ�Ԫ��ַ��ʼ�Ĵ洢���ݵĸ���
//����ֵ����
//*/
//void IIC_WriteData(uchar EEPROM_Address,uchar Address,uchar *_data,uchar bnum)
//{
//	uchar i = 0;
//	I2C_start();
//	I2C_wbyte(EEPROM_Address);
//	I2C_ASK();//˭��˭��
//   	I2C_wbyte(Address);//�ӻ��ӵ�ַ
//	I2C_ASK();	
//	for(i = 0;i<bnum;i++,_data++)
//	{	
//	I2C_wbyte(*_data);
//	I2C_ASK();
//	}
//	I2C_stop();
//   delay2(20);//�����ȶ�
//}
///*
//����:��ȡ������������Ԫ������
//���������
//EEPROM_Address:������ַ
//Address:�洢��Ԫ��ַ(24c02:0~255)
//_data:����ȡ����������ָ��ĵ�ַ(���ݿ��:8bit)
//bnum:�ӵ�Ԫ��ַ��ʼ�Ķ�ȡ�����ݵĸ���
//����ֵ����
//*/
//void IIC_ReadData(uchar EEPROM_Address,uchar Address,uchar *_data,uchar bnum)
//{
//	uchar i = 0;
//	I2C_start();
//	I2C_wbyte(EEPROM_Address); //�ӻ���ַ  ��������
//	I2C_ASK();
//	I2C_wbyte(Address);//�ӻ��洢��Ԫ��ַ
//	I2C_ASK();

//	for(i = 0;i<bnum;i++,_data++)
//	{
//	I2C_start();//α�������������ݴ��䷽��
//	I2C_wbyte(EEPROM_Address+1);	//�ӻ���ַ  ��������
//	I2C_ASK();
//	*_data=I2C_rbyte();
//	I2C_notASK();//����Ӧ��
//	}
//    I2C_stop();
//}

