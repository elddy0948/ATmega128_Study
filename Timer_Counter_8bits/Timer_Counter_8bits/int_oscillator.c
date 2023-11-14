
/*
 * int_oscillator.c
 *
 * Created: 2023-11-14 오후 10:43:52
 *  Author: HJ KIM
 */ 

#include "int_oscillator.h"

void init_port(void)
{
	DDRB = 0x01;
	PORTB = 0x00;
}

void init_timer0(void)
{
	ASSR |= (1 << AS0);	// using external oscillator
	TCCR0 |= (1 << CS02) | (1 << CS00);
	TIMSK |= (1 << TOIE0);
}