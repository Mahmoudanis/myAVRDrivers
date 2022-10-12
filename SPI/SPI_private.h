/*
 * SPI_private.h
 *
 *  Created on: Oct 8, 2022
 *      Author: mahmo
 */

#ifndef SPI_SPI_PRIVATE_H_
#define SPI_SPI_PRIVATE_H_

#define SPCR		*((volatile u8 *)0x2D)
#define SPSR		*((volatile u8 *)0x2E)
#define SPDR		*((volatile u8 *)0x2F)

/*SPCR*/
#define SPIE		7
#define SPE			6
#define DORD		5
#define MSTR		4
#define CPOL		3
#define CPHA		2
#define SPR1		1
#define SPR0		0

/*SPSR*/
#define SPIF		7
#define WCOL		6
#define SPI2X		0

/*SPDR*/
#define MSB		7
#define LSB		0

#define MASTER_MODE			1
#define SLAVE_MODE			0

#define LSB_START			1
#define RSB_START			0

#define LEADING_RISING_SAMPLE		0
#define LEADING_RISING_SETUP		1
#define LEADING_FALLING_SAMPLE		2
#define LEADING_FALLING_Setup		3

#define PRESCALER_4                 0
#define PRESCALER_16                1
#define PRESCALER_64                2
#define PRESCALER_128               3



#endif /* SPI_SPI_PRIVATE_H_ */
