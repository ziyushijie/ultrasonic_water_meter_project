#include "crc_task.h"

extern void my_crc_lib_init(MY_CRC_HandleType* CRCx, uint32_t(*func_time_tick)(void));

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参	数：
//////输出参	数：
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void crc_task_time_tick_init(uint32_t(*func_time_tick)(void))
{
	crc_lib_time_tick_init(func_time_tick);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void crc_task_init(uint32_t(*func_time_tick)(void))
{
	crc_lib_init(func_time_tick);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t  crc_task_enable(void)
{
	return crc_lib_enable();
}
///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint32_t crc_task_crc32(uint8_t *buffer, uint32_t length)
{
	return crc_lib_crc32(buffer, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint16_t crc_task_crc16_table(uint16_t crcSeed, uint16_t crc_data, uint8_t *buffer, uint32_t length)
{
	return crc_lib_crc16_table(crcSeed,crc_data,buffer, length);
}
///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t crc_task_crc8_table(uint8_t crcSeed, uint8_t crc, uint8_t *buffer, uint32_t length)
{
	return crc_lib_crc8_table(crcSeed,crc, buffer, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参	数：
//////输出参	数：
//////说		明：
//////////////////////////////////////////////////////////////////////////////
uint8_t crc_task_crc8_type(uint16_t type, uint8_t* buffer, uint32_t length)
{
	return crc_lib_crc8_type(type, buffer, length);
}


///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:
//////输入参数:
//////输出参数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t crc_task_check_sum_normal(uint8_t *buffer, uint32_t length)
{
	return crc_lib_check_sum_normal(buffer, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t  crc_task_check_sum_normal_pos(uint8_t* buffer, uint16_t pos, uint32_t length)
{
	return crc_lib_check_sum_normal_pos(buffer, pos, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t  crc_task_check_sum_special(uint8_t* buffer, uint32_t length)
{
	return crc_lib_check_sum_special(buffer, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint8_t  crc_task_check_sum_special_pos(uint8_t* buffer, uint16_t pos, uint32_t length)
{
	return crc_lib_check_sum_special_pos(buffer, pos, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参	数：
//////输出参	数：
//////说		明：
//////////////////////////////////////////////////////////////////////////////
uint8_t crc_task_check_sum_type(uint16_t type, uint8_t* buffer, uint32_t length)
{
	return crc_lib_check_sum_type(type, buffer, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint16_t crc_task_crc16_type(uint16_t type, uint8_t* buffer, uint32_t length)
{
	return crc_lib_crc16_type(type, buffer, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
uint16_t crc_task_crc16_table_seed_data(uint16_t crcSeed, uint16_t crc_data, uint8_t* buffer, uint32_t length)
{
	return crc_lib_crc16_table_seed_data(crcSeed,crc_data, buffer, length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数:
//////功		能:
//////输入参	数:
//////输出参	数:
//////说		明:
//////////////////////////////////////////////////////////////////////////////
void my_crc_task_init(MY_CRC_HandleType * CRCx, uint32_t(*func_time_tick)(void))
{
	my_crc_lib_init(CRCx,func_time_tick);
}

