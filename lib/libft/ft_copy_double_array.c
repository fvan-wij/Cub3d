#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char	**ft_copy_double_array(char **array)
{
	char	**copy;
	int		n_of_arr;
	int		i;

	n_of_arr = 0;
	i = 0;
	while (array[n_of_arr])
		n_of_arr++;
	copy = ft_calloc(sizeof(char *), n_of_arr + 1);
	if (!copy)
		return (NULL);
	while (i < n_of_arr)
	{
		copy[i] = ft_strdup(array[i]);
		if (!copy[i])
			ft_rev_free_2d(copy, i);
		i++;
	}
	return (copy);
}
