#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "user/cond.h"

struct cond con;
struct lock con_mutex;

void
sleeper(void* arg) {
    thread_mutex_lock(&con_mutex);
    printf("%d going to wait\n", getpid());
    cond_wait(&con, &con_mutex);
    printf("%d awakened\n", getpid());
    thread_mutex_unlock(&con_mutex);

    thread_exit();
}

void
waker(void* arg) {
    sleep(20);
    printf("going to wake a thread\n");
    thread_mutex_lock(&con_mutex);
    cond_signal(&con, &con_mutex);

    sleep(20);
    printf("going to wake another thread\n");
    thread_mutex_lock(&con_mutex);
    cond_signal(&con, &con_mutex);

    // printf("going to broadcast\n");
    // thread_mutex_lock(&con_mutex);
    // cond_broadcast(&con, &con_mutex);

    thread_exit();
}

int
main(int argc, char* argv[]) {
    thread_lock_init(&con_mutex, "con_mutex");
    cond_init(&con);

    void* s1 = malloc(4096);
    void* s2 = malloc(4096);
    void* s3 = malloc(4096);

    int t1 = thread_create(sleeper, (void*)0, s1);
    int t2 = thread_create(sleeper, (void*)0, s2);
    int t3 = thread_create(waker, (void*)0, s3);

    thread_join(t1);
    thread_join(t2);
    thread_join(t3);
    return 0;
}