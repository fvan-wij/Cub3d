/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:26:43 by fvan-wij          #+#    #+#             */
/*   Updated: 2022/11/01 14:34:27 by fvan-wij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*buffer;

	buffer = (char *) b;
	i = 0;
	while (i < len)
	{
		buffer[i] = (unsigned char) c;
		i++;
	}
	return (b = (void *) buffer);
}
