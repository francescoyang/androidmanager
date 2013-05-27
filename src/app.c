#include <stdio.h>
//#include "typestruct.h"
#include "typestruct.h"

#ifdef __cplusplus
extern "C" {
#endif

	void getappinfo(allappinfo_t *uiappinfo)
	{
		int i = 0;

		memset(uiappinfo, 0, sizeof(allappinfo_t));

		uiappinfo->count = appinfo.count;
//		printf("appinfo.count = %d\n",uiappinfo->count);
		for(i = 0;i <= appinfo.count; i ++)
		{
			uiappinfo->get_info[i].apppath = appinfo.get_info[i].apppath;
			uiappinfo->get_info[i].appattribute = appinfo.get_info[i].appattribute;

			memcpy(uiappinfo->get_info[i].appname,&appinfo.get_info[i].appname,50);
			memcpy(uiappinfo->get_info[i].apppackname,&appinfo.get_info[i].apppackname,100);
			memcpy(uiappinfo->get_info[i].appversion,&appinfo.get_info[i].appversion,15);
			memcpy(uiappinfo->get_info[i].appsize,&appinfo.get_info[i].appsize,16);
		}

	}

#ifdef __cplusplus
}
#endif
