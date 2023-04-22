#include "keypad.h"

uint8 KeyPad_4x3_adjustKeyNumber(uint8 button_number);


uint8 KeyPad_getPressedKey(void) //Functions Definitions
{
	uint8 col,row;
	while(1)
	{
		temp_Control();
		Dimmer_control();
		for(col=0;col<N_col;col++)        // loop for columns */
		{
		
			DDRB = (0b00010000<<col);     //01000000 
		
			PORTB = (~(0b00010000<<col)); //11101111 11011111

			for(row=0;row<N_row;row++)    // loop for rows 
			{
				if(!(PINB & (1<<row)))    // if the switch is press in this row 
				{
						
						while ((PINB & (1<<row)) == 0)  //wait till button unpressed
						{
							;
						}
							
						return KeyPad_4x3_adjustKeyNumber((row*N_col)+col+1); //return button output
				}
			}
		}
	}
}


uint8 KeyPad_4x3_adjustKeyNumber(uint8 button_number) //function to convert pin output to digit
{
	switch(button_number)
	{ 
		case 1:
		return '1';
		break;
		case 2:
		return '2';
		break;
		case 3:
		return '3';
        case 4:
        return '4';
        break;
        case 5: 
        return '5';
        break;
        case 6:
		return '6';
		break;
		case 7:
		return '7';
		break;
		case 8:
		return '8';
		break;
		case 9:
		return '9';
		break;
		case 10:
		return '*';   
		break;
		case 11:
		return '0';
		break;
		case 12:
		return '#';
		break;
	}
}

