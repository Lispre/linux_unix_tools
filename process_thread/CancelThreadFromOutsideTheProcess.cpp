#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * �������߳��ⲿ����һ���̵߳���ȷ��ʽ��ͨ��pthread_cancel�����̵߳��ڲ���ȡ����
 */

void* threadfunc(void* parm)
{
  	printf("Entered secondary thread\n");
  	while (1) 
  	{
  		printf("Secondary thread is looping\n");
  		
  		//����ĵ��þ��Ǵ���ȡ����,һ���ϵͳ�⺯����Ҳ��ȡ����
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
	
	
	//֪ͨ�߳�ȡ��
	rc = pthread_cancel(thread);
	
	
	printf("pthread_cancel() %d\n", rc);

	/* sleep() is not a very robust way to wait for the thread */
	sleep(10);
	printf("Main completed\n");
	return 0;
}