#include "ADC.h"

void ADC_init(void)   //initialize ADC Registers
{
setbit(ADCSRA,ADPS0); //set division factor =8
setbit(ADCSRA,ADPS1); //set division factor =8
setbit(ADCSRA,ADEN);  //ADC Enable
}

signed int Temp_ADC_read(void)     //Read Analog Value of Temp Sensor
{
	ADMUX=0;                        //use ADC0
	setbit(ADCSRA,4);               // clear flag
	setbit(ADCSRA,6);               //start conversion bit register
	while(readbit(ADCSRA,4)==0){ }; //wait for conversion till flag became one
    return ADC;
}

signed int Dimmer_ADC_read(void)    //Read Analog Value of Lamp Dimmer Resistor
{
	ADMUX=1;                        //use ADC1
	setbit(ADCSRA,4);               // clear flag
	setbit(ADCSRA,6);               //start conversion bit register
	while(readbit(ADCSRA,4)==0){ }; //wait for conversion till flag became one
	return ADC;
}