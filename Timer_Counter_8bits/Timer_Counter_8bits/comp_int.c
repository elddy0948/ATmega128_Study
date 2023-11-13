
/*
 * comp_int.c
 *
 * Created: 2023-11-13 오후 10:44:28
 *  Author: HJ KIM
 */ 
#include "comp_int.h"

volatile int count = 0;
int state = 0;

void comp_int_main(void)
{
	if (count == 0)
	{
		count = 0;
		state = !state;
		if (state) PORTB = 0x01;
		else PORTB = 0x00;
	}
}

ISR(TIMER0_COMP_vect)
{
	count++;
	TCNT0 = 0;
}

void INIT_TCINT(void)
{
	TCCR0 |= 0x07;
	OCR0 = 128;
	TIMSK |= 0x02;
	sei();
}

ISR(TIMER1_COMPA_vect)
{
	count++;
}

void INIT_PORT()
{
	DDRB |= 0x10;	// set wave output pin (PORTB4) to output
	PORTB = 0x00;	// start with led off
}

void INIT_TCINT2(void)
{
	TCCR0 |= 0x07;	// pre-scaling factor is 1024
	TCCR0 |= 0x08;	// CTC mode
	OCR0 = 255;
	TCCR0 |= 0x10;	// set COM01 : 0, COM00 : 1
	sei();
}