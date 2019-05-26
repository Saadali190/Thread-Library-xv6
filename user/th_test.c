#include "types.h"
#include "user.h"
#include "thread.h"

int global=0;
void th1(void *arg_ptr);

int
main(int argc, char *argv[])
{  
   int a=0;

   int t_pid= thread_create(th1, (void*) &a);
   printf(1,"Thread with PID %d created\n",t_pid);
   int t_pid1= thread_create(th1, (void*) &a);
   printf(1,"Thread with PID %d created\n",t_pid1);
   int t_pid2= thread_create(th1, (void*) &a);
   printf(1,"Thread with PID %d created\n",t_pid2);

   thread_join();
   thread_join();
   thread_join();
 
   exit();
}

void
th1(void *arg_ptr) {
  int tmp=0;
  for(int i=0; i<100000; i++){
     tmp++;      
     global=tmp;
  }
  exit();
}


