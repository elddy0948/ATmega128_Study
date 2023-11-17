
/*
 * receive_example.h
 *
 * Created: 2023-11-17 오후 12:40:09
 *  Author: HJ KIM
 */ 


#pragma once
#ifndef _RECEIVE_EXAMPLE_h
#define _RECEIVE_EXAMPLE_h

#define F_CPU 16000000L
#define BAUD_RATE_H 0
#define BAUD_RATE_L 103

#include <avr/io.h>
#include <util/delay.h>

void init_ports(void);
void init_uart1(void);
void uart1_main(void);

#endif
