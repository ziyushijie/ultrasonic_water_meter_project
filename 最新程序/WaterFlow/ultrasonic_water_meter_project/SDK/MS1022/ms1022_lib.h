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

// 参考电阻值为标称值，因此存在静态误差
#ifndef MS1022_CH3_REF_RES_1000
#define MS1022_CH3_REF_RES_1000   1000u   // 通道3参考电阻 1K欧姆
#endif

#ifndef MS1022_CH4_REF_RES_1400  
#define MS1022_CH4_REF_RES_1400   1400u   // 通道4参考电阻 1.4K欧姆
#endif

// 我的采样原则，高采样率快速采样，最后再计算。【采样次数越多计算越缓慢】
#define TEMP_SAMP_NUM     6u     // 温度采样次数设置，做算术平均滤波


// 测量次数必须大于4次，通常需要大于6次
#define FLOW_SAMP_NUM     40u     // 流量采样次数设置；实际这里至少不能低于4次，一般10次的样子
// 此值的2倍必须略小于总采样次数
#define DEL_ARRAY_NUM     (FLOW_SAMP_NUM / 4u)    // 流量采样值要掐头去尾的个数
// 错误配置检测
#if ((DEL_ARRAY_NUM + DEL_ARRAY_NUM + 2) > FLOW_SAMP_NUM)
#error "配置错误[MS1022_lib.h]：宏参数 DEL_ARRAY_NUM 的掐头去尾配置参数不正确！"
#endif



/***********************【 温度传感器状态和故障-ORG 】 *******************************/
// 在 extern __Get_Temperature  Get_TEMP; 中读取
// 使用方法： Get_TEMP.PT1000_STATE.内容
// 测量状态
#define MS1022_TempMeasure_OK        0u   // 温度测量成功
#define MS1022_TempMeasure_Fail      1u   // 温度测量失败！[超时]

// 温度传感器状态:只能被 PT1000_STATE 结构体调用。
#define MS1022_Temp_Normal  		 1u   // 温度传感器正常
#define MS1022_Temp_Open    		 2u   // 温度传感器开路故障
#define MS1022_Temp_Short   		 3u   // 温度传感器短路故障


/********************************【 END 】 ****************************************/

typedef struct __get_temperature__   // 缓冲温度测量结果
{
	
	float Temperature_In;  // 进口温度【RED】
	float Temperature_Out; // 出口温度【BLUE】
	float Temperature_Diff;// 温度差 = 出水温度 - 进水温度
	struct __PT1000_Measure_State__
	{
		unsigned char PT1000_Red_In : 3; // 进口温度传感器短路或断路状态
		unsigned char PT1000_BLUE_Out : 3; // 出口温度传感器短路或断路状态
		unsigned char PT1000_MeasureSTA : 2; // 测量是否成功？
		
	}PT1000_STATE;  // PT1000温度传感器状态
	
}__Get_Temperature; // 调用 Get_Temperature() 函数之后才能有效使用

extern __Get_Temperature  Get_TEMP; // 保存温度值[Read,用户调用温度测量函数后才能读取]


typedef struct __get_time__
{
	
	double Forward_Time; // 正向飞行时间@us
	double Reverse_Time; // 反向飞行时间@us
	
//  /-------------------------------\
//	| Time_Diff > 0 | Time_Diff < 0 |
//	|---------------|---------------|
//	|  正向（us）		|	反向（us)	|
//	\-------------------------------/

	double Time_Diff;    // 正反向飞行时间差@us
	
	unsigned int flow_status; // 流量测量的状态值
	
}__Get_Time; // 超声波相关测量参数

extern __Get_Time	 Get_Time;   // 时间相关参数

typedef struct __get_flow_heat__
{
	
	double flow_speed;  // 流速=立方米/小时
	double flow_sum;    // 累积流量=立方米
	double current_heat;// 当前热量
	float  sum_heat;    // 累积热量
	
}__Get_FlowHeat;// 超声波流量相关参数.........

extern __Get_FlowHeat  Get_FlowHeat;

// 热量相关参数........



/*------------------------------------------------------------
*********** 说明 **********************************************
* 主设备端口配置情况：
* RSTN:低电平复位信号：P14 [配置输出]
* SSN :片选信号（低电平有效）：P15 [配置输出]
* SCK:主从设备同步时钟信号：P16 [配置输出]
* SO(MISO):主机输入从机输出：P17 [配置输入]
* SI(MOSI):主机输出从机输入：P00 [配置输出]
*
* ACLK:32KHZ时钟输出：P07 [配置输出]---------应该配置为输入：尚未修正
* INT:MS1022中断输出管脚：P02  [MCU对应中断线路输入：INT7]-低电平有效
-------------------------------------------------------------*/
//-------------------------------------- MS1022相关传感器的故障或错误值标识 -----------------




// 换能器故障信息提示

/*============================ 管脚定义 ======================================================================*/

#define OUT_MS1022_RSTN      GPIO(1,4) //P1_bit.no4    // 复位信号
#define OUT_MS1022_SSN       GPIO(1,5) //P1_bit.no5    // 片选信号
//#define OUT_MS1022_SCK     P1_bit.no6    // 同步时钟信号
//#define OUT_MS1022_MOSI    P0_bit.no0    // 主机输出
//#define IN_MS1022_MISO     P1_bit.no7    // 主机输入

//#define OUT_MS1022_ACLK      GPIO(0,7)// P0_bit.no7    // 模拟模式时32KHZ时钟---------应该配置为输入
//#define IN_MS1022_INT      P0_bit.no2    // 中断查询管脚【器件中断信号】

///*===================== [ 操作命令 ] ======================================================================*/

#define WRITE_BasicAddr      0x80      // 写入地址的基地址[24bit、32bit]
#define READ_BasicAddr       0xB0      // 读入地址的基地址[8bit、16bit、32bit]

#define READ_ID              0xB7      // 读取ID [56位ID]

									   // 这个寄存器是一个 8 位的固定浮点数寄存器，其中 1 位为整数，而 7 位为小数。
#define READ_PW1ST           0xB8      // 脉冲宽度的测量比值,固定浮点数，其中 1 位为整数- (读出为8位)

#define CFGReg_To_EEPROM     0xC0      // 写配置寄存器到 EEPROM
#define EEPROM_To_CFGReg     0xF0      // 将 EEPROM 内容传回配置寄存器中
#define EEPROM_and_Reg_SJMP  0xC6 	   // 将 EEPROM 和配置寄存器内容进行比较
#define MS1022_INIT          0x70      // 初始化
#define POWER_On_Reset       0x50      // 上电复位

#define RES_0				 0XB0      // 读测量结果 1,固定浮点数，16 位整数部分，16 位小数部分【32bit】
#define RES_1				 0XB1      // 读测量结果 2,固定浮点数，16 位整数部分，16 位小数部分【32bit】
#define RES_2				 0XB2      // 读测量结果 3,固定浮点数，16 位整数部分，16 位小数部分【32bit】
#define RES_3				 0XB3      // 读测量结果 4,固定浮点数，16 位整数部分，16 位小数部分【32bit】

#define STAT                 0XB4      // 状态寄存器【16bit】

#define REG_1                0XB5      // 显示写寄存器 1 中的高 8 位,用来测试通信【8bit】

/*--- 以下几条操作命令详见手册第26页描述 [ORG]---------------------------------------------------------------------------------*/
#define START_TOF            0x01      // 触发一次时间测量
#define START_TEMP           0x02      // 将会触发一次温度测量
#define START_Cal_Resonator  0x03      // 将会触发一次对于高速晶振的校准测量
#define START_Cal_TDC        0x04      // 这个命令将会启动测量２个参考时钟周期
#define START_TOF_Restart    0x05      // 这个新的操作码将运行 Start_TOF 两次,分别在热量表的上游时间测量和下游时间测量各一次
#define START_TEMP_Restart   0x06      // 这个操作码将会运行温度测量 Start_Temp 两次
/*---------------------  [END] ----------------------------------------------------------------------------------------*/

//********** 状态命令比较标志 *******************************************************
// 配合状态寄存器读取的值使用即可[下列标识的是‘1’所在状态寄存器中的位置]
#define EEPROM_eq_CREG      0x8000     // 显示配置寄存器中的内容是否与 EEPROM 中相同; 1 = 相同
#define EEPROM_DED          0x4000     // 多次错误检查.在 EEPROM 中有 2 处不能够纠正的错误产生; 1 = 2 处错误
#define EEPROM_Error        0x2000     // 在 EEPROM 中有一个错误并且被纠正; 1 = 错误
#define Error_short         0x1000     // 显示测量温度传感器为短路 ;1 = 短路
#define Error_open          0x0800     // 显示测量温度传感器为断路; 1 = 开路
#define Timeout_Precounter  0x0400     // 显示测量范围 2 中 14 位粗值计数器的溢出; 1 = 溢出
#define Timeout_TDC         0x0200     // 显示 TDC 测量单元溢出; 1 = 溢出

#define of_hits_Ch_2        0x01C0     // 显示在 channel 2 记录下的第几次脉冲数
#define of_hits_Ch_1        0x0038     // 显示在 channel 1 记录下的第几次脉冲数

#define Pointer_result_register 0x0003 // 指针指向下一个空结果寄存器地址

// 获取状态
#define get_EEPROM_eq_CREG 	    (MS1022_Read_STAT() & EEPROM_eq_CREG)
#define get_EEPROM_DED    	    (MS1022_Read_STAT() & EEPROM_DED)
#define get_EEPROM_Error        (MS1022_Read_STAT() & EEPROM_Error)
#define get_Error_short         (MS1022_Read_STAT() & Error_short)
#define get_Error_open		    (MS1022_Read_STAT() & Error_open)
#define get_Timeout_Precounter  (MS1022_Read_STAT() & Timeout_Precounter)
#define get_Timeout_TDC  		(MS1022_Read_STAT() & Timeout_TDC)

// 显示在 channel 1,2 记录下的第几次脉冲数   0000 0001 1100 0000
#define get_of_hits_Ch_1        ((MS1022_Read_STAT() & of_hits_Ch_1) >> 6u)
#define get_of_hits_Ch_2        ((MS1022_Read_STAT() & of_hits_Ch_2) >> 6u)

// 获取指针指向下一个空结果寄存器地址
#define get_Point_res_reg		(MS1022_Read_STAT() & Pointer_result_register)

/*---------------------  [END] ----------------------------------------------------------------------------------------*/


void MS1022_Delay_us(unsigned int Xus); // us级延时

void HanderSPI_Interface_Init(void);// 初始化硬件SPI接口

void RubbleSort(float array[],unsigned char len); // 冒泡算法-小数
void ULong_RubbleSort(unsigned long *Array,unsigned char Len); //冒泡- 整数

// 算术平均滤波
unsigned long tab_long_average(unsigned long* indata,unsigned char len);// 整数平均值
float tab_float_average(float* input_value,unsigned char len);// 浮点平均值

/*############################### 【ORG】################################################################*/
// array:数组，variable:变量，len:数组长度，del_array：要掐头去尾的个数,average_output:输出值
#define ARRAY_AVERAGE(array,variable,len,del_array_len,average_output)  do{				\
																						\
average_output = 0u;	 																\
FOREACH(variable,0u + del_array_len,len - del_array_len,1u)ORG	 						\
average_output += array[variable];    						    					    \
END								     						     						\
average_output /= (double)(len - del_array_len - del_array_len); 					    \
}while(0u)
/*################################ 【END】##############################################################*/

void MS1022_RESET(void); // 复位

void MS1022_SPI_ENABLE(void); // 使能片选
void MS1022_SPI_DISABLE(void); // 失能片选

void MS1022_Init(void); // 初始化器件
void MS1022_Read_ID(unsigned char *buff_x); // 读ID[56bit = 7byte * 8bit]

void SPI_MS1022_Write(unsigned char W_Data); // 写字节
unsigned char SPI_MS1022_Read(void); // 读字节

void SPI_MS1022_Write4Byte(unsigned long W_Data); // SPI写32位数据
unsigned long SPI_MS1022_Read4Byte(void); // SPI读32位数据

void MS1022_Write_Reg(unsigned char RegNum,unsigned long RegData); // 写寄存器[32bit]
unsigned long MS1022_Read_Reg(unsigned char RegNum); // 读寄存器[32bit]

void MS1022_Transfer_Ask(unsigned char MS1022_OPCODE,unsigned char *buff_x,unsigned char LengthByte);// 
void MS1022_Transfer_Data(unsigned char *Rec_Data,unsigned char Length); // 向MS1022发送缓冲数据

void SET_CMD(unsigned char Cmd_1Byte);// 设置命令

// 等待测量完成中断
/*################################## 等待测量中断【ORG】####################################*/
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
/*################################## 等待测量中断【END】####################################*/

/*--------------------------- 快捷操作命令 ------------------------------*/

//#define SPI_SET_Idle()  OUT_MS1022_MOSI = OUT_MS1022_SCK = 0   // 设置总线空闲状态---和SPI_Init()的功能一样
 
#define CMD_INIT() 		SPI_MS1022_Write(MS1022_INIT) // 初始化命令
#define CMD_TOF()  		SPI_MS1022_Write(START_TOF)   // 触发一次时间测量
//#define CMD_TOF_TOW() 	SPI_MS1022_Write(START_TOF_Restart)  // 触发上游下游各自测量一次

//#define ACLK_ON() OUT_MS1022_ACLK = 1   // 开启ACLK管脚
//#define ACLK_OFF() OUT_MS1022_ACLK = 0   // 关闭ACLK管脚

// 此操作可以降低功耗
#define  ON_MS1022_FOSC() MS1022_Write_Reg(0,0xF347E810)  // 开启晶振并配置参数
#define OFF_MS1022_FOSC() MS1022_Write_Reg(0,0x0303e810) // 关闭晶振

#define UP_MODE() 		MS1022_Write_Reg(5,0x30000005)  // 开启上游
#define DOWN_MODE() 	MS1022_Write_Reg(5,0x50000005)  // 开启下游
//#define UP_DOWN_MODE()  MS1022_Write_Reg(5,0x90000005)  // 两个都开启

#define MS1022_Power_On_Reset() SPI_MS1022_Write(POWER_On_Reset) // 上电复位

#define Start_Temp() MS1022_Transfer_Ask(START_TEMP,0u,0u)  // 启动一次温度测量

/*------------------------ 用户功能函数 ------------------------------------*/

unsigned char MS1022_Read_REG_1(void); // 读写寄存器 1 中的高 8 位,用来测试通信
unsigned char MS1022_Read_PWM1ST(void); // PW1ST
unsigned int  MS1022_Read_STAT(void); // 读状态寄存器
unsigned long MS1022_Timecheck(void); // 时钟校验
double Get_CLK_ref(void); // 获取时钟因子

void Get_Temperature(void); //温度测量
void Get_Flow(void);		// 读取流量

extern unsigned int MS1022_STA_REG; // 状态寄存器值【执行测量后生效】

	
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* MS1022_LIB_H_ */