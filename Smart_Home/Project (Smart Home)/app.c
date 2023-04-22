#include "app.h"
#include <avr/io.h>

void Admin_Mode ()
{
	sign_up_admin();
	log_in_admin();
	
	UART_sendString("Choose Option");
	while(1){
		temp_Control();
		Dimmer_control();
		
	    char Admin_Select;
	    Admin_Select=UART_recieveByte();
	 	
		
		switch (Admin_Select)
		{
			case 'q':
			add_user();
			break;
			
			case 'w':
			delete_user();
			break;
			
			case 'e':
			change_admin_password();
			break;
			
			case 'r':
			return 0;
			
			case 't':
			Door_unlock();
			_delay_ms(3000);
			Door_lock();
			break;
			
			case 'y':
			togglebit (PORTC,2);
			break;
			
			case 'u':
			togglebit(PORTC,3);
			break;
			
			case 'i':
			togglebit(PORTC,4);
			break;
			
			case 'o':
			togglebit(PORTC,5);
			break;
			
			case 'p':
			togglebit(PORTD,2);
			break;
		}
	}
}
void User_Mode ()
{
	temp_Control();
	Dimmer_control();
	log_in_user();
	lcd_clean_screan();
	lcd_display_string("Choose Option");
	while(1){
		char User_Select=KeyPad_getPressedKey();
		switch (User_Select)
		{
			case '1':
			if (readbit(PORTC,2)==1)
			{			
				lcd_go_to_rowcolumn(1,1);
				lcd_display_string("LED 1 off");
			}
			else
			{
				lcd_go_to_rowcolumn(1,1);
				lcd_display_string("LED 1 on ");
			}
			togglebit (PORTC,2);
			break;
			case '2':
			if (readbit(PORTC,3)==1)
			{
				lcd_go_to_rowcolumn(1,1);
				lcd_display_string("LED 2 off");
			}
			else
			{
				lcd_go_to_rowcolumn(1,1);
				lcd_display_string("LED 2 on ");
			}
			togglebit(PORTC,3);
			break;
			case '3':
			if (readbit(PORTC,4)==1)
			{
				lcd_go_to_rowcolumn(1,1);
				lcd_display_string("LED 3 off");
			}
			else
			{
				lcd_go_to_rowcolumn(1,1);
				lcd_display_string("LED 3 on ");
			}
			togglebit(PORTC,4);
			break;
			case '4':
			if (readbit(PORTC,5)==1)
			{ 
				lcd_go_to_rowcolumn(1,1);
				lcd_display_string("LED 4 off");
				
			}
			else
			{
				lcd_go_to_rowcolumn(1,1);
				lcd_display_string("LED 4 on ");
			}
			togglebit(PORTC,5);
			break;
			case '5':
			if (readbit(PORTD,2)==1)
			{				
				lcd_go_to_rowcolumn(1,1);
				lcd_display_string("LED 5 off");
			}
			else
			{	
				lcd_go_to_rowcolumn(1,1);
				lcd_display_string("LED 5 on ");
			}
			togglebit(PORTD,2);
			break;
			case '0':
			return 0;
			break;
		}
	
	}
}
