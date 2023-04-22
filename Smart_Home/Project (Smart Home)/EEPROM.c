#include "EEPROM.h"

void EEPROM_Init(void)    //initialize EEPROM
{  
	TWI_Init();	
}
void EEPROM_Write(uint16 Add,uint8 Data)   //Write on EEPROM
{   	
	TWI_Start();
    TWI_Write((uint8)(0xA0|((Add & 0x0700)>>7)));  
	TWI_Write((uint8)(Add));
	TWI_Write(Data);
	TWI_Stop();
}


uint8 EEPROM_Read(uint16 Add)   //Read from EEPROM
{
	TWI_Start();
	TWI_Write((uint8)(0xA0|((Add&0x0700)>>7)));  //1010 aaa0
	TWI_Write((uint8)(Add));
	TWI_Start();
	TWI_Write((uint8)(0xA0|((Add&0x0700)>>7)|1));  //1010 aaa0
	return TWI_Read_with_NACK();
	TWI_Stop();
}
