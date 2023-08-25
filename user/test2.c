#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "user/cond.h"
#include "user/thread_wrapper.h"
int arrsize = 4 * 4096;

struct cond con;
struct lock con_mutex;
int *arr;

void
temp(void* arg) {
    while(1)
    printf("in temp\n");
}

void
sleeper(void* arg) {
    printf("t1: %d, %d\n", sbrk(0), arr[arrsize - 1]);

    void* s1 = malloc(4096);
    // void* s2 = malloc(4096);
    // void* s3 = malloc(4096);

    thread_create(sleeper, (void*)0, s1);
    while(1)
    printf("haha\n");
    // int t2 = thread_create(sleeper, (void*)0, s2);
    // thread_create(sleeper, (void*)0, s3);

    // thread_exit();
}

void
waker(void* arg) {
    // sleep(5);
    while(1)
        printf("lol\n");
}

int
main(int argc, char* argv[]) {
    thread_lock_init(&con_mutex, "con_mutex");
    cond_init(&con);

    void* s1 = malloc(4096);
    // void* s2 = malloc(4096);
    void* s3 = malloc(4096);

    thread_create(sleeper, (void*)0, s1);
    // int t2 = thread_create(sleeper, (void*)0, s2);
    thread_create(waker, (void*)0, s3);

    arr = malloc(arrsize * sizeof(int));
    printf("%d\n", sbrk(0));
    arr[arrsize - 1] = 12345;
    printf("%d\n", arr[arrsize - 1]);
    sleep(2);

    // thread_join(t3);
    // thread_join(t1);
    // thread_join(t2);
    return 0;
}