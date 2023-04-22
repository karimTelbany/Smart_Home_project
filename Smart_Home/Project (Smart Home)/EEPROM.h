#ifndef EEPROM_H_
#define EEPROM_H_

#include "StandredMacros.h"
#include "STD.h"
#include "IIC.h"

void EEPROM_Init(void);  //initialize EEPROM
void EEPROM_Write(uint16 Add,uint8 Data);  //Write on EEPROM
unsigned char EEPROM_Read(uint16 Add);     //Read from EEPROM



#endif