
/*
 * led_pattern.c
 *
 * Created: 2023-11-02 오후 9:47:40
 *  Author: HJ KIM
 */ 

#define F_CPU 16000000L
#define TURNON_NEXT_LIGHT(l) (l << 1)

#include <avr/io.h>
#include <util/delay.h>

int start_led_pattern()
{
	char light_value = 0x01;
	
	DDRB = 0xFF;
	
	while(1)
	{
		PORTB = light_value;
		
		TURNON_NEXT_LIGHT(light_value);
		
		if (light_value == 0) light_value = 0x01;
		
		_delay_ms(1000);
	}
	
	return 0;
}

int start_array_pattern()
{
	char patterns[] = 
	{
		0xA0, 0x50, 0x28, 0x14,
		0x0A, 0x05, 0x82, 0x41
	};
	
	int index = 0;
	int pattern_size = sizeof(patterns) / sizeof(patterns[0]);

	DDRB = 0xFF;

	while(1)
	{
		PORTB = patterns[index++];
		if (index >= pattern_size) { index = 0; }
		_delay_ms(1000);
	}
	
	return 0;
}

char circular_shift_right(char pattern)
{
	char LSB = pattern & 0x01;
	char MSB = LSB << 7;
	
	char new_pattern = pattern >> 1;
	
	new_pattern |= MSB;
	
	return new_pattern;
}

char circular_shift_left(char pattern)
{
	char MSB = pattern & 0x80;
	char LSB = MSB >> 7;
	
	char new_pattern = pattern << 1;
	
	new_pattern |= LSB;
	
	return new_pattern;
}

int start_circular_pattern()
{
	char pattern = 0xA0;
	
	DDRB = 0xFF;
	
	while(1)
	{
		PORTB = pattern;
		pattern = circular_shift_right(pattern);
		_delay_ms(1000);
	}
	
	return 0;
}

char start_cross_pattern()
{
	char right_pattern = 0x01;
	char left_pattern = 0x80;
	
	DDRB = 0xFF;
	
	while(1)
	{
		PORTB = right_pattern | left_pattern;

		right_pattern = circular_shift_right(right_pattern);
		left_pattern = circular_shift_left(left_pattern);
		
		if ((right_pattern << 1) == left_pattern)
		{
			right_pattern = circular_shift_right(right_pattern);
			left_pattern = circular_shift_left(left_pattern);
		}
		
		_delay_ms(1000);				
	}
}