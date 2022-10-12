/*
 * ADC_private.h
 *
 *  Created on: Sep 23, 2022
 *      Author: mahmo
 */

#ifndef ADC_ADC_PRIVATE_H_
#define ADC_ADC_PRIVATE_H_

#define ADMUX			*((volatile u8*)(0x27))
#define ADCSRA			*((volatile u8*)(0x26))
#define ADCL			*((volatile u8*)(0x24))
#define ADCH			*((volatile u8*)(0x25))
#define SFIOR			*((volatile u8*)(0x50))
#define ADC_DATA		*((volatile u16*)(0x24))

/*ADMUX bits*/
#define MUX0				0
#define MUX1				1
#define MUX2				2
#define MUX3				3
#define MUX4				4
#define ADLAR				5
#define REFS0				6
#define REFS1				7

/*ADCSRA bits*/
#define ADPS0				0
#define ADPS1				1
#define ADPS2				2
#define ADIE				3
#define ADIF				4
#define ADATE				5
#define ADSC				6
#define ADEN				7


#define VREF_AVCC 		 	0b01

#define ADC_CLK_64			0b110

#define CH_0 				0x00
#define CH_1				0x01
#define CH_2 				0x02
#define CH_3 				0x03
#define CH_4				0x04
#define CH_5 				0x05
#define CH_6 				0x06
#define CH_7 				0x07


#endif /* ADC_ADC_PRIVATE_H_ */
