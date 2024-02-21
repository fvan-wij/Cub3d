/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 11:30:48 by fvan-wij          #+#    #+#             */
/*   Updated: 2022/10/31 15:33:23 by fvan-wij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	s1_index_after_init_trim(char const *s1, char const *set)
{
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	while ((s1[i] != set[j] || s1[i] == set[j]) && s1[i])
	{
		j = 0;
		while (s1[i] != set[j])
		{
			if (s1[i] == set[j])
			{
				i++;
				break ;
			}
			if (set[j] == '\0')
				return (i);
			j++;
		}
		i++;
	}
	return (0);
}

static size_t	s1_index_after_end_trim(char const *s1, char const *set)
{
	size_t			i;
	size_t			j;

	i = ft_strlen(s1);
	j = 0;
	while ((s1[i] != set[j] || s1[i] == set[j]))
	{
		j = 0;
		if (i == 0)
			break ;
		while (s1[i] != set[j])
		{
			if (s1[i] == set[j])
			{
				i--;
				break ;
			}
			if (set[j] == '\0')
				return (i + 1);
			j++;
		}
		i--;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t			len;
	char			*s1_copy;

	s1_copy = (char *) s1;
	len = (s1_index_after_end_trim(s1, set)
			- s1_index_after_init_trim(s1, set)) + 1;
	s1_copy = ft_calloc(len, sizeof(char));
	if (!s1_copy)
		return (0);
	if (len == 1)
		return (s1_copy);
	else
		ft_strlcpy(s1_copy, &s1[s1_index_after_init_trim(s1, set)], len);
	return (s1_copy);
}

// int	main(void)
// {
// 	char    s1[] = "kkHoovin Smoovinkk";
// 	char    set[] = "kk";
// 	printf("%s", ft_strtrim(s1, set));
// }
