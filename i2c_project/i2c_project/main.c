/*
 * i2c_project.c
 *
 * Created: 2023-11-06 오후 6:06:54
 * Author : HJ KIM
 */ 

#include "i2c_main.h"
#include <util/delay.h>

const uint8_t tmp_write = 0xFF;
const uint8_t tmp_page[5] = {0xFF, 0xFE, 0xFD, 0xFC, 0xFB};
const uint16_t address_to_write = 513;
uint8_t prev_state = 0x00;
uint8_t curr_state = 0x00;

void main(void)
{
	CLK_OUT;
	DATA_OUT;
	
	DDRC = 0xFF;
	DDRE = 0x00;
	PORTC = 0xFF;
	
    while (1) 
    {
		curr_state = PINE;
		
		if (ALL_SWITCH_OFF(prev_state) && SWITCH4_ON(curr_state))
		{
			i2c_start();
			
			i2c_device_address_setup(DEVICE_ID, address_to_write, DA_WRITE);	
			i2c_address_setup(address_to_write);
 			i2c_byte_write(tmp_write);
			 
 			i2c_stop();
		}
		if (ALL_SWITCH_OFF(prev_state) && SWITCH5_ON(curr_state))
		{
			i2c_start();
			
			i2c_device_address_setup(DEVICE_ID,address_to_write, DA_WRITE);
			i2c_address_setup(address_to_write);
			i2c_page_write(tmp_page, PAGE_SIZE(tmp_page));
			
			i2c_stop();
		}
		if (ALL_SWITCH_OFF(prev_state) && SWITCH6_ON(curr_state))
		{
			i2c_start();
			i2c_device_address_setup(DEVICE_ID, address_to_write, DA_WRITE);
			i2c_address_setup(address_to_write);
			
			i2c_start();
			i2c_device_address_setup(DEVICE_ID, address_to_write, DA_READ);
			i2c_byte_read();
			
			i2c_stop();
		}
		if (ALL_SWITCH_OFF(prev_state) && SWITCH7_ON(curr_state))
		{
			i2c_start();
			i2c_device_address_setup(DEVICE_ID,address_to_write, DA_WRITE);
			i2c_address_setup(address_to_write);
			
			i2c_start();
			i2c_device_address_setup(DEVICE_ID, address_to_write, DA_READ);			
			i2c_page_read(5);
			
			i2c_stop();
		}
		
		prev_state = curr_state;
    }
	return;
}

