
/*
 * uart0_main.h
 *
 * Created: 2023-11-17 오후 2:05:50
 *  Author: HJ KIM
 */ 

#pragma once
#ifndef _UART1_MAIN_H
#define _UART1_MAIN_H

#define BAUD_RATE_H 0
#define BAUD_RATE_L 103
#define NUMBER_OFFSET 0x30
#define MENU_ENABLE 1
#define MENU_DISABLE 0

#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t UART0_RX_FLAG_BIT;
uint8_t EINT4_ENABLE_FLAG_BIT;
uint8_t EINT5_ENABLE_FLAG_BIT;
uint8_t EINT6_ENABLE_FLAG_BIT;
uint8_t EINT7_ENABLE_FLAG_BIT;

ISR(USART0_RX_vect);

void UART0_init(void);
void UART0_display_menu(void);
void UART0_transmit(char data);
void UART0_transmit_string(const char* ch);
void UART0_transmit_voltage(int volt);
void UART0_clear(void);

#endif
