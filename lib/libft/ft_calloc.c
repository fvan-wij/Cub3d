/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                       :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:09:17 by fvan-wij          #+#    #+#             */
/*   Updated: 2023/06/22 15:39:13 by flip          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	char				*ptr;
	size_t				i;

	i = 0;
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	while (i < (count * size))
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

// int	main(void)
// {
// 	int	i = 0;
// 	char *ptr = ft_calloc(10, sizeof(char));
// 	while (ptr[i])
// 	{
// 		printf("ptr[%d]", ptr[i]);
// 		i++;
// 	}
// }
