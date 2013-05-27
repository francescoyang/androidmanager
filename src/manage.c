#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>  
#include <sys/types.h>  
#include <string.h>
#include "manager_api.h"

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct __sendmmsinfo{
		char mms_no[15];
		char mms_info[200];
	}sendmmsinfo_t;

	sendmmsinfo_t sendmmsinfo;


	char shcmd[MAXLEN] = {0};
	char installapp[100] = {0};

	int len  = 0;
	char devicelist[20];
	deviceslist_t  s_devices;


	int app_uninstall(char *argv)
	{
		return(sh_module(ADB_UNINSTALL,argv));
	}

	void system_exit()
	{
		printf("system exit\n");
		net_pthread_modules_kill();
		system("./bin/adb shell am broadcast -a ServiceStop");
	}

	void tmpclean()
	{
		system("rm -rf ./etc/tmp/*");
	}

	int app_install(char *argv)
	{
		return 0;
	}


	char * app_show(char *argv)
	{
		return "test";
	}

	void c_delay(int num)
	{
		sleep(num);
	}	
	int checkappversion()
	{
		return(sh_module(ADB_CHECKVERSION,NULL));
	}

	void get_curdev(char *devname)
	{
//		memcpy(devname,s_devices.current_device,16);
	}
	int find_devices()
	{

		memset(devicelist,0,20);
		sh_module(ADB_DEVICES,NULL);
		usleep(50000);
		system("./bin/readdevice.sh");
		if(read_shfile("./etc/vusr/devices.list",s_devices.current_device,15))
		{
			printf("%s\n",s_devices.current_device);
			return 1;
		}else {
			return 0;
		}
	}

	int toinstallapp()
	{
		printf("installapp is %s\n",installapp);
		return(sh_module(ADB_INSTALL,installapp));
	}

	int tosendmms()
	{
		printf("send mms no is %s,info is %s\n",sendmmsinfo.mms_no, sendmmsinfo.mms_info);
	//	return(sh_module(ADB_SENDMMS,sendmmsinfo.mms_no, sendmmsinfo.mms_info));
	}


	void setsendmmsinfo(char *qtmms_no, char *qtmms_info)
	{
		memset((char *)&sendmmsinfo, 0, sizeof(sendmmsinfo_t));
		memcpy(sendmmsinfo.mms_no,qtmms_no,strlen(qtmms_no));
		memcpy(sendmmsinfo.mms_info,qtmms_info,strlen(qtmms_info));
	}

	void setinstallapp(char *apppath)
	{
		memset(installapp, 0, 100);
		memcpy(installapp,apppath,strlen(apppath));
	}

#ifdef __cplusplus
}
#endif
