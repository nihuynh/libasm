/*
 * File: cu_test.h
 * File Created: 13/02/2025 21:19
 * Author: Nicolas Huynh at (nico.huynh@gmail.com)
 * -----
 * Description: CU_test is a framework for unit test.
 *  Single C header
 *  No heap allocations
 * Copyright 2025 NH
 *
 * TODO: Fix test report as error depending on the order
 * TODO: Add quiet some log
 * TODO: Test memory footprint
 * TODO: Add leak testing
 * TODO: Add random test
 * TODO: Add debug for memory
 * TODO: Add option parsing
 * TODO: Option to disable colors
 * TODO: Add setup and teardown
 * TODO: Handle hanging
 * TODO: Handle segv
 */

#ifndef CU_TEST_H
# define CU_TEST_H
# include <stdio.h>
# include <stdbool.h>
# include <time.h>

/*
** Data
*/
typedef struct s_cu_result {
    int        pass;
    int        fail;
    const char *str;
    clock_t    time;
} t_cu_result;

static t_cu_result cu_suite;
// str: name of the test suite (int hold the tests results)
static t_cu_result cu_runner;
// str: test fn as str (test_fn in CU_RUN)
static t_cu_result cu_run_reg;
// str: current test section (int used as stop watch during the test run)

/*
** Formating
*/
# define _CU_COLOR_FAIL     "\33[31m"
# define _CU_COLOR_PASS     "\33[32m"
# define _CU_COLOR_RESET    "\033[0m"

# define _CU_RUN_RESULT     "[%d / %d]"_CU_COLOR_RESET"\n"
# define _CU_RUN_TIMER      "\033[62G(~%.3fms)"
# define _CU_SUCCESS_FORMAT "✅ %s:%s"_CU_RUN_TIMER"\033[76G"_CU_COLOR_PASS _CU_RUN_RESULT
# define _CU_ERROR_FORMAT   "❌ %s:%s"_CU_RUN_TIMER"\033[74G"_CU_COLOR_FAIL _CU_RUN_RESULT

/*
** Macros:
*/
// Suite:
# define CU_BEGIN(_cu_title)   do { _cu_res_set_str("CU_TEST -> ", _cu_title, &cu_suite); } while (0)
# define CU_RUN(test_fn)       do { _cu_res_set_str(" --- testing fn -> ", #test_fn, &cu_runner); test_fn(); } while (0)
# define CU_END                do { return (_cu_end()); } while (0)
// Runner:
# define CU_RUN_START          do { _cu_run_start(); } while (0)
# define CU_TEST(cond)         do { _cu_res_test(&cu_runner, !(!(cond))); } while (0)
# define CU_SECTION(_cu_title) do { _CU_SECTION(_cu_title); } while (0)
# define CU_RUN_END            do { _cu_run_end(); return; } while (0)

/*
** Polymorphic expect
*/
# define CU_EXPECT(_cu_type, _cu_value, _cu_expected) _CU_EXPECT(_cu_type, _cu_value, _cu_expected, __FILE__, __LINE__)
# define _CU_EXPECT(_cu_et, _cu_v, _cu_e, _cu_file, _cu_line) \
        do { \
            if (!_cu_res_test(&cu_runner, _CU_COND_TYPE_##_cu_et(_cu_v, _cu_e))) \
            { printf( \
                  "❌  Failure during (%s:%s) at (%s:%d)\n\t%s = "_CU_DUMP_TYPE_##_cu_et "\tExpected: "_CU_DUMP_TYPE_## \
                  _cu_et "\n", cu_runner.str, cu_run_reg.str, _cu_file, _cu_line, #_cu_v, _cu_v, _cu_e); } \
            else if (cu_run_reg.fail != cu_runner.fail) { printf("✅ %s:%s\n", cu_runner.str, cu_run_reg.str); } \
        } while (0)

# define CU_PASS                     do { CU_EXPECT(bool, true, true); } while (0)
# define CU_FAIL                     do { CU_EXPECT(bool, true, false); } while (0)
/*
** Polymorphic prints & conditons for CU_EXPECT
*/
# define _CU_COND_TYPE_NUM_EQU(a, b) ((a) == (b))
# define _CU_COND_TYPE_str(a, b)     (strcmp((const char*)a, (const char*)b) == 0)
// Derive cond
// # define _CU_COND_TYPE_float(_cu_a, _cu_b) !(!(_cu_a == _cu_b)))
# define _CU_COND_TYPE_int(a, b)     _CU_COND_TYPE_NUM_EQU(a, b)
# define _CU_COND_TYPE_long(a, b)    _CU_COND_TYPE_NUM_EQU(a, b)
# define _CU_COND_TYPE_short(a, b)   _CU_COND_TYPE_NUM_EQU(a, b)
# define _CU_COND_TYPE_size_t(a, b)  _CU_COND_TYPE_NUM_EQU(a, b)
# define _CU_COND_TYPE_ssize_t(a, b) _CU_COND_TYPE_NUM_EQU(a, b)
# define _CU_COND_TYPE__Bool(a, b)   _CU_COND_TYPE_NUM_EQU(a, b)
# define _CU_COND_TYPE_ptr(a, b)     _CU_COND_TYPE_NUM_EQU(a, b)


// Prints
// # define _CU_DUMP_TYPE_float  "%f"
# define _CU_DUMP_TYPE_int     "%d"
# define _CU_DUMP_TYPE_long    "%ld"
# define _CU_DUMP_TYPE_short   "%hd"
# define _CU_DUMP_TYPE_size_t  "%zu"
# define _CU_DUMP_TYPE_ssize_t "%zd"
# define _CU_DUMP_TYPE_str     "[%s]\n"
# define _CU_DUMP_TYPE__Bool   _CU_DUMP_TYPE_int
# define _CU_DUMP_TYPE_ptr     "%p"

/*
** Functions :
*/
// Misc fonctions:
bool _cu_res_test(t_cu_result *result, bool cond) {
    (cond) ? result->pass++ : result->fail++;
    return (cond);
}
void _cu_res_reset(t_cu_result *result) {
    result->pass = 0;
    result->fail = 0;
}
void _cu_res_print(const char *head, t_cu_result *res, int pass, int all) {
    printf(((pass == all) ? _CU_SUCCESS_FORMAT : _CU_ERROR_FORMAT), head, res->str,
           ((double)(clock() - res->time) / (CLOCKS_PER_SEC / 1000)), pass, all);
}
void _cu_res_set_str(const char *head, const char *new_str, t_cu_result *result) {
    result->str = new_str;
    result->time = clock();
    printf("%s%s\n", head, new_str);
}

// Suite fonctions:
int _cu_end(void) {
    int res = (cu_suite.fail != 0);
    _cu_res_print("\tSummary", &cu_suite, cu_suite.pass, cu_suite.pass + cu_suite.fail);
    // Clear the global variables of CU_TEST
    _cu_res_reset(&cu_suite);
    cu_suite.str = NULL;
    _cu_res_reset(&cu_runner);
    // cu_runner.str = NULL;
    _cu_res_reset(&cu_run_reg);
    cu_run_reg.str = NULL;
    return (res);
}

// Runner fonctions:
void _cu_run_start(void) {
    _cu_res_reset(&cu_runner);
    _cu_res_reset(&cu_run_reg);
    cu_run_reg.str = NULL;
}
void _CU_SECTION(const char *section_title) {
    if (cu_run_reg.str != NULL) {
        _cu_res_print(cu_runner.str, &cu_run_reg, (cu_runner.pass - cu_run_reg.pass),
                      (cu_runner.pass + cu_runner.fail - cu_run_reg.pass - cu_run_reg.fail));
    }
    cu_run_reg.str = section_title;
    cu_run_reg.time = clock();
    cu_run_reg.pass = cu_runner.pass;
    cu_run_reg.fail = cu_runner.fail;
}
void _cu_run_end(void) {
    _cu_res_print(cu_runner.str, &cu_run_reg, (cu_runner.pass - cu_run_reg.pass),
                  (cu_runner.pass + cu_runner.fail - cu_run_reg.pass - cu_run_reg.fail));
    _cu_res_print("  completed", &cu_runner, cu_runner.pass, cu_runner.pass + cu_runner.fail);
    if ((cu_runner.pass + cu_runner.fail) > 0) {
        _cu_res_test(&cu_suite, (cu_runner.fail == 0));
    }
    _cu_res_reset(&cu_runner);
    _cu_res_reset(&cu_run_reg);
}

#endif
