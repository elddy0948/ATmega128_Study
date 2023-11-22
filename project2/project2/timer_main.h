
/*
 * timer_main.h
 *
 * Created: 2023-11-20 오후 3:18:42
 *  Author: HJ KIM
 */ 

#pragma once
#ifndef _TIMER_MAIN_H
#define _TIMER_MAIN_H

#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>

#define TCNT2_BASE 6
#define TCNT0_BASE 131
#define TIMER0_FOR_TIMER3 1
#define TIMER0_FOR_ADC 2

#define OCR1_H 0x13
#define OCR1_L 0x87

#define OCR3_H 0x33	
#define OCR3_L 0x32

uint8_t TIMER2_OVF_FLAG_BIT;
uint8_t TIMER1_COMPA_FLAG_BIT;
uint8_t TIMER0_OVF_FLAG_BIT;
int timer0_count;

ISR(TIMER0_OVF_vect);
ISR(TIMER2_OVF_vect);
ISR(TIMER1_COMPA_vect);

void TIMER0_ovf_init(uint16_t cnt);
void TIMER1_compa_init(void);
void TIMER2_ovf_init(void);
void TIMER3_pwm_init(void);
void TIMER3_pc_pwm_init(void);

void TIMER_clear_all(void);
void TIMER0_clear(void);
void TIMER1_clear(void);
void TIMER2_clear(void);
void TIMER3_clear(void);

#endif
