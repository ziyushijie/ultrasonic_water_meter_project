#include "complier_cfg.h"

//===获取编译的日期和时间
#ifdef ENABE_VERSION_DATA_TIME_LOG
	#if defined(MCU_USE_STM32)
		const uint8_t g_version_date[VERSION_DATE_SIZE] = __DATE__;
		const uint8_t g_version_time[VERSION_TIME_SIZE] = __TIME__;
	#elif defined(MCU_USE_AVR)
		PRO_FLASH_uint8_t  g_version_date[VERSION_DATE_SIZE] = __DATE__;
		PRO_FLASH_uint8_t  g_version_time[VERSION_TIME_SIZE] = __TIME__;
	#elif defined(MCU_USE_RL78)
		const uint8_t g_version_date[VERSION_DATE_SIZE] = __DATE__;
		const uint8_t g_version_time[VERSION_TIME_SIZE] = __TIME__;
	#else 
		#error "不支持型号的MCU."
	#endif
#endif

