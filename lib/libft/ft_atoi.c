/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                         :+:    :+:             */
/*                                                     +:+                    */
/*   By: fvan-wij <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 12:57:30 by fvan-wij      #+#    #+#                 */
/*   Updated: 2023/10/23 18:33:22 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	skip_whitespace(int i, char *int_str)
{
	while (int_str[i] == ' ' || int_str[i] == '\t'
		|| int_str[i] == '\r' || int_str[i] == '\n'
		|| int_str[i] == '\v' || int_str[i] == '\f')
		i++;
	return (i);
}

static int	convert_atoi(char *int_str, int i)
{
	int	atoi;

	atoi = 0;
	while ((int_str[i] >= 48 && int_str[i] <= 57) && int_str[i] != '\0')
	{
		atoi = atoi * 10 + (int_str[i] - '0');
		i++;
	}
	return (atoi);
}

int	ft_atoi(const char *nptr)
{
	char	*int_str;
	int		atoi;
	int		i;
	int		j;
	int		neg_check;

	int_str = (char *) nptr;
	atoi = 0;
	i = 0;
	j = 0;
	neg_check = 1;
	i = skip_whitespace(i, int_str);
	if (int_str[i] == '-')
		neg_check = -neg_check;
	while (int_str[i] == '-' || int_str[i] == '+')
	{
		i++;
		j++;
		if (j > 1)
			return (0);
	}
	atoi = convert_atoi(int_str, i);
	return (atoi * neg_check);
}

// int main(void)
// {
//     printf("FT_ATOI: %d\n", ft_atoi("2147483647"));
// 	printf("ATOI: %d\n", atoi("2147483647"));
// }
