
/*
 * basic_uart.h
 *
 * Created: 2023-11-16 오후 10:42:57
 *  Author: HJ KIM
 */ 

#pragma once
#ifndef _BASIC_UART_H
#define _BASIC_UART_H

#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(USART1_RX_vect);
ISR(USART1_TX_vect);
ISR(USART1_UDRE_vect);

void uart1_init(void);
void uart1_interrupt_init(void);

void uart1_transmit(uint8_t data);
uint8_t uart1_receive(void);

void uart1_print_string(char *str);

#endif