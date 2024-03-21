#include <cbd_parser.h>
#include <cbd_error.h>
#include <stdlib.h>

/*
** Reads the given line and returns the path to a texture
**	
** Needs:
**	a line of the .cub file
** Returns:
**	path to a texture
*/
char	*get_texpath(char *temp)
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
t_rgba	get_col(char *temp)
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
** Checks if the path to the texture exists and returns an array of NO, SO, WE, EA textures
**	
** Needs:
**	tex_path (array of texture paths)
** 		
** Returns:
**	mlx_texture_t **textures
*/
mlx_texture_t	**get_mlx_tex(char **tex_path, uint8_t n)
{
	int				i;
	mlx_texture_t 	**textures;

	i = 0;
	textures = malloc(sizeof(mlx_texture_t *) * n);
	while (tex_path[i] && i < n)
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
