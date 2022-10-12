/*
 * SPI_interface.h
 *
 *  Created on: Oct 8, 2022
 *      Author: mahmo
 */

#ifndef SPI_SPI_INTERFACE_H_
#define SPI_SPI_INTERFACE_H_

void SPI_vInit (void);
u8 SPI_u8Trancieve_synch (u8 A_u8Byte);

void SPI_vRegisterCallback ( void (*fptr)(void)); //register means reserve
void SPI_vTransmit_asynch (u8 A_u8Byte);
u8 SPI_u8RecieveData_asynch (void);
u8 SPI_vIsAvailable_asynch (void);
#endif /* SPI_SPI_INTERFACE_H_ */
