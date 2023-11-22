
/*
 * interrupt_main.h
 *
 * Created: 2023-11-20 오후 2:40:57
 *  Author: HJ KIM
 */ 

#pragma once
#ifndef _INTERRUPT_MAIN_H
#define _INTERRUPT_MAIN_H

#define EINT4_FLAG 4
#define EINT5_FLAG 5
#define EINT6_FLAG 6
#define EINT7_FLAG 7

#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t EINT4_FLAG_BIT;
uint8_t EINT5_FLAG_BIT;
uint8_t EINT6_FLAG_BIT;
uint8_t EINT7_FLAG_BIT;

ISR(INT4_vect);
ISR(INT5_vect);
ISR(INT6_vect);
ISR(INT7_vect);

void EINT_enable_all(void);
void EINT4_init(void);
void EINT5_init(void);
void EINT6_init(void);
void EINT7_init(void);

#endif