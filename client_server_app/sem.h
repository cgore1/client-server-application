#include<stdio.h>
#include "threads.h"
#include<unistd.h>

typedef struct semaphore
{
	int count;
	struct TCB_t *tcbQ;
}semaphore_t;

semaphore_t* createSem(int inputValue)
{
	semaphore_t *node = (semaphore_t*) malloc(sizeof(semaphore_t));
	node -> count = inputValue;
	initQ(&(node -> tcbQ));
	return node;
}

void P(semaphore_t *sem)
{
	sem -> count--;
	
	if(sem -> count < 0)
	{
		struct TCB_t* tcbQItem = popQ(&runQ);
		addQ(&sem -> tcbQ, tcbQItem);
		swapcontext(&tcbQItem ->context, &(runQ->context));
	}
}

void V(semaphore_t *sem)
{
	sem -> count++;
	if(sem -> count <= 0)
	{
		struct TCB_t* semQItem = popQ(&sem -> tcbQ);
		addQ(&runQ, semQItem);
	}
	yield();
}

