/*
 * main.h
 *
 * Created: 24/04/2023 08:48:22
 * Author : echoromeo
 */ 

#include <features.h>
#include <pinout.h>

#define KBD_DRIVE_SUPPORTED 8
#define KBD_SENSE_SUPPORTED 8
#define ENCODERS_SUPPORTED  3
#define JOYSTICKS_SUPPORTED  		2
#define SPECIAL_SWITCHES_SUPPORTED  3

#define FEATURES_NUM        2
#define FLAGS_NUM           2

typedef union features_union {
	uint8_t array[FEATURES_NUM];
	struct
	{
		uint8_t drive_pins			:4;
		uint8_t sense_pins			:4;
		uint8_t encoders			:2;
		uint8_t joysticks			:2;
		uint8_t special_switches	:2;
		uint8_t reserved    		:2;
	};
} features_t;

// With this struct, maximum 48 swiches and 2 encoders supported
typedef union status_flags_union {
	uint8_t flags[FLAGS_NUM];
	struct
	{
		uint8_t switch_flags			:8;
		uint8_t encoder_flags			:3;
		uint8_t joystick_flags			:2;
		uint8_t specialswitch_flags	    :3;
	};
} status_flags_t;

typedef struct split_struct {
	uint8_t connected;
	uint8_t address;
	status_flags_t status;
	features_t features;
	uint8_t key_array[KBD_DRIVE_SUPPORTED];
	int16_t encoder_array[ENCODERS_SUPPORTED];
	int8_t joystick_array[JOYSTICKS_SUPPORTED][2];
	uint8_t specialswitches;
} board_t;

extern volatile board_t *this_board;
