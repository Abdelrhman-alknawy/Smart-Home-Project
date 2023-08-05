#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#define ADC0_SINGLE	0
#define ADC1_SINGLE	1
#define ADC2_SINGLE	2
#define ADC3_SINGLE	3
#define ADC4_SINGLE	4
#define ADC5_SINGLE	5
#define ADC6_SINGLE	6
#define ADC7_SINGLE	7
#define TIMEOUT		50000
void ADC_voidInit 	(void);
u16 ADC_u16GetAnalogReadSYNC(u8 Copy_Channel);
u8 	ADC_u16GetAnalogReadASYNC(u8 Copy_Channel,u16 *Pu8Reading,void (*PF_NotificationFun)(void));
//void EXIT_VoidSetAll(u8 Copy_u8SenseControll,u8 Copy_u8SenseControll, u8 Copy_u8SenseControll);
#endif
