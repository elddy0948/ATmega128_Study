
/*
 * led_int.h
 *
 * Created: 2023-11-13 오후 9:21:12
 *  Author: HJ KIM
 */ 
#pragma once
#ifndef _LED_INT_H
#define _LED_INT_H

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(INT0_vect);
void INIT_PORT(void);
void INIT_INT0(void);
void led_int_main(void);

#endif /* _LED_INT_H */