/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ft_putstr_fd_nl.c                                 :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/10/23 17:33:02 by fvan-wij      #+#    #+#                 */
/*   Updated: 2024/02/22 13:53:06 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putstr_fd_nl(const char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}
