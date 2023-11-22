
/*
 * variable_resistance.h
 *
 * Created: 2023-11-20 오전 10:29:17
 *  Author: HJ KIM
 */ 


#pragma once
#ifndef _VARIABLE_RESISTANCE_H
#define _VARIABLE_RESISTANCE_H

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

void init_ports(void);
void init_adc(void);
void ad_disp(int val);
void adc_main(void);

#endif
