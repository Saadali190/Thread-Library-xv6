#include "types.h"
#include "user.h"
#include "thread.h"

lock_t lock;
cond_t cond;
volatile int global=0;
//int global1=0;

void th1(void *arg_ptr);
void th2(void *arg_ptr);
void th3(void *arg_ptr);

int
main(int argc, char *argv[])
{  
   int a=0;
   lock_init(&lock);
   int t_pid= thread_create(th1, (void*) &a);
   printf(1,"Thread with PID %d created\n",t_pid);
   sleep(1);
   //while(a++<100000)
   //if(a%20000==0)
   printf(1,"global = %d \n",global);
   //sleep(1);
   //while(global!=100000);
   thread_join();
  // printf(1,"global = %d \n",global);
   int t_pid1= thread_create(th2, (void*) &a);
   printf(1,"Thread with PID %d created\n",t_pid1);
   //sleep(1);
  thread_join();
 //  int t_pid2= thread_create(th3, (void*) &a);
   //printf(1,"Thread with PID %d created\n",t_pid2);
   //thread_join();
   //thread_join();
   sleep(1);
   printf(1,"L global = %d \n",global);
    
   exit();
}

void
th1(void *arg_ptr) {
  int tmp=0;
  for(int i=0; i<20000; i++){
     tmp++;      
     global=tmp;
  }
  exit();
}

void
th2(void *arg_ptr){
  
  lock_acquire(&lock);
  int tmp=0;
  for(int i=0; i<20000; i++){
     tmp++;      
     global=tmp;
  }    
  lock_release(&lock);
      
    exit();
}

void
th3(void *arg_ptr){
      int tmp=0;
 //   printf(1,"no lock\n");
      for(int i=0; i<100000; i++){
        tmp++;
        global=tmp;
       }
       //printf(1,"nl global %d lock = %d\n",global,lock.flag);
   
    exit();
}

