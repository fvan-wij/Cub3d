#include <cbd_parser.h>
#include <cbd_error.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

/*
** Checks the given line and stores texture path or color in mapdata
**
** Needs:
**	a line of the .cub file
*/
static void	retrieve_element(char *line, t_map *mapdata)
{
	int 	i;
	char	**temp;

	temp = ft_split(line, ' ');
	i = 0;
	while (temp[i])
	{
		if (ft_strncmp(temp[i], "NO", 2) == 0 && temp[i + 1])
			mapdata->walls.w_path[NO] = get_texpath(temp[i + 1]);
		if (ft_strncmp(temp[i], "SO", 2) == 0 && temp[i + 1])
			mapdata->walls.w_path[SO] = get_texpath(temp[i + 1]);
		if (ft_strncmp(temp[i], "WE", 2) == 0 && temp[i + 1])
			mapdata->walls.w_path[WE] = get_texpath(temp[i + 1]);
		if (ft_strncmp(temp[i], "EA", 2) == 0 && temp[i + 1])
			mapdata->walls.w_path[EA] = get_texpath(temp[i + 1]);
		if (ft_strncmp(temp[i], "F", ft_strlen(temp[i])) == 0 && temp[i + 1])
			mapdata->floor = get_col(temp[i + 1]);
		if (ft_strncmp(temp[i], "C", ft_strlen(temp[i])) == 0 && temp[i + 1])
			mapdata->ceiling = get_col(temp[i + 1]);
		i++;
	}
	ft_del_2d(temp);
}

t_map	*get_map_data_mandatory(int fd, t_valid *is, char *line)
{
	t_map	*mapdata;
	ft_printf("MAndATORY!!!\n");

	mapdata = alloc_map();
	if (!mapdata)
		return (NULL);
	while (line)
	{
		if ((is_last_element(is) && !is_content(line)) || line[0] == '\n')
			return (cbd_error(ERR_INVALID_MAP), NULL);
		else if (is_tex(line, is) || is_col(line, is))
			retrieve_element(line, mapdata);
		else if (is_content(line) && is_last_element(is))
			mapdata->raw_data = ft_add_2d(mapdata->raw_data, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	get_mlx_tex(mapdata, TEX_SIZE);
	if (!mapdata->raw_data)
		return (cbd_error(ERR_INVALID_MAP), NULL);
	return (mapdata);
}

/*
** Gets all the necessary data from the .cub file
** such as:
** 	Path to NO, EA, SO, WE textures
** 	Map content
** 	Ceiling and floor colors
**
** Needs:
**	Open filedescriptor to the .cub file
**	Pointer to mapdata struct
**	Pointer to validation struct
**
** Returns:
**		t_map *mapdata
*/
t_map	*get_map_data(int fd, t_valid *is)
{
	char 	*line;
	t_map	*mapdata;

	line = get_next_line(fd);
	if (ft_strncmp(line, "CBD_BONUS", 9) == 0)
		mapdata = get_map_data_bonus(fd, line);
	else
		mapdata = get_map_data_mandatory(fd, is, line);
	return (mapdata);
}
