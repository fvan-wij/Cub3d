#include <cbd_parser.h>
#include <libft.h>

static bool	is_mapchar(char c)
{
	size_t		i;
	const char	map_content[10] = {"120NWES\t \0"};

	i = 0;
	while (map_content[i])
	{
		if (c == map_content[i])
			return (true);
		i++;
	}
	return (false);
}

bool	is_wall(char c)
{
	size_t		i;
	const char	map_content[3] = {"12\0"};

	i = 0;
	while (map_content[i])
	{
		if (c == map_content[i])
			return (true);
		i++;
	}
	return (false);
}

bool	is_content(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (false);
	while (str[i])
	{
		if (is_mapchar(str[i]))
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
	size_t	len;

	len = 0;
	if (!line)
		return (false);
	len = ft_strlen(line);
	if (len > 5 && ft_strncmp(&line[len - 5], ".png", 4) == 0)
	{
		if (ft_strncmp(line, "NO ", 3) == 0)
			return (is->tex[NO] = true);
		if (ft_strncmp(line, "SO ", 3) == 0)
			return (is->tex[SO] = true);
		if (ft_strncmp(line, "WE ", 3) == 0)
			return (is->tex[WE] = true);
		if (ft_strncmp(line, "EA ", 3) == 0)
			return (is->tex[EA] = true);
	}
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
