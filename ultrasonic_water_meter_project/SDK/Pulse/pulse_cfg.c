#include "pulse_cfg.h"

//===ȫ�ֱ�������
PULSE_HandleType					g_pulse_one = {0};
pPULSE_HandleType					p_pulse_one=&g_pulse_one;

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_init_one(PULSE_HandleType* Pulsex, uint32_t(*func_time_tick)(void))
{	
	//--->>>���ö˿��ж�---��ʼ
//	//---��ʹ���ж�
//	PMK5 = 1U;   
//	//---����жϱ�־
//	PIF5 = 0U;    
//
//	//---�����ж����ȼ�
//	PPR15 = 0U;
//	PPR05 = 1U;
//
//#if (PULSE_ACTIVE_LEVEL_ONE==ACTIVE_LEVEL_LOW)
//	//---���������ش����ж�
//	EGP0 &= ~_20_INTP5_EDGE_RISING_SEL;
//	//---ʹ���½��ش����ж�
//	EGN0 |= _20_INTP5_EDGE_FALLING_SEL;
//#elif (PULSE_ACTIVE_LEVEL_ONE==ACTIVE_LEVEL_HIGH)
//	//---�����½����ж�����Ĵ���
//	EGN0 &= ~_20_INTP5_EDGE_FALLING_SEL;
//	//---ʹ�������ش����ж�
//	EGP0 |= _20_INTP5_EDGE_RISING_SEL;
//#else
//#error "��֧�ֵĴ����ж�����!"
//#endif
//	//---����KeyΪ����ģʽ������ʹ��
//	gpio_task_pin_mode_input(PULSE_PORT_ONE, PULSE_BIT_ONE);
//#if (PULSE_ACTIVE_LEVEL_ONE==ACTIVE_LEVEL_LOW)
//	gpio_task_pin_mode_pull_up_set(PULSE_PORT_ONE, PULSE_BIT_ONE);
//#endif
//
//	//---����жϱ�־
//	PIF5 = 0U;
//	//---ʹ���ж�
//	PMK5 = 0U;

	//--->>>���ö˿��ж�---��ʼ
	//---��ʹ���ж�
	PMK7 = 1U;    /* disable INTP7 operation */
	//---����жϱ�־
	PIF7 = 0U;    /* clear INTP7 interrupt flag */

	//---�����ж����ȼ�
	PPR17 = 0U;
	PPR07 = 1U;

	//---�����½��ش���
#if (PULSE_ACTIVE_LEVEL_ONE==ACTIVE_LEVEL_LOW)
	//---���������ش����ж�
	EGP0 &= ~_80_INTP7_EDGE_RISING_SEL;
	//---ʹ���½��ش����ж�
	EGN0 |= _80_INTP7_EDGE_FALLING_SEL;
#elif (PULSE_ACTIVE_LEVEL_ONE==ACTIVE_LEVEL_HIGH)
	//---�����½��ش����ж�
	EGN0 &= ~_80_INTP7_EDGE_FALLING_SEL;
	//---ʹ�������ش����ж�
	EGP0 |= _80_INTP7_EDGE_RISING_SEL;
#else
	#error "��֧�ֵĴ����ж�����!"
#endif
	//---����INTΪ����ģʽ������ʹ��
	gpio_task_pin_mode_input(PULSE_PORT_ONE, PULSE_BIT_ONE);

#if (PULSE_ACTIVE_LEVEL_ONE==ACTIVE_LEVEL_LOW)
	gpio_task_pin_mode_pull_up_set(PULSE_PORT_ONE, PULSE_BIT_ONE);
#endif

	//---����жϱ�־
	PIF7 = 0U;
	//---ʹ���ж�
	PMK7 = 0U;

	//---������Ч��ƽ
	Pulsex->msg_level_active = PULSE_ACTIVE_LEVEL_ONE;
	//---ע��˿ڵ�ƽ��ȡ����
	Pulsex->msg_f_level = pulse_level_one;
	//---ע��δ���
	(func_time_tick != NULL) ?
		(Pulsex->msg_f_time_tick = func_time_tick) :
		(Pulsex->msg_f_time_tick = sys_tick_task_get_tick);

	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_init_two(PULSE_HandleType* Pulsex, uint32_t(*func_time_tick)(void))
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_init_three(PULSE_HandleType* Pulsex, uint32_t(*func_time_tick)(void))
{

	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_start_one(PULSE_HandleType* Pulsex)
{	
	////---����жϱ�ʶ
	//PIF5 = 0U;
	////---ʹ���ж�
	//PMK5 = 0U;
	//---����жϱ�ʶ
	PIF7 = 0U;
	//---ʹ���ж�
	PMK7 = 0U;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_start_two(PULSE_HandleType* Pulsex)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_start_three(PULSE_HandleType* Pulsex)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_stop_one(PULSE_HandleType* Pulsex)
{
	////---��ʹ���ж�
	//PMK5 = 1U;
	////---����жϱ�ʶ
	//PIF5 = 0U;
	//---��ʹ���ж�
	PMK7 = 1U;
	//---����жϱ�ʶ
	PIF7 = 0U;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_stop_two(PULSE_HandleType* Pulsex)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_stop_three(PULSE_HandleType* Pulsex)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_rising_edge_one(PULSE_HandleType* Pulsex)
{
	////---�����½��ش����ж�
	//EGN0 &= ~_20_INTP5_EDGE_FALLING_SEL;
	////---ʹ�������ش����ж�
	//EGP0 |= _20_INTP5_EDGE_RISING_SEL;
	//---�����½��ش����ж�
	EGN0 &= ~_80_INTP7_EDGE_FALLING_SEL;
	//---ʹ�������ش����ж�
	EGP0 |= _80_INTP7_EDGE_RISING_SEL;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_falling_edge_one(PULSE_HandleType* Pulsex)
{
	////---�����������ж�����Ĵ���
	//EGP0 &= ~_20_INTP5_EDGE_RISING_SEL;
	////---ʹ���½��ش����ж�
	//EGN0 |= _20_INTP5_EDGE_FALLING_SEL;
	//---���������ش����ж�
	EGP0 &= ~_80_INTP7_EDGE_RISING_SEL;
	//---ʹ���½��ش����ж�
	EGN0 |= _80_INTP7_EDGE_FALLING_SEL;
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_level_one(void)
{
	return (uint8_t)((PULSE_PORT_ONE != NULL) ? (PIN_GET_STATE(PULSE_PORT_ONE, PULSE_BIT_ONE)) : 0);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_it_irq_handle_one(PULSE_HandleType* Pulsex)
{
	//---����������
	Pulsex->msg_actice = 1;
	//---ֹͣ�жϹ���
	pulse_stop_one(Pulsex);
	//---��¼��ǰ�ļ�������
	Pulsex->msg_acticve_record = Pulsex->msg_f_time_tick();
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_it_irq_handle_two(PULSE_HandleType* Pulsex)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_it_irq_handle_three(PULSE_HandleType* Pulsex)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ������������
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_driver_one(PULSE_HandleType* Pulsex)
{
	if (Pulsex->msg_actice!=0)
	{
		if (Pulsex->msg_f_level!=NULL)
		{
			//---��ȡ��ǰ����״̬
			Pulsex->msg_level_value = Pulsex->msg_f_level();
			//---��������
			switch (Pulsex->msg_level_step)
			{
				//---�������仯
				case 0:
				{
					//---У�鰴����Ч��
					if (Pulsex->msg_level_value == Pulsex->msg_level_active)
					{
						//---��¼ʱ��
						Pulsex->msg_level_record = Pulsex->msg_f_time_tick();
						//---���밴������
						Pulsex->msg_level_step = 1;
					}
					else
					{
						//---û�а�������
						Pulsex->msg_level_state = ACTIVE_STATE_DISABLE;
					}
					break;
				}
				//---������������
				case 1:
				{
					//---У�鰴����Ч��
					if (Pulsex->msg_level_value == Pulsex->msg_level_active)
					{
						//---У����������ʱ���Ƿ񵽴�
						if (TIME_SPAN(Pulsex->msg_f_time_tick(), Pulsex->msg_level_record) > PULSE_ACTIVE_TIME_STABLE)
						{
							//---��¼ʱ��
							Pulsex->msg_level_record = Pulsex->msg_f_time_tick();
							//---����ʱ�䳬��������ʱ�䣬�жϰ�����Ч��ȥ�жϰ�����״̬
							Pulsex->msg_level_step = 0;
							//---�������źţ�����ɨ��
							Pulsex->msg_level_state = ACTIVE_STATE_ENABLE;
							//---���㼤��״̬
							Pulsex->msg_actice = 0;
						}
					}
					else
					{
						//---״̬���㣬����ɨ�谴��
						Pulsex->msg_level_step = 0;
						//---�������źţ�����ɨ��
						Pulsex->msg_level_state = ACTIVE_STATE_DISABLE;
					}
					break;
				}
				default:
				{
					//---״̬���㣬����ɨ�谴��
					Pulsex->msg_level_step = 0;
					//---�������źţ�����ɨ��
					Pulsex->msg_level_state = ACTIVE_STATE_DISABLE;
					//---���㼤��״̬
					Pulsex->msg_actice = 0;
					//---������һ�εļ���
					pulse_start_one(Pulsex);
					break;
				}
			}
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_driver_two(PULSE_HandleType* Pulsex)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_driver_three(PULSE_HandleType* Pulsex)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ɨ������仯�Ƿ���Ч
//////�����	��:
//////�����	��: 0,���������壬1��û�м���������
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_scan_one(PULSE_HandleType* Pulsex)
{
	pulse_driver_one(Pulsex);
	//---�жϵ�ƽ�仯�Ƿ���Ч
	if (Pulsex->msg_level_state ==ACTIVE_STATE_ENABLE)
	{
		Pulsex->msg_level_count++;
		//---�����ƽ��Ч��ʶ
		Pulsex->msg_level_state = ACTIVE_STATE_DISABLE;
		//---������һ�ε����崥��
		pulse_start_one(Pulsex);
		//---���ؽ��
		return OK_0;
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_scan_two(PULSE_HandleType* Pulsex)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_scan_three(PULSE_HandleType* Pulsex)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_scan(PULSE_HandleType* Pulsex)
{
	if ((Pulsex != NULL) && (Pulsex == PULSE_TASK_ONE))
	{
		return pulse_scan_one(Pulsex);
	}
	if ((Pulsex != NULL) && (Pulsex == PULSE_TASK_TWO))
	{
		return pulse_scan_two(Pulsex);
	}
	if ((Pulsex != NULL) && (Pulsex == PULSE_TASK_THREE))
	{
		return pulse_scan_three(Pulsex);
	}
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_time_tick_init(PULSE_HandleType* Pulsex, uint32_t(*func_time_tick)(void))
{
	//---ע��δ���
	(func_time_tick != NULL) ?
		(Pulsex->msg_f_time_tick = func_time_tick) :
		(Pulsex->msg_f_time_tick = sys_tick_task_get_tick);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t pulse_init(PULSE_HandleType* Pulsex, uint32_t(*func_time_tick)(void))
{
	if ((Pulsex != NULL) && (Pulsex == PULSE_TASK_ONE))
	{
		return pulse_init_one(Pulsex,func_time_tick);
	}
	if ((Pulsex != NULL) && (Pulsex == PULSE_TASK_TWO))
	{
		return pulse_init_two(Pulsex,func_time_tick);
	}
	if ((Pulsex != NULL) && (Pulsex == PULSE_TASK_THREE))
	{
		return pulse_init_three(Pulsex,func_time_tick);
	}
	return ERROR_2;
}
