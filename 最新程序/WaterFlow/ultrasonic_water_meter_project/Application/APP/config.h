#ifndef CONFIG_H_
#define CONFIG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "r_cg_macrodriver.h"	// 瑞萨单片机资源和系统
	#include "rl78_cfg.h"
	#include "LanguageRule.h"
	/*##########################################################################################################*/
	// ------------中断优先级配置区域：-----配置的范围：[0,3]超出无效，0为最高优先级。
	
	#define DKEY_EXTERN_INT_Priority                        2U		// 按键下降沿中断优先级
	#define WDT_Priority                                    2U      // 独立看门狗%75喂狗中断[注意：软件配置为最高优先级时，生成的代码任然是优先级 level2 的代码，很奇怪]

	#define MBUS_USART1_RX_Priority                         2U      // MBUS单片机接收完成中断
	#define MBUS_USART1_RX_ERROR_Priority                   3U      // MBUS单片机接收错误中断
	#define MBUS_USART1_TX_Priority                         2U      // MBUS单片机发送完成中断
	
	#define IRDA_USART2_RX_Priority                         2U      // 红外通讯-串口接收完成中断
	#define IRDA_USART2_RX_ERROR_Priority                   3U      // 红外通讯-串口接收错误中断
	#define IRDA_USART2_TX_Priority                         2U      // 红外通讯-串口发送完成中断
	
	#define MS1022_EXTERN_INT_Priority                      1U      // 外部中断-MS1022测量中断

	#define MS1022_CSI00_Priority                           3U      // SPI传输中断

	#define TIMER_Priority                                  3U      // 定时器中断
	
	// PPRH:是在默认生成的优先级配置寄存器中的最开头的那一个。PPRL第二个。
	#define _PPR_SEG_CONFIG(priiority,PPRH,PPRL)  	        PPRH = priiority / 2U, PPRL = priiority % 2U
	
//	/*----------- 键盘中断 -----------*/
//	#if (DKEY_EXTERN_INT_Priority == 3U)// 最低优先级
	
//		#define __DKEY_EXTERN_INT_Priority0  1U
//		#define __DKEY_EXTERN_INT_Priority1  1U
		
//	#elif (DKEY_EXTERN_INT_Priority == 2U) // 次低优先级
	
//		#define __DKEY_EXTERN_INT_Priority0  1U
//		#define __DKEY_EXTERN_INT_Priority1  0U
		
//	#elif (DKEY_EXTERN_INT_Priority == 1U) // 次高优先级

//		#define __DKEY_EXTERN_INT_Priority0  0U
//		#define __DKEY_EXTERN_INT_Priority1  1U
		
//	#elif (DKEY_EXTERN_INT_Priority == 0U) // 最高优先级
	
//		#define __DKEY_EXTERN_INT_Priority0  0U
//		#define __DKEY_EXTERN_INT_Priority1  0U

//	#endif
	
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* CONFIG_H_ */
