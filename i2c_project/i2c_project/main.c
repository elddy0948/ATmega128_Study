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
	uint8_t device_address = 0xA0;
	uint8_t address_to_write = 0x00;
	
	CLK_OUT;
	DATA_OUT;
	
	DDRC = 0xFF;
	//DDRE &= 0x0F;
	DDRE = 0x00;
	PORTC = 0xFF;
	
    while (1) 
    {
		if ((PINE & 0x10) == 0)
		{
			i2c_start();
			
			device_address &= 0xFE;
			i2c_device_address_setup(device_address);
			_delay_ms(1000);
			i2c_address_setup(address_to_write);
			_delay_ms(1000);
			i2c_byte_write(tmp_write);
			_delay_ms(1000);
			i2c_stop();
		}
		else if ((PINE & 0x20) == 0)
		{
			i2c_start();
			
			device_address &= 0xFE;
			i2c_device_address_setup(device_address);
			_delay_ms(1000);
			i2c_address_setup(address_to_write);
			_delay_ms(1000);
			i2c_page_write(tmp_page, 5);
			_delay_ms(1000);
			i2c_stop();
		}
		else if ((PINE & 0x80) == 0)
		{
			i2c_start();
			
			device_address &= 0xFE;
			i2c_device_address_setup(device_address);
			i2c_address_setup(address_to_write);
			
			i2c_start();
			
			device_address |= 0x01;
			i2c_device_address_setup(device_address);
			
			i2c_byte_read();
			
			i2c_stop();
		}
    }
}

