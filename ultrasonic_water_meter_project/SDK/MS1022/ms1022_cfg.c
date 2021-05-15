#include "ms1022_cfg.h"

//===变量定义
MS1022_HandleType						g_ms1022_one = { 0 };
pMS1022_HandleType						p_ms1022_one = &g_ms1022_one;

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_init_one(MS1022_HandleType* MS1022x)
{
	//--->>>配置CSI中断---开始
	ST0 |= _0001_SAU_CH0_STOP_TRG_ON;    
	
	//---不使能中断
	CSIMK00 = 1U;   
	//---清楚中断标志位
	CSIIF00 = 0U;   

	//---设置CSI的中断优先级
	CSIPR100 = 1U;
	CSIPR000 = 1U;

	SIR00 = _0002_SAU_SIRMN_PECTMN | 
			_0001_SAU_SIRMN_OVCTMN;   

	SMR00 = _0020_SAU_SMRMN_INITIALVALUE | 
			_0000_SAU_CLOCK_SELECT_CK00 | 
			_0000_SAU_CLOCK_MODE_CKS |
			_0000_SAU_TRIGGER_SOFTWARE | 
			_0000_SAU_MODE_CSI | 
			_0000_SAU_TRANSFER_END;

	SCR00 = _C000_SAU_RECEPTION_TRANSMISSION | 
			_1000_SAU_TIMING_2 | 
			_0000_SAU_MSB | 
			_0007_SAU_LENGTH_8;

	SDR00 = 0x0000;

	SO0 &= ~_0100_SAU_CH0_CLOCK_OUTPUT_1;    /* CSI00 clock initial level */
	SO0 &= ~_0001_SAU_CH0_DATA_OUTPUT_1;    /* CSI00 SO initial level */
	SOE0 |= _0001_SAU_CH0_OUTPUT_ENABLE;    /* enable CSI00 output */
	
	//---MOSI---SI----P00
	//---MISO---SO----P17
	//---SCK----SCK---P16
	//---SS-----SS----P15
	//---RST----RST---P14
	//---INT----INT---P02

	///* Set SI00 pin */
	//PFSEG5 &= 0xF7U;
	//PM1 |= 0x80U;

	///* Set SO00 pin */
	//PFSEG5 &= 0xEFU;
	//PM0 &= 0xFEU;
	//P0 |= 0x01U;

	///* Set SCK00 pin */
	//PFSEG5 &= 0xFBU;
	//P1 |= 0x40U;
	//PM1 &= 0xBFU;

	MS1022x->msg_spix.msg_gpio_miso.msg_p_port = MS1022_SPI_MISO_PORT_ONE;
	MS1022x->msg_spix.msg_gpio_miso.msg_bit = MS1022_SPI_MISO_BIT_ONE;

	MS1022x->msg_spix.msg_gpio_mosi.msg_p_port = MS1022_SPI_MOSI_PORT_ONE;
	MS1022x->msg_spix.msg_gpio_mosi.msg_bit = MS1022_SPI_MOSI_BIT_ONE;

	MS1022x->msg_spix.msg_gpio_sck.msg_p_port = MS1022_SPI_SCK_PORT_ONE;
	MS1022x->msg_spix.msg_gpio_sck.msg_bit = MS1022_SPI_SCK_BIT_ONE;

	MS1022x->msg_spix.msg_gpio_cs.msg_p_port = MS1022_SPI_CS_PORT_ONE;
	MS1022x->msg_spix.msg_gpio_cs.msg_bit = MS1022_SPI_CS_BIT_ONE;

	MS1022x->msg_gpio_rst.msg_p_port = MS1022_RST_PORT_ONE;
	MS1022x->msg_gpio_rst.msg_bit = MS1022_RST_BIT_ONE;

	//---MISO设置输入模式且上拉打开
	gpio_task_pin_mode_input(MS1022x->msg_spix.msg_gpio_miso.msg_p_port, MS1022x->msg_spix.msg_gpio_miso.msg_bit);
	gpio_task_pin_mode_pull_up_set(MS1022x->msg_spix.msg_gpio_miso.msg_p_port, MS1022x->msg_spix.msg_gpio_miso.msg_bit);

	//---MOSI设置为输出模式且输出为高
	gpio_task_pin_mode_output(MS1022x->msg_spix.msg_gpio_mosi.msg_p_port, MS1022x->msg_spix.msg_gpio_mosi.msg_bit);
	PIN_OUT_1(MS1022x->msg_spix.msg_gpio_mosi.msg_p_port, MS1022x->msg_spix.msg_gpio_mosi.msg_bit);

	//---SCK设置为输出模式且输出为高
	gpio_task_pin_mode_output(MS1022x->msg_spix.msg_gpio_sck.msg_p_port, MS1022x->msg_spix.msg_gpio_sck.msg_bit);
	PIN_OUT_1(MS1022x->msg_spix.msg_gpio_sck.msg_p_port, MS1022x->msg_spix.msg_gpio_sck.msg_bit);

	//---SS设置为输出模式且输出为高
	gpio_task_pin_mode_output(MS1022x->msg_spix.msg_gpio_cs.msg_p_port, MS1022x->msg_spix.msg_gpio_cs.msg_bit);
	PIN_OUT_1(MS1022x->msg_spix.msg_gpio_cs.msg_p_port, MS1022x->msg_spix.msg_gpio_cs.msg_bit);

	//---RST设置为输出模式且输出为0
	gpio_task_pin_mode_output(MS1022x->msg_gpio_rst.msg_p_port, MS1022x->msg_gpio_rst.msg_bit);
	PIN_OUT_1(MS1022x->msg_gpio_rst.msg_p_port, MS1022x->msg_gpio_rst.msg_bit);

	SO0 &= ~_0100_SAU_CH0_CLOCK_OUTPUT_1;   
	SO0 &= ~_0001_SAU_CH0_DATA_OUTPUT_1;    
	SOE0 |= _0001_SAU_CH0_OUTPUT_ENABLE;   
	SS0 |= _0001_SAU_CH0_START_TRG_ON;     
	
	//---清楚中断标志位
	//CSIIF00 = 0U;
	//---使能中断
	//CSIMK00 = 0U;

	//---<<<配置CSI中断---结束

	//--->>>配置端口中断---开始
	//---不使能中断
	PMK7 = 1U;    /* disable INTP7 operation */
	//---清楚中断标志
	PIF7 = 0U;    /* clear INTP7 interrupt flag */
	
	//---设置中断优先级
	PPR17 = 0U;
	PPR07 = 1U;

	//---设置下降沿触发
	EGN0 |= _80_INTP7_EDGE_FALLING_SEL;

	//---设置INT为输入模式且上拉使能
	gpio_task_pin_mode_input(MS1022_INT_PORT_ONE, MS1022_INT_BIT_ONE);
	gpio_task_pin_mode_pull_up_set(MS1022_INT_PORT_ONE, MS1022_INT_BIT_ONE);

	//---清楚中断标志
	PIF7 = 0U;   
	//---使能中断
	PMK7 = 0U; 
	//---<<<配置端口中断---结束
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_init_two(MS1022_HandleType* MS1022x)
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
uint8_t ms1022_spi_init_three(MS1022_HandleType* MS1022x)
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
uint8_t ms1022_spi_time_tick_init(MS1022_HandleType* MS1022x, uint32_t(*func_time_tick)(void))
{
	//---注册滴答函数
	(func_time_tick != NULL) ?
		(MS1022x->msg_f_time_tick = func_time_tick) :
		(MS1022x->msg_f_time_tick = sys_tick_task_get_tick);
	//---SPI滴答函数
	spi_task_time_tick_init(&(MS1022x->msg_spix), func_time_tick);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_init(MS1022_HandleType* MS1022x, void(*func_delay_us)(uint32_t us), 
	void(*func_delay_ms)(uint32_t ms), uint32_t(*func_time_tick)(void), uint8_t is_hw)
{
	uint8_t _return = ERROR_1;
	//---初始化设备1
	if ((MS1022x != NULL) && (MS1022x == MS1022_TASK_ONE))
	{
		ms1022_spi_init_one(MS1022x);
		_return = OK_0;
	}
	//---初始化设备2
	if ((MS1022x != NULL) && (MS1022x == MS1022_TASK_TWO))
	{
		ms1022_spi_init_two(MS1022x);
		_return = OK_0;
	}
	//---初始化设备2
	if ((MS1022x != NULL) && (MS1022x == MS1022_TASK_THREE))
	{
		ms1022_spi_init_three(MS1022x);
		_return = OK_0;
	}

	//---初始化SPI端口
	if (_return==OK_0)
	{
		//---us延时函数
		(func_delay_us != NULL) ?
			(MS1022x->msg_spix.msg_f_delay_us = func_delay_us) :
			(MS1022x->msg_spix.msg_f_delay_us = delay_task_us);
		//---ms延时函数
		(func_delay_us != NULL) ?
			(MS1022x->msg_f_delay_ms = func_delay_ms) :
			(MS1022x->msg_f_delay_ms = delay_task_ms);
		//---注册滴答函数
		(func_time_tick != NULL) ?
			(MS1022x->msg_f_time_tick = func_time_tick) :
			(MS1022x->msg_f_time_tick = sys_tick_task_get_tick);
		//---数据缓存区
		MS1022x->msg_spix.msg_p_send_data_buffer = MS1022x->msg_send_data_buffer;
		MS1022x->msg_spix.msg_p_read_data_buffer = MS1022x->msg_read_data_buffer;
		//---初始化SPI
		spi_task_init(&(MS1022x->msg_spix),func_delay_us,func_time_tick);
		//---判断是硬件还是软件端口
		if (is_hw!=0)
		{
			//---spi硬件初始化
			spi_task_mhw_gpio_init(&(MS1022x->msg_spix));
			MS1022x->msg_spix.msg_pulse_width = 5;
		}
		else
		{
			//---spi软件初始化
			spi_task_msw_gpio_init(&(MS1022x->msg_spix));
		}
		MS1022x->msg_spix.msg_data_count = 2;
		MS1022x->msg_spix.msg_state = 3;
		//---初始化复位ms1022
		ms1022_spi_rst(MS1022x);
	}

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 上电复位设备
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_rst(MS1022_HandleType* MS1022x)
{
	PIN_OUT_0(MS1022x->msg_gpio_rst.msg_p_port, MS1022x->msg_gpio_rst.msg_bit);
	delay_task_us(450);
	PIN_OUT_1(MS1022x->msg_gpio_rst.msg_p_port, MS1022x->msg_gpio_rst.msg_bit);
	delay_task_us(450);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 设置中断标识信号
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_int_flag_set(MS1022_HandleType* MS1022x)
{
	MS1022x->msg_int_flag = 1;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 清楚中断标识信号
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_int_flag_clear(MS1022_HandleType* MS1022x)
{
	MS1022x->msg_int_flag = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 等待中断标识信号
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_int_flag_wait(MS1022_HandleType* MS1022x)
{
	uint8_t _return = ERROR_1;
	uint32_t cnt = 0;
	//---获取时间标签
	cnt = MS1022x->msg_f_time_tick();
	//---等待中断信号
	while (1)
	{
		//---判断中断标识信号
		if (MS1022x->msg_int_flag!=0)
		{
			//---正常退出
			_return = OK_0;
			break;
		}
		//---判断是否超时
		if (TIME_SPAN(MS1022x->msg_f_time_tick(),cnt)>MS1022_WAIT_FLAG_MAX_TIME)
		{
			//---超时退出
			_return = ERROR_2;
			break;
		}
		//---喂狗
		WDT_RESET();
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 硬件收发SPI数据
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_mhw_it_byte_buffer(MS1022_HandleType* MS1022x, uint8_t *pval, uint8_t *pcmd, uint16_t length)
{
	uint8_t _return = ERROR_1;
	uint32_t cnt = 0;
	MS1022x->msg_spix.msg_p_send_data_buffer = pval;
	MS1022x->msg_spix.msg_p_read_data_buffer = pcmd;
	if (length>0)
	{
		//---使能数据发送
		PIN_OUT_0(MS1022x->msg_spix.msg_gpio_cs.msg_p_port, MS1022x->msg_spix.msg_gpio_cs.msg_bit);
		//---设置发送数据个数
		MS1022x->msg_spix.msg_data_count = length;
		//---设置spi的工作状态为忙碌中
		MS1022x->msg_spix.msg_state = BUSY;
		//---不使能中断
		CSIMK00 = 1U; 
		//---清楚中断标志位
		//CSIIF00 = 0U;
		//---数据发送
		SIO00 = *(MS1022x->msg_spix.msg_p_send_data_buffer);
		//---数据偏移
		MS1022x->msg_spix.msg_p_send_data_buffer++;
		//---使能中断
		CSIMK00 = 0U;
		//---发送数据个数减少
		MS1022x->msg_spix.msg_data_count--;
		//---获取时间标签
		cnt = MS1022x->msg_f_time_tick();
		//---等待数据发送完成
		while (1)
		{
			//---判断发送挖出讷航
			if (MS1022x->msg_spix.msg_state == IDLE)
			{
				_return = OK_0;
				//---正常退出
				break;
			}
			//---判断时间超时
			if (TIME_SPAN(MS1022x->msg_f_time_tick(),cnt)>MS1022_WAIT_IDLE_MAX_TIME)
			{
				_return = ERROR_2;
				//---超时退出
				break;
			}
			//---喂狗
			WDT_RESET();
		}
		//---不使能数据发送
		PIN_OUT_1(MS1022x->msg_spix.msg_gpio_cs.msg_p_port, MS1022x->msg_spix.msg_gpio_cs.msg_bit);
	}
	
	////---使能数据发送
	//PIN_OUT_0(MS1022x->msg_spix.msg_gpio_cs.msg_p_port, MS1022x->msg_spix.msg_gpio_cs.msg_bit);
	//_return= spi_task_mhw_it_byte_buffer(&(MS1022x->msg_spix), *pval, pcmd, length);
	////---使能数据发送
	//PIN_OUT_0(MS1022x->msg_spix.msg_gpio_cs.msg_p_port, MS1022x->msg_spix.msg_gpio_cs.msg_bit);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 硬件中断处理函数
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_mhw_it_irq_handle(MS1022_HandleType* MS1022x)
{
	vltuint16_t err_type = 0;
	err_type= (SSR00 & _0001_SAU_OVERRUN_ERROR);
	//---清楚错误标识
	SIR00 = err_type;
	//---判断错误信息
	if (err_type==0)
	{
		if (MS1022x->msg_spix.msg_data_count != 0)
		{
			//---数据接收
			*(MS1022x->msg_spix.msg_p_read_data_buffer) = SIO00;
			//---数据地址偏移
			MS1022x->msg_spix.msg_p_read_data_buffer++;
			
			//---数据发送
			SIO00 = *(MS1022x->msg_spix.msg_p_send_data_buffer);
			//---数据地址偏移
			MS1022x->msg_spix.msg_p_send_data_buffer++;

			MS1022x->msg_spix.msg_data_count--;
		}
		else
		{
			//---数据接收
			*(MS1022x->msg_spix.msg_p_read_data_buffer) = SIO00;
			//---数据收发完成设置spi的工作状态为完成
			MS1022x->msg_spix.msg_state = IDLE;
		}
		return OK_0;
	}
	else
	{
		//---设置spi的工作状态为错误
		MS1022x->msg_spix.msg_state = ERROR;
	}
	return ERROR_1;
	//return spi_task_mhw_it_irq_handle(&(MS1022x->msg_spix));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_msw_byte_buffer(MS1022_HandleType* MS1022x, uint8_t *pval, uint8_t *pcmd, uint16_t length)
{
	uint8_t _return = OK_0;
	//---使能数据发送
	PIN_OUT_0(MS1022x->msg_spix.msg_gpio_cs.msg_p_port, MS1022x->msg_spix.msg_gpio_cs.msg_bit);
	//---数据收发
	_return= spi_task_msw_msb_byte_buffer(&(MS1022x->msg_spix), pval, pcmd, length);
	//---不使能数据发送
	PIN_OUT_1(MS1022x->msg_spix.msg_gpio_cs.msg_p_port, MS1022x->msg_spix.msg_gpio_cs.msg_bit);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_byte_buffer(MS1022_HandleType* MS1022x, uint8_t *pval, uint8_t *pcmd, uint16_t length)
{
//	if (MS1022x->msg_spix.msg_hw_mode==0)
//	{
//		return ms1022_spi_msw_byte_buffer(&(MS1022x->msg_spix), pval, pcmd, length);
//	}
//	else
//	{
//		return ms1022_spi_mhw_it_byte_buffer(&(MS1022x->msg_spix), pval, pcmd, length);
//	}
	return ms1022_spi_mhw_it_byte_buffer(&(MS1022x->msg_spix), pval, pcmd, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 读取指定寄存器的值
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_read_reg(MS1022_HandleType* MS1022x, uint8_t index)
{

	return ms1022_spi_byte_buffer(MS1022x, MS1022x->msg_send_data_buffer, MS1022x->msg_read_data_buffer, 5);
}


///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 讲数据写入到指定的寄存器中
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_send_reg(MS1022_HandleType* MS1022x, uint8_t index,uint32_t val)
{

	return ms1022_spi_byte_buffer(MS1022x, MS1022x->msg_send_data_buffer, MS1022x->msg_read_data_buffer, 5);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 发送命令
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_send_cmd(MS1022_HandleType* MS1022x, uint8_t cmd)
{
	MS1022x->msg_send_data_buffer[0] = cmd;
	return ms1022_spi_byte_buffer(MS1022x, MS1022x->msg_send_data_buffer, MS1022x->msg_read_data_buffer, 1);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 读取状态寄存器的值
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_read_reg_state(MS1022_HandleType* MS1022x)
{
	MS1022x->msg_send_data_buffer[0] = MS1022_READ_STATE| MS1022_READ_ADDR_MASK;
	MS1022x->msg_send_data_buffer[1] = 0xFF;
	MS1022x->msg_send_data_buffer[2] = 0xFF;
	return ms1022_spi_byte_buffer(MS1022x, MS1022x->msg_send_data_buffer, MS1022x->msg_read_data_buffer, 3);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 读取脉冲宽度测量标志寄存器
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_read_reg_pw1st(MS1022_HandleType* MS1022x)
{
	MS1022x->msg_send_data_buffer[0] = MS1022_READ_PW1ST | MS1022_READ_ADDR_MASK;
	return ms1022_spi_byte_buffer(MS1022x, MS1022x->msg_send_data_buffer, MS1022x->msg_read_data_buffer, 1);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 通信测试函数
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_comm_test(MS1022_HandleType* MS1022x)
{
	MS1022x->msg_send_data_buffer[0] = MS1022_COMM_TEST | MS1022_READ_ADDR_MASK;
	return ms1022_spi_byte_buffer(MS1022x, MS1022x->msg_send_data_buffer, MS1022x->msg_read_data_buffer, 1);
}

