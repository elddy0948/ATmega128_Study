
/*
 * rxtx_example.h
 *
 * Created: 2023-11-17 오후 2:05:50
 *  Author: HJ KIM
 */ 

#pragma once
#ifndef _RECEIVE_EXAMPLE_h
#define _RECEIVE_EXAMPLE_h

#define F_CPU 16000000L
#define BAUD_RATE_H 0
#define BAUD_RATE_L 8

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(INT6_vect);
ISR(USART0_RX_vect);

void init_ports(void);
void init_uart1(void);
void init_eint(void);

void menu_main(void);

void display_menu(void);
void display_withoutyou(void);
void led_blink(void);
void display_char(const char* ch);

#endif
