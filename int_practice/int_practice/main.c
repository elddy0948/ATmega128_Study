/*
 * int_practice.c
 *
 * Created: 2023-11-13 오전 11:30:20
 * Author : HJ KIM

 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define SEGMENT_OUTPUT 0xF0
#define DIGIT_SELECTION_OUTPUT 0x0F

unsigned char EINT4_FLAG_BIT = 0;
unsigned char EINT5_FLAG_BIT = 0;

const unsigned char seg_pat[10]= {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,0x7f, 0x6f};

unsigned char N1, N10, N100, N1000;
unsigned char pos = 0;
unsigned char hour = 12, min = 0, sec = 0;

void Time_out(void);

ISR(INT4_vect)
{
	cli();
	EINT4_FLAG_BIT = 1;
	sei();
}

ISR(INT5_vect)
{
	cli();
	EINT5_FLAG_BIT = 1;
	sei();
}

void Seg4_out(int num);

int main(void)
{
	int num = 0;
	DDRB |= SEGMENT_OUTPUT;
	DDRD |= SEGMENT_OUTPUT;
	DDRG |= DIGIT_SELECTION_OUTPUT;
	
	EIMSK |= 0xF0;
	EICRB = 0b10101010;
	
	PORTB = 0x0;
	PORTD = 0x0;
	PORTG = 0x00;
	
	sei();
	
    while (1) 
    {
		unsigned char i;
		
		for (i = 0; i < 49; ++i)
		{
			Time_out();
		}
		
		sec++;
		
		if (sec == 60)
		{
			sec = 0;
			min++;
			if (min == 60)
			{
				
				min = 0;
				hour = (hour + 1) % 24;
			}
		}
		
		if (EINT4_FLAG_BIT == 1)
		{
			EINT4_FLAG_BIT = 0;
			N1 = min % 10;
			N10 = min / 10;
			N100 = hour % 10;
			N1000 = hour / 10;
			
			if (pos == 0) N1 = (N1 + 1) % 10;
			else if (pos == 1) N10 = (N10 + 1) % 6;
			 else if(pos == 2)
			 {
				 if(N1000 == 2) N100 = (N100 + 1) % 4;
				 else N100 = (N100 + 1) % 10;
			 }
			 else {
				 if(N100 < 4) N1000 = (N1000 + 1) % 3;
				 else N1000 = (N1000 + 1) % 2;
			 }
			 hour = N1000 * 10 + N100;
			 min = N10 * 10 + N1;
		}
		
		if (EINT5_FLAG_BIT == 1)
		{
			EINT5_FLAG_BIT = 0;
			pos = (pos + 1) % 4;
		}
    }
}

void Time_out(void)
{
	PORTG = 0x08;
	PORTD = ((seg_pat[min % 10] & 0x0F) << 4) | (PORTD & 0x0F);
	PORTB = (seg_pat[min % 10] & 0x70 ) | (PORTB & 0x0F);
	_delay_ms(5);
	
	PORTG = 0x04;
	PORTD = ((seg_pat[min / 10] & 0x0F) << 4) | (PORTD & 0x0F);
	PORTB = (seg_pat[min / 10] & 0x70 ) | (PORTB & 0x0F);
	_delay_ms(5);
	
	PORTG = 0x02;
	PORTD = ((seg_pat[hour % 10] & 0x0F) << 4) | (PORTD & 0x0F);
	PORTB = (seg_pat[hour % 10] & 0x70 ) | (PORTB & 0x0F);
	_delay_ms(5);
	
	PORTG = 0x01;
	PORTD = ((seg_pat[hour / 10] & 0x0F) << 4) | (PORTD & 0x0F);
	PORTB = (seg_pat[hour / 10] & 0x70 ) | (PORTB & 0x0F);
	_delay_ms(5);
}