
/*
 * ovf_int.h
 *
 * Created: 2023-11-15 오후 12:16:21
 *  Author: HJ KIM
 */ 

#ifndef _OVF_INT_H
#define _OVF_INT_H

#include <avr/io.h>
#include <avr/interrupt.h>

#define TCNT1H_BASE 0xB6	
#define TCNT1L_BASE 0xC2

#define OCR3H_BASE 0x48
#define OCR3L_BASE 0xE5

#define TIMER3_COMPA_INTERRUPT 3
#define TIMER1_OVF_INTERRUPT 1

ISR(TIMER1_OVF_vect);
ISR(TIMER3_COMPA_vect);
void init_ports(void);
void init_tcint(void);

void process_interrupts(void);

#endif



