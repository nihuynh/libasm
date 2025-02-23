/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:20:24 by nihuynh           #+#    #+#             */
/*   Updated: 2025/02/23 23:08:36 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cu_test.h"
#include "libasm.h"

/*
** Part I
*/
void test_ft_read(void)
{
    printf("\nLearner ft_read:\n");

    char    buff[100];
    int     fd;
    ssize_t ret;
    char    buff_ref[100];
    ssize_t ret_ref;
    errno = 0;

    CU_RUN_START;
    CU_SECTION("exiting file");
    fd = open("test.txt", O_RDONLY);
    ret = ft_read(fd, buff, 10);
    buff[ret] = '\0';
    close(fd);
    fd = open("test.txt", O_RDONLY);
    ret_ref = read(fd, buff_ref, 10);
    buff_ref[ret_ref] = '\0';
    CU_EXPECT(str, buff_ref, buff);
    CU_EXPECT(ssize_t, ret_ref, ret);
    CU_EXPECT(int, errno, 0);
    printf("\nbuff = [%s] REF = [%s]\n", buff, buff_ref);
    close(fd);

    buff[0] = '\0';
    buff_ref[0] = '\0';
    CU_SECTION("missing file");

    fd = open("lol.txt", O_RDONLY);
    ret = ft_read(fd, buff, 20);
    int tmp_errno = errno;
    buff[ret] = '\0';
    close(fd);
    fd = open("lol.txt", O_RDONLY);
    ret_ref = read(fd, buff_ref, 20);
    int ref_errno = errno;
    buff_ref[ret_ref] = '\0';
    CU_EXPECT(int, strcmp((const char*)&buff_ref, (const char*)&buff), 0);
    CU_EXPECT(ssize_t, ret, ret_ref);
    CU_EXPECT(int, tmp_errno, ref_errno);
    printf("\nbuff = [%s] REF = [%s]\n", buff, buff_ref);
    close(fd);
    CU_RUN_END;
}

void test_ft_strcmp(void)
{
    CU_RUN_START;
    CU_SECTION("basic");
    CU_EXPECT(int, ft_strcmp("abc", "abc"), strcmp("abc", "abc"));
    CU_EXPECT(int, ft_strcmp("d", "a"), strcmp("d", "a"));
    CU_EXPECT(int, ft_strcmp("test", ""), strcmp("test", ""));
    CU_RUN_END;
}

void test_ft_strcpy(void)
{
    char buffy[64];
    ft_strcpy((char*)&buffy, "Helloworld");
    CU_RUN_START;
    CU_SECTION("basic");
    CU_EXPECT(size_t, ft_strlen((const char*)&buffy), strlen("Helloworld"));
    CU_EXPECT(int, strcmp((const char*)&buffy, "Helloworld"), 0);

    CU_SECTION("overwrite");
    ft_strcpy((char*)&buffy, "42");
    CU_EXPECT(size_t, ft_strlen((const char*)&buffy), strlen("42"));
    CU_EXPECT(int, strcmp((const char*)&buffy, "42"), 0);
    CU_RUN_END;
}

void test_ft_strlen(void)
{
    CU_RUN_START;
    CU_SECTION("basic");
    CU_EXPECT(size_t, ft_strlen("test"), strlen("test"));
    CU_EXPECT(size_t, ft_strlen("\0test"), strlen("\0test"));
    CU_EXPECT(size_t, ft_strlen("te\0st"), strlen("te\0st"));
    CU_SECTION("empty string");
    CU_EXPECT(size_t, ft_strlen(""), strlen(""));
    CU_EXPECT(size_t, ft_strlen("\0\0"), strlen("\0\0"));
    CU_RUN_END;
}

void test_ft_strdup(void)
{
    char *dest = ft_strdup("Helloworld");
    CU_RUN_START;
    CU_SECTION("dup helloworld");
    CU_EXPECT(size_t, strlen(dest), strlen("Helloworld"));
    CU_EXPECT(int, strcmp(dest, "Helloworld"), 0);
    free(dest);
    CU_SECTION("empty string");
    char *null_str = ft_strdup("");
    CU_EXPECT(int, strcmp(null_str, ""), 0);
    CU_EXPECT(str, null_str, "");
    free(null_str);
    CU_RUN_END;
}

void test_ft_write(void)
{
    CU_RUN_START;
    CU_SECTION("simple print");
    CU_EXPECT(ssize_t, ft_write(1, "\nft_write:", strlen("\nft_write:")), strlen("\nft_write:"));
    CU_EXPECT(ssize_t, ft_write(1, "Test Test\n", strlen("Test Test\n")), strlen("Test Test\n"));
    CU_SECTION("Empty string");
    CU_EXPECT(ssize_t, ft_write(1, "", strlen("")), strlen(""));
    CU_SECTION("Negative fd");
    CU_EXPECT(ssize_t, ft_write(1, NULL, 5), (long)-1);
    CU_EXPECT(int, errno, -3);
    CU_RUN_END;
}

/*
** Part II
*/

void test_ft_atoi_base(void)
{
    CU_RUN_START;
    CU_SECTION("basic");
    CU_EXPECT(int, ft_atoi_base("0", "0123456789"), 0);
    CU_EXPECT(int, ft_atoi_base("42", "0123456789"), 42);
    CU_EXPECT(int, ft_atoi_base("-42", "0123456789"), -42);
    CU_EXPECT(int, ft_atoi_base("1010", "01"), 0b1010);
    CU_SECTION("Hex");
    CU_EXPECT(int, ft_atoi_base("3a2b", "0123456789abcdef"), 0x3a2b);
    CU_EXPECT(int, ft_atoi_base("3A2B", "0123456789ABCDEF"), 0x3a2b);
    CU_SECTION("Wrong base");
    CU_EXPECT(int, ft_atoi_base("42", ""), 0);
    CU_EXPECT(int, ft_atoi_base("42", "1"), 0);
    CU_EXPECT(int, ft_atoi_base("42", "aba"), 0);
    CU_EXPECT(int, ft_atoi_base("42", " 01234"), 0);
    CU_EXPECT(int, ft_atoi_base("42", "-01234"), 0);
    CU_EXPECT(int, ft_atoi_base("42", "+01234"), 0);
    CU_SECTION("space and sign skipping");
    CU_EXPECT(int, ft_atoi_base(" 1", "01"), 1);
    CU_EXPECT(int, ft_atoi_base("  1", "01"), 1);
    CU_EXPECT(int, ft_atoi_base(" -1", "01"), 1);
    CU_SECTION("double negation");
    CU_EXPECT(int, ft_atoi_base("---1", "01"), -1);
    CU_EXPECT(int, ft_atoi_base("-+-1", "01"), 1);
    CU_EXPECT(int, ft_atoi_base("+++1", "01"), 1);
    CU_EXPECT(int, ft_atoi_base("+1", "01"), 1);
    CU_RUN_END;
}
void test_ft_list_push_front(void)
{
    CU_RUN_START;
    CU_RUN_END;
}
void test_ft_list_size(void)
{
    CU_RUN_START;
    CU_RUN_END;
}
void test_ft_list_sort(void)
{
    CU_RUN_START;
    CU_RUN_END;
}
void test_ft_list_remove_if(void)
{
    CU_RUN_START;
    CU_RUN_END;
}


int main(void)
{
    CU_BEGIN("Testing libasm, part I & II");
    // CU_RUN(test_ft_write);
    // CU_RUN(test_ft_read);
    // CU_RUN(test_ft_strcmp);
    // CU_RUN(test_ft_strlen);
    // CU_RUN(test_ft_strcpy);
    // CU_RUN(test_ft_strdup);
    CU_RUN(test_ft_atoi_base);
    // CU_RUN(test_ft_list_push_front);
    // CU_RUN(test_ft_list_size);
    // CU_RUN(test_ft_list_sort);
    // CU_RUN(test_ft_list_remove_if);
    CU_END;
}
