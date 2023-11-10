
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

void i2c_start(void)
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

void i2c_stop(void)
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
	uint8_t data_buffer = data;

	DATA_OUT;
	
	for (i = 0; i < 7; ++i)
	{
		loading_led();
		if (GET_BIT(data_buffer, i) == 0x80)
		{
			DATA_HIGH;
		}
		else 
		{
			DATA_LOW;
		}
		
		_delay_us(3);
		CLK_HIGH;
		_delay_us(5);
		CLK_LOW;
		_delay_us(5);
	}
	
	if (((data_buffer << i) & 0x80) == 0x80) DATA_HIGH;
	else DATA_LOW;
	
	_delay_us(3);
	CLK_HIGH;
	_delay_us(5);
	CLK_LOW;
	_delay_us(5);
}

uint8_t receive_response(void)
{
	uint8_t t;
	
	DATA_IN;
	CLK_HIGH;
	
	for (t = 0; t < 20; ++t)
	{	
		if ((PIND & 0x02) == ACK)
		{
			_delay_us(6);			
			CLK_LOW;
			DATA_OUT;
			_delay_us(6);
			return ACK;
		}
	}
	
	_delay_us(6);
	CLK_LOW;
	DATA_OUT;
	_delay_us(6);
	
	return NOACK;
}

uint8_t read_data(void)
{
	uint8_t data_buffer = 0x00;
	uint8_t i;
	
	DATA_IN;
	
	for (i = 0; i < 8; ++i)
	{
		loading_led();
		CLK_HIGH;
		_delay_us(10);
		CLK_LOW;
		data_buffer |= ((PIND >> 1) & 0x01);
		if (i != 7) 
		{ 
			data_buffer <<= 1;
		}
		_delay_us(3);
	}
	
	return data_buffer;
}

void send_response(uint8_t data)
{
	DATA_OUT;

	if (data == ACK)
		SEND_ACK;
	else if (data == NOACK)
		SEND_NOACK;
	
	_delay_us(3);
	CLK_HIGH;
	_delay_us(5);
	CLK_LOW;
	_delay_us(5);
}

void i2c_device_address_setup(uint8_t device_id, uint16_t target_address, uint8_t rw)
{
	uint8_t device_address = 0x00;

	if (((target_address >> 9) & 0x0001) == 0x0001)
		SET_A9(device_address);
	else if (((target_address >> 8) & 0x0001) == 0x0001)
		SET_A8(device_address);
	
	device_address |= rw;
	device_address |= device_id;
	
	write_data(device_address);
	
	response = receive_response();
	
	if (response == NOACK) { i2c_stop(); }
}

void i2c_address_setup(uint16_t target_address)
{
	uint8_t address = (uint8_t)target_address;

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
	uint8_t data_buffer = 0x00;
	
	for (data_index = 0; data_index < page_size; ++data_index)
	{
		data_buffer = page[data_index];
		
		write_data(data_buffer);
		
		response = receive_response();
	}
}

void i2c_byte_read(void)
{
	uint8_t data_buffer;

	data_buffer = read_data();
	
	send_response(NOACK);
	
	display_led(data_buffer);
}

void i2c_page_read(uint8_t page_size)
{
	uint8_t data_index;
	uint8_t data_buffer = 0x00;
	
	for (data_index = 0; data_index < page_size; ++data_index)
	{
		data_buffer = read_data();
		page_buffer[data_index] = data_buffer;
		
		send_response(ACK);
		
		display_led(data_buffer);
	}
	
	send_response(NOACK);
	
	display_led(data_buffer);
}