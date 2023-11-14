
/*									
 * tcint_example.c
 *
 * Created: 2023-11-14 오후 2:13:14
 *  Author: HJ KIM
 */ 

#include "tcint_example.h"

volatile unsigned char count = 0;

unsigned char TINT0_OVF_FLAG = 0;
unsigned char state = 0;

void init_ports(void)
{
	DDRC |= 0xFF;
	PORTC = 0xFF;	
}

void init_tcint(void)
{
	TIMSK |= (1 << TOIE0);
	TCCR0 |= (1 << CS00);
	TCCR0 |= (1 << CS01);
	TCCR0 |= (1 << CS02);
	TCNT0 = TCNT0_BASE;
	sei();
}

void tint_main()
{
	if (TINT0_OVF_FLAG == 1)
	{
		TINT0_OVF_FLAG = 0;
		// do something
		count++;
		if (count == 32)
		{
			if (state) PORTC = 0x00;
			else PORTC = 0xFF;
			state = !state;
			count = 0;
		}
	}
}

ISR(TIMER0_OVF_vect)
{
	cli();
	TINT0_OVF_FLAG = 1;
	TCNT0 = TCNT0_BASE;
	sei();
}