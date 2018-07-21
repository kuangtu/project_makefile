#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>
#include <cmocka_private.h>
#include "recv.c"

static void
test_readn(void **state)
{
	char str[100];
	memset(str, 0, 100);

	readn(str, 100);
	
	assert_string_equal(str, "test");


}

int
main(int argc, char *argv[]) 
{
	const UnitTest tests[] = {
		unit_test(test_readn),
	};

	run_tests(tests);

	return 0;
}
