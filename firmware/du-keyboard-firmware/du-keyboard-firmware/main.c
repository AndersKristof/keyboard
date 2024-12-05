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
#include "port.h"
#include "keyboard_layout.h"
#include "usb0.h"
#include <usb_device.h> // only for error handling

uint8_t pin_driven_low = 0;
uint64_t key_status[NUM_ROWS][NUM_COLUMNS] = {0};

int main(void)
{
	// Configure clock to 24 MHz
	_PROTECTED_WRITE(CLKCTRL.OSCHFCTRLA, CLKCTRL_FRQSEL_24M_gc);
	CLKCTRL.MCLKTIMEBASE = 24;
	SYSCFG.VUSBCTRL = SYSCFG_USBVREG_bm;
	
	rtc_init();
	port_init();
	USB0_Initialize();
	
	sei();
}

ISR(PORT_COLUMNS_vect)
{
	
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
