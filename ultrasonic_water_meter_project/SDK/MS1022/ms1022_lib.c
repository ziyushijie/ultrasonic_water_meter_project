#include "ms1022_lib.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_lib_time_tick_init(MS1022_HandleType* MS1022x, uint32_t(*func_time_tick)(void))
{
	return ms1022_spi_time_tick_init(MS1022x, func_time_tick);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_lib_init(MS1022_HandleType* MS1022x, void(*func_delay_us)(uint32_t us),
	void(*func_delay_ms)(uint32_t ms), uint32_t(*func_time_tick)(void), uint8_t is_hw)
{
	return ms1022_spi_init(MS1022x,func_delay_us,func_delay_ms, func_time_tick,is_hw);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_lib_int_flag_set(MS1022_HandleType* MS1022x)
{
	return ms1022_spi_int_flag_set(MS1022x);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_lib_mhw_it_irq_handle(MS1022_HandleType* MS1022x)
{
	return ms1022_spi_mhw_it_irq_handle(MS1022x);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_lib_read_reg(MS1022_HandleType* MS1022x, uint8_t index)
{
	return ms1022_spi_read_reg(MS1022x, index);
}
///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_lib_send_reg(MS1022_HandleType* MS1022x, uint8_t index, uint32_t val)
{
	return ms1022_spi_send_reg(MS1022x, index,val);
}
///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_lib_send_cmd(MS1022_HandleType* MS1022x, uint8_t cmd)
{
	return ms1022_spi_send_cmd(MS1022x, cmd);
}
///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint16_t ms1022_spi_lib_read_reg_state(MS1022_HandleType* MS1022x)
{
	return ms1022_spi_read_reg_state(MS1022x);
}
///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_lib_read_reg_pw1st(MS1022_HandleType* MS1022x)
{
	return ms1022_spi_read_reg_pw1st(MS1022x);
}
///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_lib_comm_test(MS1022_HandleType* MS1022x)
{
	return ms1022_spi_comm_test(MS1022x);
}
///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_lib_read_start_temperature(MS1022_HandleType* MS1022x)
{
	return ms1022_spi_read_start_temperature(MS1022x);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_lib_read_start_temperature_restart(MS1022_HandleType* MS1022x)
{
	return ms1022_spi_read_start_temperature_restart(MS1022x);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_lib_calibration_resonator(MS1022_HandleType* MS1022x)
{
	return ms1022_spi_calibration_resonator(MS1022x);
}


///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_lib_read_start_tof(MS1022_HandleType* MS1022x)
{
	return ms1022_spi_read_start_tof(MS1022x);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能: 
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t ms1022_spi_lib_read_start_tof_restart(MS1022_HandleType* MS1022x)
{
	return ms1022_spi_read_start_tof_restart(MS1022x);
}