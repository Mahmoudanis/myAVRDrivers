/*
 * ADC_prog.c
 *
 *  Created on: Sep 23, 2022
 *      Author: mahmo
 */
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../DIO/DIO_interface.h"

#include "ADC_interface.h"
#include "ADC_CFG.h"
#include "ADC_private.h"


static void (* G_ADC16_CallBack)(void);

void ADC_vInit (void)
{
	/*1-select reference bits ADLAR */
	ADMUX=((ADMUX & ~(0b11<<REFS0))|(ADC_VREF<<REFS0));

	/*2- select data adjustment*/
	CLR_BIT(ADMUX,ADLAR);//right adjustment
	/*3-ADC enable*/
	SET_BIT(ADCSRA,ADEN);
	/*4- auto trigger disable*/
	CLR_BIT(ADCSRA,ADATE);
	/*4-a- select auto trigger source*/

	/*5- interrupt DISABLE*/
	CLR_BIT(ADCSRA,ADIE);
	/*6- conversion clock enable*/  //speed of conversion
	ADCSRA &= ~(0b111);
	ADCSRA |= (ADC_CLK_SELEC);

}
u16 ADC_vReadDigitalValue_synch(u8 A_u8Channel)
{
	/*1- select channel*/
	ADMUX &= ~(0b11111);
	ADMUX |= (A_u8Channel & CH_SELEC);//for sure that channel is from 0 to 7
	// or A_u8Channel %8
	/*2- start conversion*/
	SET_BIT(ADCSRA,ADSC);
	/*3- wait for conv. complete flag*/
	while(GET_BIT(ADCSRA,ADIF)==0);//tol m elflag m4 mrfo3 estna
	/*4- clear flag (flag is cleared by setting 1 (not 0))*/
	SET_BIT(ADCSRA,ADIF);
	/*5- return ADC value*/
	return /*(ADCL | ((u16)ADCH)<<8) or */ADC_DATA ;
}

void ADC_vSetCallback (void (* fptr)(void))
{
	G_ADC16_CallBack=fptr;
}
void __vector_16 (void) __attribute__((signal)); //attribute order of elcompiler 34an tdif option llfunction (cancel optimization t2fl el global 2bl mtd5ol 34an tmn3 el nesting
void __vector_16 (void)
{
	if(G_ADC16_CallBack!=NULL)
	{
		G_ADC16_CallBack();
	}
}
void ADC_vEnableInterrupt(void)
{
	SET_BIT(ADCSRA,ADIE);
}
void ADC_vDisableInterrupt(void)
{
	CLR_BIT(ADCSRA,ADIE);
}
void ADC_vSelectChannel(u8 A_u8Channel)
{
	switch(A_u8Channel)
	{
	case CH_0:
		ADMUX &= ~(0b11111);
		ADMUX |= (A_u8Channel & CH_0);
		break;
	case CH_1:
		ADMUX &= ~(0b11111);
		ADMUX |= (A_u8Channel & CH_1);
		break;
	case CH_2:
		ADMUX &= ~(0b11111);
		ADMUX |= (A_u8Channel & CH_2);
		break;
	case CH_3:
		ADMUX &= ~(0b11111);
		ADMUX |= (A_u8Channel & CH_3);
		break;
	case CH_4:
		ADMUX &= ~(0b11111);
		ADMUX |= (A_u8Channel & CH_4);
		break;
	case CH_5:
		ADMUX &= ~(0b11111);
		ADMUX |= (A_u8Channel & CH_5);
		break;
	case CH_6:
		ADMUX &= ~(0b11111);
		ADMUX |= (A_u8Channel & CH_6);
		break;
	case CH_7:
		ADMUX &= ~(0b11111);
		ADMUX |= (A_u8Channel & CH_6);
		break;
	}
}
void ADC_vStartConversion(u8 A_u8Channel)
{
	SET_BIT(ADCSRA,ADSC);
}
u16  ADC_vReadDigitalValue_asynch(void)
{

	return ADC_DATA;
}













































