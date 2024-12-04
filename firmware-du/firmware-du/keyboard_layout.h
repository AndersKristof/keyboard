
#ifndef _KEYBOARD_LAYER1_H_
#define _KEYBOARD_LAYER1_H_

#include <keyboard.h>
                                                                                     
// Normal Right Config
#define RIGHT_LAYER1_SWA0    {HID_KEY_NONE          , HID_MODIFIER_NONE          } // Header custom key
#define RIGHT_LAYER1_SWA1    {HID_7                 , HID_MODIFIER_NONE          } //
#define RIGHT_LAYER1_SWA2    {HID_8                 , HID_MODIFIER_NONE          } //
#define RIGHT_LAYER1_SWA3    {HID_9                 , HID_MODIFIER_NONE          } //
#define RIGHT_LAYER1_SWA4    {HID_0                 , HID_MODIFIER_NONE          } //
#define RIGHT_LAYER1_SWA5    {HID_UNDERSCORE        , HID_MODIFIER_NONE          } // + ?
#define RIGHT_LAYER1_SWA6    {HID_EQUAL             , HID_MODIFIER_NONE          } // \ ` �
#define RIGHT_LAYER1_SWA7    {HID_BACKSPACE         , HID_MODIFIER_NONE          } //
                                                                            
#define RIGHT_LAYER1_SWB0    {HID_Y                 , HID_MODIFIER_NONE          } //
#define RIGHT_LAYER1_SWB1    {HID_U                 , HID_MODIFIER_NONE          } //
#define RIGHT_LAYER1_SWB2    {HID_I                 , HID_MODIFIER_NONE          } //
#define RIGHT_LAYER1_SWB3    {HID_O                 , HID_MODIFIER_NONE          } //
#define RIGHT_LAYER1_SWB4    {HID_P                 , HID_MODIFIER_NONE          } //
#define RIGHT_LAYER1_SWB5    {HID_OPEN_BRACE        , HID_MODIFIER_NONE          } // �
#define RIGHT_LAYER1_SWB6    {HID_CLOSE_BRACE       , HID_MODIFIER_NONE          } // � ^ ~
#define RIGHT_LAYER1_SWB7    {HID_RETURN            , HID_MODIFIER_NONE          } // Enter 
                                                                            
#define RIGHT_LAYER1_SWC0    {HID_KEY_NONE          , HID_MODIFIER_NONE          } // NC
#define RIGHT_LAYER1_SWC1    {HID_H                 , HID_MODIFIER_NONE          } //
#define RIGHT_LAYER1_SWC2    {HID_J                 , HID_MODIFIER_NONE          } //
#define RIGHT_LAYER1_SWC3    {HID_K                 , HID_MODIFIER_NONE          } //
#define RIGHT_LAYER1_SWC4    {HID_L                 , HID_MODIFIER_NONE          } //
#define RIGHT_LAYER1_SWC5    {HID_SEMICOLON         , HID_MODIFIER_NONE          } // �
#define RIGHT_LAYER1_SWC6    {HID_APOSTROPHE        , HID_MODIFIER_NONE          } // �
#define RIGHT_LAYER1_SWC7    {HID_HASH_TILDE        , HID_MODIFIER_NONE          } // ' *
                                                                            
#define RIGHT_LAYER1_SWD0    {HID_KEY_NONE          , HID_MODIFIER_NONE          } // NC
#define RIGHT_LAYER1_SWD1    {HID_KEY_NONE          , HID_MODIFIER_NONE          } // Custom key
#define RIGHT_LAYER1_SWD2    {HID_N                 , HID_MODIFIER_NONE          } //
#define RIGHT_LAYER1_SWD3    {HID_M                 , HID_MODIFIER_NONE          } //
#define RIGHT_LAYER1_SWD4    {HID_COMMA             , HID_MODIFIER_NONE          } //
#define RIGHT_LAYER1_SWD5    {HID_DOT               , HID_MODIFIER_NONE          } //
#define RIGHT_LAYER1_SWD6    {HID_SLASH             , HID_MODIFIER_NONE          } // - _
#define RIGHT_LAYER1_SWD7    {HID_KEY_NONE          , HID_MODIFIER_RIGHT_SHIFT   } // Shift H�gre

#define RIGHT_LAYER1_SWE0    {HID_KEY_NONE          , HID_MODIFIER_NONE          } // NC
#define RIGHT_LAYER1_SWE1    {HID_KEY_NONE          , HID_MODIFIER_NONE          } // Custom key
#define RIGHT_LAYER1_SWE2    {HID_SPACEBAR          , HID_MODIFIER_NONE          } // Custom 2u key
#define RIGHT_LAYER1_SWE3    {HID_SPACEBAR          , HID_MODIFIER_NONE          } // Space 2u
#define RIGHT_LAYER1_SWE4    {HID_KEY_NONE			, HID_MODIFIER_RIGHT_ALT     } // Alt Gr H�gre
#define RIGHT_LAYER1_SWE5    {HID_KEY_NONE  		, HID_MODIFIER_RIGHT_UI      } // Win H�gre
#define RIGHT_LAYER1_SWE6    {CUSTOM_LAYER2  	    , HID_MODIFIER_NONE          } // Fn H�gre
#define RIGHT_LAYER1_SWE7    {HID_KEY_NONE			, HID_MODIFIER_RIGHT_CTRL    } // Ctrl H�gre

#define RIGHT_LAYER1	{ \
	{   RIGHT_LAYER1_SWA0, RIGHT_LAYER1_SWA1, RIGHT_LAYER1_SWA2, RIGHT_LAYER1_SWA3, RIGHT_LAYER1_SWA4, RIGHT_LAYER1_SWA5, RIGHT_LAYER1_SWA6, RIGHT_LAYER1_SWA7, }, \
	{   RIGHT_LAYER1_SWB0, RIGHT_LAYER1_SWB1, RIGHT_LAYER1_SWB2, RIGHT_LAYER1_SWB3, RIGHT_LAYER1_SWB4, RIGHT_LAYER1_SWB5, RIGHT_LAYER1_SWB6, RIGHT_LAYER1_SWB7, }, \
	{   RIGHT_LAYER1_SWC0, RIGHT_LAYER1_SWC1, RIGHT_LAYER1_SWC2, RIGHT_LAYER1_SWC3, RIGHT_LAYER1_SWC4, RIGHT_LAYER1_SWC5, RIGHT_LAYER1_SWC6, RIGHT_LAYER1_SWC7, }, \
	{   RIGHT_LAYER1_SWD0, RIGHT_LAYER1_SWD1, RIGHT_LAYER1_SWD2, RIGHT_LAYER1_SWD3, RIGHT_LAYER1_SWD4, RIGHT_LAYER1_SWD5, RIGHT_LAYER1_SWD6, RIGHT_LAYER1_SWD7, }, \
	{   RIGHT_LAYER1_SWE0, RIGHT_LAYER1_SWE1, RIGHT_LAYER1_SWE2, RIGHT_LAYER1_SWE3, RIGHT_LAYER1_SWE4, RIGHT_LAYER1_SWE5, RIGHT_LAYER1_SWE6, RIGHT_LAYER1_SWE7, }  }


// Leftmost Config 
#define LEFT_LAYER1_SWG0    {HID_ESCAPE				, HID_MODIFIER_NONE           } // Esc
#define LEFT_LAYER1_SWH0    {HID_P					, HID_MODIFIER_LEFT_SHIFT | HID_MODIFIER_LEFT_CTRL } // Custom key - Microchip Studio device programming
#define LEFT_LAYER1_SWI0    {HID_F5					, HID_MODIFIER_LEFT_CTRL | HID_MODIFIER_LEFT_ALT } // Custom key - Microchip Studio run without debugging
#define LEFT_LAYER1_SWJ0    {HID_F					, HID_MODIFIER_LEFT_SHIFT | HID_MODIFIER_LEFT_ALT } // Custom key - Microchip Studio find all references
#define LEFT_LAYER1_SWK0    {HID_F16				, HID_MODIFIER_NONE           } // Custom key

// Normal Left Config
#define LEFT_LAYER1_SWG1    {HID_GRAVE_TILDE  		, HID_MODIFIER_NONE          } // | �
#define LEFT_LAYER1_SWG2    {HID_1					, HID_MODIFIER_NONE          } //
#define LEFT_LAYER1_SWG3    {HID_2					, HID_MODIFIER_NONE          } //
#define LEFT_LAYER1_SWG4    {HID_3					, HID_MODIFIER_NONE          } //
#define LEFT_LAYER1_SWG5    {HID_4					, HID_MODIFIER_NONE          } //
#define LEFT_LAYER1_SWG6    {HID_5					, HID_MODIFIER_NONE          } //
#define LEFT_LAYER1_SWG7    {HID_6					, HID_MODIFIER_NONE          } //

#define LEFT_LAYER1_SWH1    {HID_TAB				, HID_MODIFIER_NONE          } //
#define LEFT_LAYER1_SWH2    {HID_Q					, HID_MODIFIER_NONE          } //
#define LEFT_LAYER1_SWH3    {HID_W					, HID_MODIFIER_NONE          } //
#define LEFT_LAYER1_SWH4    {HID_E					, HID_MODIFIER_NONE          } //
#define LEFT_LAYER1_SWH5    {HID_R					, HID_MODIFIER_NONE          } //
#define LEFT_LAYER1_SWH6    {HID_T					, HID_MODIFIER_NONE          } //
#define LEFT_LAYER1_SWH7    {HID_KEY_NONE			, HID_MODIFIER_NONE          } // Header custom key

#define LEFT_LAYER1_SWI1    {HID_CAPS_LOCK			, HID_MODIFIER_NONE          } //
#define LEFT_LAYER1_SWI2    {HID_A					, HID_MODIFIER_NONE          } //
#define LEFT_LAYER1_SWI3    {HID_S					, HID_MODIFIER_NONE          } //
#define LEFT_LAYER1_SWI4    {HID_D					, HID_MODIFIER_NONE          } //
#define LEFT_LAYER1_SWI5    {HID_F					, HID_MODIFIER_NONE          } //
#define LEFT_LAYER1_SWI6    {HID_G					, HID_MODIFIER_NONE          } //
#define LEFT_LAYER1_SWI7    {HID_KEY_NONE			, HID_MODIFIER_NONE          } // Custom key

#define LEFT_LAYER1_SWJ1    {HID_KEY_NONE			, HID_MODIFIER_LEFT_SHIFT    } //
#define LEFT_LAYER1_SWJ2    {HID_AT102				, HID_MODIFIER_NONE          } // <>
#define LEFT_LAYER1_SWJ3    {HID_Z					, HID_MODIFIER_NONE          } //
#define LEFT_LAYER1_SWJ4    {HID_X					, HID_MODIFIER_NONE          } //
#define LEFT_LAYER1_SWJ5    {HID_C					, HID_MODIFIER_NONE			 } //
#define LEFT_LAYER1_SWJ6    {HID_V					, HID_MODIFIER_NONE          } //
#define LEFT_LAYER1_SWJ7    {HID_B					, HID_MODIFIER_NONE		     } //

#define LEFT_LAYER1_SWK1    {HID_KEY_NONE           , HID_MODIFIER_LEFT_CTRL     } //
#define LEFT_LAYER1_SWK2    {HID_KEY_NONE		    , HID_MODIFIER_LEFT_UI       } //
#define LEFT_LAYER1_SWK3    {HID_KEY_NONE		    , HID_MODIFIER_LEFT_ALT      } //
#define LEFT_LAYER1_SWK4    {CUSTOM_LAYER2 	        , HID_MODIFIER_NONE          } //
#define LEFT_LAYER1_SWK5    {HID_SPACEBAR	        , HID_MODIFIER_NONE          } // Custom 2u key
#define LEFT_LAYER1_SWK6    {HID_SPACEBAR           , HID_MODIFIER_NONE          } // Custom 2u key
#define LEFT_LAYER1_SWK7    {HID_KEY_NONE           , HID_MODIFIER_RIGHT_ALT     } // Custom key as left side Alt Gr

#define LEFT_LAYER1	{ \
	{   LEFT_LAYER1_SWG0, LEFT_LAYER1_SWG1, LEFT_LAYER1_SWG2, LEFT_LAYER1_SWG3, LEFT_LAYER1_SWG4, LEFT_LAYER1_SWG5, LEFT_LAYER1_SWG6, LEFT_LAYER1_SWG7, }, \
	{   LEFT_LAYER1_SWH0, LEFT_LAYER1_SWH1, LEFT_LAYER1_SWH2, LEFT_LAYER1_SWH3, LEFT_LAYER1_SWH4, LEFT_LAYER1_SWH5, LEFT_LAYER1_SWH6, LEFT_LAYER1_SWH7, }, \
	{   LEFT_LAYER1_SWI0, LEFT_LAYER1_SWI1, LEFT_LAYER1_SWI2, LEFT_LAYER1_SWI3, LEFT_LAYER1_SWI4, LEFT_LAYER1_SWI5, LEFT_LAYER1_SWI6, LEFT_LAYER1_SWI7, }, \
	{   LEFT_LAYER1_SWJ0, LEFT_LAYER1_SWJ1, LEFT_LAYER1_SWJ2, LEFT_LAYER1_SWJ3, LEFT_LAYER1_SWJ4, LEFT_LAYER1_SWJ5, LEFT_LAYER1_SWJ6, LEFT_LAYER1_SWJ7, }, \
	{   LEFT_LAYER1_SWK0, LEFT_LAYER1_SWK1, LEFT_LAYER1_SWK2, LEFT_LAYER1_SWK3, LEFT_LAYER1_SWK4, LEFT_LAYER1_SWK5, LEFT_LAYER1_SWK6, LEFT_LAYER1_SWK7, }  }

// Normal Navigation Config
#define NAVNUM_LAYER1_SWG0    {HID_PAGEUP				, HID_MODIFIER_NONE          } // Page Up
#define NAVNUM_LAYER1_SWG1    {HID_HOME					, HID_MODIFIER_NONE          } // Home
#define NAVNUM_LAYER1_SWG2    {HID_INSERT				, HID_MODIFIER_NONE          } // Insert
#define NAVNUM_LAYER1_SWG3    {HID_DELETE				, HID_MODIFIER_NONE          } // Delete
#define NAVNUM_LAYER1_SWG4    {HID_END					, HID_MODIFIER_NONE          } // End
#define NAVNUM_LAYER1_SWG5    {HID_PAGEDOWN				, HID_MODIFIER_NONE          } // Page Down
#define NAVNUM_LAYER1_SWG6    {HID_KEY_NONE					, HID_MODIFIER_NONE          } // NC
#define NAVNUM_LAYER1_SWG7    {HID_KEY_NONE					, HID_MODIFIER_NONE          } // NC

#define NAVNUM_LAYER1_SWH7    {HID_UP					, HID_MODIFIER_NONE          } // Arrow up
#define NAVNUM_LAYER1_SWJ7    {HID_DOWN					, HID_MODIFIER_NONE          } // Arrow down
#define NAVNUM_LAYER1_SWK7    {HID_LEFT					, HID_MODIFIER_NONE          } // Arrow left
#define NAVNUM_LAYER1_SWI7    {HID_RIGHT				, HID_MODIFIER_NONE          } // Arrow rigth

/// Normal Numpad Config
#define NAVNUM_LAYER1_SWH3    {HID_KEYPAD_7				, HID_MODIFIER_NONE          } //
#define NAVNUM_LAYER1_SWH4    {HID_KEYPAD_4				, HID_MODIFIER_NONE          } //
#define NAVNUM_LAYER1_SWH5    {HID_KEYPAD_1				, HID_MODIFIER_NONE          } //
#define NAVNUM_LAYER1_SWH6    {HID_KEY_NONE					, HID_MODIFIER_NONE          } // NC

#define NAVNUM_LAYER1_SWI3    {HID_KEYPAD_8				, HID_MODIFIER_NONE          } //
#define NAVNUM_LAYER1_SWI4    {HID_KEYPAD_5				, HID_MODIFIER_NONE          } //
#define NAVNUM_LAYER1_SWI5    {HID_KEYPAD_2				, HID_MODIFIER_NONE          } //
#define NAVNUM_LAYER1_SWI6    {HID_KEYPAD_0				, HID_MODIFIER_NONE          } //

#define NAVNUM_LAYER1_SWJ3    {HID_KEYPAD_9				, HID_MODIFIER_NONE          } //
#define NAVNUM_LAYER1_SWJ4    {HID_KEYPAD_6				, HID_MODIFIER_NONE          } //
#define NAVNUM_LAYER1_SWJ5    {HID_KEYPAD_3				, HID_MODIFIER_NONE          } //
#define NAVNUM_LAYER1_SWJ6    {HID_KEYPAD_DOT			, HID_MODIFIER_NONE          } //

#define NAVNUM_LAYER1_SWK2    {HID_KEYPAD_MINUS			, HID_MODIFIER_NONE          } //
#define NAVNUM_LAYER1_SWK3    {HID_KEYPAD_PLUS			, HID_MODIFIER_NONE          } //
#define NAVNUM_LAYER1_SWK4    {HID_KEY_NONE				, HID_MODIFIER_NONE          } // NC
#define NAVNUM_LAYER1_SWK5    {HID_KEYPAD_ENTER			, HID_MODIFIER_NONE          } // 
#define NAVNUM_LAYER1_SWK6    {HID_KEY_NONE				, HID_MODIFIER_NONE          } // NC

// Extended Numpad Config
#define NAVNUM_LAYER1_SWH0    {HID_KEYPAD_D				, HID_MODIFIER_NONE          } //
#define NAVNUM_LAYER1_SWH1    {HID_KEYPAD_A				, HID_MODIFIER_NONE          } //
#define NAVNUM_LAYER1_SWH2    {HID_KEYPAD_NUM_LOCK		, HID_MODIFIER_NONE          } //

#define NAVNUM_LAYER1_SWI0    {HID_KEYPAD_E				, HID_MODIFIER_NONE          } //
#define NAVNUM_LAYER1_SWI1    {HID_KEYPAD_B				, HID_MODIFIER_NONE          } //
#define NAVNUM_LAYER1_SWI2    {HID_KEYPAD_SLASH			, HID_MODIFIER_NONE          } //

#define NAVNUM_LAYER1_SWJ0    {HID_KEYPAD_F				, HID_MODIFIER_NONE          } //
#define NAVNUM_LAYER1_SWJ1    {HID_KEYPAD_C				, HID_MODIFIER_NONE          } //
#define NAVNUM_LAYER1_SWJ2    {HID_KEYPAD_ASTERISK		, HID_MODIFIER_NONE          } //

#define NAVNUM_LAYER1_SWK0    {HID_KEYPAD_AND			, HID_MODIFIER_NONE          } //
#define NAVNUM_LAYER1_SWK1    {HID_KEYPAD_OR			, HID_MODIFIER_NONE          } //

#define NAVNUM_LAYER1	{ \
	{   NAVNUM_LAYER1_SWG0,  NAVNUM_LAYER1_SWG1, NAVNUM_LAYER1_SWG2, NAVNUM_LAYER1_SWG3, NAVNUM_LAYER1_SWG4, NAVNUM_LAYER1_SWG5, NAVNUM_LAYER1_SWG6, NAVNUM_LAYER1_SWG7, }, \
	{   NAVNUM_LAYER1_SWH0,  NAVNUM_LAYER1_SWH1, NAVNUM_LAYER1_SWH2, NAVNUM_LAYER1_SWH3, NAVNUM_LAYER1_SWH4, NAVNUM_LAYER1_SWH5, NAVNUM_LAYER1_SWH6, NAVNUM_LAYER1_SWH7, }, \
	{   NAVNUM_LAYER1_SWI0,  NAVNUM_LAYER1_SWI1, NAVNUM_LAYER1_SWI2, NAVNUM_LAYER1_SWI3, NAVNUM_LAYER1_SWI4, NAVNUM_LAYER1_SWI5, NAVNUM_LAYER1_SWI6, NAVNUM_LAYER1_SWI7, }, \
	{   NAVNUM_LAYER1_SWJ0,  NAVNUM_LAYER1_SWJ1, NAVNUM_LAYER1_SWJ2, NAVNUM_LAYER1_SWJ3, NAVNUM_LAYER1_SWJ4, NAVNUM_LAYER1_SWJ5, NAVNUM_LAYER1_SWJ6, NAVNUM_LAYER1_SWJ7, }, \
	{   NAVNUM_LAYER1_SWK0,  NAVNUM_LAYER1_SWK1, NAVNUM_LAYER1_SWK2, NAVNUM_LAYER1_SWK3, NAVNUM_LAYER1_SWK4, NAVNUM_LAYER1_SWK5, NAVNUM_LAYER1_SWK6, NAVNUM_LAYER1_SWK7, }  }

#endif /* _KEYBOARD_LAYER1_H_ */
