/**********************************************************
This is header file for 10 bit SPI ADC MCP3008 IC 
File contains function definitions specific to MCP3008 IC. 
Data frame is formed and sent to SPI slave MCP3008 accordingly.  
***********************************************************/

//include spi.h for using functions from it. Preprocessor directives are used for guarding  
//against multiple inclusion of header files, read compiler user guide for more information

#ifndef spi_h																		//if identifier spi_h is not defined then goto next line
	#include "spi.h"															//Include SPI driver file, Driver for uC 8051 SPI module
#endif																					//end if directive

//Declaration of functions which are contained in this header file

void adc_init(void);														//Initialize slave ADC IC MCP3008 
unsigned int adc(unsigned char);								//gives command to ADC IC to sample from corresponding channel 
																								//and returns 2 bytes, of which the lower 10 bits are ADC value.

//Signal to ADC IC MCP3008

sbit cs_bar_adc = P1^4;													//Chip Select for the ADC IC

//Function definition

/**********************************************************
adc_init()

Initializes peripheral specific to MCP3008 IC, here slave select
***********************************************************/
void adc_init(void)
{
	cs_bar_adc=1;
}

/**********************************************************
adc()

Function takes channel number as input and returns sampled 
10 bit ADC values. 10 bit is packed as 16 bit unsigned int.
MCP3008 have 8 channels, numbered from 0 to 7 
***********************************************************/
unsigned int adc(unsigned char channel)
{
		unsigned long int temp_adc_data,address,start,ch_address;
		
		//For MCP3008 3 bytes needs to be sent, which are packed as 4 byte (long)
		start = (((unsigned long int) 0x01)<<16);														//3rd: 0x01 is start bit,
		ch_address = (( (unsigned long int) (channel<<4 & 0x70)|0x80 )<<8);	//2nd: 0x80 | (channel&0x07) is address of 
																								//channel number with single ended input configuration, 
																								//lower nibble is don't care, 1st: 0x00 is don't care
	
		address = start + ch_address;								//Concatenate all bytes															
																									
																									
		cs_bar_adc = 0;                 						//Enable ADC IC MCP3008
		temp_adc_data = spi_trx(address);						//sending address of desired channel no. of ADC IC
		cs_bar_adc = 1;    													//Disable ADC IC MCP3008

																								
		temp_adc_data=temp_adc_data & 0x03ff;				//Masking least significant 10 bit 
	  return (unsigned int) temp_adc_data;				//Type casting from 4 byte to 2 byte integer data type (As data is of size 10 bit)
}
