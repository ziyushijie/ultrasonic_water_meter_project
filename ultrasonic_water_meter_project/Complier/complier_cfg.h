#ifndef COMPLIER_CFG_H_
#define COMPLIER_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	//===定义使用的头文件
	#include "stdbool.h"
	#include "stddef.h"
	#include "stdlib.h"
	#include "stdio.h"
	#include "string.h"
	#include "math.h"
	#include "stdarg.h"
	#include "stdint.h"

	//#define TYPDEF_UINT8_T
	#define TYPDEF_U8
	#define TYPDEF_UCHAR
	#define TYPDEF_VLTUINT8_T
	#define TYPDEF_VLTU8
	#define TYPDEF_VLTUCHAR

	//#define TYPDEF_INT8_T
	#define TYPDEF_S8
	#define TYPDEF_VLTINT8_T
	#define TYPDEF_VLTS8

	//#define TYPDEF_UINT16_T
	#define TYPDEF_U16
	#define TYPDEF_VLTUINT16_T
	#define TYPDEF_VLTU16

	//#define TYPDEF_INT16_T
	#define TYPDEF_S16
	#define TYPDEF_VLTINT16_T
	#define TYPDEF_VLTS16

	//#define TYPDEF_UINT32_T
	#define TYPDEF_U32
	#define TYPDEF_VLTUINT32_T
	#define TYPDEF_VLTU32

	//#define TYPDEF_INT32_T
	#define TYPDEF_S32
	#define TYPDEF_VLTINT32_T
	#define TYPDEF_VLTS32

	//#define TYPDEF_UINT64_T
	#define TYPDEF_U64
	#define TYPDEF_VLTUINT64_T
	#define TYPDEF_VLTU64

	//#define TYPDEF_INT64_T
	#define TYPDEF_S64
	#define TYPDEF_VLTINT64_T
	#define TYPDEF_VLTS64

	//===无符号的8位数据
#if !defined(uint8_t)&&defined(TYPDEF_UINT8_T)
	typedef	unsigned char						uint8_t;
#endif
#if !defined(u8)&&defined(TYPDEF_U8)
	typedef	unsigned char						u8;
#endif
#if !defined(uchar)&&defined(TYPDEF_UCHAR)
	typedef	unsigned char						uchar;
#endif
	//===volatile无符号的8位数据
#if !defined(vltuint8_t)&&defined(TYPDEF_VLTUINT8_T)
	typedef	volatile unsigned char				vltuint8_t;
#endif
#if !defined(vltu8)&&defined(TYPDEF_VLTU8)
	typedef	volatile unsigned char				vltu8;
#endif
#if !defined(vltuchar)&&defined(TYPDEF_VLTUCHAR)
	typedef	volatile unsigned char				vltuchar;
#endif
	//===有符号的8位数据
#if !defined(int8_t)&&defined(TYPDEF_INT8_T)
	typedef signed	 char						int8_t;
#endif
#if !defined(s8)&&defined(TYPDEF_S8)
	typedef	signed  char						s8;
#endif
	//===volatile无符号的8位数据
#if !defined(vltint8_t)&&defined(TYPDEF_VLTINT8_T)
	typedef	volatile signed  char				vltint8_t;
#endif
#if !defined(vlts8)&&defined(TYPDEF_VLTS8)
	typedef	volatile signed  char				vlts8;
#endif
#ifndef SIZE_MAX
	#define  SIZE_MAX							0xFFFF
#endif
	//===兼容不同位数的单片机
#if (SIZE_MAX==0xFFFF)	
	//===无符号的16位数据
#if !defined(uint16_t)&&defined(TYPDEF_UINT16_T)
	typedef	unsigned  int						uint16_t;
#endif	
#if !defined(u16)&&defined(TYPDEF_U16)
	typedef	unsigned  int						u16;
#endif		
#if !defined(vltuint16_t)&&defined(TYPDEF_VLTUINT16_T)
	typedef	volatile unsigned  int				vltuint16_t;
#endif
#if !defined(vltu16)&&defined(TYPDEF_VLTU16)
	typedef	volatile unsigned  int				vltu16;
#endif	
	//===有符号的16位数据
#if !defined(int16_t)&&defined(TYPDEF_INT16_T)
	typedef	signed  int							int16_t;
#endif
#if !defined(s16)&&defined(TYPDEF_S16)
	typedef	signed  int							s16;
#endif		
#if !defined(vltint16_t)&&defined(TYPDEF_VLTINT16_T)
	typedef	volatile signed  int				vltint16_t;
#endif
#if !defined(vlts16)&&defined(TYPDEF_VLTS16)
	typedef	volatile signed  int				vlts16;
#endif	

#else

#if !defined(uint16_t)&&defined(TYPDEF_UINT16_T)
	typedef	unsigned short int					uint16_t;
#endif	
#if !defined(u16)&&defined(TYPDEF_U16)
	typedef	unsigned short int					u16;
#endif
#if !defined(vltuint16_t)&&defined(TYPDEF_VLTUINT16_T)
	typedef	volatile unsigned short int			vltuint16_t;
#endif
#if !defined(vltu16)&&defined(TYPDEF_VLTU16)
	typedef	volatile unsigned short int			vltu16;
#endif	
	//===有符号的16位数据
#if !defined(int16_t)&&defined(TYPDEF_INT16_T)
	typedef	signed short int					int16_t;
#endif
#if !defined(s16)&&defined(TYPDEF_S16)
	typedef	signed short int					s16;
#endif		
#if !defined(vltint16_t)&&defined(TYPDEF_VLTINT16_T)
	typedef	volatile signed short int			vltint16_t;
#endif
#if !defined(s16)&&defined(TYPDEF_VLTS16)
	typedef	volatile signed short int			vlts16;
#endif	

#endif	
	//===兼容不同位数的单片机
#if (SIZE_MAX==0xFFFF)	
	//---无符号的32位数据
#if !defined(uint32_t)&&defined(TYPDEF_UINT32_T)
	typedef	unsigned long int					uint32_t;
#endif
#if !defined(u32)&&defined(TYPDEF_U32)
	typedef	unsigned long int					u32;
#endif		
#if !defined(vltuint32_t)&&defined(TYPDEF_VLTUINT32_T)
	typedef	volatile unsigned long int			vltuint32_t;
#endif
#if !defined(vltu32)&&defined(TYPDEF_VLTU32)
	typedef	volatile unsigned long	int			vltu32;
#endif	
	//===有符号的32位数据
#if !defined(int32_t)&&defined(TYPDEF_INT32_T)
	typedef	signed	long int					int32_t;
#endif
#if !defined(s32)&&defined(TYPDEF_S32)
	typedef	signed	long int					s32;
#endif
#if !defined(vltint32_t)&&defined(TYPDEF_VLTINT32_T)
	typedef	volatile signed	long int			vltint32_t;
#endif
#if !defined(s32)&&defined(TYPDEF_VLTS32)
	typedef	volatile signed	long int			vlts32;
#endif	

#else	

	//===无符号的32位数据
#if !defined(uint32_t)&&defined(TYPDEF_UINT32_T)
	typedef	 unsigned  int						uint32_t;
#endif
#if !defined(u32)&&defined(TYPDEF_U32)
	typedef	unsigned  int						u32;
#endif		
#if !defined(vltuint32_t)&&defined(TYPDEF_VLTUINT32_T)
	typedef	volatile unsigned  int				vltuint32_t;
#endif
#if !defined(vltu32)&&defined(TYPDEF_VLTU32)
	typedef	volatile unsigned  int				vltu32;
#endif		
	//===有符号的32位数据
#if !defined(int32_t)&&defined(TYPDEF_INT32_T)
	typedef	signed int							int32_t;
#endif
#if !defined(s32)&&defined(TYPDEF_S32)
	typedef	signed int							s32;
#endif
#if !defined(vltint32_t)&&defined(TYPDEF_VLTINT32_T)
	typedef	volatile signed	int					vltint32_t;
#endif
#if !defined(s32)&&defined(TYPDEF_VLTS32)
	typedef	volatile signed	int					vlts32;
#endif	

#endif

	//===无符号的64位数据
#if !defined(uint64_t)&&defined(TYPDEF_UINT64_T)
	typedef	unsigned long long int				uint64_t;
#endif
#if !defined(u64)&&defined(TYPDEF_U64)
	typedef	unsigned long long int				u64;
#endif
#if !defined(vltuint64_t)&&defined(TYPDEF_VLTUINT64_T)
	typedef	volatile unsigned long long int		vltuint64_t;
#endif
#if !defined(vltu64)&&defined(TYPDEF_VLTU64)
	typedef	volatile unsigned long long int		vltu64;
#endif
	//===有符号的64位数据
#if !defined(int64_t)&&defined(TYPDEF_INT64_T)
	typedef	signed long long int				int64_t;
#endif
#if !defined(s64)&&defined(TYPDEF_S64)
	typedef signed long long int				s64;
#endif	
#if !defined(vltint64_t)&&defined(TYPDEF_VLTINT64_T)
	typedef	volatile signed long long int		vltint64_t;
#endif
#if !defined(s64)&&defined(TYPDEF_VLTS64)
	typedef	volatile signed long long int		vlts64;
#endif
	//===8bit无符号的联合体
	typedef union
	{
		struct
		{
			uint8_t b0 : 1;
			uint8_t b1 : 1;
			uint8_t b2 : 1;
			uint8_t b3 : 1;
			uint8_t b4 : 1;
			uint8_t b5 : 1;
			uint8_t b6 : 1;
			uint8_t b7 : 1;
		}bit;
		uint8_t bits;
	}union_uint8_t;

	//===8bit无符号的联合体,每4bits一组
	typedef union
	{
		struct
		{
			uint8_t b0_3 : 4;
			uint8_t b4_7 : 4;
		}bit;
		uint8_t bits;
	}union_uint8_t_4bits;

	//===8bit无符号的联合体,每2bits一组
	typedef union
	{
		struct
		{
			uint8_t b0_1 : 2;
			uint8_t b2_3 : 2;
			uint8_t b4_5 : 2;
			uint8_t b6_7 : 2;
		}bit;
		uint8_t bits;
	}union_uint8_t_2bits;

	//===8bit有符号的联合体
	typedef union
	{
		struct
		{
			uint8_t b0 : 1;
			uint8_t b1 : 1;
			uint8_t b2 : 1;
			uint8_t b3 : 1;
			uint8_t b4 : 1;
			uint8_t b5 : 1;
			uint8_t b6 : 1;
			uint8_t b7 : 1;
		}bit;
		int8_t bits;
	}union_int8_t;

	//===8bit有符号的联合体,每4bits一组
	typedef union
	{
		struct
		{
			uint8_t b0_3 : 4;
			uint8_t b4_7 : 4;
		}bit;
		int8_t bits;
	}union_int8_t_4bits;

	//===8bit有符号的联合体,每2bits一组
	typedef union
	{
		struct
		{
			uint8_t b0_1 : 2;
			uint8_t b2_3 : 2;
			uint8_t b4_5 : 2;
			uint8_t b6_7 : 2;
		}bit;
		int8_t bits;
	}union_int8_t_2bits;

	//===16bit无符号的联合体
	typedef union
	{
		struct
		{
			uint8_t b0 : 1;
			uint8_t b1 : 1;
			uint8_t b2 : 1;
			uint8_t b3 : 1;
			uint8_t b4 : 1;
			uint8_t b5 : 1;
			uint8_t b6 : 1;
			uint8_t b7 : 1;
			uint8_t b8 : 1;
			uint8_t b9 : 1;
			uint8_t b10 : 1;
			uint8_t b11 : 1;
			uint8_t b12 : 1;
			uint8_t b13 : 1;
			uint8_t b14 : 1;
			uint8_t b15 : 1;
		}bit;
		uint8_t  bits[2];
		uint16_t w_bits;
	}union_uint16_t;

	//===16bit无符号的联合体,每4bit一组
	typedef union
	{
		struct
		{
			uint8_t b0_3 : 4;
			uint8_t b4_7 : 4;
			uint8_t b8_11 : 4;
			uint8_t b12_15 : 4;
		}bit;
		uint8_t  bits[2];
		uint16_t w_bits;
	}union_uint16_t_4bits;

	//===16bit无符号的联合体,每2bit一组
	typedef union
	{
		struct
		{
			uint8_t b0_1 : 2;
			uint8_t b2_3 : 2;
			uint8_t b4_5 : 2;
			uint8_t b6_7 : 2;
			uint8_t b8_9 : 2;
			uint8_t b10_11 : 2;
			uint8_t b12_13 : 2;
			uint8_t b14_15 : 2;
		}bit;
		uint8_t  bits[2];
		uint16_t w_bits;
	}union_uint16_t_2bits;

	//===16bit有符号的联合体
	typedef union
	{
		struct
		{
			uint8_t b0 : 1;
			uint8_t b1 : 1;
			uint8_t b2 : 1;
			uint8_t b3 : 1;
			uint8_t b4 : 1;
			uint8_t b5 : 1;
			uint8_t b6 : 1;
			uint8_t b7 : 1;
			uint8_t b8 : 1;
			uint8_t b9 : 1;
			uint8_t b10 : 1;
			uint8_t b11 : 1;
			uint8_t b12 : 1;
			uint8_t b13 : 1;
			uint8_t b14 : 1;
			uint8_t b15 : 1;
		}bit;
		int8_t  bits[2];
		int16_t w_bits;
	}union_int16_t;

	//===16bit有符号的联合体,每4bit一组
	typedef union
	{
		struct
		{
			uint8_t b0_3 : 4;
			uint8_t b4_7 : 4;
			uint8_t b8_11 : 4;
			uint8_t b12_15 : 4;
		}bit;
		int8_t  bits[2];
		int16_t w_bits;
	}union_int16_t_4bits;

	//===16bit有符号的联合体,每2bit一组
	typedef union
	{
		struct
		{
			uint8_t b0_1 : 2;
			uint8_t b2_3 : 2;
			uint8_t b4_5 : 2;
			uint8_t b6_7 : 2;
			uint8_t b8_9 : 2;
			uint8_t b10_11 : 2;
			uint8_t b12_13 : 2;
			uint8_t b14_15 : 2;
		}bit;
		int8_t  bits[2];
		int16_t w_bits;
	}union_int16_t_2bits;

	//===32bit无符号的联合体
	typedef union
	{
		struct
		{
			uint8_t b0 : 1;
			uint8_t b1 : 1;
			uint8_t b2 : 1;
			uint8_t b3 : 1;
			uint8_t b4 : 1;
			uint8_t b5 : 1;
			uint8_t b6 : 1;
			uint8_t b7 : 1;
			uint8_t b8 : 1;
			uint8_t b9 : 1;
			uint8_t b10 : 1;
			uint8_t b11 : 1;
			uint8_t b12 : 1;
			uint8_t b13 : 1;
			uint8_t b14 : 1;
			uint8_t b15 : 1;
			uint8_t b16 : 1;
			uint8_t b17 : 1;
			uint8_t b18 : 1;
			uint8_t b19 : 1;
			uint8_t b20 : 1;
			uint8_t b21 : 1;
			uint8_t b22 : 1;
			uint8_t b23 : 1;
			uint8_t b24 : 1;
			uint8_t b25 : 1;
			uint8_t b26 : 1;
			uint8_t b27 : 1;
			uint8_t b28 : 1;
			uint8_t b29 : 1;
			uint8_t b30 : 1;
			uint8_t b31 : 1;
		}bit;
		uint8_t  bits[4];
		uint16_t w_bits[2];
		uint32_t dw_bits;
	}union_uint32_t;

	//===32bit无符号的联合体,每4bits一组
	typedef union
	{
		struct
		{
			uint8_t b0_3 : 4;
			uint8_t b4_7 : 4;
			uint8_t b8_11  : 4;
			uint8_t b12_15 : 4;
			uint8_t b16_19 : 4;
			uint8_t b20_23 : 4;
			uint8_t b24_27 : 4;
			uint8_t b28_31 : 4;
		}bit;
		uint8_t  bits[4];
		uint16_t w_bits[2];
		uint32_t dw_bits;
	}union_uint32_t_4bits;

	//===32bit无符号的联合体,每2bits一组
	typedef union
	{
		struct
		{
			uint8_t b0_1 : 2;
			uint8_t b2_3 : 2;
			uint8_t b4_5 : 2;
			uint8_t b6_7 : 2;
			uint8_t b8_9 : 2;
			uint8_t b10_11 : 2;
			uint8_t b12_13 : 2;
			uint8_t b14_15 : 2;
			uint8_t b16_17 : 2;
			uint8_t b18_19 : 2;
			uint8_t b20_21 : 2;
			uint8_t b22_23 : 2;
			uint8_t b24_25 : 2;
			uint8_t b26_27 : 2;
			uint8_t b28_29 : 2;
			uint8_t b30_31 : 2;
		}bit;
		uint8_t  bits[4];
		uint16_t w_bits[2];
		uint32_t dw_bits;
	}union_uint32_t_2bits;

	//===32bit有符号的联合体
	typedef union
	{
		struct
		{
			uint8_t b0 : 1;
			uint8_t b1 : 1;
			uint8_t b2 : 1;
			uint8_t b3 : 1;
			uint8_t b4 : 1;
			uint8_t b5 : 1;
			uint8_t b6 : 1;
			uint8_t b7 : 1;
			uint8_t b8 : 1;
			uint8_t b9 : 1;
			uint8_t b10 : 1;
			uint8_t b11 : 1;
			uint8_t b12 : 1;
			uint8_t b13 : 1;
			uint8_t b14 : 1;
			uint8_t b15 : 1;
			uint8_t b16 : 1;
			uint8_t b17 : 1;
			uint8_t b18 : 1;
			uint8_t b19 : 1;
			uint8_t b20 : 1;
			uint8_t b21 : 1;
			uint8_t b22 : 1;
			uint8_t b23 : 1;
			uint8_t b24 : 1;
			uint8_t b25 : 1;
			uint8_t b26 : 1;
			uint8_t b27 : 1;
			uint8_t b28 : 1;
			uint8_t b29 : 1;
			uint8_t b30 : 1;
			uint8_t b31 : 1;
		}bit;
		int8_t  bits[4];
		int16_t w_bits[2];
		int32_t dw_bits;
	}union_int32_t;

	//===32bit有符号的联合体,每4bit一组
	typedef union
	{
		struct
		{
			uint8_t b0_3 : 4;
			uint8_t b4_7 : 4;
			uint8_t b8_11 : 4;
			uint8_t b12_15 : 4;
			uint8_t b16_19 : 4;
			uint8_t b20_23 : 4;
			uint8_t b24_27 : 4;
			uint8_t b28_31 : 4;
		}bit;
		int8_t  bits[4];
		int16_t w_bits[2];
		int32_t dw_bits;
	}union_int32_t_4bits;

	//===32bit有符号的联合体,每2bits一组
	typedef union
	{
		struct
		{
			uint8_t b0_1 : 2;
			uint8_t b2_3 : 2;
			uint8_t b4_5 : 2;
			uint8_t b6_7 : 2;
			uint8_t b8_9 : 2;
			uint8_t b10_11 : 2;
			uint8_t b12_13 : 2;
			uint8_t b14_15 : 2;
			uint8_t b16_17 : 2;
			uint8_t b18_19 : 2;
			uint8_t b20_21 : 2;
			uint8_t b22_23 : 2;
			uint8_t b24_25 : 2;
			uint8_t b26_27 : 2;
			uint8_t b28_29 : 2;
			uint8_t b30_31 : 2;
		}bit;
		int8_t  bits[4];
		int16_t w_bits[2];
		int32_t dw_bits;
	}union_int32_t_2bits;

	//===常用错误枚举
	typedef enum
	{
		OK_0 = 0,
		ERROR_1 = 1,
		ERROR_2 = 2,
		ERROR_3 = 3,
		ERROR_4 = 4,
		ERROR_5 = 5,
		ERROR_6 = 6,
		ERROR_7 = 7,
		ERROR_8 = 8,
		ERROR_9 = 9,
		ERROR_10 = 10,
		ERROR_11 = 11,
		ERROR_12 = 12,
		ERROR_13 = 13,
		ERROR_14 = 14,
		ERROR_15 = 15,
		ERROR_16 = 16,
		ERROR_17 = 17,
		ERROR_18 = 18,
		ERROR_19 = 19,
		ERROR_20 = 20,
		ERROR_21 = 21,
		ERROR_22 = 22,
		ERROR_23 = 23,
		ERROR_24 = 24,
		ERROR_25 = 25,
		ERROR_26 = 26,
		ERROR_27 = 27,
		ERROR_28 = 28,
		ERROR_29 = 29,
		ERROR_30 = 30,
		ERROR_31 = 31,
		ERROR_32 = 32,
		ERROR_33 = 33,
		ERROR_34 = 34,
		ERROR_35 = 35,
		ERROR_36 = 36,
		ERROR_37 = 37,
		ERROR_38 = 38,
		ERROR_39 = 39,
		ERROR_40 = 40,
		ERROR_41 = 41,
		ERROR_42 = 42,
		ERROR_43 = 43,
		ERROR_44 = 44,
		ERROR_45 = 45,
		ERROR_46 = 46,
		ERROR_47 = 47,
		ERROR_48 = 48,
		ERROR_49 = 49,
		ERROR_50 = 50,
		ERROR_FF = 0xFF,
	}FuncSTATE;

	#define ZXINT_TBZM_KEY_PRESS_ACTIVE_LEVEL_LOW			0															//---按键低电平有效
	#define ZXINT_TBZM_KEY_PRESS_ACTIVE_LEVEL_HIGH			1															//---按键高电平有效

	//===激活电平
	typedef enum
	{
		ACTIVE_LEVEL_LOW=0,				//---低电平激活
		ACTIVE_LEVEL_HIGH=1,			//---高电平激活
		ACTIVE_LEVEL_RISING_EDGE,		//---上升沿激活---不支持
		ACTIVE_LEVEL_FALLING_EDGE		//---下降沿激活---不支持
	}ACTIVE_LEVEL;

	//===结构体定义
	typedef struct _Record_DataType					Record_DataType;
	//===定义指针结构体
	typedef struct _Record_DataType					* pRecord_DataType;
	//---记录值得数据结果
	struct _Record_DataType
	{
		uint32_t msg_old_val;																							//---上一次的值
		uint32_t msg_now_val;																							//---本次的值
	};
	
	//===结构体定义
	typedef struct _RTC_TimeType					RTC_TimeType;
	//===定义指针结构体
	typedef struct _RTC_TimeType					* pRTC_TimeType;
	//===时钟结构体的定义
	struct _RTC_TimeType
	{
		uint8_t msg_second;																								//---秒
		uint8_t msg_minute;																								//---分
		uint8_t msg_hour;																								//---时
		uint8_t msg_day;																								//---天
		uint8_t msg_week;																								//---星期
		uint8_t msg_month;																								//---月
		uint8_t msg_year;																								//---年
		uint8_t msg_century;																							//---世纪
		uint8_t msg_format_24h;																							//---格式,0---12H;1---24H
		uint8_t	msg_day_zero;																							//---零点变化,0---未变化;1---变化
		uint16_t msg_years;																								//---具体哪一年 比如21世纪20年，就是2020年
		uint32_t msg_second_tick;																						//---秒变化的记录
	};
	
	//===常用宏定义
	typedef enum
	{
		IDLE = 0,
		BUSY = 1,
		ERROR
	}WORK_STATE;
	//===定义bool变量
#ifndef bool
#if !defined(true)&&!defined(false)
	typedef enum
	{
		true = 0,
		false
	}bool;
#endif
#endif	

	//===小端对其
	#define LITTLE_ENDIAN_FORCE																							//---将低序字节存储在起始地址
	//===大端对其
	//#define BIG_ENDIAN_FORCE																							//---将高序字节存储在起始地址
	
	//===数据基本操作
	#define PI										3.1415926F															//---三角函数π的值
	#define MAX(a,b)								( (a) > (b) ? (a) : (b) )											//---取最大值
	//#define MIN(a,b)								( (a) < (b) ? (a) : (b) )											//---取最小值
	#define ODD(x)									((x&0x01)==1?1:0)													//---校验是不是奇数
	#define EVEN(x)									((x&0x01)!=1?1:0)													//---校验是不是偶数
	#define ABS(a)									( (a)>=0?(a):-(a) )													//---数的绝对值
	#define RANGE(x, a, b)							( MIN( MAX( x, a ), b ) )											//---取三个数中的最小值
	#define ABS_SUB(a,b)							( (a)>(b)?((a)-(b)):((b)-(a)) )										//---两个数的绝对值差
	#define SWAP_16BITS(val)						( ((val&0x00FF)<<8)|((val&0xFF00)>>8) )
	#define SWAP_32BITS(val)						(((val&0x000000FF)<<24)|((val&0x0000FF00)<<8)| \
													 ((val&0x00FF0000)>>8)|((val&0xFF000000)>>24))

	//===根据直径计算圆的面积
	#define CIRCLE_AREA(d)							(PI*d*d/4.0f)						

	#define	VERSION_DATE_SIZE						12																	//---利用__DATE__获取当前日期，占用12个字节，包括字符串结束符
	#define VERSION_TIME_SIZE						9																	//---利用__TIME__获取当前时间，占用9个字节，包括字符串结束符	
	#define YEAR_TYPE(a)							( ((a%100!=0)&&(a%4==0))||(a%400==0) )								//---判断是否是闰年
	#define LOW_LEVEL								0																	//---低电平
	#define HIGH_LEVEL								1																	//---高电平
	#define TIME_SPAN(new_val,old_val)				((new_val<old_val)?(0xFFFFFFFF-old_val+new_val):(new_val-old_val))	//---计算差值，主要是通过滴答定时器实现的值
#ifndef _forceinline
	#define _forceinline							inline
#endif
	//////////////////////////////////////////////////////////////////////////
	//===依据MCU的型号不同，选择不同的头文件，暂时支持STM32和AVR
#if defined(MCU_USE_STM32F0)|| \
	defined(MCU_USE_STM32F1)|| \
	defined(MCU_USE_STM32F2)|| \
	defined(MCU_USE_STM32F3)|| \
	defined(MCU_USE_STM32F4)
	//===选择STM32型号
	#define MCU_USE_STM32	
#elif defined(MCU_USE_RL78_R7F0)
	//===选择STM32型号
	#define MCU_USE_RL78
	//#warning 支持RL78系列!
#else
	#error "型号:不支持型号的MCU,只支持STM32F0，F1，F2，F3，F4系列!"
#endif	
	//////////////////////////////////////////////////////////////////////////
	//===依据MCU型号，包含不同的头文件
#if defined(MCU_USE_STM32)
	#include "stm32_cfg.h"
#elif defined(MCU_USE_RL78)
	#include "rl78_cfg.h"
#else
	#error "系列:不支持型号的MCU,只支持STM32F0，F1，F2，F3，F4系列!"
#endif 	
	//===通过编译时间，用于实现版本区分
	#define ENABE_VERSION_DATA_TIME_LOG																				//---使用编译器实现的版本
	//===编译的时间和日期信息
#ifdef ENABE_VERSION_DATA_TIME_LOG
	//===外部调用接口
#if defined(MCU_USE_STM32)
	extern	const uint8_t  g_version_date[VERSION_DATE_SIZE] ;
	extern	const uint8_t  g_version_time[VERSION_TIME_SIZE] ;
#elif defined(MCU_USE_AVR)
	extern	PRO_FLASH_uint8_t  g_version_date[VERSION_DATE_SIZE] ;
	extern	PRO_FLASH_uint8_t  g_version_time[VERSION_TIME_SIZE] ;
#elif defined(MCU_USE_RL78)
	extern const uint8_t g_version_date[VERSION_DATE_SIZE];
	extern const uint8_t g_version_time[VERSION_TIME_SIZE];
#endif

#endif	
	
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* COMPLIER_CFG_H */