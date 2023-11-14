
/*
 * overflow_int.c
 *
 * Created: 2023-11-13 오후 9:55:58
 *  Author: HJ KIM
 */ 

#include "overflow_int.h"

volatile int overflow_count = 0;
volatile int sw_state = 0;

ISR(TIMER0_OVF_vect)
{
	overflow_count++;
	if (overflow_count == 32)
	{
		// 32 overflow occur (0.5 sec passed)
		overflow_count = 0;
		sw_state = !sw_state;
		if (sw_state) PORTC = 0xFE;
		else PORTC = 0xFF;
	}
}

void INIT_OF_TCINT(void)
{
	TCCR0 |= 0x07;	// set pre-scaling factor to 1024
	TIMSK |= 0x01;	// allow overflow interrupt
	sei();
}