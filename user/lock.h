#ifndef _LOCK_H
#define _LOCK_H

// Mutual exclusion lock.
struct lock {
  uint locked;       // Is the lock held?

  // For debugging:
  char *name;        // Name of lock.
  uint pid;          // Process holding the lock
};

void
thread_lock_init (struct lock *lk, char* name) {
  lk->locked = 0;
  lk->pid = 0;
  lk->name = name;
}

void
thread_spin_lock(struct lock *lk) {
  int pid = getpid();
  // push_off(); // disable interrupts to avoid deadlock.
  if(pid == lk->pid) {
      printf("Error: lock already held by %d\n", pid);
      exit(0);
  }

  while(__sync_lock_test_and_set(&lk->locked, 1) != 0)
      ;

  __sync_synchronize();
  lk->pid = pid;
}

void
thread_spin_unlock (struct lock *lk) {
  int pid = getpid();
  if(pid != lk->pid) {
      printf("Error: lock is not held by %d\n", pid);
      exit(0);
  }

  lk->pid = 0;

  __sync_synchronize();
  __sync_lock_release(&lk->locked);
  // pop_off();
}

void
thread_mutex_lock(struct lock *lk) {
  int pid = getpid();
  // push_off(); // disable interrupts to avoid deadlock.
  if(pid == lk->pid) {
      printf("Error: lock already held by %d\n", pid);
      exit(0);
  }

  while(__sync_lock_test_and_set(&lk->locked, 1) != 0)
    sleep(1);

  __sync_synchronize();
  lk->pid = pid;
}

void
thread_mutex_unlock (struct lock *lk) {
  int pid = getpid();
  if(pid != lk->pid) {
      printf("Error: lock is not held by %d\n", pid);
      exit(0);
  }

  lk->pid = 0;

  __sync_synchronize();
  __sync_lock_release(&lk->locked);
  // pop_off();
}

#endif