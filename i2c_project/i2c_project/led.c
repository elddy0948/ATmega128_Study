
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
}

void display_led(uint8_t led_to_display)
{
	PORTC = led_to_display;
}