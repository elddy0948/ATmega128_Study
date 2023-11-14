
/*
 * int_runtime.c
 *
 * Created: 2023-11-14 오후 10:56:36
 *  Author: HJ KIM
 */ 

#include "int_runtime.h"

volatile unsigned long timer0_millis = 0;
volatile unsigned int timer0_microsec = 0;
uint8_t state = 0;

ISR(TIMER0_OVF_vect)
{
	unsigned long millis = timer0_millis;
	int microsec = timer0_microsec;
	
	millis += MILLIS_INCREMENT_PER_OVERFLOW;
	microsec += MICROSEC_INCREMENT_PER_OVERFLOW;
	
	millis += (microsec / 1000);
	microsec = microsec % 1000;
	
	timer0_millis = millis;
	timer0_microsec = microsec;
}

void init_ports(void)
{
	DDRB = 0x01;
	PORTB = 0x00;
}

void init_timer0(void)
{
	TCCR0 |= (1 << CS02);
	TIMSK |= (1 << TOIE0);
	
	sei();
}

unsigned long get_millis(void)
{
	unsigned long millis;
	uint8_t oldSREG = SREG;
	
	cli();
	
	millis = timer0_millis;
	SREG = oldSREG;
	
	return millis;
}

void int_runtime_main(unsigned long curr_time, unsigned long prev_time)
{
	curr_time = get_millis();
	if ((curr_time - prev_time) > 1000)
	{
		prev_time = curr_time;
		state = (state + 1) % 2;
		PORTB = state;
	}
}