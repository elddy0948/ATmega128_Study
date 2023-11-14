/*
 * Timer_Counter_231114.c
 *
 * Created: 2023-11-14 오전 9:55:19
 * Author : HJ KIM
 */ 

#define F_CPU 16000000

#include "she.h"

void main(void)
{
	init_ports();
	init_ext_int();
	init_tc_int();
	
	sei();
	
    while (1) 
    {
		she_main();
    }
}

