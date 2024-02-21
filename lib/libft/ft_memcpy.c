/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:22:52 by fvan-wij          #+#    #+#             */
/*   Updated: 2022/11/01 14:41:08 by fvan-wij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	char			*caster_string_dst;
	char			*caster_string_src;

	caster_string_dst = (char *) dst;
	caster_string_src = (char *) src;
	i = 0;
	if (dst == 0 && src == 0)
		return (0);
	while (i < n)
	{
		caster_string_dst[i] = caster_string_src[i];
		i++;
	}
	dst = (void *) caster_string_dst;
	return (dst);
}
