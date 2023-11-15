/*
 * TC_16_231115.c
 *
 * Created: 2023-11-15 오전 11:17:28
 * Author : HJ KIM
 */ 
#include "timer_main.h"

int main(void)
{
	init_ports();
	init_ext_int();
	init_tc_int();
	sei();
    while (1) 
    {
		timer_main();
    }
}

