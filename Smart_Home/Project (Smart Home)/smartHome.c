#include "smartHome.h"
char str[100] = {0};
uint8 flag;	//to detect id admin password already exist not open sign up again unless if it called from change admin password
void sign_up_admin (void)
{  
	unsigned char desired_password_1[4] = {0};		//The first entered password is saved here
	unsigned char desired_password_2[4] = {0};		//The second entered password is saved here
	unsigned char length_1 = 0;						//Length of first entered password
	unsigned char length_2 = 0;						//Length of second entered password
	
	if (check_admin_password_empty() == true || flag == 1)
	{
	lcd_clean_screan();
	lcd_go_to_rowcolumn(0,1);
	lcd_display_string("Your new Password: ");
	lcd_go_to_rowcolumn(1,2);
	length_1 = get_admin_password(desired_password_1);
	
	lcd_clean_screan();
	lcd_go_to_rowcolumn(0,1);
	lcd_display_string("Re-enter Password: ");
	lcd_go_to_rowcolumn(1,2);
	length_2 = get_admin_password(desired_password_2);
	
	
	if(compare(desired_password_1,desired_password_2,length_1,length_2))
	{
		unsigned char i = 0;		//Just a counter variable
			
		//Save the length of the password in EEPROM (Location = 0x0001)
		EEPROM_Write(0x0001,length_1);
		
		for(i = 0; i < length_1; i++)
		{
			//Save the password in EEPROM (In location from 2 to 5)
			_delay_ms(50);
			EEPROM_Write(i+2,desired_password_1[i]);
			
			
		}

		//Successful operation
		lcd_clean_screan();
		lcd_display_string("password saved");
		_delay_ms(1000);
	}
	
	else
	{
		//Failed operation, try again
		lcd_clean_screan();
		lcd_go_to_rowcolumn(0,1);
		lcd_display_string("Wrong Password");
		lcd_go_to_rowcolumn(1,2);
		lcd_display_string("Please Try again");
		_delay_ms(1000);
		sign_up_admin();
	}
	flag=0;
}
else
{
	
}
}

/*************************************************************************************************************/

unsigned char compare(unsigned char* pass1, unsigned char* pass2, unsigned char len1, unsigned char len2)
{
	unsigned char i = 0;		//Just a counter variable

	if(len1 != len2)
	{
		
		#if debug
		lcd_clean_screan();
		lcd_go_to_rowcolumn(1,1);
		lcd_display_string("! = ");
		_delay_ms(1000);
		#endif
		return 0;
	}
	
	else
	{
		for(i = 0; i < len1; i++)
		{
			if(pass1[i] != pass2[i])
			{
				#if debug
				lcd_clean_screan();
				lcd_go_to_rowcolumn(1,1);
				lcd_display_string("pass1 = ");
				lcd_display_string(itoa((int)pass1[i],(char*)str,10));
				lcd_go_to_rowcolumn(1,2);
				lcd_display_string("pass2 = ");
				lcd_display_string(itoa((int)pass2[i],(char*)str,10));
				_delay_ms(500);
				#endif
				return 0;
			}
			else
			{
				#if debug
				lcd_clean_screan();
				lcd_go_to_rowcolumn(1,1);
				lcd_display_string("pass1 = ");
				lcd_display_string(itoa((int)pass1[i],str,10));
				lcd_go_to_rowcolumn(1,2);
				lcd_display_string("pass2 = ");
				lcd_display_string(itoa((int)pass2[i],str,10));
				_delay_ms(2000);
				#endif
				continue;			
			}
		}
		return 1;
	}
}

/*************************************************************************************************************/

unsigned char get_password(unsigned char* pass)
{
	int cnt = 0;
	unsigned char key = 0;
	
	lcd_sendcommand(cruser_on);
	
	for(cnt = 0; cnt <= 4 ; )
	{
		key = KeyPad_getPressedKey();
		
		if(key == '#')
		{
			break;
		}
		
		else if(key == '*' && cnt > 0)
		{
			lcd_display_char(' ');

		}
		else if(key == '*' && cnt <= 0)
		{
			cnt = 0;
		}
		else if(cnt != 4)
		{
			if (key != '*')
			{
				pass[cnt++] = key;
				lcd_display_char('*');
			}
			
		}
	}

	lcd_sendcommand(cruser_off);
	
	return cnt;
}

/*************************************************************************************************************/

unsigned char get_admin_password(unsigned char* pass)
{
	int cnt = 0;
	unsigned char key = 0;
	for(cnt = 0; cnt <= 4 ; )
	{
		key = UART_recieveByte();
		
		if(key == '/')
		{
			break;
		}
		else if(cnt != 4)
		{	
			pass[cnt++] = key;
				UART_sendString("*");
		}
	}	
	return cnt;
}

/****************************************************************************************/
void log_in_admin (void)
{
	unsigned char entered_password[4] = {0};				//The entered password is saved here
	unsigned char length = 0;								//Length of entered password
	unsigned char counter = 0 ;
	while(counter < 3)
	{
		lcd_clean_screan();
		UART_sendString(" Enter admin password : ");
		lcd_go_to_rowcolumn(1,2);
		length = get_admin_password(entered_password);
	
		if(check_admin_password(length, entered_password))
		{
			UART_sendString(" Login Success ");
			Door_unlock(); 
			_delay_ms(2500);
			Door_lock();
			break;
		}
		else
		{
			counter++ ;
			UART_sendString(" try again: ");
		}
	}
	if (counter > 2 )
	{
	 UART_sendString(" blocked: ");
     setbit(PORTA,2);
	while (1)
	{
	  ;
	}
	}
}

/*************************************************************************************************************/

unsigned char check_admin_password(unsigned char len, unsigned char* password)
{
	unsigned char i = 0;				//Just a counter variable
	
	if(EEPROM_Read(0x0001) != len)		//Length is stored in EEPROM location 0x0001
	{
		return 0;
	}
	else
	{
		for(i = 0; i < len; i++)
		{
			if(password[i] != EEPROM_Read(i+2))		//Password is stored in EEPROM from location 2 to 5
			{
				UART_sendString(" Wrong Pass! ");
				return 0;
			}
		}
		return 1;
	}
}

/*************************************************************************************************************/

void change_admin_password(void)
{
	unsigned char old_password[4] = {0};		//Old password is stored here
	unsigned char length = 0;					//length of old password is stored here
	
	UART_sendString(" Enter old password : ");
	length = get_admin_password(old_password);
	if (check_admin_password(length, old_password))
	{
		flag=1;
		sign_up_admin();
	}
	else
	{
		UART_sendString(" Wrong Password ");
		change_admin_password();
	}
}

/*************************************************************************************************************/

void add_user()
{

unsigned char desired_password_1[4] = {0};		//The first entered password is saved here
unsigned char desired_password_2[4] = {0};		//The second entered password is saved here
unsigned char length_1 = 0;						//Length of first entered password
unsigned char length_2 = 0;	
unsigned char id = 0 ;
	
UART_sendString(" enter user id: ");
	 
	  id = UART_recieveByte();
	  UART_sendByte(id);
	

id = 48-(int)id ;
UART_sendString(" Your new Password: ");
length_1 = get_admin_password(desired_password_1);


UART_sendString(" Re-enter Password: ");

length_2 = get_admin_password(desired_password_2);


if(compare(desired_password_1,desired_password_2,length_1,length_2))
{
	unsigned char i = 0;		//Just a counter variable
	
	EEPROM_Write( id*5 +1 ,length_1);
	
	for(i = 0; i < length_1; i++)
	{
		_delay_ms(50);
		EEPROM_Write(i + id*5 + 3,desired_password_1[i]);
	}
	
	//Successful operation
	UART_sendString(" password saved ");

}

else
{
	//Failed operation, try again
	UART_sendString(" Wrong Password ");
	UART_sendString(" Please Try again ");
	add_user();
}
}

/*************************************************************************************************************/
	
void delete_user (/*unsigned int *id*/)
{
	char id;
	UART_sendString(" User id is : ");
	id=UART_recieveByte();
	UART_sendByte(id);
	EEPROM_Write((id)*5 + 1 , 0);
	EEPROM_Write((id)*5 + 2 , 0);
	EEPROM_Write((id)*5 + 3 , 0);
	EEPROM_Write((id)*5 + 4 , 0);
    UART_sendString(" ok ");
}

/*************************************************************************************************************/

void log_in_user (void)
{
	unsigned char entered_password[4] = {0};				//The entered password is saved here
	unsigned char length = 0 ;
	unsigned char id ;
	unsigned char actual_id ;
	unsigned count=0;   //for iterations
	 lcd_clean_screan();
	   lcd_display_string("enter user id: ");
	   do
	   {
		   id = KeyPad_getPressedKey();
		   lcd_display_char(id);
	   } while (KeyPad_getPressedKey() != '#');
while (count<3)
{
	   actual_id = 48 - (int)id;
		lcd_clean_screan();
		lcd_display_string("Enter your password: ");
		lcd_go_to_rowcolumn(1,2);
		length = get_password(entered_password);
		if(check_user_password(length, entered_password ,actual_id ))
		{
			lcd_clean_screan();
			lcd_display_string("user Verified");
			lcd_go_to_rowcolumn(1,2);
			lcd_display_string("Welcome");
		    _delay_ms(1000);
			return 0;
		}
		else
		{
			lcd_clean_screan();
			lcd_display_string("wrong Password");
			count++;
			if (count > 2 )
			{
				lcd_clean_screan();
				lcd_display_string(" blocked: ");
				setbit(PORTA,2);
				while (1)
				{
					;
				}
			}
			_delay_ms(500);
					}
}
	   }
/*************************************************************************************************************/

unsigned char check_user_password(unsigned char len, unsigned char* password ,unsigned char id )
{
	unsigned char i = 0;				
	if(EEPROM_Read(id*5 +1) != len)		
	{
		return 0;
	}
	else
	{
		for(i = 0; i < len; i++)
		{
			if(password[i] != EEPROM_Read(i + id*5 + 3))		
			{
				lcd_clean_screan();
				lcd_display_string("Wrong Password");
				_delay_ms(1000);
				return 0;
			}
		}
		return 1;
	}
	
}
 
 /*************************************************************************************************************/
 
void temp_Control(void)
{
	signed int volt;
	float result;

	volt=Temp_ADC_read();
	result=(float)(5*volt)/1023;//conversation for LM45 Sensor
	result*=100;
	if (result>28)
	{
		setbit(PORTD,6);
	}
	else if (result<21)
	{
		clearbit(PORTD,6);
	}

	
}

/*************************************************************************************************************/

bool check_admin_password_empty()
{
	uint8 i;
	uint8 counter=0;
	for (i=0;i<4;i++)
	{
		if (EEPROM_Read(i+2) == 0)
		{
			counter++;
		}	
	}
	if (counter==4)
	{
		return true;
	} 
	else
	{
		return false;
	}
}

/*************************************************************************************************************/

