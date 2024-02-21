/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:36:34 by fvan-wij          #+#    #+#             */
/*   Updated: 2022/10/31 15:17:48 by fvan-wij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_caster;
	unsigned char	*s2_caster;

	i = 0;
	s1_caster = (unsigned char *) s1;
	s2_caster = (unsigned char *) s2;
	while ((s1_caster[i] != '\0' || s2_caster[i] != '\0') && (i < n))
	{
		if (s1_caster[i] != s2_caster[i])
			return (s1_caster[i] - s2_caster[i]);
		i++;
	}
	return (0);
}
