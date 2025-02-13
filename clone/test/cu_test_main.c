#include "cu_dev.h"

int		ft_isodd(int value)
{
	return (value % 2) ? 1 : 0;
}

void	ft_reset_int(int *val)
{
	*val = 0;
}

int		ft_add(int a, int b)
{
	return a + b;
}

void	test_isodd()
{
    CU_RUN_START;
    CU_RUN_SECTION("Basic tests");
    CU_TEST(0 == ft_isodd(10));
    CU_TEST(1 == ft_isodd(11));
    CU_TEST(0 == ft_isodd(0));

    CU_RUN_SECTION("Negative value");
    CU_TEST(0 == ft_isodd(-10));
    CU_TEST(1 == ft_isodd(-1));
    CU_TEST(0 == ft_isodd(-0));
    CU_RUN_END;
    return ;
}

// t_cu	test_reset_int(void)
// {
// 	// t_cu counter;

// 	// counter = cu_init();
// 	// cu_run(&counter, test_isodd("Basic test", 10, 0));
// 	// cu_run(&counter, test_isodd("Basic test 2", 11, 1));
// 	// ENDSUITE(counter);

//     return
// }

// t_cu	test_isodd(void)
// {
// 	// t_cu counter;

// 	// counter = cu_init();
// 	// cu_run(&counter, test_isodd("Basic test", 10, 0));
// 	// cu_run(&counter, test_isodd("Basic test 2", 11, 1));
// 	// ENDSUITE(counter);
// }

int     main(void)
{
    CU_BEGIN("Test project for cu_test developpement");
    CU_RUN(test_isodd);
    // CU_RUN(test_reset_int);
    CU_END;
	return (0);
}