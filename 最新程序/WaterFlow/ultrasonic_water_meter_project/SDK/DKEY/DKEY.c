
#include "DKEY.h"

/*-------------------------------------------------------
文件说明：
长按键方案一：
由于在外部终断中使用了长按键操作，此操作为了保证效率采用了定时器溢出
中断来作为延时时间基准，所以这里的定时器CH0的优先级必须比外部中断的
优先级高。
长按键方案二:
直接使用短暂延时函数作为长按键延时时间基准。
--------------------------------------------------------*/

unsigned long CurrentTime = 0u; // 当前时间系数
unsigned long LastTime = 0u;   // 上次时间系数

__DKEY_MenuPoint__ DKEY_MenuPoint; // 菜单横纵坐标点变量
__StateFlag    DKEY_SF; // 键盘状态标志

//unsigned char et = 0;

void XY_DKEY_Init(void)
{
	R_INTC_Create();
	R_INTC0_Start();
	// 菜单坐标索引从1开始
	SET_MenuX(1);
	SET_MenuY(1);
}

void CurrentTime_CNT(void)
{
	CurrentTime++; // 当前时间系数累加
}


///*------------------------------------ 
//函数功能：键盘锁
//函数输入：__IS_LOCK
//函数输出：无
//函数解释：调用此函数实现键盘上锁和解锁
//-------------------------------------*/
//void DKEY_LOCK(unsigned char __IS_LOCK)
//{
	// 暂未使用！！！
//}


/*
键盘需要完成的框架概述：
1.添加键盘锁
2.键盘长按，短按事件
*/
////////////////////////////////////////////////////////// 循环扫描检测函数///////////////////////////////////////////////////////
// 键盘扫描内核事件驱动函数
void DKEY_Scan(void (*DKEY_EVENT)(int *GetDKEY))
{
	
	static unsigned char State = 0;
	int dkey_Res = DKEY_VOID;
	
	switch(State)
	{
		case(0):
		{
		 State = 1;
		};//break;   // 去除break,则没有使用间隔延时消抖
		case(1):
		{
		if(Get_DKEY == !DKEY_IDLE_STATE) // 按下
		{
		 State = 2;	
		 LastTime = CurrentTime; // 更新时间系数变量
		 
		 DKEY_SF.OneDown = True;
//		 DKEY_MenuPoint.OneDown = DKEY_Down; // 单次按下事件标志【查询方式可用，必须手动清除】
		 DKEY_Down_RUN_Serve(); // 执行按下事件
		}
		};break;	
		case(2):
		{
		if(Get_DKEY == DKEY_IDLE_STATE)
		{
		 State = 0;
		 dkey_Res = DKEY_Up; // 弹起
		 
		 DKEY_SF.OneUp = True;
		// DKEY_MenuPoint.OneUp = DKEY_Up; // 单次弹起事件标志【查询方式可用，必须手动清除】
		
		 // 控制坐标X轴索引,列表循环
		 DKEY_MenuPoint.Menu_X++;
		 if(DKEY_MenuPoint.Menu_X > DKEY_OneMenu_XNum)
		 DKEY_MenuPoint.Menu_X = 1; 
		 
		 DKEY_Up_RUN_Serve();
		 if(DKEY_EVENT != 0)
		 DKEY_EVENT(&dkey_Res);
		}	
		else
		{
			if(CurrentTime - LastTime == DKEY_LongDownDelayTime)
			{
				
				dkey_Res = DKEY_LongDown; // 长按
				
				 DKEY_SF.OneLongDown = True;
			//	DKEY_MenuPoint.OneLongDown = DKEY_LongDown; // 单次长按事件标志【查询方式可用，必须手动清除】
				
				State = 3;
				
				 // 控制坐标Y轴索引,列表循环
				 DKEY_MenuPoint.Menu_Y++;
				 if(DKEY_MenuPoint.Menu_Y > DKEY_TowMenu_YNum)
				 DKEY_MenuPoint.Menu_Y = 1; 				
				
				DKEY_LongDown_RUN_Serve(); // 长按事件服务函数
				
				if(DKEY_EVENT != 0)
			    DKEY_EVENT(&dkey_Res);
			}
		}
		};break;
		case(3):
		{
			
			if(Get_DKEY == DKEY_IDLE_STATE)State = 0;
		
		};break;		
	}
}

/*---------------------------------------------
* 函数说明：设置菜单纵坐标索引
* 函数输入：无
* 函数输出：无
* 函数解释：无
----------------------------------------------*/
void SET_MenuY(unsigned char SET_Menu_Y)
{
  DKEY_MenuPoint.Menu_Y = SET_Menu_Y;
}

/*---------------------------------------------
* 函数说明：设置菜单纵坐标索引
* 函数输入：无
* 函数输出：无
* 函数解释：发生弹起事件时更改生效
----------------------------------------------*/
void SET_MenuX(unsigned char SET_Menu_X)
{
  DKEY_MenuPoint.Menu_X = SET_Menu_X;
}

/*---------------------------------------------
* 函数说明：获取菜单横坐标索引
* 函数输入：无
* 函数输出：无
* 函数解释：发生长按事件时更改生效
----------------------------------------------*/
unsigned char Get_MenuX(void)
{
 return DKEY_MenuPoint.Menu_X;
}


/*---------------------------------------------
* 函数说明：获取菜单纵坐标索引
* 函数输入：无
* 函数输出：无
* 函数解释：无
----------------------------------------------*/
unsigned char Get_MenuY(void)
{
 return DKEY_MenuPoint.Menu_Y;
}

/*---------------------------------------------
* 函数说明：是否有单次按下事件发生
* 函数输入：无
* 函数输出：无
* 函数解释：无
----------------------------------------------*/
_Bool Get_IsOneDown(void) 
{
	return DKEY_SF.OneDown;
}

/*---------------------------------------------
* 函数说明：是否有单次弹起事件发生
* 函数输入：无
* 函数输出：无
* 函数解释：无
----------------------------------------------*/
_Bool Get_IsOneUp(void) 
{
    return DKEY_SF.OneUp;
}

/*---------------------------------------------
* 函数说明：是否有单次长按事件发生
* 函数输入：无
* 函数输出：无
* 函数解释：无
----------------------------------------------*/
_Bool Get_IsOneLongDown(void) 
{
    return DKEY_SF.OneLongDown;
}

/*---------------------------------------------
* 函数说明：清除单次按下事件标志
* 函数输入：无
* 函数输出：无
* 函数解释：无
----------------------------------------------*/
void ClearOneDown(void) 
{
	DKEY_SF.OneDown = False;
}

/*---------------------------------------------
* 函数说明：清除单次弹起事件标志
* 函数输入：无
* 函数输出：无
* 函数解释：无
----------------------------------------------*/
void ClearOneUp(void) 
{
	DKEY_SF.OneUp = False;
}

/*---------------------------------------------
* 函数说明：清除单次长按事件标志
* 函数输入：无
* 函数输出：无
* 函数解释：无
----------------------------------------------*/
void ClearOneLongDown(void) 
{
	DKEY_SF.OneLongDown = False;
}

/*================================== 事件服务函数 ============================*/


/*------------------------------------ 
函数功能：外部中断-按键中断服务函数,优先级低
函数输入：无
函数输出：无
函数解释：下降沿会调用此函数
-------------------------------------*/
void DKEY_Serve(void)
{
//	static int j = -12;
//	while(Get_DKEY == 0){
//	LCD_Disp_Num(0,j++,4);
//	XY_Delay(100);
//	}
//    j = j == 12 ? -12 : j;
}

/*---------------------------------------------
* 函数说明：按下事件代码区，短按
* 函数输入：无
* 函数输出：无
* 函数解释：无
----------------------------------------------*/
void DKEY_Down_RUN_Serve(void) // 按下事件
{
}

/*---------------------------------------------
* 函数说明：弹起事件代码区，短按
* 函数输入：无
* 函数输出：无
* 函数解释：无
----------------------------------------------*/
void DKEY_Up_RUN_Serve(void) // 弹起事件
{
	//LCD_Disp_Num(0,et++,4);
}


/*---------------------------------------------
* 函数说明：长按事件代码区，长按
* 函数输入：无
* 函数输出：无
* 函数解释：无
----------------------------------------------*/
void DKEY_LongDown_RUN_Serve(void)// 长按事件
{
   // LCD_Disp_Num(0,et++,4);
}


/*----------------- 按键菜单描述

1.传感器错误值(故障)显示菜单
2.进口温度
3.出口温度
4.流量
5.热量
6.时间日期
7.检定
............

*/

