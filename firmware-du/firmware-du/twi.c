/*
 * i2c_host.c
 *
 * Created: 12.01.2024 12:25:28
 *  Author: echoromeo
 */ 

#include "i2c_host.h"
#include "main.h"
#include "eeprom.h"
#include <stdbool.h>
#include <string.h>

#define I2C_READ_BUFFER_SIZE 32
#define I2C_WRITE_BUFFER_SIZE 129 // Due to OLED
#define I2C_TIMEOUT 350u

uint8_t i2c_read_buffer[I2C_READ_BUFFER_SIZE] = {0};
uint8_t i2c_write_buffer[I2C_WRITE_BUFFER_SIZE] = {0};
static volatile uint16_t i2c_wait_timeout = 0;

void i2c_init(void)
{
	PORTMUX.TWIROUTEA = I2C_PORTMUX_gc;
	I2C_Host.Initialize();
	//	I2C_Host.CallbackRegister(i2c_handler);
}

void i2c_timeout_tick(void)
{
	i2c_wait_timeout++;
}

static bool i2c_blocking_wait(void)
{
	i2c_wait_timeout = 0;
	while (I2C_Host.IsBusy())
	{
		if (i2c_wait_timeout > I2C_TIMEOUT)
		{
			eeprom_write_start(true);
			eeprom->usb_error = 2;
			eeprom_write_end(true);
			
 			_PROTECTED_WRITE(RSTCTRL.SWRR, RSTCTRL_SWRST_bm);

			return true;
		}
	}
	
	return false;
}

bool i2c_keyboard_read_data_blocking(uint8_t address, i2c_splitbird_command_t command, uint8_t *data, uint8_t length)
{
	i2c_write_buffer[0] = command;
	I2C_Host.WriteRead(address, i2c_write_buffer, 1, data, length);
	return i2c_blocking_wait();
}

uint8_t i2c_keyboard_read_byte_blocking(uint8_t address, i2c_splitbird_command_t command)
{
	i2c_read_buffer[0] = 0;
	i2c_keyboard_read_data_blocking(address, command, i2c_read_buffer, 1);
	return i2c_read_buffer[0];
}

uint8_t i2c_keyboard_read_byte_nocommand_blocking(uint8_t address)
{
	i2c_read_buffer[0] = 0;
	I2C_Host.Read(address, i2c_read_buffer, 1);	
	i2c_blocking_wait();
	return i2c_read_buffer[0];
}

bool i2c_keyboard_write_data_blocking(uint8_t address, i2c_splitbird_command_t command, uint8_t *data, uint8_t length)
{
	i2c_write_buffer[0] = command;
	if (length)
	{
		memcpy(&i2c_write_buffer[1], data, length);
	}
	I2C_Host.Write(address, i2c_write_buffer, length+1);
	return i2c_blocking_wait();
}

bool i2c_keyboard_write_const_blocking(uint8_t address, i2c_splitbird_command_t command, uint8_t data, uint8_t length)
{
	i2c_write_buffer[0] = command;
	memset(&i2c_write_buffer[1], data, length);	

	I2C_Host.Write(address, i2c_write_buffer, length+1);
	return i2c_blocking_wait();
}

bool i2c_keyboard_write_byte_blocking(uint8_t address, i2c_splitbird_command_t command, uint8_t data)
{
	return i2c_keyboard_write_data_blocking(address, command, &data, 1);
}

void keyboard_host_set_led_mode(uint8_t address, led_modes_t mode)
{
	if (address != this_board->address)
	{
		i2c_keyboard_write_byte_blocking(address, I2C_COMMAND_WRITE_LEDMODE, mode);
	}
	
	if ((address == I2C_ADDRESS_KEYBOARD_ALL) || (address == this_board->address))
	{
		led_mode_set(mode);
	}
}

void keyboard_host_set_led_1d(uint8_t address, uint8_t idx, color_t color)
{
	if (address != this_board->address)
	{
		i2c_write_buffer[0] = I2C_COMMAND_WRITE_LEDDATA1D;
		i2c_write_buffer[1] = idx;
		i2c_write_buffer[2] = color.array[0];
		i2c_write_buffer[3] = color.array[1];
		i2c_write_buffer[4] = color.array[2];
		
		I2C_Host.Write(address, i2c_write_buffer, 5);
		i2c_blocking_wait();
	}
	
	if ((address == I2C_ADDRESS_KEYBOARD_ALL) || (address == this_board->address))
	{
		led_set_1d(idx, color);
	}
}

void keyboard_host_set_led_2d(uint8_t address, int8_t y, int8_t x, color_t color)
{
	if (address != this_board->address)
	{
		i2c_write_buffer[0] = I2C_COMMAND_WRITE_LEDDATA2D;
		i2c_write_buffer[1] = y;
		i2c_write_buffer[2] = x;
		i2c_write_buffer[3] = color.array[0];
		i2c_write_buffer[4] = color.array[1];
		i2c_write_buffer[5] = color.array[2];
		
		I2C_Host.Write(address, i2c_write_buffer, 6);
		i2c_blocking_wait();
	}
	
	if ((address == I2C_ADDRESS_KEYBOARD_ALL) || (address == this_board->address))
	{
		led_mode_update(y, x, color);
	}
}

void keyboard_host_set_led_special(uint8_t command, color_t color)
{
	i2c_write_buffer[0] = command;
	i2c_write_buffer[1] = color.array[0];
	i2c_write_buffer[2] = color.array[1];
	i2c_write_buffer[3] = color.array[2];
	
	I2C_Host.Write(I2C_ADDRESS_KEYBOARD_ALL, i2c_write_buffer, 4);
	led_special_update(command-I2C_COMMAND_WRITE_LEDCAPS, color);
	i2c_blocking_wait();
}

bool keyboard_host_send_calibrate(void)
{
	return i2c_keyboard_write_data_blocking(I2C_ADDRESS_KEYBOARD_ALL, I2C_COMMAND_CALIBRATE, NULL, 0);
}
