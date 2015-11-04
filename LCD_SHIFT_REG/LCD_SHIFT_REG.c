/*
 * LCD_SHIFT_REG.c
 *
 * Created: 10/10/2015 9:05:46 PM
 *  Author: MoHaMeD
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include "lcd.h"
#include "OutShiftReg.h"


int main(void)
{
	uint8_t String[] ="Gobran";
	uint8_t String1[]="Shift Reg LCD";
	
	shiftInit();
	
	Lcd_Init();
	
	 //Lcd_Senddata('a');
	
	
    while(1)
    {
        Lcd_FirstRow(5);
        Lcd_Sendstr(String);
        
        LCD_SecondRow(1);
        Lcd_Sendstr(String1);
    }
}