/**********************************************************
This header file contains function related uC 8051 SPI module. 
It has functions to initialize spi module and to communicate with SPI slave 
***********************************************************/

//preprocessor directives for guarding against multiple inclusion of header files, read compiler user guide for more information

#ifndef spi_h																						//if identifier spi_h is not defined then goto next line
	#define spi_h 1																				//Define spi_h identifier and assign constant 1 to it 
#endif																									//end if directive

//Declaration of functions which are contained in this header file

void spi_init(void);																		//Initialize SPI module 
unsigned long int spi_trx(unsigned long int spi_data_tx);				//Takes 3 bytes as an input and send it to SPI slave IC and returns 3 bytes which are received from slave
void spi_interrupt(void);																//SPI ISR 																												


//Variable declaration

bit transmit_completed= 0;															//To check if SPI data transmit is complete
unsigned char temp_spi_data;														//Temporary variable

//Function definition


/**********************************************************
  spi_init(): 
	
	Initialization function to be completed
	Initializes SPI peripheral for interfacing with MCP3008, 
	Choose appropriate SPCON value by referring to 
	MCP3008 and AT89C5131 datasheets  	
***********************************************************/
void spi_init(void)
{
  	/*
			Configure SPCON=0x__ is not a bit addressable sfr
																												
			(1) Configure MSTR to set uC in Master mode SCON.4=1
			(2) Configure SSDIS to disable SSBAR thus 
					P1.1(SSBAR) will be available as standard I/O pin SCON.5=1 	             	 	 
			(3) Configure clock polarity s.t. sck from uC set to 1 in idle state
					Refer to SPCON register table no 19-3 from AT89C5131 datasheet SPCON.3=1
			(4) Configure clock phase i.e. CPHA: Refer SPI timing SPCON.2=1
					diagram of ADC IC (figure no. 6-2 in MCP3008 datasheet)
					first and then table no 19-3, figure no. 19-4 to 19-6 in AT89C5131 datasheet
					to choose approriate CPHA value  
			(5) Fclk/16 & Fclk Periph=12MHz ,thus BAUD RATE=750KHz SPCON.7/1/0=011
			(6) Enable SPI interrupt (i.e. configure IEN1 and EA) IEN.2=1
			(7) Enable SPI module (i.e. configure SPCON ) SPCON.6=1
	*/

	
	SPCON = 0x3F;																																																								
	IEN1|= 0x04;																						//enable spi interrupt IEN1 |= 0x__
	EA= 1 ;																									//enable interrupts EA=_; 
	SPCON|= 0x7F ;																					//Enable spi module 
}

/**********************************************************
  spi_trx(): 
	
	Transmits 3 bytes to SPI slave and receive 3 bytes. 
	These 3 bytes are packed into 4 bytes as long datatype.
***********************************************************/
unsigned long int spi_trx(unsigned long int spi_data_tx)
{
	//declaration of local variables 
	unsigned long int spi_data_rx;
	unsigned char spi_data_3,spi_data_2,spi_data_1;
	
	//Send 3rd byte
		transmit_completed = 0;
		
		SPDAT = (spi_data_tx>>16)%256;											//Sending most significant byte of data to SPI slave 
	
		while(!transmit_completed);													//Wait till transmission is complete. 	
			spi_data_3	=	temp_spi_data ;											//Most significant byte will be received  
	
	//Send 2nd byte
		transmit_completed=0;
		SPDAT = (spi_data_tx>>8)%256;												//Extracting and sending byte between MS and LS byte to SPI slave	
		
		while(!transmit_completed);													//Wait till transmission is complete.
			spi_data_2	=	temp_spi_data ;											//Save byte received from SPI slave
	
	//Send 1st byte
		transmit_completed=0;
		SPDAT = (spi_data_tx%256);													//Extracting least significant byte and sending it to spi slave	
		
		while(!transmit_completed);													//Wait till transmission is complete.
			spi_data_1	=	temp_spi_data ;											//Save byte received from SPI slave
			
		spi_data_rx= (spi_data_3<<16) + (spi_data_2<<8) + spi_data_1;			//Concatenate all received byte to form a 32 bit word
	
		return spi_data_rx;																	//return it	
}

/**********************************************************
  spi_interrupt() 
	
	Interrupt service routine for SPI interrupt.
	Generates interrupt if transmission and reception are complete.
	Transmit and receive function (defined above) monitor
	for these flags to check if data transfer is done.
***********************************************************/
void spi_interrupt(void) interrupt 9 										// interrupt address is 0x004B, (Address -3)/8 = interrupt no.
{
	
	switch	( SPSTA & 0xf0)         											//read and clear SPI status register, for more info: table no 76 from datasheet 
	{
		case 0x80:																					//SPIF is set i.e. SP data transfer is complete 
			temp_spi_data=SPDAT;  														//Read received data 
			transmit_completed=1;															//Set transmission complete flag 
 		break;

		case 0x10:
			
		break;
	
		case 0x40:
		break;
	}
}