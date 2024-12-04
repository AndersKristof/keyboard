
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <stdbool.h>
#include <usb_protocol_hid.h>
#include <usb_hid_keycodes.h>

#define NUM_BOARDS	   4

#define BOARD_RIGHT_IDX 0
#define BOARD_LEFT_IDX (BOARD_RIGHT_IDX + 1)
#define BOARD_NAVNUM_IDX (BOARD_LEFT_IDX + 1)
#define BOARD_JOYCON_IDX (BOARD_NAVNUM_IDX + 1)

#define NUM_KEY_LAYERS 2

#define BOARD_RIGHT_LAYER_IDX 0
#define BOARD_LEFT_LAYER_IDX (BOARD_RIGHT_LAYER_IDX + NUM_KEY_LAYERS)
#define BOARD_NAVNUM_LAYER_IDX (BOARD_LEFT_LAYER_IDX + NUM_KEY_LAYERS)

// Custom keys
#define RESERVED_KEYS		   0xe8
#define CUSTOM_LAYER2		   0xe9
#define CUSTOM_LAYER3		   0xea
#define CUSTOM_LAYER4		   0xeb

#define CUSTOM_COMBO           0xee
#define CUSTOM_CALIBRATE       0xef
#define CUSTOM_RGB_COLOR       0xf0
#define CUSTOM_FUN             0xf8
#define CUSTOM_TEST            0xf9
#define CUSTOM_TEST2           0xfa

// Custom modifiers
#define COMBO_0X               0x01
#define COMBO_EGIL             0x02
#define COMBO_MCHP		   	   0x03
#define COMBO_MCHP_LA		   0x04
#define COMBO_KEYCOUNT         0x05

typedef struct {
	uint8_t key;
	uint8_t modifier;
} keymap_t;

void key_combo_push(keymap_t data);

void keyboard_init(void);
void keychange_add(uint8_t y, uint8_t x, uint8_t board, uint8_t down);
void keystate_update(uint8_t value);
uint32_t keycount_get(void);
uint16_t keycount_average_get(void);

void keyboard_volume_up(void);
void keyboard_volume_down(void);

void lockkeys_event_callback(uint16_t keys);

#endif /* _KEYBOARD_H_ */
