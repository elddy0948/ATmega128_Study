/*
 * Timer_Counter_8bits.c
 *
 * Created: 2023-11-13 오후 9:55:22
 * Author : HJ KIM
 */ 
<<<<<<< HEAD
#include "overflow_int.h"

int main(void)
{
	DDRC |= 0x01;
	PORTC = 0xFF;
	
	INIT_OF_TCINT();
	
    while (1) 
    {
=======
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
>>>>>>> 6b25de4a6c3123bffb209df752a8b58b2efad1fd
    }
}

