#include <cbd_parser.h>
#include <cbd_error.h>
#include <fcntl.h>
#include <stdlib.h>

static char	*get_tex(char *temp)
{
	char *path;
	char *dup;

	path = ft_strchr(temp, '.');
	if (!path)
		return (NULL);
	else
	{
		dup = ft_strdup(path);
		if (!dup)
			return (cbd_error(ERR_ALLOC), NULL); 
		return (dup);
	}
}

static t_rgba	get_col(char *temp)
{
	t_rgba color;

	color.color = 0;
	char **colors = ft_split(temp, ',');
	if (!colors)
	{
		cbd_error(ERR_ALLOC);
		return color;
	}
	if (ft_arrlen(colors) == 3) 
	{
		color.r = (uint8_t) ft_atoi(colors[0]);
		color.g = (uint8_t) ft_atoi(colors[1]);
		color.b = (uint8_t) ft_atoi(colors[2]);
		color.a = (uint8_t) 255;
		ft_del_2d(colors);
	}
	return (color);
}

static void	retrieve_element(char *line, t_map *mapdata) 
{
	int 	i;
	char	**temp;

	temp = ft_split(line, ' ');
	i = 0;
	while (temp[i])
	{
		if (ft_strncmp(temp[i], "NO", 2) == 0 && temp[i + 1])
			mapdata->cbd_tex[NO] = get_tex(temp[i + 1]);
		if (ft_strncmp(temp[i], "SO", 2) == 0 && temp[i + 1])
			mapdata->cbd_tex[SO] = get_tex(temp[i + 1]);
		if (ft_strncmp(temp[i], "WE", 2) == 0 && temp[i + 1])
			mapdata->cbd_tex[WE] = get_tex(temp[i + 1]);
		if (ft_strncmp(temp[i], "EA", 2) == 0 && temp[i + 1])
			mapdata->cbd_tex[EA] = get_tex(temp[i + 1]);
		if (ft_strncmp(temp[i], "F", ft_strlen(temp[i])) == 0 && temp[i + 1])
			mapdata->floor = get_col(temp[i + 1]);
		if (ft_strncmp(temp[i], "C", ft_strlen(temp[i])) == 0 && temp[i + 1])
			mapdata->ceiling = get_col(temp[i + 1]);
		i++;
	}
	ft_del_2d(temp);
}

t_map	*get_map_data(int fd, t_map *mapdata, t_valid *is)
{
	char 	*line;

	line = get_next_line(fd);
	while (line) 
	{
		if (is_last_element(is) && line[0] == '\n')
			return (cbd_error(ERR_INVALID_MAP), NULL);
		else if (is_tex(line, is))
			retrieve_element(line, mapdata);
		else if (is_col(line, is))
			retrieve_element(line, mapdata);
		else if (is_content(line) && is_last_element(is))
			mapdata->raw_data = ft_add_2d(mapdata->raw_data, line);
		free(line);
		line = get_next_line(fd);
	}
	if (!mapdata->raw_data)
		return (cbd_error(ERR_INVALID_MAP), NULL);
	return (mapdata);
}