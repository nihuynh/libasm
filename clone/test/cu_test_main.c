/*
 * File: cu_test_main.c
 * File Created: 13/02/2025 20:36
 * Author: Nicolas Huynh at (nico.huynh@gmail.com)
 * -----
 * Description: <Desc of the file goal(s)>
 * Copyright 2025 NH
 */

#include "cu_test.h"

int ft_isodd(int value)
{
    return (value % 2) ? 1 : 0;
}

void ft_reset_int(int *val)
{
    *val = 0;
}

int ft_add(int a, int b)
{
    return a + b;
}

void test_isodd()
{
    CU_RUN_START;
    CU_SECTION("basic");
    CU_EXPECT(int, ft_isodd(10), 0);
    CU_EXPECT(int, ft_isodd(11), 1);
    CU_EXPECT(int, ft_isodd(0), 0);

    CU_SECTION("negative value");
    CU_EXPECT(int, ft_isodd(-10), 0);
    CU_EXPECT(int, ft_isodd(-1), 1);
    CU_EXPECT(int, ft_isodd(-0), 0);
    CU_RUN_END;
}

void test_add(void)
{
    CU_RUN_START;
    CU_SECTION("basic");
    CU_EXPECT(int, ft_add(55, 14), 55 + 14);
    CU_EXPECT(int, ft_add(20, 22), 20 + 22);
    CU_SECTION("negatif");

    CU_EXPECT(int, ft_add(-21, 20), -1);
    // CU_SECTION("errorous tests");
    // CU_EXPECT(int, ft_add(2, 22), 4);
    // CU_EXPECT(int, ft_add(20, 2), 4);
    CU_RUN_END;
}
void test_reset_int(void)
{
    int a;
    ft_reset_int(&a);
    CU_RUN_START;
    CU_SECTION("basic");
    CU_EXPECT(int, a, 0);
    CU_SECTION("reset after a set");
    a = 10;
    CU_EXPECT(int, a, 10);
    ft_reset_int(&a);
    CU_EXPECT(int, a, 0);
    // CU_SECTION("errorous tests");
    // CU_EXPECT(int, a, 10);
    CU_RUN_END;
}

void test_easy_fail(void)
{
    CU_RUN_START;
    CU_SECTION("Just pass or fail with a message");
    CU_PASS;
    CU_FAIL("Planned failure");
    CU_RUN_END;
}

void test_dump_num(void)
{
    CU_RUN_START;
    CU_SECTION("int");
    int     i_a = 42;
    CU_EXPECT(int, i_a, 42);
    CU_EXPECT(int, i_a, 43);
    CU_SECTION("long");
    long    l_a = 42;
    CU_EXPECT(long, l_a, (long)42);
    CU_EXPECT(long, l_a, (long)43);
    CU_SECTION("short");
    short   s_a = 42;
    CU_EXPECT(short, s_a, (short)42);
    CU_EXPECT(short, s_a, (short)43);

    CU_SECTION("ssize_t");
    ssize_t sst_a = 42;
    CU_EXPECT(ssize_t, sst_a, (ssize_t)42);
    CU_EXPECT(ssize_t, sst_a, (ssize_t)43);

    CU_SECTION("size_t");
    size_t  st_a = 42;
    CU_EXPECT(size_t, st_a, (size_t)42);
    CU_EXPECT(size_t, st_a, (size_t)43);
    CU_RUN_END;
}


int main(void)
{
    CU_BEGIN("Test project for cu_test developpement");
    // CU_RUN(test_isodd);
    // CU_RUN(test_add);
    // CU_RUN(test_reset_int);
    // CU_RUN(test_dump_num);
    CU_RUN(test_easy_fail);
    CU_END;
}
