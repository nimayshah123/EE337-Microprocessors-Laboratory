#include <at89c5131.h>
#include <math.h>
#include "lcd.h"
#include <stdio.h>

sbit SPEAKER = P0^7;
sbit P30 = P3^0;
sbit P31 = P3^1;
sbit P32 = P3^2;
sbit P33 = P3^3;
sbit P34 = P3^4;
sbit P35 = P3^5;
sbit P36 = P3^6;
sbit P37 = P3^7;

int row=0;
int col=0;

void main (void) {
	TMOD = 0x01;//mode 1 timer 0 and timer 1
	TH0 = 0xFF;//Values for Timer 0 TH0
	TL0 = 0xFF;//Values for Timer 0 TL0
	ET0 = 1; //activate interrupts for both timers
	EA = 1;  //activate global interrupts
	TR0 = 0; //start timer 0
P3=0x0F;

while(1){
while(P3!=0x0F){
}
	
while(1){
if(P3.0==0 || P3.1==0 || P3.2==0 || P3.3==0){
break;
}
}

msdelay(20);
	
if(P3.0==0 || P3.1==0 || P3.2==0 || P3.3==0){
break;
}			
}

P3=0xFF;
while(1){
P3.7=0;
if(P3.0==0){
	row=1;
	col=1;
	break;
}

if(P3.1==0){
	row=1;
	col=2;
	break;
}

if(P3.2==0){
	row=1;
	col=3;
	break;
}

if(P3.3==0){
	row=1;
	col=4;
	break;
}

P3=0xFF;
P3.6=0;
if(P3.0==0){
	row=2;
	col=1;
	break;
}

if(P3.1==0){
	row=2;
	col=2;
	break;
}

if(P3.2==0){
	row=2;
	col=3;
	break;
}

if(P3.3==0){
	row=2;
	col=4;
	break;
}

P3=0xFF;
P3.5=0;
if(P3.0==0){
	row=3;
	col=1;
	break;
}

if(P3.1==0){
	row=3;
	col=2;
	break;
}

if(P3.2==0){
	row=3;
	col=3;
	break;
}

if(P3.3==0){
	row=3;
	col=4;
	break;
}

P3=0xFF;
P3.4=0;
if(P3.0==0){
	row=4;
	col=1;
	break;
}

if(P3.1==0){
	row=4;
	col=2;
	break;
}

if(P3.2==0){
	row=4;
	col=3;
	break;
}

if(P3.3==0){
	row=4;
	col=4;
	break;
}

if(row==1 & col==1){
	TH0=
	TL0=
}


}


}