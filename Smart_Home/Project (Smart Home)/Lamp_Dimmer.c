#include "Lamp_Dimmer.h"
 
void Lamp_Dimmer_init()  //initialize OCS 2 For Dimmer LED
{
setbit(TCCR2,WGM20);  //fast PWM mode
setbit(TCCR2,WGM21);  //fast PWM mode
setbit(TCCR2,COM21);  //Clear OC2 on compare match, set OC2 at BOTTOM,
setbit(TCCR2,CS21);   //clk/128 (From prescaler)
setbit(TCCR2,CS20);   //clk/128 (From prescaler)

}
void Dimmer_control()  //Control Dimmer
{
	uint8 data=Dimmer_ADC_read();  //Get data from ADC	
	OCR2=(data);        

}