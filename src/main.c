#include <stdio.h>
#include <string.h>
#include "add.h"
#include "recv.h"
#include "config.h"

int
main(int argc, char *argv[]) 
{
	printf("hello world.\n");
	printf("all the world.\n");

	int a = 10, b = 20;
	int c;
	c = add(a, b);
	printf("the add result is:%d\n", c);

	a = 20, b = 10;
	c = divinteger(a, b);
	printf("the div result is:%d\n", c);

	char str[100];
	memset(str, 0, 100);
	readn(str, 100);
	printf("the str is:%s\n", str);
	char *filename = "sysconfig.txt";
	c = getconfig(filename);
	printf("the getconfig result is:%d\n", c);

	return 0;
}
