/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ft_append_to_double_array.c                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/25 18:44:48 by fvan-wij      #+#    #+#                 */
/*   Updated: 2024/02/23 12:45:03 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static char	**init_array(char *str)
{
	char **new;

	new = ft_calloc(sizeof(char *), 2);
	if (!new)
		return (NULL);
	new[0] = ft_strdup(str);
	new[1] = NULL;
	return (new);
}

static char **append_to_array(char **src, char *str)
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

char	**ft_add_2d(char **src, char *str)
{
	if (!src)
		return (init_array(str));
	else 
		return (append_to_array(src, str));
}
