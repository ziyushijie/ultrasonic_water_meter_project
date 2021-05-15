#ifndef AT24CXX_CFG_H_
#define AT24CXX_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	
	#include "complier_lib.h"
	#include "gpio_task.h"
	#include "delay_task.h"
	#include "i2c_task.h"
	#include "hw_config.h"

	//===֧�ֵ�ϵ���ͺ�
	#define AT24C01										0																//---16PX8B		---16ҳ��ÿҳ8�ֽ�
	#define AT24C02										1																//---32PX8B		---32ҳ��ÿҳ8�ֽ�
	#define AT24C04										2																//---32PX16B	---32ҳ��ÿҳ16�ֽ�
	#define AT24C08										3																//---64PX16B	---64ҳ��ÿҳ16�ֽ�
	#define AT24C16										4																//---128PX16B	---128ҳ��ÿҳ16�ֽ�
	#define AT24C32										5																//---128PX32B	---128ҳ��ÿҳ32�ֽ�
	#define AT24C64										6																//---256PX32B	---256ҳ��ÿҳ32�ֽ�
	#define AT24C128									7																//---256PX64B	---256ҳ��ÿҳ64�ֽ�
	#define AT24C256									8																//---512PX64B	---512ҳ��ÿҳ64�ֽ�
	#define AT24C512									9																//---512PX128B	---512ҳ��ÿҳ128�ֽ�
	//===����AT24Cxx��ÿҳֱ�����ֵ
	#define	AT24CXX_PAGE_BYTE_SIZE_MAX					128
	//===�豸ͨѶ��ַ
	#define AT24CXX_WADDR								0xA0															//---�豸��д��ַ
	#define AT24CXX_RADDR								0xA1															//---�豸�Ķ���ַ
	//===���ʱʱ�䣬���⿴�Ź���λ
	#define AT24CXX_WAIT_MAX_TIME						(800/AT24CXX_MIN_PULSE_WIDTH)
	//===�ຯ�����õ�ʱ�򣬲���״̬��ౣ����ʱ�䣬��λms
	#define AT24CXX_TASK_WAIT_MAX_TIME					(100/AT24CXX_MIN_PULSE_WIDTH)
	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////���ú궨��---����////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////�ṹ�嶨��---��ʼ//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	//===�ṹ�嶨��
	typedef struct _AT24CXX_HandleType					AT24CXX_HandleType;
	//===ָ��ṹ�嶨��
	typedef struct _AT24CXX_HandleType					*pAT24CXX_HandleType;
	//===AT24Cxx�����ݽṹ��
	struct _AT24CXX_HandleType
	{
		I2C_HandleType	msg_i2cx;																						//---ʹ�õ�I2C

		uint8_t		msg_type;																							//---ʹ�õ��豸
		uint8_t		msg_page_byte;																						//---ÿҳ�ֽ���
		uint16_t	msg_page_num;																						//---ҳ��
#ifndef AT24CXX_ENABLE_DRAM
		uint8_t		msg_page_byte_buffer[AT24CXX_PAGE_BYTE_SIZE_MAX + 1];												//---���建����
#else
		uint8_t		*msg_page_byte_buffer;																				//---ָ�򻺴�����ָ��
#endif
		void(*msg_f_delay_ms)(uint32_t delay);																			//---������ʱ����,��̽�������Ҫ�ȴ�5ms
	};

	//===�����������
	#define AT24CXX_TASK_ONE						p_at24cxx_one
	#define AT24CXX_TASK_TWO						0
	#define AT24CXX_TASK_THREE						0

	//===�ⲿ���ýӿ�
	extern AT24CXX_HandleType						g_at24cxx_one;
	extern pAT24CXX_HandleType						p_at24cxx_one;

	//===��������
	uint8_t at24cxx_i2c_init_one(AT24CXX_HandleType *AT24Cx);
	uint8_t at24cxx_i2c_init_two(AT24CXX_HandleType *AT24Cx);
	uint8_t at24cxx_i2c_init_three(AT24CXX_HandleType *AT24Cx);
	void at24cxx_i2c_time_tick_init(AT24CXX_HandleType* AT24Cx, uint32_t(*func_time_tick)(void));
	uint8_t at24cxx_i2c_init(AT24CXX_HandleType *AT24Cx,
		void(*func_delay_us)(uint32_t delay),
		void(*func_delay_ms)(uint32_t delay),
		uint32_t(*func_time_tick)(void), uint8_t is_hw_i2c);
	uint8_t at24cxx_i2c_deinit(AT24CXX_HandleType *AT24Cx);
	uint8_t at24cxx_sw_i2c_send_single_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t buffer);
	uint8_t at24cxx_sw_i2c_send_page_byte(AT24CXX_HandleType *AT24Cx, uint16_t page_addr, uint8_t *buffer, uint16_t length);
	uint8_t at24cxx_sw_i2c_read_single_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer);
	uint8_t at24cxx_sw_i2c_read_page_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer, uint16_t length);

	uint8_t at24cxx_i2c_send_single_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t buffer);
	uint8_t at24cxx_i2c_send_page_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer, uint16_t length);
	uint8_t at24cxx_i2c_send_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer, uint16_t length);
	uint8_t at24cxx_i2c_read_single_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer);
	uint8_t at24cxx_i2c_read_page_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer, uint16_t length);
	uint8_t at24cxx_i2c_read_byte(AT24CXX_HandleType *AT24Cx, uint16_t addr, uint8_t *buffer, uint16_t length);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* AT24CXX_CFG_H_ */