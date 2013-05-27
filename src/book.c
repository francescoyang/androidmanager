#include <stdio.h>
//#include "typestruct.h"
#include "typestruct.h"

#ifdef __cplusplus
extern "C" {
#endif

	void getbookinfo(allbookinfo_t *uibookinfo)
	{
		int i = 0;

//		memset(&uibookinfo, 0, sizeof(allbookinfo_t));

		uibookinfo->count = bookinfo.count;
		for(i = 0;i <= bookinfo.count; i ++)
		{
			memcpy(uibookinfo->get_info[i].bookname,&bookinfo.get_info[i].bookname,20);
			memcpy(uibookinfo->get_info[i].booknumber,&bookinfo.get_info[i].booknumber,18);
//			printf("%s,%s\n",uibookinfo->get_info[i].bookname,uibookinfo->get_info[i].booknumber);
		}
	}

#ifdef __cplusplus
}
#endif
