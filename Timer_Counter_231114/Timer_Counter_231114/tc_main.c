
/*
 * tc_main.c
 *
 * Created: 2023-11-14 오전 9:57:24
 *  Author: HJ KIM
 */ 

#include "tc_main.h"

unsigned char led = 0xFF;
unsigned char TCINT0_FLAG = 0;
unsigned char TCINT2_FLAG = 0;
unsigned char COMPINT0_FLAG = 0;

unsigned char state0 = 0;
unsigned char state2 = 0;

void led_shifting(void)
{
	led = led << 1;
	led = led | 0x01;
	if (led == 0xFF) led = 0xFE;
	PORTC = led;
}

void led_blinking(void)
{
	if (state2) PORTC &= 0xFE;
	else PORTC |= 0x01;
	
	if (state0) PORTC &= 0x7F;
	else PORTC |= 0x80;
}

void init_port(void)
{
	DDRC = 0xFF;
	PORTC = 0xFF;
}

void init_tcint(void)
{
	TIMSK |= (1 << TOIE0);
	TCCR0 |= (1 << CS00);
	TCCR0 |= (1 << CS01);
	TCCR0 |= (1 << CS02);
	TCNT0 = TCNT_INIT_VALUE;
	sei();
}

void init_tc2int(void)
{
	TIMSK |= (1 << TOIE2);
	TCCR2 |= (1 << CS20);
	TCCR2 |= (1 << CS22);
	TCCR2 |= (1 << COM20);
	TCNT0 = 0;
	sei();
}

void tc_event(void)
{
	if (TCINT0_FLAG == 1)
	{
		TCINT0_FLAG = 0;
		led_shifting();
	}
	if (COMPINT0_FLAG == 1)
	{
		COMPINT0_FLAG = 0;
		led_blinking();
		state0 = !state0;
	}
	if (TCINT2_FLAG == 1)
	{
		TCINT2_FLAG = 0;
		led_blinking();
		state2 = !state2;
	}
}

ISR(TIMER0_OVF_vect)
{
	cli();
	TCNT0 = TCNT_INIT_VALUE;
	TCINT0_FLAG = 1;
	sei();
}

void init_compint(void)
{
	TIMSK |= (1 << OCIE0);
	TCCR0 |= (1 << CS00);
	TCCR0 |= (1 << CS01);
	TCCR0 |= (1 << CS02);
	TCCR0 |= (1 << WGM01);
	OCR0 = OCR0_VALUE;
	TCNT0 = 0;
	sei();
}

ISR(TIMER0_COMP_vect)
{
	cli();
	COMPINT0_FLAG = 1;
	sei();
}

ISR(TIMER2_OVF_vect)
{
	cli();
	TCINT2_FLAG = 1;
	sei();
}