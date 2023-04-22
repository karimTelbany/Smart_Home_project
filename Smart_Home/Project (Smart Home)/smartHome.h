#ifndef SMARTHOME_H_
#define SMARTHOME_H_

#include "LCD_Deriver.h"
#include "keypad.h"
#include "EEPROM.h"
#include "Timer.h"
#include "ADC.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#define  F_CPU 1000000UL
#include <util/delay.h>

//prototypes
void sign_up_admin (void);
unsigned char compare(unsigned char* pass1, unsigned char* pass2, unsigned char len1, unsigned char len2);
unsigned char get_password(unsigned char* pass);
void log_in_admin (void);
unsigned char check_admin_password(unsigned char len, unsigned char* password);
void change_admin_password(void);
void add_user( );
void delete_user (/*unsigned int *id*/ );
void log_in_user (void);
unsigned char check_user_password(unsigned char len, unsigned char* password ,unsigned char id );
void temp_Control(void);
void led(void);
bool check_admin_password_empty();
unsigned char get_admin_password(unsigned char* pass);
#endif