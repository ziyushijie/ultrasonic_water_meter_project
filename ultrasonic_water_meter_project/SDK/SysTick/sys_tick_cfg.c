#include "sys_tick_cfg.h"

//---��������
SYS_TICK_HandleType			g_sys_tick_one = { 0 };
pSYS_TICK_HandleType		p_sys_tick_one = &g_sys_tick_one;

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: �δ��ʼ������
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t sys_tick_init(SYS_TICK_HandleType *systickx)
{
	rl78_perpheral_clock_enable(PERIPHERAL_TIMER);
	//---֧�ֵ�����ʱ��
#if (SYS_TICK_MIN_PULSE_WIDTH<=8)
	TPS0 =	_0000_TAU_CKM0_fCLK_0 | 
			_0000_TAU_CKM1_fCLK_0 | 
			_0000_TAU_CKM2_fCLK_1 | 
			_0000_TAU_CKM3_fCLK_8;
#else
	TPS0 =	_0003_TAU_CKM0_fCLK_3 | 
			_0000_TAU_CKM1_fCLK_0 | 
			_0000_TAU_CKM2_fCLK_1 | 
			_0000_TAU_CKM3_fCLK_8;
#endif
	//---ֹͣͨ��2
	TT0 |= _0004_TAU_CH2_STOP_TRG_ON;
	//---��ʹ���ж�
	TMMK02 = 1U;    
	//---����жϱ�־λ
	TMIF02 = 0U;    
	
	//---�ж����ȼ�����
	TMPR102 = 1U;
	TMPR002 = 1U;

	//---ʱ��ѡ��CKM0.
	TMR02 = _0000_TAU_CLOCK_SELECT_CKM0 |
			_0000_TAU_CLOCK_MODE_CKS |
			_0000_TAU_COMBINATION_SLAVE |
			_0000_TAU_TRIGGER_SOFTWARE |
			_0000_TAU_MODE_INTERVAL_TIMER |
			_0001_TAU_START_INT_USED;

	//---����ʱ�ӵ�ѡ��
#if (SYS_TICK_MIN_PULSE_WIDTH<=8)
	//---ϵͳ���Ķ���
#if (SYS_TICK_MIN_PULSE_WIDTH==1)
	TDR02 = (SYS_CLOCK_KHZ - 1);
#elif (SYS_TICK_MIN_PULSE_WIDTH==2)
	TDR02 = (SYS_CLOCK_KHZ * 2 - 1);
#elif (SYS_TICK_MIN_PULSE_WIDTH==4)
	TDR02 = (SYS_CLOCK_KHZ * 4 - 1);
#elif (SYS_TICK_MIN_PULSE_WIDTH==8)&&(SYS_CLOCK_KHZ<=8000UL)
	TDR02 = (SYS_CLOCK_KHZ * 8 - 1);
#else
	#error "��֧�ֵĵδ��������!\r\n"
#endif

#else

	//---ϵͳ���Ķ���
#if (SYS_TICK_MIN_PULSE_WIDTH==1)
	TDR02 = (SYS_CLOCK_KHZ/8 - 1);
#elif (SYS_TICK_MIN_PULSE_WIDTH==2)
	TDR02 = (SYS_CLOCK_KHZ * 2 /8- 1);
#elif (SYS_TICK_MIN_PULSE_WIDTH==4)
	TDR02 = (SYS_CLOCK_KHZ * 4/8 - 1);
#elif (SYS_TICK_MIN_PULSE_WIDTH==8)
	TDR02 = (SYS_CLOCK_KHZ * 8/8 - 1);
#elif (SYS_TICK_MIN_PULSE_WIDTH==10)
	TDR02 = (10000 - 1);
#else
	#error "��֧�ֵĵδ��������!\r\n"
#endif

#endif

	TOM0 &= ~_0004_TAU_CH2_OUTPUT_COMBIN;
	TOL0 &= ~_0004_TAU_CH2_OUTPUT_LEVEL_L;
	TO0 &= ~_0004_TAU_CH2_OUTPUT_VALUE_1;
	TOE0 &= ~_0004_TAU_CH2_OUTPUT_ENABLE;
	//---ʹ�ܵδ�ʱ��
	sys_tick_enable();
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ϵͳ�δ�ʹ��
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void sys_tick_enable(void)
{
	//---ʹ�ܶ�ʱ��
	TS0 |= _0004_TAU_CH2_START_TRG_ON;
	//---����жϱ�־λ
	TMIF02 = 0U;  
	//---ʹ���ж�
	TMMK02 = 0U;    /* enable INTTM02 interrupt */
	
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ϵͳ�δ�ʹ��
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void sys_tick_disable(void)
{
	//---��ʹ���ж�
	TMMK02 = 1U;  
	//---����жϱ�־λ
	TMIF02 = 0U;   
	//---ʹ�ܶ�ʱ��
	TT0 |= _0004_TAU_CH2_STOP_TRG_ON;

}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: �жϵδ�������
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t sys_tick_it_irq_handle(SYS_TICK_HandleType *systickx)
{
	//--->>>�ݼӼ�����������ϵͳ����
	systickx->msg_inc_count++;
	if (systickx->msg_inc_count==0)
	{
		//---�����־λ
		systickx->msg_inc_ovf++;
	}
	//---<<<�ݼӼ�����������ϵͳ����

	//--->>>�ݼ�������������ms
	if (systickx->msg_dec_count!=0)
	{
		systickx->msg_dec_count--;
	}
	//---<<<�ݼ�������������ms

	//--->>>������У����ڼ򵥵�����ִ��
	
	//---<<<������У����ڼ򵥵�����ִ��
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ȡ���������������
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint32_t sys_tick_get_inc_ovf(SYS_TICK_HandleType *systickx)
{
	return systickx->msg_inc_ovf;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ȡ������������ֵ
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint32_t sys_tick_get_inc_count(SYS_TICK_HandleType *systickx)
{
	return (systickx->msg_inc_count + 5);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ȡ������������ֵ
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint32_t sys_tick_get_tick(void)
{
	return sys_tick_get_inc_count(SYS_TICK_TASK_ONE);
}