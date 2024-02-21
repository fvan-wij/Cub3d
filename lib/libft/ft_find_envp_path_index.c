/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ft_find_envp_path_index.c                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/30 15:45:18 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/05/30 15:48:19 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_find_envp_path_index(char *envp[])
{
	int	path_index;

	path_index = 0;
	while (envp[path_index])
	{
		if (ft_strnstr(envp[path_index], "PATH=", 5))
			return (path_index);
		path_index++;
	}
	return (-1);
}
