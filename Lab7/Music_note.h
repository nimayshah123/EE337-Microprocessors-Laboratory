#include <at89c5131.h>
sbit music=P0^7;
int count_freq;
void note(int freq)
{
	
	count_freq = (int) (- (1000000/(freq)));
	TL0 = count_freq&0xFF;
	TH0 = (count_freq>>8)&0xFF;
	
	TR0= 1;
}

void musical_note () interrupt 1
{ 
	music = ~music;
	TL0 = count_freq&0xFF;
	TH0 = (count_freq>>8)&0xFF;
	TR0 = 1;
}

void start(int freq)
{
	TMOD = 0x01; //mode 1 timer 0
	ET0 = 1; //activate interrupts for timer 0
	EA = 1;  //activate global interrupts
	note(freq);
}