#include <at89c5131.h>
#include <stdio.h>
#include <ctype.h>
#include <lcd.h>		
#include <serial.h>

unsigned char ch1,ch2;
unsigned int int1,int2;

void task1(void){
lcd_init();
uart_init();

		while(1){
			
		transmit_string("Lets Begin");
		ch1=receive_char();
		ch2=receive_char();
			
		int1=ch1-'0';
		int2=ch2-'0';
		int1=int1*16;	
		int2=int2*16;
			
		P1=int1;
		msdelay(3000);
		P1=int2;
		
}
}
