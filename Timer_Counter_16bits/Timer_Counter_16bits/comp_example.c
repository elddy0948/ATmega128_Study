
/*
 * comp_example.c
 *
 * Created: 2023-11-15 오전 8:49:31
 *  Author: HJ KIM
 */ 
#include "comp_example.h"


int state = 0;

ISR(TIMER1_COMPA_vect)
{
	state = !state;
	if (state) PORTC = 0xFE;
	else PORTC = 0xFF;
	TCNT1 = 0;	
}

void init_ports(void)
{
	DDRC = 0x01;
	PORTC = 0xFF;
}

void init_tci(void)
{
	OCR1A = 0x7FFF;
	TCCR1B |= (1 << CS12);
	TIMSK |= (1 << OCIE1A);
}