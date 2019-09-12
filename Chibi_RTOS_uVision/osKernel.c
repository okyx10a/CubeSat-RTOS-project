//Scheduler
//TCB
//Stack

#include "osKernel.h"

#define NUM_OF_THREADS	3
#define STACKSIZE				100

struct tcb
{
	int32_t *stackPt;
	struct tcb *nextPt;
};

typedef struct tcb tcbType;
tcbType tcbs[NUM_OF_THREADS];
tcbType *currentPt;

int32_t TCB_STACK[NUM_OF_THREADS][STACKSIZE];

void osKernelStackInit(int i)
{
	tcbs[i].stackPt = &TCB_STACK[i][STACKSIZE-16]; //-16 means we have to save the 16 register representing the original state of the CPU
	TCB_STACK[i][STACKSIZE-1] = 0x1000000; //initailize xPSR register, setting bit 24 to one to indicate that we are running in thumb mode.				 
}

uint8_t osKernelAddThreads(void(*task0)(void), void(*task1)(void), void(*task2)(void))
{
	
}