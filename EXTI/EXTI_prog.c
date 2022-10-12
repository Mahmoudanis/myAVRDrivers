/*
 * EXTI_prog.c
 *
 *  Created on: Sep 21, 2022
 *      Author: mahmo
 */
#include"../LIB/STD_TYPES.h"
#include"../LIB/BIT_MATH.h"
#include"EXTI_interface.h"
#include"EXTI_CFG.h"
#include"EXTI_private.h"
#include "../DIO/DIO_interface.h"


static void (*G_EXTI0_Callback)(void);

static void (*G_EXTI1_Callback)(void);

static void (*G_EXTI2_Callback)(void);

void EXTI_vRegisterCallback (u8 A_u8ExtiPin, void (*fptr)(void)) //register means reserve
{
	switch(A_u8ExtiPin)
	{
	case EXTI_0:
		G_EXTI0_Callback=fptr;
		break;
	case EXTI_1:
		G_EXTI1_Callback = fptr;
		break;
	case EXTI_2:
		G_EXTI2_Callback =fptr;
		break;
	}
}

void EXTI_vInit (void)
{
	/*1- make pins input*/
#if INTERRUPT == EXTI_0
	DIO_vWritePinDirection(DIO_PORTD,DIO_PIN2,DIO_PIN_INPUT);
	DIO_vWritePinVAlue(DIO_PORTD,DIO_PIN2,DIO_PIN_HIGH);
	/*2- default sense control which is falling edge*/
	SET_BIT(MCUCR,ISC01);
	CLR_BIT(MCUCR,ISC00);
		/*3- enable interrupt*/
	SET_BIT(GICR,INT0);
#endif
#if INTERRUPT == EXTI_1
	DIO_vWritePinDirection(DIO_PORTD,DIO_PIN3,DIO_PIN_INPUT);
	DIO_vWritePinVAlue(DIO_PORTD,DIO_PIN3,DIO_PIN_HIGH);
	/*2- default sense control as falling*/
	SET_BIT(MCUCR,ISC11);
	CLR_BIT(MCUCR,ISC10);
			/*3- enable interrupt*/
	SET_BIT(GICR,INT1);
#endif

#if INTERRUPT == EXTI_2
	DIO_vWritePinDirection(DIO_PORTB,DIO_PIN2,DIO_PIN_INPUT);
	DIO_vWritePinVAlue(DIO_PORTB,DIO_PIN2,DIO_PIN_HIGH);
	/*2- default sense control as falling edge*/
	CLR_BIT(MCUCSR,ISC2);
	/*3- enable interrupt*/
	SET_BIT(GICR,5);
#endif



}
void EXTI_vSetSenseCtrl (u8 A_u8ExtiPin, u8 A_u8SenseCtrl)
{
	switch(A_u8ExtiPin)
		{
		case EXTI_0:
			switch(A_u8SenseCtrl)
			{
			case FAL_EDG:
				SET_BIT(MCUCR,ISC01);
				CLR_BIT(MCUCR,ISC00);
				break;
			case RIS_EDG:
				SET_BIT(MCUCR,ISC01);
				SET_BIT(MCUCR,ISC00);
				break;
			}
			break;
		case EXTI_1:
			switch(A_u8SenseCtrl)
			{
			case FAL_EDG:
				SET_BIT(MCUCR,ISC11);
				CLR_BIT(MCUCR,ISC10);
				break;
			case RIS_EDG:
				SET_BIT(MCUCR,ISC10);
				SET_BIT(MCUCR,ISC11);
				break;
			}
			break;
		case EXTI_2:
			switch(A_u8SenseCtrl)
			{
			case FAL_EDG:
				CLR_BIT(MCUCSR,ISC2);
				break;
			case RIS_EDG:
				SET_BIT(MCUCSR,ISC2);
				break;
			}
			break;
		}
}
void EXTI_vEnableInterrupt (u8 A_u8ExtiPin, u8 A_u8SenseCtrl)
{
	EXTI_vSetSenseCtrl(A_u8ExtiPin,A_u8SenseCtrl);
	switch(A_u8ExtiPin)
	{
	case EXTI_0:
		SET_BIT(GICR,INT0);
		break;
	case EXTI_1:
		SET_BIT(GICR,INT1);
		break;
	case EXTI_2:
		SET_BIT(GICR,INT2);
		break;
	}
}
void EXTI_vDisableInterrupt (u8 A_u8ExtiPin)
{
	switch(A_u8ExtiPin)
		{
		case EXTI_0:
			CLR_BIT(GICR,INT0);
			break;
		case EXTI_1:
			CLR_BIT(GICR,INT1);
			break;
		case EXTI_2:
			CLR_BIT(GICR,INT2);
			break;
		}
}

void __vector_1 (void) __attribute__((signal)); //attribute order of elcompiler 34an tdif option llfunction (cancel optimization t2fl el global 2bl mtd5ol 34an tmn3 el nesting
void __vector_1 (void)
{
	if(G_EXTI0_Callback!=NULL)
	{
		G_EXTI0_Callback();
	}
}

void __vector_3 (void) __attribute__((signal)); //attribute order of elcompiler 34an tdif option llfunction (cancel optimization t2fl el global 2bl mtd5ol 34an tmn3 el nesting
void __vector_3 (void)
{
	if(G_EXTI0_Callback!=NULL)
	{
		G_EXTI1_Callback();
	}
}

void __vector_5 (void) __attribute__((signal)); //attribute order of elcompiler 34an tdif option llfunction (cancel optimization t2fl el global 2bl mtd5ol 34an tmn3 el nesting
void __vector_5 (void)
{
	if(G_EXTI0_Callback!=NULL)
	{
		G_EXTI2_Callback();
	}
}
