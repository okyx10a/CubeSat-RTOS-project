#include "Chibi_kernel.h"

#define MAX_NUM_THREADS			10

#define STACKSIZE						100

typedef struct Chibi_TCB
{
	int32_t *stackPt;
	struct tcb *nextPt;
}Chibi_TCB_t;

Chibi_TCB_t Chibi_TCBs[MAX_NUM_THREADS];
Chibi_TCB_t *current_thread;

int32_t TCB_stack[MAX_NUM_THREADS][STACKSIZE];

void kernel_stack_init(int i)
{
	Chibi_TCBs[i].stackPt = &TCB_stack[i][STACKSIZE-16];
	TCB_stack[i][STACKSIZE-1] = 0x01000000;
}

uint8_t add_chibi_thread(void(*C_thread)(void))
{
	__disable_irq__();
	Chibi_TCBs[0].nextPt = &Chibi_TCBs[1];
	
}

 