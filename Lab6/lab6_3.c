#include <at89c5131.h>

sbit PORT=P0^7;
int b[]={500, 750, 1000, 500, 1000, 750, 1000, 500};
int x;

void main(void)
{ 
TMOD =0x11; //mode 1 timer 0 and timer 1
PORT =1;	

while(1){
int i=0;	
for(i=0;i<8;i++){
x=b[i]/10;
while(x!=0){		
TH1 = 0xB1;
TL1= 0xE0;
TR1=1;

while(TF1==0){
switch(i){
	case 0:TH0 = 0xEF;
				 TL0 = 0xBA;
				 break;

	case 1:TH0 = 0xF1;
				 TL0 = 0x8C;
				 break;

	case 2:TH0 = 0xF2;
				 TL0 = 0xFB;
					break;

	case 3:TH0 = 0xF3;
				 TL0 = 0xCB;
				break;
	
	case 4:TH0 = 0xF5;
				 TL0 = 0x26;
					break;
	
	case 5:TH0 = 0xF6;
				 TL0 = 0x3C;
				break;
			
	case 6:TH0 = 0xF7;
				 TL0 = 0x52;
				break;
				
	case 7:TH0 = 0xF7;
				 TL0 = 0xDD;
				 break;
			 }
TR0=1;
while(TF0==0){
	if(TF1==1)
		break;
}
PORT =~PORT;
TR0=0;
TF0=0;
}

x--;
TR1=0;
TF1=0;
}
}
}
}