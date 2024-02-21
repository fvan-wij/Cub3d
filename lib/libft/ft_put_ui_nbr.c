/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_ui_nbr.c                                   :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:23:03 by fvan-wij          #+#    #+#             */
/*   Updated: 2023/06/22 15:37:35 by flip          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_put_ui_nbr(unsigned int n)
{
	char	convert;
	int		j;

	j = 0;
	if (n < 10)
	{
		convert = '0' + n;
		j += write(1, &convert, 1);
	}
	if (n >= 10)
	{
		j += ft_put_ui_nbr(n / 10);
		j += ft_put_ui_nbr(n % 10);
	}
	return (j);
}
