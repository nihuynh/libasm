/*
 * File: cu_test_main.c
 * File Created: 13/02/2025 20:36
 * Author: Nicolas Huynh at (nico.huynh@gmail.com)
 * -----
 * Description: <Desc of the file goal(s)>
 * Copyright 2025 NH
 */

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
    CU_EXPECT(ft_isodd(10), 0);
    CU_EXPECT(ft_isodd(11), 1);
    CU_EXPECT(ft_isodd(0), 0);

    CU_RUN_SECTION("negative value");
    CU_EXPECT(ft_isodd(-10), 0);
    CU_EXPECT(ft_isodd(-1), 1);
    CU_EXPECT(ft_isodd(-0), 0);
    CU_RUN_END;
    return ;
}

void	test_add(void)
{
    CU_RUN_START;
    CU_RUN_SECTION("basic");
    CU_EXPECT(ft_add(55, 14), 55 + 14);
    CU_EXPECT(ft_add(20, 22), 20 + 22);
    CU_RUN_SECTION("negatif");

    CU_EXPECT(ft_add(-21, 20), -1);
    CU_RUN_SECTION("errorous tests");
    CU_EXPECT(ft_add(2, 22), 4);
    CU_EXPECT(ft_add(20, 2), 4);
    CU_RUN_END;
    return ;
}
void	test_reset_int(void)
{
    int a;
    ft_reset_int(&a);
    CU_RUN_START;
    CU_RUN_SECTION("basic");
    CU_EXPECT(a, 0);
    CU_RUN_SECTION("reset after a set");
    a = 10;
    CU_EXPECT(a, 10);
    ft_reset_int(&a);
    CU_EXPECT(a, 0);
    CU_RUN_SECTION("errorous tests");
    CU_EXPECT(a, 10);
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