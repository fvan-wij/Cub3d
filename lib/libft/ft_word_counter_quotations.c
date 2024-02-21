/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_counter_quotations.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhussain <dhussain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:51:58 by fvan-wij          #+#    #+#             */
/*   Updated: 2023/11/01 15:53:14 by dhussain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void	ft_skip_delimiter(char const *s, char c, int *i)
{
	while (s[*i] && s[*i] == c)
		(*i)++;
}

static void	ft_skip_text(char const *s, char c, int *i)
{
	while (s[*i] && (s[*i] != c && s[*i] != '\'' && s[*i] != '"'))
		(*i)++;
}

static int	ft_skip_till_quotations(char const *s, int *i, char c)
{
	while (s[*i])
	{
		(*i)++;
		if (s[*i] == c)
			return ((*i)++);
	}
	return (*i);
}

int	ft_word_counter_quotations(char const *s, char c)
{
	int		i;
	int		w_count;

	i = 0;
	w_count = 0;
	ft_skip_delimiter(s, c, &i);
	while (s[i])
	{
		if (s[i] == '\'' )
			ft_skip_till_quotations(s, &i, '\'');
		else if (s[i] == '"')
			ft_skip_till_quotations(s, &i, '"');
		else
			ft_skip_text(s, c, &i);
		w_count++;
		ft_skip_delimiter(s, c, &i);
	}
	return (w_count);
}
