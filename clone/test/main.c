/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:20:24 by nihuynh           #+#    #+#             */
/*   Updated: 2025/02/14 14:20:26 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <errno.h>

#include "libasm.h"

/*
** Part I
*/
void    test_ft_read(void)
{
    printf("\nLearner ft_read:\n");

    char		buff[100];
    int         fd;
    ssize_t     ret;

	printf("ft_read : \n");   
    	fd = open("test.txt", O_RDONLY);
    	ret = ft_read(fd, buff, 10);
    	buff[ret] = '\0';
	printf("buff = %sret = %zd\n", buff, ret);
	close(fd);

	printf("read : \n");
	fd = open("test.txt", O_RDONLY);
	ret = read(fd, buff, 10);
	buff[ret] = '\0';
	printf("buff = %sret = %zd\n", buff, ret);
    	close(fd);
	printf("----------\n");
	printf("ft_read : \n");
    	fd = open("lol.txt", O_RDONLY);
    	ret = ft_read(fd, buff, 10);
 	printf("errno : %d\n", errno);
    	buff[ret] = '\0';
	printf("buff = %sret = %zd\n", buff, ret);
	close(fd);

	errno = 0;
	printf("read : \n");
	fd = open("lol.txt", O_RDONLY);
	ret = read(fd, buff, 10);
 	printf("errno : %d\n", errno);
	buff[ret] = '\0';
	printf("buff = %sret = %zd\n", buff, ret);
    close(fd);
}

void    test_ft_strcmp(void)
{
    printf("\nft_strcmp:\n");
	printf("res: %d Expected: %d\n", ft_strcmp("abc", "abc"), strcmp("abc", "abc"));
	printf("res: %d Expected: %d\n", ft_strcmp("a", "d"), strcmp("a", "d"));
	printf("res: %d Expected: %d\n", ft_strcmp("d", "a"), strcmp("d", "a"));
	printf("res: %d Expected: %d\n", ft_strcmp("test", ""), strcmp("test", ""));
}

void    test_ft_strcpy(void)
{
	printf("\nft_strcpy:\n");
    char buffy[64];
    ft_strcpy((char *) &buffy, "Helloworld");
    printf("%s", buffy);
}

void    test_ft_strlen(void)
{
	printf("\nft_strlen:\n");
	printf("res: %zu Expected: %zu\n", ft_strlen("test"), strlen("test"));
	printf("res: %zu Expected: %zu\n", ft_strlen("\0test"), strlen("\0test"));
	printf("res: %zu Expected: %zu\n", ft_strlen("te\0st"), strlen("te\0st"));
	printf("res: %zu Expected: %zu\n", ft_strlen(""), strlen(""));
	printf("res: %zu Expected: %zu\n", ft_strlen("\0\0"), strlen("\0\0"));
}

void    test_ft_strdup(void)
{
    printf("\nft_strdup:\n");
    char *dest = ft_strdup("Helloworld");
	printf("Dest: %s len: %zu Expected: %zu (Helloworld)\n", dest, strlen(dest), strlen("Helloworld"));
}

void    test_ft_write(void)
{
    ft_write(1, "\nft_write:\n", strlen("\nft_write:\n"));
    ft_write(1, "test\n", strlen("test\n"));
    ft_write(1, "Test Test\n", strlen("Test Test\n"));
}

/*
** Part II
*/

int test_ft_atoi_base() {
    return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
int test_ft_list_push_front() {
    return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
int test_ft_list_size() {
    return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
int test_ft_list_sort() {
    return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
int test_ft_list_remove_if() {
    return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int	main(void)
{
    test_ft_write();
    test_ft_read();
    test_ft_strcmp();
    test_ft_strlen();
    test_ft_strcpy();
    test_ft_strdup();
    test_ft_atoi_base();
    test_ft_list_push_front();
    test_ft_list_size();
    test_ft_list_sort();
    test_ft_list_remove_if();
    return EXIT_SUCCESS;
}




