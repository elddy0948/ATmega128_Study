
/*
 * pwm_example.h
 *
 * Created: 2023-11-15 오후 2:39:53
 *  Author: HJ KIM
 */ 

#ifndef _PWM_EXAMPLE_H
#define _PWM_EXAMPLE_H

#include <avr/io.h>
#include <avr/interrupt.h>

#define OCRH_BASE 0x01
#define OCRL_BASE 0xFF

ISR(INT4_vect);
ISR(INT5_vect);
ISR(INT6_vect);

void init_ports(void);
void init_ext_int(void);
void init_tc_int(void);

#endif