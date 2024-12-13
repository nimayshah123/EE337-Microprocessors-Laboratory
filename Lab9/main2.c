#include <at89c5131.h>
#include <stdio.h>
#include <ctype.h>
#include "lcd.h"		// Header file with LCD interfacing functions
#include "serial.h"	// Header file with UART interfacing functions

sbit LED1=P1^7;
int i=0;
int amt[]={10000,10000};
unsigned char ch=0; 
unsigned char ch2=0; 
unsigned char ch1=0; 
unsigned char cha=0;
unsigned int num=0;
unsigned int ret_1=0;
unsigned int ret_5=0;
unsigned int amount=0;
unsigned int d=0;
unsigned int rem_balance=0;
char balance1_ascii[6]={0,0,0,0,0,'\0'};
char balance2_ascii[6]={0,0,0,0,0,'\0'};
char rem_balance_ascii[6]={0,0,0,0,0,'\0'};
char ret_5_ascii[6]={0,0,0,0,0,'\0'};
char ret_1_ascii[6]={0,0,0,0,0,'\0'};

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

int no_of_500 (int a){
	return a/500;
}

int no_of_100 (int b){
	return b/100;
}

void int_to_string(unsigned int val,unsigned char *temp_str_data)
{	
   // char str_data[4]=0;
		temp_str_data[0]=48+(val/10000);
	  temp_str_data[1]=48+(val%10000/1000);
	  temp_str_data[2]=48+((val%1000)/100);
	  temp_str_data[3]=48+((val%100)/10);
	  temp_str_data[4]=48+(val%10);
   // return str_data;
}

// Main function
void main(void)
{
	//Call initialization functions
	lcd_init();
	uart_init();
	
	/*
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
	}*/
	
	// Initialize port P1 for output from P1.7-P1.4
	P1 = 0x0F;
	
	// Call initialization functions
	lcd_init();
	uart_init();
	
	while(1)
	{
			// Receive a character
			transmit_string("Press A for Account Display and W for withdrawing cash \r\n");
			ch = receive_char();
		
		switch(ch)
		{
			case 'A': 
			case 'a':
			transmit_string("Hello, please enter Account Number \r\n");
			cha = receive_char();
				if(cha=='1'){
					transmit_string("Account Holder: Steven \r\n");
					int_to_string(amt[0], balance1_ascii);
					transmit_string("Account Balance:");
					transmit_string(balance1_ascii);
					transmit_string("\r\n");
				}
				else if (cha=='2'){
						transmit_string("Account Holder: Gordon \r\n");				
						transmit_string("Account Balance:");
						int_to_string(amt[1], balance2_ascii);
						transmit_string(balance2_ascii);
						transmit_string("\r\n");
				}
				else{
					transmit_string("No such account, please enter valid details \r\n");
				}
				break;
				
			case 'W':
			case 'w':
					int_to_string(amt[0], balance1_ascii);
					int_to_string(amt[1], balance2_ascii);
			transmit_string("Withdraw state, enter Account Number \r\n");	
			ch = receive_char();
				if(ch=='1'){
					int_to_string(amt[0], balance1_ascii);
					int_to_string(amt[1], balance2_ascii);
					transmit_string("Account Holder: Steven \r\n");
					transmit_string("Account Balance:");
					transmit_string(balance1_ascii);
					transmit_string("\r\n");					
				}
					else if (ch=='2'){			
					transmit_string("Account Holder: Gordon \r\n");
					transmit_string("Account Balance:");
					transmit_string(balance2_ascii);
					transmit_string("\r\n");		
				}
					else if (ch!='1' && ch!='2'){
					transmit_string("No such account, please enter valid details \r\n");
				break;
				}
				
				transmit_string("Enter Amount, in hundreds \r\n");
					ch1 = receive_char();
					ch2 = receive_char();
					
					if (isdigit(ch1) && isdigit(ch2)){
					amount = (((ch1 - '0')*1000) + ((ch2 - '0')*100));
					transmit_char(ch1);
					transmit_char(ch2);
					transmit_string("\r\n");
					}
					
					else{
						break;
					}
					
					num = (int)(ch - '0');
					transmit_char(ch);
					transmit_string("\r\n");
					rem_balance = (amt[num-1]-amount);
					if((amt[num-1]-amount)<0){
					transmit_string("Insufficient Funds \r\n");	
						break;}
					
					ret_5 = no_of_500(amount);
					d = (amount - (ret_5*500));
					ret_1=no_of_100(d);
						
					
					
					amt[num-1] = rem_balance;
					int_to_string(rem_balance, rem_balance_ascii);
					int_to_string(ret_5, ret_5_ascii);
					int_to_string(ret_1, ret_1_ascii);
					transmit_string("Remaining Balance:");
					transmit_string(rem_balance_ascii);
					transmit_string("\r\n");	
					transmit_string("500 notes:");
					transmit_string(ret_5_ascii);
					transmit_string("\r\n");
					transmit_string("100 notes:");
					transmit_string(ret_1_ascii);
					transmit_string("\r\n");
						
						break;
						
			default:
				break;
		}
						
}
}
