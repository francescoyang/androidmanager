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

typedef struct __appthread{
	void *managerp;
	pthread_t tid;
	pthread_attr_t tattr;
}appthread_t;

static appthread_t appthread;

void* app_pthread(void* arg) 
{
	
	while ( 1 ) {
		sleep(1);
	}
}

int app_thread_init(void)
{

	if (!pthread_attr_init(&appthread.tattr)) {
		if (!pthread_attr_setdetachstate(&appthread.tattr, PTHREAD_CREATE_DETACHED)) {
			pthread_create(&appthread.tid, &appthread.tattr, app_pthread, NULL);
			pthread_attr_destroy(&appthread.tattr);
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

