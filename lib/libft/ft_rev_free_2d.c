
#include "libft.h"
#include <stdlib.h>

void	ft_rev_free_2d(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
}
