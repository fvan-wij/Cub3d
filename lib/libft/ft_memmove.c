/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:26:00 by fvan-wij          #+#    #+#             */
/*   Updated: 2022/11/01 14:43:20 by fvan-wij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*back_memmove(size_t i, char *dst_caster, char *src_caster)
{
	while (i > 0)
	{
		dst_caster[i - 1] = src_caster[i - 1];
		i--;
	}
	return (dst_caster);
}

static char	*forward_memmove(size_t len, char *dst_caster, char *src_caster)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dst_caster[i] = src_caster[i];
		i++;
	}
	return (dst_caster);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	char				*dst_caster;
	char				*src_caster;

	dst_caster = (char *) dst;
	src_caster = (char *) src;
	i = len;
	if (dst == 0 && src == 0)
		return (0);
	if (dst > src)
		back_memmove(i, dst_caster, src_caster);
	else
		forward_memmove(len, dst_caster, src_caster);
	dst = (void *) dst_caster;
	return (dst);
}
