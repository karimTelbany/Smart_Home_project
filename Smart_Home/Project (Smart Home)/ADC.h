#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include "StandredMacros.h"
#include "STD.h"

void ADC_init(void);                //initialize ADC Registers
signed int Dimmer_ADC_read(void);   //Read Analog Value of Lamp Dimmer Resistor
signed int Temp_ADC_read(void);     //Read Analog Value of Temp Sensor
     



#endif 