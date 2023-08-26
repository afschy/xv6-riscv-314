#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "user/lock.h"
#include "user/thread_wrapper.h"

int arrsize = 4 * 4096;

int c = 100;
int *arr;
struct lock lk;

void
f2(void* arg) {
    sleep(20);
    printf("f2 %d, %d\n", sbrk(0), arr[arrsize-1]);
}

void
f1(void* arg) {
    sleep(10);
    printf("f1 %d, %d\n", sbrk(0), arr[arrsize-1]);
    free(arr);
    arrsize *= 4;
    arr = malloc(arrsize * sizeof(int));
    arr[arrsize-1] = 222;
}

int
main() {
    void *s1 = malloc(4096);
    void *s2 = malloc(4096);
    int t1 = thread_create(f1, 0, s1);
    int t2 = thread_create(f2, 0, s2);
    printf("threads created\n");

    arr = malloc(arrsize * sizeof(int));
    arr[arrsize-1] = 111;
    printf("main %d, %d\n", sbrk(0), arr[arrsize-1]);

    thread_join(t1);
    thread_join(t2);
    return 0;
}