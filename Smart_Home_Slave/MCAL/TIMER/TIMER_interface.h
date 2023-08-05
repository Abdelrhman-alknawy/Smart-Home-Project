/*************************************************************************/
/* !File Name:         TIMER.c                                     */
/* !Layer    :         MCAL                                              */
/* !Author   :       Abdelrhman Elknawy                                  */
/* !Date     :         2 SEP, 2021                                       */
/* !Version  :         v1.0                                              */
/*************************************************************************/

#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H

void TIMER_voidTimer0Init(void);
void TIMER_voidTimer0SetCompareValue(u8 Copy_u8CompareValue);
void TIMER_voidTimer0SetCallBack(void (*Copy_pvNotificationFunction)(void));
void TIMER_voidTimer1SetInputCaptureValue(u16 Copy_u16CaptureValue);
void TIMER_voidTimer1BSetCompareValue(u16 Copy_u16CompareValue);
void TIMER_voidTimer1ASetCompareValue(u16 Copy_u16CompareValue);
void TIMER_voidTimer1Init(void);
void ICU_voidInit(void);
void ICU_voidSetTrigger(u8 Copy_u8TriggerSource);
u16  ICU_u16ReadInputCapture(void);
void ICU_voidInterruptDisbale(void);
void ICU_voidSetCallBack(void (*Copy_pvNotificationFunction)(void));



#define		RISING_EDGE			0
#define		FALLING_EDGE		1


#endif
