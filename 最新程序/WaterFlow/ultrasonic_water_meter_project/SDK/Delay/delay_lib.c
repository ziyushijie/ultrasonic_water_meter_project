#include "delay_lib.h"


// �ο�ʱ�䣺XY_Delay(5000) && @8MHZ ��ִ��ʱ���� 4.3ms���ҡ�


void XY_Delay(unsigned long xtime)
{
	unsigned long i = 0,j = 0;
	for(i = 0;i<xtime;i++)
	{
	  for(j = 0;j<1000;j++);
	}
}


//void XY_Delay_10us(void)
//{
//	// �պ�����4.16us
//	// @10us-4.16us
//	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();	
//	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();	
//	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();	
//	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();	
//	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();	

//}


///*------------------------------------ 
//�������ܣ���ȷ��ʱ @8MHZ
//�������ƣ�SET_Delay_us
//�������룺Xus ��ȡֵ��Χ��[1,65535]
//�����������
//�������ͣ���ʱʱ�� = 10us * Xus
//-------------------------------------*/
void SET_Delay_us(unsigned int _10us_Xus)
{
	// �պ�����4.16us
	while(_10us_Xus--)
	if(0u == _10us_Xus){

	#if(SYS_CLK == CPU_CLK_8MHZ)
	// @10us-4.16us
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();	
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
	
	#elif (SYS_CLK == CPU_CLK_16MHZ)
	
		// @10us-4.16us
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();	
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();	
	// @10us-4.16us
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();	
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
	
	
	#endif  /*-- @CPU_CLK_16MHZ --*/
	}
	else{
		
	#if(SYS_CLK == CPU_CLK_8MHZ)
		
	// @10us
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();	
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();	
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();	
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();	
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();		
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();	
	NOP();NOP();NOP();NOP();NOP();
	
	#elif(SYS_CLK == CPU_CLK_16MHZ)
	
		// @10us
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();	
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();	
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();	
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();	
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();		
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();	
	NOP();NOP();NOP();NOP();NOP();
	
			// @10us
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();	
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();	
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();	
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();	
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();		
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();	
	NOP();NOP();NOP();NOP();NOP();
	
	
	#endif
	
	}

}

void Delay_ms(unsigned int xms)
{
	while(xms--)
	SET_Delay_us(100);//1ms
	//SET_Delay_us(SYS_CLK);//1ms
}


