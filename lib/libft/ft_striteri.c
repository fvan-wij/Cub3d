/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_striteri.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fvan-wij <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 10:58:44 by fvan-wij      #+#    #+#                 */
/*   Updated: 2022/10/19 10:58:48 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

// void	f(unsigned int n, char c)
// {
// 	n = 32;
// 	if (c >= 'A' && c <= 'Z')
// 		c = c;
// 	else
// 		c = c - n;
// 	printf("%c", c);
// }

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
// int	main(void)
// {
// 	char s[] = "Dit is een string";
// 	ft_striteri(s, f);
// 	return (0);
// }
