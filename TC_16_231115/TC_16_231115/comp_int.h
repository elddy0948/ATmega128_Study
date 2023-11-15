
/*
 * comp_int.h
 *
 * Created: 2023-11-15 오후 12:11:13
 *  Author: HJ KIM
 */

#ifndef _COMP_INT_H
#define _COMP_INT_H

#include <avr/io.h>
#include <avr/interrupt.h>

#define OCRH_BASE 0x80
#define OCRL_BASE 0x00

ISR(TIMER1_COMPA_vect);
void init_ports(void);
void init_tcint(void);

#endif


