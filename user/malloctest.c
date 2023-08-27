#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "user/thread_wrapper.h"
#include "user/lock.h"

struct balance {
  char name[32];
  int amount;
};

volatile int total_balance = 0;

volatile unsigned int delay(unsigned int d) {
  unsigned int i;
  for (i = 0; i < d; i++) {
    __asm volatile("nop" :::);
  }

  return i;
}

volatile int _tid = 0;
int *x[2];
struct lock locked;
int n = 10000;

int *smem;

void do_work(void *arg) {
  int i;
  int old;
  int tid;
  tid = _tid++;
  // printf("&tid: %p\n", &tid);

  thread_mutex_lock(&locked);
  printf("thread %d started\n", tid);
  thread_mutex_unlock(&locked);

  struct balance *b = (struct balance *)arg;
  // printf( "Starting do_work: s:%s\n", b->name);
  x[tid] = malloc(sizeof(int) * n);

  thread_mutex_lock(&locked);
  printf("thread %d malloced %p\n", tid, x[tid]);
  thread_mutex_unlock(&locked);

  for (int i = 0; i < n; i++) {
    x[tid][i] = i;
  }

  for (i = 0; i < b->amount; i++) {
    // lock and mlock will be implemented by you.
    // thread_spin_lock(&lock);
    // thread_mutex_lock(&mlock);
    old = total_balance;
    delay(100000);
    // if(old != total_balance)  printf("we will miss an update. old: %d
    // total_balance: %d\n", old, total_balance);
    total_balance = old + 1;
    // thread_spin_unlock(&lock);
    //  thread_mutex_lock(&mlock);
  }

  for (int i = 0; i < n; i++) {
    thread_mutex_lock(&locked);
    smem[i]++;
    thread_mutex_unlock(&locked);
  }

  // printf( "Done s:%x\n", b->name);

  thread_exit();
  return;
}

void empty_task() {
  int tid;
  tid = _tid++;
  // printf("&tid: %p\n", &tid);

  thread_mutex_lock(&locked);
  printf("thread %d started\n", tid);
  thread_mutex_unlock(&locked);

  // printf( "Starting do_work: s:%s\n", b->name);

  for (int i = 0; i < n; i++) {
    thread_mutex_lock(&locked);
    smem[i]++;
    thread_mutex_unlock(&locked);
  }

  int *x = (int*)malloc(sizeof(int)*n);
  int i = 0;
  while(1){
    x[i]++;
    i = (i + 1) % n;
  }
  // printf( "Done s:%x\n", b->name);

  thread_exit();
  return;
}

int main(int argc, char *argv[]) {
  thread_lock_init(&locked, "a");

  struct balance b1 = {"b1", 3200};
  struct balance b2 = {"b2", 2800};

  int thread1, thread2, r1, r2;
  void *stack1, *stack2, *stack3;

  smem = malloc(sizeof(int) * n);
  stack1 = malloc(4096);
  stack2 = malloc(4096);
  stack3 = malloc(4096);

  thread1 = thread_create(do_work, (void *)&b1, stack1);
  thread2 = thread_create(do_work, (void *)&b2, stack2);
  thread_create(empty_task, 0, stack3);

  r1 = thread_join(thread1);
  r2 = thread_join(thread2);

  printf("Threads finished: (%d):%d, (%d):%d, shared balance:%d\n", thread1, r1,
         thread2, r2, total_balance);
  printf("Thread 1 malloced: %p\n", x[0]);
  printf("Thread 2 malloced: %p\n", x[1]);
  for (int i = 0; i < n; i++) {
    if (x[0][i] != i || x[1][i] != i) {
      printf("Doesn't match\n");
      printf("%d vs %d for %d\n", x[0][i], x[0][i], i);
      return 0;
    }
    if (smem[i] != 3) {
      printf("is't 3\n");
      return 0;
    }
  }
  printf("Match\n");
  exit(0);
}