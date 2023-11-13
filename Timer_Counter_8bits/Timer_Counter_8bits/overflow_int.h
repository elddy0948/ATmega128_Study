
/*
 * overflow_int.h
 *
 * Created: 2023-11-13 오후 9:55:41
 *  Author: HJ KIM
 */ 

#pragma once
#ifndef _OVERFLOW_INT_H
#define _OVERFLOW_INT_H

#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER0_OVF_vect);
void INIT_TCINT(void);

#endif