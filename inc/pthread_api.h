#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define REMOVE_USB	0
#define ADD_USB		1
#define KONG_USB	2
#define FIND		3
#define CHECKAPP	4
#define INSTALLAPP	5
#define	DATA_READY	6
#define WAITDATA	7



int usb_thread_init();
int main_thread_init();
int download_thread_init();
int app_thread_init();
int file_thread_init();
int net_thread_init(); 
int mutex_thread_init();

void mutex_pthread_modules_kill();
void net_pthread_modules_kill();
void exit_sock();
void allpthread_exit();
void cleansig();
	
#ifdef __cplusplus
}
#endif
