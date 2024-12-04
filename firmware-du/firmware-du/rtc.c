/*
 * rtc.c
 *
 * Created: 06.11.2022
 * Author: echoromeo
 */

#include <avr/io.h>
#include "rtc.h"

void RTC_init(void) {
	while (RTC.STATUS)
	{
	}
	
//	RTC.CLKSEL = RTC_CLKSEL_OSC32K_gc;
	RTC.PITINTCTRL = RTC_PI_bm;
	RTC.PITCTRLA =  RTC_PERIOD_CYC32_gc | RTC_PITEN_bm;
}
