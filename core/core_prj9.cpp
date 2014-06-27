/*
 * core_prj9.cpp
 *
 * Created: 27.06.2014 10:52:49
 *  Author: Essential
 */ 


#include "core.h"


void LedOn(void)
{
	GPIO_PORTB_SET(false, true, 0);
}

void LedOff(void)
{
	GPIO_PORTB_SET(false, false, 0);
}

int main(void)
{
	StartSystemClock();

    TaskPush(LedOff, 0);	
	TaskPush(LedOn, 0);		// включаем а затем выключаем диод
	while (1) {asm("nop");}
}
