#include "i2c_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_init(I2C_HandleType *I2Cx, void(*func_delay_us)(uint32_t delay), uint32_t(*func_time_tick)(void))
{
	//---SCL��ʼ��
	gpio_task_pin_mode_output(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	gpio_task_pin_set(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	//---SDA��ʼ��
	gpio_task_pin_mode_input(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	gpio_task_pin_set(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	
	//---us��ʱ����
	(func_delay_us != NULL) ?
		(I2Cx->msg_f_delay_us = func_delay_us) :
		(I2Cx->msg_f_delay_us = delay_task_us);
	//---ע��δ���
	(func_time_tick != NULL) ?
		(I2Cx->msg_f_time_tick = func_time_tick) :
		(I2Cx->msg_f_time_tick = sys_tick_task_get_tick);
	//---���ģʽ
	I2Cx->msg_hw_mode = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_deinit(I2C_HandleType *I2Cx)
{
	//---SCL��ʼ��
	gpio_task_pin_mode_input(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	gpio_task_pin_set(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	//---SDA��ʼ��
	gpio_task_pin_mode_input(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	gpio_task_pin_set(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_start(I2C_HandleType *I2Cx)
{
#ifndef I2C_GPIO_SDA_MODE_OD
	//---SDA����Ϊ���
	gpio_task_pin_mode_output(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
#endif
	//---������ʼ�����������ź�
	PIN_OUT_1(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	PIN_OUT_1(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	//I2Cx->msg_f_delay_us(I2Cx->msg_pluse_width);
	//---������ʼ�ź�;
	PIN_OUT_0(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	//I2Cx->msg_f_delay_us(I2Cx->msg_pluse_width);
	//---ǯסI2C���ߣ�׼�����ͻ��������
	PIN_OUT_0(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
#ifndef I2C_GPIO_SDA_MODE_OD
	//---SDA����Ϊ����
	gpio_task_pin_mode_input(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
#endif
	//---�ж�I2C�����ź��Ƿ�ɹ�����ȡSDA��״̬�źţ��ɹ�SDA---0��ʧ��SDA---1
	return  ((PIN_GET_STATE(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit) != 0x00) ? ERROR_1 : OK_0);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_stop(I2C_HandleType *I2Cx)
{
#ifndef I2C_GPIO_SDA_MODE_OD
	//---SDA����Ϊ���
	gpio_task_pin_mode_output(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
#endif
	//---����ֹͣ�����������ź�
	PIN_OUT_0(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	PIN_OUT_1(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	//I2Cx->msg_f_delay_us(I2Cx->msg_pluse_width);
	PIN_OUT_1(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	//I2Cx->msg_f_delay_us(I2Cx->msg_pluse_width);
#ifndef I2C_GPIO_SDA_MODE_OD
	//---SDA����Ϊ����
	gpio_task_pin_mode_input(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
#endif
	//---�ж�I2C�����ź��Ƿ�ɹ�����ȡSDA��״̬�źţ��ɹ�SDA---1��ʧ��SDA---0
	return ((PIN_GET_STATE(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit) == 0x00) ? ERROR_1 : OK_0);
}
///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����ACK�ź�
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_ack(I2C_HandleType *I2Cx)
{
#ifndef I2C_GPIO_SDA_MODE_OD
	//---SDA����Ϊ���
	gpio_task_pin_mode_output(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
#endif
	PIN_OUT_0(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	PIN_OUT_1(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	PIN_OUT_0(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����NACK�ź�
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_nack(I2C_HandleType *I2Cx)
{
#ifndef I2C_GPIO_SDA_MODE_OD
	//---SDA����Ϊ���
	gpio_task_pin_mode_output(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
#endif
	PIN_OUT_1(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	PIN_OUT_1(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	PIN_OUT_0(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ȡӦ���ź�
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_read_ack(I2C_HandleType *I2Cx)
{
	uint8_t _return = OK_0;
#ifndef I2C_GPIO_SDA_MODE_OD
	//---SDA����Ϊ���
	gpio_task_pin_mode_output(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
#endif
	//---��ȡӦ���ź�
	PIN_OUT_1(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	PIN_OUT_1(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
#ifndef I2C_GPIO_SDA_MODE_OD
	//---SDA����Ϊ����
	gpio_task_pin_mode_input(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
#endif
	//---��ȡSDA��״̬�ź�---ACK״̬��SDAΪ�͵�ƽ
	_return = ((PIN_GET_STATE(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit) != 0x00) ? ERROR_1 : OK_0);
	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	PIN_OUT_0(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_wait_ack(I2C_HandleType *I2Cx)
{
	uint8_t _return = OK_0;
#ifndef I2C_GPIO_SDA_MODE_OD
	//---SDA����Ϊ���
	gpio_task_pin_mode_output(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
#endif
	//---��ȡӦ���ź�
	PIN_OUT_1(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	PIN_OUT_1(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
#ifndef I2C_GPIO_SDA_MODE_OD
	//---SDA����Ϊ����
	gpio_task_pin_mode_input(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
#endif
	//---���SDA��ƽ,SDAΪ��,����ӻ�����ACK
	_return = gpio_task_read_level_wait(&(I2Cx->msg_gpio_sda), 1);
	if (_return != OK_0)
	{
		i2c_msw_stop(I2Cx);
	}
	else
	{
		PIN_OUT_0(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	}
	return _return;
}
///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��:
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_send_ack(I2C_HandleType *I2Cx, uint8_t is_nack)
{
	return ((is_nack != 0) ? (i2c_msw_nack(I2Cx)) : (i2c_msw_ack(I2Cx)));
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����1bit����
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_send_bit(I2C_HandleType *I2Cx, uint8_t bitbuffer)
{
	((bitbuffer & 0x80) != 0x00) ?
		PIN_OUT_1(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit) :
		PIN_OUT_0(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	//---һ��ʱ������
	PIN_OUT_1(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	PIN_OUT_0(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: �����ֽ�����
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_send_byte(I2C_HandleType *I2Cx, uint8_t buffer)
{
	uint8_t i = 0;
	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	PIN_OUT_0(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
#ifndef I2C_GPIO_SDA_MODE_OD
	//---SDA����Ϊ���
	gpio_task_pin_mode_output(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
#endif
	//---����1�ֽڵ�����
	for (i = 0; i < 8; i++)
	{
		//---��ȡ1Bit������
		i2c_msw_send_bit(I2Cx, buffer);
		buffer <<= 1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��:
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_send_word(I2C_HandleType *I2Cx, uint16_t buffer)
{
	uint8_t bufferH = (uint8_t)(buffer >> 8);
	uint8_t bufferL = (uint8_t)(buffer);
	uint8_t i = 0;
	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	PIN_OUT_0(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
#ifndef I2C_GPIO_SDA_MODE_OD
	//---SDA����Ϊ���
	gpio_task_pin_mode_output(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
#endif
	//---����1�ֽڵ�����
	for (i = 0; i < 8; i++)
	{
		//---��ȡ1Bit������
		i2c_msw_send_bit(I2Cx, bufferH);
		//---�������ƶ�
		bufferH <<= 1;
	}
	//---����1�ֽڵ�����
	for (i = 0; i < 8; i++)
	{
		//---��ȡ1Bit������
		i2c_msw_send_bit(I2Cx, bufferL);
		//---��������
		bufferL <<= 1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ȡ1bit����
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_read_bit(I2C_HandleType *I2Cx)
{
	uint8_t _return = OK_0;
	//---ʱ��������
	PIN_OUT_1(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	//---��ȡ����λ
	_return = ((PIN_GET_STATE(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit) != 0x00) ? 1 : 0);
	//---ʱ�Ӹ�����
	PIN_OUT_0(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	return  _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��:
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_read_byte(I2C_HandleType *I2Cx)
{
	uint8_t i = 0;
	uint8_t _return = 0;
	//---׼�����ݵĶ�ȡ
	PIN_OUT_1(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	PIN_OUT_0(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
#ifndef I2C_GPIO_SDA_MODE_OD
	//---SDA����Ϊ����
	gpio_task_pin_mode_input(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
#endif
	//---����1�ֽڵ�����
	for (i = 0; i < 8; i++)
	{
		_return <<= 1;
		_return |= i2c_msw_read_bit(I2Cx);
	}
	return _return;
} 

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��:
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_check_device(I2C_HandleType *I2Cx)
{
	uint8_t _return = OK_0;
#ifndef I2C_GPIO_SDA_MODE_OD
	//---SDA����Ϊ����
	gpio_task_pin_mode_input(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	//---SCL����Ϊ����
	gpio_task_pin_mode_input(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
#endif
	//---���˿ڵ�״̬
	if ((PIN_GET_STATE(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit)) &&
		(PIN_GET_STATE(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit)))
	{
#ifndef I2C_GPIO_SDA_MODE_OD
		//---SDA����Ϊ����
		gpio_task_pin_mode_output(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
		//---SCL����Ϊ����
		gpio_task_pin_mode_output(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
#endif
		//---���������ź�
		i2c_msw_start(I2Cx);
		//---���Ͷ�ȡ��������
		I2Cx->msg_addr |= 0x01;
		//---���ʹӻ���ַ
		i2c_msw_send_byte(I2Cx, (uint8_t)I2Cx->msg_addr);
		//---��ȡӦ���ź�
		_return = i2c_msw_read_ack(I2Cx);
	}
	else
	{
		_return = ERROR_2;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��:
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_send_cmd(I2C_HandleType *I2Cx, uint8_t cmd, uint8_t is_start, uint8_t is_stop)
{
	uint8_t _return = OK_0;
	if (is_start)
	{
		//---�������������ź�
		_return = i2c_msw_start(I2Cx);
		if (_return)
		{
			i2c_msw_stop(I2Cx);
			return ERROR_1;
		}
	}
	//---��������
	_return = i2c_msw_send_byte(I2Cx, cmd);
	//---��ȡӦ��
	_return = i2c_msw_read_ack(I2Cx);
	//---ֹͣ����������
	if ((is_stop) || (_return))
	{
		i2c_msw_stop(I2Cx);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��:
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_master_deinit(I2C_HandleType* I2Cx)
{
	//---ע��I2C�豸
	return i2c_msw_deinit(I2Cx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��:
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void i2c_time_tick_init(I2C_HandleType* I2Cx, uint32_t(*func_time_tick)(void))
{
	//---ע��δ���
	(func_time_tick != NULL) ?
		(I2Cx->msg_f_time_tick = func_time_tick) :
		(I2Cx->msg_f_time_tick = sys_tick_task_get_tick);
}