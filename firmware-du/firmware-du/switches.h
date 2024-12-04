/*
 * switches.h
 *
 * Created: 24/04/2023 07:43:45
 * Author : echoromeo
 */ 

#ifndef SWITCHES_H
#define SWITCHES_H

#include <features.h>
#include <pinout.h>

extern volatile uint8_t switches_scan_array[KBD_DRIVE_NUM];
extern volatile uint8_t switches_scan_idx;

void switches_init(void);
uint8_t switches_drive(void);
uint8_t switches_sense(void);
uint8_t switches_row_get(uint8_t idx);

#endif // SWITCHES_H