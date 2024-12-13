#include <at89c5131.h>
#include "lcd.h"		// Header file with LCD interfacing functions
#include "serial.h"	// Header file with UART interfacing functions

sbit LED1=P1^7;
int i=0;

void lcd_test(void);
void led_test(void);
// Test function definitions
/************************************************
lcd_test():
	LCD test function that gets called when
	'1' is received from UART
	Prints "LCD Ok" on LCD. After 4 seconds
	LCD is cleared
************************************************/
void lcd_test(void)
{
	 lcd_cmd(0x80);
	 lcd_write_string("LCD Ok");
	 msdelay(2000);
	 lcd_cmd(0x01);
	transmit_string("LCD Ok \r\n");
}	

/************************************************
led_test():
	LED test code. Update this function
	to test LEDs on P1.7-P1.4 by blinking
	them for a few times.
************************************************/
void led_test(void)
{
	for(i=0; i<5; i++){
	P1=0xFF;
	msdelay(1000);
	P1=0x0F;	
	}
	transmit_string("LED Ok \r\n");
}

// Main function
void main(void)
{
	unsigned char ch=0;
	
	// Initialize port P1 for output from P1.7-P1.4
	P1 = 0x0F;
	
	// Call initialization functions
	lcd_init();
	uart_init();
	
	// These strings will be printed in terminal software
	transmit_string("************************\r\n");
	transmit_string("******8051 Tests********\r\n");
	transmit_string("************************\r\n");
	transmit_string("Press 1 for LCD test\r\n");
	transmit_string("Press 2 for LED test\r\n");
	
	while(1)
	{
			// Receive a character
			ch = receive_char();
		
			// Decide which test function to run based on character sent
     		// Displays the string on the terminal software
			switch(ch)
			{
				case '1':
					lcd_test();
					break;
				
				case '2':
					led_test();
					break;
							
				default:
						transmit_string("Incorrect Key Pressed\r\n");
					break;
			}
			msdelay(100);
	}
}
