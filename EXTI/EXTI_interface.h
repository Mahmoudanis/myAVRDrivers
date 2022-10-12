/*
 * EXTI_interface.h
 *
 *  Created on: Sep 21, 2022
 *      Author: mahmo
 */

#ifndef EXTI_EXTI_INTERFACE_H_
#define EXTI_EXTI_INTERFACE_H_

#define EXTI_0 		0
#define EXTI_1 		1
#define EXTI_2 		2

#define FAL_EDG  	0
#define RIS_EDG 	1


void EXTI_vInit (void);
void EXTI_vSetSenseCtrl (u8 A_u8ExtiPin, u8 A_u8SenseCtrl);
void EXTI_vEnableInterrupt (u8 A_u8ExtiPin, u8 A_u8SenseCtrl);
void EXTI_vDisableInterrupt (u8 A_u8ExtiPin);
void EXTI_vRegisterCallback (u8 A_u8ExtiPin, void (*fptr)(void)); //register means reserve

#endif /* EXTI_EXTI_INTERFACE_H_ */
