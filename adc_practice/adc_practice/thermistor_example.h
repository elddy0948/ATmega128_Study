
/*
 * thermistor_example.h
 *
 * Created: 2023-11-20 오전 11:23:29
 *  Author: HJ KIM
 */ 

#pragma once
#ifndef _THERMISTOR_EXAMPLE_H
#define _THERMISTOR_EXAMPLE_H

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int ad_val;

ISR(TIMER0_OVF_vect);

void init_ports(void);
void init_timer(void);
void init_adc(void);
void display_adc(int val);

void adc_main(void);

#endif