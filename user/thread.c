#include "types.h"
#include "user.h"
#include "thread.h"
#include "x86.h"



int
thread_create(void (*start_routine)(void*), void *arg){
   
   void *stack = malloc(PGSIZE);
   if((uint)stack % PGSIZE)
     stack = stack + (4096 - (uint)stack % PGSIZE);
     uint clone_pid=clone(start_routine, arg, stack);
     if(clone_pid == -1)
        printf(1,"Could not create thread\n");

   return clone_pid;
}

int
thread_join(){
   void* stack = NULL;
   int pid = join(stack);
   return pid;
}

void 
lock_init(lock_t *lock) {
  lock->flag = 0;
}

void 
lock_acquire(lock_t *lock) {
  cli();
  while (xchg(&lock->flag, 1));
  printf(1,"Lock acquired\n");
}

void
lock_release(lock_t *lock) {
  printf(1,"Releasing Lock\n");
  lock->flag = 0;
  sti();
}

void  
cv_wait(cond_t *cond, lock_t *lock){
   cond->lock=lock;
   while(lock->flag);
   xchg(&cond->lock->flag,1);
}
   
void    
cv_signal(cond_t *cond){

   cond->lock->flag=0;
}


