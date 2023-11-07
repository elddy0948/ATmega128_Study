
/*
 * led.c
 *
 * Created: 2023-11-06 오후 10:48:15
 *  Author: HJ KIM
 */ 

#include "led.h"

uint8_t led = 0xFE;

uint8_t shift_left(uint8_t pattern)
{
	return ((pattern << 1) | (pattern >> 7));
}

void loading_led()
{
	PORTC = led;
	led = shift_left(led);
	_delay_ms(4);
}

void ack_led()
{
	PORTC = 0xBF;
}

void noack_led()
{
	PORTC = 0x7F;
}