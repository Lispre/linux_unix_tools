#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

/**
 * �������߳��ⲿ����һ���̵߳���ȷ��ʽ��ͨ��pthread_cancel�����̵߳��ڲ���ȡ����
 */

int footprint = 0;
char* storage = nullptr;

void freerc(void* s)
{
	free(s);
	puts("the free called");
}

static void checkResults(char* string, int rc)
{
	if (rc)
	{
		printf("Error on: %s, rc = %d", string, rc);
		exit(EXIT_FAILURE);
	}
	
	return;
}

void* threadfunc(void* parm)
{
	int rc = 0;
	int oldState = 0;

	rc = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &oldState);
	checkResults("pthread_setcancelstate()\n", rc);

	if ((storage = (char*) malloc(80)) == nullptr)
	{
		perror("malloc() failed!");
		exit(6);
	}

	rc = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldState);
	checkResults("pthread_setcancelstate()\n", rc);

	//ע��������˳�����Դ������
	pthread_cleanup_push(freerc, storage);

	puts("thread has obtained storage and is waiting to be cancneled");
	footprint++;
  	printf("Entered secondary thread\n");
  	while (1) 
  	{
  		printf("Secondary thread is looping\n");
  		
  		//����ĵ��þ��Ǵ���ȡ����,һ���ϵͳ�⺯����Ҳ��ȡ����
    	pthread_testcancel();

    	sleep(1);
  	}
  	pthread_cleanup_pop(1);

  	return nullptr;
}
 
int main(int argc, char **argv)
{
  	pthread_t tid;
  	void* status = nullptr;
  	if (pthread_create(&tid, nullptr, threadfunc, nullptr) != 0)
  	{
  		perror("pthread_create() error");
  		exit(1);
  	}

  	while (footprint == 0) 
  	{
  		sleep(1);
  	}

  	puts("Starting cancelling thread");
  	if (pthread_cancel(tid) != 0)
  	{
  		perror("pthread_cancel() error");
  		sleep(2);
  		exit(3);
  	}

  	if (pthread_join(tid, &status) != 0)
  	{
  		if (status != PTHREAD_CANCELED)
  		{
  			perror("pthread_join() error");
  			exit(4);
  		}
  		if (status == PTHREAD_CANCELED)
  		{
  			puts("PTHREAD_CANCELED");
  		}
  		puts("main exit");
  	}

  	return 0;
}