
/*
 * timer_main.h
 *
 * Created: 2023-11-15 오후 4:22:37
 *  Author: HJ KIM
 */ 
#pragma once
#ifndef _TIMER_MAIN_H
#define _TIMER_MAIN_H
#define F_CPU 16000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define TCNT0_BASE 131
#define MILLIS_INCREMENT_SIZE 2

ISR(INT4_vect);
ISR(INT5_vect);
ISR(TIMER0_OVF_vect);

void init_ports(void);
void init_ext_int(void);
void init_tc_int(void);

void display_digits(uint8_t position, uint8_t num);
void timer_main(void);

#endif
