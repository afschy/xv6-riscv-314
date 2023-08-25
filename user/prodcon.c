#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "user/semaphore.h"
#include "user/thread_wrapper.h"

// struct queue{
// 	int arr[16];
// 	int front;
// 	int rear;
// 	int size;
// 	queue()
// 	{
// 		front = 0;
// 		rear = 0;
// 		size = 0;
// 	}
// 	void push(int x)
// 	{
// 		arr[rear] = x;
// 		rear = (rear+1)%16;
// 		size++;
// 	}
// 	int front()
// 	{
// 		if(size==0)
// 			return -1;
// 		return arr[front];
// 	}
// 	void pop()
// 	{
// 		front = (front+1)%16;
// 		size--;
// 	}
// };
struct queue q;
struct lock mutex; // a mutex object lock 
struct semaphore empty; // a semaphore object empty
struct semaphore full; // a semaphore object full
struct lock print_lock;

void init_semaphore()
{
	// initialize mutex lock
    thread_lock_init(&mutex, "mutex");
	// initialize semaphore empty with 5
    sem_init(&empty, 5);
	// initialize semaphore full with 0
    sem_init(&full, 0);
	q_init(&q);
	thread_lock_init(&print_lock, "prlock");
}

void
ProducerFunc(void * arg)
{
	thread_mutex_lock(&print_lock);
	printf("%s, pid = %d\n",(char*)arg, getpid());
	thread_mutex_unlock(&print_lock);

	int i;
	for(i=1;i<=10;i++)
	{
		// wait for semphore empty
		sem_wait(&empty);
		// wait for mutex lock
		thread_mutex_lock(&mutex);
		sleep(1);	
		q_push(&q, i);
		thread_mutex_lock(&print_lock);
		printf("producer produced item %d\n",i);
		thread_mutex_unlock(&print_lock);
		// unlock mutex lock	
		thread_mutex_unlock(&mutex);
		// post semaphore full
		sem_post(&full);
		// sleep(1);
	}
	// thread_exit();
}

void
ConsumerFunc(void * arg)
{
	thread_mutex_lock(&print_lock);
	printf("%s, pid = %d\n",(char*)arg, getpid());
	thread_mutex_unlock(&print_lock);

	int i;
	for(i=1;i<=10;i++)
	{	
		// wait for semphore full
		sem_wait(&full);
		// wait for mutex lock
		thread_mutex_lock(&mutex);
		sleep(1);
		int item = q_front(&q);
		q_pop(&q);
		thread_mutex_lock(&print_lock);
		printf("\tconsumer consumed item %d\n",item);	
		thread_mutex_unlock(&print_lock);

		// unlock mutex lock
		thread_mutex_unlock(&mutex);
		// post semaphore empty
		sem_post(&empty);
		// sleep(1);
	}
	// printf("%d\n", full.val);
	// thread_exit();
}

int main(void)
{	
	
	init_semaphore();
	
	char * message1 = "i am producer";
	char * message2 = "i am consumer";


	void *s1, *s2;
  	int thread1, thread2, r1, r2;

  	s1 = malloc(4096);
  	s2 = malloc(4096);

  	thread1 = thread_create(ProducerFunc, (void*)message1, s1);
  	thread2 = thread_create(ConsumerFunc, (void*)message2, s2); 

  	r1 = thread_join(thread1);
	printf("Joined %d\n", r1);
  	r2 = thread_join(thread2);
	printf("Joined %d\n", r2);
	
	exit(0);
}