/*
 * File: cu_test.h
 * File Created: 13/02/2025 21:19
 * Author: Nicolas Huynh at (nico.huynh@gmail.com)
 * -----
 * Description: Single header for Unit testing C
 *  CU_test goal is to accelerate unit test developpement.
 *  Small memory usage and no heap allocation.
 * Copyright 2025 NH
 *
 * TODO: Add timers
 * TODO: Add quiet some log
 * TODO: Test memory footprint
 * TODO: Add debug for float
 * TODO: Add leak testing
 * TODO: Add setup and teardown
 * TODO: Add random test
 * TODO: Add debug for str
 * TODO: Add debug for memory
 * TODO: Add option parsing
 */

#ifndef CU_TEST_H
# define CU_TEST_H
# include <stdio.h>
# include <stdbool.h>

/*
** Data
*/
typedef struct s_cu_result
{
    int        pass;
    int        fail;
    const char *str;
} t_cu_result;

static t_cu_result cu_suite;    // str: name of the test suite (int hold the tests results)
static t_cu_result cu_runner;   // str: test fn as str (test_fn in CU_RUN)
static t_cu_result cu_run_reg;  // str: current test section (int used as stop watch during the test run)

/*
** Macros:
*/
// Suite:
# define CU_BEGIN(_cu_title)   do { _cu_res_set_str("CU_TEST -> ", _cu_title, \
                                                    &cu_suite); } while (0)
# define CU_RUN(test_fn)       do { _cu_res_set_str("\ttesting fn -> ", \
                                                    #test_fn, &cu_runner); \
                                    test_fn(); } while (0)
# define CU_END                do { return (_cu_end()); } while (0)
// Runner:
# define CU_RUN_START          do { _cu_run_start(); } while (0)
# define CU_TEST(cond)         do { _cu_res_test(&cu_runner, !(!(cond))); \
} while (0)
# define CU_SECTION(_cu_title) do { _CU_SECTION(_cu_title); } while (0)
# define CU_RUN_END            do { _cu_run_end(); return;} while (0)

/*
** Polymorphic expect
*/

# define CU_EXPECT(_cu_e_type, _cu_v, _cu_e) do { \
            if (!_cu_res_test(&cu_runner, _CU_COND_TYPE_##_cu_e_type(_cu_v, _cu_e))) \
            printf("%s:%s\t\tFailure\n\t%s="_CU_DUMP_TYPE_##_cu_e_type \
                   "\tExpected: "_CU_DUMP_TYPE_##_cu_e_type "\n", cu_runner.str, cu_run_reg.str, \
                   #_cu_v, _cu_v, _cu_e);} while (0)
/*
** Polymorphic macros
*/
// General cond
# define _CU_COND_TYPE_NUM_EQU(a, b)         ((a) == (b))
// Derive cond
// # define _CU_COND_TYPE_float(_cu_a, _cu_b) !(!(_cu_a == _cu_b)))
# define _CU_COND_TYPE_int(a, b)             _CU_COND_TYPE_NUM_EQU(a, b)
# define _CU_COND_TYPE_long(a, b)            _CU_COND_TYPE_NUM_EQU(a, b)
# define _CU_COND_TYPE_short(a, b)           _CU_COND_TYPE_NUM_EQU(a, b)
# define _CU_COND_TYPE_size_t(a, b)          _CU_COND_TYPE_NUM_EQU(a, b)
# define _CU_COND_TYPE_ssize_t(a, b)         _CU_COND_TYPE_NUM_EQU(a, b)
# define _CU_COND_TYPE_str(a, b)             (strcmp((const char*)a, (const char*)b) == 0)
// Prints

// # define _CU_DUMP_TYPE_float  "%f"
# define _CU_DUMP_TYPE_int     "%d"
# define _CU_DUMP_TYPE_long    "%ld"
# define _CU_DUMP_TYPE_short   "%hd"
# define _CU_DUMP_TYPE_size_t  "%zu"
# define _CU_DUMP_TYPE_ssize_t "%zd"
# define _CU_DUMP_TYPE_str     "[%s]\n"

/*
** Formating
*/

# define _CU_RUN_RESULT     "[%d / %d]"
# define _CU_SUCCESS_FORMAT "\033[64G\33[32m"_CU_RUN_RESULT"\033[0m\n"
# define _CU_ERROR_FORMAT   "\033[63G\33[31m"_CU_RUN_RESULT"\033[0m\n"

/*
** Functions :
*/
// Misc fonctions:
bool _cu_res_test(t_cu_result *result, bool cond) {
    (cond) ? result->pass++ : result->fail++;
    return (cond);
}

void _cu_res_reset(t_cu_result *result)
{
    result->pass = 0;
    result->fail = 0;
}
void _cu_res_print(const char *head, const char *subject, int pass, int all)
{
    if (pass == all)
        printf("%s : %s"_CU_SUCCESS_FORMAT, head, subject, pass, pass);
    else
        printf("%s : %s"_CU_ERROR_FORMAT, head, subject, pass, all);
}
void _cu_res_set_str(const char *head, const char *new_str, t_cu_result *result)
{
    result->str = new_str;
    printf("%s%s\n", head, new_str);
}

// Suite fonctions:
int _cu_end(void)
{
    int res = (cu_suite.fail != 0);
    _cu_res_print("\nBilan", cu_suite.str, cu_suite.pass, cu_suite.pass + cu_suite.fail);
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
void _cu_run_start(void)
{
    _cu_res_reset(&cu_runner);
    _cu_res_reset(&cu_run_reg);
    cu_run_reg.str = NULL;
}
void _CU_SECTION(const char *section_title)
{
    if (cu_run_reg.str != NULL)
    {
        _cu_res_print(cu_runner.str, cu_run_reg.str, (cu_runner.pass - cu_run_reg.pass),
                      (cu_runner.pass + cu_runner.fail - cu_run_reg.pass - cu_run_reg.fail));
    }
    cu_run_reg.str = section_title;
    cu_run_reg.pass = cu_runner.pass;
    cu_run_reg.fail = cu_runner.fail;
}
void _cu_run_end(void)
{
    _cu_res_print(cu_runner.str, cu_run_reg.str, (cu_runner.pass - cu_run_reg.pass),
                  (cu_runner.pass + cu_runner.fail - cu_run_reg.pass - cu_run_reg.fail));
    _cu_res_print("  completed", cu_runner.str, cu_runner.pass, cu_runner.pass + cu_runner.fail);
    if ((cu_runner.pass + cu_runner.fail) > 0)
        _cu_res_test(&cu_suite, (cu_runner.fail == 0));
    _cu_res_reset(&cu_runner);
    _cu_res_reset(&cu_run_reg);
}

#endif
