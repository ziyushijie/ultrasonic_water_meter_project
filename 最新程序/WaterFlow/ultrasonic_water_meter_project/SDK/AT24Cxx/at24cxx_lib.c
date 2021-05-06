
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
//* 函数名称：AT24C16_SendData
//* 函数说明：连续写入字节数据
//* 函数输入：StartAddr：起始地址
//		  Data：要存储的数据指针
//		  Length：要写入的数据长度
//* 函数输出：无
//* 函数解释：无
//-------------------------------------------------------------*/
//void AT24C16_SendData(u16 StartAddr,u8 *const Data,u8 Length)
//{
//	u8 ADDR_H = (u8)(StartAddr >> 8); // 得到高8位地址
//	u8 ADDR_L = (u8)StartAddr; // 得到低8位地址
	
//	u8 *p = (u8*)malloc(Length+1);  // 创建动态缓冲区
//	short int i = 0;
	
//	for(i = 1;i <= Length+1; i++) // 拷贝数据
//	{
//		*(p+i) = Data[i-1];
//	}
//	p[0] = ADDR_L;  // 首字节存储器件低8位的物理地址
	
//	R_IICA0_Master_Send(AT24Cxx_Address + (ADDR_H << 1),p,Length,200);// while内部函数空等待200次
//	AT24C16_Delay(8000); // 写数据，此延时必须大于6ms
//	free(p);  // 释放动态数组空间
//}


///*------------------------------------------------------------
//* 函数名称：AT24C16_ReadData
//* 函数说明：连续读出字节数据
//* 函数输入：StartAddr：起始地址
//		  Data：读出数据由此映射出去
//		  Length：要读取的数据长度
//* 函数输出：无
//* 函数解释：无
//-------------------------------------------------------------*/
//void AT24C16_ReadData(u16 StartAddr,u8 *const Data,u8 Length) // 读取数据
//{
//	u8 ADDR_H = (u8)(StartAddr >> 8); // 得到高8位地址
//	u8 ADDR_L = (u8)StartAddr; // 得到低8位地址
	
//	R_IICA0_Master_Send(AT24Cxx_Address + (ADDR_H << 1),&ADDR_L,1,200); // 要读取的开始单元地址
//	AT24C16_Delay(500); // 必须的延时
//	R_IICA0_Master_Receive(AT24Cxx_Address,Data,Length,200); // 读数据
//	AT24C16_Delay(500); // 必须的延时
//}


///*------------------------------------------------------------
//* 函数名称：Write_IntData
//* 函数说明：保存长整形数据
//* 函数输入：StartAddr：起始地址
//		  SaveData：要保存的数据
//* 函数输出：无
//* 函数解释：无
//-------------------------------------------------------------*/
//void Write_IntData(short int StartAddr,long int SaveData)
//{
//	CONVERT.ToLInt = SaveData;
//	AT24C16_SendData(StartAddr,CONVERT.To8Byte,8u); // save's data
//}

///*------------------------------------------------------------
//* 函数名称：Read_IntData
//* 函数说明：读取长整形数据
//* 函数输入：StartAddr：起始地址
//* 函数输出：读出的长整形数据
//* 函数解释：无
//-------------------------------------------------------------*/
//long int Read_IntData(short int StartAddr)
//{
//	AT24C16_ReadData(StartAddr,CONVERT.To8Byte,8u); // read data
//	return CONVERT.ToLInt;
//}
