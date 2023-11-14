
/*
 * tcint_example.h
 *
 * Created: 2023-11-14 오후 2:12:00
 *  Author: HJ KIM
 */ 

#pragma once
#ifndef _TCINT_EXAMPLE_H
#define _TCINT_EXAMPLE_H

#define TCNT0_BASE 100

#include <avr/io.h>
#include <avr/interrupt.h>

void init_ports(void);
void init_tcint(void);
void tint_main(void);

ISR(TIMER0_OVF_vect);

#endif