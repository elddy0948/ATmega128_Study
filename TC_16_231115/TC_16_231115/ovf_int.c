
/*
 * ovf_int.c
 *
 * Created: 2023-11-15 오후 12:16:34
 *  Author: HJ KIM
 */ 

#include "ovf_int.h"

uint8_t state1 = 0;
uint8_t state3 = 0;
uint8_t interrupt_flag = 0xFF;

ISR(TIMER1_OVF_vect)
{
	cli();
	TCNT1H = TCNT1H_BASE;
	TCNT1L = TCNT1L_BASE;
	interrupt_flag = TIMER1_OVF_INTERRUPT;

	sei();
}

ISR(TIMER3_COMPA_vect)
{
	cli();
	TCNT3H = 0x00;
	TCNT3L = 0x00;
	interrupt_flag = TIMER3_COMPA_INTERRUPT;
	sei();
}

void init_ports(void)
{
	DDRC = 0xFF;
	PORTC = 0xFF;
}

void init_tcint(void)
{
	TIMSK |= (1 << TOIE1);
	ETIMSK |= (1 << OCIE3A);
	
	TCCR1B |= (1 << CS12);
	
	TCCR3B |= (1 << WGM32); // CTC
	TCCR3B |= (1 << CS30);
	TCCR3B |= (1 << CS32);
	
	TCNT1H = TCNT1H_BASE;
	TCNT1L = TCNT1L_BASE;
	OCR3AH = OCR3H_BASE;
	OCR3AL = OCR3L_BASE;
}

void process_interrupts()
{
	switch(interrupt_flag)
	{
		case TIMER1_OVF_INTERRUPT:
		interrupt_flag = 0xFF;
		if (state1) PORTC = 0xA0;
		else PORTC = 0x0A;
		state1 = !state1;
		break;
		case TIMER3_COMPA_INTERRUPT:
		interrupt_flag = 0xFF;
		if (state3) PORTC = 0xF0;
		else PORTC = 0x0F;
		state3 = !state3;
		break;
		default:
		break;
	}
}