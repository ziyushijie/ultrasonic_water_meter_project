#ifndef AT24CXX_LIB_H_
#define AT24CXX_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////

///*---------------------------------------------
//硬件IIC接口
//---------------------------------------------*/

//#include "r_cg_iica.h"

//#define u8 unsigned char
//#define s8 signed char
//#define u16 unsigned int
////#define s16 signed int
////#define u32 unsigned long
////#define s32 signed long


//typedef union AT24C16_DATA_CONVERT
//{
//	unsigned char To8Byte[8];
//	long int ToLInt; // 占用8字节
//}__CONVERT__;



//#define AT24Cxx_Address  0xA0    // 器件地址

//// AT24C16: 1024 * 16KB / 8bit = 2048(Byte);[地址空间]

//void AT24C16_Init(void);


//// 因为首地址的是内容是AT24Cxx的物理内存地址，所以数组的空间要大一个字节
//void AT24C16_SendData(u16 StartAddr,u8 *const Data,u8 Length); // 发送数据-保存【数据首地址下面的值为起始地址】
//void AT24C16_ReadData(u16 StartAddr,u8 *const Data,u8 Length); // 读取数据

//void Write_IntData(short int StartAddr,long int SaveData); // 保存长整形数据
//long int Read_IntData(short int StartAddr); // 读取长整形数据



	
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* AT24CXX_LIB_H_ */