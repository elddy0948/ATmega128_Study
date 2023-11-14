/*
 * Timer_Counter_8bits.c
 *
 * Created: 2023-11-13 오후 9:55:22
 * Author : HJ KIM
 */ 
#include "int_runtime.h"

int main(void)
{
	init_ports();
	init_timer0();
	
	unsigned long curr_time, prev_time;
	prev_time = get_millis();
	
    while (1) 
    {
		int_runtime_main(curr_time, prev_time);
    }
}

