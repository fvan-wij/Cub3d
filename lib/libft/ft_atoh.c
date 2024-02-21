/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvan-wij <fvan-wij@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:48:18 by flip              #+#    #+#             */
/*   Updated: 2023/03/14 17:32:47 by fvan-wij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_atoh(char *hex_string)
{
	unsigned int	hex;
	int				i;

	hex = 0;
	i = 0;
	while (hex_string[i] != '\0')
	{
		if ((hex_string[i] >= '0' && hex_string[i] <= '9'))
			hex = hex * 16 + (hex_string[i] - '0');
		else if ((hex_string[i] >= 'a' && hex_string[i] <= 'f'))
			hex = hex * 16 + (10 + hex_string[i] - 'a');
		else if ((hex_string[i] >= 'A' && hex_string[i] <= 'F'))
			hex = hex * 16 + (10 + hex_string[i] - 'A');
		i++;
	}
	return (hex);
}
