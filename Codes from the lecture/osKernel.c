//Scheduler
//TCB
//Stack

#include "osKernel.h"


#define NUM_OF_THREADS	3
#define STACKSIZE				100
#define BUS_FREQ				48000000

uint32_t 	MILLIS_PRESCALER; 

typedef struct tcb
{
	int32_t *stackPt;
	struct tcb *nextPt;
}tcbTpye;

tcbTpye tcbs[NUM_OF_THREADS];
tcbTpye *currentPt;

int32_t TCB_STACK[NUM_OF_THREADS][STACKSIZE];

void osKernelStackInit(int i)
{
	tcbs[i].stackPt = &TCB_STACK[i][STACKSIZE-16];
	TCB_STACK[i][STACKSIZE-1] = 0x01000000;
}

uint8_t osKernelAddThreads(void(*task0)(void),void(*task1)(void),void(*task2)(void))
{
	__disable_irq();
	tcbs[0].nextPt = &tcbs[1];
	tcbs[1].nextPt = &tcbs[2];
	tcbs[2].nextPt = &tcbs[0];
	osKernelStackInit(0);
	TCB_STACK[0][STACKSIZE-2] = (int32_t)(task0);
	osKernelStackInit(1);
	TCB_STACK[1][STACKSIZE-2] = (int32_t)(task1);
	osKernelStackInit(2);
	TCB_STACK[2][STACKSIZE-2] = (int32_t)(task2);
	__enable_irq();
	return 1;
}												 
													 
void oskernelInit(void)
{
	__disable_irq();
	
	MILLIS_PRESCALER = BUS_FREQ/1000;
	
}	

void osKernelLaunch(uint32_t quanta)
{
	SysTick->CTRL = 0;
	SysTick->VAL = 0;
	SYSPRI3 = (SYSPRI3&0x00FFFFFF) | 0XE0000000; //set systick priority to lowest
	SysTick->LOAD = (quanta*MILLIS_PRESCALER);
	SysTick->CTRL = 0x00000007;
	//osSchedulerLaunch();
}



