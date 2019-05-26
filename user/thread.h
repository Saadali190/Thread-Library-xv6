#ifndef _THREAD_H_
#define _THREAD_H_

#define PGSIZE (4096)

int     thread_create(void (*start_routine)(void*), void *arg);
int     thread_join();
void    lock_init(lock_t *lock);
void    lock_acquire(lock_t *lock);
void    lock_release(lock_t *lock);
void    cv_wait(cond_t *cond, lock_t *lock);
void    cv_signal(cond_t *cond);

#endif
