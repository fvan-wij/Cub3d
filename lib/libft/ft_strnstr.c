/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fvan-wij <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 14:38:10 by fvan-wij      #+#    #+#                 */
/*   Updated: 2022/10/11 14:39:18 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned long long	i;
	unsigned long long	j;
	char				*big_caster;

	i = 0;
	j = 0;
	big_caster = (char *) big;
	if (little[i] == '\0')
		return (big_caster);
	while (big[i])
	{
		j = 0;
		while (big[i + j] == little[j] && (i + j) < len)
		{
			if (little[j] == '\0' && (i + j) <= len)
				return (&big_caster[i]);
			j++;
		}
		if (little[j] == '\0')
			return (&big_caster[i]);
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	printf("%s", ft_strnstr("FF", "see FF your FF return FF now FF", 4));
// 	printf("%s", strnstr("FF", "see FF your FF return FF now FF", 4));
// }
