/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ft_containschar.c                                 :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/01 13:36:15 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/11/01 13:37:36 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_containschar(char *content, char c)
{
	int	i;

	i = 0;
	if (!content)
		return (false);
	while (content[i])
	{
		if (content[i] == c)
			return (true);
		i++;
	}
	return (false);
}
