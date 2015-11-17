#include "q.h"
#define STACK_SIZE 8192

struct TCB_t *runQ;

void start_thread(void (*function)(void))
{
  //   allocate a stack
    void *sp = malloc(STACK_SIZE);
  //   allocate a TCB (via malloc)
    struct TCB_t *tcb = (struct TCB_t *) malloc(sizeof(struct TCB_t));
  //   call init_TCB with appropriate arguments
    init_TCB(tcb, function, sp, STACK_SIZE);
  //   call addQ to add this TCB into the “RunQ” which is a global header pointer
    addQ(&runQ, tcb);
}

void run()
{  
    // real code
    ucontext_t parent;     // get a place to store the main context, for faking
    getcontext(&parent);   // magic sauce
    swapcontext(&parent, &(runQ->context));  // start the first thread
}

void yield() // similar to run
{
    struct TCB_t *prevContext = runQ;
    //store current context
    rotateQ(&runQ);
    if(runQ != NULL)
    swapcontext(&(prevContext->context),&(runQ->context));
}
