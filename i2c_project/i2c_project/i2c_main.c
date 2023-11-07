
/*
 * i2c_main.c
 *
 * Created: 2023-11-06 오후 6:14:10
 *  Author: HJ KIM
 */ 

#include "i2c_main.h"
#include "led.h"

uint8_t response = 0x00;
static uint8_t page_buffer[PAGE_MAX] = {0x00};

void i2c_start()
{
	CLK_OUT;
	DATA_OUT;
	DATA_HIGH;
	CLK_HIGH;
	_delay_us(6);
	DATA_LOW;
	_delay_us(6);
	CLK_LOW;
}

void i2c_stop()
{
	CLK_OUT;
	DATA_OUT;
	DATA_LOW;
	CLK_HIGH;
	_delay_us(6);
	DATA_HIGH;
	_delay_us(6);
	CLK_LOW;
}

void write_data(uint8_t data)
{
	uint8_t i;
	DATA_OUT;
	
	for (i = 0; i < 8; ++i)
	{
		loading_led();
		if (GET_BIT(data, i) == 0x80)
		{
			DATA_HIGH;
		}
		else 
		{
			DATA_LOW;
		}
		
		_delay_us(4);
		CLK_HIGH;
		_delay_us(4);
		CLK_LOW;
		_delay_us(4);
	}
}

uint8_t receive_response()
{
	uint8_t t;
	
	DATA_IN;
	_delay_us(4);
	CLK_HIGH;
	_delay_us(4);
	
	for (t = 0; t < 20; ++t)
	{	
		// Waiting for response
		if ((PIND & 0x02) == ACK)
		{
			ack_led();
			CLK_LOW;
			_delay_us(4);
			return ACK;
		}
	}
	
	noack_led();

	_delay_us(4);
	CLK_LOW;

	return NOACK;
}

uint8_t read_data()
{
	uint8_t received_data = 0x00;
	uint8_t i;
	
	DATA_IN;
	_delay_us(4);
	CLK_HIGH;
	_delay_us(4);
	
	for (i = 0; i < 8; ++i)
	{
		loading_led();
		received_data |= ((PIND >> 1) & 0x01);
		if (i != 7) 
		{ 
			received_data <<= 1;
		}
	}
	
	_delay_us(4);
	CLK_LOW;
	
	return received_data;
}

void send_response(uint8_t data)
{
	DATA_OUT;
	_delay_us(4);
	
	if (data == ACK)
	{
		ack_led();
		PORTD &= 0xFD;
	}
	else if (data == NOACK)
	{
		noack_led();
		PORTD |= 0x02;
	}
	
	_delay_us(4);
	CLK_HIGH;
	_delay_us(4);
	CLK_LOW;
}

void i2c_device_address_setup(uint8_t device_id, uint8_t rw)
{
	uint8_t device_address = 0x00;
	device_address |= rw;
	device_address |= device_id;
	write_data(device_address);
	
	response = receive_response();
	if (response == NOACK) { i2c_stop(); }
}

void i2c_address_setup(uint8_t address)
{
	write_data(address);
	
	response = receive_response();
	if (response == NOACK) { i2c_stop(); }
}

void i2c_byte_write(uint8_t data)
{
	write_data(data);
	response = receive_response();
}

void i2c_page_write(const uint8_t page[], uint8_t page_size)
{
	uint8_t data_index;
	uint8_t temp_data;
	
	for (data_index = 0; data_index < page_size; ++data_index)
	{
		temp_data = page[data_index];
		write_data(temp_data);
		
		response = receive_response();
	}
}

void i2c_byte_read()
{
	uint8_t received_data;

	received_data = read_data();
	
	send_response(NOACK);
	
	display_led(received_data);
}

void i2c_page_read(uint8_t page_size)
{
	uint8_t data_index;
	uint8_t received_data;
	
	for (data_index = 0; data_index < page_size; ++data_index)
	{
		received_data = read_data();
		page_buffer[data_index] = received_data;
		send_response(ACK);
		
		display_led(received_data);
	}
	
	send_response(NOACK);
}