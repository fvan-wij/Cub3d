/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                         :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: dantehussain <dantehussain@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:51:27 by fvan-wij          #+#    #+#             */
/*   Updated: 2023/10/23 18:36:18 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*convert_int_to_array(int n, int j, char *integer_array)
{
	while (n != 0)
	{
		integer_array[j - 2] = (n % 10) + '0';
		n = n / 10;
		j--;
	}
	return (integer_array);
}

static int	ft_diglen(int n)
{
	int	i;

	i = 1;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*integer_array;
	int		j;

	j = ft_diglen(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	integer_array = ft_calloc(j, sizeof(char));
	if (integer_array == NULL)
		return (0);
	integer_array[j - 1] = '\0';
	if (n < 0)
	{
		n = -n;
		integer_array[0] = '-';
	}
	return (integer_array = convert_int_to_array(n, j, integer_array));
}

// int	main(void)
// {
// 	// printf("%s\n", itoa(-2147483647 -1, 15, DECIMAL));
// 	printf("%s\n", ft_itoa(-2147483648));
// }
