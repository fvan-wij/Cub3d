/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadr.c                                       :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:04:28 by fvan-wij          #+#    #+#             */
/*   Updated: 2023/06/22 15:37:31 by flip          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static int	convert_hex(char *hex, unsigned long n)
{
	unsigned long	remainder;
	unsigned long	i;

	remainder = 0;
	i = 0;
	while (n != 0)
	{
		remainder = n % 16;
		if (remainder < 10)
			hex[i] = 48 + remainder;
		else if (remainder >= 10)
			hex[i] = 87 + remainder;
		i++;
		n = n / 16;
	}
	return (i);
}

int	ft_putadr(unsigned long n)
{
	char			hex[30];
	unsigned long	j;
	unsigned long	i;

	i = 0;
	j = 0;
	if (!n)
	{
		j += write(1, "0x0", 3);
		return (j);
	}
	j += write(1, "0x", 2);
	i += convert_hex(hex, n);
	j += i;
	while (i != 0)
	{
		write(1, &hex[i - 1], 1);
		i--;
	}
	return (j);
}
