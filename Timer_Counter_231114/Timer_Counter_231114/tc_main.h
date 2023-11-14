
/*
 * tc_main.h
 *
 * Created: 2023-11-14 오전 9:56:34
 *  Author: HJ KIM
 */

#pragma once
#ifndef _TC_MAIN_H
#define _TC_MAIN_H

#define TCNT_INIT_VALUE 37
#define OCR0_VALUE 155

#include <avr/io.h>
#include <avr/interrupt.h>

void led_shifting(void);

void init_port(void);
void init_tcint(void);
void init_tc2int(void);
void tc_event(void);

ISR(TIMER0_OVF_vect);

void init_compint(void);
ISR(TIMER0_COMP_vect);

ISR(TIMER2_OVF_vect);


#endif
