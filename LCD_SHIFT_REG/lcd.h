/*
 * lcd.h
 *
 * Created: 
 *  Author: Mohamed Gobran 2015
 */ 


#ifndef LCD_H_
#define LCD_H_






void Lcd_Init();
void Lcd_Sendstr (uint8_t *ptr);

void Lcd_Senddata (uint8_t data);

void Lcd_Sendcmd (uint8_t cmd);
void Lcd_FirstRow(uint8_t column);
void LCD_SecondRow(uint8_t column);

#endif /* LCD_H_ */