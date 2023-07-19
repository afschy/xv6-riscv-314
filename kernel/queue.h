#ifndef _QUEUE_H
#define _QUEUE_H
struct spinlock;
struct proc;

struct queue {
    struct spinlock lock;
    struct proc *head;
    struct proc *tail;
};

void
enq(struct queue *q, struct proc *elem) {
    if(q->head == NULLPTR) {
        q->head = elem;
        q->tail = elem;
        elem->next = NULLPTR;
        elem->prev = NULLPTR;
        return;
    }
    q->tail->next = elem;
    elem->prev = q->tail;
    elem->next = NULLPTR;
    q->tail = elem;
}

void
remq(struct queue *q, struct proc *p) {
    if(p->prev != NULLPTR) p->prev->next = p->next;
    if(p->next != NULLPTR) p->next->prev = p->prev;
    if(q->head == p) q->head = p->next;
    if(q->tail == p) q->tail = p->prev;
    
    p->prev = NULLPTR;
    p->next = NULLPTR;
}

void
deq(struct queue *q) {
    if(q->head == NULLPTR) return;
    remq(q, q->head);
}

#endif