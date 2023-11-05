
/*
 * debounce_prac.h
 *
 * Created: 2023-11-05 오후 10:01:20
 *  Author: HJ KIM
 */ 

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

typedef unsigned char u8;

#define OUTPUT 0xFF;
#define RISING_EDGE_CHECK(prev, curr) (curr == 1 && prev == 0)

// solution 1 (using delay)
u8 circular_shift_left(u8 pattern);
int debounce_main();

// solution 2 (get input twice)
int get_button_state();
int get_input_twice();