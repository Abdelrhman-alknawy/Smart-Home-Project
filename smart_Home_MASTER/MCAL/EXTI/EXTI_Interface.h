#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

void EXTI_VoidInit();
void EXTI_VoidEnable(u8 Copy_u8InterruptNumber, u8 Copy_u8SenseControll);
void EXTI_VoidDisable(u8 Copy_u8InterruptNumber);
void EXTI_SetCallBack(void(*LPF)(void));
//void EXIT_VoidSetAll(u8 Copy_u8SenseControll,u8 Copy_u8SenseControll, u8 Copy_u8SenseControll);

#endif
