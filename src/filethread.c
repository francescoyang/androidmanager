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

typedef struct __filethread{
	void *managerp;
	pthread_t tid;
	pthread_attr_t tattr;
}filethread_t;

static filethread_t filethread;

void* file_pthread(void* arg) 
{
	while ( 1 ) {
		sleep(1);
	}
}

int file_thread_init(void)
{

	if (!pthread_attr_init(&filethread.tattr)) {
		if (!pthread_attr_setdetachstate(&filethread.tattr, PTHREAD_CREATE_DETACHED)) {
			pthread_create(&filethread.tid, &filethread.tattr, file_pthread, NULL);
			pthread_attr_destroy(&filethread.tattr);
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
