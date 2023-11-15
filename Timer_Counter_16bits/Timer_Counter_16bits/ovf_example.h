
/*
 * ovf_example.h
 *
 * Created: 2023-11-15 오전 8:53:38
 *  Author: HJ KIM
 */ 
#pragma once
#ifndef _OVF_EXAMPLE_H
#define _OVF_EXAMPLE_H

int state = 0;

ISR(TIMER1_OVF_vect)
{
	state = !state;
	if (state) PORTC = 0xFE;
	else PORTC = 0xFF;
}

void init_ports(void)
{
	DDRC = 0x01;
	PORTC = 0xFF;
	
	TCCR1B |= (1 << CS12);
	TIMSK |= (1 << TOIE1);
}

#endif

