#include <stdio.h>
#include "typestruct.h"

#ifdef __cplusplus
extern "C" {
#endif

	void getstorageinfo(storageinfo_t *uistorageinfo)
	{
			memcpy(uistorageinfo->sdSize,&storageinfo.sdSize,32);
			memcpy(uistorageinfo->sdAvail,&storageinfo.sdAvail,32);
			memcpy(uistorageinfo->memorySize,&storageinfo.memorySize,32);
			memcpy(uistorageinfo->memoryAvail,&storageinfo.memoryAvail,32);
	}

#ifdef __cplusplus
}
#endif
