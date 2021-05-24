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

	//===���ȴ�ʱ��
	#define MS1022_WAIT_FLAG_MAX_TIME					(100/MS1022_MIN_PULSE_WIDTH)
	#define MS1022_WAIT_IDLE_MAX_TIME					(200/MS1022_MIN_PULSE_WIDTH)
	//===���ݻ�������С
	#define MS1022_DATA_BUFFER_MAX_SIZE					5

	//===����ַ
	#define MS1022_READ_ADDR_MASK						0xB0
	//===д��ַ
	#define MS1022_SEND_ADDR_MASK						0x80
	//===��ȡID��Ϣ
	#define MS1022_CMD_READ_ID							0xB7
	//===��ȡPWIST,�����ȵĲ�����ֵ
	#define MS1022_CMD_READ_PW1ST						0xB8
	//===��ȡ״̬�Ĵ�����
	#define MS1022_CMD_READ_STATE						0xB4
	//===ͨ�Ų��Թ���
	#define MS1022_CMD_COMM_TEST						0xB5
	//===��ʼ��
	#define MS1022_CMD_INIT								0x70
	//===�ϵ縴λ
	#define MS1022_CMD_POWER_ON_RESET					0x50
	//===��ʼʱ�����
	#define MS1022_CMD_START_TOF						0x01
	//===��ʼʱ�����
	#define MS1022_CMD_START_TEMP						0x02
	//===��ʼʱ��У׼
	#define MS1022_CMD_START_CAL_RESONATOR				0x03
	//===��ʼTDCУ׼У׼
	#define MS1022_CMD_START_CAL_TDC					0x04
	//===��������ʱ�����
	#define MS1022_CMD_START_TOF_RESTART				0x05
	//===��������ʱ�����
	#define MS1022_CMD_START_TEMP_RESTART				0x06

	//===TDC������Ԫ���
	#define MS1022_STATE_TDC_TIME_OUT					(1<<9)
	//===������Χ2��14λ��ֵ���������
	#define MS1022_STATE_PRECOUNTER_TIME_OUT			(1<<10)
	//===TDC���Ե�ԪMASK
	#define	MS1022_STATE_TDC_MASK						(3<<9)
	//===�¶ȴ�������·
	#define MS1022_STATE_TEMPERATURE_OPEN				(1<<11)
	//===�¶ȴ�������·
	#define MS1022_STATE_TEMPERATURE_SHORT				(1<<12)
	//===�¶ȴ�����MASK
	#define MS1022_STATE_TEMPERATURE_MASK				(3<<11)
	//===�����¶Ȳ��������
	#define MS1022_TEMPERATURE_SAMPLE_MAX_NUM			8
	//===�������ʱ����������
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

	//===���廻�����ṹ��
	typedef struct _MS1022_TRANSDUCER_HandleType		MS1022_TRANSDUCER_HandleType;
	//===���廻����ָ��ṹ��
	typedef	struct _MS1022_TRANSDUCER_HandleType		*pMS1022_TRANSDUCER_HandleType;
	//===�������ṹ����
	struct _MS1022_TRANSDUCER_HandleType
	{
		uint16_t msg_type;						//---�ܶ�����,DN15:0x15;DN20:0x20;DN25:0x25;DN32:0x32;DN40:0x40
		float msg_space_length;					//---��೤��m
		float msg_diameter;						//---�ܶ�ֱ��
		float msg_flow_speed;					//---����ܵ��е�����
		float msg_flow_volume;					//---�����������
	};

	
	//===�������ʱ��ṹ��
	typedef struct _MS1022_TOF_HandleType		MS1022_TOF_HandleType;
	//===�������ʱ��ָ��ṹ��
	typedef	struct _MS1022_TOF_HandleType		*pMS1022_TOF_HandleType;
	//===����ʱ��ṹ����
	struct _MS1022_TOF_HandleType
	{
		uint16_t msg_state;					//---����ʱ�����״̬
		float msg_up_time;					//---�������ʱ��
		float msg_down_time;				//---�������ʱ��
		float msg_diff_time;				//---����ʱ�䳬
		float msg_time_factor;				//---ʱ��ϵ��
		float msg_up_rssi;					//---��һ��ģʽ����ʱ��������ź�ǿ��
		float msg_down_rssi;				//---��һ��ģʽ����ʱ��������ź�ǿ��
	};

	//===����ˮ�½ṹ��
	typedef struct _MS1022_TEMPERATURE_HandleType		MS1022_TEMPERATURE_HandleType;
	//===����ˮ��ָ��ṹ��
	typedef	struct _MS1022_TEMPERATURE_HandleType		*pMS1022_TEMPERATURE_HandleType;
	//===ˮ�½ṹ����
	struct _MS1022_TEMPERATURE_HandleType
	{
		uint8_t msg_state : 3;				//---ˮ�²���״̬	 0:����;1:����;2:��·;3:��·
		uint8_t msg_in_state : 2;			//---��ˮ�¶Ȳ���״̬
		uint8_t	msg_out_state : 2;			//---��ˮ�¶Ȳ���״̬
		uint8_t	msg_positive_mode : 1;		//---�²�������0---������1---����

		float msg_in_temp_factor;			//---��ˮ���¶�ϵ��
		float msg_in_temp;					//---��ˮ���¶�[RED]
		float msg_out_temp_factor;			//---��ˮ���¶�ϵ��
		float msg_out_temp;					//---��ˮ���¶�[BLUE]
		float msg_diff_temp;				//---����ˮ�²�

		float msg_sound_speed;				//---���������ٶ�m/s
	};

	//===����ṹ��
	typedef struct _MS1022_HandleType					MS1022_HandleType;
	//===����ָ��ṹ��
	typedef	struct _MS1022_HandleType					*pMS1022_HandleType;
	//===�ṹ����
//#pragma pack
	struct _MS1022_HandleType
	{
		SPI_HandleType  msg_spix;											//---ʹ�õ�spi�ӿ�
		GPIO_HandleType	msg_gpio_rst;										//---MOSI

		MS1022_TEMPERATURE_HandleType msg_water_temperature;				//---ˮ�¶���
		MS1022_TOF_HandleType		  msg_water_tof;						//---����ʱ�����
		MS1022_TRANSDUCER_HandleType  msg_water_transducer;					//---��������Ϣ

		vltuint8_t msg_int_flag;											//---�жϱ�ʶ��Ϣ
		vltuint8_t msg_send_data_buffer[MS1022_DATA_BUFFER_MAX_SIZE];		//---�������ݻ�����
		vltuint8_t msg_read_data_buffer[MS1022_DATA_BUFFER_MAX_SIZE];		//---�������ݻ�����
		
		void(*msg_f_delay_ms)(uint32_t delay);								//---��ʱ����
		uint32_t(*msg_f_time_tick)(void);									//---���ڳ�ʱ����
	};
//#pragma unpack

	//===ʹ��32KHz�Ĳο�ʱ��
	#define MS1022_32KHZ_CLOCK_ENABLE()				rl78_pclbuz_start(0)
	//===��ʹ��32KHz�Ĳο�ʱ��
	#define MS1022_32KHZ_CLOCK_DISABLE()			rl78_pclbuz_stop(0)

	#define MS1022_TASK_ONE							p_ms1022_one
	#define MS1022_TASK_TWO							0
	#define MS1022_TASK_THREE						0

	//===�ⲿ���ýӿ�
	extern MS1022_HandleType						g_ms1022_one;
	extern pMS1022_HandleType						p_ms1022_one;
	
	//===��������
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