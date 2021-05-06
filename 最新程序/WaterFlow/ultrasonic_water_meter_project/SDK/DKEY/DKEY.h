
#ifndef  __DKEY__H__
#define  __DKEY__H__

#include "main.h"
#include "gpio_lib.h"
#include "r_cg_intp.h"

// ����ֵ
#define True                      ((_Bool)1)
#define False                     ((_Bool)0)

#define DKEY_IDLE_STATE           1U	       // ���̿���״̬��ƽ�Ǹߵ�ƽ
#define Get_DKEY  		          GPIO(13,7)   // ��ȡ��ֵ{Ĭ�ϰ��ⲿ�жϻ���CPU}

#define DKEY_LongDown             0x01         // ����
#define DKEY_Up                   0x02         // ����
#define DKEY_Down                 0x03         // ����
#define DKEY_VOID                 0x00         // ����״̬

#define DKEY_LongDownDelayTime    10u          // ������ʱ��Чʱ�� = DKEY_LongDownDelayTime * ɨ������

#define DKEY_OneMenu_XNum         50u          // ����һ���˵�������
#define DKEY_TowMenu_YNum         50u          // ��������˵�������

typedef struct STU_Menu  // �˵�����
{
	
	unsigned char Menu_X; // X��˵�����λ��[�������ɶ̰��¼�����]
	unsigned char Menu_Y; // Y��˵�����λ��[�������ɳ����¼�����]

}__DKEY_MenuPoint__;

typedef struct STU_Flag  // ״̬��־
{

	// ����������־�����ֶ�ִ�����
	unsigned char OneDown	  : 1;// ���ΰ��±�־
	unsigned char OneUp		  : 1;  // ���ε����־
	unsigned char OneLongDown : 1; // ���γ����¼���־
	
}__StateFlag;


void XY_DKEY_Init(void); // ��ʼ��

void CurrentTime_CNT(void);  // ��ʹ�ó�����ʱ�������ڵ���

void DKEY_Serve(void); // �����жϷ���������δʹ�á�

void DKEY_Scan(void (*DKEY_EVENT)(int *GetDKEY));  // �¼�ɨ�躯��

// ���¼�-���жϷ�ʽ��ɨ�赽�¼�����ִ��
void DKEY_Down_RUN_Serve(void); // �����¼�
void DKEY_Up_RUN_Serve(void); // �����¼�
void DKEY_LongDown_RUN_Serve(void); // �����¼�

void SET_MenuX(unsigned char SET_Menu_X); // ���ò˵�����������[������Ч]
void SET_MenuY(unsigned char SET_Menu_Y); // ���ò˵�����������[������Ч]

unsigned char Get_MenuX(void); // ��ȡ�˵�����������
unsigned char Get_MenuY(void); // ��ȡ�˵�����������

// ����ѯ�¼�״̬��ʽ����ѯ���¼�����ִ�У����ʹ���˲�ѯ״̬��ôͨ��������Ҫ�����Ӧ���¼���־��
_Bool Get_IsOneDown(void); // �Ƿ��е��ΰ����¼�����
_Bool Get_IsOneUp(void); // �Ƿ��е��ε����¼�����
_Bool Get_IsOneLongDown(void);// �Ƿ��е��γ����¼�����
void ClearOneLongDown(void);// ������γ����¼���־
void ClearOneDown(void); // ������ΰ����¼���־
void ClearOneUp(void); // ������ε����¼���־

#endif




