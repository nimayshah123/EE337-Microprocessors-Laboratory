#include <at89c5131.h>
#include <stdlib.h>
#include <stdio.h>
#include <serial.h>
unsigned int resources1[5]={0,5,5,8,6};
unsigned int resources[5]={0,5,5,8,6};  //STORING THE DATA IN ARRAY
unsigned char ds;   
unsigned char af;
unsigned char dm;
unsigned char dp;
unsigned char index_char;         
unsigned char ch;
int index;
int quantity;
unsigned char quantity_char;

void main(void)
{

	uart_init();      
	
	RESET:				//RESET STATE

	ds= resources[1] +48;  //Converting int to char to transmit
	af=resources[2]+48;      
	dm=resources[3]+48;
	dp= resources[4]+48;
	transmit_string("Resources availble:");
	transmit_string("\r\n");
	transmit_string("DSO-");
	transmit_char(ds);
	transmit_string("\r\n");
	transmit_string("AFG-");
	transmit_char(af);
	transmit_string("\r\n");
	transmit_string("DMM-");
	transmit_char(dm);
	transmit_string("\r\n");
	transmit_string("DPS-");
	transmit_char(dp);
	transmit_string("\r\n");
	transmit_string("PRESS I FOR ISSUE R FOR RETURN");
	transmit_string("\r\n");
	
	while(1)
	{
		ch = receive_char();
		if(ch == 'I')     //ISSUE STATE IF "I" PRESSED 
		{
			transmit_string("\r\n");
			transmit_string("Enter Resource to be borrowed:");
			
			index_char= receive_char();
			index = index_char - 48;
				if(index > 0)
				{
					transmit_string("\r\n");
					transmit_string("index is:: ");
					transmit_char(index_char);
					transmit_string("\r\n");
					if(index > 4 ) 
					{
						transmit_string("Requested resource not available...");
						transmit_string("\r\n");
					}
					else
					{
					transmit_string("Enter quantity:");
					transmit_string("\r\n");
					quantity_char= receive_char();
					quantity = quantity_char - 48;
					transmit_string("quantity is :");
					transmit_char(quantity_char);
					transmit_string("\r\n");
					
					if(resources[index] == 0 || quantity > resources[index] )  	//Checking index violation & no resources error & more than max of elements allocation
					{
						transmit_string("Requested resource not available...");
						transmit_string("\r\n");
					}
					else
					{
						transmit_string("Requested resource allocated!");
						transmit_string("\r\n");
						resources[index] = resources[index] - quantity;
					}
			
				}
			}
				goto RESET;   //GOING TO RESET AFTER ISSUE STATE
			}
		else if(ch == 'R')  //RETURN STATE IF "R" PRESSED 
		{
			transmit_string("Enter Resource to be returned::");
			transmit_string("\r\n");
			index_char = receive_char();
			index = index_char - 48;
			if(index > 0) 
			{
				transmit_string("\r\n");
				transmit_string("index is :");
				transmit_char(index+48);
				transmit_string("\r\n");
				
				if( index > 4)  	//Checking index violation & returning more no. of resources 
				{
					transmit_string("YOU CANT RETURN RESOURCES WHAT WE DONT HAVE! " );
					goto RESET;
				}
				
				else if(resources1[index] == resources[index]) 						
				{
					transmit_string("You cant return what you dont have!");
					transmit_string("\r\n"); 
					goto RESET;
				}
				
				transmit_string("Enter quantity:");
				transmit_string("\r\n");
				
				quantity_char = receive_char();
				quantity = quantity_char - 48;
				transmit_string("Quantity::");
				transmit_char(quantity+48);
				transmit_string("\r\n");

			 
					if(resources[index] + quantity > resources1[index] || quantity > resources1[index] )			
					{
							transmit_string("resources are out of bound");
							transmit_string("\r\n");
					}
					else
					{	
						transmit_string("Returned resource received");
						transmit_string("\r\n");
						resources[index] =resources[index] + quantity;
						
					}

					
		}
			goto RESET;   
	}
		else
		{
			goto RESET;   //GOING BACK TO RESET STATE IF ANY OTHER CHARACTER IS PRESSED

		}
}		
}
