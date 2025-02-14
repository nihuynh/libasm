#include "cu_test.h"

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
    CU_RUN_SECTION("basic");
    CU_TEST(0 == ft_isodd(10));
    CU_TEST(1 == ft_isodd(11));
    CU_TEST(0 == ft_isodd(0));

    CU_RUN_SECTION("negative value");
    CU_TEST(0 == ft_isodd(-10));
    CU_TEST(1 == ft_isodd(-1));
    CU_TEST(0 == ft_isodd(-0));
    CU_RUN_END;
    return ;
}

void	test_add(void)
{
    CU_RUN_START;
    CU_RUN_SECTION("basic");
    CU_TEST(69 == ft_add(55, 14));
    CU_TEST(42 == ft_add(20, 22));
    CU_RUN_SECTION("negatif");

    CU_TEST(-1 == ft_add(-21, 20));
    CU_RUN_SECTION("errorous tests");
    CU_TEST(42 == ft_add(2, 22));
    CU_TEST(42 == ft_add(20, 2));
    CU_RUN_END;
    return ;
}
void	test_reset_int(void)
{
    int a;
    ft_reset_int(&a);
    CU_RUN_START;
    CU_RUN_SECTION("basic");
    CU_TEST(0 == a);
    CU_RUN_SECTION("reset after a set");
    a = 10;
    CU_TEST(10 == a);
    ft_reset_int(&a);
    CU_TEST(0 == a);
    CU_RUN_SECTION("errorous tests");
    CU_TEST(10 == a);
    CU_RUN_END;
    return ;
}


int     main(void)
{
    CU_BEGIN("Test project for cu_test developpement");
    CU_RUN(test_isodd);
    CU_RUN(test_add);
    CU_RUN(test_reset_int);
    CU_END;
	return (0);
}