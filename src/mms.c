#include <stdio.h>
//#include "typestruct.h"
#include "typestruct.h"

#ifdef __cplusplus
extern "C" {
#endif

	void getmmsinfo(allmmsinfo_t *uimmsinfo)
	{
		int i = 0;

//		memset(&uimmsinfo, 0, sizeof(allmmsinfo_t));

		uimmsinfo->count = mmsinfo.count;
		printf("uimmsinfo->count  = %d\n",uimmsinfo->count);
		for(i = 0;i <= mmsinfo.count; i ++)
		{
			memcpy(uimmsinfo->get_info[i].mmsname,&mmsinfo.get_info[i].mmsname,20);
			memcpy(uimmsinfo->get_info[i].mmsnumber,&mmsinfo.get_info[i].mmsnumber,18);
			memcpy(uimmsinfo->get_info[i].mmsbody,&mmsinfo.get_info[i].mmsbody,1024*2);
			memcpy(uimmsinfo->get_info[i].mmsdate,&mmsinfo.get_info[i].mmsdate,25);
//			printf("%s,%s,%s,%s\n",uimmsinfo->get_info[i].mmsname,uimmsinfo->get_info[i].mmsnumber,uimmsinfo->get_info[i].mmsbody,uimmsinfo->get_info[i].mmsdate);
		}
	}

#ifdef __cplusplus
}
#endif
