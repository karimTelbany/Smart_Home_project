#ifndef LAMP_DIMMER_H_
#define LAMP_DIMMER_H_

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "StandredMacros.h"
#include "STD.h"
#include "ADC.h"

void Dimmer_control();  //Control Dimmer
void Lamp_Dimmer_init();  //initialize OCS 2 For Dimmer LED

#endif