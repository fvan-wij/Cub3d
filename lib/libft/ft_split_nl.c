/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_nl.c                                     :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: flip <flip@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 04:29:16 by flip              #+#    #+#             */
/*   Updated: 2023/10/23 18:35:07 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	word_counter(char const *s, char c)
{
	int		i;
	int		w_count;

	i = 0;
	w_count = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		while (s[i])
		{
			if (s[i] == c || s[i] == '\n' || s[i] == ',')
				break ;
			i++;
		}
		w_count++;
		while (s[i])
		{
			if (s[i] != c && s[i] != '\n' && s[i] != ',')
				break ;
			i++;
		}
	}
	return (w_count);
}

static char	**free_substrings(char **strings_array, int j)
{
	while (j >= 0)
	{
		free(strings_array[j]);
		j--;
	}
	free(strings_array);
	return (0);
}

static int	word_length(char const *s, int i, char c)
{
	int	j;

	j = 0;
	while ((s[i] != c && s[i] != '\n' && s[i] != ',') && s[i])
	{
		i++;
		j++;
	}
	return (j);
}

static char	**split_words(char **str_array, char const *s, char c, int words)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	while (j < words && s[i])
	{
		while (s[i] == c || s[i] == '\n' || s[i] == ',')
			i++;
		len = word_length(s, i, c);
		str_array[j] = ft_substr(s, i, len);
		if (!str_array[j])
		{
			str_array = free_substrings(str_array, j);
			return (0);
		}
		i += len;
		j++;
	}
	return (str_array);
}

char	**ft_split_nl(char const *s, char c)
{
	char	**str_array;
	int		words;

	words = word_counter(s, c);
	str_array = ft_calloc(words + 1, sizeof(char *));
	if (!str_array)
		return (0);
	str_array = split_words(str_array, s, c, words);
	if (!str_array)
		return (0);
	return (str_array);
}
