// #include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "libasm.h"

int ft_add(int a, int b);

// Test fn
void    test_strlen(void)
{

}

void    test_ft_add(void)
{
    printf("\nLearner ft_add:\n");
    printf("ft_add 1 + 3 = %d", ft_add(1, 3));
}

void    test_ft_read(void)
{
    printf("-------------------ft_read-------------------\n");
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
}

void    test_ft_write(void)
{
    ft_write(1, "\nft_write:\n", strlen("\nft_write:\n"));
    ft_write(1, "test\n", strlen("test\n"));
    ft_write(1, "Test Test\n", strlen("Test Test\n"));
}

// Main program
int	main(void)
{
    test_ft_write();
    test_ft_read();
    test_ft_strcmp();
    test_ft_strlen();
    test_ft_strcpy();
    test_ft_add();
    // test_ft_strdup();
    return EXIT_SUCCESS;
}
