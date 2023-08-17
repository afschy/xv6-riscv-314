#ifndef _Q_H
#define _Q_H

struct queue{
	int arr[70];
	int front;
	int rear;
	int size;
};

void
q_init(struct queue *q) {
    q->front = 0;
    q->rear = 0;
    q->size = 0;
}
void
q_push(struct queue *q, int x) {
    q->arr[q->rear] = x;
    q->rear = (q->rear+1)%16;
    q->size++;
}
int
q_front(struct queue *q) {
    if(q->size==0)
        return -1;
    return q->arr[q->front];
}
void
q_pop(struct queue *q) {
    q->front = (q->front+1)%16;
    q->size--;
}

#endif