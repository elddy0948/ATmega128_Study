
/*
 * seven_segments.c
 *
 * Created: 2023-11-20 오후 2:45:20
 *  Author: HJ KIM
 */ 
#include "seven_segments.h"

const char seg_pat[10]= {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
uint32_t digits_display = 0x00000000;

void SEG_init(void)
{
	DDRB = 0xF0;
	DDRD = 0xF0;
	DDRG = 0x0F;
	
	PORTB = 0x00;
	PORTD = 0x00;
	PORTG = 0x0F;
}

void SEG_display_4byte(uint32_t val)
{
	PORTG = 0x08;
	PORTD = ((val & 0x0000000F) << 4) | (PORTD & 0x0F);
	PORTB = (val & 0x000000F0) | (PORTB & 0x0F);
	_delay_ms(2);
	PORTG = 0x04;
	PORTD = ((val & 0x00000F00) >> 4) | (PORTD & 0x0F);
	PORTB = ((val & 0x0000F000) >> 8) | (PORTB & 0x0F);
	_delay_ms(2);
	PORTG = 0x02;
	PORTD = ((val & 0x000F0000) >> 12) | (PORTD & 0x0F);
	PORTB = ((val & 0x00F00000) >>16) | (PORTB & 0x0F);
	_delay_ms(2);
	PORTG = 0x01;
	PORTD = ((val & 0x0F000000) >> 20) | (PORTD & 0x0F);
	PORTB = ((val & 0xF0000000) >> 24) | (PORTB & 0x0F);
	_delay_ms(2);
}

void SEG_display_birthday(void)
{
	uint8_t i;
	uint8_t bday[8] = {
		seg_pat[2], seg_pat[0], seg_pat[2], seg_pat[3],
		seg_pat[0], seg_pat[3], seg_pat[2], seg_pat[0],
	};
	uint8_t bday_size = sizeof(bday) / sizeof(bday[0]);
	
	uint8_t digit_index = 0;
	
	for (i = 0; i < bday_size; ++i)
	{
		digits_display |= bday[i];
		
		for (digit_index = 0; digit_index < 25; ++digit_index)
		{
			SEG_display_4byte(digits_display);
		}
		
		if (i != bday_size - 1) {		
			digits_display <<= 8;	
		}
	}
}

void SEG_display_digit(int pos, int val)
{
	PORTG = (1 << (4 - pos));
	PORTD = ((seg_pat[val] & 0x0F) << 4) | (PORTD & 0x0F);
	PORTB = (seg_pat[val] & 0x70) | (PORTB & 0x0F);
}