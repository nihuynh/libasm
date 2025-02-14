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

static t_cu_result cu_suite;
static t_cu_result cu_runner;
static t_cu_result cu_run_reg;

/*
** Macros:
*/
// Suite:
# define CU_BEGIN(title) do { _cu_begin(title); } while (0)
# define CU_RUN(test_fn) do { _cu_run(#test_fn); test_fn(); } while (0)
# define CU_END do { _cu_end(); } while (0)
// Runner:
# define CU_RUN_START do { _cu_run_start(); } while (0)
# define CU_TEST(cond) do { _cu_result_test(&cu_runner, !(!(cond))); } while (0)
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

// Suite fonctions:
void	_cu_begin(const char *suite_title)
{
    cu_suite.str = suite_title;
    printf("%s\n", suite_title);
}
void	_cu_run(const char *test_fn_name)
{
    cu_runner.str = test_fn_name;
    printf("\n\ttesting fn: %s\n", test_fn_name);
}
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
        (cu_runner.fail == 0) ? cu_suite.pass++ : cu_suite.fail++;
    _cu_result_reset(&cu_runner);
    _cu_result_reset(&cu_run_reg);
}

#endif