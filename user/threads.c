#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "user/lock.h"
#include "user/wrapper.h"

struct balance {
    char name[32];
    int amount;
};

volatile int total_balance = 0;
struct lock lock;
struct lock print_lock;

volatile unsigned int delay (unsigned int d) {
   unsigned int i; 
   for (i = 0; i < d; i++) {
       __asm volatile( "nop" ::: );
   }

   return i;   
}

void do_work(void *arg){
    int i; 
    int old;
   
    struct balance *b = (struct balance*) arg; 
    thread_mutex_lock(&print_lock);
    printf( "Starting do_work: s:%s\n", b->name);
    thread_mutex_unlock(&print_lock);

    for (i = 0; i < b->amount; i++) { 
        // lock and mlock will be implemented by you.
        // thread_spin_lock(&lock);
        thread_mutex_lock(&lock);
        old = total_balance;
        delay(100000);
        if(old != total_balance)
            printf("we will miss an update. old: %d total_balance: %d\n", old, total_balance);
        total_balance = old + 1;
        // thread_spin_unlock(&lock);
        thread_mutex_unlock(&lock);
        // thread_kernel_unlock(&lock);

    }
  
    printf( "Done s:%x\n", b->name);

    // thread_exit();
    // return;
}

int main(int argc, char *argv[]) {

  struct balance b1 = {"b1", 3200};
  struct balance b2 = {"b2", 2800};
 
  void *s1, *s2;
  int thread1, thread2, r1, r2;

  s1 = malloc(4096); // 4096 is the PGSIZE defined in kernel/riscv.h
  s2 = malloc(4096);
  thread_lock_init(&lock, "temp");
  thread_lock_init(&print_lock, "print_lock");
  thread1 = thread_create(do_work, (void*)&b1, s1);
  thread2 = thread_create(do_work, (void*)&b2, s2); 

  r1 = thread_join(thread1);
  r2 = thread_join(thread2);
  
  printf("Threads finished: (%d):%d, (%d):%d, shared balance:%d\n", 
      thread1, r1, thread2, r2, total_balance);

  exit(0);
}
