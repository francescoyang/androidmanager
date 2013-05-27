#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#include "pthread_api.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __downthread{
	void *managerp;
	pthread_t tid;
	pthread_attr_t tattr;
}downthread_t;

static downthread_t downthread;

void* down_pthread(void* arg) 
{
	
	while ( 1 ) {
		sleep(1);
	}
}

int download_thread_init(void)
{

	if (!pthread_attr_init(&downthread.tattr)) {
		if (!pthread_attr_setdetachstate(&downthread.tattr, PTHREAD_CREATE_DETACHED)) {
			pthread_create(&downthread.tid, &downthread.tattr, down_pthread, NULL);
			pthread_attr_destroy(&downthread.tattr);
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

