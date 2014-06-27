/*
 * Created: 25.06.2014 19:52:06
 *  Author: Ivanov Dmitry
 *	E-mail: ivan-747@yandex.ru
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>



///////////////////////////TIMER//0///////////////////////////////
ISR (TIMER0_OVF_vect)
{
	asm("nop");
}

ISR (TIMER0_COMPA_vect)
{
	asm("nop");
}

ISR (TIMER0_COMPB_vect)
{
	asm("nop");
}
///////////////////////END//TIMER//0///////////////////////////////


///////////////////////////TIMER//1///////////////////////////////
ISR (TIMER1_OVF_vect)
{
	asm("nop");
}

ISR (TIMER1_COMPA_vect)
{
	asm("nop");
}

ISR (TIMER1_COMPB_vect)
{
	asm("nop");
}
///////////////////////END//TIMER//1///////////////////////////////


///////////////////////////TIMER//2///////////////////////////////
ISR (TIMER2_OVF_vect)
{
	asm("nop");
}

ISR (TIMER2_COMPA_vect)
{
	asm("nop");
}

ISR (TIMER2_COMPB_vect)
{
	asm("nop");
}
///////////////////////END//TIMER//2///////////////////////////////


///////////////////////Watch//Dog//TIMER//////////////////////////
ISR (WDT_vect)
{
	asm("cli");
	asm("nop");
	WDTCSR = (1 << WDIE); // WDIE = 6
	asm("sei");
}
///////////////////////END//Watch//Dog//TIMER/////////////////////

/* 
	0 - allow interrupt
	1 - disable interrupt
*/
#define T0_COMPB 1
#define T0_COMPA 1
#define T0_OVF 1

#define T1_COMPB 1
#define T1_COMPA 1
#define T1_OVF 1

#define T2_COMPB 1
#define T2_COMPA 1
#define T2_OVF 1


int main(void)
{
	/*
		OCR0B = 2
		OCR0A = 1
		TCNT0 = 0
	*/
	TIMSK0 |= (T0_COMPB<<OCR0B) | (T0_COMPA<<OCR0A) | (T0_OVF<<TCNT0);
	TCCR0B |= (1 << 0); 	// 1/1 
	OCR0A = 30;		// from 0xFF
	OCR0B = 180;		// from 0xFF
	
	/*
		OCR1B = 2
		OCR1A = 1
		TCNT1 = 0
	*/
	TIMSK1 |= (T1_COMPB<<OCR1B) | (T1_COMPA<<OCR1A) | (T1_OVF<<TCNT1);
	TCCR1B |= (1 << 0); 	// 1/1 
	OCR1A = 0x0F0F;		// from 0xFFFF
	OCR1B = 0xFF0F;		// from 0xFFFF
	/*
		OCR2B = 2
		OCR2A = 1
		TCNT2 = 0
	*/
	TIMSK2 |= (T2_COMPB<<OCR2B) | (T2_COMPA<<OCR2A) | (T2_OVF<<TCNT2);
	TCCR2B |= (1 << 0); 	// 1/1 
	OCR2A = 50;		// from 0xFF
	OCR2B = 240;		// from 0xFF(255)
	
	
	/* 
		You know how to work with timers, but WATCH DOG is't simple timer!
		if you wanna turn on watch dog timer, you need defined WATCH_DOG 1
			and write WDIE bit;
		if in the course of the program there is a need to turn off the watch dog 
			time, you need write WDCE bit and for 4 cycles clear WDE bit;
	 */
	#define WATCH_DOG 1
	
	WDTCSR = (WATCH_DOG<<WDE) |		// do u wanna? // WDE = 3
				(3 << 0)	// 1/8;
				(1 << WDIE);	// enable irq
	// !!!!!!!
	asm("wdr");	// Watch Dog reset


	asm("sei");	// enable global interrupt
    while(1)
    {
        asm("nop");
    }
}
