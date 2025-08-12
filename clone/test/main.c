/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:20:24 by nihuynh           #+#    #+#             */
/*   Updated: 2025/08/13 01:20:07 by nihuynh          ###   ########.fr       */
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
    CU_EXPECT(int, ft_atoi_base("111", "01"), 7);
    CU_SECTION("Error checks");
    CU_EXPECT(int, ft_atoi_base("", "01"), 0);
    CU_EXPECT(int, ft_atoi_base("01", ""), 0);
    CU_EXPECT(int, ft_atoi_base("", ""), 0);
    char *tmp = NULL;
    CU_EXPECT(int, ft_atoi_base(tmp, "01"), 0);
    CU_EXPECT(int, ft_atoi_base("01", tmp), 0);
    CU_SECTION("Hex");
    CU_EXPECT(int, ft_atoi_base("3a2b", "0123456789abcdef"), 0x3a2b);
    CU_EXPECT(int, ft_atoi_base("3a2b", "0123456789abcdef"), 0x3a2b);
    CU_EXPECT(int, ft_atoi_base("---ff", "0123456789abcdef"), -255);
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
    CU_EXPECT(int, ft_atoi_base("568", "012345	6789"), 0);
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
    CU_SECTION("garbage after the data");
    CU_EXPECT(int, ft_atoi_base("-++++++-+--ff\xff", "0123456789abcdef"), 255);
    CU_EXPECT(int, ft_atoi_base("+-123", "01"), -1);
    CU_EXPECT(int, ft_atoi_base("-++++01++-+--ff", "01"), -1);
    CU_EXPECT(int, ft_atoi_base(" 644yo", "01234567"), 420);
    CU_RUN_END;
}
void test_ft_list_push_front(void)
{
    t_list *head = NULL;

    CU_RUN_START;
    CU_EXPECT(int, ft_list_size(head), 0);
    CU_SECTION("Pushing item to list.");
    ft_list_push_front(&head, malloc(8));
    CU_EXPECT(int, ft_list_size(head), 1);
    ft_list_push_front(&head, malloc(16));
    CU_EXPECT(int, ft_list_size(head), 2);
    ft_list_push_front(&head, malloc(2));
    CU_EXPECT(int, ft_list_size(head), 3);
    CU_SECTION("Error checks");
    ft_list_push_front(&head, NULL);
    CU_EXPECT(int, ft_list_size(head), 3);
    t_list *node = head;
    while (node)
    {
        /* code */
        t_list *current = node;
        node = node->next;
        printf("current: %p, data %p, next: %p\n", current, current->data, current->next);
        free(current->data);
        free(current);
    }

    CU_RUN_END;
}
void test_ft_list_size(void)
{
    t_list end = { .data = NULL, .next = NULL };
    t_list start = { .data = NULL, .next = &end };

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
    // printf("Compare %d, %d result %d\n", *a, *b, (*a - *b));
    return (*a - *b);
}
void del_node(int *node_data) {
    // printf("removing %d\n", (int)*node_data);
    (void)node_data;
    return;
}

int compare_str(char *a, char *b) {
    int res = strcmp(a, b);
    // printf("Compare %s, %s [res: %d]\n", a, b, res);
    return res;
}
void del_str(char *str_node) {
    // printf("removing %s\n", str_node);
    free(str_node);
    return;
}
enum e_dump_type {
    DUMP_PTR,
    DUMP_STR,
    DUMP_INT,
};
void dump_tlist(t_list *runner, enum e_dump_type type_dump) {
    int idx = 0;
    while (runner)
    {
        switch (type_dump)
        {
        case DUMP_INT:
            printf("node %d %p, %d\n", idx, runner, *((int*)runner->data));
            break;
        case DUMP_STR:
            printf("node %d %p, %s\n", idx, runner, (char*)runner->data);
            break;
        default:
            printf("node %d %p, %p\n", idx, runner, runner->data);
            break;
        }
        idx++;
        runner = runner->next;
    }
}
void test_ft_list_sort(void)
{
    int    a = 42;
    int    b = 16;
    int    c = 3;
    t_list *head = NULL;

    CU_RUN_START;
    CU_SECTION("Initialize int list");
    CU_EXPECT(int, ft_list_size(head), 0);
    ft_list_push_front(&head, &c);
    ft_list_push_front(&head, &a);
    ft_list_push_front(&head, &c);
    ft_list_push_front(&head, &b);
    ft_list_push_front(&head, &b);
    ft_list_push_front(&head, &b);
    ft_list_push_front(&head, &a);
    ft_list_push_front(&head, &b);
    CU_EXPECT(int, ft_list_size(head), 8);
    CU_EXPECT(ptr, head->data, &b);
    dump_tlist(head, DUMP_INT);
    CU_SECTION("Sorting");
    ft_list_sort(&head, compare_int);
    CU_EXPECT(ptr, head->data, &c);
    CU_EXPECT(int, *((int*)head->data), 3);
    dump_tlist(head, DUMP_INT);
    CU_RUN_END;
}


void test_ft_list_sort_sorted_list(void)
{
    int    list[5] = { 1, 2, 3, 4, 5 };
    t_list *head = NULL;
    CU_RUN_START;
    CU_SECTION("Sorted list of 5 int");
    CU_EXPECT(int, ft_list_size(head), 0);
    for (size_t i = 5; i > 0 ; i--)
    {
        ft_list_push_front(&head, &list[i - 1]);
    }
    CU_EXPECT(int, ft_list_size(head), 5);
    CU_EXPECT(int, *((int*)head->data), 1);
    dump_tlist(head, DUMP_INT);
    CU_SECTION("Sorting");
    ft_list_sort(&head, compare_int);
    CU_EXPECT(int, *((int*)head->data), 1);
    dump_tlist(head, DUMP_INT);

    t_list *head_rev = NULL;
    CU_SECTION("Reversed list of 5 int");
    CU_EXPECT(int, ft_list_size(head_rev), 0);
    for (size_t i = 5; i > 0 ; i--)
    {
        ft_list_push_front(&head_rev, &list[i - 1]);
    }
    CU_EXPECT(int, ft_list_size(head_rev), 5);
    CU_EXPECT(int, *((int*)head_rev->data), 1);
    dump_tlist(head_rev, DUMP_INT);
    CU_SECTION("Sorting");
    ft_list_sort(&head_rev, compare_int);
    CU_EXPECT(int, *((int*)head_rev->data), 1);
    dump_tlist(head_rev, DUMP_INT);

    t_list *head_zero = NULL;
    int    list_zero[5] = { 1, 2, 0, 4, 5 };
    CU_SECTION("List of int with zero value");
    CU_EXPECT(int, ft_list_size(head_zero), 0);
    for (size_t i = 5; i > 0 ; i--)
    {
        ft_list_push_front(&head_zero, &list_zero[i - 1]);
    }
    CU_EXPECT(int, ft_list_size(head_zero), 5);
    CU_EXPECT(int, *((int*)head_zero->data), 1);
    dump_tlist(head_zero, DUMP_INT);
    CU_SECTION("Sorting");
    ft_list_sort(&head_zero, compare_int);
    CU_EXPECT(int, *((int*)head_zero->data), 0);
    dump_tlist(head_zero, DUMP_INT);

    CU_RUN_END;
}


void test_ft_list_sort_str(void)
{
    t_list *head = NULL;
    CU_RUN_START;
    CU_SECTION("Initialize str list");
    CU_EXPECT(int, ft_list_size(head), 0);
    ft_list_push_front(&head, strdup("Hellow"));
    ft_list_push_front(&head, strdup("Byebye"));
    ft_list_push_front(&head, strdup("Coucou"));
    CU_EXPECT(int, ft_list_size(head), 3);
    dump_tlist(head, DUMP_STR);
    CU_EXPECT(str, (char*)head->data, "Coucou");
    CU_SECTION("Sorting");
    ft_list_sort(&head, compare_str);
    dump_tlist(head, DUMP_STR);
    CU_EXPECT(str, (char*)head->data, "Byebye");
    CU_RUN_END;
}

void test_ft_list_remove_if(void)
{
    int    a = 42;
    int    b = 16;
    int    c = 3;
    int    ref = 42;
    t_list *head = NULL;

    CU_RUN_START;
    CU_SECTION("Setup");
    CU_EXPECT(int, ft_list_size(head), 0);
    ft_list_push_front(&head, &a);
    ft_list_push_front(&head, &a);
    ft_list_push_front(&head, &c);
    ft_list_push_front(&head, &b);
    ft_list_push_front(&head, &b);
    CU_EXPECT(int, ft_list_size(head), 5);
    CU_EXPECT(ptr, head->data, &b);
    dump_tlist(head, DUMP_INT);
    CU_SECTION("Remove starting elt");
    ft_list_remove_if(&head, &ref, compare_int, del_node);
    dump_tlist(head, DUMP_INT);
    CU_EXPECT(int, ft_list_size(head), 3);
    CU_SECTION("Remove more elt");
    ref = 16;
    ft_list_remove_if(&head, &ref, compare_int, del_node);
    dump_tlist(head, DUMP_INT);
    CU_EXPECT(int, ft_list_size(head), 1);
    CU_SECTION("Remove last elt");
    ref = 3;
    ft_list_remove_if(&head, &ref, compare_int, del_node);
    CU_EXPECT(int, ft_list_size(head), 0);
    CU_EXPECT(ptr, head, NULL);
    CU_RUN_END;
}

void test_ft_list_remove_if_str(void)
{
    t_list *head = NULL;
    ft_list_push_front(&head, strdup("Helloword"));
    ft_list_push_front(&head, strdup("Coucou"));
    ft_list_push_front(&head, strdup("Byebye"));
    ft_list_push_front(&head, strdup("Core"));
    char   *ref = "Core";
    dump_tlist(head, DUMP_STR);
    CU_RUN_START;
    CU_SECTION("Initialize str list");
    CU_EXPECT(int, ft_list_size(head), 4);
    CU_SECTION("Remove elt");
    ft_list_remove_if(&head, ref, strcmp, del_str);
    CU_EXPECT(int, ft_list_size(head), 3);
    dump_tlist(head, DUMP_STR);
    CU_SECTION("Unknowned elt");
    ref = "panic?";
    ft_list_remove_if(&head, ref, strcmp, del_str);
    CU_EXPECT(int, ft_list_size(head), 3);
    dump_tlist(head, DUMP_STR);
    CU_SECTION("Remove first elt");
    ref = "Helloword";
    ft_list_remove_if(&head, ref, strcmp, del_str);
    dump_tlist(head, DUMP_STR);
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
    // CU_SECTION("bonus");
    CU_RUN(test_ft_atoi_base);
    CU_RUN(test_ft_list_size);
    CU_RUN(test_ft_list_push_front);
    CU_RUN(test_ft_list_sort);
    CU_RUN(test_ft_list_sort_sorted_list);
    CU_RUN(test_ft_list_sort_str);
    CU_RUN(test_ft_list_remove_if);
    CU_RUN(test_ft_list_remove_if_str);
    CU_END;
}
