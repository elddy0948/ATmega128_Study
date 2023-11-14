/*
 * seven_segment.c
 *
 * Created: 2023-11-10 오후 2:22:56
 * Author : HJ KIM
 */ 
#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

#define SEGMENT_OUTPUT 0xF0
#define DIGIT_SELECTION_OUTPUT 0x0F

const unsigned char good[4] = {0x3D, 0x5C, 0x5C, 0x5E};
const char seg_pat[10]= {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};


uint8_t shift_left(uint8_t bits)
{
	return (bits >> 1) | ((bits & 0x01) << 4);
}

void seg4_out(int num);
void happy_birthday();
void example_falling_edge(unsigned char num);

void main(void)
{
	unsigned char old_sw, curr_sw, num;
	DDRB |= SEGMENT_OUTPUT;
	DDRD |= SEGMENT_OUTPUT;
	DDRG |= DIGIT_SELECTION_OUTPUT;
	
	DDRE &= 0x0F;
	
	PORTB = 0x0;
	PORTD = 0x0;
	PORTG = 0x08;
	
	old_sw = PINE & 0xF0;
	num = 0;
	
    while (1)
    {
		PORTD = ((seg_pat[num] & 0x0F) << 4) | (PORTD & 0x0F);
		PORTB = (seg_pat[num] & 0x70) | (PORTB & 0x0F);
		
		curr_sw = PINE & 0xF0;
		
		if (old_sw == 0xF0 && curr_sw == 0xE0)
		{
			num = (num + 1) % 10;
		}
		else if (old_sw == 0xF0 && curr_sw == 0xD0)
		{
			if (num != 0) { num--; }
		}
		
		old_sw = curr_sw;
		
    }
}

void seg4_out(int num)
{
	int i, n1000, n100, n10, n1, buf;
	
	n1000 = num / 1000;	
	buf = num % 1000;
	n100 = buf / 100;
	buf = buf % 100;
	
	n10 = buf / 10;
	n1 = buf % 10;
	for (i = 0; i < 2; ++i)
	{
		PORTG = 0x08;
		PORTD = ((seg_pat[n1] & 0x0F) << 4) | (PORTD & 0x0F);
		PORTB = (seg_pat[n1] & 0x70) | (PORTB & 0x0F);
		_delay_ms(5);
		
		PORTG = 0x04;
		PORTD = ((seg_pat[n10] & 0x0F) << 4) | (PORTD & 0x0F);
		PORTB = (seg_pat[n10] & 0x70) | (PORTB & 0x0F);
		_delay_ms(5);
		
		PORTG = 0x02;
		PORTD = ((seg_pat[n100] & 0x0F) << 4) | (PORTD & 0x0F);
		PORTB = (seg_pat[n100] & 0x70) | (PORTB & 0x0F);
		_delay_ms(5);
		
		PORTG = 0x01;
		PORTD = ((seg_pat[n1000] & 0x0F) << 4) | (PORTD & 0x0F);
		PORTB = (seg_pat[n1000] & 0x70) | (PORTB & 0x0F);
		_delay_ms(5);		
	}
}

void happy_birthday()
{
	uint32_t digits_display = 0x00000000;
	uint8_t i;
	uint8_t bday[8] = {
		seg_pat[2], seg_pat[0], seg_pat[2], seg_pat[3],
		seg_pat[0], seg_pat[3], seg_pat[2], seg_pat[0],
	};
	uint8_t bday_size = sizeof(bday) / sizeof(bday[0]);
	
	uint8_t digit_cursor = 0x08;
	uint8_t digit_index = 0;
	
	for (i = 0; i < bday_size; ++i)
	{
		digits_display |= bday[i];
		
		for (digit_index = 0; digit_index < 25; ++digit_index)
		{
			PORTG = 0x08;
			PORTD = ((digits_display & 0x0000000F) << 4) | (PORTD & 0x0F);
			PORTB = (digits_display & 0x000000F0) | (PORTB & 0x0F);
			_delay_ms(5);
			PORTG = 0x04;
			PORTD = ((digits_display & 0x00000F00) >> 4) | (PORTD & 0x0F);
			PORTB = ((digits_display & 0x0000F000) >> 8) | (PORTB & 0x0F);
			_delay_ms(5);
			PORTG = 0x02;
			PORTD = ((digits_display & 0x000F0000) >> 12) | (PORTD & 0x0F);
			PORTB = ((digits_display & 0x00F00000) >>16) | (PORTB & 0x0F);
			_delay_ms(5);
			PORTG = 0x01;
			PORTD = ((digits_display & 0x0F000000) >> 20) | (PORTD & 0x0F);
			PORTB = ((digits_display & 0xF0000000) >> 24) | (PORTB & 0x0F);
			_delay_ms(5);
		}
		
		//PORTD = ((digits_display & 0x0F) << 4) | (PORTD & 0x0F);
		//PORTB = (digits_display & 0x70) | (PORTB & 0x0F);
		
		digit_cursor >>= 1;
		
		if (digit_cursor == 0x00) { digit_cursor = 0x08; }
		digits_display <<= 8;
	}
	
}