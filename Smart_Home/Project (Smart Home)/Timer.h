#ifndef TIMER_H_
#define TIMER_H_

#include "StandredMacros.h"
#include <avr/io.h>
#include <util/delay.h>

void init_servo_timer(void);    //initialize timer value
void Door_lock(void);     //Function to lock the door
void Door_unlock(void);   //Function to unlock the door


#endif 