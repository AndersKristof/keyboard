/*
 * switches.c
 *
 * Created: 24/04/2023 07:43:45
 * Author : echoromeo
 */ 

#include "switches.h"
#include "main.h"

volatile uint8_t switches_scan_idx = KBD_DRIVE_NUM-1; // Init to max so that preincrement and overflow

void switches_init(void) {
	
	KBD_DRIVE_PORT.DIRSET = KBD_DRIVE_gm;
	KBD_DRIVE_PORT.OUTSET = KBD_DRIVE_gm;
	KBD_DRIVE_PORT.PORTCTRL = PORT_SRL_bm;

	KBD_SENSE_PORT.PINCONFIG = KBD_SENSE_cfg;
	KBD_SENSE_PORT.PINCTRLUPD = KBD_SENSE_gm;	
}

uint8_t switches_drive(void) {
	KBD_DRIVE_PORT.OUTSET = 1 << (switches_scan_idx + KBD_DRIVE_gp);
	if (++switches_scan_idx >= KBD_DRIVE_NUM)
	{
		switches_scan_idx = 0;
	}
	KBD_DRIVE_PORT.OUTCLR = 1 << (switches_scan_idx + KBD_DRIVE_gp);
	
	return switches_scan_idx;
}

uint8_t switches_sense(void) {
	uint8_t sense = KBD_SENSE_PORT.IN;
	if (sense != this_board->key_array[switches_scan_idx])
	{
		this_board->key_array[switches_scan_idx] = sense;
		this_board->status.switch_flags |= 1 << switches_scan_idx;
	}

	return switches_scan_idx;
}

uint8_t switches_row_get(uint8_t idx){
	this_board->status.switch_flags &= ~(1 << idx);
	return this_board->key_array[idx];
}