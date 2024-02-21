/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ft_strchr_index.c                                 :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/23 18:36:38 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/10/23 18:36:46 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr_index(const char *s, int c)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != (char)c)
		i++;
	return (i);
}
