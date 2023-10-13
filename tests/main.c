/* main.c */
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

/*
** Prototype
*/
size_t		ft_strlen(const char *str);
char 		*ft_strcpy(char *dst, char *src);
int			ft_strcmp(const char *s1, const char *s2);
ssize_t		ft_read(int fd, void *buf, size_t nbyte);
ssize_t		ft_write(int fd, const void *buf, size_t nbyte);
char		*ft_strdup(const char *str);

/*
** Macros
*/
# define TEST_STRLEN(x)		printf("`%s` = %ld (%d)\n", x, ft_strlen(x), (int)strlen(x));
# define TEST_STRCMP(a, b)	printf("`%s`:`%s` = %d (%d)\n", a, b, ft_strcmp(a, b), strcmp(a, b));
# define TEST_WRITE(s, x)	printf("^%ld (`%s`:%ld)\n", ft_write(STDOUT_FILENO, s, x), s, x);
# define TEST_READ(b, x)	read = ft_read(STDIN_FILENO, buffer, x); printf("`%s`:%ld\n", buffer, read);
# define TEST_DUP(s)		tmp = ft_strdup(s); printf("`%s` (`%s`)\n", tmp, s); free(tmp); tmp = NULL;

void	say_hi(void);

int main(void) {
	// extern say_hi();
	say_hi();
	// char buff[100];
	// ft_strcpy(buff,"toto");
	// TEST_STRCMP("", "");
	// TEST_STRCMP("toto", "");

	// TEST_STRCMP("toto", "toto");


	// TEST_STRLEN("")
	// TEST_STRLEN("Doriakis")
	return EXIT_SUCCESS;
}
