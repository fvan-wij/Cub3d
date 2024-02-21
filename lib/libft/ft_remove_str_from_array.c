/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ft_remove_str_from_array.c                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/25 18:48:33 by fvan-wij      #+#    #+#                 */
/*   Updated: 2024/02/21 16:16:59 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static char	**remove_str(char **src, int index, int n_of_arr, char **new)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < (n_of_arr - 1) && src[j])
	{
		if (j == index)
			j++;
		if (j > n_of_arr)
			new[i] = ft_strdup(src[n_of_arr]);
		else
			new[i] = ft_strdup(src[j]);
		if (!new[i])
		{
			ft_rev_free_2d(new, i);
			break ;
		}
		i++;
		j++;
	}
	return (new);
}

char	**ft_remove_str_from_array(char **src, int index)
{
	char	**new;
	int		n_of_arr;

	n_of_arr = 0;
	n_of_arr = ft_arrlen(src);
	new = ft_calloc(sizeof(char *), n_of_arr + 1);
	if (!new)
		return (src);
	new = remove_str(src, index, n_of_arr, new);
	if (!new)
		return (src);
	return (ft_del_2d(src), new);
}
