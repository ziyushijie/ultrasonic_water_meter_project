#include "key_cfg.h"

//===ȫ�ֱ�������
KEY_HandleType		g_key_one = {0};
pKEY_HandleType		p_key_one=&g_key_one;

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ʼ������1
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t key_init_one(KEY_HandleType* KEYx,uint32_t(*func_time_tick)(void))
{
#if (KEY_BUTTON_MAX_NUM > 1)
	uint8_t button_index = 0;
	for (button_index=0;button_index<KEY_BUTTON_MAX_NUM;button_index++)
	{
		//---ע��˿ڵ�ƽ��ȡ����
		KEYx->msg_button[button_index].msg_f_pin_level = key_pin_level_one;
		//---ע��δ���
		(func_time_tick != NULL) ?
			(KEYx->msg_button[button_index].msg_f_time_tick = func_time_tick) :
			(KEYx->msg_button[button_index].msg_f_time_tick = sys_tick_task_get_tick);
		//---��������״̬�����
		switch (button_index)
		{
			case 0:
			{
				KEYx->msg_button[button_index].msg_pin_index = KEY_BUTTON_INDEX_ONE_K1;
				//---������Ч��ƽ
				KEYx->msg_button[button_index].msg_pin_level_active = KEY_BUTTON_ACTIVE_LEVEL_ONE_K1;
				break;
			}
			case 1:
			{
				KEYx->msg_button[button_index].msg_pin_index = 1;
				//---������Ч��ƽ
				KEYx->msg_button[button_index].msg_pin_level_active = KEY_BUTTON_ACTIVE_LEVEL_ONE_K1;
				break;
			}
			case 2:
			{
				break;
			}
			case 3:
			{
				break;
			}
			default:
				break;
		}
	}
#else
	//--->>>���ö˿��ж�---��ʼ
	//---��ʹ���ж�
	PMK0 = 1U;
	//---����жϱ�־
	PIF0 = 0U;

	//---�����ж����ȼ�
	PPR10 = 0U;
	PPR00 = 1U;

#if (KEY_BUTTON_ACTIVE_LEVEL_ONE_K1==ACTIVE_LEVEL_LOW)
	//---���������ش����ж�
	EGP0 &= ~_01_INTP0_EDGE_RISING_SEL;
	//---ʹ���½��ش����ж�
	EGN0 |= _01_INTP0_EDGE_FALLING_SEL;
#elif (KEY_BUTTON_ACTIVE_LEVEL_ONE_K1==ACTIVE_LEVEL_HIGH)
	//---�����½��ش����ж�
	EGN0 &=~ _01_INTP0_EDGE_FALLING_SEL;
	//---ʹ�������ش����ж�
	EGP0 |= _01_INTP0_EDGE_RISING_SEL;
#else
	#error "��֧�ֵĴ����ж�����!"
#endif
	//---����KeyΪ����ģʽ������ʹ��
	gpio_task_pin_mode_input(KEY_BUTTON_PORT_ONE_K1, KEY_BUTTON_BIT_ONE_K1);
#if (KEY_BUTTON_ACTIVE_LEVEL_ONE_K1==ACTIVE_LEVEL_LOW)
	gpio_task_pin_mode_pull_up_set(KEY_BUTTON_PORT_ONE_K1, KEY_BUTTON_BIT_ONE_K1);
#endif
	//---����жϱ�־
	PIF0 = 0U;
	//---ʹ���ж�
	PMK0 = 0U;

	KEYx->msg_button.msg_pin_index = KEY_BUTTON_INDEX_ONE_K1;
	//---������Ч��ƽ
	KEYx->msg_button.msg_pin_level_active = KEY_BUTTON_ACTIVE_LEVEL_ONE_K1;
	//---ע��˿ڵ�ƽ��ȡ����
	KEYx->msg_button.msg_f_pin_level = key_pin_level_one;
	//---ע��δ���
	(func_time_tick != NULL) ?
		(KEYx->msg_button.msg_f_time_tick = func_time_tick) :
		(KEYx->msg_button.msg_f_time_tick = sys_tick_task_get_tick);
#endif

	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t key_init_two(KEY_HandleType* KEYx, uint32_t(*func_time_tick)(void))
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
uint8_t key_init_three(KEY_HandleType* KEYx, uint32_t(*func_time_tick)(void))
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��������1�ж�
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t key_start_one(KEY_HandleType* KEYx,uint8_t index)
{
#if (KEY_BUTTON_MAX_NUM > 1)
	return ERROR_1;
#else
	//---����жϱ�ʶ
	PIF0 = 0U;    
	//---ʹ���ж�
	PMK0 = 0U;    
	return OK_0;
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ֹͣ����1�ж�
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t key_stop_one(KEY_HandleType* KEYx,uint8_t index)
{
#if (KEY_BUTTON_MAX_NUM > 1)
	return ERROR_1;
#else
	//---ʹ���ж�
	PMK0 = 1U;    
	//---����жϱ�ʶ
	PIF0 = 0U;   
	return OK_0;
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t key_rising_edge_one(KEY_HandleType* KEYx,uint8_t index)
{
#if (KEY_BUTTON_MAX_NUM > 1)
	return ERROR_1;
#else
	//---�����½����ж�����Ĵ���
	EGN0 &= ~_01_INTP0_EDGE_FALLING_SEL;
	//---ʹ�������ش����ж�
	EGP0 |= _01_INTP0_EDGE_RISING_SEL;
	return OK_0;
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t key_falling_edge_one(KEY_HandleType* KEYx, uint8_t index)
{
#if (KEY_BUTTON_MAX_NUM > 1)
	return ERROR_1;
#else
	//---�����������ж�����Ĵ���
	EGP0 &= ~_01_INTP0_EDGE_RISING_SEL;
	//---ʹ���½��ش����ж�
	EGN0 |= _01_INTP0_EDGE_FALLING_SEL;
	return OK_0;
#endif
}


///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t key_pin_level_one(uint8_t index)
{
#if (KEY_BUTTON_MAX_NUM>1)
	uint8_t _return = ERROR_FF;
	//---�ж����ĸ�����
	switch (index)
	{
		case 0:
		{
			_return = (uint8_t)((KEY_BUTTON_PORT_ONE_K1 != NULL) ? (PIN_GET_STATE(KEY_BUTTON_PORT_ONE_K1, KEY_BUTTON_BIT_ONE_K1)) : 0);
			break;
		}
		case 1:
		{
			break;
		}
		case 2:
		{
			break;
		}
		default:
		{
			break;
		}
	}
	return _return;
#else
	return (uint8_t)((KEY_BUTTON_PORT_ONE_K1 != NULL) ? (PIN_GET_STATE(KEY_BUTTON_PORT_ONE_K1, KEY_BUTTON_BIT_ONE_K1)) : 0);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t key_it_irq_handle_one(KEY_HandleType *KEYx, uint8_t index)
{
	//---ֹͣ�����ж�
	key_stop_one(KEYx,index);
	//---��ע�а�������
#if (KEY_BUTTON_MAX_NUM>1)
	return ERROR_1;
#else
	KEYx->msg_active = 1;
	return OK_0;
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ������������
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t key_driver_one(KEY_PRESS_HandleType* KEYx)
{
	if (KEYx->msg_f_pin_level!=NULL)
	{
		//---��ȡ��ǰ����״̬
		KEYx->msg_pin_level_value = KEYx->msg_f_pin_level(KEYx->msg_pin_index);
		//---��������
		switch (KEYx->msg_pin_level_step)
		{
			//---�ж����ް�������
			case 0:
			{
				//---У�鰴����Ч��
				if (KEYx->msg_pin_level_value== KEYx->msg_pin_level_active)
				{
					//---��¼ʱ��
					KEYx->msg_pin_level_record = KEYx->msg_f_time_tick();
					//---���밴������
					KEYx->msg_pin_level_step = 1;
				}
				else
				{
					//---û�а�������
					KEYx->msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
				}
				break;
			}
			//---����������
			case 1:
			{
				//---У�鰴����Ч��
				if (KEYx->msg_pin_level_value == KEYx->msg_pin_level_active)
				{
					if (TIME_SPAN(KEYx->msg_f_time_tick(), KEYx->msg_pin_level_record)> KEY_BUTTON_ACTIVE_TIME_STABLE)
					{
						//---��¼ʱ��
						KEYx->msg_pin_level_record = KEYx->msg_f_time_tick();
						//---����ʱ�䳬��������ʱ�䣬�жϰ�����Ч��ȥ�жϰ�����״̬
						KEYx->msg_pin_level_step = 2;
					}
				}
				else
				{
					//---״̬���㣬����ɨ�谴��
					KEYx->msg_pin_level_step = 0;
					//---�������źţ�����ɨ��
					KEYx->msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
				}
				break;
			}
			//---�жϵ������ǳ���
			case 2:
			{
				//---У�鰴����Ч��
				if (KEYx->msg_pin_level_value != KEYx->msg_pin_level_active)
				{
					//---�����ͷţ�������Ч״̬�ǵ���
					KEYx->msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_ONE;
					//---״̬��0������ɨ�谴��
					KEYx->msg_pin_level_step = 0;
				}
				else
				{
					//---����ʱ�䳬���趨�ĳ���ʱ��
					if (TIME_SPAN(KEYx->msg_f_time_tick(), KEYx->msg_pin_level_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_LONG)
					{
						//---������Ч״̬�ǳ���,�������ж��ǲ��ǳ�����
						KEYx->msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_LONG;
						//---����ʱ�䳬��������ʱ�䣬�жϰ�����Ч��ȥ�жϰ�����״̬
						KEYx->msg_pin_level_step = 3;
					}
				}
				break;
			}
			//---�жϳ������ǳ�������
			case 3:
			{
				//---У�鰴����Ч��
				if (KEYx->msg_pin_level_value != KEYx->msg_pin_level_active)
				{
					//---�����ͷţ�������Ч״̬�ǳ���
					KEYx->msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_LONG;
					//---״̬���㣬����ɨ�谴��
					KEYx->msg_pin_level_step = 0;
					//---�����¼�
#if (MODULE_LOG_KEY_BUTTON>0)
					LOG_VA_ARGS("����:����\r\n");
#endif
				}
				else
				{
					//---����ʱ�䳬���趨�ĳ���ʱ��
					if (TIME_SPAN(KEYx->msg_f_time_tick(), KEYx->msg_pin_level_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_LONG_LONG)
					{
						//---������Ч״̬�ǳ���
						KEYx->msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_LONG_LONG;
						//---����ʱ�䳬��������ʱ�䣬�жϰ�����Ч��ȥ�жϰ�����״̬
						KEYx->msg_pin_level_step = 4;
						//---�������¼�
#if (MODULE_LOG_KEY_BUTTON>0)
						LOG_VA_ARGS("����:������\r\n");
#endif
					}
				}
				break;
			}
			//---��������
			case 4:
			{
				if (KEYx->msg_pin_level_value == KEYx->msg_pin_level_active)
				{
					//---��¼ʱ��
					KEYx->msg_pin_level_record = KEYx->msg_f_time_tick();
					//---״̬���㣬����ɨ�谴��
					KEYx->msg_pin_level_step = 5;
					//---�����¼�
				}
				else
				{
					//---״̬���㣬����ɨ�谴��
					KEYx->msg_pin_level_step = 0;
				}
				break;
			}
			//---��������
			case 5:
			{
				if (KEYx->msg_pin_level_value == KEYx->msg_pin_level_active)
				{
					//---����ʱ�䳬���趨�Ĵ���ʱ��
					if (TIME_SPAN(KEYx->msg_f_time_tick(), KEYx->msg_pin_level_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_ERROR)
					{
						//---������Ч״̬�ǳ���
						KEYx->msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
						//---״̬���㣬����ɨ�谴��
						KEYx->msg_pin_level_step = 6;
						//---�������¼�
#if (MODULE_LOG_KEY_BUTTON>0)
						LOG_VA_ARGS("����:����\r\n");
#endif
					}
				}
				else
				{
					//---״̬���㣬����ɨ�谴��
					KEYx->msg_pin_level_step = 0;
				}
			}
			//---�����˳�
			case 6:
			{
				if (KEYx->msg_pin_level_value != KEYx->msg_pin_level_active)
				{
					//---������Ч״̬�ǳ���
					KEYx->msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
					//---״̬���㣬����ɨ�谴��
					KEYx->msg_pin_level_step = 0;
					//---�������¼�
#if (MODULE_LOG_KEY_BUTTON>0)
					LOG_VA_ARGS("����:�ָ�\r\n");
#endif
				}
				break;
			}
			default:
			{	
				//---״̬���㣬����ɨ�谴��
				KEYx->msg_pin_level_step = 0;
				break;
			}
		}
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
uint8_t key_scan_one(KEY_HandleType* KEYx)
{
#if (KEY_BUTTON_MAX_NUM>1)
	uint8_t button_index = 0;
	for (button_index=0;button_index< KEY_BUTTON_MAX_NUM;button_index++)
	{
		//---��ȡ����״̬
		key_press_driver_one(&(KEYx->msg_button[button_index]));
		//---ɨ��״̬��ѵ
		switch (KEYx->msg_button[button_index].msg_pin_scan_step)
		{
			//---�����Ч����
			case 0:
			{
				if (KEYx->msg_button[button_index].msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
				{
					//---���������������Ϸ��ؼ�ֵ���ж��ǲ���˫��
					KEYx->msg_button[button_index].msg_pin_scan_record = KEYx->msg_button[button_index].msg_f_time_tick();
					//---��һ״̬
					KEYx->msg_button[button_index].msg_pin_scan_step = 1;
					//---��������
					KEYx->msg_button[button_index].msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_ONE;
				}
				else
				{
					//---ֱ�ӷ��ؼ�ֵ
					KEYx->msg_button[button_index].msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
					//---����״̬0���ȴ��µ���Ч����
					KEYx->msg_button[button_index].msg_pin_scan_step = 0;
				}
				break;
			}
			//---У�鵥��
			case 1:
			{
				if (KEYx->msg_button[button_index].msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
				{
					//---���������������Ϸ��ؼ�ֵ���ж��ǲ���˫��
					KEYx->msg_button[button_index].msg_pin_scan_record = KEYx->msg_button[button_index].msg_f_time_tick();
					//---��һ״̬
					KEYx->msg_button[button_index].msg_pin_scan_step = 2;
				}
				else
				{
					//---�ж��Ƿ񳬹�ʱ����
					if (TIME_SPAN(KEYx->msg_button[button_index].msg_f_time_tick(),
						KEYx->msg_button[button_index].msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE)
					{
						//---������Ч
						KEYx->msg_button[button_index].msg_pin_scan_active = ACTIVE_STATE_ENABLE;
						//---������Ч����״̬Ϊ����
						KEYx->msg_button[button_index].msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
						//---��������
						KEYx->msg_button[button_index].msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_ONE;
						//---����״̬0���ȴ��µ���Ч����
						KEYx->msg_button[button_index].msg_pin_scan_step = 0;
						//---ִ�е�������
#if (MODULE_LOG_KEY_BUTTON>0)
						LOG_VA_ARGS("����%d:����\r\n",button_index+1);
#endif
					}
				}
				break;
			}
			//---У��˫��
			case 2:
			{
				if (KEYx->msg_button[button_index].msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
				{
					//---���������������Ϸ��ؼ�ֵ���ж��ǲ���˫��
					KEYx->msg_button[button_index].msg_pin_scan_record = KEYx->msg_button[button_index].msg_f_time_tick();
					//---��һ״̬
					KEYx->msg_button[button_index].msg_pin_scan_step = 3;
				}
				else
				{
					//---�ж��Ƿ񳬹�ʱ����
					if (TIME_SPAN(KEYx->msg_button[button_index].msg_f_time_tick(),
						KEYx->msg_button[button_index].msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_TWO)
					{
						//---������Ч
						KEYx->msg_button[button_index].msg_pin_scan_active = ACTIVE_STATE_ENABLE;
						//---������Ч����״̬Ϊ˫��
						KEYx->msg_button[button_index].msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
						//---˫������
						KEYx->msg_button[button_index].msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_TWO;
						//---����״̬0���ȴ��µ���Ч����
						KEYx->msg_button[button_index].msg_pin_scan_step = 0;
						//---ִ��˫������
#if (MODULE_LOG_KEY_BUTTON>0)
						LOG_VA_ARGS("����%d:˫��\r\n", button_index + 1);
#endif
					}
				}
				break;
			}
			//---У������
			case 3:
			{
				if (KEYx->msg_button[button_index].msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
				{
					//---���������������Ϸ��ؼ�ֵ���ж��ǲ���˫��
					KEYx->msg_button[button_index].msg_pin_scan_record = KEYx->msg_button[button_index].msg_f_time_tick();
					//---��һ״̬
					KEYx->msg_button[button_index].msg_pin_scan_step = 4;
				}
				else
				{
					//---�ж��Ƿ񳬹�ʱ����
					if (TIME_SPAN(KEYx->msg_button[button_index].msg_f_time_tick(),
						KEYx->msg_button[button_index].msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_THREE)
					{
						//---������Ч
						KEYx->msg_button[button_index].msg_pin_scan_active = ACTIVE_STATE_ENABLE;
						//---������Ч����״̬Ϊ˫��
						KEYx->msg_button[button_index].msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
						//---˫������
						KEYx->msg_button[button_index].msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_THREE;
						//---����״̬0���ȴ��µ���Ч����
						KEYx->msg_button[button_index].msg_pin_scan_step = 0;
						//---ִ����������
#if (MODULE_LOG_KEY_BUTTON>0)
						LOG_VA_ARGS("����%d:����\r\n", button_index + 1);
#endif
					}
				}
				break;
			}
			//---У���Ļ�
			case 4:
			{
				if (KEYx->msg_button[button_index].msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
				{
					//---���������������Ϸ��ؼ�ֵ���ж��ǲ���˫��
					KEYx->msg_button[button_index].msg_pin_scan_record = KEYx->msg_button[button_index].msg_f_time_tick();
					//---��һ״̬
					KEYx->msg_button[button_index].msg_pin_scan_step = 5;
				}
				else
				{
					//---�ж��Ƿ񳬹�ʱ����
					if (TIME_SPAN(KEYx->msg_button[button_index].msg_f_time_tick(),
						KEYx->msg_button[button_index].msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_FOUR)
					{
						//---������Ч
						KEYx->msg_button[button_index].msg_pin_scan_active = ACTIVE_STATE_ENABLE;
						//---������Ч����״̬Ϊ˫��
						KEYx->msg_button[button_index].msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
						//---˫������
						KEYx->msg_button[button_index].msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_FOUR;
						//---����״̬0���ȴ��µ���Ч����
						KEYx->msg_button[button_index].msg_pin_scan_step = 0;
						//---ִ���Ļ�����
#if (MODULE_LOG_KEY_BUTTON>0)
						LOG_VA_ARGS("����%d:�Ļ�\r\n", button_index + 1);
#endif
					}
				}
				break;
			}
			//---У�����
			case 5:
			{
				if (KEYx->msg_button[button_index].msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
				{
					//---���������������Ϸ��ؼ�ֵ���ж��ǲ���˫��
					KEYx->msg_button[button_index].msg_pin_scan_record = KEYx->msg_button[button_index].msg_f_time_tick();
					//---��һ״̬
					KEYx->msg_button[button_index].msg_pin_scan_step = 6;
				}
				else
				{
					//---�ж��Ƿ񳬹�ʱ����
					if (TIME_SPAN(KEYx->msg_button[button_index].msg_f_time_tick(),
						KEYx->msg_button[button_index].msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_FIVR)
					{
						//---������Ч
						KEYx->msg_button[button_index].msg_pin_scan_active = ACTIVE_STATE_ENABLE;
						//---������Ч����״̬Ϊ˫��
						KEYx->msg_button[button_index].msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
						//---˫������
						KEYx->msg_button[button_index].msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_FIVE;
						//---����״̬0���ȴ��µ���Ч����
						KEYx->msg_button[button_index].msg_pin_scan_step = 0;
						//---ִ���������
#if (MODULE_LOG_KEY_BUTTON>0)
						LOG_VA_ARGS("����%d:���\r\n", button_index + 1);
#endif
					}
				}
				break;
			}
			//---У������
			case 6:
			{
				if (KEYx->msg_button[button_index].msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
				{
					//---���������������Ϸ��ؼ�ֵ���ж��ǲ���˫��
					KEYx->msg_button[button_index].msg_pin_scan_record = KEYx->msg_button[button_index].msg_f_time_tick();
					//---��һ״̬
					KEYx->msg_button[button_index].msg_pin_scan_step = 7;
				}
				else
				{
					//---�ж��Ƿ񳬹�ʱ����
					if (TIME_SPAN(KEYx->msg_button[button_index].msg_f_time_tick(),
						KEYx->msg_button[button_index].msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_SIX)
					{
						//---������Ч
						KEYx->msg_button[button_index].msg_pin_scan_active = ACTIVE_STATE_ENABLE;
						//---������Ч����״̬Ϊ˫��
						KEYx->msg_button[button_index].msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
						//---˫������
						KEYx->msg_button[button_index].msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_SIX;
						//---����״̬0���ȴ��µ���Ч����
						KEYx->msg_button[button_index].msg_pin_scan_step = 0;
						//---ִ����������
#if (MODULE_LOG_KEY_BUTTON>0)
						LOG_VA_ARGS("����%d:����\r\n", button_index + 1);
#endif
					}
				}
				break;
			}
			//---У���߻�
			case 7:
			{
				if (KEYx->msg_button[button_index].msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
				{
					//---���������������Ϸ��ؼ�ֵ���ж��ǲ���˫��
					KEYx->msg_button[button_index].msg_pin_scan_record = KEYx->msg_button[button_index].msg_f_time_tick();
					//---��һ״̬
					KEYx->msg_button[button_index].msg_pin_scan_step = 8;
				}
				else
				{
					//---�ж��Ƿ񳬹�ʱ����
					if (TIME_SPAN(KEYx->msg_button[button_index].msg_f_time_tick(),
						KEYx->msg_button[button_index].msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_SEVEN)
					{
						//---������Ч
						KEYx->msg_button[button_index].msg_pin_scan_active = ACTIVE_STATE_ENABLE;
						//---������Ч����״̬Ϊ˫��
						KEYx->msg_button[button_index].msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
						//---˫������
						KEYx->msg_button[button_index].msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_SEVEN;
						//---����״̬0���ȴ��µ���Ч����
						KEYx->msg_button[button_index].msg_pin_scan_step = 0;
						//---ִ���߻�����
#if (MODULE_LOG_KEY_BUTTON>0)
						LOG_VA_ARGS("����%d:�߻�\r\n", button_index + 1);
#endif
					}
				}
				break;
			}
			//---У��˻�
			case 8:
			{
				if (KEYx->msg_button[button_index].msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
				{
					//---���������������Ϸ��ؼ�ֵ���ж��ǲ���˫��
					KEYx->msg_button[button_index].msg_pin_scan_record = KEYx->msg_button[button_index].msg_f_time_tick();
					//---��һ״̬
					KEYx->msg_button[button_index].msg_pin_scan_step = 9;
				}
				else
				{
					//---�ж��Ƿ񳬹�ʱ����
					if (TIME_SPAN(KEYx->msg_button[button_index].msg_f_time_tick(),
						KEYx->msg_button[button_index].msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_EIGHT)
					{
						//---������Ч
						KEYx->msg_button[button_index].msg_pin_scan_active = ACTIVE_STATE_ENABLE;
						//---������Ч����״̬Ϊ˫��
						KEYx->msg_button[button_index].msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
						//---˫������
						KEYx->msg_button[button_index].msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_EIGHT;
						//---����״̬0���ȴ��µ���Ч����
						KEYx->msg_button[button_index].msg_pin_scan_step = 0;
						//---ִ�а˻�����
#if (MODULE_LOG_KEY_BUTTON>0)
						LOG_VA_ARGS("����%d:�˻�\r\n", button_index + 1);
#endif
					}
				}
				break;
			}
			//---У��Ż�
			case 9:
			{
				if (KEYx->msg_button[button_index].msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
				{
					//---���������������Ϸ��ؼ�ֵ���ж��ǲ���˫��
					KEYx->msg_button[button_index].msg_pin_scan_record = KEYx->msg_button[button_index].msg_f_time_tick();
					//---��һ״̬
					KEYx->msg_button[button_index].msg_pin_scan_step = 10;
				}
				else
				{
					//---�ж��Ƿ񳬹�ʱ����
					if (TIME_SPAN(KEYx->msg_button[button_index].msg_f_time_tick(),
						KEYx->msg_button[button_index].msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_NINE)
					{
						//---������Ч
						KEYx->msg_button[button_index].msg_pin_scan_active = ACTIVE_STATE_ENABLE;
						//---������Ч����״̬Ϊ˫��
						KEYx->msg_button[button_index].msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
						//---˫������
						KEYx->msg_button[button_index].msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_NINE;
						//---����״̬0���ȴ��µ���Ч����
						KEYx->msg_button[button_index].msg_pin_scan_step = 0;
						//---ִ�оŻ�����
#if (MODULE_LOG_KEY_BUTTON>0)
						LOG_VA_ARGS("����%d:�Ż�\r\n", button_index + 1);
#endif
					}
				}
				break;
			}
			//---У��ʮ��
			case 10:
			{
				if (KEYx->msg_button[button_index].msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
				{
					//---���������������Ϸ��ؼ�ֵ���ж��ǲ���˫��
					KEYx->msg_button[button_index].msg_pin_scan_record = KEYx->msg_button[button_index].msg_f_time_tick();
					//---��һ״̬
					KEYx->msg_button[button_index].msg_pin_scan_step = 11;
				}
				else
				{
					//---�ж��Ƿ񳬹�ʱ����
					if (TIME_SPAN(KEYx->msg_button[button_index].msg_f_time_tick(),
						KEYx->msg_button[button_index].msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_TEN)
					{
						//---������Ч
						KEYx->msg_button[button_index].msg_pin_scan_active = ACTIVE_STATE_ENABLE;
						//---������Ч����״̬Ϊ˫��
						KEYx->msg_button[button_index].msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
						//---˫������
						KEYx->msg_button[button_index].msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_TEN;
						//---����״̬0���ȴ��µ���Ч����
						KEYx->msg_button[button_index].msg_pin_scan_step = 0;
						//---ִ��ʮ������
#if (MODULE_LOG_KEY_BUTTON>0)
						LOG_VA_ARGS("����%d:ʮ��\r\n", button_index + 1);
#endif
					}
				}
				break;
			}
			//---����
			case 11:
			default:
			{
				//---���������������Ϸ��ؼ�ֵ���ж��ǲ���˫��
				KEYx->msg_button[button_index].msg_pin_scan_record = KEYx->msg_button[button_index].msg_f_time_tick();
				//---������Ч����״̬Ϊ��Ч
				KEYx->msg_button[button_index].msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
				//---˫������
				KEYx->msg_button[button_index].msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
				//---������Ч
				KEYx->msg_button[button_index].msg_pin_scan_active = ACTIVE_STATE_DISABLE;
				//---����״̬0���ȴ��µ���Ч����
				KEYx->msg_button[button_index].msg_pin_scan_step = 0;
				//---ִ�а�����Ч����
				break;
			}
		}
	}
#else
	//---��ȡ����״̬
	key_driver_one(&(KEYx->msg_button));
	//---ɨ��״̬��ѵ
	switch (KEYx->msg_button.msg_pin_scan_step)
	{
		//---�����Ч����
		case 0:
		{
			if (KEYx->msg_button.msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
			{
				//---���������������Ϸ��ؼ�ֵ���ж��ǲ���˫��
				KEYx->msg_button.msg_pin_scan_record = KEYx->msg_button.msg_f_time_tick();
				//---��һ״̬
				KEYx->msg_button.msg_pin_scan_step = 1;
				//---��������
				KEYx->msg_button.msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_ONE;
			}
			else
			{
				//---ֱ�ӷ��ؼ�ֵ
				KEYx->msg_button.msg_pin_level_state= KEY_BUTTON_PRESS_STATE_CLICK_NONE;
				//---����״̬0���ȴ��µ���Ч����
				KEYx->msg_button.msg_pin_scan_step = 0;
			}
			break;
		}
		//---У�鵥��
		case 1:
		{
			if (KEYx->msg_button.msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
			{
				//---���������������Ϸ��ؼ�ֵ���ж��ǲ���˫��
				KEYx->msg_button.msg_pin_scan_record = KEYx->msg_button.msg_f_time_tick();
				//---��һ״̬
				KEYx->msg_button.msg_pin_scan_step = 2;
			}
			else
			{
				//---�ж��Ƿ񳬹�ʱ����
				if (TIME_SPAN(KEYx->msg_button.msg_f_time_tick(),
					KEYx->msg_button.msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_ONE)
				{
					//---������Ч
					KEYx->msg_button.msg_pin_scan_active = ACTIVE_STATE_ENABLE;
					//---������Ч����״̬Ϊ����
					KEYx->msg_button.msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
					//---��������
					KEYx->msg_button.msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_ONE;
					//---����״̬0���ȴ��µ���Ч����
					KEYx->msg_button.msg_pin_scan_step = 0;
					//---ִ�е�������
#if (MODULE_LOG_KEY_BUTTON>0)
					LOG_VA_ARGS("����:����\r\n");
#endif
				}
			}
			break;
		}
		//---У��˫��
		case 2:
		{
			if (KEYx->msg_button.msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
			{
				//---���������������Ϸ��ؼ�ֵ���ж��ǲ���˫��
				KEYx->msg_button.msg_pin_scan_record = KEYx->msg_button.msg_f_time_tick();
				//---��һ״̬
				KEYx->msg_button.msg_pin_scan_step = 3;
			}
			else
			{
				//---�ж��Ƿ񳬹�ʱ����
				if (TIME_SPAN(KEYx->msg_button.msg_f_time_tick(),
					KEYx->msg_button.msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_TWO)
				{
					//---������Ч
					KEYx->msg_button.msg_pin_scan_active = ACTIVE_STATE_ENABLE;
					//---������Ч����״̬Ϊ˫��
					KEYx->msg_button.msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
					//---˫������
					KEYx->msg_button.msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_TWO;
					//---����״̬0���ȴ��µ���Ч����
					KEYx->msg_button.msg_pin_scan_step = 0;
					//---ִ��˫������
#if (MODULE_LOG_KEY_BUTTON>0)
					LOG_VA_ARGS("����:˫��\r\n");
#endif
				}
			}
			break;
		}
		//---У������
		case 3:
		{
			if (KEYx->msg_button.msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
			{
				//---���������������Ϸ��ؼ�ֵ���ж��ǲ���˫��
				KEYx->msg_button.msg_pin_scan_record = KEYx->msg_button.msg_f_time_tick();
				//---��һ״̬
				KEYx->msg_button.msg_pin_scan_step = 4;
			}
			else
			{
				//---�ж��Ƿ񳬹�ʱ����
				if (TIME_SPAN(KEYx->msg_button.msg_f_time_tick(),
					KEYx->msg_button.msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_THREE)
				{
					//---������Ч
					KEYx->msg_button.msg_pin_scan_active = ACTIVE_STATE_ENABLE;
					//---������Ч����״̬Ϊ˫��
					KEYx->msg_button.msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
					//---˫������
					KEYx->msg_button.msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_THREE;
					//---����״̬0���ȴ��µ���Ч����
					KEYx->msg_button.msg_pin_scan_step = 0;
					//---ִ����������
#if (MODULE_LOG_KEY_BUTTON>0)
					LOG_VA_ARGS("����:����\r\n");
#endif
				}
			}
			break;
		}
		//---У���Ļ�
		case 4:
		{
			if (KEYx->msg_button.msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
			{
				//---���������������Ϸ��ؼ�ֵ���ж��ǲ���˫��
				KEYx->msg_button.msg_pin_scan_record = KEYx->msg_button.msg_f_time_tick();
				//---��һ״̬
				KEYx->msg_button.msg_pin_scan_step = 5;
			}
			else
			{
				//---�ж��Ƿ񳬹�ʱ����
				if (TIME_SPAN(KEYx->msg_button.msg_f_time_tick(),
					KEYx->msg_button.msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_FOUR)
				{
					//---������Ч
					KEYx->msg_button.msg_pin_scan_active = ACTIVE_STATE_ENABLE;
					//---������Ч����״̬Ϊ˫��
					KEYx->msg_button.msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
					//---˫������
					KEYx->msg_button.msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_FOUR;
					//---����״̬0���ȴ��µ���Ч����
					KEYx->msg_button.msg_pin_scan_step = 0;
					//---ִ���Ļ�����
#if (MODULE_LOG_KEY_BUTTON>0)
					LOG_VA_ARGS("����:�Ļ�\r\n");
#endif
				}
			}
			break;
		}
		//---У�����
		case 5:
		{
			if (KEYx->msg_button.msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
			{
				//---���������������Ϸ��ؼ�ֵ���ж��ǲ���˫��
				KEYx->msg_button.msg_pin_scan_record = KEYx->msg_button.msg_f_time_tick();
				//---��һ״̬
				KEYx->msg_button.msg_pin_scan_step = 6;
			}
			else
			{
				//---�ж��Ƿ񳬹�ʱ����
				if (TIME_SPAN(KEYx->msg_button.msg_f_time_tick(),
					KEYx->msg_button.msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_FIVR)
				{
					//---������Ч
					KEYx->msg_button.msg_pin_scan_active = ACTIVE_STATE_ENABLE;
					//---������Ч����״̬Ϊ˫��
					KEYx->msg_button.msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
					//---˫������
					KEYx->msg_button.msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_FIVE;
					//---����״̬0���ȴ��µ���Ч����
					KEYx->msg_button.msg_pin_scan_step = 0;
					//---ִ���������
#if (MODULE_LOG_KEY_BUTTON>0)
					LOG_VA_ARGS("����:���\r\n");
#endif
				}
			}
			break;
		}
		//---У������
		case 6:
		{
			if (KEYx->msg_button.msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
			{
				//---���������������Ϸ��ؼ�ֵ���ж��ǲ���˫��
				KEYx->msg_button.msg_pin_scan_record = KEYx->msg_button.msg_f_time_tick();
				//---��һ״̬
				KEYx->msg_button.msg_pin_scan_step = 7;
			}
			else
			{
				//---�ж��Ƿ񳬹�ʱ����
				if (TIME_SPAN(KEYx->msg_button.msg_f_time_tick(),
					KEYx->msg_button.msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_SIX)
				{
					//---������Ч
					KEYx->msg_button.msg_pin_scan_active = ACTIVE_STATE_ENABLE;
					//---������Ч����״̬Ϊ˫��
					KEYx->msg_button.msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
					//---˫������
					KEYx->msg_button.msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_SIX;
					//---����״̬0���ȴ��µ���Ч����
					KEYx->msg_button.msg_pin_scan_step = 0;
					//---ִ����������
#if (MODULE_LOG_KEY_BUTTON>0)
					LOG_VA_ARGS("����:����\r\n");
#endif
				}
			}
			break;
		}
		//---У���߻�
		case 7:
		{
			if (KEYx->msg_button.msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
			{
				//---���������������Ϸ��ؼ�ֵ���ж��ǲ���˫��
				KEYx->msg_button.msg_pin_scan_record = KEYx->msg_button.msg_f_time_tick();
				//---��һ״̬
				KEYx->msg_button.msg_pin_scan_step = 8;
			}
			else
			{
				//---�ж��Ƿ񳬹�ʱ����
				if (TIME_SPAN(KEYx->msg_button.msg_f_time_tick(),
					KEYx->msg_button.msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_SEVEN)
				{
					//---������Ч
					KEYx->msg_button.msg_pin_scan_active = ACTIVE_STATE_ENABLE;
					//---������Ч����״̬Ϊ˫��
					KEYx->msg_button.msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
					//---˫������
					KEYx->msg_button.msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_SEVEN;
					//---����״̬0���ȴ��µ���Ч����
					KEYx->msg_button.msg_pin_scan_step = 0;
					//---ִ���߻�����
#if (MODULE_LOG_KEY_BUTTON>0)
					LOG_VA_ARGS("����:�߻�\r\n");
#endif
				}
			}
			break;
		}
		//---У��˻�
		case 8:
		{
			if (KEYx->msg_button.msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
			{
				//---���������������Ϸ��ؼ�ֵ���ж��ǲ���˫��
				KEYx->msg_button.msg_pin_scan_record = KEYx->msg_button.msg_f_time_tick();
				//---��һ״̬
				KEYx->msg_button.msg_pin_scan_step = 9;
			}
			else
			{
				//---�ж��Ƿ񳬹�ʱ����
				if (TIME_SPAN(KEYx->msg_button.msg_f_time_tick(),
					KEYx->msg_button.msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_EIGHT)
				{
					//---������Ч
					KEYx->msg_button.msg_pin_scan_active = ACTIVE_STATE_ENABLE;
					//---������Ч����״̬Ϊ˫��
					KEYx->msg_button.msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
					//---˫������
					KEYx->msg_button.msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_EIGHT;
					//---����״̬0���ȴ��µ���Ч����
					KEYx->msg_button.msg_pin_scan_step = 0;
					//---ִ�а˻�����
#if (MODULE_LOG_KEY_BUTTON>0)
					LOG_VA_ARGS("����:�˻�\r\n");
#endif
				}
			}
			break;
		}
		//---У��Ż�
		case 9:
		{
			if (KEYx->msg_button.msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
			{
				//---���������������Ϸ��ؼ�ֵ���ж��ǲ���˫��
				KEYx->msg_button.msg_pin_scan_record = KEYx->msg_button.msg_f_time_tick();
				//---��һ״̬
				KEYx->msg_button.msg_pin_scan_step = 10;
			}
			else
			{
				//---�ж��Ƿ񳬹�ʱ����
				if (TIME_SPAN(KEYx->msg_button.msg_f_time_tick(),
					KEYx->msg_button.msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_NINE)
				{
					//---������Ч
					KEYx->msg_button.msg_pin_scan_active = ACTIVE_STATE_ENABLE;
					//---������Ч����״̬Ϊ˫��
					KEYx->msg_button.msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
					//---˫������
					KEYx->msg_button.msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_NINE;
					//---����״̬0���ȴ��µ���Ч����
					KEYx->msg_button.msg_pin_scan_step = 0;
					//---ִ�оŻ�����
#if (MODULE_LOG_KEY_BUTTON>0)
					LOG_VA_ARGS("����:�Ż�\r\n");
#endif
				}
			}
			break;
		}
		//---У��ʮ��
		case 10:
		{
			if (KEYx->msg_button.msg_pin_level_state == KEY_BUTTON_PRESS_STATE_CLICK_ONE)
			{
				//---���������������Ϸ��ؼ�ֵ���ж��ǲ���˫��
				KEYx->msg_button.msg_pin_scan_record = KEYx->msg_button.msg_f_time_tick();
				//---��һ״̬
				KEYx->msg_button.msg_pin_scan_step = 11;
			}
			else
			{
				//---�ж��Ƿ񳬹�ʱ����
				if (TIME_SPAN(KEYx->msg_button.msg_f_time_tick(),
					KEYx->msg_button.msg_pin_scan_record) > KEY_BUTTON_ACTIVE_TIME_REPEAT_TEN)
				{
					//---������Ч
					KEYx->msg_button.msg_pin_scan_active = ACTIVE_STATE_ENABLE;
					//---������Ч����״̬Ϊ˫��
					KEYx->msg_button.msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
					//---˫������
					KEYx->msg_button.msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_TEN;
					//---����״̬0���ȴ��µ���Ч����
					KEYx->msg_button.msg_pin_scan_step = 0;
					//---ִ��ʮ������
#if (MODULE_LOG_KEY_BUTTON>0)
					LOG_VA_ARGS("����:ʮ��\r\n");
#endif
				}
			}
			break;
		}
		//---����
		case 11:
		default:
		{	
			//---���������������Ϸ��ؼ�ֵ���ж��ǲ���˫��
			KEYx->msg_button.msg_pin_scan_record = KEYx->msg_button.msg_f_time_tick();
			//---������Ч����״̬Ϊ��Ч
			KEYx->msg_button.msg_pin_level_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
			//---˫������
			KEYx->msg_button.msg_pin_scan_state = KEY_BUTTON_PRESS_STATE_CLICK_NONE;
			//---������Ч
			KEYx->msg_button.msg_pin_scan_active = ACTIVE_STATE_DISABLE;
			//---����״̬0���ȴ��µ���Ч����
			KEYx->msg_button.msg_pin_scan_step = 0;
			//---ִ�а�����Ч����
			break;
		}
	}
	//---���鰴����Ч���ж��Ƿ�ʹ���ж�
	if (KEYx->msg_button.msg_pin_scan_active == ACTIVE_STATE_ENABLE)
	{
		//---������������
		key_start_one(KEYx, 0);
	}
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t key_scan_two(KEY_HandleType* KEYx)
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
uint8_t key_scan_three(KEY_HandleType* KEYx)
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
uint8_t key_time_tick_init(KEY_HandleType* KEYx, uint32_t(*func_time_tick)(void))
{
#if (KEY_BUTTON_MAX_NUM>1)
	
#else
	//---ע��δ���
	(func_time_tick != NULL) ?
		(KEYx->msg_button.msg_f_time_tick = func_time_tick) :
		(KEYx->msg_button.msg_f_time_tick = sys_tick_task_get_tick);
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t key_init(KEY_HandleType* KEYx, uint32_t(*func_time_tick)(void))
{
	if ((KEYx != NULL) && (KEYx == KEY_TASK_ONE))
	{
		return key_init_one(KEYx, func_time_tick);
	}
	if ((KEYx != NULL) && (KEYx == KEY_TASK_TWO))
	{
		return key_init_two(KEYx, func_time_tick);
	}
	if ((KEYx != NULL) && (KEYx ==KEY_TASK_THREE))
	{
		return key_init_three(KEYx, func_time_tick);
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
uint8_t key_scan(KEY_HandleType* KEYx)
{
	if ((KEYx != NULL) && (KEYx == KEY_TASK_ONE))
	{
		return key_scan_one(KEYx);
	}
	if ((KEYx != NULL) && (KEYx == KEY_TASK_TWO))
	{
		return key_scan_two(KEYx);
	}
	if ((KEYx != NULL) && (KEYx == KEY_TASK_THREE))
	{
		return key_scan_three(KEYx);
	}
	return ERROR_2;
}
