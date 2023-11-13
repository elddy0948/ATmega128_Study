
/*
 * comp_int.h
 *
 * Created: 2023-11-13 오후 10:44:17
 *  Author: HJ KIM
 */ 

#pragma once
#ifndef _COMP_INT_H
#define _COMP_INT_H

#include <avr/io.h>
#include <avr/interrupt.h>

// 1
void comp_int_main(void);
ISR(TIMER0_COMP_vect);
void INIT_TCINT(void);

// 2
ISR(TIMER1_COMPA_vect);
void INIT_PORT();
void INIT_TCINT2(void);

#endif
