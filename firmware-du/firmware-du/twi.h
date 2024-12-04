/*
 * i2c_host.h
 *
 * Created: 12.01.2024 12:35:51
 *  Author: echoromeo
 */ 


#ifndef I2C_HOST_H_
#define I2C_HOST_H_

#include "i2c.h"
#include "mcc_DU/mcc_generated_files/i2c_host/twi0.h"
#include "leds.h"

void i2c_init(void);
void i2c_timeout_tick(void);

bool i2c_keyboard_read_data_blocking(uint8_t address, i2c_splitbird_command_t command, uint8_t *data, uint8_t length);
uint8_t i2c_keyboard_read_byte_blocking(uint8_t address, i2c_splitbird_command_t command);
uint8_t i2c_keyboard_read_byte_nocommand_blocking(uint8_t address);
bool i2c_keyboard_write_data_blocking(uint8_t address, i2c_splitbird_command_t command, uint8_t *data, uint8_t length);
bool i2c_keyboard_write_const_blocking(uint8_t address, i2c_splitbird_command_t command, uint8_t data, uint8_t length);
bool i2c_keyboard_write_byte_blocking(uint8_t address, i2c_splitbird_command_t command, uint8_t data);

void keyboard_host_set_led_mode(uint8_t address, led_modes_t mode);
void keyboard_host_set_led_1d(uint8_t address, uint8_t idx, color_t color);
void keyboard_host_set_led_2d(uint8_t address, int8_t y, int8_t x, color_t color);
void keyboard_host_set_led_special(uint8_t command, color_t color);
bool keyboard_host_send_calibrate(void);

#endif /* I2C_HOST_H_ */