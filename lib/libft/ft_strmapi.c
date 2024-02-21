/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                      :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:59:08 by fvan-wij          #+#    #+#             */
/*   Updated: 2023/06/22 15:35:51 by flip          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

// char	f(unsigned int i, char c)
// {
// 	if (i % 3 == 2)
// 		c = c - 32;
// 	return (c);
// }
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	memory_size;
	char			*s_caster;

	i = 0;
	memory_size = (ft_strlen(s) + 1);
	s_caster = (char *) malloc(memory_size * sizeof(char));
	if (!s_caster)
		return (0);
	while (s[i])
	{
		s_caster[i] = f(i, s[i]);
		i++;
	}
	s_caster[i] = '\0';
	return (s_caster);
}
// int	main(void)
// {
// 	char s[] = "Dit is een string";
// 	printf("%s", ft_strmapi(s, f));
// 	return (0);
// }
