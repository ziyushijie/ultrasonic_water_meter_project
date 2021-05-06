
#include "rqz_lcd.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
//#include "dbg.h"

#define CORRECT  1   // 显示正确【正常】
#define ERROR    0   // 超出显示能力【异常】

//static char DBG_UART2_SBUF_Temp[20]={ 0 };

// LCD数据段码表 
// 段码表堆积格式：高4位SEG2n+1,低4位SEG2n.
unsigned char const LCD_DISP_TAB[10] = {0xf5,0x60,0xd3,0xf2,0x66,0xb6,0xb7,0xe0,0xf7,0xf6};// 数字显示
unsigned char const LCD_ABC_TAB[6] = {0xe7,0x37,0x95,0x73,0x97,0x87}; // A~F的字母显示

unsigned char const LCD_SpecificTAB[2] = { // 预留的特殊字符段码显示表,在此空间扩展要显示的代码

0x02,	// '-'
0x00    // ' '

};  

LCD_USE_VOID__user  USER_LCD_USE_FILL = LCD_USE_VOID;   // 使用空字符覆盖保留多余的位长



// 开启显示
void XY_LCD_DisplayON(void)
{
	SCOC = 1;
	LCDON = 1;
}


// 关闭显示
void XY_LCD_DisplayOFF(void)
{
	SCOC = 1;
	LCDON = 0;
}


/*---- 使用了 22个SEGn --------*/

void XY_LCD_Init(void)
{
    // 初始化屏幕
    R_LCD_Create();
    // 开启显示
    XY_LCD_DisplayON();
}

// -------- 清空屏幕所有
void clear_lcd(void){
	
	SEG0 = 0xf0;
	SEG1 = 0xf0;
	SEG2 = 0xf0;
	SEG3 = 0xf0;
	SEG7 = 0xf0;
	SEG8 = 0xf0;

	SEG11 = 0xf0;
	SEG12 = 0xf0;
	SEG16 = 0xf0;
	SEG17 = 0xf0;
	SEG18 = 0xf0;
	SEG19 = 0xf0;
	SEG20 = 0xf0;
	SEG21 = 0xf0;
	SEG22 = 0xf0;
	SEG23 = 0xf0;

	SEG35 = 0xf0;
	SEG36 = 0xf0;
	SEG37 = 0xf0;
	SEG38 = 0xf0;
//	SEG48 = 0;
//	SEG49 = 0;
	SEG33=0xf0;//!
	SEG34=0xf0;//!
	
}

// 显示所有
void XY_LCD_Display_ALL(void)
{
	// 20210315------------显示所有
	SEG0 = 0x0f;
	SEG1 = 0x0f;
	SEG2 = 0x0f;
	SEG3 = 0x0f;
	SEG7 = 0x0f;
	SEG8 = 0x0f;

	SEG11 = 0x0f;
	SEG12 = 0x0f;
	SEG16 = 0x0f;
	SEG17 = 0x0f;
	SEG18 = 0x0f;
	SEG19 = 0x0f;
	SEG20 = 0x0f;
	SEG21 = 0x0f;
	SEG22 = 0x0f;
	SEG23 = 0x0f;

	// 单位小数点等
	SEG35 = 0x0f;
	SEG36 = 0x0f;
	SEG37 = 0x0f;
//	SEG48 = 0x0f;
//	SEG49 = 0x0f;
	SEG33=0x0f;//!
	SEG34=0x0f;//!

}


// 清除LCD-段码部分全灭
void XY_LCD_DisplayClear(void)
{
	
	SEG1 &= 0xf0;
	SEG0 &= 0xf8;
	
	SEG3 &= 0xf0;
	SEG2 &= 0xf8;
	
	SEG8 &= 0xf0;
	SEG7 &= 0xf8;
	
	SEG12 &= 0xf0;
	SEG11 &= 0xf8;
	
	SEG17 &= 0xf0;
	SEG16 &= 0xf8;
	
	SEG19 &= 0xf0;
	SEG18 &= 0xf8;
	
	SEG21 &= 0xf0;
	SEG20 &= 0xf8;
	
	SEG23 &= 0xf0;
	SEG22 &= 0xf8;
}


// 清除指定位置开始的指定长度的段显示【清除开始方向：从左往右】
// StartPoint:开始清除的位置
// ClearLen：清除的长度
static void XY_LCD_DisplayClearLen(unsigned char StartPoint,unsigned char ClearLen)
{
	
	switch(StartPoint)
	{
		case(0):
				SEG23 &= 0xf0;
				SEG22 &= 0xf8;
				ClearLen--;
				if(ClearLen == 0)break;
		case(1):
				SEG21 &= 0xf0;
				SEG20 &= 0xf8;	
				ClearLen--;
				if(ClearLen == 0)break;
		case(2):
				SEG19 &= 0xf0;
				SEG18 &= 0xf8;					
				ClearLen--;
				if(ClearLen == 0)break;
		case(3):
				SEG17 &= 0xf0;
				SEG16 &= 0xf8;						
				ClearLen--;
				if(ClearLen == 0)break;
		case(4):
				SEG12 &= 0xf0;
				SEG11 &= 0xf8;	
				ClearLen--;
				if(ClearLen == 0)break;
		case(5):
				SEG8 &= 0xf0;
				SEG7 &= 0xf8;	
				ClearLen--;
				if(ClearLen == 0)break;
		case(6):
				SEG3 &= 0xf0;
				SEG2 &= 0xf8;	
				ClearLen--;
				if(ClearLen == 0)break;
		case(7):
				SEG1 &= 0xf0;
				SEG0 &= 0xf8;
				ClearLen--;
				if(ClearLen == 0)break;
	}
}

//void XY_LCD_DisplayClearBIT(unsigned char Point)
//{
	
//	switch(Point)
//	{
//		case(0):
//				SEG10 = 0x00;
//				SEG11 &= 0xf8;
// 				break;
//		case(1):
//				SEG12 = 0x00;
//				SEG13 &= 0xf8;	
// 				break;

//		case(2):
//				SEG14 = 0x00;
//				SEG15 &= 0xf8;	
// 				break;

//		case(3):
//				SEG16 = 0x00;
//				SEG17 &= 0xf8;	
// 				break;

//		case(4):
//				SEG18 = 0x00;
//				SEG19 &= 0xf8;	
// 				break;

//		case(5):
//				SEG20 = 0x00;
//				SEG21 &= 0xf8;
// 				break;

//		case(6):
//				SEG22 = 0x00;
//				SEG23 &= 0xf8;	
// 				break;

//		case(7):
//				SEG24 = 0x00;
//				SEG25 &= 0xf8;
// 				break;

//	}
//}



/*------------------------------------------------------
// 函数功能： 显示/隐藏汉字单位标识或者单位选项
// 函数输入：要显示的单位或汉字标识
// 函数输入：显示，ENABLE;不显示，DISABLE
// 函数输出：无
// 函数解释：无
-------------------------------------------------------*/
void LCD_DisplayUnit(LCD_Unit dispSelf,LCD_EN _EN)
{
	switch(dispSelf)
	{		
	case(HZ_Summation): // 显示累积
	{
		if(_EN == ENABLE)
	         SEG0 |= 0x08;
		else
	         SEG0 &= 0xf7;
	};break;
	case(HZ_Heat): // 显示热量
	{
		if(_EN == ENABLE)
	         SEG2 |= 0x08;
		else
	         SEG2 &= 0xf7;
	};break;
	case(HZ_Cauld): // 显示冷量
	{
		if(_EN == ENABLE)
	         SEG7 |= 0x08;
		else
	         SEG7 &= 0xf7;
	};break;
	case(HZ_Flow): // 显示流量
	{
		if(_EN == ENABLE)
	         SEG11 |= 0x08;
		else
	         SEG11 &= 0xf7;
	};break;
	
	case(HZ_InWater): // 显示进水
	{
		if(_EN == ENABLE)
	         SEG16 |= 0x08;
		else
	         SEG16 &= 0xf7;
	};break;
	case(HZ_OutWater): // 显示回水
	{
		if(_EN == ENABLE)
	         SEG20 |= 0x08;
		else
	         SEG20 &= 0xf7;
	};break;	
	case(Bit5_UD_): // 显示位5的上下横杠
	{
		if(_EN == ENABLE)
	         SEG18 |= 0x08;
		else
	         SEG18 &= 0xf7;
	};break;
	case(Bit6_UD_): // 显示位6的上下横杠
	{
		if(_EN == ENABLE)
	         SEG22 |= 0x08;
		else
	         SEG22 &= 0xf7;
	};break;	

	case(HZ_Time): // 显示汉字：时间
	{
		if(_EN == ENABLE)
	         SEG33 |= 0x01;
		else
	         SEG33 &= 0xfe;
	};break;

	case(Symbol_UnPower): // 显示符号：电池没电
	{
		if(_EN == ENABLE)
	         SEG33 |= 0x02;
		else
	         SEG33 &= 0xfd;
	};break;
	case(BK_RightGraph): // LCD的数字显示的最右侧"半口"符号显示，开口朝左。
	{
		if(_EN == ENABLE)
	         SEG33 |= 0x04;
		else
	         SEG33 &= 0xfb;
	};break;	
	case(HZ_TemperatureDifference): // 显示：温差
	{
		if(_EN == ENABLE)
	         SEG33 |= 0x08;
		else
	         SEG33 &= 0xf7;
	};break;	
	case(Right_Dot1): // 右侧小数点显示，保留一位小数时使用
	{
		if(_EN == ENABLE)
	         SEG34 |= 0x01;
		else
	         SEG34 &= 0xfe;
	};break;
	
	case(Unit_K): // 显示单位：K
	{
		if(_EN == ENABLE)
	         SEG34 |= 0x02;
		else
	         SEG34 &= 0xfd;
	};break;
	case(Unit_Temp_DU): // 显示：℃
	{
		if(_EN == ENABLE)
	         SEG34 |= 0x04;
		else
	         SEG34 &= 0xfb;
	};break;	
	case(HZ_Date): // 显示：日期
	{
		if(_EN == ENABLE)
	         SEG34 |= 0x08;
		else
	         SEG34 &= 0xf7;
	};break;
	case(Right_Dot2): // 显示：右边开始的第2个小数点
	{
		if(_EN == ENABLE)
	         SEG35 |= 0x01;
		else
	         SEG35 &= 0xfe;
	};break;
	case(Unit_KW): // 显示：KW
	{
		if(_EN == ENABLE)
	         SEG35 |= 0x02;
		else
	         SEG35 &= 0xfd;
	};break;
	case(KWh_IS_Dot): // 显示：KW.h之间的小数点
	{
		if(_EN == ENABLE)
	         SEG35 |= 0x04;
		else
	         SEG35 &= 0xfb;
	};break;	
	case(HZ_Address): // 显示：地址
	{
		if(_EN == ENABLE)
	         SEG35 |= 0x08;
		else
	         SEG35 &= 0xf7;
	};break;
	case(Right_Dot3): // 显示：右边开始的第3个小数点
	{
		if(_EN == ENABLE)
	         SEG36 |= 0x01;
		else
	         SEG36 &= 0xfe;
	};break;
	case(Unit_MW_h): // 显示：MW.h
	{
		if(_EN == ENABLE)
	         SEG36 |= 0x02;
		else
	         SEG36 &= 0xfd;
	};break;	
	case(Unit_h): // 显示：第二行的 h
	{
		if(_EN == ENABLE)
	         SEG36 |= 0x04;
		else
	         SEG36 &= 0xfb;
	};break;
	case(HZ_Power): // 显示：功率
	{
		if(_EN == ENABLE)
	         SEG36 |= 0x08;
		else
	         SEG36 &= 0xf7;
	};break;
	case(Right_Dot4): // 显示：右边开始的第4个小数点
	{
		if(_EN == ENABLE)
	         SEG37 |= 0x01;
		else
	         SEG37 &= 0xfe;
	};break;
	case(Unit_GJ): // 显示：GJ【第4行】
	{
		if(_EN == ENABLE)
	         SEG37 |= 0x02;
		else
	         SEG37 &= 0xfd;
	};break;
	case(Unit_MJ): // 显示：MJ【第4行】
	{
		if(_EN == ENABLE)
	         SEG37 |= 0x04;
		else
	         SEG37 &= 0xfb;
	};break;	
	case(HZ_BUZZ): // 显示：报警
	{
		if(_EN == ENABLE)
	         SEG37 |= 0x08;
		else
	         SEG37 &= 0xf7;
	};break;
	case(Right_Dot5): // 显示：右边开始的第5个小数点
	{
		if(_EN == ENABLE)
	         SEG38 |= 0x01;
		else
	         SEG38 &= 0xfe;
	};break;
	case(Unit_MMM): // 显示：立方米
	{
		if(_EN == ENABLE)
	         SEG38 |= 0x02;
		else
	         SEG38 &= 0xfd;
	};break;
	
	case(Unit_1h): // 显示：/h
	{
		if(_EN == ENABLE)
	         SEG38 |= 0x04;
		else
	         SEG38 &= 0xfb;
	};break;
	case(HZ_TEST): // 显示检定
	{
		if(_EN == ENABLE)
			SEG38 |= 0x08;
		else
			SEG38 &= 0xf7;

	};break;	
	}
}


/*------------------------------------------------------
// 函数功能：位段码显示
// 函数输入：要显示哪一位[0,7)
// 函数输入：要显示的值[0,9] || [A,F] || '-' || ' '
// 函数输出：CORRECT：正常；ERROR：异常。
// 函数解释：输入显示内容时以字符呈现，字母必须大写
-------------------------------------------------------*/
unsigned char LCD_Disp1ByteBit(unsigned char DispBit,unsigned char Data)
{
	unsigned char DisH,DisL;
	
	if(DispBit > 8)return ERROR; // 字符超长
	
	if((Data >= '0') && (Data <= '9')) // 数字
	{
		DisL = LCD_DISP_TAB[Data - '0'] >> 4;
		// 这里必须要排出最高位的干扰，避免影响到汉字的显示。
		DisH = LCD_DISP_TAB[Data - '0'] & 0x0f;
	}
	else if((Data >= 'A') && (Data <= 'F'))  // 字母显示
	{
		DisL = LCD_ABC_TAB[Data - 'A'] >> 4;
		// 这里必须要排出最高位的干扰，避免影响到汉字的显示。
	    DisH = LCD_ABC_TAB[Data - 'A'] & 0x0f;
	}	
	else if(Data == '-')// 显示负号
	{
		DisL = LCD_SpecificTAB[0] >> 4;
		DisH = LCD_SpecificTAB[0] & 0x0f;	
	}
	else if(Data == ' ') // 该位显示空格
	{
		DisL = LCD_SpecificTAB[1] >> 4;
		DisH = LCD_SpecificTAB[1] & 0x0f;		
	}
//	else if(Data == '.') // 小数点显示
//	{
//		switch(DispBit){  // 小数位顺序：从右到左
		
//			case(5):{
				
//				LCD_DisplayUnit(Right_Dot1,ENABLE);
				
//			};return CORRECT; // 正确显示
			
//			case(4):{
				
//				LCD_DisplayUnit(Right_Dot2,ENABLE);
				
//			};return CORRECT; // 正确显示
			
//			case(3):{
				
//				LCD_DisplayUnit(Right_Dot3,ENABLE);
				
//			};return CORRECT; // 正确显示
			
//			case(2):{
				
//				LCD_DisplayUnit(Right_Dot4,ENABLE);
				
//			};return CORRECT; // 正确显示
			
//			case(1):{
				
//				LCD_DisplayUnit(Right_Dot5,ENABLE);
				
//			};return CORRECT; // 正确显示
//			default:return ERROR; // 不存在
//		}
//	}
	else
	return ERROR; // 超出显示能力
	
	//XY_LCD_DisplayClearBIT(DispBit);  // 清除该位显示【不显示】
	
	// 显示内容
	switch(DispBit)
	{
	case(0):
	{	
		SEG0 = DisH;// 最高位为1则显示汉字:累积
		SEG1 |= DisL;  
	};break;
	case(1):
	{	
		SEG2 = DisH;// 最高位=1显示汉字：热量
		SEG3 |= DisL;  
	};break;
	case(2):
	{	
		SEG7 = DisH;// 最高位=1显示汉字：冷量
		SEG8 |= DisL;
	};break;
	case(3):
	{	
		SEG11 = DisH;// 最高位=1显示汉字：流量
		SEG12 |= DisL;
	};break;
	case(4):
	{	
		SEG16 = DisH;// 最高位=1显示汉字：进水
		SEG17 |= DisL;
	};break;
	case(5):
	{	
		SEG18 = DisH; // 最高位=1显示：前一位位数码的上下横线
		SEG19 |= DisL;
	};break;
	case(6):
	{	
		SEG20 = DisH;// 最高位=1显示汉字：回水
		SEG21 |= DisL;
	};break;
	case(7):
	{	
		SEG22 = DisH;// 最高位=1显示：前一位位数码的上下横线
		SEG23 |= DisL;
	};break;
	}
	return CORRECT; // 正确显示
}



/*------------------------------------------------------
// 函数功能：字符串显示，内容区间：[0,9]||[A,F] || '-'
// 函数输入：从哪一位开始显示[0,7)
// 函数输入：要显示的字符串
// 函数输出：无
// 函数解释：输入显示内容时以字符呈现，字母必须大写
-------------------------------------------------------*/
void LCD_Disp_String(unsigned char StartPoint,char *Str)
{
	//XY_LCD_DisplayClear(); // 清除显示
	while(*Str != '\0')
	LCD_Disp1ByteBit(StartPoint++,*Str++);
}

/*------------------------------------------------------
// 函数功能：整数显示
// 函数输入：StartPoint 从哪一位开始显示[0,7)
// 函数输入：Disp_VAL 要显示有符号长整数值
// 函数输出：无
// 函数解释：无
-------------------------------------------------------*/
void LCD_Disp_Num(unsigned char StartPoint,long long Disp_VAL,unsigned char Len)
{
	char Char_Temp[8] = { 0 };
	unsigned char i = 0;
	
	unsigned char flag = 0;  // 标识符号
	
	//XY_LCD_DisplayClear(); 
	
	if(Disp_VAL < 0)  // 负数
	{
		Disp_VAL = -Disp_VAL;
		flag = 1;
	}
	
	XY_LCD_DisplayClearLen(StartPoint,Len + 0);// 清除显示【2021更改，这里的1改成了0】
	
	if(USER_LCD_USE_FILL == LCD_USE_VOID){   // 使用空字符覆盖保留多余的位长
		
	sprintf(Char_Temp,"%lld",Disp_VAL); // 按照正数处理
	Len = strlen(Char_Temp);
	
	}
	
	switch(Len)
	{
		
		case(8):
		{
			Char_Temp[i++] = Disp_VAL / 10000000 % 10 + '0'; // 千万位
		};
		case(7):
		{
			Char_Temp[i++] = Disp_VAL / 1000000 % 10 + '0'; // 百万位	
		}; 
		case(6):
		{
			Char_Temp[i++] = Disp_VAL / 100000 % 10 + '0'; // 十万位
		};
		case(5):
		{
			Char_Temp[i++] = Disp_VAL / 10000 % 10 + '0'; // 万位	
		};
		case(4):
		{
			Char_Temp[i++] = Disp_VAL / 1000 % 10 + '0'; // 千位	
		};
		case(3):
		{
			Char_Temp[i++] = Disp_VAL / 100 % 10 + '0'; // 百位	
		};
		case(2):
		{
			Char_Temp[i++] = Disp_VAL / 10 % 10 + '0'; // 十位
		};
		case(1):
		{
			Char_Temp[i] = Disp_VAL % 10 + '0';   // 个位
		};break;
		
	}
	
	LCD_Disp_String(7-(StartPoint+Len-1),Char_Temp); // 数值显示
	
	if(1 == flag) // 最后添加符号，避免前面的清屏导致看不见符号带来副作用。
	{
		flag = '-';
	}
	else  // 如果是正数，则清除该位的“负号”显示
	{
		flag = ' ';
	}
	LCD_Disp1ByteBit(7-(StartPoint+Len),flag); // 符号位显示控制
}

// 计算 a^b 的值
static long int Count_a_b(unsigned char a,unsigned char b)
{
	long int Resualt = a;

	if(!b)return 1; // 特例
	if(--b)
	Resualt *= Count_a_b(a,b); // 递归
	
	return Resualt;
}

void __del_alldot__(void) // 移除小数点;应用场景：整数显示一律不使用小数点
{
	LCD_DisplayUnit(Right_Dot1,DISABLE);
	LCD_DisplayUnit(Right_Dot2,DISABLE);
	LCD_DisplayUnit(Right_Dot3,DISABLE);
	LCD_DisplayUnit(Right_Dot4,DISABLE);
	LCD_DisplayUnit(Right_Dot5,DISABLE);	
}


// 小数点的位置（用于浮点数显示的小数保留位选择）
void LCD_DotLens(unsigned char dotlen)
{
	switch(dotlen) // 小数保留位
	{				
		case(1):
		{
			LCD_DisplayUnit(Right_Dot1,ENABLE);
			LCD_DisplayUnit(Right_Dot2,DISABLE);
			LCD_DisplayUnit(Right_Dot3,DISABLE);
			LCD_DisplayUnit(Right_Dot4,DISABLE);
			LCD_DisplayUnit(Right_Dot5,DISABLE);
		};break;
		case(2):
		{
			LCD_DisplayUnit(Right_Dot1,DISABLE);
			LCD_DisplayUnit(Right_Dot2,ENABLE);
			LCD_DisplayUnit(Right_Dot3,DISABLE);
			LCD_DisplayUnit(Right_Dot4,DISABLE);
			LCD_DisplayUnit(Right_Dot5,DISABLE);
		};break;
		case(3):
		{
			LCD_DisplayUnit(Right_Dot1,DISABLE);
			LCD_DisplayUnit(Right_Dot2,DISABLE);
			LCD_DisplayUnit(Right_Dot3,ENABLE);
			LCD_DisplayUnit(Right_Dot4,DISABLE);
			LCD_DisplayUnit(Right_Dot5,DISABLE);
		};break;
		case(4):
		{
			LCD_DisplayUnit(Right_Dot1,DISABLE);
			LCD_DisplayUnit(Right_Dot2,DISABLE);
			LCD_DisplayUnit(Right_Dot3,DISABLE);
			LCD_DisplayUnit(Right_Dot4,ENABLE);
			LCD_DisplayUnit(Right_Dot5,DISABLE);
		};break;
		case(5):
		{
			LCD_DisplayUnit(Right_Dot1,DISABLE);
			LCD_DisplayUnit(Right_Dot2,DISABLE);
			LCD_DisplayUnit(Right_Dot3,DISABLE);
			LCD_DisplayUnit(Right_Dot4,DISABLE);
			LCD_DisplayUnit(Right_Dot5,ENABLE);
		};break;
		default://不存在此操作
		return;
	}
}



/*--------------------------------------------------------------------
// 函数功能：浮点数显示
// 函数输入：FVal 要显示的浮点数
// 函数输入：IntLen 要显示的浮点数整数部分长度;范围：[1,8]
// 函数输入：DotLen 要显示的浮点数小数部分长度，其中存在四舍五入;范围：[1,5]
// 函数输出：无
// 函数解释：浮点数显示默认从最右侧开始作为其实显示点
// 函数升级：空格填补情况下小于1的显示不全问题已解决。
---------------------------------------------------------------------*/
void LCD_DoubleDisplayMode1(double FVal,unsigned char IntLen,unsigned char DotLen)
{
    long long Disp_VAL = Count_a_b(10,DotLen) * FVal; // 有效数值整数化,不做四舍五入处理

	unsigned char Len = 0;
	char Char_Temp[8] = { 0 };
	unsigned char i = 0;
	//unsigned char strlens = IntLen + DotLen; // 允许长度
	unsigned char flag = 0;  // 标识符号
	unsigned char cn0 = 0;
	
	if(Disp_VAL < 0)  // 负数
	{
		Disp_VAL = -Disp_VAL;
		flag = 1;
	}
	
	sprintf(Char_Temp,"%lld",Disp_VAL); // 按照正整数处理
	Len = strlen(Char_Temp); // 实际长度

	XY_LCD_DisplayClearLen(0u,IntLen + DotLen + 0);// 清除显示【2021更改，这里的1改成了0】
	
	i = 0;
	if((FVal < 1) && (FVal > -1))  // 0<x<1 的数显示特殊处理
	{
		
			while(i < DotLen - (Len - 1)){
				
			LCD_Disp1ByteBit(7 - Len - i++,'0');
			cn0++; // 决定负号的位置
			}
	}
	
	i = 0;
	// 如果数值超出显示范围
	if(Disp_VAL > 10000000){
	__del_alldot__();	// 	移除小数点
	return;  // 超出范围不显示
	}
	
	switch(Len) 
	{
		
		case(8):
		{
			Char_Temp[i++] = Disp_VAL / 10000000 % 10 + '0'; // 千万位
		};
		case(7):
		{
			Char_Temp[i++] = Disp_VAL / 1000000 % 10 + '0'; // 百万位	
		}; 
		case(6):
		{
			Char_Temp[i++] = Disp_VAL / 100000 % 10 + '0'; // 十万位
		};
		case(5):
		{
			Char_Temp[i++] = Disp_VAL / 10000 % 10 + '0'; // 万位	
		};
		case(4):
		{
			Char_Temp[i++] = Disp_VAL / 1000 % 10 + '0'; // 千位	
		};
		case(3):
		{
			Char_Temp[i++] = Disp_VAL / 100 % 10 + '0'; // 百位	
		};
		case(2):
		{
			Char_Temp[i++] = Disp_VAL / 10 % 10 + '0'; // 十位
		};
		case(1):
		{
			Char_Temp[i] = Disp_VAL % 10 + '0';   // 个位
		};break;
		
	}
	
	LCD_Disp_String(7-(Len-1),Char_Temp); // 数值显示
	
	if(1 == flag) // 最后添加符号，避免前面的清屏导致看不见符号带来副作用。
	{
		flag = '-';
	}
	else  // 如果是正数，则清除该位的“负号”显示
	{
		flag = ' ';
	}
	LCD_Disp1ByteBit(7 - Len - cn0,flag); // 符号位显示控制
	
	LCD_DotLens(DotLen); // 小数点位置
	
}

//// 浮点显示方式2
//void LCD_DoubleDisplayMode2(double FVal,unsigned char IntLen,unsigned char DotLen)
//{
//	char _temp_str[9] = { 0 };
//	unsigned char len = 0;
////    long long Num = Count_a_b(10,DotLen) * FVal + 0.5f; // 有效数值整数化,做四舍五入处理
	
////	XY_LCD_DisplayClearLen(0u,IntLen + DotLen + 1);// 清除显示
	
//	//#define CONTROL_CHARP(_IntLen,_DotLen)  #%##_IntLen##.##_DotLen##f
//	//#define CONTROL_CHARP(_IntLen,_DotLen) %##_IntLen##._DotLen##f
////	#define _IntLen 1
////	#define _DotLen 1
	
//	sprintf(_temp_str,"%3.2f",FVal); // 整数化处理
////	//len = strlen(_temp_str) - 1;
//	LCD_Disp_String(0,_temp_str); // 数值显示	
////	LCD_DotLens(DotLen); // 小数点位置
	
//}


//// 浮点显示方式3
//void LCD_DoubleDisplayMode2(double FVal,unsigned char IntLen,unsigned char DotLen)
//{
////	char _temp_str[9] = { 0 };
////	char _ctrstr[9];
	
//	// 1.整数部分长度设置
//	// 2.小数部分长度设置
//	// 3.合并字符串并生成转化的字符串
//	// 4.去除小数点
//	// 5.归纳显示
//	//XY_LCD_DisplayClearLen(0u,IntLen + DotLen + 1);// 清除显示	
//	//sprintf(_temp_str,CtrStr,Num); // 整数化处理
	
//	//LCD_Disp_String(7 - len,_temp_str); // 字符串显示	
	
//	LCD_DotLens(DotLen); // 小数点位置
	
//}



/*------------------------------------------------------
// 函数功能：10进制整数显示，简洁代码形式版
// 函数输入：StartPoint 从哪一位开始显示[0,7)
// 函数输入：Disp_VAL 要显示有符号长整数值
// 函数输出：无
// 函数解释：可以对比执行速度.示波器 {空白填充}
-------------------------------------------------------*/
void LCD_Disp_To10Num(unsigned char StartPoint,long long Disp_VAL,unsigned char Len)
{
	char Char_Temp[8] = { 0 };
	unsigned char flag = 0u;

	if(Disp_VAL < 0){
		Disp_VAL = -Disp_VAL;
		flag = 1;
	}	

	XY_LCD_DisplayClearLen(StartPoint,Len + 0);// 清除显示【2021更改，这里的1改成了0】
	
	sprintf(Char_Temp,"%lld",Disp_VAL); // 按照10进制处理
	Len = strlen(Char_Temp);
	
	LCD_Disp_String(7-(StartPoint+Len-1),Char_Temp); // 数值显示
	if(1 == flag) // 最后添加符号，避免前面的清屏导致看不见符号带来副作用。
	{
		flag = '-';
	}
	else  // 如果是正数，则清除该位的“负号”显示
	{
		flag = ' ';
	}
	LCD_Disp1ByteBit(7-(StartPoint+Len),flag); // 符号位显示控制
}

/*------------------------------------------------------
// 函数功能：转化为HEX整数显示
// 函数输入：StartPoint 从哪一位开始显示[0,7)
// 函数输入：Disp_VAL 要显示有符号长整数值
// 函数输出：无
// 函数解释：{空白填充};只能显示整数
-------------------------------------------------------*/
void LCD_Disp_ToHEX(unsigned char StartPoint,unsigned long long Disp_VAL,unsigned char Len)
{
	char Char_Temp[8] = { 0 };

	
	XY_LCD_DisplayClearLen(StartPoint,Len + 0);// 清除显示【2021更改，这里的1改成了0】
	
	sprintf(Char_Temp,"%llX",Disp_VAL); // 按照HEX处理
	Len = strlen(Char_Temp);
	
	LCD_Disp_String(7-(StartPoint+Len-1),Char_Temp); // 数值显示
	
}


/*------- 功能函数，各物理量功能显示函数区域 ------*/

void LCD_VOID(void)
{}

/*
unsigned char LCD_Disp1ByteBit(unsigned char DispBit,unsigned char Data);
后期优化添加一个函数，以上函数改一个为数值显示，衍生新的数据显示的函数，以提高执行速度，降低功耗。

*/