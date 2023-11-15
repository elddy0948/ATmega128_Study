
/*
 * timer_main.c
 *
 * Created: 2023-11-15 오후 4:23:15
 *  Author: HJ KIM
 */

#include "timer_main.h"

uint16_t millis = 0;
uint8_t secs = 0;
uint8_t mins = 0;
uint8_t hours = 0;
uint8_t numbers[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
uint8_t position = 0;

ISR(INT4_vect)
{
	cli();
	PORTC = 0xFE;
	if (position == 0)
	{
		mins++;
		mins = mins % 60;
	}
	if (position == 1)
	{
		mins += 10;
		mins = mins % 60;
	}
	if (position == 2)
	{
		hours++;
		hours = hours % 24;
	}
	if (position == 3)
	{
		hours += 10;
		hours = hours % 24;
	}
	sei();
}

ISR(INT5_vect)
{
	cli();
	PORTC = 0xFC;
	position = (position + 1) % 4;
	sei();
}

ISR(TIMER0_OVF_vect)
{
	cli();
	millis += MILLIS_INCREMENT_SIZE;
	secs += (millis / 1000);
	millis = (millis % 1000);
	
	mins += (secs / 60);
	secs = (secs % 60);
	
	hours += (mins / 60);
	mins = (mins % 60);
	
	hours = hours % 24;
	TCNT0 = TCNT0_BASE;
	sei();
}

void init_ports(void)
{
	DDRC |= 0xFF;
	DDRB |= 0xF0;
	DDRD |= 0xF0;
	DDRG |= 0x0F;
	
	PORTC = 0xFF;
	PORTB = 0x00;
	PORTD = 0x00;
	PORTG = 0x0F;
}

void init_ext_int()
{
	EICRB |= (1 << ISC41) | (1 << ISC51);
	EIMSK |= (1 << INT4) | (1 << INT5);
}

void init_tc_int()
{
	TCCR0 |= (1 << CS02) | (1 << CS01);
	TCNT0 = TCNT0_BASE;
	TIMSK |= (1 << TOIE0);
}

void display_digits(uint8_t position, uint8_t num)
{
	PORTG &= 0xF0;
	PORTG |= (1 << (position - 1));
	PORTD = ((numbers[num] & 0x0F) << 4) | (PORTD & 0x0F);
	PORTB = (numbers[num] & 0x70) | (PORTB & 0x0F);
}

void timer_main()
{
	uint8_t i = 0;
	for (i = 0; i < 2; ++i)
	{
		display_digits(1, hours / 10);
		_delay_ms(5);
 		display_digits(2, hours % 10);
 		_delay_ms(5);
 		display_digits(3, mins / 10);
 		_delay_ms(5);
 		display_digits(4, mins % 10);
 		_delay_ms(5);
	}
}