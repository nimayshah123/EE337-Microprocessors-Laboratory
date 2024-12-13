#include <at89c5131.h>

bit tx_complete = 0;
bit rx_complete = 0;

void msdelay(unsigned int time)
{
	int i,j;
	for(i=0;i<time;i++)
	{
		for(j=0;j<382;j++);
	}
}

void uart_init(void)
{
	TMOD=0x20;			  
	TH1=0xF3;					
	SCON=0x50;        
  TCON=0x40;       
	ES=1;            
	EA=1;						
}
	
void transmit_char(unsigned char ch)
{
	SBUF=ch;				
	while(!tx_complete); 			
	tx_complete = 0;		 
}

void transmit_string(unsigned char *s)
{
	while(*s != 0)
	{
		transmit_char(*s++);
	}
}
	
unsigned char receive_char(void)
{
	unsigned char ch = 0;
	while(!rx_complete);				
	rx_complete = 0;
	ch = SBUF;					
	return ch;					
}
	
void serial_ISR(void) interrupt 4
{
	if(TI==1)			
	{
		TI = 0;			
		tx_complete = 1;	
	}
	else if(RI==1)			
	{
		RI = 0;			
		rx_complete = 1;
	}
}

void main(void)
{
	unsigned char data_recv[5] = {0,0,0,0,'\0'};
	int sample_val;
	int sample_val_doub;
	unsigned char data_send[5] = {0,0,0,0,'\0'};
	
	uart_init();
	
	while (1)
	{
		//receiving sample value from PC
		//since each sample is a 4 digit number, the digits are stored in a character array of length 4  
		data_recv[0] = receive_char(); 		
		data_recv[1] = receive_char();
		data_recv[2] = receive_char(); 
		data_recv[3] = receive_char();
		data_recv[4] = '\0';

		//converting character array to its equivalent integer value
		sample_val = (data_recv[0]-48)*1000 + (data_recv[1]-48)*100 + (data_recv[2]-48)*10 + (data_recv[3]-48);
		
		//doubling the obtained integer value (you need to implement filtering here...)
		sample_val_doub = sample_val * 2; 
		
		//converting integer value back to 4 character array (i.e string)
		data_send[0] = 48 + (sample_val_doub/1000);
		data_send[1] = 48 + (sample_val_doub%1000/100);
		data_send[2] = 48 + (sample_val_doub%100/10);
		data_send[3] = 48 + (sample_val_doub%10);
		
		//transmitting output back to PC
		transmit_string(data_send);
		transmit_string("\r\n");
	}
}

