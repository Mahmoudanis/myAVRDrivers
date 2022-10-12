/*
 * UART_interface.h
 *
 *  Created on: Oct 7, 2022
 *      Author: mahmo
 */

#ifndef UART_DRIVER_UART_INTERFACE_H_
#define UART_DRIVER_UART_INTERFACE_H_

void UART_vInit (void);
void UART_vTransmitByte_synch (u8 A_u8Byte);
u8 UART_u8RecieveByte_synch (void);
void UART_vSetBaudRate (u32 A_u32Baud);

void UART_vTransmitByte_asynch (u8 A_u8Byte);
u8 UART_u8RecievetByte_asynch (void);
void UART_vPrintString(char str[]);
void UART_vReadString(char str[],u32 A_u32size);

u8 UART_u8GetUDRValue (void);
void UART_vSetCallback (void (*fptr)(void));

/*transmit asynch with TX flag*/

#endif /* UART_DRIVER_UART_INTERFACE_H_ */
