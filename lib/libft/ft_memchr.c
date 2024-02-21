/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:17:00 by fvan-wij          #+#    #+#             */
/*   Updated: 2022/10/31 15:15:47 by fvan-wij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, unsigned long long n)
{
	unsigned long long	i;
	char				*s_caster;
	char				*void_caster;

	i = 0;
	s_caster = (char *) s;
	void_caster = (void *) s;
	while (i < n)
	{
		if (s_caster[i] == (char) c)
			return (&void_caster[i]);
		i++;
	}
	return (NULL);
}
