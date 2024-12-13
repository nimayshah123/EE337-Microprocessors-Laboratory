#include <at89c5131.h>

sbit LED=P3^6;

//Functions prototype
void timerdelay_ON(void);
void timerdelay_OFF(void);

/*
The 8051 has two timers T0 and T1.
When used as timers, the 8051 timers count up every 12th clock cycle.
That means for oscillator clock of 24MHz the timer count increments at the rate 24MHz/12 i.e. 2MHz
So one upcount in timer registers takes 0.5 microseconds.

So to get 4ms delay we need to count for 4ms/0.5us = 8000 count

Hexadecimal value of -8000 is E0C0H

OR 

8000 in hex will be 1F40 . So, 10000 - 1F40 = E0C0H

*/

//Main function
void main(void)
{
	TMOD = 0x10; //Timer 1 in mod 1
	while(1)
	{
		LED = 1;
		timerdelay_ON();
		LED = 0;
		timerdelay_OFF();
	}

}


void timerdelay_ON(void)
{
	TL1 = 0xC0; //Starting Count value
	TH1 = 0xE0;
	TR1 = 1; //Start bit indicates the counting starts
	while(TF1 == 0); //Checks overflow that is FFFFH to 0000H
	TR1 = 0; //Stops the timer
	TF1 = 0;
}

void timerdelay_OFF(void)
{
	TL1 = 
	TH1 = 
	TR1 = 1;
	while(TF1 == 0);
	TR1 = 0;
	TF1 = 0;
}