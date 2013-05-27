#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <linux/netlink.h>

#define UEVENT_BUFFER_SIZE 2048


int thread_net_link()
{
	struct sockaddr_nl client;
	struct timeval tv;
	int skfd, rcvlen, ret;
	fd_set fds;
	int buffersize = 1024;
	int i = 0;

	skfd = socket(AF_NETLINK, SOCK_RAW, NETLINK_KOBJECT_UEVENT);
	memset(&client, 0, sizeof(client)); 	   
	client.nl_family = AF_NETLINK;
	client.nl_pid = getpid(); 
	client.nl_groups = 1; /* receive broadcast message*/	
	setsockopt(skfd, SOL_SOCKET, SO_RCVBUF, &buffersize, sizeof(buffersize));
	bind(skfd, (struct sockaddr*)&client, sizeof(client));

	while (1) {
		char buf[UEVENT_BUFFER_SIZE] = { 0 };

		FD_ZERO(&fds);
		FD_SET(skfd, &fds);
		tv.tv_sec = 0;
		tv.tv_usec = 100 * 1000;
		ret = select(skfd + 1, &fds, NULL, NULL, &tv);
		if(ret < 0) 
			continue;
		if(!(ret > 0 && FD_ISSET(skfd, &fds)))
			continue;

		/* receive data */ 
		rcvlen = recv(skfd, &buf, sizeof(buf), 0);
//		rcvlen = recv(skfd, &buf, 3, 0);
		if (rcvlen > 0) {
			printf("times = %d,%s\n",i++, buf);
#if 0
			if(strstr("add",buf) || strstr("cha",buf))
				printf("you add a device\n");
			else
				printf("you remove a device\n");
#endif
		}
	}
	close(skfd);
	return 0;
}

main()
{
	thread_net_link();
}
