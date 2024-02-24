#include <cbd_parser.h>

bool	is_content(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (false);
	while (str[i])
	{
		if (str[i] == '1' || str[i] == '0'
			|| str[i] == 'N' || str[i] == 'W' 
			|| str[i] == 'E' || str[i] == 'S'
			|| str[i] == '\t' || str[i] == ' ')
			i++;
		else
			break;
	}
	if (str[i] == '\n')
		return (true);
	return (false);
}

bool	is_tex(char *line, t_valid *is)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (is->tex[NO] = true);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (is->tex[SO] = true);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (is->tex[WE] = true);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (is->tex[EA] = true);
	return (false);
}

bool	is_col(char *line, t_valid *is)
{
	if (ft_strncmp(line, "F ", 2) == 0)
		return (is->col_fl = true);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (is->col_cl = true);
	return (false);
}

bool	is_last_element(t_valid *is)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < TEX_SIZE)
	{
		if (is->tex[i] == true)
			count++;
		i++;
	}
	if (count == 4 && is->col_cl && is->col_fl)
		return (true);
	return (false);
}