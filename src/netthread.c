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

typedef struct __netthread{
	void *managerp;
	pthread_t tid;
	pthread_attr_t tattr;
}netthread_t;

static netthread_t netthread;

void* net_pthread(void* arg) 
{
	
//		sleep(1);
		printf("Acanoe net_pthread create success\n");
		amservicestart();
}

void net_pthread_modules_kill()
{
	printf("net_pthread kill success\n");
	pthread_cancel(netthread.tid);
//	exit_sock();
}

int net_thread_init(void)
{

	if (!pthread_attr_init(&netthread.tattr)) {
		if (!pthread_attr_setdetachstate(&netthread.tattr, PTHREAD_CREATE_DETACHED)) {
			pthread_create(&netthread.tid, &netthread.tattr, net_pthread, NULL);
			pthread_attr_destroy(&netthread.tattr);
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
