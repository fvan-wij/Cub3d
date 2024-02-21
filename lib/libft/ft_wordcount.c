/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ft_wordcount.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/01 12:35:37 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/11/01 12:36:58 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wordcount(char const *s, char delim)
{
	int		i;
	int		w_count;

	i = 0;
	w_count = 0;
	while (s[i] == delim && s[i])
		i++;
	while (s[i])
	{
		while (s[i])
		{
			if (s[i] == delim)
				break ;
			i++;
		}
		w_count++;
		while (s[i])
		{
			if (s[i] != delim)
				break ;
			i++;
		}
	}
	return (w_count);
}
