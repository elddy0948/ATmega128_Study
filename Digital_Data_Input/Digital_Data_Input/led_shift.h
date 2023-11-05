
/*
 * led_shift.h
 *
 * Created: 2023-11-05 오후 9:40:49
 *  Author: HJ KIM
 */ 

#define F_CPU 16000000L

#define OUTPUT 0xFF; // 1111 1111

#include <avr/io.h>
#include <util/delay.h>

typedef unsigned char u8;

char circular_shift_left(char pattern);
int run_circular_shift();