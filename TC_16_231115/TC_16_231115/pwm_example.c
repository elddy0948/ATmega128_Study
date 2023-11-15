
/*
 * pwm_example.c
 *
 * Created: 2023-11-15 오후 2:40:08
 *  Author: HJ KIM
 */ 

#include "pwm_example.h"

int ocr_value = 0x0055;

ISR(INT4_vect)
{
	cli();
	ocr_value += 20;
	if (ocr_value > 0x03FF) { ocr_value = 0x03FF; }
	OCR1C = ocr_value;
	sei();
}

ISR(INT5_vect)
{
	cli();
	ocr_value -= 20;
	if (ocr_value < 0) { ocr_value = 0; }
	OCR1C = ocr_value;
	sei();
}

ISR(INT6_vect)
{
	cli();
	TCCR1A |= (1 << COM1C0);
	sei();
}

void init_ports()
{
	DDRB |= 0x80;
	DDRG = 0xFF;
	PORTG = 0x0F;
}

void init_ext_int()
{
	EICRB |= (1 << ISC41) | (1 << ISC51) | (1 << ISC61);
	EIMSK |= (1 << INT4) | (1 << INT5) | (1 << INT6);
}

void init_tc_int()
{
	TCCR1A |= (1 << COM1C1);
	TCCR1A |= (1 << WGM11) | (1 << WGM10);
	TCCR1B |= (1 << CS12);
	OCR1C = ocr_value;
	TCNT1 = 0;
}