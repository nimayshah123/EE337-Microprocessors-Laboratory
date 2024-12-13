#include <at89c5131.h>

sbit SPEAK1 = P0^7;
unsigned int i = 0;
unsigned int j = 10;
unsigned int k = 15;
unsigned int l = 20;

void nextie(void); // Function prototype

void timer0_isr() interrupt 1 {
    SPEAK1 = ~SPEAK1;
    // Reload values for TH0 and TL0. Start timer 0.
    switch(i) {
        case 0:
            TH0 = 0xEF;
            TL0 = 0xBA;
            break;
        case 1:
            TH0 = 0xF1;
            TL0 = 0x8C;
            break;
        case 2:
            TH0 = 0xF2;
            TL0 = 0xFB;
            break;
        case 3:
            TH0 = 0xF3;
            TL0 = 0xCB;
            break;
        case 4:
            TH0 = 0xF5;
            TL0 = 0x26;
            break;
        case 5:
            TH0 = 0xF6;
            TL0 = 0x3C;
            break;
        case 6:
            TH0 = 0xF7;
            TL0 = 0x52;
            break;
        case 7:
            TH0 = 0xF7;
            TL0 = 0xDD;
            break;
        default:
            break;
    }
    TR0 = 1;
}

void timer1_isr() interrupt 3 {
    nextie();
}

void nextie(void) {
    if (i == 8) {
        i = 0;
    }
    switch(i) {
        case 0:
            j--;
            break;
        case 1:
            k--;
            break;
        case 2:
            l--;
            break;
        case 3:
            j--;
            break;
        case 4:
            l--;
            break;
        case 5:
            k--;
            break;
        case 6:
            l--;
            break;
        case 7:
            j--;
            break;
        default:
            break;
    }

    if (j == 0 || k == 0 || l == 0) {
        i += 1;
        j = 10;
        k = 15;
        l = 20;
    }

    TH1 = 0x4B;
    TL1 = 0xFD;
    TR1 = 1;

    return;
}

void main(void) {
		P0=0xFF;
    TMOD = 0x11; // Mode 1 timer 0 and timer 1
    TH1 = 0xFF; // Values for Timer 1 TH1
    TL1 = 0xFF; // Values for Timer 1 TL1
    ET0 = 1; // Activate interrupts for both timers
    ET1 = 1;
    EA = 1; // Activate global interrupts
    TR1 = 1; // Start timer 1
		TH0 = 0xFF;
	  TL0 = 0xFF;
		TR0 = 1;
	while(1);
}
