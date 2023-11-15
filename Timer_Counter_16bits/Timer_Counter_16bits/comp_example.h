
/*
 * comp_example.h
 *
 * Created: 2023-11-15 오전 8:48:13
 *  Author: HJ KIM
 */ 

#pragma once
#ifndef _COMP_EXAMPLE_H
#define _COMP_EXAMPLE_H

#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER1_COMPA_vect);
void init_ports(void);
void init_tci(void);

#endif
