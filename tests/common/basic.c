/*
 * Copyright (c) 2019 HabanaLabs Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "hlthunk.h"
#include "hlthunk_tests.h"

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <limits.h>
#include <cmocka.h>
#include <stdio.h>

void test_open_device_failure(void **state)
{
	(void) state; /* unused */
	int fd, ret;

	fd = hlthunk_open(NULL);
	assert_in_range(fd, 0, INT_MAX);
	ret = hlthunk_open(NULL);
	assert_in_range(ret, INT_MIN, -1);
	hlthunk_close(fd);
}

void test_open_device_success(void **state)
{
	(void) state; /* unused */
	int fd;

	fd = hlthunk_open(NULL);
	assert_in_range(fd, 0, INT_MAX);
	hlthunk_close(fd);
}

const struct CMUnitTest open_device_tests[] = {
	cmocka_unit_test(test_open_device_failure),
	cmocka_unit_test(test_open_device_success),
};

int main(void)
{
	int rc;

	rc = hlthunk_tests_init();
	if (rc) {
		printf("Failed to init tests library %d\n", rc);
		return rc;
	}

	rc = cmocka_run_group_tests(open_device_tests, NULL, NULL);

	hlthunk_tests_fini();

	return rc;
}