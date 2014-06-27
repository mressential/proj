/*
 * GPIO.cpp
 *
 * Created: 27.06.2014 13:02:24
 *  Author: Essential
 */ 

#include "core.h"
#include <avr/io.h>

/* экономия времени работы */

void GPIO_PORTB_SET(bool input, bool state, char port)
{
	Disable_Interrupt;
	DDRB &= (~(1<<port));
	DDRB |= (input << port);
	PORTB &= (~(1<<port));
	PORTB |= (state << port);
	Enable_Interrupt;
}
