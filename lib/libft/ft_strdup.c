/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                       :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:29:24 by fvan-wij          #+#    #+#             */
/*   Updated: 2023/06/22 15:36:18 by flip          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	int		i;
	int		j;
	char	*duplicate;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	duplicate = malloc(i + 1 * sizeof(char));
	if (duplicate == NULL)
		return (0);
	else
	{
		while (s1[j])
		{
			duplicate[j] = s1[j];
			j++;
		}
		duplicate[i] = '\0';
	}
	return (duplicate);
}
// int	main(void)
// {
// 	char	s1[48] = "Copy me again, motherfucker, I double dare you!";
// 	printf("%s", ft_strdup(s1));
// 	return (0);
// }
