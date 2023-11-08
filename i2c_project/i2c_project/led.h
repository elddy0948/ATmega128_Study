
/*
 * led.h
 *
 * Created: 2023-11-06 오후 10:43:53
 *  Author: HJ KIM
 */ 

#pragma once
#ifndef _LED_H
#define _LED_H

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

typedef unsigned char uint8_t;

uint8_t shift_left(uint8_t pattern);

void loading_led();
void display_led(uint8_t led_to_display);

#endif /* _LED_H */
