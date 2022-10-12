/*
 * SPI_prog.c
 *
 *  Created on: Oct 8, 2022
 *      Author: mahmo
 */
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "SPI_interface.h"
#include "SPI_private.h"
#include "SPI_CFG.h"
#include "../DIO/DIO_interface.h"

static void (*G_SPI_Callback)(void);

void SPI_vInit (void)
{
	//SPCR = 0b01011100;
#if MASTER_OR_SLAVE == MASTER_MODE
	DIO_vWritePinDirection(DIO_PORTB,DIO_PIN5 , DIO_PIN_OUTPUT);//MOSI
	DIO_vWritePinDirection(DIO_PORTB,DIO_PIN7 , DIO_PIN_OUTPUT);//SCK
	DIO_vWritePinDirection(DIO_PORTB,DIO_PIN6 , DIO_PIN_INPUT);//MISO
#endif
#if MASTER_OR_SLAVE == SLAVE_MODE
	DIO_vWritePinDirection(DIO_PORTB,DIO_PIN5 , DIO_PIN_INPUT);//MOSI
	DIO_vWritePinDirection(DIO_PORTB,DIO_PIN7 , DIO_PIN_INPUT);//SCK
	DIO_vWritePinDirection(DIO_PORTB,DIO_PIN6 , DIO_PIN_OUTPUT);//MISO
#endif

	/*1- SPI ENABLE*/
	SET_BIT(SPCR,SPE);
	/*2- SPI INTERRUPT ENABLE*/
	SET_BIT(SPCR,SPIE);
	/*3- DATA ORDER*/
#if LSB_OR_RSB_START == LSB_START
	SET_BIT(SPCR,DORD);
#endif
#if LSB_OR_RSB_START == RSB_START
	CLR_BIT(SPCR,DORD);
#endif
	/*4- SPI MASTER/ SLAVE*/
#if MASTER_OR_SLAVE == MASTER_MODE
	SET_BIT(SPCR,MSTR);
#endif
#if MASTER_OR_SLAVE == SLAVE_MODE
	CLR_BIT(SPCR,MSTR);
#endif
	/*5- SPI MODE*/
#if SPI_MODE == LEADING_RISING_SETUP
	/*5-A CPOL*/
	CLR_BIT(SPCR,CPOL);
	/*5-B CPHA*/
	SET_BIT(SPCR,CPHA);
#endif
#if SPI_MODE == LEADING_FALLING_Setup
	/*5-A CPOL*/
	SET_BIT(SPCR,CPOL);
	/*5-B CPHA*/
	SET_BIT(SPCR,CPHA);
#endif
#if SPI_MODE == LEADING_RISING_SAMPLE
	/*5-A CPOL*/
	CLR_BIT(SPCR,CPOL);
	/*5-B CPHA*/
	CLR_BIT()_BIT(SPCR,CPHA);
#endif
#if SPI_MODE == LEADING_FALLING_SAMPLE
	/*5-A CPOL*/
	SET_BIT(SPCR,CPOL);
	/*5-B CPHA*/
	CLR_BIT(SPCR,CPHA);
#endif
	/*6- SPI BAUDRATE*/
#if BAUD_RATE == PRESCALER_4
	SPCR&=(~(0b11<<0)|PRESCALER_4);
#endif
#if BAUD_RATE == PRESCALER_16
	SPCR&=(~(0b11<<0)|PRESCALER_16);
#endif
#if BAUD_RATE == PRESCALER_64
	SPCR&=(~(0b11<<0)|PRESCALER_64);
#endif
#if BAUD_RATE == PRESCALER_128
	SPCR&=(~(0b11<<0)|PRESCALER_128);
#endif
}
u8 SPI_u8Trancieve_synch (u8 A_u8Byte)
{
	/* Start transmission */
	SPDR = A_u8Byte;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));

	return SPDR;//di eladata elly rag3a
}
/**************asynchronas********************/

u8 SPI_vIsAvailable_asynch (void)
{
	u8 local_flag = 0;
	if (GET_BIT(SPSR,SPIF)==1)
		local_flag = 1;
	return local_flag;
}



void SPI_vRegisterCallback ( void (*fptr)(void)) //register means reserve
{
	G_SPI_Callback = fptr;
}

void SPI_vTransmit_asynch (u8 A_u8Byte)
{
	SPDR= A_u8Byte;
//	u8 Data;
//	if (GET_BIT(SPSR,SPIF)==1)
//	return SPDR;
}

u8 SPI_u8RecieveData_asynch (void)
{
	return SPDR;
}

void __vector_12 (void) __attribute__((signal)); //attribute order of elcompiler 34an tdif option llfunction (cancel optimization t2fl el global 2bl mtd5ol 34an tmn3 el nesting
void __vector_12 (void)
{
	if(G_SPI_Callback!=NULL)
	{
		G_SPI_Callback();
	}
}
