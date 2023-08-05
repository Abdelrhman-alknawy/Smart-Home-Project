#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

void LCD_voidInit(void);
void LCD_voidSendData(u8 Copy_u8Data);
void LCD_voidSendCommand(u8 Copy_u8Command);
void LCD_voidGoToXY(u8 Copy_u8XPosistion, u8 Copy_u8YPosition);
void LCD_voidSendString(u8 * Copy_pu8String);
void LCD_voidSendCustomCharacter(u8 * Copy_pu8CharacterArray, u8 Copy_u8PatternNum, u8 Copy_u8XPosition, u8 Copy_u8YPosition);
void LCD_voidSendNumber(u16 Copy_u16Number);
void LCD_voidClearDisplay(void);
#define		CLEAR_COMMAND		0x01


#endif
