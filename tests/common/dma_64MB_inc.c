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
#include <errno.h>
#include <unistd.h>

DMA_1KB_INC_DRAM(test_dma_dram_size_64MB, state, 64 * 1024 * 1024)
DMA_1KB_INC_DRAM(test_dma_dram_size_128MB, state, 128 * 1024 * 1024)
DMA_1KB_INC_DRAM(test_dma_dram_size_192MB, state, 192 * 1024 * 1024)
DMA_1KB_INC_DRAM(test_dma_dram_size_256MB, state, 256 * 1024 * 1024)

const struct CMUnitTest dma_64MB_inc_tests[] = {
	cmocka_unit_test_setup(test_dma_dram_size_64MB,
			hl_tests_ensure_device_operational),
	cmocka_unit_test_setup(test_dma_dram_size_128MB,
			hl_tests_ensure_device_operational),
	cmocka_unit_test_setup(test_dma_dram_size_192MB,
			hl_tests_ensure_device_operational),
	cmocka_unit_test_setup(test_dma_dram_size_256MB,
			hl_tests_ensure_device_operational),
};

static const char *const usage[] = {
    "dma_64MB_inc [options]",
    NULL,
};

int main(int argc, const char **argv)
{
	char *test_names_to_run;

	test_names_to_run = getenv("HLTHUNK_TESTS_NAMES");
	if (test_names_to_run)
		cmocka_set_test_filter(test_names_to_run);

	hltests_parser(argc, argv, usage, HLTHUNK_DEVICE_INVALID,
		dma_64MB_inc_tests,
		sizeof(dma_64MB_inc_tests) / sizeof((dma_64MB_inc_tests)[0]));

	return cmocka_run_group_tests(dma_64MB_inc_tests, hltests_setup,
					hltests_teardown);
}
