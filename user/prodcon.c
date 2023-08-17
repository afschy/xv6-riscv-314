#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

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
// struct queue q;
// // a mutex object lock 
// // a semaphore object empty
// // a semaphore object full

// void init_semaphore()
// {
// 	// initialize mutex lock
// 	// initialize semaphore empty with 5
// 	// initialize semaphore full with 0

// }

// void * ProducerFunc(void * arg)
// {	
// 	printf("%s\n",(char*)arg);
// 	int i;
// 	for(i=1;i<=10;i++)
// 	{
// 		// wait for semphore empty

// 		// wait for mutex lock
		
// 		sleep(1);	
// 		q.push(i);
// 		printf("producer produced item %d\n",i);
		
// 		// unlock mutex lock	
// 		// post semaphore full
// 	}
// }

// void * ConsumerFunc(void * arg)
// {
// 	printf("%s\n",(char*)arg);
// 	int i;
// 	for(i=1;i<=10;i++)
// 	{	
// 		// wait for semphore full
// 		// wait for mutex lock
 		
			
// 		sleep(1);
// 		int item = q.front();
// 		q.pop();
// 		printf("consumer consumed item %d\n",item);	


// 		// unlock mutex lock
// 		// post semaphore empty		
// 	}
// }

int main(void)
{	
	
// 	init_semaphore();
	
// 	char * message1 = "i am producer";
// 	char * message2 = "i am consumer";


// 	void *s1, *s2;
//   	int thread1, thread2, r1, r2;

//   	s1 = malloc(4096);
//   	s2 = malloc(4096);

//   	thread1 = thread_create(ProducerFunc, (void*)message1, s1);
//   	thread2 = thread_create(ConsumerFunc, (void*)message2, s2); 

//   	r1 = thread_join();
//   	r2 = thread_join();	
	
// 	exit();
    return 0;
}