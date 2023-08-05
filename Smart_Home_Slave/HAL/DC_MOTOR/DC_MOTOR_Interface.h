/*
 * DC_MOTOR_Interface.h
 *
 *  Created on: Apr 1, 2023
 *      Author: abdelrhman
 */

#ifndef HAL_DC_MOTOR_DC_MOTOR_INTERFACE_H_
#define HAL_DC_MOTOR_DC_MOTOR_INTERFACE_H_

#define CCW		0
#define CW		1


void STEPPER_MOTOR_VoidStep1();
void STEPPER_MOTOR_VoidStep2();
void STEPPER_MOTOR_VoidStep3();
void STEPPER_MOTOR_VoidStep4();
/******************************/
/*SWC:DC_MOTOR_VoidInit		**/
/******************************/
/******************************/
/******************************/
/******************************/
void DC_MOTOR_VoidInit(void);
/******************************/
/**SWC:DC_MOTOR_VoidDirection**/
/******************************/
/******************************/
/******************************/

void DC_MOTOR_VoidDirection(u8 Copy_u8Direction);
/******************************/
/******************************/
/******************************/
/******************************/
/******************************/

void DC_MOTOR_VoidStop();

#endif /* HAL_DC_MOTOR_DC_MOTOR_INTERFACE_H_ */
