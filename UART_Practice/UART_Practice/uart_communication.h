
/*
 * uart_communication.h
 *
 * Created: 2023-11-05 오후 11:22:16
 *  Author: HJ KIM
 */ 

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>
#define _BV(bit) (1 << (bit))

typedef unsigned char u8;

void UART1_init();
void UART1_transmit(char data);
u8 UART1_receive();
int UART_main();