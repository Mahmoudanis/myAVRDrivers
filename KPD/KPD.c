/*
 * KPD.c
 *
 *  Created on: Sep 10, 2022
 *      Author: mahmo
 */
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
//#include "../DIO/DIO_interface.h"
#include <avr/io.h>
#include <util/delay.h>
#include "KPD.h"

#define no_col 4
#define no_row 4

void KPD_vInit (void)
{
	//DIO_vWritePortDirection(DIO_PORTC,0x0f);
	DDRC=0x0F;
	//DIO_vWritePortVAlue(DIO_PORTC,0xff);
	PORTC=0xFF;
}
u8 KPD_u8GetPressedKey(void)
{
	u8 pressed_key=0;
	u8 col;
	u8 row;
	for(col=0;col<no_col;col++)
	{
		//DIO_vWritePinVAlue(DIO_PORTC,col,DIO_PIN_LOW);
		CLR_BIT(PORTC,col);
		for(row=0;row<no_row;row++)
		{
			if(GET_BIT(PINC,(row+4))/*DIO_u8ReadPinVAlue(DIO_PORTC,row+4)*/==0)
			{
				pressed_key = (row+(col*4)+1);
			}
				while(GET_BIT(PINC,(row+4))/*DIO_u8ReadPinVAlue(DIO_PORTC,row+4)*/==0){}
				_delay_ms(5);


		}
		//DIO_vWritePinVAlue(DIO_PORTC,col,DIO_PIN_HIGH);
		SET_BIT(PORTC,col);
	}
	return pressed_key;


}
