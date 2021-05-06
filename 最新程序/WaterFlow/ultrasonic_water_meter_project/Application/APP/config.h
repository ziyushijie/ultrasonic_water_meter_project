#ifndef CONFIG_H_
#define CONFIG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "r_cg_macrodriver.h"	// ������Ƭ����Դ��ϵͳ
	#include "rl78_cfg.h"
	#include "LanguageRule.h"
	/*##########################################################################################################*/
	// ------------�ж����ȼ���������-----���õķ�Χ��[0,3]������Ч��0Ϊ������ȼ���
	
	#define DKEY_EXTERN_INT_Priority                        2U		// �����½����ж����ȼ�
	#define WDT_Priority                                    2U      // �������Ź�%75ι���ж�[ע�⣺�������Ϊ������ȼ�ʱ�����ɵĴ�����Ȼ�����ȼ� level2 �Ĵ��룬�����]

	#define MBUS_USART1_RX_Priority                         2U      // MBUS��Ƭ����������ж�
	#define MBUS_USART1_RX_ERROR_Priority                   3U      // MBUS��Ƭ�����մ����ж�
	#define MBUS_USART1_TX_Priority                         2U      // MBUS��Ƭ����������ж�
	
	#define IRDA_USART2_RX_Priority                         2U      // ����ͨѶ-���ڽ�������ж�
	#define IRDA_USART2_RX_ERROR_Priority                   3U      // ����ͨѶ-���ڽ��մ����ж�
	#define IRDA_USART2_TX_Priority                         2U      // ����ͨѶ-���ڷ�������ж�
	
	#define MS1022_EXTERN_INT_Priority                      1U      // �ⲿ�ж�-MS1022�����ж�

	#define MS1022_CSI00_Priority                           3U      // SPI�����ж�

	#define TIMER_Priority                                  3U      // ��ʱ���ж�
	
	// PPRH:����Ĭ�����ɵ����ȼ����üĴ����е��ͷ����һ����PPRL�ڶ�����
	#define _PPR_SEG_CONFIG(priiority,PPRH,PPRL)  	        PPRH = priiority / 2U, PPRL = priiority % 2U
	
//	/*----------- �����ж� -----------*/
//	#if (DKEY_EXTERN_INT_Priority == 3U)// ������ȼ�
	
//		#define __DKEY_EXTERN_INT_Priority0  1U
//		#define __DKEY_EXTERN_INT_Priority1  1U
		
//	#elif (DKEY_EXTERN_INT_Priority == 2U) // �ε����ȼ�
	
//		#define __DKEY_EXTERN_INT_Priority0  1U
//		#define __DKEY_EXTERN_INT_Priority1  0U
		
//	#elif (DKEY_EXTERN_INT_Priority == 1U) // �θ����ȼ�

//		#define __DKEY_EXTERN_INT_Priority0  0U
//		#define __DKEY_EXTERN_INT_Priority1  1U
		
//	#elif (DKEY_EXTERN_INT_Priority == 0U) // ������ȼ�
	
//		#define __DKEY_EXTERN_INT_Priority0  0U
//		#define __DKEY_EXTERN_INT_Priority1  0U

//	#endif
	
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* CONFIG_H_ */
