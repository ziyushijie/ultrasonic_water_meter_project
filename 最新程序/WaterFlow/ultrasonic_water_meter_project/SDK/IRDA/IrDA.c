

#include "IrDA.h"
#include "r_cg_sau.h"


/*------------------------------------------------------------
* 函数名称：IrDA_init
* 函数说明：红外通信初始化
* 函数输入：无
* 函数输出：无
* 函数解释：串口发送+接收:波特率=2400bps,偶校验，1stop
-------------------------------------------------------------*/
void IrDA_init(void)     
{
     // 串口+外部中断+电源IO
	 R_SAU1_Create(); // 串口2初始化
	 R_UART2_Start(); // 启动串口2
	 IrDA_PowerControl(IRDA_POWER_OFF); // 关闭红外电源
}

/*------------------------------------------------------------
* 函数名称：IrDA_PowerControl_ON
* 函数说明：开启需要的红外通信电源
* 函数输入：无
* 函数输出：无
* 函数解释：无
-------------------------------------------------------------*/
void IrDA_PowerControl(__IRDA_POWER_OFF_ON__ ON_Ctr)
{
	if (IRDA_POWER_ON == ON_Ctr) // 发送，电源控制开
	{
		IrDA_Power_PIN = 1u;
	}
    if (IRDA_POWER_OFF == ON_Ctr) // 接收，电源控制开
	{
		IrDA_Power_PIN = 0u;
	}
}



