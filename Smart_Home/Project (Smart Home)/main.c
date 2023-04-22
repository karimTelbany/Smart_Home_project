#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "StandredMacros.h"
#include "LCD_Deriver.h"
#include "Timer.h"
#include "ADC.h"
#include "EEPROM.h"
#include "UART.h"
#include "keypad.h"
#include "smartHome.h"
#include "Lamp_Dimmer.h"
#include "app.h"

void Registers_init();

ISR(INT1_vect)
{
	User_Mode();
}

int main(void)
{
	 Registers_init();  //initialize Controller Registers
    lcd_display_string("Welcome");
	_delay_ms(2000);
    while (1) 
    {     
		Admin_Mode();
	}
}

void Registers_init()  //initialize Controller Registers
{
	init_servo_timer();
    Lamp_Dimmer_init();
	ADC_init();
	lcd_init();
	EEPROM_Init();
	UART_init();
	
	setbit(DDRA,2);   	//for Buzzer
	setbit(DDRD,5);   	//for servo motor
	setbit(DDRD,6);   	//for  ac motor
	setbit(DDRD,7);    	//for lamp dimmer
	setbit(SREG,7);

PORTD |= (1<<PD3); 	//enable pull-up
GICR |= (1<<INT1);	//enable external interrupt 1
sei();		//enable global interrupt
	
	setbit(DDRC,2);     // for LED 1
	setbit(DDRC,3);     // for LED 2
	setbit(DDRC,4);     // for LED 3
	setbit(DDRC,5);     // for LED 4
	setbit(DDRD,2);     // for LED 5
	clearbit(DDRA,3);   //for LED button
	clearbit(PORTA,2);  //Buzzer initially off
}

