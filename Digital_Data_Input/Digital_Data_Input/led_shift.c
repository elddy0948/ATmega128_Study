
/*
 * led_shift.c
 *
 * Created: 2023-11-05 오후 9:44:31
 *  Author: HJ KIM
 */ 
#include "led_shift.h"

char circular_shift_left(char pattern)
{
	return ( (pattern << 1) | (pattern >> 7) ); // 원형이동
}

int run_circular_shift()
{
	DDRB = OUTPUT;
	DDRF &= ~0x04;
	
	u8 pattern = 0x01;
	PORTB = pattern;
	
	while(1)
	{
		if ( (PINF & 0x04) >> 2 == 1) // when button pushed
		{
			pattern = circular_shift_left(pattern);
			PORTB = pattern;
		}
	}
	
	return 0;
}

// 수정 버전
int run_shift_lights_fixed()
{
	DDRB = OUTPUT;
	DDRF &= ~0x04;
	
	u8 pattern = 0x01;
	
	PORTB = pattern;
	
	u8 prev_pattern = 0;
	u8 curr_pattern;
	
	while(1)
	{
		curr_pattern = (PINF & 0x04) >> 2;
		
		if (curr_pattern == 1 && prev_pattern == 0)
		{
			pattern = circular_shift_left(pattern);
			PORTB = pattern;
		}
		prev_pattern = curr_pattern;
		
	}
	
	return 0;
}