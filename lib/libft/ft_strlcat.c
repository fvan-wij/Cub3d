/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fvan-wij <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 13:31:53 by fvan-wij      #+#    #+#                 */
/*   Updated: 2022/10/11 14:32:23 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*concatenate(const char *src, char *dst, size_t size, size_t j)
{
	size_t	k;

	k = 0;
	while (src[k] && j < size - 1)
	{
		dst[j] = src[k];
		j++;
		k++;
	}
	dst[j] = '\0';
	return (dst);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t					j;
	size_t					size_2;

	j = 0;
	size_2 = 0;
	if (size == 0 && !dst)
		return (ft_strlen(src));
	while (dst[j] != '\0')
	{
		if (j < size)
			size_2++;
		j++;
	}
	if (size > 0)
		concatenate(src, dst, size, j);
	return (ft_strlen(src) + size_2);
}

// int	main(void)
// {
// 	//int	size = 0;
// 	char dst[10] = "Hey ";
// 	char src[10] = "Tom";

// 	char dst2[10] = "Hey ";
// 	char src2[10] = "Tom";

// 	printf("strlcat: %s return: %zu\n", dst, strlcat(dst, src, 5));
// 	printf("ft_strlcat: %s return: %zu\n", dst2, ft_strlcat(dst2, src2, 5));

// 	return (0);
// }