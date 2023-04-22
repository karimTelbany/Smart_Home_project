#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "STD.h"
#include <avr/io.h>
#include <util/delay.h>

// Keypad configurations for number of rows and columns
#define N_col 3  //Number of columns is 3
#define N_row 4  //Number of row is 4

//Prototypes
uint8 KeyPad_getPressedKey(void);

#endif