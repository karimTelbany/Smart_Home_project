#include "Timer.h"

void init_servo_timer(void)       //initialize timer value
{
	setbit(TCCR1A,COM1A1);  //  Clear OC1A/OC1B on compare match, set OC1A at BOTTOM (non-inverting mode)
	setbit(TCCR1A,WGM11);   //  Set fast PWM with the TOP in ICR1
	setbit(TCCR1B,WGM12);   //  Set fast PWM with the TOP in ICR1
    setbit(TCCR1B,WGM13);   //  Set fast PWM with the TOP in ICR1
	setbit(TCCR1B,CS11);    //  Prescaler/8
    ICR1=2500;
}
void Door_unlock(void)      //Function to lock the door
{
	OCR1A = 187;
}
void Door_lock(void)        //Function to unlock the door
{
	OCR1A = 124;
}