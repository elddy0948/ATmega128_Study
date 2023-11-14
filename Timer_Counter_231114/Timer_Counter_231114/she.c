
/*
 * she.c
 *
 * Created: 2023-11-14 오후 2:45:55
 *  Author: HJ KIM
 */ 

#include "she.h"

unsigned char EINT4_FLAG = 0;
unsigned char EINT5_FLAG = 0;
unsigned char EINT6_FLAG = 0;
unsigned char EINT7_FLAG = 0;

unsigned char TINT0_OVF_FLAG = 0;
unsigned char TINT2_COMP_FLAG = 0;

unsigned char state0 = 0;
unsigned char state2 = 0;

unsigned char her_count = 0;
unsigned char his_count = 0;

void init_ports(void)
{
	DDRC |= 0xFF;
	PORTC = 0xFF;
}

void init_ext_int(void)
{
	EIMSK |= 0xF0;
	EICRB = 0b10111110;	
}

void init_tc_int(void)
{
	TIMSK |= (1 << TOIE0);
	TIMSK |= (1 << OCIE2);
	OCR2 = HER_BIRTHDAY;
	TCNT0 = HIS_BIRTHDAY;
}

void start_timer2(void)
{
	TCCR2 |= (1 << CS20);
	TCCR2 |= (1 << CS22);
	TCCR2 |= (1 << WGM21); // CTC
}

void start_timer0(void)
{
	TCCR0 |= (1 << CS00);
	TCCR0 |= (1 << CS01);
	TCCR0 |= (1 << CS02);
}

void stop_timer2(void)
{
	TCCR2 &= 0xF8;
}

void stop_timer0(void)
{
	TCCR0 &= 0xF8;
}

void she_main(void)
{
	if (EINT4_FLAG == 1)
	{
		EINT4_FLAG = 0;
		start_timer2();
	}
	if (EINT5_FLAG == 1)
	{
		EINT5_FLAG = 0;
		stop_timer2();
	}
	if (EINT6_FLAG == 1)
	{
		EINT6_FLAG = 0;
		start_timer0();
	}
	if (EINT7_FLAG == 1)
	{
		EINT7_FLAG = 0;
		stop_timer0();
	}
	if (TINT0_OVF_FLAG == 1)
	{
		TINT0_OVF_FLAG = 0;
		his_count++;
		if (his_count == 10)
		{
			if (state0) PORTC = 0xF0;
			else PORTC = 0x0F;
			state0 = !state0;
			his_count = 0;
		}
		
	}
	if (TINT2_COMP_FLAG == 1)
	{
		TINT2_COMP_FLAG = 0;
		her_count++;
		if (her_count == 100)
		{
			if (state2) PORTC = 0xAA;
			else PORTC = 0x55;
			state2 = !state2;
			her_count = 0;
		}
		
	}
}

ISR(TIMER0_OVF_vect)
{
	cli();
	TCNT0 = HIS_BIRTHDAY;
	TINT0_OVF_FLAG = 1;
	sei();
}

ISR(TIMER2_COMP_vect)
{
	cli();
	TCNT2 = 0;
	TINT2_COMP_FLAG = 1;
	sei();	
}

ISR(INT4_vect)
{
	cli();
	EINT4_FLAG = 1;
	sei();
}

ISR(INT5_vect)
{
	cli();
	EINT5_FLAG = 1;
	sei();
}

ISR(INT6_vect)
{
	cli();
	EINT6_FLAG = 1;
	sei();
}

ISR(INT7_vect)
{
	cli();
	EINT7_FLAG = 1;
	sei();	
}