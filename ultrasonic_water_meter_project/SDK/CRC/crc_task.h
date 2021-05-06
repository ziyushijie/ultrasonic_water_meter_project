#ifndef CRC_TASK_H_
#define CRC_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "crc_lib.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===º¯Êý¶¨Òå
	void	 crc_task_time_tick_init(uint32_t(*func_time_tick)(void));
	void	 crc_task_init(uint32_t(*func_time_tick)(void));
	uint8_t  crc_task_enable(void);
	uint32_t crc_task_crc32(uint8_t *buffer, uint32_t length);
	uint16_t crc_task_crc16_table(uint16_t crcSeed, uint16_t crc_data, uint8_t *buffer, uint32_t length);
	uint8_t  crc_task_crc8_table(uint8_t crcSeed, uint8_t crc, uint8_t *buffer, uint32_t length);
	uint8_t  crc_task_crc8_type(uint16_t type, uint8_t* buffer, uint32_t length);
	uint8_t  crc_task_check_sum_normal(uint8_t *buffer, uint32_t length);
	uint8_t  crc_task_check_sum_normal_pos(uint8_t* buffer, uint16_t pos, uint32_t length);
	uint8_t  crc_task_check_sum_special(uint8_t* buffer, uint32_t length);
	uint8_t  crc_task_check_sum_special_pos(uint8_t* buffer, uint16_t pos, uint32_t length);
	uint8_t  crc_task_check_sum_type(uint16_t type, uint8_t* buffer, uint32_t length);
	uint16_t crc_task_crc16_type(uint16_t type, uint8_t* buffer, uint32_t length);
	uint16_t crc_task_crc16_table_seed_data(uint16_t crcSeed, uint16_t crc_data, uint8_t* buffer, uint32_t length);
	//void my_crc_task_init(MY_CRC_HandleType* MCRCx, uint32_t(*func_time_tick)(void));
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*CRC_TASK_H_ */ 