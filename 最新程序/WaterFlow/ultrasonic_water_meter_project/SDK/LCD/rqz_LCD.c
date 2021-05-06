
#include "rqz_lcd.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
//#include "dbg.h"

#define CORRECT  1   // ��ʾ��ȷ��������
#define ERROR    0   // ������ʾ�������쳣��

//static char DBG_UART2_SBUF_Temp[20]={ 0 };

// LCD���ݶ���� 
// �����ѻ���ʽ����4λSEG2n+1,��4λSEG2n.
unsigned char const LCD_DISP_TAB[10] = {0xf5,0x60,0xd3,0xf2,0x66,0xb6,0xb7,0xe0,0xf7,0xf6};// ������ʾ
unsigned char const LCD_ABC_TAB[6] = {0xe7,0x37,0x95,0x73,0x97,0x87}; // A~F����ĸ��ʾ

unsigned char const LCD_SpecificTAB[2] = { // Ԥ���������ַ�������ʾ��,�ڴ˿ռ���չҪ��ʾ�Ĵ���

0x02,	// '-'
0x00    // ' '

};  

LCD_USE_VOID__user  USER_LCD_USE_FILL = LCD_USE_VOID;   // ʹ�ÿ��ַ����Ǳ��������λ��



// ������ʾ
void XY_LCD_DisplayON(void)
{
	SCOC = 1;
	LCDON = 1;
}


// �ر���ʾ
void XY_LCD_DisplayOFF(void)
{
	SCOC = 1;
	LCDON = 0;
}


/*---- ʹ���� 22��SEGn --------*/

void XY_LCD_Init(void)
{
    // ��ʼ����Ļ
    R_LCD_Create();
    // ������ʾ
    XY_LCD_DisplayON();
}

// -------- �����Ļ����
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

// ��ʾ����
void XY_LCD_Display_ALL(void)
{
	// 20210315------------��ʾ����
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

	// ��λС�����
	SEG35 = 0x0f;
	SEG36 = 0x0f;
	SEG37 = 0x0f;
//	SEG48 = 0x0f;
//	SEG49 = 0x0f;
	SEG33=0x0f;//!
	SEG34=0x0f;//!

}


// ���LCD-���벿��ȫ��
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


// ���ָ��λ�ÿ�ʼ��ָ�����ȵĶ���ʾ�������ʼ���򣺴������ҡ�
// StartPoint:��ʼ�����λ��
// ClearLen������ĳ���
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
// �������ܣ� ��ʾ/���غ��ֵ�λ��ʶ���ߵ�λѡ��
// �������룺Ҫ��ʾ�ĵ�λ���ֱ�ʶ
// �������룺��ʾ��ENABLE;����ʾ��DISABLE
// �����������
// �������ͣ���
-------------------------------------------------------*/
void LCD_DisplayUnit(LCD_Unit dispSelf,LCD_EN _EN)
{
	switch(dispSelf)
	{		
	case(HZ_Summation): // ��ʾ�ۻ�
	{
		if(_EN == ENABLE)
	         SEG0 |= 0x08;
		else
	         SEG0 &= 0xf7;
	};break;
	case(HZ_Heat): // ��ʾ����
	{
		if(_EN == ENABLE)
	         SEG2 |= 0x08;
		else
	         SEG2 &= 0xf7;
	};break;
	case(HZ_Cauld): // ��ʾ����
	{
		if(_EN == ENABLE)
	         SEG7 |= 0x08;
		else
	         SEG7 &= 0xf7;
	};break;
	case(HZ_Flow): // ��ʾ����
	{
		if(_EN == ENABLE)
	         SEG11 |= 0x08;
		else
	         SEG11 &= 0xf7;
	};break;
	
	case(HZ_InWater): // ��ʾ��ˮ
	{
		if(_EN == ENABLE)
	         SEG16 |= 0x08;
		else
	         SEG16 &= 0xf7;
	};break;
	case(HZ_OutWater): // ��ʾ��ˮ
	{
		if(_EN == ENABLE)
	         SEG20 |= 0x08;
		else
	         SEG20 &= 0xf7;
	};break;	
	case(Bit5_UD_): // ��ʾλ5�����º��
	{
		if(_EN == ENABLE)
	         SEG18 |= 0x08;
		else
	         SEG18 &= 0xf7;
	};break;
	case(Bit6_UD_): // ��ʾλ6�����º��
	{
		if(_EN == ENABLE)
	         SEG22 |= 0x08;
		else
	         SEG22 &= 0xf7;
	};break;	

	case(HZ_Time): // ��ʾ���֣�ʱ��
	{
		if(_EN == ENABLE)
	         SEG33 |= 0x01;
		else
	         SEG33 &= 0xfe;
	};break;

	case(Symbol_UnPower): // ��ʾ���ţ����û��
	{
		if(_EN == ENABLE)
	         SEG33 |= 0x02;
		else
	         SEG33 &= 0xfd;
	};break;
	case(BK_RightGraph): // LCD��������ʾ�����Ҳ�"���"������ʾ�����ڳ���
	{
		if(_EN == ENABLE)
	         SEG33 |= 0x04;
		else
	         SEG33 &= 0xfb;
	};break;	
	case(HZ_TemperatureDifference): // ��ʾ���²�
	{
		if(_EN == ENABLE)
	         SEG33 |= 0x08;
		else
	         SEG33 &= 0xf7;
	};break;	
	case(Right_Dot1): // �Ҳ�С������ʾ������һλС��ʱʹ��
	{
		if(_EN == ENABLE)
	         SEG34 |= 0x01;
		else
	         SEG34 &= 0xfe;
	};break;
	
	case(Unit_K): // ��ʾ��λ��K
	{
		if(_EN == ENABLE)
	         SEG34 |= 0x02;
		else
	         SEG34 &= 0xfd;
	};break;
	case(Unit_Temp_DU): // ��ʾ����
	{
		if(_EN == ENABLE)
	         SEG34 |= 0x04;
		else
	         SEG34 &= 0xfb;
	};break;	
	case(HZ_Date): // ��ʾ������
	{
		if(_EN == ENABLE)
	         SEG34 |= 0x08;
		else
	         SEG34 &= 0xf7;
	};break;
	case(Right_Dot2): // ��ʾ���ұ߿�ʼ�ĵ�2��С����
	{
		if(_EN == ENABLE)
	         SEG35 |= 0x01;
		else
	         SEG35 &= 0xfe;
	};break;
	case(Unit_KW): // ��ʾ��KW
	{
		if(_EN == ENABLE)
	         SEG35 |= 0x02;
		else
	         SEG35 &= 0xfd;
	};break;
	case(KWh_IS_Dot): // ��ʾ��KW.h֮���С����
	{
		if(_EN == ENABLE)
	         SEG35 |= 0x04;
		else
	         SEG35 &= 0xfb;
	};break;	
	case(HZ_Address): // ��ʾ����ַ
	{
		if(_EN == ENABLE)
	         SEG35 |= 0x08;
		else
	         SEG35 &= 0xf7;
	};break;
	case(Right_Dot3): // ��ʾ���ұ߿�ʼ�ĵ�3��С����
	{
		if(_EN == ENABLE)
	         SEG36 |= 0x01;
		else
	         SEG36 &= 0xfe;
	};break;
	case(Unit_MW_h): // ��ʾ��MW.h
	{
		if(_EN == ENABLE)
	         SEG36 |= 0x02;
		else
	         SEG36 &= 0xfd;
	};break;	
	case(Unit_h): // ��ʾ���ڶ��е� h
	{
		if(_EN == ENABLE)
	         SEG36 |= 0x04;
		else
	         SEG36 &= 0xfb;
	};break;
	case(HZ_Power): // ��ʾ������
	{
		if(_EN == ENABLE)
	         SEG36 |= 0x08;
		else
	         SEG36 &= 0xf7;
	};break;
	case(Right_Dot4): // ��ʾ���ұ߿�ʼ�ĵ�4��С����
	{
		if(_EN == ENABLE)
	         SEG37 |= 0x01;
		else
	         SEG37 &= 0xfe;
	};break;
	case(Unit_GJ): // ��ʾ��GJ����4�С�
	{
		if(_EN == ENABLE)
	         SEG37 |= 0x02;
		else
	         SEG37 &= 0xfd;
	};break;
	case(Unit_MJ): // ��ʾ��MJ����4�С�
	{
		if(_EN == ENABLE)
	         SEG37 |= 0x04;
		else
	         SEG37 &= 0xfb;
	};break;	
	case(HZ_BUZZ): // ��ʾ������
	{
		if(_EN == ENABLE)
	         SEG37 |= 0x08;
		else
	         SEG37 &= 0xf7;
	};break;
	case(Right_Dot5): // ��ʾ���ұ߿�ʼ�ĵ�5��С����
	{
		if(_EN == ENABLE)
	         SEG38 |= 0x01;
		else
	         SEG38 &= 0xfe;
	};break;
	case(Unit_MMM): // ��ʾ��������
	{
		if(_EN == ENABLE)
	         SEG38 |= 0x02;
		else
	         SEG38 &= 0xfd;
	};break;
	
	case(Unit_1h): // ��ʾ��/h
	{
		if(_EN == ENABLE)
	         SEG38 |= 0x04;
		else
	         SEG38 &= 0xfb;
	};break;
	case(HZ_TEST): // ��ʾ�춨
	{
		if(_EN == ENABLE)
			SEG38 |= 0x08;
		else
			SEG38 &= 0xf7;

	};break;	
	}
}


/*------------------------------------------------------
// �������ܣ�λ������ʾ
// �������룺Ҫ��ʾ��һλ[0,7)
// �������룺Ҫ��ʾ��ֵ[0,9] || [A,F] || '-' || ' '
// ���������CORRECT��������ERROR���쳣��
// �������ͣ�������ʾ����ʱ���ַ����֣���ĸ�����д
-------------------------------------------------------*/
unsigned char LCD_Disp1ByteBit(unsigned char DispBit,unsigned char Data)
{
	unsigned char DisH,DisL;
	
	if(DispBit > 8)return ERROR; // �ַ�����
	
	if((Data >= '0') && (Data <= '9')) // ����
	{
		DisL = LCD_DISP_TAB[Data - '0'] >> 4;
		// �������Ҫ�ų����λ�ĸ��ţ�����Ӱ�쵽���ֵ���ʾ��
		DisH = LCD_DISP_TAB[Data - '0'] & 0x0f;
	}
	else if((Data >= 'A') && (Data <= 'F'))  // ��ĸ��ʾ
	{
		DisL = LCD_ABC_TAB[Data - 'A'] >> 4;
		// �������Ҫ�ų����λ�ĸ��ţ�����Ӱ�쵽���ֵ���ʾ��
	    DisH = LCD_ABC_TAB[Data - 'A'] & 0x0f;
	}	
	else if(Data == '-')// ��ʾ����
	{
		DisL = LCD_SpecificTAB[0] >> 4;
		DisH = LCD_SpecificTAB[0] & 0x0f;	
	}
	else if(Data == ' ') // ��λ��ʾ�ո�
	{
		DisL = LCD_SpecificTAB[1] >> 4;
		DisH = LCD_SpecificTAB[1] & 0x0f;		
	}
//	else if(Data == '.') // С������ʾ
//	{
//		switch(DispBit){  // С��λ˳�򣺴��ҵ���
		
//			case(5):{
				
//				LCD_DisplayUnit(Right_Dot1,ENABLE);
				
//			};return CORRECT; // ��ȷ��ʾ
			
//			case(4):{
				
//				LCD_DisplayUnit(Right_Dot2,ENABLE);
				
//			};return CORRECT; // ��ȷ��ʾ
			
//			case(3):{
				
//				LCD_DisplayUnit(Right_Dot3,ENABLE);
				
//			};return CORRECT; // ��ȷ��ʾ
			
//			case(2):{
				
//				LCD_DisplayUnit(Right_Dot4,ENABLE);
				
//			};return CORRECT; // ��ȷ��ʾ
			
//			case(1):{
				
//				LCD_DisplayUnit(Right_Dot5,ENABLE);
				
//			};return CORRECT; // ��ȷ��ʾ
//			default:return ERROR; // ������
//		}
//	}
	else
	return ERROR; // ������ʾ����
	
	//XY_LCD_DisplayClearBIT(DispBit);  // �����λ��ʾ������ʾ��
	
	// ��ʾ����
	switch(DispBit)
	{
	case(0):
	{	
		SEG0 = DisH;// ���λΪ1����ʾ����:�ۻ�
		SEG1 |= DisL;  
	};break;
	case(1):
	{	
		SEG2 = DisH;// ���λ=1��ʾ���֣�����
		SEG3 |= DisL;  
	};break;
	case(2):
	{	
		SEG7 = DisH;// ���λ=1��ʾ���֣�����
		SEG8 |= DisL;
	};break;
	case(3):
	{	
		SEG11 = DisH;// ���λ=1��ʾ���֣�����
		SEG12 |= DisL;
	};break;
	case(4):
	{	
		SEG16 = DisH;// ���λ=1��ʾ���֣���ˮ
		SEG17 |= DisL;
	};break;
	case(5):
	{	
		SEG18 = DisH; // ���λ=1��ʾ��ǰһλλ��������º���
		SEG19 |= DisL;
	};break;
	case(6):
	{	
		SEG20 = DisH;// ���λ=1��ʾ���֣���ˮ
		SEG21 |= DisL;
	};break;
	case(7):
	{	
		SEG22 = DisH;// ���λ=1��ʾ��ǰһλλ��������º���
		SEG23 |= DisL;
	};break;
	}
	return CORRECT; // ��ȷ��ʾ
}



/*------------------------------------------------------
// �������ܣ��ַ�����ʾ���������䣺[0,9]||[A,F] || '-'
// �������룺����һλ��ʼ��ʾ[0,7)
// �������룺Ҫ��ʾ���ַ���
// �����������
// �������ͣ�������ʾ����ʱ���ַ����֣���ĸ�����д
-------------------------------------------------------*/
void LCD_Disp_String(unsigned char StartPoint,char *Str)
{
	//XY_LCD_DisplayClear(); // �����ʾ
	while(*Str != '\0')
	LCD_Disp1ByteBit(StartPoint++,*Str++);
}

/*------------------------------------------------------
// �������ܣ�������ʾ
// �������룺StartPoint ����һλ��ʼ��ʾ[0,7)
// �������룺Disp_VAL Ҫ��ʾ�з��ų�����ֵ
// �����������
// �������ͣ���
-------------------------------------------------------*/
void LCD_Disp_Num(unsigned char StartPoint,long long Disp_VAL,unsigned char Len)
{
	char Char_Temp[8] = { 0 };
	unsigned char i = 0;
	
	unsigned char flag = 0;  // ��ʶ����
	
	//XY_LCD_DisplayClear(); 
	
	if(Disp_VAL < 0)  // ����
	{
		Disp_VAL = -Disp_VAL;
		flag = 1;
	}
	
	XY_LCD_DisplayClearLen(StartPoint,Len + 0);// �����ʾ��2021���ģ������1�ĳ���0��
	
	if(USER_LCD_USE_FILL == LCD_USE_VOID){   // ʹ�ÿ��ַ����Ǳ��������λ��
		
	sprintf(Char_Temp,"%lld",Disp_VAL); // ������������
	Len = strlen(Char_Temp);
	
	}
	
	switch(Len)
	{
		
		case(8):
		{
			Char_Temp[i++] = Disp_VAL / 10000000 % 10 + '0'; // ǧ��λ
		};
		case(7):
		{
			Char_Temp[i++] = Disp_VAL / 1000000 % 10 + '0'; // ����λ	
		}; 
		case(6):
		{
			Char_Temp[i++] = Disp_VAL / 100000 % 10 + '0'; // ʮ��λ
		};
		case(5):
		{
			Char_Temp[i++] = Disp_VAL / 10000 % 10 + '0'; // ��λ	
		};
		case(4):
		{
			Char_Temp[i++] = Disp_VAL / 1000 % 10 + '0'; // ǧλ	
		};
		case(3):
		{
			Char_Temp[i++] = Disp_VAL / 100 % 10 + '0'; // ��λ	
		};
		case(2):
		{
			Char_Temp[i++] = Disp_VAL / 10 % 10 + '0'; // ʮλ
		};
		case(1):
		{
			Char_Temp[i] = Disp_VAL % 10 + '0';   // ��λ
		};break;
		
	}
	
	LCD_Disp_String(7-(StartPoint+Len-1),Char_Temp); // ��ֵ��ʾ
	
	if(1 == flag) // �����ӷ��ţ�����ǰ����������¿��������Ŵ��������á�
	{
		flag = '-';
	}
	else  // ������������������λ�ġ����š���ʾ
	{
		flag = ' ';
	}
	LCD_Disp1ByteBit(7-(StartPoint+Len),flag); // ����λ��ʾ����
}

// ���� a^b ��ֵ
static long int Count_a_b(unsigned char a,unsigned char b)
{
	long int Resualt = a;

	if(!b)return 1; // ����
	if(--b)
	Resualt *= Count_a_b(a,b); // �ݹ�
	
	return Resualt;
}

void __del_alldot__(void) // �Ƴ�С����;Ӧ�ó�����������ʾһ�ɲ�ʹ��С����
{
	LCD_DisplayUnit(Right_Dot1,DISABLE);
	LCD_DisplayUnit(Right_Dot2,DISABLE);
	LCD_DisplayUnit(Right_Dot3,DISABLE);
	LCD_DisplayUnit(Right_Dot4,DISABLE);
	LCD_DisplayUnit(Right_Dot5,DISABLE);	
}


// С�����λ�ã����ڸ�������ʾ��С������λѡ��
void LCD_DotLens(unsigned char dotlen)
{
	switch(dotlen) // С������λ
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
		default://�����ڴ˲���
		return;
	}
}



/*--------------------------------------------------------------------
// �������ܣ���������ʾ
// �������룺FVal Ҫ��ʾ�ĸ�����
// �������룺IntLen Ҫ��ʾ�ĸ������������ֳ���;��Χ��[1,8]
// �������룺DotLen Ҫ��ʾ�ĸ�����С�����ֳ��ȣ����д�����������;��Χ��[1,5]
// �����������
// �������ͣ���������ʾĬ�ϴ����Ҳ࿪ʼ��Ϊ��ʵ��ʾ��
// �����������ո�������С��1����ʾ��ȫ�����ѽ����
---------------------------------------------------------------------*/
void LCD_DoubleDisplayMode1(double FVal,unsigned char IntLen,unsigned char DotLen)
{
    long long Disp_VAL = Count_a_b(10,DotLen) * FVal; // ��Ч��ֵ������,�����������봦��

	unsigned char Len = 0;
	char Char_Temp[8] = { 0 };
	unsigned char i = 0;
	//unsigned char strlens = IntLen + DotLen; // ������
	unsigned char flag = 0;  // ��ʶ����
	unsigned char cn0 = 0;
	
	if(Disp_VAL < 0)  // ����
	{
		Disp_VAL = -Disp_VAL;
		flag = 1;
	}
	
	sprintf(Char_Temp,"%lld",Disp_VAL); // ��������������
	Len = strlen(Char_Temp); // ʵ�ʳ���

	XY_LCD_DisplayClearLen(0u,IntLen + DotLen + 0);// �����ʾ��2021���ģ������1�ĳ���0��
	
	i = 0;
	if((FVal < 1) && (FVal > -1))  // 0<x<1 ������ʾ���⴦��
	{
		
			while(i < DotLen - (Len - 1)){
				
			LCD_Disp1ByteBit(7 - Len - i++,'0');
			cn0++; // �������ŵ�λ��
			}
	}
	
	i = 0;
	// �����ֵ������ʾ��Χ
	if(Disp_VAL > 10000000){
	__del_alldot__();	// 	�Ƴ�С����
	return;  // ������Χ����ʾ
	}
	
	switch(Len) 
	{
		
		case(8):
		{
			Char_Temp[i++] = Disp_VAL / 10000000 % 10 + '0'; // ǧ��λ
		};
		case(7):
		{
			Char_Temp[i++] = Disp_VAL / 1000000 % 10 + '0'; // ����λ	
		}; 
		case(6):
		{
			Char_Temp[i++] = Disp_VAL / 100000 % 10 + '0'; // ʮ��λ
		};
		case(5):
		{
			Char_Temp[i++] = Disp_VAL / 10000 % 10 + '0'; // ��λ	
		};
		case(4):
		{
			Char_Temp[i++] = Disp_VAL / 1000 % 10 + '0'; // ǧλ	
		};
		case(3):
		{
			Char_Temp[i++] = Disp_VAL / 100 % 10 + '0'; // ��λ	
		};
		case(2):
		{
			Char_Temp[i++] = Disp_VAL / 10 % 10 + '0'; // ʮλ
		};
		case(1):
		{
			Char_Temp[i] = Disp_VAL % 10 + '0';   // ��λ
		};break;
		
	}
	
	LCD_Disp_String(7-(Len-1),Char_Temp); // ��ֵ��ʾ
	
	if(1 == flag) // �����ӷ��ţ�����ǰ����������¿��������Ŵ��������á�
	{
		flag = '-';
	}
	else  // ������������������λ�ġ����š���ʾ
	{
		flag = ' ';
	}
	LCD_Disp1ByteBit(7 - Len - cn0,flag); // ����λ��ʾ����
	
	LCD_DotLens(DotLen); // С����λ��
	
}

//// ������ʾ��ʽ2
//void LCD_DoubleDisplayMode2(double FVal,unsigned char IntLen,unsigned char DotLen)
//{
//	char _temp_str[9] = { 0 };
//	unsigned char len = 0;
////    long long Num = Count_a_b(10,DotLen) * FVal + 0.5f; // ��Ч��ֵ������,���������봦��
	
////	XY_LCD_DisplayClearLen(0u,IntLen + DotLen + 1);// �����ʾ
	
//	//#define CONTROL_CHARP(_IntLen,_DotLen)  #%##_IntLen##.##_DotLen##f
//	//#define CONTROL_CHARP(_IntLen,_DotLen) %##_IntLen##._DotLen##f
////	#define _IntLen 1
////	#define _DotLen 1
	
//	sprintf(_temp_str,"%3.2f",FVal); // ����������
////	//len = strlen(_temp_str) - 1;
//	LCD_Disp_String(0,_temp_str); // ��ֵ��ʾ	
////	LCD_DotLens(DotLen); // С����λ��
	
//}


//// ������ʾ��ʽ3
//void LCD_DoubleDisplayMode2(double FVal,unsigned char IntLen,unsigned char DotLen)
//{
////	char _temp_str[9] = { 0 };
////	char _ctrstr[9];
	
//	// 1.�������ֳ�������
//	// 2.С�����ֳ�������
//	// 3.�ϲ��ַ���������ת�����ַ���
//	// 4.ȥ��С����
//	// 5.������ʾ
//	//XY_LCD_DisplayClearLen(0u,IntLen + DotLen + 1);// �����ʾ	
//	//sprintf(_temp_str,CtrStr,Num); // ����������
	
//	//LCD_Disp_String(7 - len,_temp_str); // �ַ�����ʾ	
	
//	LCD_DotLens(DotLen); // С����λ��
	
//}



/*------------------------------------------------------
// �������ܣ�10����������ʾ����������ʽ��
// �������룺StartPoint ����һλ��ʼ��ʾ[0,7)
// �������룺Disp_VAL Ҫ��ʾ�з��ų�����ֵ
// �����������
// �������ͣ����ԶԱ�ִ���ٶ�.ʾ���� {�հ����}
-------------------------------------------------------*/
void LCD_Disp_To10Num(unsigned char StartPoint,long long Disp_VAL,unsigned char Len)
{
	char Char_Temp[8] = { 0 };
	unsigned char flag = 0u;

	if(Disp_VAL < 0){
		Disp_VAL = -Disp_VAL;
		flag = 1;
	}	

	XY_LCD_DisplayClearLen(StartPoint,Len + 0);// �����ʾ��2021���ģ������1�ĳ���0��
	
	sprintf(Char_Temp,"%lld",Disp_VAL); // ����10���ƴ���
	Len = strlen(Char_Temp);
	
	LCD_Disp_String(7-(StartPoint+Len-1),Char_Temp); // ��ֵ��ʾ
	if(1 == flag) // �����ӷ��ţ�����ǰ����������¿��������Ŵ��������á�
	{
		flag = '-';
	}
	else  // ������������������λ�ġ����š���ʾ
	{
		flag = ' ';
	}
	LCD_Disp1ByteBit(7-(StartPoint+Len),flag); // ����λ��ʾ����
}

/*------------------------------------------------------
// �������ܣ�ת��ΪHEX������ʾ
// �������룺StartPoint ����һλ��ʼ��ʾ[0,7)
// �������룺Disp_VAL Ҫ��ʾ�з��ų�����ֵ
// �����������
// �������ͣ�{�հ����};ֻ����ʾ����
-------------------------------------------------------*/
void LCD_Disp_ToHEX(unsigned char StartPoint,unsigned long long Disp_VAL,unsigned char Len)
{
	char Char_Temp[8] = { 0 };

	
	XY_LCD_DisplayClearLen(StartPoint,Len + 0);// �����ʾ��2021���ģ������1�ĳ���0��
	
	sprintf(Char_Temp,"%llX",Disp_VAL); // ����HEX����
	Len = strlen(Char_Temp);
	
	LCD_Disp_String(7-(StartPoint+Len-1),Char_Temp); // ��ֵ��ʾ
	
}


/*------- ���ܺ�������������������ʾ�������� ------*/

void LCD_VOID(void)
{}

/*
unsigned char LCD_Disp1ByteBit(unsigned char DispBit,unsigned char Data);
�����Ż����һ�����������Ϻ�����һ��Ϊ��ֵ��ʾ�������µ�������ʾ�ĺ����������ִ���ٶȣ����͹��ġ�

*/