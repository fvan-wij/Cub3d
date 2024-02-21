/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ft_append_to_double_array.c                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/25 18:44:48 by fvan-wij      #+#    #+#                 */
/*   Updated: 2024/02/21 16:16:10 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char	**ft_append_to_double_array(char **src, char *str)
{
	char	**new;
	int		n_of_arr;
	int		i;

	n_of_arr = 0;
	i = 0;
	while (src[n_of_arr])
		n_of_arr++;
	new = ft_calloc(sizeof(char *), n_of_arr + 2);
	if (!new)
		return (src);
	while (i < n_of_arr)
	{
		new[i] = ft_strdup(src[i]);
		if (!new[i])
			ft_rev_free_2d(new, i);
		i++;
	}
	new[i] = ft_strdup(str);
	if (!new[i])
		ft_rev_free_2d(new, i);
	ft_del_2d(src);
	return (new);
}
