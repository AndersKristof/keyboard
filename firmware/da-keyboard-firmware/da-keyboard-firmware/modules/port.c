#include <avr/io.h>

#include "port.h"
#include "port_config.h"

void port_init()
{
	// Set up rows as output pins
	PORT_ROWS.DIRSET = (0xFF>>(8-NUM_ROWS));
	PORT_ROWS.OUTSET = (0xFF>>(8-NUM_ROWS));
	
	// Set up columns as input pins with pull-up enabled
	PORT_COLUMNS.DIRCLR = (0xFF>>(8-NUM_COLUMNS));
	PORT_COLUMNS.PINCONFIG = (PORT_PULLUPEN_bm | PORT_ISC_BOTHEDGES_gc);
	PORT_COLUMNS.PINCTRLSET = (0xFF>>(8-NUM_COLUMNS));
}