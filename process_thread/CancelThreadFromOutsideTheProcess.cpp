#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * 结束从线程外部结束一个线程的正确范式是通过pthread_cancel激活线程的内部的取消点
 */

void* threadfunc(void* parm)
{
  	printf("Entered secondary thread\n");
  	while (1) 
  	{
  		printf("Secondary thread is looping\n");
  		
  		//这里的调用就是创造取消点,一般的系统库函数中也有取消点
    	pthread_testcancel();

    	sleep(1);
  	}
  	return NULL;
}
 
int main(int argc, char **argv)
{
  	pthread_t             thread;
  	int                   rc=0;
 
  	printf("Entering testcase\n");
 
  	/* Create a thread using default attributes */
  	printf("Create thread using the NULL attributes\n");
  	rc = pthread_create(&thread, NULL, threadfunc, NULL);
  	printf("pthread_create(NULL) %d\n", rc);
 
	/* sleep() is not a very robust way to wait for the thread */
	sleep(1);

	printf("Cancel the thread\n");
	
	
	//通知线程取消
	rc = pthread_cancel(thread);
	
	
	printf("pthread_cancel() %d\n", rc);

	/* sleep() is not a very robust way to wait for the thread */
	sleep(10);
	printf("Main completed\n");
	return 0;
}