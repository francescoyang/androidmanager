#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include "pthread_api.h"
#include "manager_api.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __mutexthread{
	void *managerp;
	pthread_t tid;
	pthread_attr_t tattr;
}mutexthread_t;

static mutexthread_t mutexthread;

void* mutex_pthread(void* arg) 
{
	
	printf("Acanoe mutex_pthread create success\n");
	while ( 1 ) {
		sleep(5);
//		mutexmanager();
		usleep(1000);
	}
}

void mutex_pthread_modules_kill()
{
	pthread_cancel(mutexthread.tid);
	printf("mutex_pthread kill success\n");
}

int mutex_thread_init(void)
{

	if (!pthread_attr_init(&mutexthread.tattr)) {
		if (!pthread_attr_setdetachstate(&mutexthread.tattr, PTHREAD_CREATE_DETACHED)) {
			pthread_create(&mutexthread.tid, &mutexthread.tattr, mutex_pthread, NULL);
			pthread_attr_destroy(&mutexthread.tattr);
		} else {
			return -1;
		}	
	} else {
		return -1;
	}

	return 0;
}


#ifdef __cplusplus
}
#endif
