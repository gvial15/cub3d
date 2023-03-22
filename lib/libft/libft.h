/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:08:42 by gvial             #+#    #+#             */
/*   Updated: 2022/10/14 13:26:44 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "get_next_line/get_next_line.h"
# include "ft_printf/ft_printf.h"
# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
char	*ft_itoa(int n);
char	*ft_ltoa(long n);
char	*ft_itoa_base(int value, int base);
int     ft_atoi_base(const char *str, int str_base);
char	*get_next_line(int fd);
char	*ft_ltox(long n, int caps);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	**ft_split(const char *s, char c);
char	**splitdup(char **split);
char	*split_to_str(char **split, int free);
size_t	split_count(char *s, char c);
char	*ft_ultox(unsigned long n, int caps);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
size_t	ft_strlen(char *str);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	ft_putchar(char c);
void	ft_putstr(char *str);
void	free_split(void **split, int split_length);
void	print_split(char **split);
void	ft_putnbr_fd(int n, int fd);
void	ft_bzero(void *s, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	print_int_tab(int *tab, int size);
void	split_cpy(char **src, char **dst);
void	*ft_calloc(size_t count, size_t size);
void	bubble_sort(int *tab, unsigned int size);
void	*ft_memset(void *str, int c, size_t len);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	*ft_memchr(const void *s, int c, size_t n);
void	ft_lstadd_back(t_list **lst, t_list *node);
void	ft_lstadd_front(t_list **lst, t_list *node);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
int		is_quote(char c);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_isascii(char c);
int		ft_isprint(char c);
int		split_len(char **split);
int		ft_lstsize(t_list *lst);
int		ft_atoi(const char *str);
int		ft_printf(const char *s, ...);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

//martin_fct
int		ft_strrchr_i(char *s, int c);
int		ft_iscmd_char(char c);
int		ft_isallcmd_char(char *str);
int		ft_isspace_r(char c);
int		ft_isallspace(char *str);

#endif
