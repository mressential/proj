#include <avr/io.h>
#include <avr/interrupt.h>
#include "core.h"

// no used
ISR (TIMER0_OVF_vect) {};

// System Clock Interrupt
ISR (TIMER0_COMPA_vect)
{
	Disable_Interrupt;
	TCNT0 = 0;
	if (!TaskIsEmpty())
	{
		//TaskSort();
		TFP GoToTask = TaskGet();
		TaskPop();
		(GoToTask)();	
	}		
	Enable_Interrupt;
}


void StartSystemClock(void)
{
	Disable_Interrupt;
	TCCR0A |= (1<<6);
	TCCR0B |= (1<<0) | (1<<1);
	OCR0A = 249;
	TIMSK0 |= (3<<0);
	Enable_Interrupt;
}


