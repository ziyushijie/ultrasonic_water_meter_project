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
		float msg_rssi;						//---��һ��ģʽ����ʱ����ź�ǿ��
	};

	//===����ˮ�½ṹ��
	typedef struct _MS1022_TEMPERATURE_HandleType		MS1022_TEMPERATURE_HandleType;
	//===����ˮ��ָ��ṹ��
	typedef	struct _MS1022_TEMPERATURE_HandleType		*pMS1022_TEMPERATURE_HandleType;
	//===ˮ�½ṹ����
	struct _MS1022_TEMPERATURE_HandleType
	{
		uint8_t msg_state : 2;				//---ˮ�²���״̬
		uint8_t msg_in_state : 3;			//---��ˮ�¶Ȳ���״̬
		uint8_t	msg_out_state : 3;			//---��ˮ�¶Ȳ���״̬
		uint8_t	msg_positive_mode : 2;		//---�²�������0---������1---����

		float msg_in_temp_factor;			//---��ˮ���¶�ϵ��
		float msg_in_temp;					//---��ˮ���¶�[RED]
		float msg_out_temp_factor;			//---��ˮ���¶�ϵ��
		float msg_out_temp;					//---��ˮ���¶�[BLUE]
		float msg_diff_temp;				//---����ˮ�²�
	};

	//===����ṹ��
	typedef struct _MS1022_HandleType					MS1022_HandleType;
	//===����ָ��ṹ��
	typedef	struct _MS1022_HandleType					*pMS1022_HandleType;
	//===�ṹ����
//#pragma pack
	struct _MS1022_HandleType
	{
		SPI_HandleType  msg_spix;																						//---ʹ�õ�spi�ӿ�
		GPIO_HandleType	msg_gpio_rst;																					//---MOSI

		MS1022_TEMPERATURE_HandleType msg_water_temperature;															//---ˮ�¶���
		MS1022_TOF_HandleType		  msg_water_tof;																	//---����ʱ�����

		vltuint8_t msg_int_flag;																						//---�жϱ�ʶ��Ϣ
		vltuint8_t msg_send_data_buffer[MS1022_DATA_BUFFER_MAX_SIZE];													//---�������ݻ�����
		vltuint8_t msg_read_data_buffer[MS1022_DATA_BUFFER_MAX_SIZE];													//---�������ݻ�����
		
		void(*msg_f_delay_ms)(uint32_t delay);																			//---��ʱ����
		uint32_t(*msg_f_time_tick)(void);																				//---���ڳ�ʱ����
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
	uint8_t ms1022_spi_read_reg_state(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_read_reg_pw1st(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_comm_test(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_config_init(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_read_temperature(MS1022_HandleType* MS1022x);
	uint8_t ms1022_spi_calibration_resonator(MS1022_HandleType* MS1022x);


	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* MS1022_CFG_H_ */