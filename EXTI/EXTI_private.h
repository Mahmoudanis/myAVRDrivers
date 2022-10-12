/*
 * EXTI_private.h
 *
 *  Created on: Sep 21, 2022
 *      Author: mahmo
 */

#ifndef EXTI_EXTI_PRIVATE_H_
#define EXTI_EXTI_PRIVATE_H_

#define MCUCR    *((volatile u8*)(0x55))
#define MCUCSR   *((volatile u8*)(0x54))
#define GICR     *((volatile u8*)(0x5B))
#define GIFR     *((volatile u8*)(0x5A))


#define ISC00 		0
#define ISC01		1
#define ISC10		2
#define ISC11		3

#define ISC2		6

#define INT2		5
#define INT0		6
#define INT1		7



#endif /* EXTI_EXTI_PRIVATE_H_ */
