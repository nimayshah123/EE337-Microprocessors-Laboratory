/**********************************************************
EE337: ADC IC MCP3008 interfacing with pt-51
(1) Complete spi_init() function from spi.h 

***********************************************************/

#include <at89c5131.h>
#include "lcd.h"																				//Driver for interfacing lcd 
#include "mcp3008.h"																		//Driver for interfacing ADC ic MCP3008


char adc_ip_data_ascii[6]={0,0,0,0,0,'\0'}; //string array for saving ascii of input sample
char adc_ip_data_ascii2[6]={0,0,0,0,0,'\0'};
code unsigned char display_msg1[]="Volt.: ";						//Display msg on 1st line of lcd
code unsigned char display_msg2[]=" mV";								//Display msg on 2nd line of lcd
char* y;


void main(void)
{
	int j=0;
	unsigned int adc_data=0;
	unsigned int adc_data2=0;
	
	spi_init();																					
	adc_init();
  lcd_init();
	
	
	
	while(1)
	{
	 	unsigned int x;		 
		x = adc(4);																					//Read analog value from 0th channel of ADC Ic MCP3008
		adc_data = (unsigned int) (x*3.2258); 							//Converting received 10 bits value to milli volt (3.3*1000*i/p /1023)
		
		int_to_string(adc_data,adc_ip_data_ascii);
		
	lcd_cmd(0x80);	// Function set: 2 Line, 8-bit, 5x7 dots
	msdelay(4);
		
	lcd_write_string(display_msg1); //Display "Volt: " on first line of lcd
		    //Print analog sampled input on lcd using int_to_string function and 
		    //Display "XXXXX mV" on second line of LCD
	lcd_write_string(adc_ip_data_ascii);

	}
}
