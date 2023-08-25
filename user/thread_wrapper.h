#ifndef _THREAD_WRAPPER_H
#define _THREAD_WRAPPER_H

void
thread_exit_wrapper() {
    // printf("exiting thread %d\n", getpid());
    thread_exit();
}

int
thread_create(void* fcn, void* arg, void* stack) {
    return thread_create_kernel(fcn, arg, stack, thread_exit_wrapper);
}

#endif