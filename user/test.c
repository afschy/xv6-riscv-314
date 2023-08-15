#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int c = 100;
int *arr;

void
cuck(void* arg) {
    int a = (uint64)arg-10, b = (uint64)arg+10;
    printf("In cuck %d\n", a + b - c);
    sleep(20);
    for(int i=0; i<5; i++)
        printf("%d\n", arr[i]);
    while(1);
}

int
main() {
    printf("Calling malloc\n");
    void* stack = malloc(4096);
    thread_create(cuck, (void*)1125, stack);
    arr = malloc(10 * sizeof(uint32));
    for(int i=0; i<5; i++)
        arr[i] = i+1;
    sleep(2);
    printf("Malloc for a done\n");
    while(1);
    return 0;
}