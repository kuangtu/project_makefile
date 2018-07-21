#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <cmocka_private.h>
#include "config.c"

static void
test_getconfig(void **state)
{
	char *szfilename = "config.txt";
	int res;
	res = getconfig(szfilename);
	assert_int_equal(res, 2);

}

int
main(int argc, char *argv[]) 
{
	const UnitTest tests[] = {
		unit_test(test_getconfig),
	};

	run_tests(tests);

	return 0;
}
