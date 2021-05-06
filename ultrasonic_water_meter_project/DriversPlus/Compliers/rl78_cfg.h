#ifndef RL78_CFG_H_
#define RL78_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	
	#include "iodefine.h"
	#include "complier_lib.h"	
	#include "r_cg_macrodriver.h"
	#include "r_cg_userdefine.h"
	#include "r_cg_cgc.h"
	#include "r_cg_sau.h"	
	
#pragma region GPIO配置
	
	#define GPIO_TypeDef 										uint32_t	
	//===端口寄存器
#ifdef P0
	#define GPIOP0												&P0
#endif
#ifdef P1
	#define GPIOP1												&P1
#endif
#ifdef P2
	#define GPIOP2												&P2
#endif
#ifdef P3
	#define GPIOP3												&P3
#endif
#ifdef P4
	#define GPIOP4												&P4
#endif
#ifdef P5
	#define GPIOP5												&P5
#endif
#ifdef P6
	#define GPIOP6												&P6
#endif
#ifdef P7
	#define GPIOP7												&P7
#endif
#ifdef P8
	#define GPIOP8												&P8
#endif
#ifdef P9
	#define GPIOP9												&P9
#endif
#ifdef P10
	#define GPIOP10												&P10
#endif
#ifdef P11
	#define GPIOP11												&P11
#endif
#ifdef P12
	#define GPIOP12												&P12
#endif
#ifdef P13
	#define GPIOP13												&P13
#endif

	//===端口模式寄存器
#ifdef PM0
	#define GPIOPM0												&PM0
#endif
#ifdef PM1
	#define GPIOPM1												&PM1
#endif
#ifdef PM2
	#define GPIOPM2												&PM2
#endif
#ifdef PM3
	#define GPIOPM3												&PM3
#endif
#ifdef PM4
	#define GPIOPM4												&PM4
#endif
#ifdef PM5
	#define GPIOPM5												&PM5
#endif
#ifdef PM6
	#define GPIOPM6												&PM6
#endif
#ifdef PM7
	#define GPIOPM7												&PM7
#endif
#ifdef PM8
	#define GPIOPM8												&PM8
#endif
#ifdef PM9
	#define GPIOPM9												&PM9
#endif
#ifdef PM10
	#define GPIOPM10											&PM10
#endif
#ifdef PM11
	#define GPIOPM11											&PM11
#endif
#ifdef PM12
	#define GPIOPM12											&PM12
#endif
#ifdef PM13
	#define GPIOPM13											&PM13
#endif

	//===上拉电阻选择寄存器
#ifdef PU0
	#define GPIOPU0												&PU0
#endif
#ifdef PU1
	#define GPIOPU1												&PU1
#endif
#ifdef PU2
	#define GPIOPU2												&PU2
#endif
#ifdef PU3
	#define GPIOPU3												&PU3
#endif
#ifdef PU4
	#define GPIOPU4												&PU4
#endif
#ifdef PU5
	#define GPIOPU5												&PU5
#endif
#ifdef PU6
	#define GPIOPU6												&PU6
#endif
#ifdef PU7
	#define GPIOPU7												&PU7
#endif
#ifdef PU8
	#define GPIOPU8												&PU8
#endif
#ifdef PU9
	#define GPIOPU9												&PU9
#endif
#ifdef PU10
	#define GPIOPU10												&PU10
#endif
#ifdef PU11
	#define GPIOPU11												&PU11
#endif
#ifdef PU12
	#define GPIOPU12												&PU12
#endif
#ifdef PU13
	#define GPIOPU13												&PU13
#endif

	//===端口输入模式寄存器
#ifdef PIM0
	#define GPIOPIM0												&PIM0
#endif
#ifdef PIM1
	#define GPIOPIM1												&PIM1
#endif
#ifdef PIM2
	#define GPIOPIM2												&PIM2
#endif
#ifdef PIM3
	#define GPIOPIM3												&PIM3
#endif
#ifdef PIM4
	#define GPIOPIM4												&PIM4
#endif
#ifdef PIM5
	#define GPIOPIM5												&PIM5
#endif
#ifdef PIM6
	#define GPIOPIM6												&PIM6
#endif
#ifdef PIM7
	#define GPIOPIM7												&PIM7
#endif
#ifdef PIM8
	#define GPIOPIM8												&PIM8
#endif
#ifdef PIM9
	#define GPIOPIM9												&PIM9
#endif
#ifdef PIM10
	#define GPIOPIM10											&PIM10
#endif
#ifdef PIM11
	#define GPIOPIM11											&PIM11
#endif
#ifdef PIM12
	#define GPIOPIM12											&PIM12
#endif
#ifdef PIM13
	#define GPIOPIM13											&PIM13
#endif
	
	//===端口输出模式寄存器
#ifdef POM0
	#define GPIOPOM0												&POM0
#endif
#ifdef POM1
	#define GPIOPOM1												&POM1
#endif
#ifdef POM2
	#define GPIOPOM2												&POM2
#endif
#ifdef POM3
	#define GPIOPOM3												&POM3
#endif
#ifdef POM4
	#define GPIOPOM4												&POM4
#endif
#ifdef POM5
	#define GPIOPOM5												&POM5
#endif
#ifdef POM6
	#define GPIOPOM6												&POM6
#endif
#ifdef POM7
	#define GPIOPOM7												&POM7
#endif
#ifdef POM8
	#define GPIOPOM8												&POM8
#endif
#ifdef POM9
	#define GPIOPOM9												&POM9
#endif
#ifdef POM10
	#define GPIOPOM10											&POM10
#endif
#ifdef POM11
	#define GPIOPOM11											&POM11
#endif
#ifdef POM12
	#define GPIOPOM12											&POM12
#endif
#ifdef POM13
	#define GPIOPOM13											&POM13
#endif
	
	//===端口模式控制寄存器
#ifdef PMC0
	#define GPIOPMC0												&PMC0
#endif
#ifdef PMC1
	#define GPIOPMC1												&PMC1
#endif
#ifdef PMC2
	#define GPIOPMC2												&PMC2
#endif
#ifdef PMC3
	#define GPIOPMC3												&PMC3
#endif
#ifdef PMC4
	#define GPIOPMC4												&PMC4
#endif
#ifdef PMC5
	#define GPIOPMC5												&PMC5
#endif
#ifdef PMC6
	#define GPIOPMC6												&PMC6
#endif
#ifdef PMC7
	#define GPIOPMC7												&PMC7
#endif
#ifdef PMC8
	#define GPIOPMC8												&PMC8
#endif
#ifdef PMC9
	#define GPIOPMC9												&PMC9
#endif
#ifdef PMC10
	#define GPIOPMC10											&PMC10
#endif
#ifdef PMC11
	#define GPIOPMC11											&PMC11
#endif
#ifdef PMC12
	#define GPIOPMC12											&PMC12
#endif
#ifdef PMC13
	#define GPIOPMC13											&PMC13
#endif

	//===I/O端口重映射控制寄存器
#ifdef PIOR
	#define GPIOPIOR0											&PIOR
#endif

#ifdef PIOR0
	#define GPIOPIOR0											&PIOR0
#endif
#ifdef PIOR1
	#define GPIOPIOR1											&PIOR1
#endif
#ifdef PIOR2
	#define GPIOPIOR2											&PIOR2
#endif
#ifdef PIOR3
	#define GPIOPIOR3											&PIOR3
#endif
#ifdef PIOR4
	#define GPIOPIOR4											&PIOR4
#endif
#ifdef PIOR5
	#define GPIOPIOR5											&PIOR5
#endif
#ifdef PIOR6
	#define GPIOPIOR6											&PIOR6
#endif
#ifdef PIOR7
	#define GPIOPIOR7											&PIOR7
#endif
#ifdef PIOR8
	#define GPIOPIOR8											&PIOR8
#endif
#ifdef PIOR9
	#define GPIOPIOR9											&PIOR9
#endif
#ifdef PIOR10
	#define GPIOPIOR10											&PIOR10
#endif
#ifdef PIOR11
	#define GPIOPIOR11											&PIOR11
#endif
#ifdef PIOR12
	#define GPIOPIOR12											&PIOR12
#endif
#ifdef PIOR13
	#define GPIOPIOR13											&PIOR13
#endif

	
	#define GPIO_PIN_BIT_0										0x0001
	#define GPIO_PIN_BIT_1										0x0002
	#define GPIO_PIN_BIT_2										0x0004
	#define GPIO_PIN_BIT_3										0x0008
	#define GPIO_PIN_BIT_4										0x0010
	#define GPIO_PIN_BIT_5										0x0020
	#define GPIO_PIN_BIT_6										0x0040
	#define GPIO_PIN_BIT_7										0x0080
	#define GPIO_PIN_BIT_8										0x0100
	#define GPIO_PIN_BIT_9										0x0200
	#define GPIO_PIN_BIT_10										0x0400
	#define GPIO_PIN_BIT_11										0x0800
	#define GPIO_PIN_BIT_12										0x1000
	#define GPIO_PIN_BIT_13										0x2000
	#define GPIO_PIN_BIT_14										0x4000
	#define GPIO_PIN_BIT_15										0x8000
	#define GPIO_PIN_BIT_ALL									0xFF
	
#pragma endregion
	
	
	//===获取系统时钟的定义
	#define	SYS_CLOCK_HZ							( g_system_core_clock )
	#define	SYS_CLOCK_KHZ							( (SYS_CLOCK_HZ/1000U) )
	#define SYS_CLOCK_MHZ							( (SYS_CLOCK_HZ/1000000U) )
	#define SYS_CLOCK_ADD							( SYS_CLOCK_MHZ-20 )
	
	#include "wdt_task.h"	

	//===使能全局中断
	#define SEI()									EI()	
	//===禁止全局中断
	#define CLI()									DI()	
	//===喂狗
	#define WDT_RESET()								wdt_task_restart()
	//===软件复位
	#define SOFT_RESET()							asm("db 0xFF")
	//===系统重启
	#define SYS_REBOOT()							SOFT_RESET()

	//===外部定义
	extern volatile uint32_t g_system_core_clock;

	//===函数定义
	void rl78_init(uint8_t opt);
	void rl78_clock_init(void);
	void rl78_adc_clock(uint8_t enable);
	void rl78_i2c1_clock(uint8_t enable);
#ifdef IICA1EN
	void rl78_i2c2_clock(uint8_t enable);
#endif
	void rl78_sau1_clock(uint8_t enable);
	void rl78_sau2_clock(uint8_t enable);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* RL78_CFG_H_ */