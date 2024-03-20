#include <cbd_parser.h>
#include <cbd_error.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

/*
** Reads the given line and returns the path to a texture
**	
** Needs:
**	a line of the .cub file
** Returns:
**	path to a texture
*/
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

/*
** Reads the given line and returns the color values
**	
** Needs:
**	a line of the .cub file
** Returns:
**	t_rgba color values	
*/
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
			mapdata->tex_path[NO] = get_tex(temp[i + 1]);
		if (ft_strncmp(temp[i], "SO", 2) == 0 && temp[i + 1])
			mapdata->tex_path[SO] = get_tex(temp[i + 1]);
		if (ft_strncmp(temp[i], "WE", 2) == 0 && temp[i + 1])
			mapdata->tex_path[WE] = get_tex(temp[i + 1]);
		if (ft_strncmp(temp[i], "EA", 2) == 0 && temp[i + 1])
			mapdata->tex_path[EA] = get_tex(temp[i + 1]);
		if (ft_strncmp(temp[i], "F", ft_strlen(temp[i])) == 0 && temp[i + 1])
			mapdata->floor = get_col(temp[i + 1]);
		if (ft_strncmp(temp[i], "C", ft_strlen(temp[i])) == 0 && temp[i + 1])
			mapdata->ceiling = get_col(temp[i + 1]);
		i++;
	}
	ft_del_2d(temp);
}

/*
** Checks if the path to the texture exists and returns an array of NO, SO, WE, EA textures
**	
** Needs:
**	tex_path (array of texture paths)
** 		
** Returns:
**	mlx_texture_t **textures
*/
static mlx_texture_t	**get_mlx_tex(char **tex_path)
{
	int				i;
	mlx_texture_t 	**textures;

	i = 0;
	textures = malloc(sizeof(mlx_texture_t *) * TEX_SIZE);
	while (tex_path[i] && i < TEX_SIZE)
	{
		if (tex_exists(tex_path[i]))
			textures[i] = mlx_load_png(tex_path[i]);
		else
			return (cbd_error(ERR_FILE_INEXISTS), NULL);
		if (!textures)
			return (cbd_error(ERR_ALLOC), NULL);
		i++;
	}
	return (textures);
}

t_map	*get_map_data_mandatory(int fd, t_map *mapdata, t_valid *is, char *line)
{
	ft_printf("MAndATORY!!!\n");
	while (line)
	{
		if (is_last_element(is) && line[0] == '\n')
			return (cbd_error(ERR_INVALID_MAP), NULL);
		else if (is_tex(line, is) || is_col(line, is))
			retrieve_element(line, mapdata);
		else if (is_content(line) && is_last_element(is))
			mapdata->raw_data = ft_add_2d(mapdata->raw_data, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!mapdata->raw_data)
		return (cbd_error(ERR_INVALID_MAP), NULL);
	mapdata->tex = get_mlx_tex(mapdata->tex_path);
	if (!mapdata->tex)
		return (NULL);
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
t_map	*get_map_data(int fd, t_map *mapdata, t_valid *is)
{
	char 	*line;

	line = get_next_line(fd);
	if (ft_strncmp(line, "CBD_BONUS", 9) == 0)
		mapdata = get_map_data_bonus(fd, mapdata, is, line);
	else
		mapdata = get_map_data_mandatory(fd, mapdata, is, line);
	return (mapdata);
}
