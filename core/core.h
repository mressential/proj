#ifndef _CORE_ARX_H_
#define _CORE_ARX_H_
#pragma once

#include <stdbool.h> // теперь знает bool

#define Disable_Interrupt	asm("cli")
#define Enable_Interrupt	asm("sei")


typedef void (*TFP)(void);		// указатель на функцию
typedef char TByte;
typedef unsigned char TUByte;
typedef unsigned int TUi;
typedef struct _TProcess
{
	TFP process;
	TUByte priority;
} TProcess; 

// TASK
const unsigned int TaskQueueSize = 255;
volatile static TProcess TaskQueue[TaskQueueSize]; 
#define Idle 0

void TaskPush(TFP TS, TUByte priority);
TFP  TaskGet(void);
void TaskPop(void);
void TaskSort(void);
bool TaskIsEmpty(void);



// SYS CLOCK
void StartSystemClock(void);



// WORK WITH FLAGS
bool FlagStateGet(TByte point);
void FlagStateSet(TByte point, bool v);


// FLAGS
#define FLAG_STATE_IS_INTERRUPT 0
#define FLAG_STATE_CAN_INTERRUPT 1
#define FLAG_STATE_IS_TASK_CHANGE 2


// General-purpose input/output (GPIO)
void GPIO_PORTB_SET(bool input, bool state, char port);



#endif

