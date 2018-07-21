#include <string.h>
#include <stdlib.h>
#include "recv.h"


size_t
readn(char *szBuf, size_t n)
{
	char *str = "test";

	memcpy(szBuf, str, strlen(str));

	return n;
}
