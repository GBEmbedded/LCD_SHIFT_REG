/*
 * lcd.c
 *
 * author Mohamed Gobran 2015
 */ 

#define F_CPU 16000000UL
#include "avr/io.h"
#include "OutShiftReg.h"      
#include <util/delay.h>
#include "lcd.h"
#include "lcd_config.h"

void Lcd_Init()
{
	
	Lcd_Cont_Port |=(1<<Lcd_E_Pin) ;
	
	Lcd_E_Port |=(1<<Lcd_E_Pin);

	

	Lcd_Sendcmd(0X30);//initialize LCD
	_delay_ms(1);
	Lcd_Sendcmd(0X30);//initialize LCD
	_delay_ms(1);
	Lcd_Sendcmd(0X30);//initialize LCD
	_delay_ms(1);
		
//	Lcd_Sendcmd(0x20);
	/* When the power supply is given to LCD, it remains in 8-bit mode. 
	Now, if 0x20 is sent, lower nibble will not be received by LCD because four data lines (D4-D7) are connected, so 0x02 is sent instead of 0x20.
*/
	Lcd_Sendcmd(0X02);// 4 bit mode
	Lcd_Sendcmd(0X28);// 4 bit 2 lines
	_delay_ms(1);
	Lcd_Sendcmd(0X0C);// display on  cursor off
	
	
	_delay_ms(1);
	Lcd_Sendcmd(0x01);          // make clear LCD
	_delay_ms(1);
	Lcd_Sendcmd(0x02);          // return home
	_delay_ms(1);
	Lcd_Sendcmd(0x06);          // make increment in cursor
	_delay_ms(1);
	Lcd_Sendcmd(0x80);          // “8” go to first line and “0” is for 0th position
	_delay_ms(1);

}


/*   void Lcd_Senddata(uint8_t data)
 *    takse the data to be sent to the LCD through the serial in parallel output shift register
*/
void Lcd_Senddata(uint8_t data)
{
	
	//RS=1 ; RW=0 ;  E From 1 to 0
	uint8_t lownible,highnible;
	
	highnible=(data & 0xf0);      //mask the high nible of data
	highnible = (highnible>>4);  //shift the high nible data 4 bits to right as we will use the LS Nible of the port
	highnible |=(1<<4);          // to set RS =1
	shiftWrite(highnible);       //write the high nible to the serial output shift register
	
	Lcd_E_Port |=(1<<Lcd_E_Pin) ;  //set LCD Enable
	_delay_ms(1);
	Lcd_E_Port &=~(1<<Lcd_E_Pin) ; //clear LCD Enable
	//_delay_ms(1000);	

	lownible=(data &0x0f);   // mask the low nible of data
	lownible |=(1<<4);  // to set RS =1
	shiftWrite(lownible);  //write the low nible to the serial in parallel output shift register
	
	Lcd_E_Port |=(1<<Lcd_E_Pin) ; //set LCD Enable
	_delay_ms(1);
	Lcd_E_Port &=~(1<<Lcd_E_Pin) ;//clear LCD Enable
//_delay_ms(1000);
	
}	

/*   void Lcd_Sendcmd(uint8_t data)
 *    takse the command to be sent to the LCD through the serial in parallel output shift register
*/
void Lcd_Sendcmd(uint8_t cmd)
{
	
	//RS=0 ; RW=0 ;  E From 1 to 0
	unsigned int lownible,highnible;
	
	highnible=(cmd & 0xf0);
	highnible = (highnible>>4);
	highnible &=~(1<<4);  // to set RS =0
	shiftWrite(highnible);
	
	Lcd_E_Port |=(1<<Lcd_E_Pin) ;
	_delay_ms(1);
	Lcd_E_Port &=~(1<<Lcd_E_Pin) ;
	//_delay_ms(1000);
	
	lownible=(cmd &0x0f);
	lownible &=~(1<<4);  // to set RS =0
	shiftWrite(lownible);
	
	Lcd_E_Port |=(1<<Lcd_E_Pin) ;
	_delay_ms(1);
	Lcd_E_Port &=~(1<<Lcd_E_Pin) ;
  // _delay_ms(1000);
}
void Lcd_Sendstr (uint8_t *ptr)
{
	int i=0;
	while (ptr[i]!='\0')
	{
		Lcd_Senddata(ptr[i]);
		i++;
	}
		
}

void Lcd_FirstRow(uint8_t column)
{
	Lcd_Sendcmd(0x80+column);
	
}

void LCD_SecondRow(uint8_t column)
{
	Lcd_Sendcmd(0xC0+column);
}