/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:07:27 by fvan-wij          #+#    #+#             */
/*   Updated: 2022/11/01 14:36:43 by fvan-wij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*caster_string;

	i = 0;
	caster_string = (char *) s;
	while (i < n)
	{
		caster_string[i] = '\0';
		i++;
	}
	s = (void *) caster_string;
}
