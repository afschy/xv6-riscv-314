#ifndef _COND_H
#define _COND_H
#include "user/lock.h"
#include "user/queue.h"

struct cond {
    struct queue q;
    struct lock q_lock;     // guards q
};

void
cond_init(struct cond* c) {
    q_init(&c->q);
    thread_lock_init(&c->q_lock, "condlock");
}

void
cond_wait(struct cond* c, struct lock* mutex) {         // mutex MUST BE HELD by the caller
    thread_mutex_lock(&c->q_lock);
    q_push(&c->q, getpid());
    thread_mutex_unlock(&c->q_lock);

    mutex->pid = 0;
    suspend_self(&mutex->locked);
    thread_mutex_lock(mutex);
    // printf("after suspend\n");
}

void
cond_signal(struct cond* c, struct lock* mutex) {       // mutex MUST BE HELD by the caller
    thread_mutex_lock(&c->q_lock);
    int pid = q_front(&c->q);
    q_pop(&c->q);
    thread_mutex_unlock(&c->q_lock);

    if(pid > 0)
        wake_other(pid);
    thread_mutex_unlock(mutex);
}

void
cond_broadcast(struct cond* c, struct lock* mutex) {    // mutex MUST BE HELD by the caller
    thread_mutex_lock(&c->q_lock);
    while(c->q.size) {
        int pid = q_front(&c->q);
        q_pop(&c->q);
        if(pid > 0)
            wake_other(pid);
    }
    thread_mutex_unlock(&c->q_lock);
    thread_mutex_unlock(mutex);
}

#endif