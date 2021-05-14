#include "spi_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_time_tick_init(SPI_HandleType* SPIx, uint32_t(*func_time_tick)(void))
{
	//---注册滴答函数
	(func_time_tick != NULL) ?
		(SPIx->msg_f_time_tick = func_time_tick) :
		(SPIx->msg_f_time_tick = sys_tick_task_get_tick);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_init(SPI_HandleType* SPIx, void(*func_delay_us)(uint32_t delay), uint32_t(*func_time_tick)(void))
{
	//---us延时函数
	(func_delay_us != NULL) ?
		(SPIx->msg_f_delay_us = func_delay_us) :
		(SPIx->msg_f_delay_us = delay_task_us);
	//---注册滴答函数
	(func_time_tick != NULL) ?
		(SPIx->msg_f_time_tick = func_time_tick) :
		(SPIx->msg_f_time_tick = sys_tick_task_get_tick);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_mhw_gpio_init(SPI_HandleType* SPIx)
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
uint8_t spi_msw_gpio_init(SPI_HandleType* SPIx)
{
	if (SPIx->msg_gpio_cs.msg_p_port != NULL)
	{
		//---SS---设置为输出
		gpio_task_pin_mode_output(SPIx->msg_gpio_cs.msg_p_port, SPIx->msg_gpio_cs.msg_bit);
		//---上拉使能
		gpio_task_pin_mode_pull_up_set(SPIx->msg_gpio_cs.msg_p_port, SPIx->msg_gpio_cs.msg_bit);
		PIN_OUT_1(SPIx->msg_gpio_cs.msg_p_port, SPIx->msg_gpio_cs.msg_bit);
	}
	//---SCK---设置为输出
	gpio_task_pin_mode_output(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	//---上拉使能
	gpio_task_pin_mode_pull_up_set(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	//---MOSI---设置为输出
	gpio_task_pin_mode_output(SPIx->msg_gpio_mosi.msg_p_port, SPIx->msg_gpio_mosi.msg_bit);
	//---上拉使能
	gpio_task_pin_mode_pull_up_set(SPIx->msg_gpio_mosi.msg_p_port, SPIx->msg_gpio_mosi.msg_bit);
	PIN_OUT_1(SPIx->msg_gpio_mosi.msg_p_port, SPIx->msg_gpio_mosi.msg_bit);
	//---MISO---设置为输入
	gpio_task_pin_mode_input(SPIx->msg_gpio_mosi.msg_p_port, SPIx->msg_gpio_mosi.msg_bit);
	//---上拉使能
	gpio_task_pin_mode_pull_up_set(SPIx->msg_gpio_mosi.msg_p_port, SPIx->msg_gpio_mosi.msg_bit);
	PIN_OUT_1(SPIx->msg_gpio_miso.msg_p_port, SPIx->msg_gpio_miso.msg_bit);
	//---软件模拟模式
	SPIx->msg_hw_mode = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_gpio_deinit(SPI_HandleType* SPIx, uint8_t is_init_ss)
{
	if ((is_init_ss != 0) && (SPIx->msg_gpio_cs.msg_p_port != NULL))
	{
		//---SS---设置为输入
		gpio_task_pin_mode_input(SPIx->msg_gpio_cs.msg_p_port, SPIx->msg_gpio_cs.msg_bit);
		PIN_OUT_1(SPIx->msg_gpio_cs.msg_p_port, SPIx->msg_gpio_cs.msg_bit);
	}
	//---SCK---设置为输入
	gpio_task_pin_mode_input(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	//---MOSI---设置为输入
	gpio_task_pin_mode_input(SPIx->msg_gpio_mosi.msg_p_port, SPIx->msg_gpio_mosi.msg_bit);
	PIN_OUT_1(SPIx->msg_gpio_mosi.msg_p_port, SPIx->msg_gpio_mosi.msg_bit);
	//---MISO---设置为输入
	gpio_task_pin_mode_input(SPIx->msg_gpio_miso.msg_p_port, SPIx->msg_gpio_miso.msg_bit);
	PIN_OUT_1(SPIx->msg_gpio_miso.msg_p_port, SPIx->msg_gpio_miso.msg_bit);
	return OK_0;
}

#pragma region MSB

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 高位在前发送字节的最高位
//////输入参数:
//////输出参数:
//////说		明: 高位在前
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_send_bit_msb_byte(SPI_HandleType* SPIx, uint8_t val)
{
	//---发送1bit的数据
	((val & 0x80) != 0x00) ?
		PIN_OUT_1(SPIx->msg_gpio_mosi.msg_p_port, SPIx->msg_gpio_mosi.msg_bit) :
		PIN_OUT_0(SPIx->msg_gpio_mosi.msg_p_port, SPIx->msg_gpio_mosi.msg_bit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数: 
//////功		能: 
//////输入参数: 
//////输出参数: 
//////说		明: 高位在前
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_read_bit_msb_byte(SPI_HandleType* SPIx, uint8_t* pval)
{
	//---读取1bit的数据
	(*pval) |=((PIN_GET_STATE(SPIx->msg_gpio_miso.msg_p_port, SPIx->msg_gpio_miso.msg_bit) != 0) ? 1 : 0);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:  高位在前发送字的最高位
//////输入参	数:
//////输出参	数:
//////说		明: 高位在前
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_send_bit_msb_word(SPI_HandleType* SPIx, uint16_t val)
{
	//---发送1bit的数据
	((val & 0x8000) != 0x0000) ?
		PIN_OUT_1(SPIx->msg_gpio_mosi.msg_p_port, SPIx->msg_gpio_mosi.msg_bit) :
		PIN_OUT_0(SPIx->msg_gpio_mosi.msg_p_port, SPIx->msg_gpio_mosi.msg_bit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数: 
//////功		能: 
//////输入参数: 
//////输出参数: 
//////说		明: 高位在前
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_read_bit_msb_word(SPI_HandleType* SPIx, uint16_t* pval)
{
	//---读取1bit的数据
	(*pval) |=((PIN_GET_STATE(SPIx->msg_gpio_miso.msg_p_port, SPIx->msg_gpio_miso.msg_bit) != 0) ? 1 : 0);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_bit_msb_byte(SPI_HandleType* SPIx, uint8_t val, uint8_t *pcmd)
{
	spi_msw_send_bit_msb_byte(SPIx, val);
	//---校验是否需要读取数据
	if (pcmd!=NULL)
	{
		spi_msw_read_bit_msb_byte(SPIx, pcmd);
	}
	
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_bit_msb_byte_clock_pulse(SPI_HandleType* SPIx, uint8_t val, uint8_t *pcmd)
{
	//---00---11
	if (((SPIx->msg_cpol == 0) && (SPIx->msg_cpha == 0)) || ((SPIx->msg_cpol == 1) && (SPIx->msg_cpha == 1)))
	{
		PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
		spi_msw_bit_msb_byte(SPIx, val,pcmd);
		PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	}
	//---10---01
	else
	{
		PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
		spi_msw_bit_msb_byte(SPIx,val, pcmd);
		PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_bit_msb_word(SPI_HandleType* SPIx, uint16_t val, uint16_t *pcmd)
{
	spi_msw_send_bit_msb_word(SPIx, val);
	//---校验是否需要读取数据
	if (pcmd!=NULL)
	{
		spi_msw_read_bit_msb_word(SPIx, pcmd);
	}	
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_bit_msb_word_clock_pulse(SPI_HandleType* SPIx, uint16_t val, uint16_t *pcmd)
{
	//---00---11
	if (((SPIx->msg_cpol == 0) && (SPIx->msg_cpha == 0)) || ((SPIx->msg_cpol == 1) && (SPIx->msg_cpha == 1)))
	{
		PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
		spi_msw_bit_msb_word(SPIx, val,pcmd);
		PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	}
	//---10---01
	else
	{
		PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
		spi_msw_bit_msb_word(SPIx,val, pcmd);
		PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_send_msb_byte(SPI_HandleType* SPIx, uint8_t val,uint8_t polarity)
{
	uint8_t index = 0;
	//---工作状态为忙碌
	SPIx->msg_state = BUSY;
	//---发送8bit 
	for (index=0;index<8;index++)
	{
		spi_msw_bit_msb_word(SPIx,val, NULL);
		val <<= 1;
	}
	//---时钟线的极性
	if (polarity!=0)
	{
		(SPIx->msg_cpol == 0) ?
			PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit) :
			PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	}	
	//---工作状态为空闲
	SPIx->msg_state = IDLE;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_read_msb_byte(SPI_HandleType* SPIx, uint8_t* pval, uint8_t polarity)
{
	uint8_t index = 0;
	//---工作状态为忙碌
	SPIx->msg_state = BUSY;
	//---发送8bit 
	for (index = 0; index < 8; index++)
	{
		(*pval) <<= 1;
		spi_msw_bit_msb_byte(SPIx,1, pval);
	}
	//---时钟线的极性
	if (polarity != 0)
	{
		(SPIx->msg_cpol == 0) ?
			PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit) :
			PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	}
	//---工作状态为空闲
	SPIx->msg_state = IDLE;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_msb_byte_cmd(SPI_HandleType* SPIx, uint8_t val, uint8_t *pcmd)
{
	uint8_t index = 0;
	//---发送8bit 
	for (index = 0; index < 8; index++)
	{
		(*pcmd) <<= 1;
		spi_msw_bit_msb_byte(SPIx, val, pcmd);
		val <<= 1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_msb_byte(SPI_HandleType* SPIx, uint8_t val,uint8_t *pcmd)
{
	//---工作状态为忙碌
	SPIx->msg_state = BUSY;
	spi_msw_msb_byte_cmd(SPIx, val, pcmd);
	//---时钟线的极性
	(SPIx->msg_cpol == 0) ?
		PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit) :
		PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	//---工作状态为空闲
	SPIx->msg_state = IDLE;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_send_msb_byte_buffer(SPI_HandleType* SPIx, uint8_t *pval,uint16_t length)
{
	uint16_t index = 0;
	//---工作状态为忙碌
	SPIx->msg_state = BUSY;
	//---发送8bit 
	for (index = 0; index < length; index++)
	{
		spi_msw_send_msb_byte(SPIx,*pval,0);
		pval++;
	}
	//---时钟线的极性
	(SPIx->msg_cpol == 0) ?
		PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit) :
		PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	//---工作状态为空闲
	SPIx->msg_state = IDLE;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_read_msb_byte_buffer(SPI_HandleType* SPIx, uint8_t* pval,uint16_t length)
{
	uint16_t index = 0;
	//---工作状态为忙碌
	SPIx->msg_state = BUSY;
	//---发送8bit 
	for (index = 0; index < length; index++)
	{
		spi_msw_read_msb_byte(SPIx,pval,0);
		pval++;
	}
	//---时钟线的极性
	(SPIx->msg_cpol == 0) ?
		PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit) :
		PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	//---工作状态为空闲
	SPIx->msg_state = IDLE;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_msb_byte_buffer(SPI_HandleType* SPIx, uint8_t *pval, uint8_t *pcmd,uint16_t length)
{
	uint16_t index = 0;
	//---工作状态为忙碌
	SPIx->msg_state = BUSY;
	//---发送8bit 
	for (index = 0; index < length; index++)
	{
		spi_msw_msb_byte_cmd(SPIx, *pval, pcmd);
		pval++;
		pcmd++;
	}
	//---时钟线的极性
	(SPIx->msg_cpol == 0) ?
		PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit) :
		PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	//---工作状态为空闲
	SPIx->msg_state = IDLE;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_send_msb_word(SPI_HandleType* SPIx, uint16_t val, uint8_t polarity)
{
	uint8_t index = 0;
	//---工作状态为忙碌
	SPIx->msg_state = BUSY;
	//---发送8bit 
	for (index = 0; index < 16; index++)
	{
		spi_msw_bit_msb_word(SPIx,val, NULL);
		val <<= 1;
	}
	//---校验时钟极性
	if (polarity!=0)
	{
		//---时钟线的极性
		(SPIx->msg_cpol == 0) ?
			PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit) :
			PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	}
	//---工作状态为空闲
	SPIx->msg_state = IDLE;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_read_msb_word(SPI_HandleType* SPIx, uint16_t* pval, uint8_t polarity)
{
	uint8_t index = 0;
	//---工作状态为忙碌
	SPIx->msg_state = BUSY;
	//---发送8bit 
	for (index = 0; index < 16; index++)
	{
		(*pval) <<= 1;
		spi_msw_bit_msb_word(SPIx, 1, pval);
	}
	//---校验时钟极性
	if (polarity != 0)
	{
		//---时钟线的极性
		(SPIx->msg_cpol == 0) ?
			PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit) :
			PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	}
	//---工作状态为空闲
	SPIx->msg_state = IDLE;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_send_msb_word_buffer(SPI_HandleType* SPIx, uint16_t *pval, uint16_t length)
{
	uint16_t index = 0;
	//---工作状态为忙碌
	SPIx->msg_state = BUSY;
	//---发送8bit 
	for (index = 0; index < length; index++)
	{
		spi_msw_send_msb_word_buffer(SPIx, *pval, 0);
		pval++;
	}
	//---时钟线的极性
	(SPIx->msg_cpol == 0) ?
		PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit) :
		PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	//---工作状态为空闲
	SPIx->msg_state = IDLE;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_read_msb_word_buffer(SPI_HandleType* SPIx, uint16_t *pval, uint16_t length)
{
	uint16_t index = 0;
	//---工作状态为忙碌
	SPIx->msg_state = BUSY;
	//---发送8bit 
	for (index = 0; index < length; index++)
	{
		spi_msw_read_msb_word_buffer(SPIx, *pval, 0);
		pval++;
	}
	//---时钟线的极性
	(SPIx->msg_cpol == 0) ?
		PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit) :
		PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	//---工作状态为空闲
	SPIx->msg_state = IDLE;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_msb_word_cmd(SPI_HandleType* SPIx, uint16_t val, uint16_t *pcmd)
{
	uint8_t index = 0;
	//---发送8bit 
	for (index = 0; index < 16; index++)
	{
		(*pcmd) <<= 1;
		spi_msw_bit_msb_word(SPIx, val, pcmd);
		val <<= 1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_msb_word(SPI_HandleType* SPIx, uint16_t val, uint16_t *pcmd)
{
	//---工作状态为忙碌
	SPIx->msg_state = BUSY;
	//---发送子数据
	spi_msw_msb_word_cmd(SPIx, val, pcmd);
	//---时钟线的极性
	(SPIx->msg_cpol == 0) ?
		PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit) :
		PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	//---工作状态为空闲
	SPIx->msg_state = IDLE;
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_msb_word_buffer(SPI_HandleType* SPIx, uint16_t *pval, uint16_t *pcmd,uint16_t length)
{
	uint16_t index = 0;
	//---工作状态为忙碌
	SPIx->msg_state = BUSY;
	//---发送字数据
	for (index=0;index<length;index++)
	{
		spi_msw_msb_word_cmd(SPIx, *pval, pcmd);
		pval++;
		pcmd++;
	}
	//---时钟线的极性
	(SPIx->msg_cpol == 0) ?
		PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit) :
		PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	//---工作状态为空闲
	SPIx->msg_state = IDLE;
	return OK_0;
}

#pragma endregion MSB

#pragma region LSB

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 高位在前发送字节的最高位
//////输入参数:
//////输出参数:
//////说		明: 高位在前
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_send_bit_lsb_byte(SPI_HandleType* SPIx, uint8_t val)
{
	//---发送1bit的数据
	((val & 0x01) != 0x00) ?
		PIN_OUT_1(SPIx->msg_gpio_mosi.msg_p_port, SPIx->msg_gpio_mosi.msg_bit) :
		PIN_OUT_0(SPIx->msg_gpio_mosi.msg_p_port, SPIx->msg_gpio_mosi.msg_bit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数: 
//////功		能: 
//////输入参数: 
//////输出参数: 
//////说		明: 高位在前
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_read_bit_lsb_byte(SPI_HandleType* SPIx, uint8_t* pval)
{
	//---读取1bit的数据
	(*pval) |=((PIN_GET_STATE(SPIx->msg_gpio_miso.msg_p_port, SPIx->msg_gpio_miso.msg_bit) != 0) ? 0x80 : 0);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:  高位在前发送字的最高位
//////输入参	数:
//////输出参	数:
//////说		明: 高位在前
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_send_bit_lsb_word(SPI_HandleType* SPIx, uint16_t val)
{
	//---发送1bit的数据
	((val & 0x0001) != 0x0000) ?
		PIN_OUT_1(SPIx->msg_gpio_mosi.msg_p_port, SPIx->msg_gpio_mosi.msg_bit) :
		PIN_OUT_0(SPIx->msg_gpio_mosi.msg_p_port, SPIx->msg_gpio_mosi.msg_bit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数: 
//////功		能: 
//////输入参数: 
//////输出参数: 
//////说		明: 高位在前
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_read_bit_lsb_word(SPI_HandleType* SPIx, uint16_t* pval)
{
	//---读取1bit的数据
	(*pval) |=((PIN_GET_STATE(SPIx->msg_gpio_miso.msg_p_port, SPIx->msg_gpio_miso.msg_bit) != 0) ? 0x8000 : 0);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_bit_lsb_byte(SPI_HandleType* SPIx, uint8_t val, uint8_t *pcmd)
{
	spi_msw_send_bit_lsb_byte(SPIx, val);
	//---校验是否需要读取数据
	if (pcmd!=NULL)
	{
		spi_msw_read_bit_lsb_byte(SPIx, pcmd);
	}
	
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_bit_lsb_byte_clock_pulse(SPI_HandleType* SPIx, uint8_t val, uint8_t *pcmd)
{
	//---00---11
	if (((SPIx->msg_cpol == 0) && (SPIx->msg_cpha == 0)) || ((SPIx->msg_cpol == 1) && (SPIx->msg_cpha == 1)))
	{
		PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
		spi_msw_bit_lsb_byte(SPIx, val,pcmd);
		PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	}
	//---10---01
	else
	{
		PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
		spi_msw_bit_lsb_byte(SPIx,val, pcmd);
		PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_bit_lsb_word(SPI_HandleType* SPIx, uint16_t val, uint16_t *pcmd)
{
	spi_msw_send_bit_lsb_word(SPIx, val);
	//---校验是否需要读取数据
	if (pcmd!=NULL)
	{
		spi_msw_read_bit_lsb_word(SPIx, pcmd);
	}	
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_bit_lsb_word_clock_pulse(SPI_HandleType* SPIx, uint16_t val, uint16_t *pcmd)
{
	//---00---11
	if (((SPIx->msg_cpol == 0) && (SPIx->msg_cpha == 0)) || ((SPIx->msg_cpol == 1) && (SPIx->msg_cpha == 1)))
	{
		PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
		spi_msw_bit_lsb_word(SPIx, val,pcmd);
		PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	}
	//---10---01
	else
	{
		PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
		spi_msw_bit_lsb_word(SPIx,val, pcmd);
		PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_send_lsb_byte(SPI_HandleType* SPIx, uint8_t val,uint8_t polarity)
{
	uint8_t index = 0;
	//---工作状态为忙碌
	SPIx->msg_state = BUSY;
	//---发送8bit 
	for (index=0;index<8;index++)
	{
		spi_msw_bit_lsb_word(SPIx,val, NULL);
		val >>= 1;
	}
	//---时钟线的极性
	if (polarity!=0)
	{
		(SPIx->msg_cpol == 0) ?
			PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit) :
			PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	}	
	//---工作状态为空闲
	SPIx->msg_state = IDLE;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_read_lsb_byte(SPI_HandleType* SPIx, uint8_t* pval, uint8_t polarity)
{
	uint8_t index = 0;
	//---工作状态为忙碌
	SPIx->msg_state = BUSY;
	//---发送8bit 
	for (index = 0; index < 8; index++)
	{
		(*pval) >>= 1;
		spi_msw_bit_lsb_byte(SPIx,1, pval);
	}
	//---时钟线的极性
	if (polarity != 0)
	{
		(SPIx->msg_cpol == 0) ?
			PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit) :
			PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	}
	//---工作状态为空闲
	SPIx->msg_state = IDLE;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_lsb_byte_cmd(SPI_HandleType* SPIx, uint8_t val, uint8_t *pcmd)
{
	uint8_t index = 0;
	//---发送8bit 
	for (index = 0; index < 8; index++)
	{
		(*pcmd) >>= 1;
		spi_msw_bit_lsb_byte(SPIx, val, pcmd);
		val >>= 1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_lsb_byte(SPI_HandleType* SPIx, uint8_t val,uint8_t *pcmd)
{
	//---工作状态为忙碌
	SPIx->msg_state = BUSY;
	spi_msw_lsb_byte_cmd(SPIx, val, pcmd);
	//---时钟线的极性
	(SPIx->msg_cpol == 0) ?
		PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit) :
		PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	//---工作状态为空闲
	SPIx->msg_state = IDLE;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_send_lsb_byte_buffer(SPI_HandleType* SPIx, uint8_t *pval,uint16_t length)
{
	uint16_t index = 0;
	//---工作状态为忙碌
	SPIx->msg_state = BUSY;
	//---发送8bit 
	for (index = 0; index < length; index++)
	{
		spi_msw_send_lsb_byte(SPIx,*pval,0);
		pval++;
	}
	//---时钟线的极性
	(SPIx->msg_cpol == 0) ?
		PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit) :
		PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	//---工作状态为空闲
	SPIx->msg_state = IDLE;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_read_lsb_byte_buffer(SPI_HandleType* SPIx, uint8_t* pval,uint16_t length)
{
	uint16_t index = 0;
	//---工作状态为忙碌
	SPIx->msg_state = BUSY;
	//---发送8bit 
	for (index = 0; index < length; index++)
	{
		spi_msw_read_lsb_byte(SPIx,pval,0);
		pval++;
	}
	//---时钟线的极性
	(SPIx->msg_cpol == 0) ?
		PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit) :
		PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	//---工作状态为空闲
	SPIx->msg_state = IDLE;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_lsb_byte_buffer(SPI_HandleType* SPIx, uint8_t *pval, uint8_t *pcmd,uint16_t length)
{
	uint16_t index = 0;
	//---工作状态为忙碌
	SPIx->msg_state = BUSY;
	//---发送8bit 
	for (index = 0; index < length; index++)
	{
		spi_msw_lsb_byte_cmd(SPIx, *pval, pcmd);
		pval++;
		pcmd++;
	}
	//---时钟线的极性
	(SPIx->msg_cpol == 0) ?
		PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit) :
		PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	//---工作状态为空闲
	SPIx->msg_state = IDLE;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_send_lsb_word(SPI_HandleType* SPIx, uint16_t val, uint8_t polarity)
{
	uint8_t index = 0;
	//---工作状态为忙碌
	SPIx->msg_state = BUSY;
	//---发送8bit 
	for (index = 0; index < 16; index++)
	{
		spi_msw_bit_lsb_word(SPIx,val, NULL);
		val >>= 1;
	}
	//---校验时钟极性
	if (polarity!=0)
	{
		//---时钟线的极性
		(SPIx->msg_cpol == 0) ?
			PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit) :
			PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	}
	//---工作状态为空闲
	SPIx->msg_state = IDLE;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_read_lsb_word(SPI_HandleType* SPIx, uint16_t* pval, uint8_t polarity)
{
	uint8_t index = 0;
	//---工作状态为忙碌
	SPIx->msg_state = BUSY;
	//---发送8bit 
	for (index = 0; index < 16; index++)
	{
		(*pval) >>= 1;
		spi_msw_bit_lsb_word(SPIx, 1, pval);
	}
	//---校验时钟极性
	if (polarity != 0)
	{
		//---时钟线的极性
		(SPIx->msg_cpol == 0) ?
			PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit) :
			PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	}
	//---工作状态为空闲
	SPIx->msg_state = IDLE;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_send_lsb_word_buffer(SPI_HandleType* SPIx, uint16_t *pval, uint16_t length)
{
	uint16_t index = 0;
	//---工作状态为忙碌
	SPIx->msg_state = BUSY;
	//---发送8bit 
	for (index = 0; index < length; index++)
	{
		spi_msw_send_lsb_word_buffer(SPIx, *pval, 0);
		pval++;
	}
	//---时钟线的极性
	(SPIx->msg_cpol == 0) ?
		PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit) :
		PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	//---工作状态为空闲
	SPIx->msg_state = IDLE;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_read_lsb_word_buffer(SPI_HandleType* SPIx, uint16_t *pval, uint16_t length)
{
	uint16_t index = 0;
	//---工作状态为忙碌
	SPIx->msg_state = BUSY;
	//---发送8bit 
	for (index = 0; index < length; index++)
	{
		spi_msw_read_lsb_word_buffer(SPIx, *pval, 0);
		pval++;
	}
	//---时钟线的极性
	(SPIx->msg_cpol == 0) ?
		PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit) :
		PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	//---工作状态为空闲
	SPIx->msg_state = IDLE;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_lsb_word_cmd(SPI_HandleType* SPIx, uint16_t val, uint16_t *pcmd)
{
	uint8_t index = 0;
	//---发送8bit 
	for (index = 0; index < 16; index++)
	{
		(*pcmd) >>= 1;
		spi_msw_bit_lsb_word(SPIx, val, pcmd);
		val >>= 1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_lsb_word(SPI_HandleType* SPIx, uint16_t val, uint16_t *pcmd)
{
	//---工作状态为忙碌
	SPIx->msg_state = BUSY;
	//---发送子数据
	spi_msw_lsb_word_cmd(SPIx, val, pcmd);
	//---时钟线的极性
	(SPIx->msg_cpol == 0) ?
		PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit) :
		PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	//---工作状态为空闲
	SPIx->msg_state = IDLE;
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_lsb_word_buffer(SPI_HandleType* SPIx, uint16_t *pval, uint16_t *pcmd,uint16_t length)
{
	uint16_t index = 0;
	//---工作状态为忙碌
	SPIx->msg_state = BUSY;
	//---发送字数据
	for (index=0;index<length;index++)
	{
		spi_msw_lsb_word_cmd(SPIx, *pval, pcmd);
		pval++;
		pcmd++;
	}
	//---时钟线的极性
	(SPIx->msg_cpol == 0) ?
		PIN_OUT_0(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit) :
		PIN_OUT_1(SPIx->msg_gpio_sck.msg_p_port, SPIx->msg_gpio_sck.msg_bit);
	//---工作状态为空闲
	SPIx->msg_state = IDLE;
	return OK_0;
}

#pragma endregion

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 发送字节数据
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_send_byte(SPI_HandleType* SPIx, uint8_t val)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 读取字节数据
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_read_byte(SPI_HandleType* SPIx, uint8_t *pval)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 收发字节数据
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_byte(SPI_HandleType* SPIx, uint8_t val, uint8_t *pcmd)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 收发多字节数据
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t spi_msw_byte_buffer(SPI_HandleType* SPIx, uint8_t *pval, uint8_t *pcmd,uint16_t length)
{
	return OK_0;
}



