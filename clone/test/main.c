/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:20:24 by nihuynh           #+#    #+#             */
/*   Updated: 2025/08/10 13:43:02 by nihuynh          ###   ########.fr       */
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

    char    buff[32];
    char    buff_ref[32];
    int     fd;
    ssize_t ret;
    ssize_t ret_ref;
    errno = 0;

    CU_RUN_START;
    CU_SECTION("exiting file");
    fd = open("test.txt", O_RDONLY);
    ret = ft_read(fd, &buff, 10);
    buff[10] = '\0';
    close(fd);
    fd = open("test.txt", O_RDONLY);
    ret_ref = read(fd, &buff_ref, 10);
    buff_ref[10] = '\0';
    CU_EXPECT(str, buff_ref, buff);
    CU_EXPECT(ssize_t, ret_ref, ret);
    CU_EXPECT(int, errno, 0);
    // printf("\nbuff = [%s] REF = [%s]\n", buff, buff_ref);
    close(fd);

    buff[0] = '\0';
    buff_ref[0] = '\0';
    CU_SECTION("missing file");

    fd = open("lol.txt", O_RDONLY);
    ret = ft_read(fd, &buff, 20);
    int tmp_errno = errno;
    buff[20] = '\0';
    close(fd);
    fd = open("lol.txt", O_RDONLY);
    ret_ref = read(fd, &buff_ref, 20);
    int ref_errno = errno;
    buff_ref[20] = '\0';
    CU_EXPECT(int, strcmp((const char*)&buff_ref, (const char*)&buff), 0);
    CU_EXPECT(ssize_t, ret, ret_ref);
    CU_EXPECT(int, tmp_errno, ref_errno);
    // printf("\nbuff = [%s] REF = [%s]\n", buff, buff_ref);
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
    CU_EXPECT(int, ft_atoi_base("1010", "01"), 0xa);
    CU_SECTION("Hex");
    CU_EXPECT(int, ft_atoi_base("3a2b", "0123456789abcdef"), 0x3a2b);
    CU_EXPECT(int, ft_atoi_base("3A2B", "0123456789ABCDEF"), 0x3a2b);
    CU_SECTION("Wrong base");
    CU_EXPECT(int, ft_atoi_base("1", "01"), 1);
    CU_EXPECT(int, ft_atoi_base("42", ""), 0);
    CU_EXPECT(int, ft_atoi_base("42", "1"), 0);
    CU_EXPECT(int, ft_atoi_base("42", "aba"), 0);
    CU_EXPECT(int, ft_atoi_base("1", "01 2"), 0);
    CU_EXPECT(int, ft_atoi_base("1", "+012"), 0);
    CU_EXPECT(int, ft_atoi_base("2", "012+"), 0);
    CU_EXPECT(int, ft_atoi_base("2", "01+2"), 0);
    CU_EXPECT(int, ft_atoi_base("2", "-012"), 0);
    CU_EXPECT(int, ft_atoi_base("+2", "-012"), 0);
    CU_EXPECT(int, ft_atoi_base(" 2", "-012"), 0);
    CU_SECTION("space and sign skipping");
    CU_EXPECT(int, ft_atoi_base(" 1", "01"), 1);
    CU_EXPECT(int, ft_atoi_base("  1", "01"), 1);
    CU_EXPECT(int, ft_atoi_base(" -1", "01"), -1);
    CU_SECTION("double negation");
    CU_EXPECT(int, ft_atoi_base("-1", "01"), -1);
    CU_EXPECT(int, ft_atoi_base(" +1", "01"), 1);
    CU_EXPECT(int, ft_atoi_base("--1", "01"), 1);
    CU_EXPECT(int, ft_atoi_base("---1", "01"), -1);
    CU_EXPECT(int, ft_atoi_base("+++1", "01"), 1);
    CU_EXPECT(int, ft_atoi_base(" ---1", "01"), -1);
    CU_EXPECT(int, ft_atoi_base("-+-1", "01"), 1);
    CU_RUN_END;
}
void test_ft_list_push_front(void)
{
    t_list start;
    t_list node;
    t_list *head = &start;
    start.next = NULL;
    node.next = NULL;
    CU_RUN_START;
    CU_SECTION("Setup");
    CU_EXPECT(int, ft_list_size(head), 1);
    CU_EXPECT(int, ft_list_size(&start), 1);
    CU_EXPECT(int, ft_list_size(&node), 1);

    CU_SECTION("Pushing item to list.");
    ft_list_push_front(&head, &node);
    CU_EXPECT(int, ft_list_size(head), 2);
    CU_EXPECT(int, ft_list_size(&node), 2);
    CU_EXPECT(ptr, (void*)node.next, (void*)&start);
    CU_EXPECT(ptr, (void*)head, (void*)&node);

    CU_SECTION("More in the list.");
    t_list node_a;
    node_a.next = NULL;
    t_list node_b;
    node_b.next = NULL;
    ft_list_push_front(&head, &node_a);
    ft_list_push_front(&head, &node_b);
    CU_EXPECT(int, ft_list_size(head), 4);
    CU_EXPECT(ptr, (void*)head, (void*)&node_b);

    CU_SECTION("Error detection, node NULL");
    ft_list_push_front(&head, NULL);
    CU_EXPECT(int, ft_list_size(head), 4);
    CU_EXPECT(ptr, (void*)head, (void*)&node_b);
    CU_RUN_END;
}
void test_ft_list_size(void)
{
    t_list end = {.data=NULL, .next=NULL};
    t_list start = {.data=NULL, .next=&end};

    CU_RUN_START;
    // t_list *head = &start;
    // printf("start: %p, %p, %p\n", head, &head->data, &head->next);
    // printf("start: %p, %p, %p\n", &end, end.data, end.next);

    CU_SECTION("Bonus: list size");
    CU_EXPECT(int, ft_list_size(NULL), 0);
    CU_EXPECT(int, ft_list_size(&end), 1);
    CU_EXPECT(int, ft_list_size(&start), 2);
    CU_EXPECT(int, ft_list_size(NULL), 0);
    CU_RUN_END;
}


int compare_int(int *a, int *b) {
    printf("Compare %d, %d result %d\n", *a, *b, (*b - *a));
    return (*b - *a);
}
void del_node(int *node_data) {
    printf("removing %d", (int)*node_data);
    return;
}
void test_ft_list_sort(void)
{
    int    a = 5;
    int    b = 4;
    int    c = 3;
    t_list node_b = {.data=&c};
    t_list node = {.data=&a, .next=&node_b};
    t_list start = {.data=&b, .next=&node};
    t_list *head = &start;
    CU_RUN_START;
    CU_SECTION("Initialize int list");
    CU_EXPECT(int, ft_list_size(head), 3);
    CU_EXPECT(ptr, head->data, &b);
    t_list *runner = NULL;
    runner = head;
    while (runner)
	{
        int *tmp = runner->data;
        printf("node %p, %d\n", runner, *tmp);
        runner = runner->next;
    }
    CU_SECTION("Sorting");
    ft_list_sort(&head, compare_int);
    CU_EXPECT(ptr, head->data, &c);
    CU_EXPECT(int, *((int*)head->data), 3);
    runner = head;
    while (runner)
	{
        int *tmp = runner->data;
        printf("node %p, %d\n", runner, *tmp);
        runner = runner->next;
    }
    CU_RUN_END;
}

void test_ft_list_sort_str(void)
{
    char*   a = "Helloword";
    char*   b = "Core";
    char*   c = "Byebye";
    t_list node_b = {.data=c};
    t_list node = {.data=a, .next=&node_b};
    t_list start = {.data=b, .next=&node};
    t_list *head = &start;
    t_list *runner = NULL;
    runner = head;
    while (runner)
	{
        char *tmp = runner->data;
        printf("node %p, %s\n", runner, tmp);
        runner = runner->next;
    }
    CU_RUN_START;
    CU_SECTION("Initialize str list");
    CU_EXPECT(int, ft_list_size(head), 3);
    CU_EXPECT(ptr, head->data, &b);
    CU_SECTION("Sorting");
    ft_list_sort(&head, strcmp);
    runner = head;
    while (runner)
	{
        char *tmp = runner->data;
        printf("node %p, %s\n", runner, tmp);
        runner = runner->next;
    }
    CU_EXPECT(ptr, head->data, &c);
    CU_EXPECT(str, (char*)head->data, "Byebye");
    CU_RUN_END;
}

void test_ft_list_remove_if(void)
{
    CU_RUN_START;
    int    a = 42;
    int    b = 16;
    int    c = 3;
    int    ref = 42;
    t_list node_b = {.data=&c};
    t_list node = {.data=&a, .next=&node_b};
    t_list start = {.data=&b, .next=&node};
    t_list *head = &start;
    CU_SECTION("Initialize int list");
    CU_EXPECT(int, ft_list_size(head), 3);
    CU_EXPECT(ptr, head->data, &b);
    CU_SECTION("Remove elt");
    ft_list_remove_if(&head, &ref, compare_int, del_node);
    CU_EXPECT(int, ft_list_size(head), 2);
    CU_RUN_END;
}


int main(void)
{
    CU_BEGIN("Testing libasm, part I & II");
    // CU_SECTION("fails on mac");

    CU_RUN(test_ft_write);
    CU_RUN(test_ft_read);
    CU_RUN(test_ft_strcmp);
    // CU_SECTION("mandatory");

    CU_RUN(test_ft_strlen);
    CU_RUN(test_ft_strcpy);
    CU_RUN(test_ft_strdup);
    CU_RUN(test_ft_atoi_base);

    // CU_SECTION("bonus");
    CU_RUN(test_ft_list_size);
    CU_RUN(test_ft_list_push_front);
    CU_RUN(test_ft_list_sort);
    CU_RUN(test_ft_list_sort_str); // TODO: fix me
    CU_RUN(test_ft_list_remove_if);
    CU_END;
}
