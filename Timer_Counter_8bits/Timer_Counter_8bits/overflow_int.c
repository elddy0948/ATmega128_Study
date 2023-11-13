
/*
 * overflow_int.c
 *
 * Created: 2023-11-13 오후 9:55:58
 *  Author: HJ KIM
 */ 

#include "overflow_int.h"

int count = 0;
int state = 0;

ISR(TIMER0_OVF_vect)
{
	count++;
	if (count == 32)
	{
		// 32 overflow occur (0.5 sec passed)
		count = 0;
		state = !state;
		if (state) PORTB = 0x01;
		else PORTB = 0x00;
	}
}

void INIT_TCINT(void)
{
	TCCR0 |= 0x07;	// set pre-scaling factor to 1024
	TIMSK |= 0x01;	// allow overflow interrupt
	sei();
}