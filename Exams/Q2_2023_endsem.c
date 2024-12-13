#include <at89c5131.h>
#include <stdio.h>
#include <ctype.h>
#include <lcd.h>		// Header file with LCD interfacing functions
#include <serial.h>	// Header file with UART interfacing functions

sbit LED1=P1^7;
int i=0;
int amt[]={10000,10000};
unsigned char ch=0; 
unsigned char ch2=0; 
unsigned char ch1=0; 
unsigned char cha=0;
unsigned char quant=0;
unsigned char a_c, b_c, c_c, d_c, q_c;
unsigned int num=0;
unsigned int ret_1=0;
int ret_5=0, q=0;
unsigned int amount=0;
unsigned int d=0;
unsigned int rem_balance=0;
char balance1_ascii[6]={0,0,0,0,0,'\0'};
char balance2_ascii[6]={0,0,0,0,0,'\0'};
char rem_balance_ascii[6]={0,0,0,0,0,'\0'};
char ret_5_ascii[6]={0,0,0,0,0,'\0'};
char ret_1_ascii[6]={0,0,0,0,0,'\0'};
int numbers[4]={8,6,4,4};


void string_maker(unsigned int a, unsigned int b, unsigned int c, unsigned int d){
transmit_string("8051- ");
a_c = a + '0';
transmit_char(a_c);
transmit_string("\r\n");
transmit_string("TIVA-C- ");
b_c = b + '0';
transmit_char(b_c);
transmit_string("\r\n");
transmit_string("Atmega328p- ");
c_c = c + '0';
transmit_char(c_c);
transmit_string("\r\n");
transmit_string("STM32- ");
d_c = d + '0';
transmit_char(d_c);
transmit_string("\r\n");
}	


// Main function
void main(void)
{
	lcd_init();
	uart_init();
	
	while(1)
	{
			string_maker(numbers[0],numbers[1],numbers[2],numbers[3]);
			transmit_string("Press I for Issue and R for return\r\n");
			ch = receive_char();
		
		switch(ch)
		{
			case 'I': 
			case 'i':
			transmit_string("Enter Microcontroller to be borrowed \r\n");
			cha = receive_char();
			transmit_string("Enter quantitiy\r\n");
			q_c = receive_char();
			q = q_c -'0';
			
				if(cha=='1'){
					if((numbers[0]-q)<9 && (numbers[0]-q)>=0){
					transmit_string("requested microcontroller alloted\r\n");
					numbers[0]-=q;
					}
					else{
						transmit_string("Not available");
					}
			}
				else if(cha=='2'){
					if(9>(numbers[1]-q)>0){
					transmit_string("requested microcontroller alloted \r\n");
					numbers[1]-=q;
					}
					else{
						transmit_string("Not available");
					}
					}
					
				else if(cha=='3'){
					if(9>(numbers[2]-q)>0){
					transmit_string("requested microcontroller alloted\r\n");
					numbers[2]-=q;
					}
						else{
						transmit_string("Not available");
					}
				}
				else if(cha=='4'){
					if(9>(numbers[3]-q)>0){
					transmit_string("requested microcontroller alloted\r\n");
					numbers[3]-=q;
					}
						else{
						transmit_string("Not available");
					}
				}
					
				else{
					transmit_string("No such uC \r\n");
				}
				break;
				
case 'R':
case 'r':
transmit_string("Enter Microcontroller to be borrowed \r\n");
cha = receive_char();
			
if(cha=='1'){
if(numbers[0]==8){
transmit_string("You cant return what you dont have bitch");	
				}
else{
	transmit_string("Enter quantity");
	quant = receive_char();
	if((quant-'0')+numbers[0]<9){
	transmit_string("microcontroller returned");
		numbers[0]+=(quant-'0');
	}
	else{
		transmit_string("Returned micro-controller out of bounds...");
	}
}
}
	
if(cha=='2'){
if(numbers[1]==6){
transmit_string("You cant return what you dont have bitch");	
				}
else{
	transmit_string("Enter quantity");
	quant = receive_char();
	if((quant-'0')+numbers[1]<7){
	transmit_string("microcontroller returned");
		numbers[1]+=(quant-'0');
	}
	else{
		transmit_string("Returned micro-controller out of bounds...");
	}
}
}

if(cha=='3'){
if(numbers[2]==4){
transmit_string("You cant return what you dont have bitch");	
				}
else{
	transmit_string("Enter quantity");
	quant = receive_char();
	if((quant-'0')+numbers[2]<7){
	transmit_string("microcontroller returned");
		numbers[2]+=(quant-'0');
	}
	else{
		transmit_string("Returned micro-controller out of bounds...");
	}
}
}

if(cha=='4'){
if(numbers[3]==4){
transmit_string("You cant return what you dont have bitch");	
				}
else{
	transmit_string("Enter quantity");
	quant = receive_char();
	if((quant-'0')+numbers[3]<5){
	transmit_string("microcontroller returned");
		numbers[3]+=(quant-'0');
	}
	else{
		transmit_string("Returned micro-controller out of bounds...");
	}
}
}
						break;
						
			default:
				break;
		}
						
}
}
