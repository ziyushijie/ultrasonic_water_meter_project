#include "at24cxx_cfg.h"

//===ȫ�ֱ�������
AT24CXX_HandleType		g_at24cxx_one = { 0 };
pAT24CXX_HandleType		p_at24cxx_one = &g_at24cxx_one;

///////////////////////////////////////////////////////////////////////////////
//////��		��: 
//////��		��: AT24Cxx������
//////�������: 
//////�������: 
//////˵		��: 
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_i2c_device_type(AT24CXX_HandleType* AT24Cx)
{
	//---����ҳ�����ֽ�����
	if (AT24Cx->msg_type == AT24C01)																					//at24c01
	{
		AT24Cx->msg_page_num = 16;
		AT24Cx->msg_page_byte = 8;
	}
	else if (AT24Cx->msg_type == AT24C02)																				//at24c02
	{
		AT24Cx->msg_page_num = 32;
		AT24Cx->msg_page_byte = 8;
	}
	else if (AT24Cx->msg_type == AT24C04)																				//at24c04
	{
		AT24Cx->msg_page_num = 32;
		AT24Cx->msg_page_byte = 16;
	}
	else if (AT24Cx->msg_type == AT24C08)																				//at24c08
	{
		AT24Cx->msg_page_num = 64;
		AT24Cx->msg_page_byte = 16;
	}
	else if (AT24Cx->msg_type == AT24C16)																				//at24c16
	{
		AT24Cx->msg_page_num = 128;
		AT24Cx->msg_page_byte = 16;
	}
	else if (AT24Cx->msg_type == AT24C32)																				//at24c32
	{
		AT24Cx->msg_page_num = 128;
		AT24Cx->msg_page_byte = 32;
	}
	else if (AT24Cx->msg_type == AT24C64)																				//at24c64
	{
		AT24Cx->msg_page_num = 256;
		AT24Cx->msg_page_byte = 32;
	}
	else if (AT24Cx->msg_type == AT24C128)																				//at24c128
	{
		AT24Cx->msg_page_num = 256;
		AT24Cx->msg_page_byte = 64;
	}
	else if (AT24Cx->msg_type == AT24C256)																				//at24c256
	{
		AT24Cx->msg_page_num = 512;
		AT24Cx->msg_page_byte = 64;
	}
	else if (AT24Cx->msg_type == AT24C512)																				//at24c512
	{
		AT24Cx->msg_page_num = 512;
		AT24Cx->msg_page_byte = 128;
	}
	else
	{
		return ERROR_1;
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
uint8_t at24cxx_i2c_init_one(AT24CXX_HandleType* AT24Cx)
{
	AT24Cx->msg_type = AT24CXX_CHIP_TYPE_ONE;
	AT24Cx->msg_i2cx.msg_gpio_scl.msg_p_port = AT24CXX_I2C_SCL_PORT_ONE;
	AT24Cx->msg_i2cx.msg_gpio_scl.msg_bit = AT24CXX_I2C_SCL_BIT_ONE;
	AT24Cx->msg_i2cx.msg_gpio_sda.msg_p_port = AT24CXX_I2C_SDA_PORT_ONE;
	AT24Cx->msg_i2cx.msg_gpio_sda.msg_bit = AT24CXX_I2C_SDA_BIT_ONE;
	AT24Cx->msg_i2cx.msg_hw_mode = AT24CXX_ENABLE_HW_I2C_ONE;
	AT24Cx->msg_i2cx.msg_pluse_width = AT24CXX_I2C_PLUSE_WIDTH_ONE;
	AT24Cx->msg_i2cx.msg_f_delay_us = NULL;
	AT24Cx->msg_i2cx.msg_addr = AT24CXX_WRITE_ADDR_ONE;
	//---����ҳ�����ֽ�����
	return at24cxx_i2c_device_type(AT24Cx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��:
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_i2c_init_two(AT24CXX_HandleType* AT24Cx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��:
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_i2c_init_three(AT24CXX_HandleType* AT24Cx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��:
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
void at24cxx_i2c_time_tick_init(AT24CXX_HandleType* AT24Cx, uint32_t(*func_time_tick)(void))
{
	(func_time_tick != NULL) ?
		(i2c_task_time_tick_init(&(AT24Cx->msg_i2cx), func_time_tick)) :
		(i2c_task_time_tick_init(&(AT24Cx->msg_i2cx), sys_tick_task_get_tick));
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ��:
//////��	   ��:
//////�������:is_hw_i2c---1 Ӳ����0 ���
//////�������:
//////˵	   ��:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_i2c_init(AT24CXX_HandleType* AT24Cx,
	void(*func_delay_us)(uint32_t delay),
	void(*func_delay_ms)(uint32_t delay),
	uint32_t(*func_time_tick)(void), uint8_t is_hw)
{
	uint8_t _return = OK_0;
	//---ָ���豸�ĳ�ʼ��
	if ((AT24Cx != NULL) && (AT24Cx == AT24CXX_TASK_ONE))
	{
		_return = at24cxx_i2c_init_one(AT24Cx);
	}
	else if ((AT24Cx != NULL) && (AT24Cx == AT24CXX_TASK_TWO))
	{
		_return = at24cxx_i2c_init_two(AT24Cx);
	}
	else if ((AT24Cx != NULL) && (AT24Cx == AT24CXX_TASK_THREE))
	{
		_return = at24cxx_i2c_init_three(AT24Cx);
	}
	else
	{
		return ERROR_1;
	}
	i2c_task_msw_init(&(AT24Cx->msg_i2cx), func_delay_us, func_time_tick);
	//---������ʱ������ע��
	(func_delay_ms != NULL) ?
		(AT24Cx->msg_f_delay_ms = func_delay_ms) :
		(AT24Cx->msg_f_delay_ms = delay_task_ms);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��:	ע��I2C������
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_i2c_deinit(AT24CXX_HandleType* AT24Cx)
{
	return i2c_task_msw_deinit(&(AT24Cx->msg_i2cx));
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��:
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_sw_i2c_send_single_byte(AT24CXX_HandleType* AT24Cx, uint16_t addr, uint8_t buffer)
{
	uint8_t _return = OK_0;
	//---�����豸�ĵ�ַ�����ں���ָ�
	uint16_t deviceaddr = AT24Cx->msg_i2cx.msg_addr;
	//---����豸����
	if (AT24Cx->msg_type > AT24C16)
	{
		//---����IIC������������ַ��д����
		_return = i2c_task_msw_start(&(AT24Cx->msg_i2cx), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
		//---���ͼĴ�����ַ,�ߵ�ַ
		i2c_task_msw_send_byte(&(AT24Cx->msg_i2cx), (uint8_t)(addr >> 8));
		//---��ȡACK
		_return = i2c_task_msw_read_ack(&(AT24Cx->msg_i2cx));
		if (_return != OK_0)
		{
			//---��������ʧ��
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24Cx->msg_i2cx.msg_addr += (((addr >> 8) << 1) & 0x0F);
		//---����IIC������������ַ��д����
		_return = i2c_task_msw_start(&(AT24Cx->msg_i2cx), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---���ͼĴ�����ַ,��λ��ַ
	i2c_task_msw_send_byte(&(AT24Cx->msg_i2cx), (uint8_t)(addr & 0xFF));
	//---��ȡACK
	_return = i2c_task_msw_read_ack(&(AT24Cx->msg_i2cx));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---���ݷ���
	i2c_task_msw_send_byte(&(AT24Cx->msg_i2cx), buffer);
	//---��ȡACK
	_return = i2c_task_msw_read_ack(&(AT24Cx->msg_i2cx));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_4;
		goto GoToExit;
	}
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	i2c_task_msw_stop(&(AT24Cx->msg_i2cx));
	//---�ָ��豸�ĵ�ַ
	AT24Cx->msg_i2cx.msg_addr = deviceaddr;
	//---������ȷ��������ʱ�ȴ���̽���
	if (_return == OK_0)
	{
		//---�Ա��ʱ����5ms
		if (AT24Cx->msg_f_delay_ms != NULL)
		{
			AT24Cx->msg_f_delay_ms(5);
		}
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
uint8_t at24cxx_sw_i2c_send_page_byte(AT24CXX_HandleType* AT24Cx, uint16_t page_addr, uint8_t* buffer, uint16_t length)
{
	//---�ж�ҳ�ź�ҳ�ڵ�����
	if (length > AT24Cx->msg_page_byte)
	{
		length = AT24Cx->msg_page_byte;
	}
	uint8_t _return = OK_0;
	//---�����豸�ĵ�ַ�����ں���ָ�
	uint16_t at24cxxAddr = AT24Cx->msg_i2cx.msg_addr;
	uint16_t i = 0;
	//---����豸����
	if (AT24Cx->msg_type > AT24C16)
	{
		//---����IIC������������ַ��д����
		_return = i2c_task_msw_start(&(AT24Cx->msg_i2cx), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
		//---���ͼĴ�����ַ,�ߵ�ַ
		i2c_task_msw_send_byte(&(AT24Cx->msg_i2cx), (uint8_t)(page_addr >> 8));
		//---��ȡACK
		_return = i2c_task_msw_read_ack(&(AT24Cx->msg_i2cx));
		if (_return != OK_0)
		{
			//---��������ʧ��
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24Cx->msg_i2cx.msg_addr += (((page_addr >> 8) << 1) & 0x0F);
		//---����IIC������������ַ��д����
		_return = i2c_task_msw_start(&(AT24Cx->msg_i2cx), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---���ͼĴ�����ַ,��λ��ַ
	i2c_task_msw_send_byte(&(AT24Cx->msg_i2cx), (uint8_t)(page_addr & 0xFF));
	//---��ȡACK
	_return = i2c_task_msw_read_ack(&(AT24Cx->msg_i2cx));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---���ݷ���
	for (i = 0; i < length; i++)
	{
		i2c_task_msw_send_byte(&(AT24Cx->msg_i2cx), buffer[i]);
		//---��ȡACK
		_return = i2c_task_msw_read_ack(&(AT24Cx->msg_i2cx));
		//---�ж���ȷ��
		if (_return != OK_0)
		{
			//---��������ʧ��
			_return = ERROR_4;
			goto GoToExit;
		}
	}
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	i2c_task_msw_stop(&(AT24Cx->msg_i2cx));
	//---�ָ��豸�ĵ�ַ
	AT24Cx->msg_i2cx.msg_addr = at24cxxAddr;
	//---������ȷ��������ʱ�ȴ���̽���
	if (_return == OK_0)
	{
		//---�Ա��ʱ����5ms
		if (AT24Cx->msg_f_delay_ms != NULL)
		{
			AT24Cx->msg_f_delay_ms(5);
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ��:
//////��	   ��:��ȡ�Ĵ���
//////�������:
//////�������:
//////˵	   ��:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_sw_i2c_read_single_byte(AT24CXX_HandleType* AT24Cx, uint16_t addr, uint8_t* buffer)
{
	uint8_t _return = OK_0;
	//---�����豸�ĵ�ַ�����ں���ָ�
	uint16_t at24cxxAddr = AT24Cx->msg_i2cx.msg_addr;
	//---����豸����
	if (AT24Cx->msg_type > AT24C16)
	{
		//---����IIC������������ַ��д����
		_return = i2c_task_msw_start(&(AT24Cx->msg_i2cx), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
		//---���ͼĴ�����ַ,�ߵ�ַ
		i2c_task_msw_send_byte(&(AT24Cx->msg_i2cx), (uint8_t)(addr >> 8));
		//---��ȡACK
		_return = i2c_task_msw_read_ack(&(AT24Cx->msg_i2cx));
		if (_return != OK_0)
		{
			//---��������ʧ��
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24Cx->msg_i2cx.msg_addr += (((addr >> 8) << 1) & 0x0F);
		//---����IIC������������ַ��д����
		_return = i2c_task_msw_start(&(AT24Cx->msg_i2cx), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---���ͼĴ�����ַ,��λ��ַ
	i2c_task_msw_send_byte(&(AT24Cx->msg_i2cx), (uint8_t)(addr & 0xFF));
	//---��ȡACK
	_return = i2c_task_msw_read_ack(&(AT24Cx->msg_i2cx));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = i2c_task_msw_start(&(AT24Cx->msg_i2cx), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_4;
		goto GoToExit;
	}
	//---��ȡ����
	*buffer = i2c_task_msw_read_byte(&(AT24Cx->msg_i2cx));
	//---���Ͳ�Ӧ���ź�
	i2c_task_msw_send_ack(&(AT24Cx->msg_i2cx), 1);
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	i2c_task_msw_stop(&(AT24Cx->msg_i2cx));
	AT24Cx->msg_i2cx.msg_addr = at24cxxAddr;
	return _return;
}
///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��:
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_sw_i2c_read_page_byte(AT24CXX_HandleType* AT24Cx, uint16_t addr, uint8_t* buffer, uint16_t length)
{
	//---�ж�ҳ�ź�ҳ�ڵ�����
	if (length > AT24Cx->msg_page_byte)
	{
		length = AT24Cx->msg_page_byte;
	}
	uint8_t _return = OK_0;
	//---�����豸�ĵ�ַ�����ں���ָ�
	uint16_t deviceaddr = AT24Cx->msg_i2cx.msg_addr;
	uint16_t i = 0;
	//---����豸����
	if (AT24Cx->msg_type > AT24C16)
	{
		//---����IIC������������ַ��д����
		_return = i2c_task_msw_start(&(AT24Cx->msg_i2cx), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
		//---���ͼĴ�����ַ,�ߵ�ַ
		i2c_task_msw_send_byte(&(AT24Cx->msg_i2cx), (uint8_t)(addr >> 8));
		//---��ȡACK
		_return = i2c_task_msw_read_ack(&(AT24Cx->msg_i2cx));
		if (_return != OK_0)
		{
			//---��������ʧ��
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24Cx->msg_i2cx.msg_addr += (((addr >> 8) << 1) & 0x0F);
		//---����IIC������������ַ��д����
		_return = i2c_task_msw_start(&(AT24Cx->msg_i2cx), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---���ͼĴ�����ַ,��λ��ַ
	i2c_task_msw_send_byte(&(AT24Cx->msg_i2cx), (uint8_t)(addr & 0xFF));
	//---��ȡACK
	_return = i2c_task_msw_read_ack(&(AT24Cx->msg_i2cx));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = i2c_task_msw_start(&(AT24Cx->msg_i2cx), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_4;
		goto GoToExit;
	}
	//---ѭ����ȡָ�����ȵ�����
	for (i = 0; i < length; i++)
	{
		//---��ȡ����
		buffer[i] = i2c_task_msw_read_byte(&(AT24Cx->msg_i2cx));
		//---����Ӧ���ź�
		i2c_task_msw_send_ack(&(AT24Cx->msg_i2cx), (i == (length - 1)) ? 1 : 0);
	}
	_return = OK_0;
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	i2c_task_msw_stop(&(AT24Cx->msg_i2cx));
	AT24Cx->msg_i2cx.msg_addr = deviceaddr;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��:
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_sw_i2c_read_byte(AT24CXX_HandleType* AT24Cx, uint16_t addr, uint8_t* buffer, uint16_t length)
{
	uint8_t _return = OK_0;
	//---�����豸�ĵ�ַ�����ں���ָ�
	uint16_t deviceaddr = AT24Cx->msg_i2cx.msg_addr;
	uint16_t i = 0;
	uint32_t cnt = 0;
	//---����豸����
	if (AT24Cx->msg_type > AT24C16)
	{
		//---����IIC������������ַ��д����
		_return = i2c_task_msw_start(&(AT24Cx->msg_i2cx), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
		//---���ͼĴ�����ַ,�ߵ�ַ
		i2c_task_msw_send_byte(&(AT24Cx->msg_i2cx), (uint8_t)(addr >> 8));
		//---��ȡACK
		_return = i2c_task_msw_read_ack(&(AT24Cx->msg_i2cx));
		if (_return != OK_0)
		{
			//---��������ʧ��
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24Cx->msg_i2cx.msg_addr += (((addr >> 8) << 1) & 0x0F);
		//---����IIC������������ַ��д����
		_return = i2c_task_msw_start(&(AT24Cx->msg_i2cx), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---���ͼĴ�����ַ,��λ��ַ
	i2c_task_msw_send_byte(&(AT24Cx->msg_i2cx), (uint8_t)(addr & 0xFF));
	//---��ȡACK
	_return = i2c_task_msw_read_ack(&(AT24Cx->msg_i2cx));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = i2c_task_msw_start(&(AT24Cx->msg_i2cx), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_4;
		goto GoToExit;
	}
	//---ͬ��ʱ��
	cnt = AT24Cx->msg_i2cx.msg_f_time_tick();
	//---ѭ����ȡָ�����ȵ�����
	for (i = 0; i < length; i++)
	{
		//---��ȡ����
		buffer[i] = i2c_task_msw_read_byte(&(AT24Cx->msg_i2cx));
		//---����Ӧ���ź�
		i2c_task_msw_send_ack(&(AT24Cx->msg_i2cx), (i == (length - 1)) ? 1 : 0);
		//---У��ʱ���ȣ����⿴�Ź���λ
		if (TIME_SPAN(AT24Cx->msg_i2cx.msg_f_time_tick(), cnt) > AT24CXX_WAIT_MAX_TIME)
		{
			//---ͬ��ʱ��
			cnt = AT24Cx->msg_i2cx.msg_f_time_tick();
			//---ι��
			WDT_RESET();
		}
	}
	_return = OK_0;
	//---�˳����������
GoToExit:
	//---����ֹͣ�ź�
	i2c_task_msw_stop(&(AT24Cx->msg_i2cx));
	AT24Cx->msg_i2cx.msg_addr = deviceaddr;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��:
//////�������:
//////�������:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_sw_i2c_send_byte(AT24CXX_HandleType* AT24Cx, uint16_t addr, uint8_t* buffer, uint16_t length)
{
	//---Ҫд��ҳ��
	uint16_t pageNum = 0;
	//---����ҳҪд����ֽ���
	uint16_t byteNum = 0;
	//---ҳ��ַ������ʼҳ������
	uint16_t pageIndexAddr = addr / (AT24Cx->msg_page_byte);
	//---����һҳ������
	uint16_t byteIndexAddr = addr % (AT24Cx->msg_page_byte);
	//---����һҳ������Ҫд����ֽ���
	uint16_t pageByteNum = AT24Cx->msg_page_byte - byteIndexAddr;
	//---
	uint16_t i = 0;
	uint8_t _return = OK_0;
	uint32_t cnt = 0;
	//---������д���д�������Ϊ��
	if ((length == 0) || (buffer == NULL))
	{
		return ERROR_6;
	}
	//---���ݳ��ȵĴ�С
	if (length <= pageByteNum)
	{
		pageByteNum = length;
	}
	//---��Ҫд������ݲ�����2�ֽڵ�ʱ�򣬰�ҳд��Ͱ��ֽ�д�����ĵ�ʱ�������ͬ
	if (length < 3)
	{
		//---���ֽ�д��
		for (i = 0; i < length; i++)
		{
			_return = at24cxx_sw_i2c_send_single_byte(AT24Cx, addr, *buffer);
			addr++;
			buffer++;
			//---�ж��ǲ���д��ɹ�
			if (_return != OK_0)
			{
				return ERROR_7;
			}
		}
	}
	else
	{
		//---��ҳд��
#ifdef AT24CXX_ENABLE_DRAM
		//---�����ڴ�
		AT24Cx->msg_page_byte_buffer = (uint8_t*)my_malloc(AT24Cx->msg_page_byte);
		//---�жϻ���ռ������Ƿ�ɹ�
		if (AT24Cx->msg_page_byte_buffer == NULL)
		{
			_return = ERROR_8;
			goto GoToExit;
		}
#endif
		//---�ȵ�һҳд����д����ֽ�����С��3���ֽ�
		if (pageByteNum != AT24Cx->msg_page_byte)
		{
			//---��ȡһҳ������
#ifdef AT24CXX_ENABLE_DRAM
			_return = at24cxx_sw_i2c_read_page_byte(AT24Cx, (pageIndexAddr * (AT24Cx->msg_page_byte)), AT24Cx->msg_page_byte_buffer, (AT24Cx->msg_page_byte));
#else
			_return = at24cxx_sw_i2c_read_page_byte(AT24Cx, (pageIndexAddr * (AT24Cx->msg_page_byte)), AT24Cx->msg_page_byte_buffer, (AT24Cx->msg_page_byte));
#endif
			//---��ȡ�ж�
			if (_return != OK_0)
			{
				_return = ERROR_9;
				goto GoToExit;
			}
			//---�������
			for (i = 0; i < pageByteNum; i++)
			{
				//---������ݵ�������
#ifdef AT24CXX_ENABLE_DRAM
				AT24Cx->msg_page_byte_buffer[i + byteIndexAddr] = *buffer;
#else
				AT24Cx->msg_page_byte_buffer[i + byteIndexAddr] = *buffer;
#endif
				//---��ַƫ�ƣ�ʹ��ַƫ�Ƶ�ҳ���׵�ַ
				addr++;
				//---����ƫ��
				buffer++;
				//---���ݳ���ƫ��
				length--;
				//---����������
				if (length == 0)
				{
					//---�˳����ݵ����
					break;
				}
			}
			//---���㵱ǰҳ�е��ֽ�ƫ�Ƶ�ַ
			byteIndexAddr = 0;
			//---��ҳд������
#ifdef AT24CXX_ENABLE_DRAM
			_return = at24cxx_sw_i2c_send_page_byte(AT24Cx, (pageIndexAddr * (AT24Cx->msg_page_byte)), AT24Cx->msg_page_byte_buffer, AT24Cx->msg_page_byte);
#else
			_return = at24cxx_sw_i2c_send_page_byte(AT24Cx, (pageIndexAddr * (AT24Cx->msg_page_byte)), AT24Cx->msg_page_byte_buffer, AT24Cx->msg_page_byte);
#endif
			//---д���ж�
			if (_return != OK_0)
			{
				_return = ERROR_10;
				goto GoToExit;
			}
		}
		//---д��ҳ����
		//---����Ҫд���ҳ��
		pageNum = length / AT24Cx->msg_page_byte;
		//---�������һҳҪд����ֽ���
		byteNum = length % AT24Cx->msg_page_byte;
		//---�ж��Ƿ���Ҫҳд��
		if (pageNum != 0)
		{
			cnt = AT24Cx->msg_i2cx.msg_f_time_tick();
			//---ѭ������ҳд�����
			for (i = 0; i < pageNum; i++)
			{
				_return = at24cxx_sw_i2c_send_page_byte(AT24Cx, addr, buffer, AT24Cx->msg_page_byte);
				//---��ַƫ�ƣ�ƫ�Ƶ��´�Ҫд������ݵ�ҳ���׵�ַ
				addr += AT24Cx->msg_page_byte;
				//---����ƫ��
				buffer += AT24Cx->msg_page_byte;
				//---���ݳ���ƫ��
				length -= AT24Cx->msg_page_byte;
				//---�ж��ǲ���д��ɹ�
				if (_return != OK_0)
				{
					_return = ERROR_11;
					goto GoToExit;
				}
				//---���ʹ��ʱ��
				if (TIME_SPAN(AT24Cx->msg_i2cx.msg_f_time_tick(), cnt) > AT24CXX_WAIT_MAX_TIME)
				{
					//---ͬ��ʱ��
					cnt = AT24Cx->msg_i2cx.msg_f_time_tick();
					//---ι��
					WDT_RESET();
				}
			}
		}
		//---�ж��ǲ��ǲ���ҳ�Ĳ���
		if (byteNum != 0)
		{
			//---��ȡһҳ������
#ifdef AT24CXX_ENABLE_DRAM
			_return = at24cxx_sw_i2c_read_page_byte(AT24Cx, addr, AT24Cx->msg_page_byte_buffer, (AT24Cx->msg_page_byte));
#else
			_return = at24cxx_sw_i2c_read_page_byte(AT24Cx, addr, AT24Cx->msg_page_byte_buffer, (AT24Cx->msg_page_byte));
#endif
			//---��ȡ�ж�
			if (_return != OK_0)
			{
				_return = ERROR_12;
				goto GoToExit;
			}
			//---�������
			for (i = 0; i < pageByteNum; i++)
			{
				//---������ݵ�������
#ifdef AT24CXX_ENABLE_DRAM
				AT24Cx->msg_page_byte_buffer[i + byteIndexAddr] = *buffer;
#else
				AT24Cx->msg_page_byte_buffer[i + byteIndexAddr] = *buffer;
#endif
				//---��ַƫ�ƣ���ʱ�Ѿ���ҳ���׵�ַ�ˣ�����ֵ����ƫ����
				//addr++;
				//---����ƫ��
				buffer++;
				//---���ݳ���ƫ��
				length--;
				//---����������
				if (length == 0)
				{
					//---�˳����ݵ����
					break;
				}
			}
			//---��ҳд������
#ifdef AT24CXX_ENABLE_DRAM
			_return = at24cxx_sw_i2c_send_page_byte(AT24Cx, addr, AT24Cx->msg_page_byte_buffer, AT24Cx->msg_page_byte);
#else
			_return = at24cxx_sw_i2c_send_page_byte(AT24Cx, addr, AT24Cx->msg_page_byte_buffer, AT24Cx->msg_page_byte);
#endif
			//---д���ж�
			if (_return != OK_0)
			{
				_return = ERROR_13;
				goto GoToExit;
			}
		}
#ifdef AT24CXX_ENABLE_DRAM
	//---�˳��������
	GoToExit :
		 //---У�黺����
		 if (AT24Cx->msg_page_byte_buffer != NULL)
		 {
			 //---�ͷ��ڴ�
			 my_free(AT24Cx->msg_page_byte_buffer);
		 }
#endif
	}
#ifndef AT24CXX_ENABLE_DRAM
	GoToExit :
#endif
	return  _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_i2c_send_single_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t buffer)
{
	return at24cxx_sw_i2c_send_single_byte(AT24Cx, addr, buffer);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_i2c_send_page_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer, uint16_t length)
{
	return at24cxx_sw_i2c_send_page_byte(AT24Cx, addr, buffer,length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_i2c_send_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer, uint16_t length)
{
	return at24cxx_sw_i2c_send_byte(AT24Cx, addr, buffer,length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_i2c_read_single_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer)
{
	return at24cxx_sw_i2c_read_single_byte(AT24Cx, addr, buffer);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_i2c_read_page_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer, uint16_t length)
{
	return at24cxx_sw_i2c_read_page_byte(AT24Cx, addr, buffer,length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_i2c_read_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer, uint16_t length)
{
	return at24cxx_sw_i2c_read_byte(AT24Cx, addr, buffer,length);
}
