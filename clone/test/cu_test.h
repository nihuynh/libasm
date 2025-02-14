/*
 * File: cu_test.h
 * File Created: 13/02/2025 21:19
 * Author: Nicolas Huynh at (nico.huynh@gmail.com)
 * -----
 * Description: Single header for Unit testing C
 *  CU_test goal is to accelerate unit test developpement.
 *  Small memory usage and no heap allocation.
 * Copyright 2025 NH
 */

#ifndef CU_TEST_H
# define CU_TEST_H
# include <stdio.h>
# include <stdbool.h>

/*
** Data
*/
typedef struct          s_cu_result
{
    int                 pass;
    int                 fail;
    const char          *str;
}                       t_cu_result;

static t_cu_result cu_suite;    // str: suite title
static t_cu_result cu_runner;   // str: current test fn
static t_cu_result cu_run_reg;  // str: section title

/*
** Macros:
*/
// Suite:
# define CU_BEGIN(title) do { _cu_result_update_str("\nCU_TEST -> ", title, &cu_suite); } while (0)
# define CU_RUN(test_fn) do { _cu_result_update_str("\n\ttesting fn -> ", #test_fn, &cu_runner); test_fn(); } while (0)
# define CU_END do { _cu_end(); } while (0)
// Runner:
# define CU_RUN_START do { _cu_run_start(); } while (0)
# define CU_TEST(cond) do { _cu_result_test(&cu_runner, !(!(cond))); } while (0)
# define CU_EXPECT(val, expected) do { _cu_result_expect(!(!(val == expected)), #val, #expected); } while (0)
# define CU_RUN_SECTION(section_title) do { _cu_run_section(section_title); } while (0)
# define CU_RUN_END do { _cu_run_end(); } while (0)

/*
** Formating
*/
# define _CU_SUCCESS_FORMAT "\033[64G\33[32m[%d / %d]\033[0m\n"
# define _CU_ERROR_FORMAT "\033[64G\33[31m[%d / %d]\033[0m\n"

/*
** Functions :
*/
// Misc fonctions:
void	_cu_result_test(t_cu_result *result, bool cond) {(cond) ? result->pass++ : result->fail++;}
void	_cu_result_expect(bool cond, const char *val, const char *expected)
{
    int fail = cu_runner.fail;
    _cu_result_test(&cu_runner, cond);
    if (fail != cu_runner.fail)
        printf("Failure on : %s == %s\n", val, expected);
}

void	_cu_result_reset(t_cu_result *result)
{
    result->pass = 0;
    result->fail = 0;
}
void	_cu_result_print(const char *head, const char *subject, int pass, int all)
{
    if (pass == all)
        printf("%s : %s"_CU_SUCCESS_FORMAT, head, subject, pass, pass);
    else
        printf("%s : %s"_CU_ERROR_FORMAT, head, subject, pass, all);
}
void	_cu_result_update_str(const char *head, const char *new_str, t_cu_result *result)
{
    result->str = new_str;
    printf("%s%s\n", head, new_str);
}

// Suite fonctions:
void	_cu_end(void)
{
    _cu_result_print("\nBilan", cu_suite.str, cu_suite.pass, cu_suite.pass + cu_suite.fail);
    // Clear the global variables of CU_TEST
    _cu_result_reset(&cu_suite);
    cu_suite.str = NULL;
    _cu_result_reset(&cu_runner);
    // cu_runner.str = NULL;
    _cu_result_reset(&cu_run_reg);
    cu_run_reg.str = NULL;
}

// Runner fonctions:
void	_cu_run_start(void)
{
    _cu_result_reset(&cu_runner);
    _cu_result_reset(&cu_run_reg);
    cu_run_reg.str = NULL;
}
void	_cu_run_section(const char *section_title)
{
    if (cu_run_reg.str != NULL)
    {
        _cu_result_print(cu_runner.str, cu_run_reg.str, (cu_runner.pass - cu_run_reg.pass),
            (cu_runner.pass + cu_runner.fail - cu_run_reg.pass - cu_run_reg.fail));
    }
    cu_run_reg.str = section_title;
    cu_run_reg.pass = cu_runner.pass;
    cu_run_reg.fail = cu_runner.fail;
}
void	_cu_run_end(void)
{
    _cu_result_print(cu_runner.str, cu_run_reg.str, (cu_runner.pass - cu_run_reg.pass),
        (cu_runner.pass + cu_runner.fail - cu_run_reg.pass - cu_run_reg.fail));
    _cu_result_print("\tcompleted", cu_runner.str, cu_runner.pass, cu_runner.pass + cu_runner.fail);
    _cu_result_test(&cu_suite, (cu_runner.fail == 0));
    _cu_result_reset(&cu_runner);
    _cu_result_reset(&cu_run_reg);
}

#endif