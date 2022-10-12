/*
 * UART_prog.c
 *
 *  Created on: Oct 7, 2022
 *      Author: mahmo
 */
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "UART_interface.h"
#include "UART_CFG.h"
#include "UART_private.h"

static void (*GS_UART_RXC_callback) (void);

void UART_vInit (void)
{
#if 0
	UCSRB = 0b00011000;

	UCSRC = 0b10000110;
	UBRRL = 51 ;/*9600*/
#endif
#if 1
	/*1- TRANSMITER ENABLE / RECIEVER ENABLE*/
	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRB,RXEN);
	/*2- INTERRUPT ENABLES*/

	/*2-a 	RX IE  */
	SET_BIT(UCSRB,RXCIE);
	/*2-b   TX IE*/
	SET_BIT(UCSRB,TXCIE);
	/*2-c   UDRE IE*/
	SET_BIT(UCSRB,UDRIE);
	/*3- CHARACTER SIZE*/
	u8 ucsrc_setting = 0;/**************************************/
	SET_BIT(ucsrc_setting,7);
	SET_BIT(ucsrc_setting,UCSZ0);
	SET_BIT(ucsrc_setting,UCSZ1);
	//UCSRC |= ucsrc_setting;

	CLR_BIT(UCSRB,UCSZ2);
	/*4- UART MODE SYNCH OR ASYNCH*/
	CLR_BIT(ucsrc_setting,UMSEL);
	//UCSRC |= ucsrc_setting;
	/*5- PARITY EVEN OR ODD*/
	CLR_BIT(ucsrc_setting,UPM0);
	CLR_BIT(ucsrc_setting,UPM1);
	//UCSRC |= ucsrc_setting;
	/*6- 1 STOP OR 2*/
	CLR_BIT(ucsrc_setting,USBS);
	UCSRC = ucsrc_setting;
#endif

}
void UART_vTransmitByte_synch (u8 A_u8Byte)
{
	/* Wait for empty transmit buffer */ //lma yb2a fady eb3t
	while ( !( UCSRA & (1<<UDRE)) );//estna l7d myb2a not be 1 fyb2a b 0
	/* Put data into buffer, sends the data */
	UDR = A_u8Byte;


}
u8 UART_u8RecieveByte_synch (void)
{

	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) );
	/* Get and return received data from buffer */
	return UDR;


}

void UART_vSetBaudRate (u32 A_u32Baud)
{
	UBRRL = A_u32Baud;
}

void UART_vPrintString(char str[])
{
	while (*str != '\0')
	{
		UART_vTransmitByte_synch(*str);
		str++ ;
	}
}
void UART_vReadString(char str[],u32 A_u32size)
{
	for(int i=0 ; i < A_u32size - 1 /*for null terminator*/; i++)
	{
		str[i] = UART_u8RecieveByte_synch();
		if(str[i] == '\n' || str[i] == '\r') // 34an run on linux and windows
		{
			str[i] = '\0';//overright on \n
			break;
		}
	}
}

u8 UART_u8GetUDRValue (void)
{
	return UDR;
}

void UART_vSetCallback (void (*fptr)(void))
{
	GS_UART_RXC_callback = fptr;
}

void __vector_13 (void) __attribute__((signal)); //attribute order of elcompiler 34an tdif option llfunction (cancel optimization t2fl el global 2bl mtd5ol 34an tmn3 el nesting
void __vector_13 (void)
{
	if(GS_UART_RXC_callback!=NULL)
	{
		GS_UART_RXC_callback();
	}
}
