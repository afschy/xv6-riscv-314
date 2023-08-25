#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "user/lock.h"
#include "user/thread_wrapper.h"

int c = 100;
int *arr;
struct lock lk;

void
f2(void* arg) {
    printf("In f2\n");
    sleep(30);
    printf("f2 woken\n");
    while(1);
}

void
f1(void* arg) {
    printf("In f1\n");
    void *s = malloc(4096);
    thread_create(f2, 0, s);
    sleep(40);
    printf("f1 woken\n");
    while(1);
}

int
main() {
    void *s1 = malloc(4096);
    void *s2 = malloc(4096);
    thread_create(f1, 0, s1);
    thread_create(f1, 0, s2);
    sleep(10);
    return 0;
}