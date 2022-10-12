/*
 * LCD_prog.c
 *
 *  Created on: Sep 16, 2022
 *      Author: mahmo
 */
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "LCD_interface.h"
#include "LCD_private.h"
#include "LCD_config.h"
#include "avr/io.h"
#include "avr/delay.h"

void LCD_vidSendChar(char character)
{
	/*select RS -> 1*/
	SET_BIT(LCD_CTRL_PORT,PIN0);
	/*select RW -> 0*/
	CLR_BIT(LCD_CTRL_PORT,PIN1);
	/*put data on LCD pins*/
	PORTB=character;

	/*pulse on enable*/
	SET_BIT(LCD_CTRL_PORT,PIN2);
	_delay_ms(1);
	CLR_BIT(LCD_CTRL_PORT,PIN2);
	_delay_ms(1);

}
void LCD_vidSendCommand(u8 command)
{
	/*select RS -> 1*/
	CLR_BIT(LCD_CTRL_PORT,PIN0);
	/*select RW -> 0*/
	CLR_BIT(LCD_CTRL_PORT,PIN1);
	/*put data on LCD pins*/
	PORTB=command;

	/*pulse on enable*/
	SET_BIT(LCD_CTRL_PORT,PIN2);
	_delay_ms(1);
	CLR_BIT(LCD_CTRL_PORT,PIN2);
	_delay_ms(1);

}

void LCD_vidInit (void)
{
	/* pins direction */
	LCD_DATA_DDR = 0xff;

	SET_BIT(LCD_CTRL_DDR,PIN0);
	SET_BIT(LCD_CTRL_DDR,PIN1);
	SET_BIT(LCD_CTRL_DDR,PIN2);

	_delay_ms(50);

	LCD_vidSendCommand(0b00111000);
	_delay_ms(1);

	LCD_vidSendCommand(0b00001100);
	_delay_ms(1);

	LCD_vidSendCommand(0b00000001);
	_delay_ms(2);

	LCD_vidSendCommand(0b00000110);
	_delay_ms(1);

}

void LCD_vidSendWord (char * ptr)
{
	for(int i=0;ptr[i]!='\0';i++)
	{
		LCD_vidSendChar(ptr[i]);
	}
}
void LCD_vidDisplayCustomChar (u8 CharId)//from0 to 7
{
	if(CharId<8)
	{
	LCD_vidSendChar(CharId);
	}
	}
void LCD_vidSendNumber (s32 num)
{
	if (num <0)
		{
			num = num * (-1);
			LCD_vidSendChar('-');

		}
	s32 rev =0;
	u8 flag =0;



	while(num!=0)
	{
		rev = rev*10 + num%10;
		if (rev == 0 )
		{
			flag ++;

		}
		num/=10;

	}

	while (rev!=0)
	{


		LCD_vidSendChar((rev%10)+'0');

		rev /= 10;
	}
	if (flag !=0)
		{
		while(flag!=0)
		{
		LCD_vidSendChar('0');
			flag --;
		}
		}


}

void LCD_vidSaveCustomChar (u8 CharArr[],u8 CharId)
{
	if(CharId<8)
	{
	LCD_vidSendCommand(0b01000000 + (8 * CharId));
	for(int i = 0 ; i<8 ; i++)
	{
		LCD_vidSendChar(CharArr[i]);
	}
	LCD_vidSendCommand(0b10000000 );
	}
}

void LCD_vidClear_screen (void)
{
	LCD_vidSendCommand(0b00000001);
}

void LCD_vidSet_cursor (u8 x,u8 y)
{
	if(x==1)
		{
		LCD_vidSendCommand(0x80+y-1);
		}
		if(x==2)
			{
			LCD_vidSendCommand(0xc0+y-1);
			}
}
