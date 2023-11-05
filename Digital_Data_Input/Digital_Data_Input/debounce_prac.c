
/*
 * debounce_prac.c
 *
 * Created: 2023-11-05 오후 10:01:27
 *  Author: HJKIM
 */ 

#include "debounce_prac.h"

u8 circular_shift_left(u8 pattern)
{
	return ( (pattern << 1) | (pattern >> 7) );
}

int debounce_main()
{
	DDRB = OUTPUT;
	DDRF &= ~0x04;
	
	u8 pattern = 0x01;
	PORTB = pattern;
	
	u8 prev_state = 0, curr_state;
	
	while(1)
	{
		curr_state = (PINF & 0x04) >> 2;
		
		if (RISING_EDGE_CHECK(prev_state, curr_state))
		{
			_delay_ms(30); // 디바운스
			pattern = circular_shift_left(pattern);
			PORTB = pattern;
		}
		prev_state = curr_state;
	}
	
	return 0;
}

int get_button_state()
{
	if ((PINF & 0x04) >> 2 == 1)
	{
		_delay_ms(10);
		if ((PINF & 0x04) >> 2 == 1)
		{
			return 1;	
		}
	}
	return 0;
}

int get_input_twice()
{
	DDRB = OUTPUT;
	DDRF = ~0x04;
	
	u8 pattern = 0x01;
	
	PORTB = pattern;
	
	u8 prev_state = 0, curr_state;
	
	while(1)
	{
		curr_state = get_button_state();
		
		if (RISING_EDGE_CHECK(prev_state, curr_state))
		{
			pattern = circular_shift_left(pattern);
			PORTB = pattern;
		}
		prev_state = curr_state;
	}
	
	return 0;
}