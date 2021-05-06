#include "gpio_cfg.h"

//===GPIOʹ�õĵδ�ʱ
uint32_t(*gpio_time_tick)(void);

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: GPIO��ʼ��
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void gpio_init(uint32_t(*func_time_tick)(void))
{
	gpio_time_tick_init(func_time_tick);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��:
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void gpio_time_tick_init(uint32_t(*func_time_tick)(void))
{
	//---ע����ĺ��������û�н��ĺ�����Ĭ��ʹ��ϵͳ�δ���Ϊ����
	(func_time_tick != NULL) ?
		(gpio_time_tick = func_time_tick) : 
		(gpio_time_tick = sys_tick_task_get_tick);
	//---У����ĺ���
	if (gpio_time_tick == NULL)
	{
		gpio_time_tick = sys_tick_task_get_tick;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: GPIOģʽ
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void gpio_pin_mode_set(GPIO_TypeDef *gpio,uint32_t pin)
{
	switch(pin)
	{
		case GPIO_PIN_BIT_0:
		{
			(*gpio)|=GPIO_PIN_BIT_0;
			break;
		}
		case GPIO_PIN_BIT_1:
		{
			(*gpio)|=GPIO_PIN_BIT_1;
			break;
		}
		case GPIO_PIN_BIT_2:
		{
			(*gpio)|=GPIO_PIN_BIT_2;			
			break;
		}
		case GPIO_PIN_BIT_3:
		{
			(*gpio)|=GPIO_PIN_BIT_3;
			break;
		}
		case GPIO_PIN_BIT_4:
		{
			(*gpio)|=GPIO_PIN_BIT_4;
			break;
		}
		case GPIO_PIN_BIT_5:
		{
			(*gpio)|=GPIO_PIN_BIT_5;
			break;
		}
		case GPIO_PIN_BIT_6:
		{
			(*gpio)|=GPIO_PIN_BIT_6;
			break;
		}
		case GPIO_PIN_BIT_7:
		{
			(*gpio)|=GPIO_PIN_BIT_7;
			break;
		}
		case GPIO_PIN_BIT_ALL:
		default:
		{
			(*gpio)|=GPIO_PIN_BIT_ALL;
			break;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: GPIOģʽ
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void gpio_pin_mode_reset(GPIO_TypeDef *gpio,uint32_t pin)
{
	switch(pin)
	{
		case GPIO_PIN_BIT_0:
		{
			(*gpio)&=(~GPIO_PIN_BIT_0);
			break;
		}
		case GPIO_PIN_BIT_1:
		{
			(*gpio)&=(~GPIO_PIN_BIT_1);
			break;
		}
		case GPIO_PIN_BIT_2:
		{
			(*gpio)&=(~GPIO_PIN_BIT_2);			
			break;
		}
		case GPIO_PIN_BIT_3:
		{
			(*gpio)&=(~GPIO_PIN_BIT_3);
			break;
		}
		case GPIO_PIN_BIT_4:
		{
			(*gpio)&=(~GPIO_PIN_BIT_4);
			break;
		}
		case GPIO_PIN_BIT_5:
		{
			(*gpio)&=(~GPIO_PIN_BIT_5);
			break;
		}
		case GPIO_PIN_BIT_6:
		{
			(*gpio)&=(~GPIO_PIN_BIT_6);
			break;
		}
		case GPIO_PIN_BIT_7:
		{
			(*gpio)&=(~GPIO_PIN_BIT_7);
			break;
		}
		case GPIO_PIN_BIT_ALL:
		default:
		{
			(*gpio)&=(~GPIO_PIN_BIT_ALL);
			break;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����GPIOΪ����ģʽ
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void gpio_pin_mode_input(GPIO_TypeDef *gpio,uint32_t pin)
{
#if defined(GPIOP0)&&defined(GPIOPM0)
	if(gpio==GPIOP0)
	{
		gpio_pin_mode_set(GPIOPM0,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP1)&&defined(GPIOPM1)
	if(gpio==GPIOP1)
	{
		gpio_pin_mode_set(GPIOPM1,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP2)&&defined(GPIOPM2)
	if(gpio==GPIOP2)
	{
		gpio_pin_mode_set(GPIOPM2,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP3)&&defined(GPIOPM3)
	if(gpio==GPIOP3)
	{
		gpio_pin_mode_set(GPIOPM3,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP4)&&defined(GPIOPM4)
	if(gpio==GPIOP4)
	{
		gpio_pin_mode_set(GPIOPM4,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP5)&&defined(GPIOPM5)
	if(gpio==GPIOP5)
	{
		gpio_pin_mode_set(GPIOPM5,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP6)&&defined(GPIOPM6)
	if(gpio==GPIOP6)
	{
		gpio_pin_mode_set(GPIOPM6,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP7)&&defined(GPIOPM7)
	if(gpio==GPIOP7)
	{
		gpio_pin_mode_set(GPIOPM7,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP8)&&defined(GPIOPM8)
	if(gpio==GPIOP8)
	{
		gpio_pin_mode_set(GPIOPM8,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP9)&&defined(GPIOPM9)
	if(gpio==GPIOP9)
	{
		gpio_pin_mode_set(GPIOPM9,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP10)&&defined(GPIOPM10)
	if(gpio==GPIOP10)
	{
		gpio_pin_mode_set(GPIOPM10,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP11)&&defined(GPIOPM11)
	if(gpio==GPIOP11)
	{
		gpio_pin_mode_set(GPIOPM11,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP12)&&defined(GPIOPM12)
	if(gpio==GPIOP12)
	{
		gpio_pin_mode_set(GPIOPM12,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP13)&&defined(GPIOPM13)
	if(gpio==GPIOP13)
	{
		gpio_pin_mode_set(GPIOPM13,pin);
		//---�˳�����
		return;
	}
#endif

#if (MODULE_LOG_GPIO>0)
	else
	{
		LOG_VA_ARGS("�˿���������:��֧�ֵĶ˿���Ϣ\r\n");
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����GPIOΪ���ģʽ
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void gpio_pin_mode_output(GPIO_TypeDef *gpio,uint32_t pin)
{
#if defined(GPIOP0)&&defined(GPIOPM0)
	if(gpio==GPIOP0)
	{
		gpio_pin_mode_reset(GPIOPM0,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP1)&&defined(GPIOPM1)
	if(gpio==GPIOP1)
	{
		gpio_pin_mode_reset(GPIOPM1,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP2)&&defined(GPIOPM2)
	if(gpio==GPIOP2)
	{
		gpio_pin_mode_reset(GPIOPM2,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP3)&&defined(GPIOPM3)
	if(gpio==GPIOP3)
	{
		gpio_pin_mode_reset(GPIOPM3,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP4)&&defined(GPIOPM4)
	if(gpio==GPIOP4)
	{
		gpio_pin_mode_reset(GPIOPM4,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP5)&&defined(GPIOPM5)
	if(gpio==GPIOP5)
	{
		gpio_pin_mode_reset(GPIOPM5,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP6)&&defined(GPIOPM6)
	if(gpio==GPIOP6)
	{
		gpio_pin_mode_reset(GPIOPM6,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP7)&&defined(GPIOPM7)
	if(gpio==GPIOP7)
	{
		gpio_pin_mode_reset(GPIOPM7,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP8)&&defined(GPIOPM8)
	if(gpio==GPIOP8)
	{
		gpio_pin_mode_reset(GPIOPM8,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP9)&&defined(GPIOPM9)
	if(gpio==GPIOP9)
	{
		gpio_pin_mode_reset(GPIOPM9,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP10)&&defined(GPIOPM10)
	if(gpio==GPIOP10)
	{
		gpio_pin_mode_reset(GPIOPM10,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP11)&&defined(GPIOPM11)
	if(gpio==GPIOP11)
	{
		gpio_pin_mode_reset(GPIOPM11,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP12)&&defined(GPIOPM12)
	if(gpio==GPIOP12)
	{
		gpio_pin_mode_reset(GPIOPM12,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP13)&&defined(GPIOPM13)
	if(gpio==GPIOP13)
	{
		gpio_pin_mode_reset(GPIOPM13,pin);
		//---�˳�����
		return;
	}
#endif

#if (MODULE_LOG_GPIO>0)
	else
	{
		LOG_VA_ARGS("�˿��������:��֧�ֵĶ˿���Ϣ\r\n");
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����GPIO����ʹ��
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void gpio_pin_mode_pull_up_set(GPIO_TypeDef *gpio,uint32_t pin)
{
#if defined(GPIOP0)&&defined(GPIOPU0)
	if(gpio==GPIOP0)
	{
		gpio_pin_mode_set(GPIOPU0,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP1)&&defined(GPIOPU1)
	if(gpio==GPIOP1)
	{
		gpio_pin_mode_set(GPIOPM1,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP2)&&defined(GPIOPU2)
	if(gpio==GPIOP2)
	{
		gpio_pin_mode_set(GPIOPM2,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP3)&&defined(GPIOPU3)
	if(gpio==GPIOP3)
	{
		gpio_pin_mode_set(GPIOPM3,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP4)&&defined(GPIOPU4)
	if(gpio==GPIOP4)
	{
		gpio_pin_mode_set(GPIOPU4,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP5)&&defined(GPIOPU5)
	if(gpio==GPIOP5)
	{
		gpio_pin_mode_set(GPIOPU5,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP6)&&defined(GPIOPU6)
	if(gpio==GPIOP6)
	{
		gpio_pin_mode_set(GPIOPU6,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP7)&&defined(GPIOPU7)
	if(gpio==GPIOP7)
	{
		gpio_pin_mode_set(GPIOPU7,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP8)&&defined(GPIOPU8)
	if(gpio==GPIOP8)
	{
		gpio_pin_mode_set(GPIOPU8,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP9)&&defined(GPIOPU9)
	if(gpio==GPIOP9)
	{
		gpio_pin_mode_set(GPIOPU9,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP10)&&defined(GPIOPU10)
	if(gpio==GPIOP10)
	{
		gpio_pin_mode_set(GPIOPU10,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP11)&&defined(GPIOPU11)
	if(gpio==GPIOP11)
	{
		gpio_pin_mode_set(GPIOPU11,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP12)&&defined(GPIOPU12)
	if(gpio==GPIOP12)
	{
		gpio_pin_mode_set(GPIOPU12,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP13)&&defined(GPIOPU13)
	if(gpio==GPIOP13)
	{
		gpio_pin_mode_set(GPIOPU13,pin);
		//---�˳�����
		return;
	}
#endif

#if (MODULE_LOG_GPIO>0)
	else
	{
		LOG_VA_ARGS("�˿�����ʹ������:��֧�ֵĶ˿���Ϣ\r\n");
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����GPIO������ʹ��
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void gpio_pin_mode_pull_up_reset(GPIO_TypeDef *gpio,uint32_t pin)
{
#if defined(GPIOP0)&&defined(GPIOPU0)
	if(gpio==GPIOP0)
	{
		gpio_pin_mode_reset(GPIOPU0,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP1)&&defined(GPIOPU1)
	if(gpio==GPIOP1)
	{
		gpio_pin_mode_reset(GPIOPU1,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP2)&&defined(GPIOPU2)
	if(gpio==GPIOP2)
	{
		gpio_pin_mode_reset(GPIOPU2,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP3)&&defined(GPIOPU3)
	if(gpio==GPIOP3)
	{
		gpio_pin_mode_reset(GPIOPU3,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP4)&&defined(GPIOPU4)
	if(gpio==GPIOP4)
	{
		gpio_pin_mode_reset(GPIOPU4,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP5)&&defined(GPIOPU5)
	if(gpio==GPIOP5)
	{
		gpio_pin_mode_reset(GPIOPU5,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP6)&&defined(GPIOPU6)
	if(gpio==GPIOP6)
	{
		gpio_pin_mode_reset(GPIOPU6,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP7)&&defined(GPIOPU7)
	if(gpio==GPIOP7)
	{
		gpio_pin_mode_reset(GPIOPU7,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP8)&&defined(GPIOPU8)
	if(gpio==GPIOP8)
	{
		gpio_pin_mode_reset(GPIOPU8,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP9)&&defined(GPIOPU9)
	if(gpio==GPIOP9)
	{
		gpio_pin_mode_reset(GPIOPU9,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP10)&&defined(GPIOPU10)
	if(gpio==GPIOP10)
	{
		gpio_pin_mode_reset(GPIOPU10,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP11)&&defined(GPIOPU11)
	if(gpio==GPIOP11)
	{
		gpio_pin_mode_reset(GPIOPU11,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP12)&&defined(GPIOPU12)
	if(gpio==GPIOP12)
	{
		gpio_pin_mode_reset(GPIOPU12,pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP13)&&defined(GPIOPU13)
	if(gpio==GPIOP13)
	{
		gpio_pin_mode_reset(GPIOPU13,pin);
		//---�˳�����
		return;
	}
#endif

#if (MODULE_LOG_GPIO>0)
	else
	{
		LOG_VA_ARGS("�˿�������ʹ������:��֧�ֵĶ˿���Ϣ\r\n");
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��������ģʽ
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void gpio_pin_mode_input_normal(GPIO_TypeDef *gpio,uint32_t pin)
{
#if defined(GPIOP0)&&defined(GPIOPIM0)
	if (gpio == GPIOP0)
	{
		gpio_pin_mode_reset(GPIOPIM0, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP1)&&defined(GPIOPIM1)
	if (gpio == GPIOP1)
	{
		gpio_pin_mode_reset(GPIOPIM1, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP2)&&defined(GPIOPIM2)
	if (gpio == GPIOP2)
	{
		gpio_pin_mode_reset(GPIOPIM2, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP3)&&defined(GPIOPIM3)
	if (gpio == GPIOP3)
	{
		gpio_pin_mode_reset(GPIOPIM3, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP4)&&defined(GPIOPIM4)
	if (gpio == GPIOP4)
	{
		gpio_pin_mode_reset(GPIOPIM4, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP5)&&defined(GPIOPIM5)
	if (gpio == GPIOP5)
	{
		gpio_pin_mode_reset(GPIOPIM5, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP6)&&defined(GPIOPIM6)
	if (gpio == GPIOP6)
	{
		gpio_pin_mode_reset(GPIOPIM6, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP7)&&defined(GPIOPIM7)
	if (gpio == GPIOP7)
	{
		gpio_pin_mode_reset(GPIOPIM7, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP8)&&defined(GPIOPIM8)
	if (gpio == GPIOP8)
	{
		gpio_pin_mode_reset(GPIOPIM8, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP9)&&defined(GPIOPIM9)
	if (gpio == GPIOP9)
	{
		gpio_pin_mode_reset(GPIOPIM9, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP10)&&defined(GPIOPIM10)
	if (gpio == GPIOP10)
	{
		gpio_pin_mode_reset(GPIOPIM10, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP11)&&defined(GPIOPIM11)
	if (gpio == GPIOP11)
	{
		gpio_pin_mode_reset(GPIOPIM11, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP12)&&defined(GPIOPIM12)
	if (gpio == GPIOP12)
	{
		gpio_pin_mode_reset(GPIOPIM12, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP13)&&defined(GPIOPIM13)
	if (gpio == GPIOP13)
	{
		gpio_pin_mode_reset(GPIOPIM13, pin);
		//---�˳�����
		return;
	}
#endif

#if (MODULE_LOG_GPIO>0)
	else
	{
		LOG_VA_ARGS("�˿���������ģʽ����:��֧�ֵĶ˿���Ϣ\r\n");
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ttl����ģʽ
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void gpio_pin_mode_input_ttl(GPIO_TypeDef *gpio,uint32_t pin)
{
#if defined(GPIOP0)&&defined(GPIOPIM0)
	if (gpio == GPIOP0)
	{
		gpio_pin_mode_set(GPIOPIM0, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP1)&&defined(GPIOPIM1)
	if (gpio == GPIOP1)
	{
		gpio_pin_mode_set(GPIOPIM1, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP2)&&defined(GPIOPIM2)
	if (gpio == GPIOP2)
	{
		gpio_pin_mode_set(GPIOPIM2, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP3)&&defined(GPIOPIM3)
	if (gpio == GPIOP3)
	{
		gpio_pin_mode_set(GPIOPIM3, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP4)&&defined(GPIOPIM4)
	if (gpio == GPIOP4)
	{
		gpio_pin_mode_set(GPIOPIM4, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP5)&&defined(GPIOPIM5)
	if (gpio == GPIOP5)
	{
		gpio_pin_mode_set(GPIOPIM5, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP6)&&defined(GPIOPIM6)
	if (gpio == GPIOP6)
	{
		gpio_pin_mode_set(GPIOPIM6, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP7)&&defined(GPIOPIM7)
	if (gpio == GPIOP7)
	{
		gpio_pin_mode_set(GPIOPIM7, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP8)&&defined(GPIOPIM8)
	if (gpio == GPIOP8)
	{
		gpio_pin_mode_set(GPIOPIM8, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP9)&&defined(GPIOPIM9)
	if (gpio == GPIOP9)
	{
		gpio_pin_mode_set(GPIOPIM9, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP10)&&defined(GPIOPIM10)
	if (gpio == GPIOP10)
	{
		gpio_pin_mode_set(GPIOPIM10, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP11)&&defined(GPIOPIM11)
	if (gpio == GPIOP11)
	{
		gpio_pin_mode_set(GPIOPIM11, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP12)&&defined(GPIOPIM12)
	if (gpio == GPIOP12)
	{
		gpio_pin_mode_set(GPIOPIM12, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP13)&&defined(GPIOPIM13)
	if (gpio == GPIOP13)
	{
		gpio_pin_mode_set(GPIOPIM13, pin);
		//---�˳�����
		return;
	}
#endif

#if (MODULE_LOG_GPIO>0)
	else
	{
		LOG_VA_ARGS("�˿�����TTLģʽ����:��֧�ֵĶ˿���Ϣ\r\n");
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: �������ģʽ
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void gpio_pin_mode_output_normal(GPIO_TypeDef *gpio,uint32_t pin)
{
#if defined(GPIOP0)&&defined(GPIOPOM0)
	if (gpio == GPIOP0)
	{
		gpio_pin_mode_reset(GPIOPOM0, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP1)&&defined(GPIOPOM1)
	if (gpio == GPIOP1)
	{
		gpio_pin_mode_reset(GPIOPOM1, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP2)&&defined(GPIOPOM2)
	if (gpio == GPIOP2)
	{
		gpio_pin_mode_reset(GPIOPOM2, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP3)&&defined(GPIOPOM3)
	if (gpio == GPIOP3)
	{
		gpio_pin_mode_reset(GPIOPOM3, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP4)&&defined(GPIOPOM4)
	if (gpio == GPIOP4)
	{
		gpio_pin_mode_reset(GPIOPOM4, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP5)&&defined(GPIOPOM5)
	if (gpio == GPIOP5)
	{
		gpio_pin_mode_reset(GPIOPOM5, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP6)&&defined(GPIOPOM6)
	if (gpio == GPIOP6)
	{
		gpio_pin_mode_reset(GPIOPOM6, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP7)&&defined(GPIOPOM7)
	if (gpio == GPIOP7)
	{
		gpio_pin_mode_reset(GPIOPOM7, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP8)&&defined(GPIOPOM8)
	if (gpio == GPIOP8)
	{
		gpio_pin_mode_reset(GPIOPOM8, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP9)&&defined(GPIOPOM9)
	if (gpio == GPIOP9)
	{
		gpio_pin_mode_reset(GPIOPOM9, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP10)&&defined(GPIOPOM10)
	if (gpio == GPIOP10)
	{
		gpio_pin_mode_reset(GPIOPOM10, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP11)&&defined(GPIOPOM11)
	if (gpio == GPIOP11)
	{
		gpio_pin_mode_reset(GPIOPOM11, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP12)&&defined(GPIOPOM12)
	if (gpio == GPIOP12)
	{
		gpio_pin_mode_reset(GPIOPOM12, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP13)&&defined(GPIOPOM13)
	if (gpio == GPIOP13)
	{
		gpio_pin_mode_reset(GPIOPOM13, pin);
		//---�˳�����
		return;
	}
#endif

#if (MODULE_LOG_GPIO>0)
	else
	{
		LOG_VA_ARGS("�˿��������ģʽ����:��֧�ֵĶ˿���Ϣ\r\n");
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��©���ģʽ
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void gpio_pin_mode_output_od(GPIO_TypeDef *gpio,uint32_t pin)
{
#if defined(GPIOP0)&&defined(GPIOPOM0)
	if (gpio == GPIOP0)
	{
		gpio_pin_mode_set(GPIOPOM0, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP1)&&defined(GPIOPOM1)
	if (gpio == GPIOP1)
	{
		gpio_pin_mode_set(GPIOPM1, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP2)&&defined(GPIOPOM2)
	if (gpio == GPIOP2)
	{
		gpio_pin_mode_set(GPIOPOM2, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP3)&&defined(GPIOPOM3)
	if (gpio == GPIOP3)
	{
		gpio_pin_mode_set(GPIOPOM3, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP4)&&defined(GPIOPOM4)
	if (gpio == GPIOP4)
	{
		gpio_pin_mode_set(GPIOPOM4, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP5)&&defined(GPIOPOM5)
	if (gpio == GPIOP5)
	{
		gpio_pin_mode_set(GPIOPOM5, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP6)&&defined(GPIOPOM6)
	if (gpio == GPIOP6)
	{
		gpio_pin_mode_set(GPIOPOM6, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP7)&&defined(GPIOPOM7)
	if (gpio == GPIOP7)
	{
		gpio_pin_mode_set(GPIOPOM7, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP8)&&defined(GPIOPOM8)
	if (gpio == GPIOP8)
	{
		gpio_pin_mode_set(GPIOPOM8, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP9)&&defined(GPIOPOM9)
	if (gpio == GPIOP9)
	{
		gpio_pin_mode_set(GPIOPOM9, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP10)&&defined(GPIOPOM10)
	if (gpio == GPIOP10)
	{
		gpio_pin_mode_set(GPIOPOM10, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP11)&&defined(GPIOPOM11)
	if (gpio == GPIOP11)
	{
		gpio_pin_mode_set(GPIOPOM11, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP12)&&defined(GPIOPOM12)
	if (gpio == GPIOP12)
	{
		gpio_pin_mode_set(GPIOPOM12, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP13)&&defined(GPIOPOM13)
	if (gpio == GPIOP13)
	{
		gpio_pin_mode_set(GPIOPOM13, pin);
		//---�˳�����
		return;
	}
#endif

#if (MODULE_LOG_GPIO>0)
	else
	{
		LOG_VA_ARGS("�˿������©ģʽ����:��֧�ֵĶ˿���Ϣ\r\n");
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����ģʽ
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void gpio_pin_mode_digital(GPIO_TypeDef *gpio,uint32_t pin)
{
#if defined(GPIOP0)&&defined(GPIOPMC0)
	if (gpio == GPIOP0)
	{
		gpio_pin_mode_reset(GPIOPMC0, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP1)&&defined(GPIOPMC1)
	if (gpio == GPIOP1)
	{
		gpio_pin_mode_reset(GPIOPMC1, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP2)&&defined(GPIOPMC2)
	if (gpio == GPIOP2)
	{
		gpio_pin_mode_reset(GPIOPMC2, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP3)&&defined(GPIOPMC3)
	if (gpio == GPIOP3)
	{
		gpio_pin_mode_reset(GPIOPMC3, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP4)&&defined(GPIOPMC4)
	if (gpio == GPIOP4)
	{
		gpio_pin_mode_reset(GPIOPMC4, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIO5)&&defined(GPIOPMC5)
	if (gpio == GPIOP5)
	{
		gpio_pin_mode_reset(GPIOPMC5, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP6)&&defined(GPIOPMC6)
	if (gpio == GPIOP6)
	{
		gpio_pin_mode_reset(GPIOPMC6, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP7)&&defined(GPIOPMC7)
	if (gpio == GPIOP7)
	{
		gpio_pin_mode_reset(GPIOPMC7, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP8)&&defined(GPIOPMC8)
	if (gpio == GPIOP8)
	{
		gpio_pin_mode_reset(GPIOPMC8, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP9)&&defined(GPIOPMC9)
	if (gpio == GPIOP9)
	{
		gpio_pin_mode_reset(GPIOPMC9, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP10)&&defined(GPIOPMC10)
	if (gpio == GPIOP10)
	{
		gpio_pin_mode_reset(GPIOPMC10, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP11)&&defined(GPIOPMC11)
	if (gpio == GPIOP11)
	{
		gpio_pin_mode_reset(GPIOPMC11, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP12)&&defined(GPIOPMC12)
	if (gpio == GPIOP12)
	{
		gpio_pin_mode_reset(GPIOPMC12, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP13)&&defined(GPIOPMC13)
	if (gpio == GPIOP13)
	{
		gpio_pin_mode_reset(GPIOPMC13, pin);
		//---�˳�����
		return;
	}
#endif

#if (MODULE_LOG_GPIO>0)
	else
	{
		LOG_VA_ARGS("�˿�����ģʽ����:��֧�ֵĶ˿���Ϣ\r\n");
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ģ��ģʽ
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void gpio_pin_mode_analog(GPIO_TypeDef *gpio,uint32_t pin)
{
#if defined(GPIOP0)&&defined(GPIOPMC0)
	if (gpio == GPIOP0)
	{
		gpio_pin_mode_set(GPIOPMC0, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP1)&&defined(GPIOPMC1)
	if (gpio == GPIOP1)
	{
		gpio_pin_mode_set(GPIOPMC1, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP2)&&defined(GPIOPMC2)
	if (gpio == GPIOP2)
	{
		gpio_pin_mode_set(GPIOPMC2, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP3)&&defined(GPIOPMC3)
	if (gpio == GPIOP3)
	{
		gpio_pin_mode_set(GPIOPMC3, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP4)&&defined(GPIOPMC4)
	if (gpio == GPIOP4)
	{
		gpio_pin_mode_set(GPIOPMC4, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP5)&&defined(GPIOPMC5)
	if (gpio == GPIOP5)
	{
		gpio_pin_mode_set(GPIOPMC5, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP6)&&defined(GPIOPMC6)
	if (gpio == GPIOP6)
	{
		gpio_pin_mode_set(GPIOPMC6, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP7)&&defined(GPIOPMC7)
	if (gpio == GPIOP7)
	{
		gpio_pin_mode_set(GPIOPMC7, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP8)&&defined(GPIOPMC8)
	if (gpio == GPIOP8)
	{
		gpio_pin_mode_set(GPIOPMC8, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP9)&&defined(GPIOPMC9)
	if (gpio == GPIOP9)
	{
		gpio_pin_mode_set(GPIOPMC9, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP10)&&defined(GPIOPMC10)
	if (gpio == GPIOP10)
	{
		gpio_pin_mode_set(GPIOPMC10, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP11)&&defined(GPIOPMC11)
	if (gpio == GPIOP11)
	{
		gpio_pin_mode_set(GPIOPMC11, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP12)&&defined(GPIOPMC12)
	if (gpio == GPIOP12)
	{
		gpio_pin_mode_set(GPIOPMC12, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP13)&&defined(GPIOPMC13)
	if (gpio == GPIOP13)
	{
		gpio_pin_mode_set(GPIOPMC13, pin);
		//---�˳�����
		return;
	}
#endif

#if (MODULE_LOG_GPIO>0)
	else
	{
		LOG_VA_ARGS("�˿�ģ��ģʽ����:��֧�ֵĶ˿���Ϣ\r\n");
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����IO�˿���ӳ��
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void gpio_pin_mode_ior_set(GPIO_TypeDef *gpio,uint32_t pin)
{
#if defined(GPIOP0)&&defined(GPIOPIOR0)
	if (gpio == GPIOP0)
	{
		gpio_pin_mode_set(GPIOPIOR0, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP1)&&defined(GPIOPIOR1)
	if (gpio == GPIOP1)
	{
		gpio_pin_mode_set(GPIOPIOR1, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP2)&&defined(GPIOPIOR2)
	if (gpio == GPIOP2)
	{
		gpio_pin_mode_set(GPIOPIOR2, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP3)&&defined(GPIOPIOR3)
	if (gpio == GPIOP3)
	{
		gpio_pin_mode_set(GPIOPIOR3, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP4)&&defined(GPIOPIOR4)
	if (gpio == GPIOP4)
	{
		gpio_pin_mode_set(GPIOPIOR4, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP5)&&defined(GPIOPIOR5)
	if (gpio == GPIOP5)
	{
		gpio_pin_mode_set(GPIOPIOR5, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP6)&&defined(GPIOPIOR6)
	if (gpio == GPIOP6)
	{
		gpio_pin_mode_set(GPIOPIOR6, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP7)&&defined(GPIOPIOR7)
	if (gpio == GPIOP7)
	{
		gpio_pin_mode_set(GPIOPMC7, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP8)&&defined(GPIOPIOR8)
	if (gpio == GPIOP8)
	{
		gpio_pin_mode_set(GPIOPMC8, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP9)&&defined(GPIOPIOR9)
	if (gpio == GPIOP9)
	{
		gpio_pin_mode_set(GPIOPMC9, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP10)&&defined(GPIOPIOR10)
	if (gpio == GPIOP10)
	{
		gpio_pin_mode_set(GPIOPMC10, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP11)&&defined(GPIOPIOR11)
	if (gpio == GPIOP11)
	{
		gpio_pin_mode_set(GPIOPMC11, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP12)&&defined(GPIOPIOR12)
	if (gpio == GPIOP12)
	{
		gpio_pin_mode_set(GPIOPIOR12, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP13)&&defined(GPIOPIOR13)
	if (gpio == GPIOP13)
	{
		gpio_pin_mode_set(GPIOPIOR13, pin);
		//---�˳�����
		return;
	}
#endif

#if (MODULE_LOG_GPIO>0)
	else
	{
		LOG_VA_ARGS("�˿ڸ�����������:��֧�ֵĶ˿���Ϣ\r\n");
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��λIO�˿���ӳ��
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void gpio_pin_mode_ior_reset(GPIO_TypeDef *gpio,uint32_t pin)
{
#if defined(GPIOP0)&&defined(GPIOPIOR0)
	if (gpio == GPIOP0)
	{
		gpio_pin_mode_reset(GPIOPIOR0, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP1)&&defined(GPIOPIOR1)
	if (gpio == GPIOP1)
	{
		gpio_pin_mode_reset(GPIOPIOR1, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP2)&&defined(GPIOPIOR2)
	if (gpio == GPIOP2)
	{
		gpio_pin_mode_reset(GPIOPIOR2, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP3)&&defined(GPIOPIOR3)
	if (gpio == GPIOP3)
	{
		gpio_pin_mode_reset(GPIOPIOR3, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP4)&&defined(GPIOPIOR4)
	if (gpio == GPIOP4)
	{
		gpio_pin_mode_reset(GPIOPIOR4, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP5)&&defined(GPIOPIOR5)
	if (gpio == GPIOP5)
	{
		gpio_pin_mode_reset(GPIOPIOR5, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP6)&&defined(GPIOPIOR6)
	if (gpio == GPIOP6)
	{
		gpio_pin_mode_reset(GPIOPIOR6, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP7)&&defined(GPIOPIOR7)
	if (gpio == GPIOP7)
	{
		gpio_pin_mode_reset(GPIOPMC7, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP8)&&defined(GPIOPIOR8)
	if (gpio == GPIOP8)
	{
		gpio_pin_mode_reset(GPIOPMC8, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP9)&&defined(GPIOPIOR9)
	if (gpio == GPIOP9)
	{
		gpio_pin_mode_reset(GPIOPMC9, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP10)&&defined(GPIOPIOR10)
	if (gpio == GPIOP10)
	{
		gpio_pin_mode_reset(GPIOPMC10, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP11)&&defined(GPIOPIOR11)
	if (gpio == GPIOP11)
	{
		gpio_pin_mode_reset(GPIOPMC11, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP12)&&defined(GPIOPIOR12)
	if (gpio == GPIOP12)
	{
		gpio_pin_mode_reset(GPIOPMC12, pin);
		//---�˳�����
		return;
	}
#endif
#if defined(GPIOP13)&&defined(GPIOPIOR13)
	if (gpio == GPIOP13)
	{
		gpio_pin_mode_reset(GPIOPMC13, pin);
		//---�˳�����
		return;
	}
#endif

#if (MODULE_LOG_GPIO>0)
	else
	{
		LOG_VA_ARGS("�˿ڸ�����������:��֧�ֵĶ˿���Ϣ\r\n");
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����GPIO���1
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void gpio_pin_set(GPIO_TypeDef *gpio,uint32_t pin)
{
	switch(pin)
	{
		case GPIO_PIN_BIT_0:
		{
			(*gpio)|=GPIO_PIN_BIT_0;
			break;
		}
		case GPIO_PIN_BIT_1:
		{
			(*gpio)|=GPIO_PIN_BIT_1;
			break;
		}
		case GPIO_PIN_BIT_2:
		{
			(*gpio)|=GPIO_PIN_BIT_2;			
			break;
		}
		case GPIO_PIN_BIT_3:
		{
			(*gpio)|=GPIO_PIN_BIT_3;
			break;
		}
		case GPIO_PIN_BIT_4:
		{
			(*gpio)|=GPIO_PIN_BIT_4;
			break;
		}
		case GPIO_PIN_BIT_5:
		{
			(*gpio)|=GPIO_PIN_BIT_5;
			break;
		}
		case GPIO_PIN_BIT_6:
		{
			(*gpio)|=GPIO_PIN_BIT_6;
			break;
		}
		case GPIO_PIN_BIT_7:
		{
			(*gpio)|=GPIO_PIN_BIT_7;
			break;
		}
		case GPIO_PIN_BIT_ALL:
		default:
		{
			(*gpio)|=GPIO_PIN_BIT_ALL;
			break;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����GPIO�����λ
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void gpio_set(GPIO_HandleType* gpio)
{
	gpio_pin_set(gpio->msg_p_port, gpio->msg_bit);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����GPIO���0
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void gpio_pin_reset(GPIO_TypeDef *gpio,uint32_t pin)
{
	switch(pin)
	{
		case GPIO_PIN_BIT_0:
		{
			(*gpio)&=(~GPIO_PIN_BIT_0);
			break;
		}
		case GPIO_PIN_BIT_1:
		{
			(*gpio)&=(~GPIO_PIN_BIT_1);
			break;
		}
		case GPIO_PIN_BIT_2:
		{
			(*gpio)&=(~GPIO_PIN_BIT_2);			
			break;
		}
		case GPIO_PIN_BIT_3:
		{
			(*gpio)&=(~GPIO_PIN_BIT_3);
			break;
		}
		case GPIO_PIN_BIT_4:
		{
			(*gpio)&=(~GPIO_PIN_BIT_4);
			break;
		}
		case GPIO_PIN_BIT_5:
		{
			(*gpio)&=(~GPIO_PIN_BIT_5);
			break;
		}
		case GPIO_PIN_BIT_6:
		{
			(*gpio)&=(~GPIO_PIN_BIT_6);
			break;
		}
		case GPIO_PIN_BIT_7:
		{
			(*gpio)&=(~GPIO_PIN_BIT_7);
			break;
		}
		case GPIO_PIN_BIT_ALL:
		default:
		{
			(*gpio)&=(~GPIO_PIN_BIT_ALL);
			break;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����GPIO�������
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void gpio_reset(GPIO_HandleType* gpio)
{
	gpio_pin_reset(gpio->msg_p_port, gpio->msg_bit);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����GPIO���ȡ��
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void gpio_pin_toggle(GPIO_TypeDef *gpio,uint32_t pin)
{
	switch(pin)
	{
		case GPIO_PIN_BIT_0:
		{
			(*gpio)^=GPIO_PIN_BIT_0;
			break;
		}
		case GPIO_PIN_BIT_1:
		{
			(*gpio)^=GPIO_PIN_BIT_1;
			break;
		}
		case GPIO_PIN_BIT_2:
		{
			(*gpio)^=GPIO_PIN_BIT_2;			
			break;
		}
		case GPIO_PIN_BIT_3:
		{
			(*gpio)^=GPIO_PIN_BIT_3;
			break;
		}
		case GPIO_PIN_BIT_4:
		{
			(*gpio)^=GPIO_PIN_BIT_4;
			break;
		}
		case GPIO_PIN_BIT_5:
		{
			(*gpio)^=GPIO_PIN_BIT_5;
			break;
		}
		case GPIO_PIN_BIT_6:
		{
			(*gpio)^=GPIO_PIN_BIT_6;
			break;
		}
		case GPIO_PIN_BIT_7:
		{
			(*gpio)^=GPIO_PIN_BIT_7;
			break;
		}
		case GPIO_PIN_BIT_ALL:
		default:
		{
			(*gpio)^=GPIO_PIN_BIT_ALL;
			break;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����GPIO���ȡ��
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void gpio_toggle(GPIO_HandleType* gpio)
{
	gpio_pin_toggle(gpio->msg_p_port, gpio->msg_bit);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ȡ����˿ڵĵ�ƽ
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint32_t gpio_pin_read(GPIO_TypeDef *gpio,uint32_t pin)
{
	return ((((*gpio)&pin)!=0)?1:0);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ȡ����˿ڵĵ�ƽ
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint32_t gpio_read(GPIO_HandleType* gpio)
{
	return gpio_pin_read(gpio->msg_p_port, gpio->msg_bit);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: �˿���ʱ�ȴ�״̬
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t gpio_wait_time(uint32_t wait_time)
{
	//---��ȡ��ǰʱ�����
	uint32_t cnt = gpio_time_tick();
	//---���ʱ�䵽��
	while (1)
	{
		//---�ж��Ƿ�ʱ
		if (TIME_SPAN(gpio_time_tick(), cnt) > wait_time)
		{
			//---���ͷ�����ʱ����
			break;
		}
		WDT_RESET();
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: �˿���λ��֮����ʱһ��ʱ��
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void gpio_set_wait_time(GPIO_HandleType* gpio, uint32_t wait_time)
{
	gpio_pin_set(gpio->msg_p_port, gpio->msg_bit);
	gpio_wait_time(wait_time);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: �˿����㣬֮����ʱһ��ʱ��
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void gpio_reset_wait_time(GPIO_HandleType* gpio, uint32_t wait_time)
{
	gpio_pin_reset(gpio->msg_p_port, gpio->msg_bit);
	gpio_wait_time(wait_time);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: �˿�ȡ����֮����ʱһ��ʱ��
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void gpio_toggle_wait_time(GPIO_HandleType* gpio, uint32_t wait_time)
{
	gpio_pin_toggle(gpio->msg_p_port, gpio->msg_bit);
	gpio_wait_time(wait_time);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ȡ�˿ڵ�ƽ״̬
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t gpio_read_level_wait_time(GPIO_HandleType* gpio, uint8_t highlevel,uint32_t waittime)
{
	//---��ȡ��ǰʱ�����
	uint32_t cnt = gpio_time_tick();
	//---�����շ�
	while (1)
	{
		//---��ȡ�˿ڵ�ƽ״̬
		if (gpio_read(gpio) == highlevel)
		{
			//---�˳�ѭ��
			break;
		}
		//---�ж��Ƿ�ʱ
		if (TIME_SPAN(gpio_time_tick(), cnt) > waittime)
		{
			//---���ͷ�����ʱ����
			return ERROR_1;
		}
		WDT_RESET();
	}
	return OK_0;
}