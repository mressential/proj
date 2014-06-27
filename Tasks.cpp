/*
 * Tasks.cpp
 *
 * Created: 27.06.2014 11:27:59
 *  Author: Essential
 */ 
#include "core.h"

TUi TaskQueueTop = -1;

void TaskPush(TFP TS, TUByte priority)
{
	Disable_Interrupt;
	FlagStateSet(FLAG_STATE_IS_TASK_CHANGE, true);
	TaskQueueTop++;
	TaskQueue[TaskQueueTop].process = TS;
	TaskQueue[TaskQueueTop].priority = priority;
	Enable_Interrupt;
}

TFP  TaskGet(void)
{
	return TaskQueue[TaskQueueTop].process;
}

void TaskPop(void)
{
	Disable_Interrupt;
	TaskQueueTop--;
	Enable_Interrupt;
}

bool TaskIsEmpty(void)
{
	if (TaskQueueTop == -1)
		return true;
	else
		return false;
}
void TaskSort(void)
{
	// поч. не работает???
	Disable_Interrupt;
	if (FlagStateGet(FLAG_STATE_IS_TASK_CHANGE))
	{
		TUi i,j;
		for (i = 0; i < TaskQueueTop; i++)
			for(j = 0; j < TaskQueueTop-i; j++)
				if (TaskQueue[TaskQueueTop].priority < TaskQueue[TaskQueueTop+1].priority)
				{
						// swap =)
						TFP process = TaskQueue[TaskQueueTop+1].process;
						TUByte priority = TaskQueue[TaskQueueTop+1].priority;
				
						TaskQueue[TaskQueueTop+1].process = TaskQueue[TaskQueueTop].process;
						TaskQueue[TaskQueueTop+1].priority = TaskQueue[TaskQueueTop].priority;
				
						TaskQueue[TaskQueueTop+1].process = process;
						TaskQueue[TaskQueueTop+1].priority = priority;
				}
		FlagStateSet(FLAG_STATE_IS_TASK_CHANGE, false);
	}	
	Enable_Interrupt;
}

