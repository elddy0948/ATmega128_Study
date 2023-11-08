/*
 * i2c_project.c
 *
 * Created: 2023-11-06 오후 6:06:54
 * Author : HJ KIM
 */ 

#define F_CPU 16000000L

#include "i2c_main.h"
#include <util/delay.h>

const uint8_t tmp_write = 0xFF;
const uint8_t tmp_page[5] = {0xFF, 0xFE, 0xFD, 0xFC, 0xFB};

int main(void)
{
	int address_to_write = 513;
	
	CLK_OUT;
	DATA_OUT;
	
	DDRC = 0xFF;
	DDRE = 0x00;
	PORTC = 0xFF;
	
    while (1) 
    {
		if ((PINE & 0x10) == 0)
		{
			i2c_start();
			
			i2c_device_address_setup(DEVICE_ID, address_to_write, DA_WRITE);	
			i2c_address_setup(address_to_write);
 			i2c_byte_write(tmp_write);
			 
 			i2c_stop();
			 _delay_ms(3000);
		}
		else if ((PINE & 0x20) == 0)
		{
			i2c_start();
			
			i2c_device_address_setup(DEVICE_ID,address_to_write, DA_WRITE);
			i2c_address_setup(address_to_write);
			i2c_page_write(tmp_page, 5);
			
			i2c_stop();
			_delay_ms(3000);
		}
		else if ((PINE & 0x40) == 0)
		{
			i2c_start();
			i2c_device_address_setup(DEVICE_ID, address_to_write, DA_WRITE);
			i2c_address_setup(address_to_write);
			
			i2c_start();
			i2c_device_address_setup(DEVICE_ID, address_to_write, DA_READ);
			i2c_byte_read();
			
			i2c_stop();
			_delay_ms(3000);
		}
		else if ((PINE & 0x80) == 0)
		{
			i2c_start();
			i2c_device_address_setup(DEVICE_ID,address_to_write, DA_WRITE);
			i2c_address_setup(address_to_write);
			
			i2c_start();
			i2c_device_address_setup(DEVICE_ID, address_to_write, DA_READ);			
			i2c_page_read(5);
			
			i2c_stop();
			_delay_ms(3000);
		}
    }
}

