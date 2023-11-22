
/*
 * free_running.h
 *
 * Created: 2023-11-20 오전 10:45:59
 *  Author: HJ KIM
 */ 

#pragma once
#ifndef _FREE_RUNNING_H
#define _FREE_RUNNING_H

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

void init_ports(void);
void init_adc(void);
void ad_disp(int pos, int val);
void adc_main(void);

#endif