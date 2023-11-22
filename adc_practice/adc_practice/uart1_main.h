
/*
 * uart1_main.h
 *
 * Created: 2023-11-20 오전 8:41:30
 *  Author: HJ KIM
 */

#pragma once
#ifndef _UART1_MAIN_H
#define _UART1_MAIN_H

#include <avr/io.h>

void uart1_init(void);
void uart1_transmit(char data);
uint8_t uart1_receive(void);
void uart1_print_string(char* str);
void uart1_print_1byte_number(uint8_t n);

#endif