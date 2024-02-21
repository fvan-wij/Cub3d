/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_and_free.c                             :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:28:28 by fvan-wij          #+#    #+#             */
/*   Updated: 2023/10/19 13:22:00 by flip          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	int		len;
	char	*strjoin;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	strjoin = malloc(len * sizeof(char));
	if (!strjoin)
		return (free(s1), NULL);
	ft_strcpy(strjoin, s1);
	ft_strcpy(strjoin + ft_strlen(s1), s2);
	free(s1);
	return (strjoin);
}
