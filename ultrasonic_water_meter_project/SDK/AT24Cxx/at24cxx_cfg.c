#include "at24cxx_cfg.h"

//===全局变量定义
AT24CXX_HandleType		g_at24cxx_one = { 0 };
pAT24CXX_HandleType		p_at24cxx_one = &g_at24cxx_one;

///////////////////////////////////////////////////////////////////////////////
//////函		数: 
//////功		能: AT24Cxx的类型
//////输入参数: 
//////输出参数: 
//////说		明: 
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_i2c_device_type(AT24CXX_HandleType* AT24Cx)
{
	//---解析页数和字节数据
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
//////函		数:
//////功		能:
//////输入参数:
//////输出参数:
//////说		明:
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
	//---解析页数和字节数据
	return at24cxx_i2c_device_type(AT24Cx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_i2c_init_two(AT24CXX_HandleType* AT24Cx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_i2c_init_three(AT24CXX_HandleType* AT24Cx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void at24cxx_i2c_time_tick_init(AT24CXX_HandleType* AT24Cx, uint32_t(*func_time_tick)(void))
{
	(func_time_tick != NULL) ?
		(i2c_task_time_tick_init(&(AT24Cx->msg_i2cx), func_time_tick)) :
		(i2c_task_time_tick_init(&(AT24Cx->msg_i2cx), sys_tick_task_get_tick));
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数:
//////功	   能:
//////输入参数:is_hw_i2c---1 硬件，0 软件
//////输出参数:
//////说	   明:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_i2c_init(AT24CXX_HandleType* AT24Cx,
	void(*func_delay_us)(uint32_t delay),
	void(*func_delay_ms)(uint32_t delay),
	uint32_t(*func_time_tick)(void), uint8_t is_hw)
{
	uint8_t _return = OK_0;
	//---指定设备的初始化
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
	//---毫秒延时函数的注册
	(func_delay_ms != NULL) ?
		(AT24Cx->msg_f_delay_ms = func_delay_ms) :
		(AT24Cx->msg_f_delay_ms = delay_task_ms);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:	注销I2C的配置
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_i2c_deinit(AT24CXX_HandleType* AT24Cx)
{
	return i2c_task_msw_deinit(&(AT24Cx->msg_i2cx));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_sw_i2c_send_single_byte(AT24CXX_HandleType* AT24Cx, uint16_t addr, uint8_t buffer)
{
	uint8_t _return = OK_0;
	//---保存设备的地址，用于后面恢复
	uint16_t deviceaddr = AT24Cx->msg_i2cx.msg_addr;
	//---检查设备类型
	if (AT24Cx->msg_type > AT24C16)
	{
		//---启动IIC并发送器件地址，写数据
		_return = i2c_task_msw_start(&(AT24Cx->msg_i2cx), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
		//---发送寄存器地址,高地址
		i2c_task_msw_send_byte(&(AT24Cx->msg_i2cx), (uint8_t)(addr >> 8));
		//---读取ACK
		_return = i2c_task_msw_read_ack(&(AT24Cx->msg_i2cx));
		if (_return != OK_0)
		{
			//---发送数据失败
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24Cx->msg_i2cx.msg_addr += (((addr >> 8) << 1) & 0x0F);
		//---启动IIC并发送器件地址，写数据
		_return = i2c_task_msw_start(&(AT24Cx->msg_i2cx), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---发送寄存器地址,低位地址
	i2c_task_msw_send_byte(&(AT24Cx->msg_i2cx), (uint8_t)(addr & 0xFF));
	//---读取ACK
	_return = i2c_task_msw_read_ack(&(AT24Cx->msg_i2cx));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---数据发送
	i2c_task_msw_send_byte(&(AT24Cx->msg_i2cx), buffer);
	//---读取ACK
	_return = i2c_task_msw_read_ack(&(AT24Cx->msg_i2cx));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_4;
		goto GoToExit;
	}
	//---退出操作入口
GoToExit:
	//---发送停止信号
	i2c_task_msw_stop(&(AT24Cx->msg_i2cx));
	//---恢复设备的地址
	AT24Cx->msg_i2cx.msg_addr = deviceaddr;
	//---操作正确，进行延时等待编程结束
	if (_return == OK_0)
	{
		//---自编程时间是5ms
		if (AT24Cx->msg_f_delay_ms != NULL)
		{
			AT24Cx->msg_f_delay_ms(5);
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_sw_i2c_send_page_byte(AT24CXX_HandleType* AT24Cx, uint16_t page_addr, uint8_t* buffer, uint16_t length)
{
	//---判断页号和页内的数据
	if (length > AT24Cx->msg_page_byte)
	{
		length = AT24Cx->msg_page_byte;
	}
	uint8_t _return = OK_0;
	//---保存设备的地址，用于后面恢复
	uint16_t at24cxxAddr = AT24Cx->msg_i2cx.msg_addr;
	uint16_t i = 0;
	//---检查设备类型
	if (AT24Cx->msg_type > AT24C16)
	{
		//---启动IIC并发送器件地址，写数据
		_return = i2c_task_msw_start(&(AT24Cx->msg_i2cx), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
		//---发送寄存器地址,高地址
		i2c_task_msw_send_byte(&(AT24Cx->msg_i2cx), (uint8_t)(page_addr >> 8));
		//---读取ACK
		_return = i2c_task_msw_read_ack(&(AT24Cx->msg_i2cx));
		if (_return != OK_0)
		{
			//---发送数据失败
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24Cx->msg_i2cx.msg_addr += (((page_addr >> 8) << 1) & 0x0F);
		//---启动IIC并发送器件地址，写数据
		_return = i2c_task_msw_start(&(AT24Cx->msg_i2cx), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---发送寄存器地址,低位地址
	i2c_task_msw_send_byte(&(AT24Cx->msg_i2cx), (uint8_t)(page_addr & 0xFF));
	//---读取ACK
	_return = i2c_task_msw_read_ack(&(AT24Cx->msg_i2cx));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---数据发送
	for (i = 0; i < length; i++)
	{
		i2c_task_msw_send_byte(&(AT24Cx->msg_i2cx), buffer[i]);
		//---读取ACK
		_return = i2c_task_msw_read_ack(&(AT24Cx->msg_i2cx));
		//---判断正确性
		if (_return != OK_0)
		{
			//---发送数据失败
			_return = ERROR_4;
			goto GoToExit;
		}
	}
	//---退出函数入口
GoToExit:
	//---发送停止信号
	i2c_task_msw_stop(&(AT24Cx->msg_i2cx));
	//---恢复设备的地址
	AT24Cx->msg_i2cx.msg_addr = at24cxxAddr;
	//---操作正确，进行延时等待编程结束
	if (_return == OK_0)
	{
		//---自编程时间是5ms
		if (AT24Cx->msg_f_delay_ms != NULL)
		{
			AT24Cx->msg_f_delay_ms(5);
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数:
//////功	   能:读取寄存器
//////输入参数:
//////输出参数:
//////说	   明:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_sw_i2c_read_single_byte(AT24CXX_HandleType* AT24Cx, uint16_t addr, uint8_t* buffer)
{
	uint8_t _return = OK_0;
	//---保存设备的地址，用于后面恢复
	uint16_t at24cxxAddr = AT24Cx->msg_i2cx.msg_addr;
	//---检查设备类型
	if (AT24Cx->msg_type > AT24C16)
	{
		//---启动IIC并发送器件地址，写数据
		_return = i2c_task_msw_start(&(AT24Cx->msg_i2cx), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
		//---发送寄存器地址,高地址
		i2c_task_msw_send_byte(&(AT24Cx->msg_i2cx), (uint8_t)(addr >> 8));
		//---读取ACK
		_return = i2c_task_msw_read_ack(&(AT24Cx->msg_i2cx));
		if (_return != OK_0)
		{
			//---发送数据失败
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24Cx->msg_i2cx.msg_addr += (((addr >> 8) << 1) & 0x0F);
		//---启动IIC并发送器件地址，写数据
		_return = i2c_task_msw_start(&(AT24Cx->msg_i2cx), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---发送寄存器地址,低位地址
	i2c_task_msw_send_byte(&(AT24Cx->msg_i2cx), (uint8_t)(addr & 0xFF));
	//---读取ACK
	_return = i2c_task_msw_read_ack(&(AT24Cx->msg_i2cx));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---启动IIC并发送器件地址，读数据
	_return = i2c_task_msw_start(&(AT24Cx->msg_i2cx), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_4;
		goto GoToExit;
	}
	//---读取数据
	*buffer = i2c_task_msw_read_byte(&(AT24Cx->msg_i2cx));
	//---发送不应答信号
	i2c_task_msw_send_ack(&(AT24Cx->msg_i2cx), 1);
	//---退出函数入口
GoToExit:
	//---发送停止信号
	i2c_task_msw_stop(&(AT24Cx->msg_i2cx));
	AT24Cx->msg_i2cx.msg_addr = at24cxxAddr;
	return _return;
}
///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_sw_i2c_read_page_byte(AT24CXX_HandleType* AT24Cx, uint16_t addr, uint8_t* buffer, uint16_t length)
{
	//---判断页号和页内的数据
	if (length > AT24Cx->msg_page_byte)
	{
		length = AT24Cx->msg_page_byte;
	}
	uint8_t _return = OK_0;
	//---保存设备的地址，用于后面恢复
	uint16_t deviceaddr = AT24Cx->msg_i2cx.msg_addr;
	uint16_t i = 0;
	//---检查设备类型
	if (AT24Cx->msg_type > AT24C16)
	{
		//---启动IIC并发送器件地址，写数据
		_return = i2c_task_msw_start(&(AT24Cx->msg_i2cx), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
		//---发送寄存器地址,高地址
		i2c_task_msw_send_byte(&(AT24Cx->msg_i2cx), (uint8_t)(addr >> 8));
		//---读取ACK
		_return = i2c_task_msw_read_ack(&(AT24Cx->msg_i2cx));
		if (_return != OK_0)
		{
			//---发送数据失败
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24Cx->msg_i2cx.msg_addr += (((addr >> 8) << 1) & 0x0F);
		//---启动IIC并发送器件地址，写数据
		_return = i2c_task_msw_start(&(AT24Cx->msg_i2cx), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---发送寄存器地址,低位地址
	i2c_task_msw_send_byte(&(AT24Cx->msg_i2cx), (uint8_t)(addr & 0xFF));
	//---读取ACK
	_return = i2c_task_msw_read_ack(&(AT24Cx->msg_i2cx));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---启动IIC并发送器件地址，读数据
	_return = i2c_task_msw_start(&(AT24Cx->msg_i2cx), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_4;
		goto GoToExit;
	}
	//---循环读取指定长度的数据
	for (i = 0; i < length; i++)
	{
		//---读取数据
		buffer[i] = i2c_task_msw_read_byte(&(AT24Cx->msg_i2cx));
		//---发送应答信号
		i2c_task_msw_send_ack(&(AT24Cx->msg_i2cx), (i == (length - 1)) ? 1 : 0);
	}
	_return = OK_0;
	//---退出函数入口
GoToExit:
	//---发送停止信号
	i2c_task_msw_stop(&(AT24Cx->msg_i2cx));
	AT24Cx->msg_i2cx.msg_addr = deviceaddr;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_sw_i2c_read_byte(AT24CXX_HandleType* AT24Cx, uint16_t addr, uint8_t* buffer, uint16_t length)
{
	uint8_t _return = OK_0;
	//---保存设备的地址，用于后面恢复
	uint16_t deviceaddr = AT24Cx->msg_i2cx.msg_addr;
	uint16_t i = 0;
	uint32_t cnt = 0;
	//---检查设备类型
	if (AT24Cx->msg_type > AT24C16)
	{
		//---启动IIC并发送器件地址，写数据
		_return = i2c_task_msw_start(&(AT24Cx->msg_i2cx), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
		//---发送寄存器地址,高地址
		i2c_task_msw_send_byte(&(AT24Cx->msg_i2cx), (uint8_t)(addr >> 8));
		//---读取ACK
		_return = i2c_task_msw_read_ack(&(AT24Cx->msg_i2cx));
		if (_return != OK_0)
		{
			//---发送数据失败
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24Cx->msg_i2cx.msg_addr += (((addr >> 8) << 1) & 0x0F);
		//---启动IIC并发送器件地址，写数据
		_return = i2c_task_msw_start(&(AT24Cx->msg_i2cx), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---发送寄存器地址,低位地址
	i2c_task_msw_send_byte(&(AT24Cx->msg_i2cx), (uint8_t)(addr & 0xFF));
	//---读取ACK
	_return = i2c_task_msw_read_ack(&(AT24Cx->msg_i2cx));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---启动IIC并发送器件地址，读数据
	_return = i2c_task_msw_start(&(AT24Cx->msg_i2cx), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_4;
		goto GoToExit;
	}
	//---同步时间
	cnt = AT24Cx->msg_i2cx.msg_f_time_tick();
	//---循环读取指定长度的数据
	for (i = 0; i < length; i++)
	{
		//---读取数据
		buffer[i] = i2c_task_msw_read_byte(&(AT24Cx->msg_i2cx));
		//---发送应答信号
		i2c_task_msw_send_ack(&(AT24Cx->msg_i2cx), (i == (length - 1)) ? 1 : 0);
		//---校验时间宽度，避免看门狗复位
		if (TIME_SPAN(AT24Cx->msg_i2cx.msg_f_time_tick(), cnt) > AT24CXX_WAIT_MAX_TIME)
		{
			//---同步时间
			cnt = AT24Cx->msg_i2cx.msg_f_time_tick();
			//---喂狗
			WDT_RESET();
		}
	}
	_return = OK_0;
	//---退出函数的入口
GoToExit:
	//---发送停止信号
	i2c_task_msw_stop(&(AT24Cx->msg_i2cx));
	AT24Cx->msg_i2cx.msg_addr = deviceaddr;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_sw_i2c_send_byte(AT24CXX_HandleType* AT24Cx, uint16_t addr, uint8_t* buffer, uint16_t length)
{
	//---要写的页数
	uint16_t pageNum = 0;
	//---不满页要写入的字节数
	uint16_t byteNum = 0;
	//---页地址，即开始页的总数
	uint16_t pageIndexAddr = addr / (AT24Cx->msg_page_byte);
	//---不满一页的余数
	uint16_t byteIndexAddr = addr % (AT24Cx->msg_page_byte);
	//---不满一页的数据要写入的字节数
	uint16_t pageByteNum = AT24Cx->msg_page_byte - byteIndexAddr;
	//---
	uint16_t i = 0;
	uint8_t _return = OK_0;
	uint32_t cnt = 0;
	//---无数据写入或写入的数据为空
	if ((length == 0) || (buffer == NULL))
	{
		return ERROR_6;
	}
	//---数据长度的大小
	if (length <= pageByteNum)
	{
		pageByteNum = length;
	}
	//---当要写入的数据不大于2字节的时候，按页写入和按字节写入消耗的时间基本相同
	if (length < 3)
	{
		//---按字节写入
		for (i = 0; i < length; i++)
		{
			_return = at24cxx_sw_i2c_send_single_byte(AT24Cx, addr, *buffer);
			addr++;
			buffer++;
			//---判断是不是写入成功
			if (_return != OK_0)
			{
				return ERROR_7;
			}
		}
	}
	else
	{
		//---按页写入
#ifdef AT24CXX_ENABLE_DRAM
		//---申请内存
		AT24Cx->msg_page_byte_buffer = (uint8_t*)my_malloc(AT24Cx->msg_page_byte);
		//---判断缓存空间申请是否成功
		if (AT24Cx->msg_page_byte_buffer == NULL)
		{
			_return = ERROR_8;
			goto GoToExit;
		}
#endif
		//---先第一页写满，写入的字节数不小于3个字节
		if (pageByteNum != AT24Cx->msg_page_byte)
		{
			//---读取一页的数据
#ifdef AT24CXX_ENABLE_DRAM
			_return = at24cxx_sw_i2c_read_page_byte(AT24Cx, (pageIndexAddr * (AT24Cx->msg_page_byte)), AT24Cx->msg_page_byte_buffer, (AT24Cx->msg_page_byte));
#else
			_return = at24cxx_sw_i2c_read_page_byte(AT24Cx, (pageIndexAddr * (AT24Cx->msg_page_byte)), AT24Cx->msg_page_byte_buffer, (AT24Cx->msg_page_byte));
#endif
			//---读取判断
			if (_return != OK_0)
			{
				_return = ERROR_9;
				goto GoToExit;
			}
			//---填充数据
			for (i = 0; i < pageByteNum; i++)
			{
				//---填充数据到缓存区
#ifdef AT24CXX_ENABLE_DRAM
				AT24Cx->msg_page_byte_buffer[i + byteIndexAddr] = *buffer;
#else
				AT24Cx->msg_page_byte_buffer[i + byteIndexAddr] = *buffer;
#endif
				//---地址偏移，使地址偏移到页的首地址
				addr++;
				//---数据偏移
				buffer++;
				//---数据长度偏移
				length--;
				//---数据填充完成
				if (length == 0)
				{
					//---退出数据的填充
					break;
				}
			}
			//---清零当前页中的字节偏移地址
			byteIndexAddr = 0;
			//---按页写入数据
#ifdef AT24CXX_ENABLE_DRAM
			_return = at24cxx_sw_i2c_send_page_byte(AT24Cx, (pageIndexAddr * (AT24Cx->msg_page_byte)), AT24Cx->msg_page_byte_buffer, AT24Cx->msg_page_byte);
#else
			_return = at24cxx_sw_i2c_send_page_byte(AT24Cx, (pageIndexAddr * (AT24Cx->msg_page_byte)), AT24Cx->msg_page_byte_buffer, AT24Cx->msg_page_byte);
#endif
			//---写入判断
			if (_return != OK_0)
			{
				_return = ERROR_10;
				goto GoToExit;
			}
		}
		//---写整页操作
		//---计算要写入的页数
		pageNum = length / AT24Cx->msg_page_byte;
		//---计算最后一页要写入的字节数
		byteNum = length % AT24Cx->msg_page_byte;
		//---判断是否需要页写入
		if (pageNum != 0)
		{
			cnt = AT24Cx->msg_i2cx.msg_f_time_tick();
			//---循环进行页写入操作
			for (i = 0; i < pageNum; i++)
			{
				_return = at24cxx_sw_i2c_send_page_byte(AT24Cx, addr, buffer, AT24Cx->msg_page_byte);
				//---地址偏移，偏移到下次要写入的数据的页的首地址
				addr += AT24Cx->msg_page_byte;
				//---数据偏移
				buffer += AT24Cx->msg_page_byte;
				//---数据长度偏移
				length -= AT24Cx->msg_page_byte;
				//---判断是不是写入成功
				if (_return != OK_0)
				{
					_return = ERROR_11;
					goto GoToExit;
				}
				//---检查使用时间
				if (TIME_SPAN(AT24Cx->msg_i2cx.msg_f_time_tick(), cnt) > AT24CXX_WAIT_MAX_TIME)
				{
					//---同步时间
					cnt = AT24Cx->msg_i2cx.msg_f_time_tick();
					//---喂狗
					WDT_RESET();
				}
			}
		}
		//---判断是不是不满页的操作
		if (byteNum != 0)
		{
			//---读取一页的数据
#ifdef AT24CXX_ENABLE_DRAM
			_return = at24cxx_sw_i2c_read_page_byte(AT24Cx, addr, AT24Cx->msg_page_byte_buffer, (AT24Cx->msg_page_byte));
#else
			_return = at24cxx_sw_i2c_read_page_byte(AT24Cx, addr, AT24Cx->msg_page_byte_buffer, (AT24Cx->msg_page_byte));
#endif
			//---读取判断
			if (_return != OK_0)
			{
				_return = ERROR_12;
				goto GoToExit;
			}
			//---填充数据
			for (i = 0; i < pageByteNum; i++)
			{
				//---填充数据到缓存区
#ifdef AT24CXX_ENABLE_DRAM
				AT24Cx->msg_page_byte_buffer[i + byteIndexAddr] = *buffer;
#else
				AT24Cx->msg_page_byte_buffer[i + byteIndexAddr] = *buffer;
#endif
				//---地址偏移，此时已经是页的首地址了，不能值继续偏移了
				//addr++;
				//---数据偏移
				buffer++;
				//---数据长度偏移
				length--;
				//---数据填充完成
				if (length == 0)
				{
					//---退出数据的填充
					break;
				}
			}
			//---按页写入数据
#ifdef AT24CXX_ENABLE_DRAM
			_return = at24cxx_sw_i2c_send_page_byte(AT24Cx, addr, AT24Cx->msg_page_byte_buffer, AT24Cx->msg_page_byte);
#else
			_return = at24cxx_sw_i2c_send_page_byte(AT24Cx, addr, AT24Cx->msg_page_byte_buffer, AT24Cx->msg_page_byte);
#endif
			//---写入判断
			if (_return != OK_0)
			{
				_return = ERROR_13;
				goto GoToExit;
			}
		}
#ifdef AT24CXX_ENABLE_DRAM
	//---退出函数入口
	GoToExit :
		 //---校验缓存区
		 if (AT24Cx->msg_page_byte_buffer != NULL)
		 {
			 //---释放内存
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
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_i2c_send_single_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t buffer)
{
	return at24cxx_sw_i2c_send_single_byte(AT24Cx, addr, buffer);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_i2c_send_page_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer, uint16_t length)
{
	return at24cxx_sw_i2c_send_page_byte(AT24Cx, addr, buffer,length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_i2c_send_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer, uint16_t length)
{
	return at24cxx_sw_i2c_send_byte(AT24Cx, addr, buffer,length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_i2c_read_single_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer)
{
	return at24cxx_sw_i2c_read_single_byte(AT24Cx, addr, buffer);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_i2c_read_page_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer, uint16_t length)
{
	return at24cxx_sw_i2c_read_page_byte(AT24Cx, addr, buffer,length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t at24cxx_i2c_read_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer, uint16_t length)
{
	return at24cxx_sw_i2c_read_byte(AT24Cx, addr, buffer,length);
}
