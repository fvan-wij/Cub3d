#include <cbd_parser.h>
#include <cbd_error.h>
#include <fcntl.h>
#include <stdlib.h>

static int	open_map(const char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (cbd_error(ERR_OPEN), fd);
	return (fd);
}

static void	retrieve_tex_col(char *line, t_map *mapdata) 
{
	int 	i;
	char	**temp;

	temp = ft_split(line, ' ');
	i = 0;
	while (temp[i])
	{
		if (ft_strncmp(temp[i], "NO", 2) == 0 && temp[i + 1])
			mapdata->cbd_tex[NO] = parse_texture(temp[i + 1]);
		if (ft_strncmp(temp[i], "SO", 2) == 0 && temp[i + 1])
			mapdata->cbd_tex[SO] = parse_texture(temp[i + 1]);
		if (ft_strncmp(temp[i], "WE", 2) == 0 && temp[i + 1])
			mapdata->cbd_tex[WE] = parse_texture(temp[i + 1]);
		if (ft_strncmp(temp[i], "EA", 2) == 0 && temp[i + 1])
			mapdata->cbd_tex[EA] = parse_texture(temp[i + 1]);
		if (ft_strncmp(temp[i], "F", ft_strlen(temp[i])) == 0 && temp[i + 1])
			mapdata->floor = parse_color(temp[i + 1]);
		if (ft_strncmp(temp[i], "C", ft_strlen(temp[i])) == 0 && temp[i + 1])
			mapdata->ceiling = parse_color(temp[i + 1]);
		i++;
	}
	free(line);
	ft_del_2d(temp);
}

bool	is_mapcontent(char *str)
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

t_map	*cbd_read_map(const char *file, t_map *mapdata)
{
	int 	fd;
	char 	*line;

	fd = open_map(file);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	while (line	) 
	{
		if (is_mapcontent(line))
		{
			mapdata->raw_data = ft_append_to_double_array(mapdata->raw_data, line);
			if (!mapdata->raw_data)
				return (free(line), NULL);
		}
		else
		{
			retrieve_tex_col(line, mapdata);
		}
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (mapdata);
}
