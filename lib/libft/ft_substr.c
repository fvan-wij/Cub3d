/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                       :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:38:07 by fvan-wij          #+#    #+#             */
/*   Updated: 2023/11/16 14:45:53 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	if (start > ft_strlen(s))
		len = 0;
	else if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	substr = ft_calloc(len + 1, sizeof(char));
	if (substr == NULL)
		return (NULL);
	while (j < len && s[i] != '\0')
	{
		substr[j] = s[i + start];
		i++;
		j++;
	}
	substr[j] = '\0';
	return (substr);
}

// int    main(void)
// {
//     //char    s[36] = "Copy me one more time, motherfucker!";
//     printf("%s\n", ft_substr("0123456789", 9, 10));
// }
