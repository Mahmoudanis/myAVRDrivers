/*
 * LCD_interface.h
 *
 *  Created on: Sep 16, 2022
 *      Author: mahmo
 */

#ifndef LCD_LCD_INTERFACE_H_
#define LCD_LCD_INTERFACE_H_

void LCD_vidSendChar(char character);
void LCD_vidSendCommand(u8 command);
void LCD_vidInit (void);
void LCD_vidSendWord (char * ptr);
void LCD_vidDisplayCustomChar (u8 CharId);//from0 to 7
void LCD_vidSaveCustomChar (u8 CharArr[],u8 CharId);
void LCD_vidClear_screen (void);
void LCD_vidSendNumber (s32 num);
void LCD_vidSet_cursor (u8 x,u8 y);

#endif /* LCD_LCD_INTERFACE_H_ */
