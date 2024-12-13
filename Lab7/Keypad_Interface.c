#include<at89c5131.h>
#include<string.h>
#include"Text_Write.h"
#include"Music_note.h"
int Read;
int Row;
int Col;
int x;
struct Out1{
	int freq;    //a struct storing the frequency of note 
	char out[3]; // storing string to be displayed: "sil"--> max 3 
} Output;
char letter[4][4] = {'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};
x = 0x0F;

void Read_Value(int x)
{
	P3 = x;
	Read = P3 & 0x0F;
}

void Ground_Row()
{
	Read_Value(x);   // put all 1 
	while(Read != x)
		Read_Value(x);
}

void Read_Col()
{
	while(1)
	{
		Read_Value(x);  
		if(Read != x)
			break;     //kuch mil gya
	}
	
	msdelay(20);  //debounce 
	
	Read_Value(x);   
	while(Read == x)
		Read_Value(x); //when read!=x, come out with the last iteration value
}

void Find_Row()
{
	int row;
	int d;
	d = 1;
	row = 0;
	while(15 - d >= 7) //didnot check if Read still = 0x0F for all the time => erroneous input
	{
		Read_Value((((15 - d)*16)+15));  //1110 1101 1011 0111
		if(Read == 0x0F)
		{
			row++;
			d *= 2;
		}
		else
			break;
		
		Row = row;
	}
}

void Find_Col()
{
	int col;
	col = 3;
	while(Read & 1 != 0) //1111 0111 0011 0001 0000
	{
		Read>>=1;
		col--;
	}
	
	Col = col;
}

void Output_func()
{
	char k;
	k = letter[Row][Col];
	switch(k)
	{
		case '1':
			Output.freq = 240;
			strcpy(Output.out, "Sa");
			break;
		
		case '2':
			Output.freq = 270;
			strcpy(Output.out, "Re");
			break;
		
		case '3':
			Output.freq = 300;
			strcpy(Output.out, "Ga");
			break;
		
		case '4':
			Output.freq = 320;
			strcpy(Output.out, "Ma");
			break;
		
		case '5':
			Output.freq = 360;
			strcpy(Output.out, "Pa");
			break;
		
		case '6':
			Output.freq = 400;
			strcpy(Output.out, "Dha");
			break;
		
		case '7':
			Output.freq = 450;
			strcpy(Output.out, "Ni");
			break;
		
		case '8':
			Output.freq = 480;
			strcpy(Output.out, "Sa");
			break;
		
		case '9':
			Output.freq = 0;
			strcpy(Output.out, "Sil");
			break;
		
		default:
			Output.freq = 0;
			strcpy(Output.out, "#$%");
	}
	
	lcd_init();
	lcd_cmd(0x80);
	lcd_write_string(Output.out);
	
	
}

void Music_func()
{
	start(Output.freq);
}

void main(void)
{
	while(1)
	{
		Row = 0;
		Col = 3;
		Ground_Row();
		Read_Col();
		Find_Row();
		Find_Col();
		Output_func();
		Music_func();
	}
}