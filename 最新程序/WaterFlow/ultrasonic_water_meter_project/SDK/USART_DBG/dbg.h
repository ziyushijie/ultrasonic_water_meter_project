

#ifndef __DBG__H__
#define __DBG__H__

#include "r_cg_macrodriver.h"
#include "stdio.h"


#define DBG_UART_Send  R_UART1_Send // 串口发送函数

void DBG_SendString_LEN(char *Str,unsigned char len); // 发送指定长度数据

void DBG_SendString(char *Str); // 发送字符串

void DBG_Printf_Int(char *str,long cmd); // 整型串口调试
void DBG_Printf_Double(char *str,double cmd); // 双精度浮点数串口调试
unsigned char Get_StrLength(char* string); // 获取字符串长度

#endif   // 串口2调试组件



