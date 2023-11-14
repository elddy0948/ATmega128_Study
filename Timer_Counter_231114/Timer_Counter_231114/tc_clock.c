
/*
 * tc_clock.c
 *
 * Created: 2023-11-14 오후 12:01:39
 *  Author: HJ KIM
 */ 
#include "tc_clock.h"

unsigned int millis = 0;
unsigned int secs = 0;
const unsigned char seg_pat[10]= {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,0x7f, 0x6f};

void init_ports(void)
{
	DDRB |= SEGMENT_OUTPUT;
	DDRD |= SEGMENT_OUTPUT;
	DDRG |= DIGITS_SELECTION_OUTPUT;
	PORTB = 0x00;
	PORTD = 0x00;
	PORTG = 0x00;
}

void init_tcint(void)
{
	TIMSK |= (1 << TOIE0);
	TCCR0 |= (1 << CS02);
	TCNT0 = 0;
	sei();
}

void dispaly_digits(int pos, int num)
{
	PORTG |= 0x0F;
	PORTG &= ~(1 << (pos - 1));
	PORTD = ((seg_pat[num] & 0x0F) << 4) | (PORTD & 0x0F);
	PORTB = (seg_pat[num] & 0x70) | (PORTB & 0X0F);
}

void clock_main(void)
{
	int buf = 0;
	dispaly_digits(1, secs / 1000);
	buf = secs % 1000;
	dispaly_digits(2, buf / 100);
	buf = secs % 100;
	dispaly_digits(3, buf / 10);
	dispaly_digits(4, buf % 10);
}

ISR(TIMER0_OVF_vect)
{
	millis++;
	
	secs = (millis / 1000);
	millis = millis % 1000;
}