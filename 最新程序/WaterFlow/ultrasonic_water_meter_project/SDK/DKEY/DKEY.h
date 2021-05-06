
#ifndef  __DKEY__H__
#define  __DKEY__H__

#include "main.h"
#include "gpio_lib.h"
#include "r_cg_intp.h"

// 布尔值
#define True                      ((_Bool)1)
#define False                     ((_Bool)0)

#define DKEY_IDLE_STATE           1U	       // 键盘空闲状态电平是高电平
#define Get_DKEY  		          GPIO(13,7)   // 读取键值{默认绑定外部中断唤醒CPU}

#define DKEY_LongDown             0x01         // 长按
#define DKEY_Up                   0x02         // 弹起
#define DKEY_Down                 0x03         // 按下
#define DKEY_VOID                 0x00         // 空闲状态

#define DKEY_LongDownDelayTime    10u          // 长按延时生效时间 = DKEY_LongDownDelayTime * 扫描周期

#define DKEY_OneMenu_XNum         50u          // 横向一级菜单最大个数
#define DKEY_TowMenu_YNum         50u          // 纵向二级菜单最大个数

typedef struct STU_Menu  // 菜单坐标
{
	
	unsigned char Menu_X; // X轴菜单索引位置[横坐标由短按事件驱动]
	unsigned char Menu_Y; // Y轴菜单索引位置[纵坐标由长按事件驱动]

}__DKEY_MenuPoint__;

typedef struct STU_Flag  // 状态标志
{

	// 下列三个标志必须手动执行清除
	unsigned char OneDown	  : 1;// 单次按下标志
	unsigned char OneUp		  : 1;  // 单次弹起标志
	unsigned char OneLongDown : 1; // 单次长按事件标志
	
}__StateFlag;


void XY_DKEY_Init(void); // 初始化

void CurrentTime_CNT(void);  // 当使用长按键时必须周期调用

void DKEY_Serve(void); // 按键中断服务函数【暂未使用】

void DKEY_Scan(void (*DKEY_EVENT)(int *GetDKEY));  // 事件扫描函数

// 【事件-类中断方式】扫描到事件立即执行
void DKEY_Down_RUN_Serve(void); // 按下事件
void DKEY_Up_RUN_Serve(void); // 弹起事件
void DKEY_LongDown_RUN_Serve(void); // 长按事件

void SET_MenuX(unsigned char SET_Menu_X); // 设置菜单横坐标索引[弹起生效]
void SET_MenuY(unsigned char SET_Menu_Y); // 设置菜单纵坐标索引[长按生效]

unsigned char Get_MenuX(void); // 获取菜单横坐标索引
unsigned char Get_MenuY(void); // 获取菜单纵坐标索引

// 【查询事件状态方式】查询到事件立即执行（如果使用了查询状态那么通常都必须要清除对应的事件标志）
_Bool Get_IsOneDown(void); // 是否有单次按下事件发生
_Bool Get_IsOneUp(void); // 是否有单次弹起事件发生
_Bool Get_IsOneLongDown(void);// 是否有单次长按事件发生
void ClearOneLongDown(void);// 清除单次长按事件标志
void ClearOneDown(void); // 清除单次按下事件标志
void ClearOneUp(void); // 清除单次弹起事件标志

#endif




