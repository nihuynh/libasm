#ifndef CU_TEST_H
    # define CU_TEST_H
    # include <stdio.h>
    # include <stdbool.h>

    /*
    ** Macros
    */

    // Unit test common macros:
    # define CU_BEGIN(title) do { printf("\tCU_TEST : testing begins...\n%s\n\n", title); } while (0)
    # define CU_RUN(test_fn) do { printf("\ttest fn: %s\n", #test_fn); test_fn(); } while (0)
    # define CU_END do { _cu_end(); } while (0)

    // Unit test common macros:
    # define CU_RUN_START do { cu_section_old_title = NULL;\
                                _cu_result_reset(&cu_runner);\
                                _cu_result_reset(&cu_run_reg); } while (0)
    # define CU_TEST(cond) do { _cu_result_test(&cu_runner, !(!(cond))); } while (0)
    # define CU_RUN_SECTION(section_title) do { _cu_run_section(section_title); } while (0)
    # define CU_RUN_END do { _cu_run_end(); } while (0)

    // Helper private:
    # define _CU_RESULT_OUTCOME(result_value) (result_value == 0) ? "Success" : "Failure"

    /*
    ** Data
    */
    typedef struct  s_cu_result
    {
        int         pass;
        int         fail;
    }               t_cu_result;

    // Config
    static t_cu_result cu_suite;
    static t_cu_result cu_runner;
    static t_cu_result cu_run_reg;
    static const char *cu_section_old_title;

    /*
    ** Fn :
    */

    void	_cu_result_reset(t_cu_result *result)
    {
        result->pass = 0;
        result->fail = 0;
    }
    void	_cu_result_test(t_cu_result *result, bool cond)
    {
        (cond) ? result->pass++ : result->fail++;
    }
    void	_cu_run_section(const char *section_title)
    {
        if (cu_section_old_title == NULL)
            printf("\nsection: %s\n", section_title);
        else
        {
            printf("\nsection: %s \t[ %d passed / %d ] %s\n%s\n", cu_section_old_title,
                (cu_runner.pass - cu_run_reg.pass), 
                (cu_runner.pass + cu_runner.fail - cu_run_reg.pass - cu_run_reg.fail),
                _CU_RESULT_OUTCOME(cu_runner.fail - cu_run_reg.fail),
                section_title);
        }
        cu_section_old_title = section_title;
        cu_run_reg.pass = cu_runner.pass;
        cu_run_reg.fail = cu_runner.fail;
    }

    void	_cu_run_end(void)
    {
        printf("\nsection: %s \t[ %d passed / %d ] %s\n", cu_section_old_title,
            (cu_runner.pass - cu_run_reg.pass), 
            (cu_runner.pass + cu_runner.fail - cu_run_reg.pass - cu_run_reg.fail),
            _CU_RESULT_OUTCOME(cu_runner.fail - cu_run_reg.fail));

        printf("\n\t%s on the tests: [ %d passed / %d ]\n", _CU_RESULT_OUTCOME(cu_runner.fail),
            cu_runner.pass, cu_runner.pass + cu_runner.fail);
        (cu_runner.fail == 0) ? cu_suite.pass++ : cu_suite.fail++;
        _cu_result_reset(&cu_runner);
        _cu_result_reset(&cu_run_reg);
    }

    void	_cu_end(void)
    {
        printf("\n%s\t[ %d / %d ]\n", _CU_RESULT_OUTCOME(cu_suite.fail), cu_suite.pass, \
            cu_suite.pass + cu_suite.fail);
        // Clear the global variables of CU_TEST
        cu_section_old_title = NULL;
        _cu_result_reset(&cu_suite);
        _cu_result_reset(&cu_runner);
        _cu_result_reset(&cu_run_reg);
    }

#endif
   
   
   
   //  /* file: minunit.h */
   //  #define mu_assert(message, test) do { if (!(test)) return message; } while (0)
   //  #define mu_run_test(test) do { char *message = test(); tests_run++; \
   //                                 if (message) return message; } while (0)
   //  extern int tests_run;
   
   // int carry;
   
   // carry = ft_isodd(var);
   // if (DEBUG)
   //     cu_dump_int(var, expect_out, carry);
   // VERIFY(carry == expect_out, msg);
   // return (EXIT_TEST(carry == expect_out));