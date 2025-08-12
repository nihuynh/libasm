/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:22:05 by nihuynh           #+#    #+#             */
/*   Updated: 2025/08/11 22:53:51 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBASM_H
# define LIBASM_H

#include <stdlib.h>
#include <unistd.h>
/*
** Part I
*/
char    *ft_strcpy(char *dst, const char *src);
char    *ft_strdup(const char *s1);
int     ft_strcmp(const char *s1, const char *s2);
size_t  ft_strlen(const char *s);
ssize_t ft_read(int fd, void *buf, size_t count);
ssize_t ft_write(int fd, const void *buf, size_t count);

/*
** Part II
*/
typedef struct s_list
{
    void          *data;
    struct s_list *next;
} t_list;

// # define size_struct sizeof(t_list)

int  ft_atoi_base(char *str, char *base);
void ft_list_push_front(t_list **head, void *data);
int  ft_list_size(t_list *begin);
void ft_list_sort(t_list **head, int (*cmp)());
void ft_list_remove_if(t_list **head, void *ref, int (*cmp)(), void (*free_fn)());

#endif
