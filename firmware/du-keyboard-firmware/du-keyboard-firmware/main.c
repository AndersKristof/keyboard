#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "main.h"
#include "rtc.h"
#include "port.h"

#include "keyboard_layout.h"
#include "port_config.h"
#include "usb0.h"

#include <usb_device.h> // only for error handling

#define F_CPU 24e6

void key_press(uint8_t row, uint8_t column);
void key_release(uint8_t row, uint8_t column);

uint8_t pin_driven_low = 0;
uint8_t key_status[NUM_ROWS][NUM_COLUMNS] = {0};

int main(void)
{
	// Configure clock to 24 MHz
	_PROTECTED_WRITE(CLKCTRL.OSCHFCTRLA, CLKCTRL_FRQSEL_24M_gc);
	CLKCTRL.MCLKTIMEBASE = 24;
	SYSCFG.VUSBCTRL = SYSCFG_USBVREG_bm;
	
	rtc_init();
	port_init();
	twi_init();
	USB0_Initialize();
	
	sei();
}

void key_press(uint8_t row, uint8_t column)
{
	if (!key_status[row][column])
	{
		key_status[row][column] = 1;
		USB_HIDKeyPressDown(keyboard_layout[row][column]);
	}
}

void key_release(uint8_t row, uint8_t column)
{
	if (key_status[row][column])
	{
		key_status[row][column] = 0;
		USB_HIDKeyPressUp(keyboard_layout[row][column]);
	}
}

ISR(PORT_COLUMNS_vect)
{
	uint8_t row = 0;
	uint8_t column = 0;
	
	for (int i = 0; i<NUM_COLUMNS; i++)
	{
		if ((0xFF>>(NUM_COLUMNS - 1 - i)) & PORT_COLUMNS.INTFLAGS)
		{
			column = i;
			break;
		}
	}
	
	row = pin_driven_low;
	
	if (PORT_COLUMNS.IN & 1<<column)
	{
		key_release(row, column);
	} 
	else
	{
		key_press(row, column);
	}
	
	PORT_COLUMNS.INTFLAGS = 0xFF;
}

ISR(RTC_PIT_vect)
{
	static volatile uint16_t rtc_tick = 0;

	rtc_tick++;
	
	pin_driven_low += 1;
	if (pin_driven_low >= NUM_ROWS)
	{
		pin_driven_low = 0;
		PORT_ROWS.OUTSET = 0xFF;
		PORT_ROWS.OUTCLR = 1<<pin_driven_low;
	}
	else
	{
		PORT_ROWS.OUTSET = 0xFF;
		PORT_ROWS.OUTCLR = 1<<pin_driven_low;
	}

	RTC.PITINTFLAGS = RTC_PI_bm;
}
