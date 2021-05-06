

#ifndef __DBG__H__
#define __DBG__H__

#include "r_cg_macrodriver.h"
#include "stdio.h"


#define DBG_UART_Send  R_UART1_Send // ���ڷ��ͺ���

void DBG_SendString_LEN(char *Str,unsigned char len); // ����ָ����������

void DBG_SendString(char *Str); // �����ַ���

void DBG_Printf_Int(char *str,long cmd); // ���ʹ��ڵ���
void DBG_Printf_Double(char *str,double cmd); // ˫���ȸ��������ڵ���
unsigned char Get_StrLength(char* string); // ��ȡ�ַ�������

#endif   // ����2�������



