#include <at89c5131.h>
#include <math.h>
#include <lcd.h>
#include <stdio.h>

code long unsigned int a= 29851;
code long unsigned int b= 11237;
long unsigned int a1,a0,b1,b0,c0,c1,c2,c3,c,j=0,t;

code unsigned char display_msg1[]="    Input-1     ";
char a_st[10]={0,0,0,0,0,0,0,0,0,'\0'};
char b_st[6]={0,0,0,0,0,'\0'};

void timer0_isr () interrupt 1
{
	j+=1;
	TR0 = 1;
	TH0 = 0xFF;//Values for Timer 0 TH0
	TL0 = 0xFE;//Values for Timer 0 TL0
}

void int_to_string9(long unsigned int val,unsigned char *temp_str_data)
{	
   // char str_data[4]=0;
		temp_str_data[0]=48+(val/100000000);
	  temp_str_data[1]=48+((val%100000000)/10000000);
	  temp_str_data[2]=48+((val%10000000)/1000000);
	  temp_str_data[3]=48+((val%1000000)/100000);
	  temp_str_data[4]=48+((val%100000)/10000);
		temp_str_data[5]=48+((val%10000)/1000);
	  temp_str_data[6]=48+((val%1000)/100);
	  temp_str_data[7]=48+((val%100)/10);
		temp_str_data[8]=48+((val%10)/1);
   // return str_data;
}

void int_to_string5(long unsigned int val,unsigned char *temp_str_data)
{	
   // char str_data[4]=0;
		temp_str_data[0]=48+(val/10000);
	  temp_str_data[1]=48+(val%10000/1000);
	  temp_str_data[2]=48+((val%1000)/100);
	  temp_str_data[3]=48+((val%100)/10);
	  temp_str_data[4]=48+(val%10);
   // return str_data;
}


void main()
{
	TMOD = 0x01;//mode 1 timer 0 and timer 1
	TH0 = 0xFF;//Values for Timer 0 TH0
	TL0 = 0xFE;//Values for Timer 0 TL0
	ET0=1;
	EA=1;
	TR0=1;
	
a1 = a/10;
a0 = a%10;
b1 = b/10;
b0 = b%10;
c0 = a0*b0;
c1 = (a0+a1)*(b0+b1);
c2 = a1*b1;
c = c0 + (c1 - c0 - c2)*10 + c2*100;
t=j;
TR0=0;
	
	int_to_string5(t,b_st);
	int_to_string9(c,a_st);
	lcd_init();
	lcd_cmd(0x80);													//Move cursor to first line
	msdelay(4);
	lcd_write_string(a_st);
	lcd_cmd(0xC0);													//Move cursor to first line
	msdelay(4);
	lcd_write_string(b_st);
}