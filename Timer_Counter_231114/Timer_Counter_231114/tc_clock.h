
/*
 * tc_clock.h
 *
 * Created: 2023-11-14 오후 12:00:12
 *  Author: HJ KIM
 */ 

#pragma once
#ifndef _TC_CLOCK_H
#define _TC_CLOCK_H

#define SEGMENT_OUTPUT 0xF0
#define DIGITS_SELECTION_OUTPUT 0x0F

#include <avr/io.h>
#include <avr/interrupt.h>

void init_ports(void);
void init_tcint(void);
void dispaly_digits(int pos, int num);
void clock_main(void);

ISR(TIMER0_OVF_vect);

#endif
