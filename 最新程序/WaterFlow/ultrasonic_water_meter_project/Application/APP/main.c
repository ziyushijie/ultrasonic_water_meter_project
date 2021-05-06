#include "main.h"
#include "dbg.h"
/*---------------------------------------------------------------------------------
* 说明文件：
* 中断相关优先级配置：设为宏可配置，方便后续更改调节，以得到最优方案。
----------------------------------------------------------------------------------*/
void event_dkey(int* e);

char usart_test_disp[50];  // 测试显示所用的缓冲区

uint8_t buf_test[10] = { 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0xa0 };
uint8_t test_rbuf;

unsigned char ms1022_id[7];  // ID寄存器

void main(void)
{
	int i = 0;
//	unsigned char ref_buf[10] = { 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0xa0 };
//	LCD_Unit exe_display;
	hdwinit();
	//clear_lcd(); 
	//XY_LCD_DisplayClear();
	//XY_LCD_Display_ALL();
	//XY_LCD_DisplayClearLen(0,2);
	//IrDA_PowerControl(IRDA_POWER_ON);
	
	//R_UART1_Receive(buf_test,10U);
	R_UART2_Receive(buf_test,1U);
	//DBG_SendString("系统初始化成功！\r\n");
	//DBG_SendString("123！\r\n");
	R_UART1_Send("123\r\n",6);
		Delay_ms(50U);
		R_UART1_Send("234\r\n",6);
	//MS1022_Read_ID(ms1022_id);

	while(1)
	{
	}
	
//	while(1)
//	{
	
//	//XY_LCD_Display_ALL();
		
//		CurrentTime_CNT();
//		DKEY_Scan(event_dkey);

////		exe_display = Bit6_UD_;
//		Delay_ms(50U);
////		LCD_DisplayUnit(exe_display,ENABLE);

////IrDA_PowerControl(IRDA_POWER_OFF);
////Delay_ms(200U);
//if(i++ % 20 == 0){  // 1s

////R_UART2_Send(ref_buf,10u);
	
////	R_UART1_Send(buf_test,10U);

////ON_MS1022_FOSC();

//MS1022_Read_ID(ms1022_id);

//Get_Temperature(); // 温度测量
//Get_Flow(); // 流体测量

//if(Get_TEMP.PT1000_STATE.PT1000_MeasureSTA == MS1022_TempMeasure_OK){
//	DBG_SendString("温度测量成功！\r\n");
//}
//else{
//	DBG_SendString("温度测量失败！\r\n");
//}

//// ID
//sprintf(usart_test_disp,"ID:%2X %2X %2X %2X %2X %2X %2X\r\n",ms1022_id[0],ms1022_id[1],ms1022_id[2],ms1022_id[3],ms1022_id[4],ms1022_id[5],ms1022_id[6]);
//DBG_SendString(usart_test_disp);

//sprintf(usart_test_disp,"进口温度：%7.3f\r\n",Get_TEMP.Temperature_In);
//DBG_SendString(usart_test_disp);

//sprintf(usart_test_disp,"出口温度：%7.3f\r\n",Get_TEMP.Temperature_Out);
//DBG_SendString(usart_test_disp);

//sprintf(usart_test_disp,"正向飞行时间：%7.3f\r\n",Get_Time.Forward_Time);
//DBG_SendString(usart_test_disp);

//sprintf(usart_test_disp,"逆向飞行时间：%7.3f\r\n",Get_Time.Reverse_Time);
//DBG_SendString(usart_test_disp);

//sprintf(usart_test_disp,"时间差：%7.3f\r\n",Get_Time.Time_Diff);
//DBG_SendString(usart_test_disp);

//sprintf(usart_test_disp,"流体速度：%7.3f\r\n",Get_FlowHeat.flow_speed);
//DBG_SendString(usart_test_disp);


////LCD_DoubleDisplayMode1(575.5566,3,2);
////LCD_DoubleDisplayMode1(0,3,3);
////LCD_DotLens(3);
////SEG35 = 0x01;
////SEG36 |= 0x01;
////DBG_SendString("OK---------------printf!");
//}

////Delay_ms(200U);

////		LCD_DisplayUnit(exe_display,DISABLE);
		
//		//DBG_SendString("发送测试\r\n");
//	//XY_LCD_Display_ALL();
////	SEG0 = 0x07;
////	SEG1 = 0x0f;
	
////	SEG2 = 0x07;
////	SEG3 = 0x0f;
	
////	SEG7 = 0x07;
////	SEG8 = 0x0f;

////	SEG11 = 0x07;
////	SEG12 = 0x0f;

////	SEG16 = 0x07;
////	SEG17 = 0x0f;

////	SEG18 = 0x07;
////	SEG19 = 0x0f;

////	SEG20 = 0x07;
////	SEG21 = 0x0f;

////	SEG22 = 0x0f;
////	SEG23 = 0x0f;

////SEG35 = 0x08;
////SEG36 = 0x08;
////SEG37 = 0x08;
////SEG38 = 0x08;
////	// 单位小数点等
////	SEG35 = 0xff;
////	SEG36 = 0xff;
////	SEG37 = 0xff;
////	SEG38 = 0xff;
////	SEG48 = 0x0f;
////	SEG49 = 0x0f;
////	i=0;
////#define disp_test_ascii(ascii)  #ascii


////	LCD_Disp_String(0,(char*)disp_test_ascii(33333333));
////	LCD_Disp1ByteBit(1,(unsigned char)disp_test_ascii(2));
////	LCD_Disp1ByteBit(2,'2');
////	LCD_Disp1ByteBit(3,'2');
////	LCD_Disp1ByteBit(4,'2');
////	LCD_Disp1ByteBit(5,'2');
////	LCD_Disp1ByteBit(6,'2');
////	LCD_Disp1ByteBit(7,'3');
////	i++;
////	if(i>255)i=0;
////	LCD_USE_0_FILL();
////	//LCD_DoubleDisplayMode2(234.563,0,0);
	
////	LCD_Disp_String(3,"23456");
	
//	///////////////////////////////////////////////////////////////
	
////	SEG0 = SEG1 = SEG2 = SEG3 = 0x0f;
////	SEG7=SEG8=0x0f;
////	SEG11=SEG12=0x0f;
////	SEG16=SEG17=SEG18=SEG19=SEG20=SEG21=SEG22=SEG23=0X0F;
////	SEG35=SEG36=SEG37=SEG38=0x0f;
	
////	SEG33=0x0f;//!
////	SEG34=0x0f;//!

////SEG34 = 0x01;
//	}
}


void event_dkey(int* e){
	
	switch(*e){
	
		case(DKEY_Up):{
		
		LCD_DoubleDisplayMode1(234.563,3,3);
		DBG_SendString("发送测试=1，单次弹起！\r\n");
			
		};break;
		
		case(DKEY_LongDown):{
			
		LCD_DoubleDisplayMode1(657.565,3,3);
		DBG_SendString("发送测试=2,长按！\r\n");
			
		};break;
		
	}
	
}

