/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ft_inject_str_in_array.c                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/25 18:49:02 by fvan-wij      #+#    #+#                 */
/*   Updated: 2024/02/21 16:17:17 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static char	**inject_str(char **src, char *str, int index, int size)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = ft_calloc(size + 2, sizeof(char *));
	if (!new)
		return (src);
	while (j < size)
	{
		if (i == index)
		{
			new[i] = ft_strdup(str);
			j--;
		}
		else
			new[i] = ft_strdup(src[j]);
		if (!new[i])
			return (ft_rev_free_2d(new, i), NULL);
		i++;
		j++;
	}
	return (new);
}

char	**ft_inject_str_in_array(char **src, char *str, int index)
{
	char	**new;
	int		size;

	size = ft_arrlen(src);
	new = inject_str(src, str, index, size);
	if (!new)
		return (src);
	ft_del_2d(src);
	return (new);
}
