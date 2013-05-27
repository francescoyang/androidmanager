#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include "manager_api.h"
#include "typestruct.h"

int read_shfile(char *argv,char *readbuf,int readlen)
{
	FILE * stream;
	int len = 0;
	char tmpbuf[20];


	memset(tmpbuf,0,20);
	stream = fopen(argv,"r");
	if(!stream) {
		printf("opoen devicelistfile error \n");
		return 0;
	}
	fread(tmpbuf,readlen,1,stream);

	if(!memcmp((void*)tmpbuf,"unknown",7))
	{
		printf("unknown devices\n");
		return 0;
	}

	printf("tmpbuf is %s\n",tmpbuf);
	tmpbuf[ strlen(tmpbuf) -1 ] = '\0';
	memcpy(readbuf,tmpbuf,len);
	fclose(stream);
	return 1;
}

int exec_system(char *argv)
{
	pid_t status;
	char version[20];

	memset(version,0,20);

	printf("%s",argv);
	status = system(argv);

	if (-1 == status)
	{
		printf("system error!");
	}
	else
	{
		printf("exit status value = [0x%x]\n", status);

		if (WIFEXITED(status))
		{
			if (0 == WEXITSTATUS(status))
			{
				printf("run shell script successfully.\n");
				/*
				read_shfile("./etc/vusr/version.file",version,3);
				return(atoi(version));
				*/
				return 1;
			}
			else
			{
				printf("run shell script fail, script exit code: %d\n", WEXITSTATUS(status));
				return 0;
			}
		}
		else
		{
			printf("exit status = [%d]\n", WEXITSTATUS(status));
			return 0;
		}
	}

	return 1;
}

int sh_module(int adbcmd,char *argv)
{
	char endcmd[MAXLEN] = {0};
	memset(endcmd,0,MAXLEN);

	switch(adbcmd)
	{
		case ADB_SENDMMS:
			//			sprintf(endcmd,"%s %s","./bin/adb uninstall -k",argv);
			sprintf(endcmd,"%s %s","./bin/adb shell pm uninstall -k",argv);
			if(exec_system(endcmd))
			{
				regetinfo(CMD_APP);
			}

			return 1;
			break;
		case ADB_INSTALL:
			sprintf(endcmd,"%s %s","./bin/adb install -r",argv);  // -s sdcard -f flash
//			regetinfo(CMD_APP);
			if(exec_system(endcmd))
			{
				regetinfo(CMD_APP);
			}	
			return 1;
			break;
		case ADB_UNINSTALL:
			//			sprintf(endcmd,"%s %s","./bin/adb uninstall -k",argv);
			sprintf(endcmd,"%s %s","./bin/adb shell pm uninstall -k",argv);
			if(exec_system(endcmd))
			{
				regetinfo(CMD_APP);
			}

			return 1;
			break;
		case ADB_DEVICES:
			//			sprintf(endcmd,"%s","./bin/adb get-serialno > ./etc/tmp/devices.list");
			return (exec_system("./bin/adb get-serialno > ./etc/tmp/devices.list\n"));
			break;
		case ADB_PUSH:
			sprintf(endcmd,"%s %s","./bin/adb",argv);
			return (exec_system(endcmd));
			break;
		case ADB_PULL:
			sprintf(endcmd,"%s %s","./bin/adb",argv);
			return (exec_system(endcmd));
			break;
		case ADB_CHECKVERSION:
//			return (exec_system("./bin/adb shell ls /mnt/sdcard/phonemanager/versions/ > ./etc/vusr/version.file\n"));
			return 1;
			break;
		default :
			return 0;
			break;

	}
}



