/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                    :+:    :+:             */
/*                                                     +:+                    */
/*   By: fvan-wij <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 10:46:29 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/06/22 15:36:53 by flip          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
// int main(void)
// {
//     ft_putstr_fd("Hello, what's going on?\n", 1);
// }
