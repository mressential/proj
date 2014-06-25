/*
 * v01.c
 *
 * Created: 25.06.2014 23:16:21
 *  Author: Essential
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>


typedef char TByte;
TByte GetWord(TByte _addr)
{
	_addr |= (0<<7);
	DDRD = 0xFF;
	DDRB = 0x00;
	PORTD = _addr;
	asm("nop");
	return PINB;
}

void SetWord(TByte _addr, TByte _word)
{
	DDRD = 0xFF;
	DDRB = 0xFF;
	asm("nop");
	_addr |= (1<<7);
	PORTD = _addr;
	PORTB = _word;
	asm("nop");
}

#define MOV_R_M 0xE
#define ADD_R_M 0xB
#define MOV_M_R 0xF

char regs[7];
#define AX 0
#define BX 1
#define CX 2
void RUN(void)
{
	int i = 0;
	TByte _vector = GetWord(i);
	switch(_vector&0x0F)
	{
		case MOV_R_M: 
		{
				i++;
				char _addr = GetWord(i);
				regs[_vector&0xC0] = GetWord(_addr);
				i++;
				_vector = GetWord(i);
		} break;
		case MOV_M_R:
		{
				i++;
				char _addr = GetWord(i);
				SetWord(_addr, regs[_vector&0xC0]);
				i++;
				_vector = GetWord(i);
		} break;
		case ADD_R_M:
		{
				i++;
				char _addr = GetWord(i);
				regs[_vector&0xC0] += GetWord(_addr);
				i++;
				_vector = GetWord(i);
		} break;
		
	};
	
}
/*
	memory[0] = 0x0E; MOV AX
	memory[1] = 0x32;	mem
	memory[2] = 0x0B; ADD AX
	memory[3] = 0x33;	mem
	memory[4] = 0x0F; MOV AX
	memory[5] = 0x34;	mem
	

	memory[50] = 19;
	memory[51] = 15;
	memory[52] = 0;
	
	mov ax,19
	add ax,15
	mov 52,ax
*/
int main(void)
{
	
    while(1)
    {
		RUN();
        asm("nop");
		PORTC = GetWord(0x34);
    }
}
