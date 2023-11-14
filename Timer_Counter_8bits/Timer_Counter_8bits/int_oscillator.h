
/*
 * int_oscillator.h
 *
 * Created: 2023-11-14 오후 10:43:44
 *  Author: HJ KIM
 */ 

#pragma once
#ifndef _INT_OSCILLATOR_H
#define _INT_OSCILLATOR_H

#include <avr/io.h>
#include <avr/interrupt.h>

void init_port(void);
void init_timer0(void);

#endif /* _INT_OSCILLATOR_H */