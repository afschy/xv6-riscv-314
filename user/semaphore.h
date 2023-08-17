#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H
#include "user/cond.h"

struct semaphore {
    int val;
    struct cond con;
    struct lock lk;
};

void
sem_init(struct semaphore* sem, int v) {
    sem->val = v;
    cond_init(&sem->con);
    thread_lock_init(&sem->lk, "sem_lock");
}

void
sem_wait(struct semaphore* sem) {
    thread_mutex_lock(&sem->lk);
    while(sem->val <= 0) 
        cond_wait(&sem->con, &sem->lk);
    sem->val--;
    if(sem->val < 0) sem->val = 0;
    thread_mutex_unlock(&sem->lk);
}

void
sem_post(struct semaphore* sem) {
    thread_mutex_lock(&sem->lk);
    sem->val++;
    cond_signal(&sem->con);
    thread_mutex_unlock(&sem->lk);
}

#endif