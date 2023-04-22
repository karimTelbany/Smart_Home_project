#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#define SET_BIT(REG,BIT) (REG|=(1<<BIT))
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))
#define BIT_IS_SET(REG,BIT) (REG & (1<<BIT) )
#define BIT_IS_CLEAR(REG,BIT) (!(REG & (1<<BIT)) )

/* UART Driver Baud Rate */
#define USART_BAUDRATE 9600

// Functions Prototypes 
void UART_init(void);     //initialize UART
void UART_sendByte(const unsigned char data);  //Send  1 byte of data
unsigned char UART_recieveByte(void);  //receive  1 byte of data
void UART_sendString(const unsigned char *Str);  //Send bytes of data
void UART_receiveString(unsigned char *Str); // //Send bytes of data

#endif 
