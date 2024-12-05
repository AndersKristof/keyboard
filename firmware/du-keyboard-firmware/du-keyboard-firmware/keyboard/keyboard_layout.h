/*
 * keyboard_layout.h
 *
 * Created: 05.12.2024 15:25:30
 *  Author: M78000
 */ 


#ifndef KEYBOARD_LAYOUT_H_
#define KEYBOARD_LAYOUT_H_

#define NUM_ROWS 5
#define NUM_COLUMNS 7
#define NUM_EXTRA 0
#define NUM_KEYS (NUM_ROWS*NUM_COLUMNS + NUM_EXTRA)

#define PORT_COLUMNS PORTD
#define PORT_ROWS PORTF

#define PORT_COLUMNS_vect PORTD_PORT_vect

#include <stdint.h>

#include "usb_hid_keycodes.h"


uint8_t keys[NUM_ROWS][NUM_COLUMNS] =
{
	{HID_ESCAPE, HID_1, HID_2, HID_3, HID_4, HID_5, HID_6}
}


#endif /* KEYBOARD_LAYOUT_H_ */