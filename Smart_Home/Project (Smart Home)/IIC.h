#ifndef IIC_H_
#define IIC_H_

#include <util/delay.h>
#include <avr/io.h>
#define F_CPU 1000000UL
#include <avr/interrupt.h>
#include "StandredMacros.h"
#include "STD.h"

//Prototypes
void TWI_Init(void);
void TWI_Start(void);
void TWI_Stop(void);
void TWI_Write(uint8 data);
uint8 TWI_Read_with_ACK(void);
uint8 TWI_Read_with_NACK(void);
uint8 TWI_Status(void);

/* I2C Status Bits in the TWSR Register */
#define TW_START         0x08 // start has been sent
#define TW_REP_START     0x10 // repeated start
#define TW_MT_SLA_W_ACK  0x18 // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TW_MT_SLA_R_ACK  0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TW_MT_DATA_ACK   0x28 // Master transmit data and ACK has been received from Slave.
#define TW_MR_DATA_ACK   0x50 // Master received data and send ACK to slave
#define TW_MR_DATA_NACK  0x58 // Master received data but doesn't send ACK to slave



#endif