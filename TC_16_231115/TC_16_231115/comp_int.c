
/*
 * comp_int.c
 *
 * Created: 2023-11-15 오후 12:13:05
 *  Author: HJ KIM
 */ 

#include "comp_int.h"

unsigned int state = 0;

ISR(TIMER1_COMPA_vect)
{	
	cli();
	state = !state;
	if (state) PORTC = 0xFE;
	else PORTC = 0xFF;
	TCNT1H = 0x00;
	TCNT1L = 0x00;
	sei();
}

void init_ports(void)
{
	DDRC = 0xFF;
	PORTC = 0xFF;	
}

void init_tcint(void)
{
	TCCR1B |= (1 << CS12);
	TCCR1B |= (1 << WGM12);	// CTC
	TIMSK |= (1 << OCIE1A);
	
	OCR1AH = OCRH_BASE;
	OCR1AL = OCRL_BASE;
}
