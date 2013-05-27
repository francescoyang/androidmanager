#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif


#define MAXLEN  500 


#define SUCCESS			1
#define FAILURE			0

#define ADB_INSTALL		1
#define ADB_UNINSTALL	2
#define ADB_DEVICES		3
#define ADB_PUSH		4 
#define ADB_PULL		5
#define ADB_CHECKVERSION	6
#define ADB_SENDMMS			7	


typedef struct __deviceslist{
	char * list[16];
	char current_device[16];
}deviceslist_t;

int adb_ah();
int app_install(char *argv);
int app_uninstall(char *argv);

char * app_show(char *argv);
int  find_devices();
void get_curdev(char *devname);

int monitor_usb();
void c_delay(int num);
int checkappversion();
void tmpclean();
int amservicestart();
int waitdata();
int refreshinfo();

int sh_module(int adbcmd, char *argv);
int read_shfile(char *argv,char *readbuf,int readlen);
void setinstallapp(char *apppath);
void setsendmmsinfo(char *qtmms_no, char *qtmms_info);
int toinstallapp();
int tosendmms();
void system_exit();
int regetinfo(int argc);

#ifdef __cplusplus
}
#endif
