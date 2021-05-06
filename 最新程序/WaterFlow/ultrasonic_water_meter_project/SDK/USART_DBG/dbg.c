

#include "dbg.h"
#include "r_cg_sau.h"
#include "stdlib.h"

/*--------------------------------------------------------------------------
******************* 说明文件 **************************
* 调试应注意：使用dbg发送函数（发送操作太频繁）会干扰到键盘可能导致键盘失效；
---------------------------------------------------------------------------*/

extern _Bool busy; // 串口 发送忙标志

void DBG_SendString_LEN(char *Str,unsigned char len)
{
	
	busy = 1; 
    DBG_UART_Send((unsigned char*)Str,len);
	while(busy); // 检测忙信号[uart 中断服务文件中]
	
}

unsigned char Get_StrLength(char* string)
{
	unsigned char i = 0;
	while(*string != '\0')
	{
		i++;
		string++;
	}
	return i;
}



void DBG_SendString(char *String)
{
	unsigned char len = 0;
	len= Get_StrLength(String);
	
	//LCD_Disp_Num(4,len,3);
 
	DBG_SendString_LEN(String,len);

}


void DBG_Printf_Int(char *str,long cmd)
{
	char *Dbg_char;
	unsigned char Len_str = Get_StrLength(str);
	unsigned char Len_cmd = sizeof(cmd);
	
	Dbg_char = (char*)malloc(Len_str + Len_cmd); 
	
	sprintf(Dbg_char,str,cmd);
	DBG_SendString(Dbg_char);
	
	free(Dbg_char);
	
}

void DBG_Printf_Double(char *str,double cmd)
{
	char *Dbg_char;
	unsigned char Len_str = Get_StrLength(str);
	unsigned char Len_cmd = sizeof(cmd);
	
	Dbg_char = (char*)malloc(Len_str + Len_cmd);
	
	sprintf(Dbg_char,str,cmd);
	DBG_SendString(Dbg_char);
	
	free(Dbg_char);
	
}




