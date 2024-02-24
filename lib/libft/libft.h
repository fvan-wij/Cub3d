/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                           :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:46:37 by fvan-wij          #+#    #+#             */
/*   Updated: 2024/02/22 13:42:11 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stddef.h>
# include <stdarg.h>
# include <stdbool.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int				ft_arrlen(char **arr);
unsigned int	ft_atoh(char *hex_string);
int				ft_atoi(const char *nptr);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_iswhitespace(int c); //New, add to libft!
void			*ft_memchr(const void *s, int c, unsigned long long n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
char			*ft_strchr(const char *s, int c);
int				ft_strchr_index(const char *s, int c);
char			*ft_strdup(const char *s1);
size_t			ft_strcpy(char *dst, const char *src);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strrchr(const char *s, int c);
int				ft_tolower(int c);
int				ft_toupper(int c);
char			*ft_itoa(int n);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			**ft_split(char const *s, char c);
void			ft_putnbr_fd(int n, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putstr_fd_nl(const char *s, int fd);
void			ft_putstr_fd_2d(char *s[], int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
t_list			*ft_lstnew(void *content);
int				ft_lstsize(t_list *lst);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstadd_back(t_list **lst, t_list *new);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
int				ft_wordcount(char const *s, char delim);

// GET_NEXT_LINE
char			*get_next_line(int fd);

// PRINTF
int				ft_printf(const char *s, ...);
int				ft_putnbr(int n);
int				ft_putchar(char c);
int				ft_put_ui_nbr(unsigned int n);
int				ft_putstr(char *s);
int				ft_puthex(unsigned int n);
int				ft_put_cap_hex(unsigned int n);
int				ft_putadr(unsigned long n);
int				ft_printspecifier(int specifier, va_list args);

// CUSTOM FUNCTIONS
char			*ft_strjoin_and_free(char *s1, char *s2);
char			**ft_split_nl(char const *s, char c);
int				ft_word_counter_quotations(char const *s, char c);
char			**ft_split_quotations(char const *s, char c);
int				ft_find_envp_path_index(char *envp[]);
void			ft_del_2d(char **arr);
int				ft_strisalpha(char *str);
bool			ft_containschar(char *content, char c);

char			**ft_copy_double_array(char **array);
char			**ft_add_2d(char **src, char *str);
char			**ft_replace_str_in_array(char **src, char *str, int index);
char			**ft_remove_str_from_array(char **src, int index);
char			**ft_inject_str_in_array(char **src, char *str, int index);
void			ft_rev_free_2d(char **arr, int i);

#endif
