#include "types.h"
#include "user.h"
#include "thread.h"

lock_t lock;
cond_t cond;
int global=0;
int global1=0;
void th2(void *arg_ptr);
void th1 (void *arg_ptr); 

int
main(int argc, char *argv[])
{  
   int a=0;
   lock_init(&lock);
   int t_pid= thread_create(th1, (void*) &a);
   printf(1,"Thread with PID %d created\n",t_pid);
   
   int c=1;  
   int t_pid1= thread_create(th2, (void*) &c);
   printf(1,"Thread with PID %d created\n",t_pid1);
   while(a++<2000000)
   if(a%200000==0)
   printf(1,"global1 = %d \tglobal = %d \n",global1,global);
   thread_join();
   thread_join();
   
   exit();
}

void
th1 (void *arg_ptr) {
      cv_wait(&cond,&lock);
      for(int i=0; i<100000; i++)
      {  
        global++;
      }
    cv_signal(&cond);
   exit();
}

void
th2 (void *arg_ptr) {
      cv_wait(&cond,&lock);
      
      for(int i=0; i<100000; i++)
      {  
        global1++;
      }
      
      cv_signal(&cond);
  
   exit();
}
