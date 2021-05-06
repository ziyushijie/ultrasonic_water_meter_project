#include "ms1022_lib.h"
#include "delay_lib.h"
#include "r_cg_intp.h"
#include "math.h"
#include "r_cg_pclbuz.h"

extern _Bool MS1022_Interrupt_FLAG; // MS1022中断标志【中断为1】
extern _Bool SPI_BUSY_RX; // SPI接收完成标志【中断为0】
extern _Bool SPI_BUSY_TX; // SPI发送完成标志【中断为0】

unsigned int MS1022_STA_REG = 0x0000; // 缓冲状态寄存器值【一般内部程序读取使用】

__Get_Temperature  Get_TEMP; // 保存温度值
__Get_Time	 Get_Time;   // 时间相关参数
__Get_FlowHeat  Get_FlowHeat;	 // 流量热量相关参数

static float Count_Temper_Rt(float input_PoRes); // 通过阻值计算摄氏度

// 初始化硬件SPI接口
void HanderSPI_Interface_Init(void){
	
	//R_SAU0_Create(); // 创建接口
	R_CSI00_Start(); // 启动
	
	// 32.768KHZ输出----ACLK
	R_PCLBUZ0_Create();
	R_PCLBUZ0_Start();

	R_INTC_Create();
    R_INTC7_Start();  // MS1022中断管脚启动
	
}


/*-----------------------------------------------------------------
* 函数名称：MS1022_Delay_us
* 函数说明：MS1022器件使用的精确延时
* 函数输入：Xus延时时间；取值范围:[1,65535]且只能是10的整数倍
* 函数输出：无
* 函数解释：直接使用 SET_Delay_us 函数原型会更准确，因为函数也会有执行时间。
-----------------------------------------------------------------*/
void MS1022_Delay_us(unsigned int Xus)
{
	
	unsigned int Temp_delay = Xus / 10; // 换算延时时间
	SET_Delay_us(Temp_delay);
	
}

/*------------------------------------------------------------
* 函数名称：MS1022_RESET
* 函数说明：MS1022器件复位
* 函数输出：无
* 函数解释：系统上电复位必须拉低500us
-------------------------------------------------------------*/
void MS1022_RESET(void)
{

	OUT_MS1022_RSTN = 0;
	MS1022_Delay_us(100); 
	OUT_MS1022_RSTN = 1;
	
	MS1022_Delay_us(600); // >500us
}

/*------------------------------------------------------------
* 函数名称：MS1022_SPI_ENABLE
* 函数说明：MS1022的SPI通讯开启
* 函数输出：无
* 函数解释：使能片选
-------------------------------------------------------------*/
void MS1022_SPI_ENABLE(void)
{
	NOP();NOP();NOP();NOP();NOP();
	OUT_MS1022_SSN = 0u;
	NOP();NOP();NOP();NOP();NOP();
}

/*------------------------------------------------------------
* 函数名称：MS1022_SPI_DISABLE
* 函数说明：MS1022的SPI通讯关闭：0-1-0
* 函数输出：无
* 函数解释：失能片选
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
* 函数名称：SPI_MS1022_Write
* 函数说明：SPI写字节
* 函数输入：W_Data 要写入的数据
* 函数输出：无
* 函数解释：数据从高位开始发送
-------------------------------------------------------------*/
void SPI_MS1022_Write(unsigned char W_Data)
{
	unsigned char temp_data = W_Data;
	
	SPI_BUSY_TX = 1;
	
	R_CSI00_Send_Receive(&temp_data,1u,0u); // 发送1byte数据
	
	while(SPI_BUSY_TX); // 等待发送完成
}


/*------------------------------------------------------------
* 函数名称：SPI_MS1022_Read
* 函数说明：SPI读字节
* 函数输入：无
* 函数输出：读取的一字节数据
* 函数解释：数据从高位开始接收
-------------------------------------------------------------*/
unsigned char SPI_MS1022_Read(void)
{

	unsigned char Temp_Data = 0x00;

	SPI_BUSY_RX = SPI_BUSY_TX = 1; 
	
	R_CSI00_Send_Receive(0u,1u,&Temp_Data); // 接收1byte数据
	
	//while(SPI_BUSY_RX || SPI_BUSY_TX); // 等待接收完成
	while(SPI_BUSY_RX); // 等待接收完成
	
	return Temp_Data;
	
}


/*------------------------------------------------------------
* 函数名称：SPI_MS1022_Write4Byte
* 函数说明：SPI写4字节
* 函数输入：W_Data 要写入的数据
* 函数输出：无
* 函数解释：数据从高位开始发送
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
* 函数名称：SPI_MS1022_Read4Byte
* 函数说明：SPI读字节
* 函数输入：无
* 函数输出：读取的一字节数据
* 函数解释：数据从高位开始接收
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
* 函数名称：MS1022_Init
* 函数说明：MS1022器件初始化
* 函数输入：RegNum 寄存器号：0、1~7；RegData 往寄存器内写的数据
		  RegData32位数据
* 函数输出：无
* 函数解释：无
* 函数功能：写寄存器
-------------------------------------------------------------*/
void MS1022_Write_Reg(unsigned char RegNum,unsigned long RegData)
{
	
	MS1022_SPI_ENABLE();  // 使能片选
	
	SPI_MS1022_Write(WRITE_BasicAddr | RegNum);  // 目标寄存器 [ 在基地址上累加选择寄存器 ]
	SPI_MS1022_Write4Byte(RegData); // 寄存器数据
	
	MS1022_SPI_DISABLE(); // 失能片选
}

/*------------------------------------------------------------
* 函数名称：Read_Reg
* 函数输入：RegNum 寄存器号 0-7
		  ReadData 寄存器数据
* 函数输出：无
* 函数解释：无
* 函数功能：读寄存器
-------------------------------------------------------------*/
unsigned long MS1022_Read_Reg(unsigned char RegNum)
{
    unsigned long ReadData = 0;
	
	MS1022_SPI_ENABLE();
	
	SPI_MS1022_Write(READ_BasicAddr | RegNum); // 在基地址上累加选择寄存器
	ReadData = SPI_MS1022_Read4Byte();
	
	MS1022_SPI_DISABLE();
	
	return ReadData;
}

/*------------------------------------------------------------
* 函数名称：MS1022_Transfer
* 函数说明：向MS1022发送操作命令
* 函数输入：MS1022_OPCODE : 操作码
*         LengthByte ： 读取数据字节长度
* 函数输出：buff_x 读数据缓冲区
* 函数解释：如果只发操作码时，除了操作码的参数以外的其他参数全部设为0
-------------------------------------------------------------*/
void MS1022_Transfer_Ask(unsigned char MS1022_OPCODE,unsigned char *buff_x,unsigned char LengthByte)
{
	
	unsigned char i;
	
	MS1022_SPI_ENABLE(); // 片选
	
	SPI_MS1022_Write(MS1022_OPCODE); // 发送操作码
	
	if(0u != LengthByte)  // 如果 LengthByte = 0 表示只是单纯的发送操作码，并不读取数据
	for(i = 0; i < LengthByte;i++){
		*buff_x++ = SPI_MS1022_Read();
	}
	
	MS1022_SPI_DISABLE(); // 关闭片选 
}

/*----------------------------------------------------------------------
* 函数名称：MS1022_Transfer_Data
* 函数说明：向MS1022发送数据缓存内的 Length 个字节数据(用于配置MS1022的内部寄存器)
* 函数输入：MS1022_OPCODE : 操作码
*         LengthByte ： 发送数据字节长度
* 函数输出：buff_x 发送数据缓冲区
* 函数解释： 
-----------------------------------------------------------------------*/
void MS1022_Transfer_Data(unsigned char *Rec_Data,unsigned char Length)
{
	
	unsigned char i = 0;
	MS1022_SPI_ENABLE(); // 片选
	
	for(i = 0;i < Length; i++){
	SPI_MS1022_Write(*(Rec_Data + i));
	}
	
	MS1022_SPI_DISABLE(); // 关闭片选 
	
}

/*--------------------------------------------------------------------
// 函数功能：读取器件ID
// 函数名称：MS1022_Read_ID
// 函数输入：无
// 函数输出：7个字节的器件ID
// 函数解释：读取器件ID[56bit = 7byte * 8bit]
// 			实质是读取7个寄存器的最后8位的区域，EEPROM区域。
---------------------------------------------------------------------*/
void MS1022_Read_ID(unsigned char *buff_x)
{
	MS1022_Transfer_Ask(READ_ID,buff_x,7u); // 操作读取ID
}

/*--------------------------------------------------------------------
// 函数功能：显示写寄存器 1 中的高 8 位,用来测试通信
// 函数名称：MS1022_Read_REG_1
// 函数输入：无
// 函数输出：1个字节
// 函数解释：用来测试通信;见手册22页：2.读寄存器
---------------------------------------------------------------------*/
unsigned char MS1022_Read_REG_1(void)
{
	unsigned char temp = 0x00;
	
	MS1022_SPI_ENABLE(); // 片选
	MS1022_Delay_us(20); // 20us
	
	SPI_MS1022_Write(REG_1); // 测试通讯的ask
	temp = SPI_MS1022_Read();
	
	MS1022_Delay_us(20); // 20us
	MS1022_SPI_DISABLE(); // 失能片选
	
	return temp;
	
}

/*--------------------------------------------------------------------
// 函数功能：脉冲宽度的测量比值,固定浮点数，其中 1 位为整数
// 函数名称：MS1022_Read_PWM1ST
// 函数输入：无
// 函数输出：1个字节
// 函数解释：用来测试通信;见手册22页：2.读寄存器
---------------------------------------------------------------------*/
unsigned char MS1022_Read_PWM1ST(void)
{
	unsigned char temp = 0x00;
	
	MS1022_SPI_ENABLE(); // 片选
	MS1022_Delay_us(20); // 20us
	
	SPI_MS1022_Write(READ_PW1ST); // PW1ST ask
	temp = SPI_MS1022_Read();
	
	MS1022_Delay_us(20); // 20us
	MS1022_SPI_DISABLE(); // 失能片选
	
	return temp;
}


/*--------------------------------------------------------------------
// 函数功能：读状态寄存器
// 函数名称：MS1022_Read_STAT
// 函数输入：无
// 函数输出：16bit,高位在前: res_state 
// 函数解释：用来测试通信;见手册22页：2.读寄存器
---------------------------------------------------------------------*/
unsigned int MS1022_Read_STAT(void)
{
	unsigned int res_state = 0x0000;
	
	MS1022_SPI_ENABLE(); // 片选
	
	SPI_MS1022_Write(STAT); // STAT ask
	
	res_state = SPI_MS1022_Read();
	res_state = (res_state << 8) | SPI_MS1022_Read();
	
	MS1022_SPI_DISABLE(); // 失能片选 
	
	return res_state;
	
}



///*--------------------------------------------------------------------
//// 函数功能：获取高速时钟校正因子
//// 函数名称：MS1022_Read_ID
//// 函数输入：无
//// 函数输出：7个字节的器件ID
//// 函数解释：读取器件ID[56bit = 7byte * 8bit]
//// 			实质是读取7个寄存器的最后8位的区域，EEPROM区域。
//---------------------------------------------------------------------*/
//unsigned char Get_CLK_x(float *g_factor_value)                              
//{
//    unsigned char ret = 0;
//    unsigned long factor_unit;    
//	unsigned char SPI_Buf[4] = { 0 };
	
	
//	MS1022_Transfer_Ask(MS1022_INIT, NULL, 0);         //TDC_GP22快速初始化  
//    MS1022_Transfer_Ask(START_Cal_Resonator, NULL, 0); //启动高速晶振校准测量

//    MS1022_Transfer_Ask(READ_BasicAddr, SPI_Buf, 4);           //读GP22结果寄存器0(高速晶振校准测量结果)32bit数据到SPI_Buf/高位在第一位

//	factor_unit = SPI_Buf[0];
//    factor_unit = (factor_unit << 8) | SPI_Buf[1];
//    factor_unit = (factor_unit << 8) | SPI_Buf[2];
//    factor_unit = (factor_unit << 8) | SPI_Buf[3];
	
//    *g_factor_value = (float)(factor_unit)/65536;          //16位整数位16小数位
//    *g_factor_value = 244.140625 / (*g_factor_value * 0.25);   //计算高速晶振校正系数(8个脉冲的32768HZ的校正系数)
	
//    return ret;
//}


/*------------------------------------------------------------
* 函数名称：MS1022_Init
* 函数说明：MS1022器件初始化
* 函数输入：无
* 函数输出：无
* 函数解释：无
-------------------------------------------------------------*/
void MS1022_Init(void)
{
//	DBG_SendString("MS1022进入初始化，请稍等...\r\n");
//	HanderSPI_Interface_Init();  // 硬件接口相关初始化
	
	MS1022_RESET(); // 芯片系统复位
	MS1022_SPI_ENABLE(); // 片选
	
	// 1-初始化配置-（估计）
	SPI_MS1022_Write(POWER_On_Reset);  // 上电复位
	
	MS1022_Delay_us(800);//700us等待数据稳定
	MS1022_Read_STAT();
	MS1022_Write_Reg(0,0xF347E810);                 //配置MS1022配置寄存器0 
	MS1022_Write_Reg(1,0x21444012);                 //配置MS1022配置寄存器1
	MS1022_Write_Reg(6,0xCEC06006);                 //配置MS1022配置寄存器6【模拟模式】
	//MS1022_Write_Reg(6,0x4EC06006);                 //配置MS1022配置寄存器6【数字模式】

    // 3-测流量配置（估计）
	MS1022_Write_Reg(2,0xA01F14A0);                 //配置MS1022配置寄存器2
	MS1022_Write_Reg(3,0x08000000);                 //配置MS1022配置寄存器3
	MS1022_Write_Reg(4,0x20000000);                 //配置MS1022配置寄存器4
	MS1022_Write_Reg(5,0x50000005);       	      	//配置MS1022配置寄存器5【下游模式】
	
	// 假测量
	Get_Temperature();
	Get_Flow();
	
	MS1022_SPI_DISABLE(); // 关闭片选
	
}


	/*------------------------------------------------------------
* 函数名称：Get_Temperature
* 函数说明：计算PT1000两个通道的温度值
* 函数输入：无
* 函数输出：PT1000传感器工作状态和测量情况
* 函数解释：无
-------------------------------------------------------------*/
void Get_Temperature(void) //温度测量
{
	unsigned int err_time = 0L; // 超时时间 , 测量状态
	unsigned char SamplingNum; // 采样次数
	unsigned long temper_val[4] = { 0.0f };  // 缓冲读取的温度值

	float temper_red[TEMP_SAMP_NUM] = { 0.0f };// N次采样的温度值-red
	float temper_blue[TEMP_SAMP_NUM] = { 0.0f };// N次采样的温度值-blue	
	float temper_temp = 0.0f; 
	float temper_red1,temper_red2; 
	float temper_blue1,temper_blue2;
	
	ON_MS1022_FOSC(); // 开晶振
	
	Get_TEMP.PT1000_STATE.PT1000_MeasureSTA = MS1022_TempMeasure_OK; // 默认状态测量成功
	MS1022_SPI_ENABLE();

	// 初始化温度配置

	SET_CMD(POWER_On_Reset); // 0x50
	MS1022_Delay_us(800);//700us等待数据稳定
	MS1022_Write_Reg(0,0xf347e810);
	MS1022_Write_Reg(1,0x21444012);
	MS1022_Write_Reg(6,0xcec06006);
	
	for(SamplingNum = 0;SamplingNum < TEMP_SAMP_NUM;SamplingNum++){ // 疯狂采样6次,做算术平均滤波处理

	MS1022_SPI_ENABLE();
	SET_CMD(MS1022_INIT); // 0x70初始化
	SET_CMD(START_TEMP); // 0x02,启动一次温度测量	
	MS1022_Delay_us(800);//700us等待数据稳定
	
	MS1022_STA_REG = MS1022_Read_STAT(); // 读取状态寄存器，必须加此句
	
	while(!MS1022_Interrupt_FLAG)  // 等待中断
	{
		if(++err_time > 1000U){
			Get_TEMP.PT1000_STATE.PT1000_MeasureSTA = MS1022_TempMeasure_Fail; // 标志超时测量失败！
			break; 
		}
	}
	MS1022_Interrupt_FLAG = 0; // 清除中断标志
	
	// 读取铂电阻4个通道值
	temper_val[0] = MS1022_Read_Reg(0);
	temper_val[1] = MS1022_Read_Reg(1);
	temper_val[2] = MS1022_Read_Reg(2);
	temper_val[3] = MS1022_Read_Reg(3);
	
	// 红色温度探头
	temper_temp = (float)(temper_val[0]) / temper_val[2];
	temper_red1 = temper_temp * MS1022_CH3_REF_RES_1000;  // 通道3参考电阻	
	temper_temp = (float)temper_val[0] / temper_val[3];
	temper_red2 = temper_temp * MS1022_CH4_REF_RES_1400;  // 通道4参考电阻
	
	// 蓝色温度探头
	temper_temp  = (float)temper_val[1] / temper_val[2];
	temper_blue1 = temper_temp * MS1022_CH3_REF_RES_1000;
	temper_temp  = (float)temper_val[1] / temper_val[3];
	temper_blue2 = temper_temp * MS1022_CH4_REF_RES_1400;

	temper_red[SamplingNum] = (temper_red1 + temper_red2) / 2.0f;
	temper_blue[SamplingNum] = (temper_blue1 + temper_blue2) / 2.0f;

	}	

	OFF_MS1022_FOSC(); // 关闭晶振
	
	// 算术平均值滤波
	for(SamplingNum = 0u,temper_red1 = temper_blue1 = 0.0f;SamplingNum < TEMP_SAMP_NUM;SamplingNum++){
		temper_red1 += temper_red[SamplingNum];
		temper_blue1 += temper_blue[SamplingNum];
	}

	temper_red1 /= TEMP_SAMP_NUM;
	temper_blue1 /= TEMP_SAMP_NUM;
	
	// 温度值计算
	temper_red1 = Count_Temper_Rt(temper_red1);
	temper_blue1 = Count_Temper_Rt(temper_blue1);

	// 最终温度值
	Get_TEMP.Temperature_In = temper_red1;// RED
	Get_TEMP.Temperature_Out = temper_blue1;// BLUE

	// 温度校准...........
	
	// PT1000传感器工作状态识别处理
	if((int)Get_TEMP.Temperature_In < -50){  // 进口温度传感器短路故障
	
		Get_TEMP.PT1000_STATE.PT1000_Red_In = MS1022_Temp_Short;
		
	}else if((int)Get_TEMP.Temperature_In > 300){ // 进口温度传感器开路故障
		
	    Get_TEMP.PT1000_STATE.PT1000_Red_In = MS1022_Temp_Open;
	
	}else{  // 进口温度传感器正常
		
	    Get_TEMP.PT1000_STATE.PT1000_Red_In = MS1022_Temp_Normal;
		
	}
	
	if((int)Get_TEMP.Temperature_Out < -50){  // 出口温度传感器短路故障
	
		Get_TEMP.PT1000_STATE.PT1000_BLUE_Out = MS1022_Temp_Short;
		
	}else if((int)Get_TEMP.Temperature_Out > 300){ // 出口温度传感器开路故障
		
	    Get_TEMP.PT1000_STATE.PT1000_BLUE_Out = MS1022_Temp_Open;
	
	}else{  // 出口温度传感器正常
		
	    Get_TEMP.PT1000_STATE.PT1000_BLUE_Out = MS1022_Temp_Normal;
		
	}	
	
	MS1022_SPI_DISABLE(); 
		
	// 判断温度传感器状态方法：直接判断换算后的温度值；
	// 再根据PT1000的测量范围是：-50 ~ 300 摄氏度，因此判定极限值就取测量范围的上下限。
	// 使用此方式判断的好处是可以准确定位到某个温度传感器的状态，这样更容易分析问题
	// 短路：温度值 < -50 : 实测为 -247摄氏度
	// 开路：温度值 > 300:实测为 3398263 摄氏度
	//Get_TEMP.PT1000_STATE.PT1000_MeasureSTA = MS1022_TempMeasure_OK; // 标志测量温度成功
	
	
	// 计算温差 = 出水温度 - 进水温度
	Get_TEMP.Temperature_Diff = Get_TEMP.Temperature_Out - Get_TEMP.Temperature_In;
	
}

/*------------------------------------------------------------
* 函数名称：Count_Temper_Rt
* 函数说明：根据铂电阻阻值计算温度值（摄氏度）
* 函数输入：input_PoRes:铂电阻阻值
* 函数输出：摄氏度
* 函数解释：无
-------------------------------------------------------------*/
static float Count_Temper_Rt(float input_PoRes)
{
	long double temp_e3 = 8e-10 * input_PoRes * input_PoRes * input_PoRes; // 3次项
	long double temp_e2 = 7e-6 * input_PoRes * input_PoRes; // 2次项
	long double temp = 0;
	float temperature = 0;
	
    temp = -247.01f + 0.2393f * input_PoRes + temp_e2 + temp_e3; //计算当前根据参考电阻所测的未进行补偿的温度
	temperature = temp;
	return temperature;
}

// 冒泡排序--浮点数
void RubbleSort(float array[],unsigned char len)   // 从小到大排序
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
		// 交换
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
		// 交换
        temp = Array[k];
        Array[k] = Array[i];
        Array[i] = temp;
    }
}


// 设置命令
void SET_CMD(unsigned char Cmd_1Byte)
{
		MS1022_SPI_ENABLE();
		SPI_MS1022_Write(Cmd_1Byte);
		MS1022_SPI_DISABLE();
}

// 整数平均值
unsigned long tab_long_average(unsigned long* indata,unsigned char len){

	unsigned long resualt = 0;
	unsigned char i = 0;
	for(i = 0;i < len;i++){
		
		resualt += (*indata)++;
	}
	return (unsigned long)((float)resualt / len);
	
}

// 浮点平均值
float tab_float_average(float* input_value,unsigned char len)
{
	unsigned char i = 0;
	double resualt = 0.0f;
	
	for(i = 0;i < len;i++){
		
		resualt += input_value[i];
	}
	return (float)(resualt / len);
}

//获取高速时钟校正因子
double Get_CLK_ref(void)                              
{
    unsigned int ret = 0;
    unsigned long factor_unit = 0UL;
	double g_factor_value = 0.0f;  
	
	SET_CMD(MS1022_INIT); // 0x70初始化
    SET_CMD(START_Cal_Resonator); //启动高速晶振校准测量
	//MS1022_Interrupt_FLAG
	Wait_InterruptSucceed(ret,500u,MS1022_Interrupt_FLAG);// 等待测量中断完成并自动清除标志

	//读GP22结果寄存器0(高速晶振校准测量结果)32bit数据到SPI_Buf/高位在第一位
	factor_unit = MS1022_Read_Reg(0);

	g_factor_value = (double)(factor_unit) / 65536.0f;          //16位整数位16小数位
    g_factor_value = 244.140625 / (g_factor_value * 0.25);   //计算高速晶振校正系数(8个脉冲的32768HZ的校正系数)

	return g_factor_value;
}


/*------------------------------------------------------------
* 函数名称：Get_Flow
* 函数说明：计算得到得到上游、下游测量飞行时间（us）和时间差。
* 函数输入：无
* 函数输出：无
* 函数解释：结果值在 typedef struct __get_time__ 的 Get_Time中。
-------------------------------------------------------------*/
void Get_Flow(void)
{
	unsigned int err_time = 0x0000;  // 超时时间
	unsigned char samping_n = 0;  // 采样次数累加变量
	
	// 上游：三组回波测量值2次累加和
	unsigned long sum_up_0_val[FLOW_SAMP_NUM] = { 0 };
	unsigned long sum_up_1_val[FLOW_SAMP_NUM] = { 0 };
	unsigned long sum_up_2_val[FLOW_SAMP_NUM] = { 0 };
	// 下游：三组回波测量值2次累加和
	unsigned long sum_down_0_val[FLOW_SAMP_NUM] = { 0 };
	unsigned long sum_down_1_val[FLOW_SAMP_NUM] = { 0 };
	unsigned long sum_down_2_val[FLOW_SAMP_NUM] = { 0 };

	// 缓冲
	double up_time_0 = 0,up_time_1 = 0,up_time_2 = 0;
	double down_time_0 = 0,down_time_1 = 0,down_time_2 = 0;
	
	// 流量测量初始化配置
	SET_CMD(POWER_On_Reset); // 0x50
	MS1022_Delay_us(800);//700us等待数据稳定	
	
	/*----- 我的配置 ---------------*/ 
//	MS1022_Write_Reg(0,0xf347e800);
//	MS1022_Write_Reg(1,0x21444001);
//	MS1022_Write_Reg(2,0xa01f3802);
//	MS1022_Write_Reg(3,0x08000003);//
//	MS1022_Write_Reg(4,0x20000004);
//	MS1022_Write_Reg(5,0x30000005);	
//	MS1022_Write_Reg(6,0xcec06006);// 应用场景：这里必须用模拟模式，需要32KHZ信号输入。
//	//MS1022_Write_Reg(6,0x4ec06006);// 数字模式
	
	/*------------ 瑞盟，马工配置 --------------*/
	MS1022_Write_Reg(0,0xf347e800);	//携带开启晶振
	MS1022_Write_Reg(1,0x21444001);	
	MS1022_Write_Reg(2,0xa01e0002);	
	MS1022_Write_Reg(3,0xf8510303);	
	MS1022_Write_Reg(4,0x20004f04);	
	MS1022_Write_Reg(5,0x30000005);	
	MS1022_Write_Reg(6,0xcec06006);	
	
	// 超声波时间采样
	FOREACH(samping_n,0u,FLOW_SAMP_NUM,1u)ORG       // 采样开始
			
/*================ [第一次测量上游] ================================*/

	MS1022_Write_Reg(5,0x30000005);  // 上游测量模式
	SET_CMD(MS1022_INIT); // 0x70初始化
	SET_CMD(START_TOF); // 0x01	
	SET_Delay_us(50);  // 等待MS1022准备
	
	Get_Time.flow_status = MS1022_Read_STAT(); // 读状态
	
	Wait_InterruptSucceed(err_time,50u,MS1022_Interrupt_FLAG);// 等待测量中断完成并自动清除标志

	SET_CMD(MS1022_INIT); // 0x70初始化
	SET_CMD(START_TOF); // 0x01	
	SET_Delay_us(50);  // 等待MS1022准备
	
	Get_Time.flow_status = MS1022_Read_STAT(); // 读状态
	
	Wait_InterruptSucceed(err_time,50u,MS1022_Interrupt_FLAG);// 等待测量中断完成并自动清除标志

	SET_CMD(MS1022_INIT); // 0x70初始化
	SET_CMD(START_TOF); // 0x01	
	SET_Delay_us(50);  // 等待MS1022准备
	
	Get_Time.flow_status = MS1022_Read_STAT(); // 读状态
	
	Wait_InterruptSucceed(err_time,50u,MS1022_Interrupt_FLAG);// 等待测量中断完成并自动清除标志
	
	// 读取3个回波脉冲的时间值
	sum_up_0_val[samping_n] = MS1022_Read_Reg(0);
	sum_up_1_val[samping_n] = MS1022_Read_Reg(1);
	sum_up_2_val[samping_n] = MS1022_Read_Reg(2);
	
/*================ [第二次测量下游] ================================*/

	MS1022_Write_Reg(5,0x50000005);// 下游模式测量
	SET_CMD(MS1022_INIT); // 0x70初始化
	SET_CMD(START_TOF); // 0x01	
	SET_Delay_us(50);  // 等待MS1022准备

	Get_Time.flow_status = MS1022_Read_STAT(); // 读状态
	
	Wait_InterruptSucceed(err_time,50u,MS1022_Interrupt_FLAG);// 等待测量中断完成并自动清除标志
	
	// 读取3个回波脉冲的时间值
	sum_down_0_val[samping_n] = MS1022_Read_Reg(0);
	sum_down_1_val[samping_n] = MS1022_Read_Reg(1);
	sum_down_2_val[samping_n] = MS1022_Read_Reg(2);

	END // n次采样计算结束
	
	OFF_MS1022_FOSC(); // 关闭MS1022晶振等
	
	// 冒泡
	ULong_RubbleSort(sum_up_0_val,FLOW_SAMP_NUM); // 上游第1个回波多次采样值排序
	ULong_RubbleSort(sum_up_1_val,FLOW_SAMP_NUM); // 上游第2个回波多次采样值排序
	ULong_RubbleSort(sum_up_2_val,FLOW_SAMP_NUM); // 上游第3个回波多次采样值排序

	ULong_RubbleSort(sum_down_0_val,FLOW_SAMP_NUM); // 下游第1个回波多次采样值排序
	ULong_RubbleSort(sum_down_1_val,FLOW_SAMP_NUM); // 下游第2个回波多次采样值排序
	ULong_RubbleSort(sum_down_2_val,FLOW_SAMP_NUM); // 下游第3个回波多次采样值排序	
	
	// 采样结束---计算平均值缓冲
	// 三组回波的上游时间
	ARRAY_AVERAGE(sum_up_0_val,samping_n,FLOW_SAMP_NUM,DEL_ARRAY_NUM,up_time_0);// 第一个回波平均值
	ARRAY_AVERAGE(sum_up_1_val,samping_n,FLOW_SAMP_NUM,DEL_ARRAY_NUM,up_time_1);// 第二个回波平均值
	ARRAY_AVERAGE(sum_up_2_val,samping_n,FLOW_SAMP_NUM,DEL_ARRAY_NUM,up_time_2);// 第三个回波平均值
//	Get_Time.Forward_Time = (up_time_0 + up_time_1 + up_time_2) / 3.0f / 65536.0f / 4.0f; // 得到上游时间
	Get_Time.Forward_Time = (up_time_0 + up_time_1 + up_time_2) / 786432.0f; // 得到上游时间
	
	// 三组回波的下游时间
	ARRAY_AVERAGE(sum_down_0_val,samping_n,FLOW_SAMP_NUM,DEL_ARRAY_NUM,down_time_0);// 第一个回波平均值
	ARRAY_AVERAGE(sum_down_1_val,samping_n,FLOW_SAMP_NUM,DEL_ARRAY_NUM,down_time_1);// 第二个回波平均值
	ARRAY_AVERAGE(sum_down_2_val,samping_n,FLOW_SAMP_NUM,DEL_ARRAY_NUM,down_time_2);// 第三个回波平均值
//	Get_Time.Reverse_Time = (down_time_0 + down_time_1 + down_time_2) / 3.0f / 65536.0f / 4.0f; // 得到下游时间
	Get_Time.Reverse_Time = (down_time_0 + down_time_1 + down_time_2) / 786432.0f; // 得到下游时间

	Get_Time.Time_Diff = Get_Time.Forward_Time - Get_Time.Reverse_Time; // 时间差
	
	// 流量矫正： 时钟矫正，温度对流量的影响、分段线性矫正。
	Get_CLK_ref();
	// 计算流体流速
	#define VOICE_SPEED_C   1400.0f  // m/s	----- 理论中的声音再水中的速度
	#define WATER_PIPE_L    0.006f   // m   ----- 超声波传输路径长度
	
	Get_FlowHeat.flow_speed = (double)(pow(VOICE_SPEED_C,2U) * Get_Time.Time_Diff / 1000000.0f) / (WATER_PIPE_L * sqrt(2));
	Get_FlowHeat.flow_speed /= 36.0f; // m3/h
	
	#undef  VOICE_SPEED_C
	#undef  WATER_PIPE_L
	
	// 修正处理
	// 按温度
	// 计算流量
	
	// y = 1.3363x - 14.254

//	if(Get_FlowHeat.flow_speed > )
//	Get_FlowHeat.flow_speed = 1.3363f * Get_FlowHeat.flow_speed - 14.254f;
	// Get_FlowHeat.flow_speed = ((Get_Time.Time_Diff / (Get_Time.Forward_Time * Get_Time.Reverse_Time)) / 1000000.0f / 3600.0f) * (0.06 / sqrt(2));
}




