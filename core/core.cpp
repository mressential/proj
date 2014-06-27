/*
 * core.cpp
 *
 * Created: 27.06.2014 11:38:34
 *  Author: Essential
 */ 
#include "core.h"


TUByte flags;

bool FlagStateGet(TByte point)
{
	return  ((flags & (1<<point)) != 0);
}

void FlagStateSet(TByte point, bool v)
{
	flags &= (~(1<<point));	// обнулем нужный бит
	flags |= (v<<point);	// пишем необходимое 
}

