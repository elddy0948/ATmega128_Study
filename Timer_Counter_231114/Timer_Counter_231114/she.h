
/*
 * she.h
 *
 * Created: 2023-11-14 오후 2:43:17
 *  Author: HJ KIM
 */ 


#pragma once
#ifndef _SHE_H
#define _SHE_H

#include <avr/io.h>
#include <avr/interrupt.h>

#define TCNT0_BASE 0
#define HER_BIRTHDAY 109
#define HIS_BIRTHDAY 53

void init_ports(void);
void init_ext_int(void);
void init_tc_int(void);

void start_timer2(void);
void start_timer0(void);
void stop_timer2(void);
void stop_timer0(void);

void she_main(void);

ISR(TIMER0_OVF_vect);
ISR(TIMER2_COMP_vect);

ISR(INT4_vect);
ISR(INT5_vect);
ISR(INT6_vect);
ISR(INT7_vect);

#endif /* SHE */
