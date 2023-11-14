
/*
 * led_int.c
 *
 * Created: 2023-11-13 오후 9:23:08
 *  Author: HJ KIM
 */ 

#include "led_int.h"

volatile int state = 0;

ISR(INT4_vect)
{
	state = (state + 1) % 2;
}

void INIT_PORT(void)
{
	DDRC = 0x01;	// set PORTB 0 to output (for led)
	PORTC = 0xFF;	// turn off led
	
	DDRD = 0x00;	// set switch to input
	PORTD = 0x01;	// set switch pull-up
}

void INIT_INT0(void)
{
	EIMSK |= 0xF0;
	EICRA = 0b10101010; // falling edge
	sei();
}

void led_int_main(void)
{
	if (state == 1) { PORTC = 0xFE; }
	else { PORTC = 0xFF; }
}