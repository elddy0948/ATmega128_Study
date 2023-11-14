/*
 * interrupt_study.c
 *
 * Created: 2023-11-13 오후 9:10:39
 * Author : HJ KIM
 */ 

#include "led_int.h"

int main(void)
{
	INIT_PORT();
	INIT_INT0();
	
    while (1) 
    {
		led_int_main();
    }
	
	return 0;
}

