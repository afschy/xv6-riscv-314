#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "user/lock.h"
#include "user/wrapper.h"

int c = 100;
int *arr;
struct lock lk;

void
tempfunc(void* arg) {
    // int a = (uint64)arg-10, b = (uint64)arg+10;
    // printf("In tempfunc %d\n", a + b - c);
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
    printf("Calling malloc %d\n", sizeof(uint32));
    thread_lock_init(&lk, "test");
    thread_spin_lock(&lk);
    thread_kernel_unlock(&lk);
    printf("kernel release done\n");

    thread_spin_lock(&lk);
    thread_spin_unlock(&lk);
    printf("acquire-release\n");
    return 0;
}