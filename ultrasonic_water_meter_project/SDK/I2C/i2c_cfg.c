#include "i2c_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_init(I2C_HandleType *I2Cx, void(*func_delay_us)(uint32_t delay), uint32_t(*func_time_tick)(void))
{
	//---SCL初始化
	gpio_task_pin_mode_output(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	gpio_task_pin_set(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	//---SDA初始化
	gpio_task_pin_mode_input(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	gpio_task_pin_set(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	
	//---us延时函数
	(func_delay_us != NULL) ?
		(I2Cx->msg_f_delay_us = func_delay_us) :
		(I2Cx->msg_f_delay_us = delay_task_us);
	//---注册滴答函数
	(func_time_tick != NULL) ?
		(I2Cx->msg_f_time_tick = func_time_tick) :
		(I2Cx->msg_f_time_tick = sys_tick_task_get_tick);
	//---软件模式
	I2Cx->msg_hw_mode = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_deinit(I2C_HandleType *I2Cx)
{
	//---SCL初始化
	gpio_task_pin_mode_input(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	gpio_task_pin_set(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	//---SDA初始化
	gpio_task_pin_mode_input(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	gpio_task_pin_set(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_start(I2C_HandleType *I2Cx)
{
#ifndef I2C_GPIO_SDA_MODE_OD
	//---SDA设置为输出
	gpio_task_pin_mode_output(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
#endif
	//---发送起始条件的数据信号
	PIN_OUT_1(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	PIN_OUT_1(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	//I2Cx->msg_f_delay_us(I2Cx->msg_pluse_width);
	//---发送起始信号;
	PIN_OUT_0(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	//I2Cx->msg_f_delay_us(I2Cx->msg_pluse_width);
	//---钳住I2C总线，准备发送或接收数据
	PIN_OUT_0(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
#ifndef I2C_GPIO_SDA_MODE_OD
	//---SDA设置为输入
	gpio_task_pin_mode_input(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
#endif
	//---判断I2C启动信号是否成功，读取SDA的状态信号，成功SDA---0；失败SDA---1
	return  ((PIN_GET_STATE(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit) != 0x00) ? ERROR_1 : OK_0);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_stop(I2C_HandleType *I2Cx)
{
#ifndef I2C_GPIO_SDA_MODE_OD
	//---SDA设置为输出
	gpio_task_pin_mode_output(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
#endif
	//---发送停止条件的数据信号
	PIN_OUT_0(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	PIN_OUT_1(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	//I2Cx->msg_f_delay_us(I2Cx->msg_pluse_width);
	PIN_OUT_1(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	//I2Cx->msg_f_delay_us(I2Cx->msg_pluse_width);
#ifndef I2C_GPIO_SDA_MODE_OD
	//---SDA设置为输入
	gpio_task_pin_mode_input(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
#endif
	//---判断I2C启动信号是否成功，读取SDA的状态信号，成功SDA---1；失败SDA---0
	return ((PIN_GET_STATE(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit) == 0x00) ? ERROR_1 : OK_0);
}
///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 发送ACK信号
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_ack(I2C_HandleType *I2Cx)
{
#ifndef I2C_GPIO_SDA_MODE_OD
	//---SDA设置为输出
	gpio_task_pin_mode_output(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
#endif
	PIN_OUT_0(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	PIN_OUT_1(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	//---清时钟线,钳住I2C总线，准备发送或接收数据
	PIN_OUT_0(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 发送NACK信号
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_nack(I2C_HandleType *I2Cx)
{
#ifndef I2C_GPIO_SDA_MODE_OD
	//---SDA设置为输出
	gpio_task_pin_mode_output(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
#endif
	PIN_OUT_1(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	PIN_OUT_1(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	//---清时钟线,钳住I2C总线，准备发送或接收数据
	PIN_OUT_0(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 读取应答信号
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_read_ack(I2C_HandleType *I2Cx)
{
	uint8_t _return = OK_0;
#ifndef I2C_GPIO_SDA_MODE_OD
	//---SDA设置为输出
	gpio_task_pin_mode_output(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
#endif
	//---读取应答信号
	PIN_OUT_1(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	PIN_OUT_1(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
#ifndef I2C_GPIO_SDA_MODE_OD
	//---SDA设置为输入
	gpio_task_pin_mode_input(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
#endif
	//---读取SDA的状态信号---ACK状态下SDA为低电平
	_return = ((PIN_GET_STATE(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit) != 0x00) ? ERROR_1 : OK_0);
	//---清时钟线,钳住I2C总线，准备发送或接收数据
	PIN_OUT_0(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_wait_ack(I2C_HandleType *I2Cx)
{
	uint8_t _return = OK_0;
#ifndef I2C_GPIO_SDA_MODE_OD
	//---SDA设置为输出
	gpio_task_pin_mode_output(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
#endif
	//---读取应答信号
	PIN_OUT_1(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	PIN_OUT_1(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
#ifndef I2C_GPIO_SDA_MODE_OD
	//---SDA设置为输入
	gpio_task_pin_mode_input(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
#endif
	//---检查SDA电平,SDA为高,代表从机发送ACK
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
//////函		数:
//////功		能:
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_send_ack(I2C_HandleType *I2Cx, uint8_t is_nack)
{
	return ((is_nack != 0) ? (i2c_msw_nack(I2Cx)) : (i2c_msw_ack(I2Cx)));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 发送1bit数据
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_send_bit(I2C_HandleType *I2Cx, uint8_t bitbuffer)
{
	((bitbuffer & 0x80) != 0x00) ?
		PIN_OUT_1(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit) :
		PIN_OUT_0(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	//---一个时钟脉冲
	PIN_OUT_1(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	PIN_OUT_0(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 发送字节数据
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_send_byte(I2C_HandleType *I2Cx, uint8_t buffer)
{
	uint8_t i = 0;
	//---清时钟线,钳住I2C总线，准备发送或接收数据
	PIN_OUT_0(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
#ifndef I2C_GPIO_SDA_MODE_OD
	//---SDA设置为输出
	gpio_task_pin_mode_output(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
#endif
	//---发送1字节的数据
	for (i = 0; i < 8; i++)
	{
		//---读取1Bit的数据
		i2c_msw_send_bit(I2Cx, buffer);
		buffer <<= 1;
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
uint8_t i2c_msw_send_word(I2C_HandleType *I2Cx, uint16_t buffer)
{
	uint8_t bufferH = (uint8_t)(buffer >> 8);
	uint8_t bufferL = (uint8_t)(buffer);
	uint8_t i = 0;
	//---清时钟线,钳住I2C总线，准备发送或接收数据
	PIN_OUT_0(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
#ifndef I2C_GPIO_SDA_MODE_OD
	//---SDA设置为输出
	gpio_task_pin_mode_output(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
#endif
	//---发送1字节的数据
	for (i = 0; i < 8; i++)
	{
		//---读取1Bit的数据
		i2c_msw_send_bit(I2Cx, bufferH);
		//---数据左移动
		bufferH <<= 1;
	}
	//---发送1字节的数据
	for (i = 0; i < 8; i++)
	{
		//---读取1Bit的数据
		i2c_msw_send_bit(I2Cx, bufferL);
		//---数据右移
		bufferL <<= 1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 读取1bit数据
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_read_bit(I2C_HandleType *I2Cx)
{
	uint8_t _return = OK_0;
	//---时钟正脉冲
	PIN_OUT_1(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	//---读取数据位
	_return = ((PIN_GET_STATE(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit) != 0x00) ? 1 : 0);
	//---时钟负脉冲
	PIN_OUT_0(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
	return  _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t i2c_msw_read_byte(I2C_HandleType *I2Cx)
{
	uint8_t i = 0;
	uint8_t _return = 0;
	//---准备数据的读取
	PIN_OUT_1(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	//---清时钟线,钳住I2C总线，准备发送或接收数据
	PIN_OUT_0(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
#ifndef I2C_GPIO_SDA_MODE_OD
	//---SDA设置为输入
	gpio_task_pin_mode_input(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
#endif
	//---发送1字节的数据
	for (i = 0; i < 8; i++)
	{
		_return <<= 1;
		_return |= i2c_msw_read_bit(I2Cx);
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
uint8_t i2c_msw_check_device(I2C_HandleType *I2Cx)
{
	uint8_t _return = OK_0;
#ifndef I2C_GPIO_SDA_MODE_OD
	//---SDA设置为输入
	gpio_task_pin_mode_input(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
	//---SCL设置为输入
	gpio_task_pin_mode_input(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
#endif
	//---检查端口的状态
	if ((PIN_GET_STATE(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit)) &&
		(PIN_GET_STATE(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit)))
	{
#ifndef I2C_GPIO_SDA_MODE_OD
		//---SDA设置为输入
		gpio_task_pin_mode_output(I2Cx->msg_gpio_sda.msg_p_port, I2Cx->msg_gpio_sda.msg_bit);
		//---SCL设置为输入
		gpio_task_pin_mode_output(I2Cx->msg_gpio_scl.msg_p_port, I2Cx->msg_gpio_scl.msg_bit);
#endif
		//---发送启动信号
		i2c_msw_start(I2Cx);
		//---发送读取操作命令
		I2Cx->msg_addr |= 0x01;
		//---发送从机地址
		i2c_msw_send_byte(I2Cx, (uint8_t)I2Cx->msg_addr);
		//---读取应答信号
		_return = i2c_msw_read_ack(I2Cx);
	}
	else
	{
		_return = ERROR_2;
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
uint8_t i2c_msw_send_cmd(I2C_HandleType *I2Cx, uint8_t cmd, uint8_t is_start, uint8_t is_stop)
{
	uint8_t _return = OK_0;
	if (is_start)
	{
		//---发送启动启动信号
		_return = i2c_msw_start(I2Cx);
		if (_return)
		{
			i2c_msw_stop(I2Cx);
			return ERROR_1;
		}
	}
	//---发送数据
	_return = i2c_msw_send_byte(I2Cx, cmd);
	//---读取应答
	_return = i2c_msw_read_ack(I2Cx);
	//---停止条件的满足
	if ((is_stop) || (_return))
	{
		i2c_msw_stop(I2Cx);
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
uint8_t i2c_master_deinit(I2C_HandleType* I2Cx)
{
	//---注销I2C设备
	return i2c_msw_deinit(I2Cx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void i2c_time_tick_init(I2C_HandleType* I2Cx, uint32_t(*func_time_tick)(void))
{
	//---注册滴答函数
	(func_time_tick != NULL) ?
		(I2Cx->msg_f_time_tick = func_time_tick) :
		(I2Cx->msg_f_time_tick = sys_tick_task_get_tick);
}