/*
 * firmware-du.c
 *
 * Created: 30.10.2024 16:24:12
 * Author : M78000
 */ 

#include <string.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "main.h"
#include "rtc.h"
#include "switches.h"
#include "twi.h"
#include "pins.h"
#include "keyboard.h"
#include <usb_hid_mouse.h>
#include <usb_device.h> // only for error handling

void update_encoder_array(void);
void handle_special_leds(void);
void handle_keys_standard(uint8_t board);
void handle_keys_special(uint8_t board);
void handle_keys_clear_on_fail(uint8_t board);
void handle_encoders(void);

void i2c_split_boards_update(void);

int main(void)
{
	// Configure clock to 24 MHz
	_PROTECTED_WRITE(CLKCTRL.OSCHFCTRLA, CLKCTRL_FRQSEL_24M_gc);
	CLKCTRL.MCLKTIMEBASE = 24;
	SYSCFG.VUSBCTRL = SYSCFG_USBVREG_bm;
	
	switches_init();
	switches_drive();
	
	i2c_init();

	#if (ENCODER_NUM > 0)
	encoders_init();
	#endif

	RTC_init();
	keyboard_init();
	sei();
	
	while (1)
	{
		update_encoder_array();

		if (update.lock_keys)
		{
			update.lock_keys = 0;
		}
		
		// loopable handlers
		for (uint8_t board = 0; board < NUM_BOARDS; board++)
		{
			handle_keys_standard(board);
			handle_keys_special(board);
		}

		// potentially loopable handlers
		handle_encoders();

		// non-loopable handlers, only one per loop
		if (update.boards)
		{
			update.boards = 0;
			i2c_split_boards_update();
		}
	}
}

void lockkeys_event_callback(uint16_t keys)
{
	lock_keys = keys >> 8;
	update.lock_keys = 1;
	enumerated = true;
}

void update_encoder_array(void)
{
	#if (ENCODER_NUM > 0)
	static volatile uint8_t encoder_previous[ENCODER_NUM] = {0};
	for (uint8_t i = 0; i < ENCODER_NUM; i++)
	{
		if (encoder_positions[i] != encoder_previous[i])
		{
			this_board->encoder_array[i] += encoder_positions[i]-encoder_previous[i];
			this_board->status.encoder_flags |= (1 << i);
			encoder_previous[i] = encoder_positions[i];
		}
	}
	#endif
}

void handle_keys_standard(uint8_t board)
{
	static volatile uint8_t prev_keys[NUM_BOARDS][KBD_DRIVE_NUM] = {0};
	
	if (split_board[board].status.switch_flags)
	{
		for (uint8_t row = 0; row < split_board[board].features.drive_pins; row++)
		{
			if (split_board[board].status.switch_flags & (1 << row))
			{
				split_board[board].status.switch_flags &= ~(1 << row);
				uint8_t key_changes = split_board[board].key_array[row];
				key_changes ^= prev_keys[board][row];
				prev_keys[board][row] = split_board[board].key_array[row];

				for (uint8_t column = 0; column < split_board[board].features.sense_pins; column++)
				{
					if (key_changes & (1 << column))
					{
						uint8_t state = split_board[board].key_array[row] & (1 << column);
						
						keychange_add(row, column, board, state);
					}
				}
			}
		}
	}
}

void handle_keys_clear_on_fail(uint8_t board)
{
	// Clear keys to avoid key down annoyance
	for (uint8_t i = 0; i < KBD_DRIVE_SUPPORTED; i++)
	{
		if (split_board[board].key_array[i])
		{
			split_board[board].status.switch_flags |= (1 << i);
			split_board[board].key_array[i] = 0;
		}
	}
}

void handle_encoders()
{
	if (split_board[BOARD_LEFT_IDX].encoder_array[0] > 0)
	{
		keyboard_volume_up();
		split_board[BOARD_LEFT_IDX].encoder_array[0]--;
	}
	else if (split_board[BOARD_LEFT_IDX].encoder_array[0] < 0)
	{
		keyboard_volume_down();
		split_board[BOARD_LEFT_IDX].encoder_array[0]++;
	}
	
	if (split_board[BOARD_LEFT_IDX].encoder_array[1]) // Todo: Pull out into separate function
	{
		global_brightness += split_board[BOARD_LEFT_IDX].encoder_array[1] * 2;
		split_board[BOARD_LEFT_IDX].encoder_array[1] = 0;
		
		if (global_brightness < 0)
		{
			global_brightness = 0;
		}
		else if (global_brightness > 100)
		{
			global_brightness = 100;
		}
		
		update.leds = 1;
	}
}

void i2c_split_boards_update(void)
{
	for (uint8_t board = BOARD_LEFT_IDX; board < NUM_BOARDS; board++)
	{
		bool i2c_timeout = false;
		if (!split_board[board].connected)
		{
			i2c_timeout = i2c_keyboard_read_data_blocking(split_board[board].address, I2C_COMMAND_READ_FEATURE0, (uint8_t *)split_board[board].features.array, FEATURES_NUM);
			if (!i2c_timeout && (I2C_ERROR_NONE == I2C_Host.ErrorGet()))
			{
				split_board[board].connected = 1;
			}
		}
		else if (!(split_board[board].status.flags[0] || split_board[board].status.flags[1]))
		{
			i2c_timeout = i2c_keyboard_read_data_blocking(split_board[board].address, I2C_COMMAND_READ_FLAG0, (uint8_t *)split_board[board].status.flags, FLAGS_NUM);
			if (!i2c_timeout && (I2C_ERROR_NONE == I2C_Host.ErrorGet()))
			{
				if (split_board[board].status.switch_flags)
				{
					i2c_timeout = i2c_keyboard_read_data_blocking(split_board[board].address, I2C_COMMAND_READ_OUTPUTS, (uint8_t *)split_board[board].key_array, split_board[board].features.drive_pins);
					if (i2c_timeout || (I2C_ERROR_NONE != I2C_Host.ErrorGet()))
					{
						eeprom_write_start(true);
						eeprom->usb_error = 1;
						eeprom_write_end(true);

						handle_keys_clear_on_fail(board);
					}
				}
				if (split_board[board].status.specialswitch_flags)
				{
					//split_board[board].status.specialswitch_flags = 0; // TODO: Should be cleared when handled
					i2c_timeout = i2c_keyboard_read_data_blocking(split_board[board].address, I2C_COMMAND_READ_SPECIAL, (uint8_t *)&split_board[board].specialswitches, sizeof(uint8_t));
				}
				if (split_board[board].status.encoder_flags)
				{
					split_board[board].status.encoder_flags = 0; // TODO: Should be cleared when handled?
					for (uint8_t i = 0; i < split_board[board].features.encoders; i++)
					{
						int16_t diff = 0;
						i2c_timeout = i2c_keyboard_read_data_blocking(split_board[board].address, I2C_COMMAND_READ_ENCODER1L+i*sizeof(int16_t), (uint8_t *) &diff, sizeof(int16_t));
						split_board[board].encoder_array[i] += diff;
					}
				}
				if (split_board[board].status.joystick_flags)
				{
					split_board[board].status.joystick_flags = 0; // TODO: Should be cleared when handled?
					for (uint8_t i = 0; i < split_board[board].features.joysticks; i++)
					{
						i2c_timeout = i2c_keyboard_read_data_blocking(split_board[board].address, I2C_COMMAND_READ_JOYSTICK1_X+i*sizeof(int8_t)*2, (uint8_t *) &split_board[board].joystick_array[i], sizeof(int8_t)*2);
					}
				}
			}
			else
			{
				handle_keys_clear_on_fail(board);
				split_board[board].connected = 0;
			}
		}
	}
}

ISR(RTC_PIT_vect)
{
	static volatile uint16_t rtc_tick = 0;

	rtc_tick++;
	i2c_timeout_tick();

	if (this_board != NULL)
	{
		switches_sense();
		switches_drive();
	}

	#if (ENCODER_NUM > 0)
	encoder_positions[0] += encoder1_count();
	encoder1_reset(0);
	#endif

	update.boards |= !(rtc_tick % UPDATE_PERIOD_BOARDS);

	RTC.PITINTFLAGS = RTC_PI_bm;
}
