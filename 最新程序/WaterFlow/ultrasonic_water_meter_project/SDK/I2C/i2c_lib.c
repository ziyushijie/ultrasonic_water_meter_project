#include "i2c_lib.h"


////兼容C51的延时程序(1us/5us)
//void Delay(bit IF_Delay)
//{
//}

//void I2C_start(void)  //开始信号
//{	
//	sda=1; 
//	scl=1;
//	Delay(Delay_5us);
//	sda=0;
//	Delay(Delay_5us);
//	scl=0;	
//	Delay(Delay_1us);
//}

//void I2C_stop()   //停止
//{	
//	scl=0;
//	sda=0;
//Delay(Delay_5us);
//	scl=1;
//Delay(Delay_5us);
//	sda=1;
//Delay(Delay_1us);
//}

//void I2C_ASK()  //应答
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

//void I2C_notASK()//非应答
//{
//	sda=1;
//	Delay(Delay_5us);
//	Delay(Delay_5us);
//	scl=1;
//	Delay(Delay_5us);
//	Delay(Delay_5us);
//	scl=0;	
//}

//void I2C_wbyte(uchar date)	  //写一个字节
//{
//	uchar i,temp;
//	temp=date;
//	for(i=0;i<8;i++)
//	{
//		temp=temp<<1;
//		scl=0;
//		sda=CY;
//		Delay(Delay_5us);//延时大于4.7us ，让数据变化
//		scl=1;
//		Delay(Delay_5us);//延时大于4.7us ，让数据传送

//	}
//	scl=0;
//	Delay(Delay_1us);
//}

//uchar I2C_rbyte()	  //读一个字节
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
//功能:存储单个数据(写数据)
//EEPROM_Address:器件地址
//Address:存储单元地址
//_data:数据
//*/
//void WriteData(uchar EEPROM_Address,uchar Address,uchar _data)
//{
//	I2C_start();
//	I2C_wbyte(EEPROM_Address+0);//器件地址
//	I2C_ASK();//谁收谁答
//	I2C_wbyte(Address);//从机子地址
//	I2C_ASK();		
//	I2C_wbyte(_data);
//	I2C_ASK();
//	I2C_stop();
//	delay2(20);//数据稳定 (这个延时很重要 >= 3ms)
//}
///*
//功能:读取单个单元中数据
//输入参数：
//EEPROM_Address:器件地址
//Address:存储单元地址(24c02:0~255)
//返回值：从单元读取到的数据
//*/
//uchar ReadData(uchar EEPROM_Address,uchar Address)
//{
//	uchar _data = 0;
//	I2C_start();
//	I2C_wbyte(EEPROM_Address+0); //从器件地址  主机发送
//	I2C_ASK();//应答位
//	I2C_wbyte(Address);//从机存储单元地址
//	I2C_ASK();//应答位
//	I2C_start();//伪启动，更改数据传输方向
//	I2C_wbyte(EEPROM_Address+1);	//从机地址  主机接收
//	I2C_ASK();//应答位
//	_data=I2C_rbyte();//读取数据
//	I2C_notASK();//主机应答
//	I2C_stop();
//	return _data;
//}
///*
//功能:将数据连续或单个存储到EEPROM单元地址中
//输入参数：
//EEPROM_Address:器件地址
//Address:存储单元地址(24c02:0~255)
//_data:被存储的数据所指向的地址(数据宽度:8bit)
//bnum:从单元地址开始的存储数据的个数
//返回值：无
//*/
//void IIC_WriteData(uchar EEPROM_Address,uchar Address,uchar *_data,uchar bnum)
//{
//	uchar i = 0;
//	I2C_start();
//	I2C_wbyte(EEPROM_Address);
//	I2C_ASK();//谁收谁答
//   	I2C_wbyte(Address);//从机子地址
//	I2C_ASK();	
//	for(i = 0;i<bnum;i++,_data++)
//	{	
//	I2C_wbyte(*_data);
//	I2C_ASK();
//	}
//	I2C_stop();
//   delay2(20);//数据稳定
//}
///*
//功能:读取单个或连续单元中数据
//输入参数：
//EEPROM_Address:器件地址
//Address:存储单元地址(24c02:0~255)
//_data:被读取到的数据所指向的地址(数据宽度:8bit)
//bnum:从单元地址开始的读取的数据的个数
//返回值：无
//*/
//void IIC_ReadData(uchar EEPROM_Address,uchar Address,uchar *_data,uchar bnum)
//{
//	uchar i = 0;
//	I2C_start();
//	I2C_wbyte(EEPROM_Address); //从机地址  主机发送
//	I2C_ASK();
//	I2C_wbyte(Address);//从机存储单元地址
//	I2C_ASK();

//	for(i = 0;i<bnum;i++,_data++)
//	{
//	I2C_start();//伪启动，更改数据传输方向
//	I2C_wbyte(EEPROM_Address+1);	//从机地址  主机接收
//	I2C_ASK();
//	*_data=I2C_rbyte();
//	I2C_notASK();//主机应答
//	}
//    I2C_stop();
//}

