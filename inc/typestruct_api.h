#include <stdio.h>

#define MAXNU	2000
#define APPMAXNU 200	
#define BOOKMAXNU   2000	

#define SIG_START 0xAC
#define CMD_IMAGE  0X01
#define CMD_VIDEO  0X02
#define CMD_MUSIC  0X03
#define CMD_APP    0X04
#define CMD_MMS    0X05
#define CMD_BOOK   0X06
#define CMD_STORAGE 0X07
#define CMD_SENDMMS 0X08
#define CMD_CALLPHONE	9	
#define CMD_ALL			10


#ifdef __cplusplus
extern "C" {
#endif
	typedef struct __fileinfo{
		char filesize[16];
		char filepath[200];
		char filename[50];
	}fileinfo_t;

	typedef struct __allinfo{
		int count;
		fileinfo_t get_info[MAXNU];
	}media_t;


	typedef struct __appinfo{
		int  apppath;       // in sdcard or phonestore 0 is on phone 1 is on sdcard
		int  appattribute;  // system app or user app
		char appname[50];
		char apppackname[100];
		char appversion[15];
		char appsize[16];
	}appinfo_t;

	typedef struct __bookinfo{
		char bookname[20]; 
		char booknumber[18];
	}bookinfo_t;

	typedef struct __mmsinfo{
		char mmsname[20];
		char mmsnumber[18];
		char mmsbody[1024*2];
		char mmsdate[25];
		char typeId; 
	}mmsinfo_t;

	typedef struct __sendmessage{
		char mmsnumber[18];
		char mmsdata[1024];
	}sendmessage_t;

	typedef struct __storageinfo{
		char sdSize[32];            // SD卡总容量
		char sdAvail[32];           // SD卡剩余容量
		char memoryAvail[32];       // 手机内存剩余容量
		char memorySize[32];        // 手机内存总容量
	}storageinfo_t;

	typedef struct __allappnfo{
		int count;
		appinfo_t get_info[APPMAXNU];
	}allappinfo_t;

	typedef struct __allbookinfo{
		int count;
		bookinfo_t get_info[BOOKMAXNU];
	}allbookinfo_t;


	typedef struct __allmmsinfo{
		int count;
		mmsinfo_t get_info[BOOKMAXNU];
	}allmmsinfo_t;


	//	allappinfo_t appinfo;


	void getappinfo(allappinfo_t *uiappinfo);
	void getmmsinfo(allmmsinfo_t *uiappinfo);
	void getbookinfo(allbookinfo_t *uibookinfo);
	void getstorageinfo(storageinfo_t *uistorageinfo);
	void setmessageinfo(char *char_mmsnumber,char *char_mmsdata);
	void setcallphone(char *phonenumber); 

#ifdef __cplusplus
}
#endif
