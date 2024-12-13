#include <at89c5131.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"		// Header file with LCD interfacing functions
#include "serial.h"	// Header file with UART interfacing functions

unsigned char ac=0, bd=0, eg=0, ch=0;
int acc1=10000;
int acc2=10000;
char c[6]={'0','0','0','0','0','\0'};
char d[6]={'0','0','0','0','0','\0'};
char acs1[9]={'0','0','0','0','0','0','0','0','\0'};
char acs2[9]={'0','0','0','0','0','0','0','0','\0'};
char x_st[9]={'0','0','0','0','0','0','0','0','\0'};
char z_st[9]={'0','0','0','0','0','0','0','0','\0'};
int i1=0,i2=0;
int amt=0;
int balance=0;
unsigned int x=0,y=0,z=0;

void withdraw_cash(void);
void valid(void);
void int_to_string(unsigned int, char*);
int isdigit(unsigned char);
void accountdisplay (void);

int isdigit(unsigned char c){
		if(0<=(c-'0')<=9){
			return 1;
	}
		else return 0;
}

void int_to_string(unsigned int val,unsigned char *temp_str_data)
{	
   // cha str_data[4]=0;
		temp_str_data[0]=48+(val/10000);
	  temp_str_data[1]=48+(val%10000/1000);
	  temp_str_data[2]=48+((val%1000)/100);
	  temp_str_data[3]=48+((val%100)/10);
	  temp_str_data[4]=48+(val%10);
   // return str_data;
}

void accountdisplay (void){
	if(ac=='1' || ac=='2'){
		valid();
	}
	else{
		transmit_string("No such account, please enter valid details\r\n");
	}
	return;
}

void valid(void){
if(ac=='1'){
	transmit_string("Account Holder: Steven\r\n");
	transmit_string("Account Balance: ");
	int_to_string(acc1, c);
	transmit_string(c);
	transmit_string("\r\n");
					}

if(ac=='2'){
	transmit_string("Account Holder: Gordon\r\n");
	transmit_string("Account Balance: ");
	int_to_string(acc2, d);
	transmit_string(d);
	transmit_string("\r\n");
					}

if(ch=='w' || ch=='W'){
	withdraw_cash();
	}
return;
				}

void withdraw_cash(void){
	transmit_string("Enter AMount, in hundreds\r\n");
	bd = receive_char();
	eg = receive_char();
	
	if((isdigit(bd)==1) && (isdigit(eg)==1)) {
	i1=(int)bd; // i1=(bd - '0');
	i2=(int)eg;
	amt = i1*1000 + i2*100;
	if(ac=='1' || ac=='2'){
	if(ac=='1'){
	balance=acc1;
	}
	else if(ac=='2'){
		balance=acc2;
	}
	
	if(balance-amt<0){
		transmit_string("Insufficient Funds");
	}
	else{
		x=amt/500;
		y=amt-(x*500);
		z=y/100;
		int_to_string(x,x_st);
		int_to_string(z,z_st);
		transmit_string("No. of 500 notes are");
		transmit_string(x_st);
		transmit_string("\r\n");
		transmit_string("No. of 100 notes are");
		transmit_string(z_st);
		transmit_string("\r\n");
		
		if(ac=='1'){
			acc1=acc1-amt;
			transmit_string("Remaining Balance: ");
			int_to_string(acc1,acs1);
			transmit_string(acs1);
			transmit_string("\r\n");
		}
		else if(ac=='2'){
			acc2=acc2-amt;
			transmit_string("Remaining Balance: ");
			int_to_string(acc2,acs2);
			transmit_string(acs2);
			transmit_string("\r\n");
		}
}
	}
	else{
		transmit_string("Invalid Amount");
	}
return;
}
}
// Main function
void main(void)
{
	// Initialize port P1 for output from P1.7-P1.4
	P1 = 0x0F;
	
	// Call initialization functions
	lcd_init();
	uart_init();
	while(1){
	// These strings will be printed in terminal software
	transmit_string("Press A for Account display and W for withdrawing cash\r\n");
	
		ch = receive_char();
		if(ch== 'a' || ch=='A'){
			transmit_string("Hello, Please enter Account Number\r\n");
			ac = receive_char();
			accountdisplay();
		}
		if(ch == 'w' || ch=='W'){
			transmit_string("Withdraw state, enter account number\r\n");
			accountdisplay();
		}
			msdelay(100);
	}
}
