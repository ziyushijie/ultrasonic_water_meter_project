#ifndef __IRDA_H__
#define __IRDA_H__

typedef enum IrDA_PowerON_OFF_SET
{
	
	IRDA_POWER_OFF = 0x01, // 红外器件电源开启
	IRDA_POWER_ON  = 0x02, // 红外器件电源开启
	
}__IRDA_POWER_OFF_ON__; 

#define IrDA_Power_PIN   P12_bit.no7     // 红外电源管脚

void IrDA_init(void);
void IrDA_PowerControl(__IRDA_POWER_OFF_ON__ ON_Ctr); // 控制红外器件电源开关


#endif  


