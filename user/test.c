#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int c = 100;
int *arr;

void
cuck(void* arg) {
    // int a = (uint64)arg-10, b = (uint64)arg+10;
    // printf("In cuck %d\n", a + b - c);
    c = 999;
    sleep(20);
    for(int i=0; i<5; i++) {
        printf("%d\n", arr[i]);
        // arr[i] += 10;
    }
    free(arr);
    arr = malloc(10 * sizeof(uint32));
    for(int i=0; i<5; i++)
        arr[i] = 100 + i;
    thread_exit();
}

int
main() {
    printf("Calling malloc\n");
    void* stack1 = malloc(4096);
    void* stack2 = malloc(4096);
    /*int tid1 = */thread_create(cuck, (void*)1125, stack1);
    // sleep(2);
    /*int tid2 = */thread_create(cuck, (void*)75, stack2);
    
    arr = malloc(10 * sizeof(uint32));
    for(int i=0; i<5; i++)
        arr[i] = i+1;
    // sleep(10);
    // printf("Malloc for arr done\n");
    // thread_join(tid1);
    // thread_join(tid2);
    // printf("c after edit = %d\n", c);
    for(int i=0; i<5; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}