/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ft_strisalpha.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/27 13:00:04 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/06/27 13:02:30 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strisalpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}
