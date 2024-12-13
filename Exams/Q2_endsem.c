#include <at89c5131.h>
#include <lcd.h>		
#include <serial.h>

unsigned char cha1,cha2;
int i1,i2,i1a,i1b,h1,h2,h0,y0,y1,y2,arg;
int max=0;
char arg_c;
char max_c;
char maxa[2]={0,0};
int watchdog=0;

int argmax(int a, int b, int c){
	max=a;
	if(b>max){
		max=b;
	}
	if (c>max){
		max=c;
	}
	
	if(max==a){ return 0;}
	if(max==b){return 1;}
	if(max==c){return 2;}
	else
		return 10;
}

int relu(int i){
	if(i<0){
		return 0;
	}
	else
		return i;
}

void task2(void){
lcd_init();
uart_init();

lcd_cmd(0x80);													//Move cursor to first line
msdelay(4);
lcd_write_string("Nimay Shah");
lcd_cmd(0xC0);
msdelay(4);
lcd_write_string("22B1232");

		transmit_string("Lets Begin");
		transmit_string("\r\n");
		cha1=receive_char();
		cha2=receive_char();
			
		i1=cha1-'0';
		i2=cha2-'0';
		
		i1a=i1-i2;
		i1b=i2-1;
		
		h0=relu(i1a);
		h1=relu(i1b);
		h2=0;

		y0 = (-1*h1)+h2+2;
		y1 = (-3*h0);
		y2 = (h2)-1;
			
		arg=argmax(y0,y1,y2);
			
		arg_c = arg +'0';
		transmit_char(arg_c);
		transmit_string("\r\n");
maxa[0]='0';
	max=y0;
	if(y1>max){
	max=y1;
	}
	if (y2>max){
	max=y2;
	}
		if(max<0){
			transmit_string("-");
		max=max*(-1);
		maxa[0]='-';
		}
		max_c = max + '0';
		transmit_char(max_c);
		transmit_string("\r\n");		
		
maxa[1]=max+'0';
lcd_cmd(0x01);
lcd_cmd(0x80);													//Move cursor to first line
msdelay(4);
lcd_write_string("Class= ");
lcd_write_char(arg_c);
lcd_cmd(0xC0);
lcd_write_string("Max Val= ");
lcd_write_char(maxa[0]);
lcd_write_char(maxa[1]);		
msdelay(1000);
return;
}

void printer(void){
	lcd_cmd(0x01);
	lcd_cmd(0x80);
			lcd_write_string("Program Stuck!!");
	lcd_cmd(0xC0);
			lcd_write_string("Restarting...");
	msdelay(2000);
	return;
}

void call_new(void){
	lcd_cmd(0x01);
	lcd_cmd(0x80);													//Move cursor to first line
msdelay(4);
lcd_write_string("Nimay Shah");
lcd_cmd(0xC0);
msdelay(4);
lcd_write_string("22B1232");
	return;
}

void timer0_isr () interrupt 1
{
	watchdog++;
	if(watchdog>2750){
	TR0=0;
	printer();
	watchdog=0;
	call_new();
	}
	
	TR0 = 1;
	TH0 = 0x00;//Values for Timer 0 TH0
	TL0 = 0x00;//Values for Timer 0 TL0
	return;
}

void main(void){

	TMOD = 0x01;//mode 1 timer 0 and timer 1
	TH0 = 0x00;//Values for Timer 0 TH0
	TL0 = 0x00;//Values for Timer 0 TL0
	ET0 = 1; //activate interrupts for both timers
	EA = 1;  //activate global interrupts
	TR0 = 1; //start timer 0
	while(1){
		task2();
		watchdog=0;
		TR0=0;
		TH0=0x00;
		TL0=0x00;
		TR0=1;
	}
}
	
	
		