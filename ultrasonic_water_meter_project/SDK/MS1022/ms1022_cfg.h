#ifndef MS1022_CFG_H_
#define MS1022_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	
	#include "complier_lib.h"
	#include "gpio_task.h"
	#include "delay_task.h"
	#include "sys_tick_task.h"
	#include "hw_config.h"
	#include "spi_task.h"

	//===最大等待时间
	#define MS1022_WAIT_FLAG_MAX_TIME					(100/MS1022_MIN_PULSE_WIDTH)
	#define MS1022_WAIT_IDLE_MAX_TIME					(200/MS1022_MIN_PULSE_WIDTH)
	//===数据缓存区大小
	#define MS1022_DATA_BUFFER_MAX_SIZE					5

	//===读地址
	#define MS1022_READ_ADDR_MASK						0xB0
	//===写地址
	#define MS1022_SEND_ADDR_MASK						0x80
	//===读取ID信息
	#define MS1022_CMD_READ_ID							0xB7
	//===读取PWIST,脉冲宽度的测量比值
	#define MS1022_CMD_READ_PW1ST						0xB8
	//===读取状态寄存器器
	#define MS1022_CMD_READ_STATE						0xB4
	//===通信测试功能
	#define MS1022_CMD_COMM_TEST						0xB5
	//===初始化
	#define MS1022_CMD_INIT								0x70
	//===上电复位
	#define MS1022_CMD_POWER_ON_RESET					0x50
	//===开始时差测量
	#define MS1022_CMD_START_TOF						0x01
	//===开始时差测量
	#define MS1022_CMD_START_TEMP						0x02
	//===开始时钟校准
	#define MS1022_CMD_START_CAL_RESONATOR				0x03
	//===开始TDC校准校准
	#define MS1022_CMD_START_CAL_TDC					0x04
	//===重新启动时差测量
	#define MS1022_CMD_START_TOF_RESTART				0x05
	//===重新启动时差测量
	#define MS1022_CMD_START_TEMP_RESTART				0x06

	//===TDC测量单元溢出
	#define MS1022_STATE_TDC_TIME_OUT					(1<<9)
	//===测量范围2的14位粗值计数器溢出
	#define MS1022_STATE_PRECOUNTER_TIME_OUT			(1<<10)
	//===TDC测试单元MASK
	#define	MS1022_STATE_TDC_MASK						(3<<9)
	//===温度传感器开路
	#define MS1022_STATE_TEMPERATURE_OPEN				(1<<11)
	//===温度传感器短路
	#define MS1022_STATE_TEMPERATURE_SHORT				(1<<12)
	//===温度传感器MASK
	#define MS1022_STATE_TEMPERATURE_MASK				(3<<11)
	//===定义温度采样点个数
	#define MS1022_TEMPERATURE_SAMPLE_MAX_NUM			8
	//===定义飞行时间采样点个数
	#define MS1022_TOF_SAMPLE_MAX_NUM					24

	#define MS1022_REG_START_CAL_RESONATOR_MASK			0x00800000
	#define MS1022_REG_START_CAL_RESONATOR_VAL			0xFF0FFFFF

	#define MS1022_OFFSET_MV_P0							(0<<8)
	#define MS1022_OFFSET_MV_P1							(1<<8)
	#define MS1022_OFFSET_MV_P2							(2<<8)
	#define MS1022_OFFSET_MV_P3							(3<<8)
	#define MS1022_OFFSET_MV_P4							(4<<8)
	#define MS1022_OFFSET_MV_P5							(5<<8)
	#define MS1022_OFFSET_MV_P6							(6<<8)
	#define MS1022_OFFSET_MV_P7							(7<<8)
	#define MS1022_OFFSET_MV_P8							(8<<8)
	#define MS1022_OFFSET_MV_P9							(9<<8)
	#define MS1022_OFFSET_MV_P10						(10<<8)
	#define MS1022_OFFSET_MV_P11						(11<<8)
	#define MS1022_OFFSET_MV_P12						(12<<8)
	#define MS1022_OFFSET_MV_P13						(13<<8)
	#define MS1022_OFFSET_MV_P14						(14<<8)
	#define MS1022_OFFSET_MV_P15						(15<<8)
	#define MS1022_OFFSET_MV_N1							(31<<8)
	#define MS1022_OFFSET_MV_N2							(30<<8)
	#define MS1022_OFFSET_MV_N3							(29<<8)
	#define MS1022_OFFSET_MV_N4							(28<<8)
	#define MS1022_OFFSET_MV_N5							(27<<8)
	#define MS1022_OFFSET_MV_N6							(26<<8)
	#define MS1022_OFFSET_MV_N7							(25<<8)
	#define MS1022_OFFSET_MV_N8							(24<<8)
	#define MS1022_OFFSET_MV_N9							(23<<8)
	#define MS1022_OFFSET_MV_N10						(22<<8)
	#define MS1022_OFFSET_MV_N11						(21<<8)
	#define MS1022_OFFSET_MV_N12						(20<<8)
	#define MS1022_OFFSET_MV_N13						(19<<8)
	#define MS1022_OFFSET_MV_N14						(18<<8)
	#define MS1022_OFFSET_MV_N15						(17<<8)
	#define MS1022_OFFSET_MV_N16						(16<<8)

	//===定义换能器结构体
	typedef struct _MS1022_TRANSDUCER_HandleType		MS1022_TRANSDUCER_HandleType;
	//===定义换能器指针结构体
	typedef	struct _MS1022_TRANSDUCER_HandleType		*pMS1022_TRANSDUCER_HandleType;
	//===换能器结构定义
	struct _MS1022_TRANSDUCER_HandleType
	{
		uint16_t msg_type;						//---管段类型,DN15:0x15;DN20:0x20;DN25:0x25;DN32:0x32;DN40:0x40
		float msg_space_length;					//---间距长度m
		float msg_diameter;						//---管段直径
		float msg_flow_speed;					//---计算管道中的流速
		float msg_flow_volume;					//---计算体积流量
	};

	
	//===定义飞行时间结构体
	typedef struct _MS1022_TOF_HandleType		MS1022_TOF_HandleType;
	//===定义飞行时间指针结构体
	typedef	struct _MS1022_TOF_HandleType		*pMS1022_TOF_HandleType;
	//===飞行时间结构定义
	struct _MS1022_TOF_HandleType
	{
		uint16_t msg_state;					//---飞行时间测量状态
		float msg_up_time;					//---正向飞行时间
		float msg_down_time;				//---反向飞行时间
		float msg_diff_time;				//---飞行时间超
		float msg_time_factor;				//---时间系数
		float msg_up_rssi;					//---第一波模式计算时差的上游信号强度
		float msg_down_rssi;				//---第一波模式计算时差的上游信号强度
	};

	//===定义水温结构体
	typedef struct _MS1022_TEMPERATURE_HandleType		MS1022_TEMPERATURE_HandleType;
	//===定义水温指针结构体
	typedef	struct _MS1022_TEMPERATURE_HandleType		*pMS1022_TEMPERATURE_HandleType;
	//===水温结构定义
	struct _MS1022_TEMPERATURE_HandleType
	{
		uint8_t msg_state : 3;				//---水温测试状态	 0:正常;1:错误;2:开路;3:短路
		uint8_t msg_in_state : 2;			//---进水温度测试状态
		uint8_t	msg_out_state : 2;			//---出水温度测试状态
		uint8_t	msg_positive_mode : 1;		//---温差正负，0---正数；1---负数

		float msg_in_temp_factor;			//---进水口温度系数
		float msg_in_temp;					//---进水口温度[RED]
		float msg_out_temp_factor;			//---出水口温度系数
		float msg_out_temp;					//---出水口温度[BLUE]
		float msg_diff_temp;				//---进出水温差

		float msg_sound_speed;				//---超声波的速度m/s
	};

	//===定义结构体
	typedef struct _MS1022_HandleType					MS1022_HandleType;
	//===定义指针结构体
	typedef	struct _MS1022_HandleType					*pMS1022_HandleType;
	//===结构定义
//#pragma pack
	struct _MS1022_HandleType
	{
		SPI_HandleType  msg_spix;											//---使用的spi接口
		GPIO_HandleType	msg_gpio_rst;										//---MOSI

		MS1022_TEMPERATURE_HandleType msg_water_temperature;				//---水温定义
		MS1022_TOF_HandleType		  msg_water_tof;						//---飞行时间测量
		MS1022_TRANSDUCER_HandleType  msg_water_transducer;					//---换能器信息

		vltuint8_t msg_int_flag;											//---中断标识信息
		vltuint8_t msg_send_data_buffer[MS1022_DATA_BUFFER_MAX_SIZE];		//---发送数据缓存区
		vltuint8_t msg_read_data_buffer[MS1022_DATA_BUFFER_MAX_SIZE];		//---接收数据缓存区
		
		void(*msg_f_delay_ms)(uint32_t delay);								//---延时参数
		uint32_t(*msg_f_time_tick)(void);									//---用于超时计数
	};
//#pragma unpack

	//===使能32KHz的参考时钟
	#define MS1022_32KHZ_CLOCK_ENABLE()				rl78_pclbuz_start(0)
	//===不使能32KHz的参考时钟
	#define MS1022_32KHZ_CLOCK_DISABLE()			rl78_pclbuz_stop(0)

	#define MS1022_TASK_ONE							p_ms1022_one
	#define MS1022_TASK_TWO							0
	#define MS1022_TASK_THREE						0

	//===外部调用接口
	extern MS1022_HandleType						g_ms1022_one;
	extern pMS1022_HandleType						p_ms1022_one;
	
	//===函数定义
	uint8_t ms1022_spi_time_tick_init(MS1022_HandleType* MS1022x, uint32_t(*func_time_tick)(void));
	uint8_t ms1022_spi_init(MS1022_HandleType* MS1022x, void(*func_delay_us)(uint32_t us),
		void(*func_delay_ms)(uint32_t ms), uint32_t(*func_time_tick)(void), uint8_t is_hw);
	uint8_t ms1022_spi_rst(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_int_flag_set(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_int_flag_clear(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_int_flag_wait(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_mhw_it_irq_handle(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_read_reg(MS1022_HandleType* MS1022x, uint8_t index);
	uint8_t ms1022_spi_send_reg(MS1022_HandleType* MS1022x, uint8_t index, uint32_t val);
	uint8_t ms1022_spi_send_cmd(MS1022_HandleType* MS1022x, uint8_t cmd);
	uint16_t ms1022_spi_read_state(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_read_pw1st(MS1022_HandleType* MS1022x, uint8_t isup);
	uint8_t ms1022_spi_comm_test(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_config_init(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_read_start_temperature(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_read_start_temperature_restart(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_calibration_resonator(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_read_start_tof(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_read_start_tof_restart(MS1022_HandleType* MS1022x);

	uint8_t ms1022_spi_get_temperature(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_get_flow(MS1022_HandleType* MS1022x);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* MS1022_CFG_H_ */