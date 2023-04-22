#include "LCD_Deriver.h"

void lcd_init(void)               //Initialize LCD
{          
	setbit(DDRC,RS);              //Data-Command Control     
	setbit(DDRC,EN);              //LCD Enable
      
      DDRA |= 0xF0;                       //work on 4bit in micro controller
 
    lcd_sendcommand(four_bits_mode);      //work on 4bit in micro controller
	lcd_sendcommand(two_lines_lcd_4bit);  //use two lines + 4 bits data


   lcd_sendcommand(clear_command);        //clear screen
   lcd_sendcommand(cruser_off);           //set cruiserp of
}

void lcd_sendcommand(uint8 command)  //send command to control LCD 
{
	clearbit(PORTC,RS);    //send command to LCD RS=0
    setbit(PORTC,EN);	   //EN=1
    _delay_ms(1);
   
   
	 PORTA = (command & 0xF0); //out is the 4 most significant bits only
	
	_delay_ms(1);
	clearbit(PORTC,EN);     //EN=0
	_delay_ms(1);
	setbit(PORTC,EN);       //EN=1
	_delay_ms(1);
	                      
	PORTA = (command << 4) & 0xF0; // out the lowest 4 bits of the required command to the data bus D4 --> D7 
	
	_delay_ms(1);                  // delay for processing Tdsw = 100ns 
	clearbit(PORTC,EN);            // disable LCD E=0 
	_delay_ms(1);                  // delay for processing Th = 13ns 

}

void lcd_display_char(uint8 data)  //display data
{
	setbit(PORTC,RS);         //Write data to LCD RS=1
	setbit(PORTC,EN);	      //EN=1
	_delay_ms(1);
	
 	PORTA = (data & 0xF0);    //out is the 4 most significant bits only
	
	_delay_ms(1);
	clearbit(PORTC,EN);       //EN=0
	_delay_ms(1);
	setbit(PORTC,EN);         //EN=1
	_delay_ms(1);
	
	PORTA = (data << 4) & 0xF0;   // out the lowest 4 bits of the required command to the data bus D4 --> D7	
	_delay_ms(1);                 //delay for processing Tdsw = 100ns 
	clearbit(PORTC,EN);           // disable LCD E=0 
	_delay_ms(1);                 // delay for processing Th = 13ns 

}

void lcd_display_string(const Int8 *Str)  //display array of data(String)
{
	uint8 i=0;
	while(Str[i] !='\0')         //not equal null
	{
		lcd_display_char(Str[i]);
		i++;
	}
}

void lcd_into_string(int32 data) //display integer numbers
{
	Int8 buff[16];              //string to hold ascii result
	itoa(data,buff,10);         //10 for decimal
	lcd_display_string(buff);   // display output
}

void lcd_clean_screan()  //clear data from screen
{
	
	lcd_sendcommand(clear_command);  //clear display
	
}

void lcd_go_to_rowcolumn(uint8 row,uint8 col)  //go to specified location
{ 
   uint8 address;  //Get which address you want depend on row
switch(row){
	case 0: 
	address=col;
	break;
	case 1:
	address=col+0x40;
	break;
}
lcd_sendcommand(address + set_cruser_location);	
}

void lcd_display_string_a_rowcolumn(uint8 row,uint8 col,const Int8 *Str) //display String at specified location
{
	lcd_go_to_rowcolumn(row,col); //go to required location
	lcd_display_string(Str);      //LCD display string
}
