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
#include "manager_api.h"

#define UEVENT_BUFFER_SIZE 1024*10
#ifdef __cplusplus
extern "C" {
#endif

	int USB_STATE = KONG_USB;
	struct sockaddr_nl client;
	struct timeval tv;
	int skfd, rcvlen, ret;
	fd_set fds;
	int buffersize = 1024;
	int return_usb = KONG_USB;



	typedef struct __usbthread{
		void *managerp;
		pthread_t tid;
		pthread_attr_t tattr;
	}usbthread_t;

	static usbthread_t usbthread;

	int usb_sock()
	{
		skfd = socket(AF_NETLINK, SOCK_RAW, NETLINK_KOBJECT_UEVENT);
		memset(&client, 0, sizeof(client)); 	   
		client.nl_family = AF_NETLINK;
		client.nl_pid = getpid(); 
		client.nl_groups = 1; /* receive broadcast message*/	
		setsockopt(skfd, SOL_SOCKET, SO_RCVBUF, &buffersize, sizeof(buffersize));
		bind(skfd, (struct sockaddr*)&client, sizeof(client));


		FD_ZERO(&fds);
		FD_SET(skfd, &fds);
		tv.tv_sec = 0;
		tv.tv_usec = 100 * 1000;
		ret = select(skfd + 1, &fds, NULL, NULL, &tv);
		if(ret < 0) {
			printf("select return error\n");
		}
		if(!(ret > 0 && FD_ISSET(skfd, &fds)))
		{
			printf("FD_ISSET return error\n");
		}
		return 1;
	}
	int usb_event()
	{
		//		rcvlen = recv(skfd, &buf, sizeof(buf), 0);
		char buf[UEVENT_BUFFER_SIZE] = { 0 };
		rcvlen = recv(skfd, &buf, 3, 0);
		if (rcvlen > 0) {
			printf("%s\n", buf);
			if((strstr("add",buf) || strstr("cha",buf)) ){
				USB_STATE = ADD_USB;
			} 
			if(strstr("rem",buf)){
				USB_STATE = REMOVE_USB;
			}
		}
		return 1;
	}

	int monitor_usb()
	{
		if( return_usb == USB_STATE ) {
			return KONG_USB;
		} else {
			return_usb = USB_STATE;
			USB_STATE = KONG_USB;
			return return_usb;
		}
	}
	void* usb_pthread(void* arg) 
	{
		usb_sock();

		while ( 1 ) {
			usb_event();
			usleep(50000);
		}
		close(skfd);
		return 0;
	}

	int usb_thread_init(void)
	{

		if (!pthread_attr_init(&usbthread.tattr)) {
			if (!pthread_attr_setdetachstate(&usbthread.tattr, PTHREAD_CREATE_DETACHED)) {
				pthread_create(&usbthread.tid, &usbthread.tattr, usb_pthread, NULL);
				pthread_attr_destroy(&usbthread.tattr);
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

