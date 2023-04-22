#ifndef LCD_DERIVER_H_
#define LCD_DERIVER_H_

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "StandredMacros.h"
#include "STD.h"

//LCD Pins
#define EN 6
#define RS 7
#define LCD_CTRL_PORT PORTB
#define LCD_CTRL_PORT_DIR DDRB
#define LCD_DATA_PORT PORTA
#define LCD_DATA_PORT_DIR DDRA

//LCD Commands
#define clear_command 0x01
#define four_bits_mode 0x02
#define two_lines_lcd_4bit 0x28
#define two_lines_lcd_8bit 0x38
#define cruser_off 0x0C
#define cruser_on 0x0E
#define set_cruser_location 0x80
#define curser_home               0x02
#define curser_left               0x04
#define curser_right              0x06
#define shift_display_right       0x05
#define shift_display_left        0x07
#define display_on_curser_blinking 0x0E
#define curser_second_line        0xC0
#define active_second_line        0x3C
#define display_off_curser_off    0x08

//Prototypes
void lcd_sendcommand(uint8 command);      //Send command to control LCD 
void lcd_display_char(uint8 data);        //Display data
void lcd_display_string(const char *Str); //Display array of data(String)  
void lcd_init(void);                      //Initialize LCD
void lcd_clean_screan(void);              //Remove data from screen
void lcd_display_string_a_rowcolumn(uint8 row,uint8 col,const char *Str);  //Display String at specified location
void lcd_go_to_rowcolumn(uint8 row,uint8 col);  //go to specified location
void lcd_into_string(int data);            //Display integer numbers

#endif 