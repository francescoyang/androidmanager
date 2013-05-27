#include <string.h>
#include <assert.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <linux/netlink.h>

#include "pthread_api.h"
#include "typestruct.h"


#define UEVENT_BUFFER_SIZE 2048
#ifdef __cplusplus
extern "C" {
#endif
	typedef struct __mainthread{
		void *managerp;
		pthread_t tid;
		pthread_attr_t tattr;
	}mainthread_t;

	static mainthread_t mainthread;
	int PTHREAD_EXIT_SIG = 0;

	void deviceinit()
	{
		system("./bin/shadb.sh");
	}

	void cleanbuf()
	{
		memset(&mmsinfo, 0, sizeof(allmmsinfo_t));
		memset(&bookinfo, 0, sizeof(allbookinfo_t));
		memset(&appinfo, 0, sizeof(allappinfo_t));
	}

	void* main_pthread(void* arg) 
	{
		deviceinit();
		net_thread_init();

		while ( 1 ) {
			usleep(50000);
			if(PTHREAD_EXIT_SIG)
			{
				PTHREAD_EXIT_SIG = 0;
				goto pthreadexit;
			}
		}
		//		close(skfd);
pthreadexit:
		net_pthread_modules_kill();
		cleanbuf();
		cleansig();
		PTHREAD_EXIT_SIG = 0;
		printf("exit pthread\n");
		pthread_exit(NULL);
	}
	void allpthread_exit()
	{
		PTHREAD_EXIT_SIG  = 1;
	}

	int main_thread_init(void)
	{

		if (!pthread_attr_init(&mainthread.tattr)) {
			if (!pthread_attr_setdetachstate(&mainthread.tattr, PTHREAD_CREATE_DETACHED)) {
				pthread_create(&mainthread.tid, &mainthread.tattr, main_pthread, NULL);
				pthread_attr_destroy(&mainthread.tattr);
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

