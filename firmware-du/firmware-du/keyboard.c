/*
 * keyboard.c
 *
 * Created: 08.12.2016 11:14:28
 * Author : M43977
 */

#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>

#include <usb_core.h>
#include <usb_hid_keyboard.h>
#include <usb0.h>
#include <usb_device.h>

#include "keyboard.h"
#include "keyboard_layout.h"
#include "twi.h"

#define EEPROM_KEYCOUNT_ADRESS   EEPROM_START
#define EEPROM_ELITE_ADRESS      (EEPROM_KEYCOUNT_ADRESS + sizeof(uint32_t))

static const keymap_t hid_values[NUM_BOARDS*NUM_KEY_LAYERS][KBD_DRIVE_NUM][KBD_SENSE_NUM] = 
{
	RIGHT_LAYER1,																																		  
	RIGHT_LAYER2,	
//	RIGHT_LAYER3,
	LEFT_LAYER1,																												
	LEFT_LAYER2,
//	LEFT_LAYER3,
	NAVNUM_LAYER1,
	NAVNUM_LAYER2,
//	NAVNUM_LAYER3,
};

static volatile uint8_t layer = 0;
volatile RETURN_CODE_t usb_status;

#define COMBO_FIFO_SIZE 32

static keymap_t combo_fifo[COMBO_FIFO_SIZE] = {{0}};
static uint8_t head = 0;
static uint8_t tail = 0;

#define KEYCOUNT_HISTORY_LEN 16
static volatile uint32_t seconds = 0;  
static volatile uint32_t keycount = 0, keycount_average = 0, elite = 0;
static uint16_t keycount_history[KEYCOUNT_HISTORY_LEN] = {0};

//Internal prototypes
void sof_event_callback(void);
void reset_event_callback(void);
void suspend_event_callback(void);
void wake_event_callback(void);

void keycount_store(void);
void keycount_calculate(void);

void special_key_handling(uint8_t y, uint8_t x, uint8_t layer_idx, uint8_t down);

void key_combo_pop(void);
void key_combo_start(uint8_t combo);
void key_combo_push_string(const char *str);

void cafebabe(uint8_t key);


void keyboard_init(void)
{
	USB0.INTCTRLA = USB_OVF_bm | USB_UNF_bm | USB_STALLED_bm | USB_RESET_bm | USB_RESUME_bm | USB_SUSPEND_bm | USB_SOF_bm;
	USB0.INTCTRLB = USB_SETUP_bm | USB_TRNCOMPL_bm;

	USBDevice_StartOfFrameCallbackRegister(sof_event_callback);
	USBDevice_SuspendCallbackRegister(suspend_event_callback);
	USBDevice_WakeFromSuspendCallbackRegister(wake_event_callback);
	USBDevice_ResetCallbackRegister(reset_event_callback);
	HID_SetReportCallbackRegister(lockkeys_event_callback);
	
	keycount = eeprom->keycount;
	elite = keycount + 1337;
	keycount_calculate();

	USB0_Initialize();
	USB_HIDMouseInitialize(NULL); // Keyboard handles this, called by USBDevice_Initialize
	USBDevice_Initialize();

	USB_SOFCallbackRegister(sof_event_callback);
	HID_SetReportCallbackRegister(lockkeys_event_callback); // In main_DU.c
}

void sof_event_callback(void)
{
	static volatile uint16_t countdown = 1000;
	key_combo_pop();	// too fast without USB_HIDKeyPressModifierUp/Down
	
	if (!countdown--)
	{
		countdown = 1000;

		seconds++;
		if (!(seconds % 10ul)) // 10 sec?
		{
			keycount_store();

			if (!(seconds % 60ul))
			{
				keycount_calculate();
			}
		}
	}
}

void reset_event_callback(void)
{
	_PROTECTED_WRITE(RSTCTRL.SWRR, RSTCTRL_SWRST_bm);	
}

void suspend_event_callback(void)
{
	
}

void wake_event_callback(void)
{
	
}

void special_key_handling(uint8_t y, uint8_t x, uint8_t layer_idx, uint8_t down)
{
	uint8_t key = hid_values[layer_idx][y][x].key;

	switch (key)
	{
		case CUSTOM_LAYER2:
		case CUSTOM_LAYER3:
		case CUSTOM_LAYER4:
			if (down)
			{
				layer = key - (CUSTOM_LAYER2 - 1);
			}
			else
			{
				layer = 0;
			}
//			layer_leds_update(down);
			break;
		case CUSTOM_FUN:
			if (down)
			{
//				start_fun_with_cafeleds();
			}
			break;
		case CUSTOM_RGB_COLOR:
			if (down)
			{
//				led_color_change(400);
			}
			break;
		case CUSTOM_COMBO:
			if (down)
			{
				key_combo_start(hid_values[layer_idx][y][x].modifier);
			}
			break;
		case CUSTOM_CALIBRATE:
			if (down)
			{
				// TODO: Put everything i2c in main?
				keyboard_host_send_calibrate();
			}
		case CUSTOM_TEST:
		    if (down)
			{
				USB_HIDKeySpecialDown(1);
			}
			else
			{
				USB_HIDKeySpecialUp();	
			}
			break;
		case CUSTOM_TEST2:
		    if (down)
			{
				USB_HIDKeySpecialDown(2);
			}
			else
			{
				USB_HIDKeySpecialUp();	
			}
			break;
		default:
			break;
	}
}

void key_combo_push(keymap_t data) {
    if ((head + 1) % COMBO_FIFO_SIZE == tail) {
        // Combo FIFO is full
        return;
    }
    combo_fifo[head] = data;
    head = (head + 1) % COMBO_FIFO_SIZE;
}

void key_combo_pop(void) {
	static keymap_t prev = {.key = HID_KEY_NONE, .modifier = HID_MODIFIER_NONE};
	bool consecutive = false;

    if ((head != tail) && (prev.key == combo_fifo[tail].key))
    {
	    // We have two consecutive letters
		consecutive = true; 
	}

	if (prev.key || prev.modifier)
	{
		USB_HIDKeyPressModifierUp(prev.key, prev.modifier);
		prev.key = HID_KEY_NONE;
		prev.modifier = HID_MODIFIER_NONE;
	}

    if ((head == tail) || consecutive)
	{
        // Combo FIFO is empty, or we have consecutive letters
        return;
    }

	prev.modifier = combo_fifo[tail].modifier;
	prev.key = combo_fifo[tail].key;
	USB_HIDKeyPressModifierDown(prev.key, prev.modifier);

    tail = (tail + 1) % COMBO_FIFO_SIZE;
}

void key_combo_push_string(const char *str)
{
	while (*str != '\0')
	{
		keymap_t next = {.modifier = HID_MODIFIER_NONE};
		if (*str >= 'a' && *str <= 'z')
		{
			next.key = (*str - 'a') + HID_A;
		}
		else if (*str >= 'A' && *str <= 'Z')
		{
			next.modifier = HID_MODIFIER_LEFT_SHIFT;
			next.key = (*str - 'A') + HID_A;
		}
		else if (*str >= '1' && *str <= '9')
		{
			next.key = (*str - '1') + HID_1;
		}
		else 
		{
			switch (*str)
			{
				case '0':
					next.key = HID_0;
					break;
				case ' ':
					next.key = HID_SPACEBAR;
					break;
				case ';':
					next.modifier = HID_MODIFIER_LEFT_SHIFT; // fallthrough
				case ',':
					next.key = HID_COMMA;
					break;
				case ':':
					next.modifier = HID_MODIFIER_LEFT_SHIFT; // fallthrough
				case '.':
					next.key = HID_DOT;
					break;
				case '-':
					next.key = HID_SLASH;
					break;
				case '_':
					next.modifier = HID_MODIFIER_LEFT_SHIFT;
					next.key = HID_SLASH;
					break;
				case '!':
					next.modifier = HID_MODIFIER_LEFT_SHIFT;
					next.key = HID_1;
				case '/':
					next.modifier = HID_MODIFIER_LEFT_SHIFT;
					next.key = HID_7;
					break;
				case '\\':
					next.key = HID_BACKSLASH;
					break;
				case '\n':
					next.key = HID_RETURN;
					break;					
				default:
					break;
			}		
		}

		key_combo_push(next);
		str++;
	}
}

char print_buffer[33] = "";
void key_combo_start(uint8_t combo)
{
	switch (combo)
	{
	case COMBO_0X:
		key_combo_push_string("0x");
		break;
	case COMBO_EGIL:
		key_combo_push_string("Venleg helsing,\nEgil Rotevatn");
		break;
	case COMBO_MCHP:
		key_combo_push_string("M43977");
		break;
	case COMBO_MCHP_LA:
		key_combo_push_string("M43977.LA");
		break;
	case COMBO_KEYCOUNT:
		itoa(keycount, print_buffer, 10);
		key_combo_push_string(print_buffer);
		break;
	default:
		break;
	}
	
//	key_combo_pop();
}

void keychange_add(uint8_t y, uint8_t x, uint8_t board, uint8_t down)
{
	// Get key-combination from array and send first modifiers and then the normal key value, opposite if releasing key
	// TODO: How to handle hold button, switch layer, release button? Not relevant?
	uint8_t hid_value_index = (board*NUM_KEY_LAYERS)+layer;
	if(hid_values[hid_value_index][y][x].key >= RESERVED_KEYS)
	{
		if (down)
		{
			keycount++;
		}
		special_key_handling(y, x, hid_value_index, down);
	}	
	else if(down)
	{
		keycount++;
		// Shortcut combos apparently need the modifiers first, then the key
		usb_status = USB_HIDKeyModifierDown(hid_values[hid_value_index][y][x].modifier);
		if(SUCCESS == usb_status)
		{
			usb_status = USB_HIDKeyPressDown(hid_values[hid_value_index][y][x].key);			
		}
		cafebabe(hid_values[hid_value_index][y][x].key);
	} 
	else // up
	{
		usb_status = USB_HIDKeyPressModifierUp(hid_values[hid_value_index][y][x].key, hid_values[hid_value_index][y][x].modifier);
	}
}

void keycount_store(void)
{
	static volatile uint8_t index = 0;
	if (keycount > eeprom->keycount)
	{
		if(!eeprom_write_start(false))
		{	
			// If always starting at the LSB, eeprom keycount will always be smaller than keycount?		
			eeprom->keycountarray[index] = 0xff & (keycount >> (index*8));
			eeprom_write_end(false);
			index++;
			index %= 4;
		}

// 		if(keycount >= elite) {
// 			elite <<= 2;    //Will never overflow with uint32t..
// 			status = nvm_write(INT_EEPROM, EEPROM_ELITE_ADRESS, (void *)&elite,
// 			sizeof(elite));
// 			leds_all_keys_on(13, 33, 37); //Need to improve!
// 		}
	}
	else
	{
		index = 0;
	}
}

void keycount_calculate(void)
{
	static bool reset = true;
	static uint8_t nokey_count = 0, history_index = 0;
	static uint32_t prev_keycount = 0;
	
	if (prev_keycount == 0)
	{
		prev_keycount = keycount;
		keycount_average = 0;
	}
	else if (prev_keycount == keycount)
	{
		if (++nokey_count >= 15)
		{
			// "session" done
			reset = true;
		}
	}
	else
	{
		nokey_count = 0;
	}
	
	if (reset)
	{
		reset = false;

		uint16_t thediff = keycount - prev_keycount;
		for (uint8_t i = 0; i < KEYCOUNT_HISTORY_LEN; i++)
		{
			keycount_history[i] = thediff;
		}
		keycount_average = thediff;
	}
	else
	{
		keycount_history[history_index++] = keycount - prev_keycount;
		keycount_average = 0;
		for (uint8_t i = 0; i < KEYCOUNT_HISTORY_LEN; i++)
		{
			keycount_average += keycount_history[i];
		}
		keycount_average /= KEYCOUNT_HISTORY_LEN;
	}
		
	prev_keycount = keycount;
	history_index %= KEYCOUNT_HISTORY_LEN;
}

uint32_t keycount_get(void)
{
	if (keycount < eeprom->keycount) // Boot
	{
		return eeprom->keycount;
	}
	
	return keycount;
}

uint16_t keycount_average_get(void)
{
	return keycount_average;
}

void keyboard_volume_up(void)
{
	//TODO
}

void keyboard_volume_down(void)
{
	//TODO
}

void cafebabe(uint8_t key)
{
	static uint8_t babe = 0;
	const uint8_t cafe[8] = {6, 4, 9, 8, 5, 4, 5, 8};

	if(key != cafe[babe++]) {
		babe = 0;
	}

	if(babe > 7) {
//		start_fun_with_cafeleds();
		babe = 0;
	} else {
//		stop_fun_with_cafeleds();
	}
}
