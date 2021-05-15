#include "ms1022_cfg.h"

//===��������
MS1022_HandleType						g_ms1022_one = { 0 };
pMS1022_HandleType						p_ms1022_one = &g_ms1022_one;

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_init_one(MS1022_HandleType* MS1022x)
{
	//--->>>����CSI�ж�---��ʼ
	ST0 |= _0001_SAU_CH0_STOP_TRG_ON;    
	
	//---��ʹ���ж�
	CSIMK00 = 1U;   
	//---����жϱ�־λ
	CSIIF00 = 0U;   

	//---����CSI���ж����ȼ�
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

	//---MISO��������ģʽ��������
	gpio_task_pin_mode_input(MS1022x->msg_spix.msg_gpio_miso.msg_p_port, MS1022x->msg_spix.msg_gpio_miso.msg_bit);
	gpio_task_pin_mode_pull_up_set(MS1022x->msg_spix.msg_gpio_miso.msg_p_port, MS1022x->msg_spix.msg_gpio_miso.msg_bit);

	//---MOSI����Ϊ���ģʽ�����Ϊ��
	gpio_task_pin_mode_output(MS1022x->msg_spix.msg_gpio_mosi.msg_p_port, MS1022x->msg_spix.msg_gpio_mosi.msg_bit);
	PIN_OUT_1(MS1022x->msg_spix.msg_gpio_mosi.msg_p_port, MS1022x->msg_spix.msg_gpio_mosi.msg_bit);

	//---SCK����Ϊ���ģʽ�����Ϊ��
	gpio_task_pin_mode_output(MS1022x->msg_spix.msg_gpio_sck.msg_p_port, MS1022x->msg_spix.msg_gpio_sck.msg_bit);
	PIN_OUT_1(MS1022x->msg_spix.msg_gpio_sck.msg_p_port, MS1022x->msg_spix.msg_gpio_sck.msg_bit);

	//---SS����Ϊ���ģʽ�����Ϊ��
	gpio_task_pin_mode_output(MS1022x->msg_spix.msg_gpio_cs.msg_p_port, MS1022x->msg_spix.msg_gpio_cs.msg_bit);
	PIN_OUT_1(MS1022x->msg_spix.msg_gpio_cs.msg_p_port, MS1022x->msg_spix.msg_gpio_cs.msg_bit);

	//---RST����Ϊ���ģʽ�����Ϊ0
	gpio_task_pin_mode_output(MS1022x->msg_gpio_rst.msg_p_port, MS1022x->msg_gpio_rst.msg_bit);
	PIN_OUT_1(MS1022x->msg_gpio_rst.msg_p_port, MS1022x->msg_gpio_rst.msg_bit);

	SO0 &= ~_0100_SAU_CH0_CLOCK_OUTPUT_1;   
	SO0 &= ~_0001_SAU_CH0_DATA_OUTPUT_1;    
	SOE0 |= _0001_SAU_CH0_OUTPUT_ENABLE;   
	SS0 |= _0001_SAU_CH0_START_TRG_ON;     
	
	//---����жϱ�־λ
	//CSIIF00 = 0U;
	//---ʹ���ж�
	//CSIMK00 = 0U;

	//---<<<����CSI�ж�---����

	//--->>>���ö˿��ж�---��ʼ
	//---��ʹ���ж�
	PMK7 = 1U;    /* disable INTP7 operation */
	//---����жϱ�־
	PIF7 = 0U;    /* clear INTP7 interrupt flag */
	
	//---�����ж����ȼ�
	PPR17 = 0U;
	PPR07 = 1U;

	//---�����½��ش���
	EGN0 |= _80_INTP7_EDGE_FALLING_SEL;

	//---����INTΪ����ģʽ������ʹ��
	gpio_task_pin_mode_input(MS1022_INT_PORT_ONE, MS1022_INT_BIT_ONE);
	gpio_task_pin_mode_pull_up_set(MS1022_INT_PORT_ONE, MS1022_INT_BIT_ONE);

	//---����жϱ�־
	PIF7 = 0U;   
	//---ʹ���ж�
	PMK7 = 0U; 
	//---<<<���ö˿��ж�---����
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_init_two(MS1022_HandleType* MS1022x)
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
uint8_t ms1022_spi_init_three(MS1022_HandleType* MS1022x)
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
uint8_t ms1022_spi_time_tick_init(MS1022_HandleType* MS1022x, uint32_t(*func_time_tick)(void))
{
	//---ע��δ���
	(func_time_tick != NULL) ?
		(MS1022x->msg_f_time_tick = func_time_tick) :
		(MS1022x->msg_f_time_tick = sys_tick_task_get_tick);
	//---SPI�δ���
	spi_task_time_tick_init(&(MS1022x->msg_spix), func_time_tick);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_init(MS1022_HandleType* MS1022x, void(*func_delay_us)(uint32_t us), 
	void(*func_delay_ms)(uint32_t ms), uint32_t(*func_time_tick)(void), uint8_t is_hw)
{
	uint8_t _return = ERROR_1;
	//---��ʼ���豸1
	if ((MS1022x != NULL) && (MS1022x == MS1022_TASK_ONE))
	{
		ms1022_spi_init_one(MS1022x);
		_return = OK_0;
	}
	//---��ʼ���豸2
	if ((MS1022x != NULL) && (MS1022x == MS1022_TASK_TWO))
	{
		ms1022_spi_init_two(MS1022x);
		_return = OK_0;
	}
	//---��ʼ���豸2
	if ((MS1022x != NULL) && (MS1022x == MS1022_TASK_THREE))
	{
		ms1022_spi_init_three(MS1022x);
		_return = OK_0;
	}

	//---��ʼ��SPI�˿�
	if (_return==OK_0)
	{
		//---us��ʱ����
		(func_delay_us != NULL) ?
			(MS1022x->msg_spix.msg_f_delay_us = func_delay_us) :
			(MS1022x->msg_spix.msg_f_delay_us = delay_task_us);
		//---ms��ʱ����
		(func_delay_us != NULL) ?
			(MS1022x->msg_f_delay_ms = func_delay_ms) :
			(MS1022x->msg_f_delay_ms = delay_task_ms);
		//---ע��δ���
		(func_time_tick != NULL) ?
			(MS1022x->msg_f_time_tick = func_time_tick) :
			(MS1022x->msg_f_time_tick = sys_tick_task_get_tick);
		//---���ݻ�����
		MS1022x->msg_spix.msg_p_send_data_buffer = MS1022x->msg_send_data_buffer;
		MS1022x->msg_spix.msg_p_read_data_buffer = MS1022x->msg_read_data_buffer;
		//---��ʼ��SPI
		spi_task_init(&(MS1022x->msg_spix),func_delay_us,func_time_tick);
		//---�ж���Ӳ����������˿�
		if (is_hw!=0)
		{
			//---spiӲ����ʼ��
			spi_task_mhw_gpio_init(&(MS1022x->msg_spix));
			MS1022x->msg_spix.msg_pulse_width = 5;
		}
		else
		{
			//---spi�����ʼ��
			spi_task_msw_gpio_init(&(MS1022x->msg_spix));
		}
		MS1022x->msg_spix.msg_data_count = 2;
		MS1022x->msg_spix.msg_state = 3;
		//---��ʼ����λms1022
		ms1022_spi_rst(MS1022x);
	}

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: �ϵ縴λ�豸
//////�����	��:
//////�����	��:
//////˵		��:
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
//////��		��:
//////��		��: �����жϱ�ʶ�ź�
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_int_flag_set(MS1022_HandleType* MS1022x)
{
	MS1022x->msg_int_flag = 1;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ����жϱ�ʶ�ź�
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_int_flag_clear(MS1022_HandleType* MS1022x)
{
	MS1022x->msg_int_flag = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: �ȴ��жϱ�ʶ�ź�
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_int_flag_wait(MS1022_HandleType* MS1022x)
{
	uint8_t _return = ERROR_1;
	uint32_t cnt = 0;
	//---��ȡʱ���ǩ
	cnt = MS1022x->msg_f_time_tick();
	//---�ȴ��ж��ź�
	while (1)
	{
		//---�ж��жϱ�ʶ�ź�
		if (MS1022x->msg_int_flag!=0)
		{
			//---�����˳�
			_return = OK_0;
			break;
		}
		//---�ж��Ƿ�ʱ
		if (TIME_SPAN(MS1022x->msg_f_time_tick(),cnt)>MS1022_WAIT_FLAG_MAX_TIME)
		{
			//---��ʱ�˳�
			_return = ERROR_2;
			break;
		}
		//---ι��
		WDT_RESET();
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: Ӳ���շ�SPI����
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_mhw_it_byte_buffer(MS1022_HandleType* MS1022x, uint8_t *pval, uint8_t *pcmd, uint16_t length)
{
	uint8_t _return = ERROR_1;
	uint32_t cnt = 0;
	MS1022x->msg_spix.msg_p_send_data_buffer = pval;
	MS1022x->msg_spix.msg_p_read_data_buffer = pcmd;
	if (length>0)
	{
		//---ʹ�����ݷ���
		PIN_OUT_0(MS1022x->msg_spix.msg_gpio_cs.msg_p_port, MS1022x->msg_spix.msg_gpio_cs.msg_bit);
		//---���÷������ݸ���
		MS1022x->msg_spix.msg_data_count = length;
		//---����spi�Ĺ���״̬Ϊæµ��
		MS1022x->msg_spix.msg_state = BUSY;
		//---��ʹ���ж�
		CSIMK00 = 1U; 
		//---����жϱ�־λ
		//CSIIF00 = 0U;
		//---���ݷ���
		SIO00 = *(MS1022x->msg_spix.msg_p_send_data_buffer);
		//---����ƫ��
		MS1022x->msg_spix.msg_p_send_data_buffer++;
		//---ʹ���ж�
		CSIMK00 = 0U;
		//---�������ݸ�������
		MS1022x->msg_spix.msg_data_count--;
		//---��ȡʱ���ǩ
		cnt = MS1022x->msg_f_time_tick();
		//---�ȴ����ݷ������
		while (1)
		{
			//---�жϷ����ڳ�ګ��
			if (MS1022x->msg_spix.msg_state == IDLE)
			{
				_return = OK_0;
				//---�����˳�
				break;
			}
			//---�ж�ʱ�䳬ʱ
			if (TIME_SPAN(MS1022x->msg_f_time_tick(),cnt)>MS1022_WAIT_IDLE_MAX_TIME)
			{
				_return = ERROR_2;
				//---��ʱ�˳�
				break;
			}
			//---ι��
			WDT_RESET();
		}
		//---��ʹ�����ݷ���
		PIN_OUT_1(MS1022x->msg_spix.msg_gpio_cs.msg_p_port, MS1022x->msg_spix.msg_gpio_cs.msg_bit);
	}
	
	////---ʹ�����ݷ���
	//PIN_OUT_0(MS1022x->msg_spix.msg_gpio_cs.msg_p_port, MS1022x->msg_spix.msg_gpio_cs.msg_bit);
	//_return= spi_task_mhw_it_byte_buffer(&(MS1022x->msg_spix), *pval, pcmd, length);
	////---ʹ�����ݷ���
	//PIN_OUT_0(MS1022x->msg_spix.msg_gpio_cs.msg_p_port, MS1022x->msg_spix.msg_gpio_cs.msg_bit);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: Ӳ���жϴ�����
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_mhw_it_irq_handle(MS1022_HandleType* MS1022x)
{
	vltuint16_t err_type = 0;
	err_type= (SSR00 & _0001_SAU_OVERRUN_ERROR);
	//---��������ʶ
	SIR00 = err_type;
	//---�жϴ�����Ϣ
	if (err_type==0)
	{
		if (MS1022x->msg_spix.msg_data_count != 0)
		{
			//---���ݽ���
			*(MS1022x->msg_spix.msg_p_read_data_buffer) = SIO00;
			//---���ݵ�ַƫ��
			MS1022x->msg_spix.msg_p_read_data_buffer++;
			
			//---���ݷ���
			SIO00 = *(MS1022x->msg_spix.msg_p_send_data_buffer);
			//---���ݵ�ַƫ��
			MS1022x->msg_spix.msg_p_send_data_buffer++;

			MS1022x->msg_spix.msg_data_count--;
		}
		else
		{
			//---���ݽ���
			*(MS1022x->msg_spix.msg_p_read_data_buffer) = SIO00;
			//---�����շ��������spi�Ĺ���״̬Ϊ���
			MS1022x->msg_spix.msg_state = IDLE;
		}
		return OK_0;
	}
	else
	{
		//---����spi�Ĺ���״̬Ϊ����
		MS1022x->msg_spix.msg_state = ERROR;
	}
	return ERROR_1;
	//return spi_task_mhw_it_irq_handle(&(MS1022x->msg_spix));
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_msw_byte_buffer(MS1022_HandleType* MS1022x, uint8_t *pval, uint8_t *pcmd, uint16_t length)
{
	uint8_t _return = OK_0;
	//---ʹ�����ݷ���
	PIN_OUT_0(MS1022x->msg_spix.msg_gpio_cs.msg_p_port, MS1022x->msg_spix.msg_gpio_cs.msg_bit);
	//---�����շ�
	_return= spi_task_msw_msb_byte_buffer(&(MS1022x->msg_spix), pval, pcmd, length);
	//---��ʹ�����ݷ���
	PIN_OUT_1(MS1022x->msg_spix.msg_gpio_cs.msg_p_port, MS1022x->msg_spix.msg_gpio_cs.msg_bit);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: 
//////�����	��:
//////�����	��:
//////˵		��:
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
//////��		��:
//////��		��: ��ȡָ���Ĵ�����ֵ
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_read_reg(MS1022_HandleType* MS1022x, uint8_t index)
{

	return ms1022_spi_byte_buffer(MS1022x, MS1022x->msg_send_data_buffer, MS1022x->msg_read_data_buffer, 5);
}


///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ������д�뵽ָ���ļĴ�����
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_send_reg(MS1022_HandleType* MS1022x, uint8_t index,uint32_t val)
{

	return ms1022_spi_byte_buffer(MS1022x, MS1022x->msg_send_data_buffer, MS1022x->msg_read_data_buffer, 5);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��������
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_send_cmd(MS1022_HandleType* MS1022x, uint8_t cmd)
{
	MS1022x->msg_send_data_buffer[0] = cmd;
	return ms1022_spi_byte_buffer(MS1022x, MS1022x->msg_send_data_buffer, MS1022x->msg_read_data_buffer, 1);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ȡ״̬�Ĵ�����ֵ
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_read_reg_state(MS1022_HandleType* MS1022x)
{
	MS1022x->msg_send_data_buffer[0] = MS1022_READ_STATE| MS1022_READ_ADDR_MASK;
	MS1022x->msg_send_data_buffer[1] = 0xFF;
	MS1022x->msg_send_data_buffer[2] = 0xFF;
	return ms1022_spi_byte_buffer(MS1022x, MS1022x->msg_send_data_buffer, MS1022x->msg_read_data_buffer, 3);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ��ȡ�����Ȳ�����־�Ĵ���
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_read_reg_pw1st(MS1022_HandleType* MS1022x)
{
	MS1022x->msg_send_data_buffer[0] = MS1022_READ_PW1ST | MS1022_READ_ADDR_MASK;
	return ms1022_spi_byte_buffer(MS1022x, MS1022x->msg_send_data_buffer, MS1022x->msg_read_data_buffer, 1);
}

///////////////////////////////////////////////////////////////////////////////
//////��		��:
//////��		��: ͨ�Ų��Ժ���
//////�����	��:
//////�����	��:
//////˵		��:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_comm_test(MS1022_HandleType* MS1022x)
{
	MS1022x->msg_send_data_buffer[0] = MS1022_COMM_TEST | MS1022_READ_ADDR_MASK;
	return ms1022_spi_byte_buffer(MS1022x, MS1022x->msg_send_data_buffer, MS1022x->msg_read_data_buffer, 1);
}

