
/*
 * interrupt_main.c
 *
 * Created: 2023-11-20 오후 3:02:28
 *  Author: HJ KIM
 */ 

#include "interrupt_main.h"

uint8_t EINT4_FLAG_BIT = 0;
uint8_t EINT5_FLAG_BIT = 0;
uint8_t EINT6_FLAG_BIT = 0;
uint8_t EINT7_FLAG_BIT = 0;

ISR(INT4_vect)
{
	cli();
	EINT4_FLAG_BIT = 1;
	sei();
}

ISR(INT5_vect)
{
	cli();
	EINT5_FLAG_BIT = 1;
	sei();
}

ISR(INT6_vect)
{
	cli();
	EINT6_FLAG_BIT = 1;
	sei();
}

ISR(INT7_vect)
{
	cli();
	EINT7_FLAG_BIT = 1;
	sei();
}

void EINT_enable_all(void)
{
	EINT4_init();
	EINT5_init();
	EINT6_init();
	EINT7_init();
}
void EINT4_init(void) {
	EIMSK |= (1 << INT4);
	EICRB |= (1 << ISC41) | (1 << ISC40);
}
void EINT5_init(void) {
	EIMSK |= (1 << INT5);
	EICRB |= (1 << ISC51);	
}
void EINT6_init(void) {
	EIMSK |= (1 << INT6);
	EICRB |= (1 << ISC61) | (1 << ISC60);
}
void EINT7_init(void) {
	EIMSK |= (1 << INT7);
	EICRB |= (1 << ISC71);
}