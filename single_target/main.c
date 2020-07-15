#include <iconv.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dummy.h"

int main()
{
	char *dest = NULL;
	size_t destSize = 0;
	char name[]= {0x52, 0x00, 0x6f, 0x00, 0x6f, 0x00, 0x74, 0x00}; // Root -- UNICODE编码
	iconv_t cd = NULL;
	printf("name = %s \r\n", name);

	cd = iconv_open("UTF8", "UNICODE");
	if((void*)-1 == cd)
	{
		return;
	}
	size_t a = (size_t)sizeof(name);
	char * sp = name ;
//	char *outBuf = (char*)malloc(a * 4);
	char outBuf[a * 4];
	char *pout = outBuf;

	printf("sp=%p, outbuf=%p\r\n", sp, outBuf);
	memset((void *)outBuf, 0, a* 4);
	size_t b =(size_t) (a*4);
	printf("sp = %s, a=%d, b = %d\r\n",sp,  a, b);

	size_t n = iconv(cd, &sp, &a, &pout, &b);
	printf("sp=%p,  outbuf=%p\r\n",sp, outBuf);
	printf("END-outBuf:%s, name = %s \r\n", outBuf, name);

    dummy();
	return 0;
}
