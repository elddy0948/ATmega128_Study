
/*
 * seven_segments.h
 *
 * Created: 2023-11-20 오후 2:43:19
 *  Author: HJ KIM
 */ 

#pragma once
#ifndef _SEVEN_SEGMENTS_H
#define _SEVEN_SEGMENTS_H

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

uint32_t digits_display;

void SEG_init(void);
void SEG_display_4byte(uint32_t val);
void SEG_display_birthday(void);
void SEG_display_digit(int pos, int val);
void SEG_display_adc(int val);

#endif
