#define NUM_ROWS 5
#define NUM_COLUMNS 7
#define NUM_EXTRA 0
#define NUM_KEYS (NUM_ROWS*NUM_COLUMNS + NUM_EXTRA)

#define PORT_COLUMNS PORTD
#define PORT_ROWS PORTF

#define PORT_COLUMNS_vect PORTD_PORT_vect

#include <stdint.h>

#include "usb_hid_keycodes.h"


uint8_t keyboard_layout[NUM_ROWS][NUM_COLUMNS] =
{
	{HID_7, HID_8, HID_9, HID_0, HID_KEYPAD_PLUS_MINUS, HID_EQUAL, HID_BACKSLASH}
}




#endif /* KEYBOARD_LAYOUT_H_ */