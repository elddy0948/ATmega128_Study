
/*
 * int_runtime.h
 *
 * Created: 2023-11-14 오후 10:56:21
 *  Author: HJ KIM
 */ 
#pragma once
#ifndef _INT_RUNTIME_H
#define _INT_RUNTIME_H

#include <avr/io.h>
#include <avr/interrupt.h>

#define MILLIS_INCREMENT_PER_OVERFLOW 1
#define MICROSEC_INCREMENT_PER_OVERFLOW 24

ISR(TIMER0_OVF_vect);

void init_ports(void);
void init_timer0(void);
unsigned long get_millis(void);
void int_runtime_main(unsigned long curr_time, unsigned long prev_time);

#endif