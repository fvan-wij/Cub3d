#include <cub3d.h>
#include <libft.h>
#include <cbd_parser.h>
#include <cbd_error.h>
#include <stdlib.h>



void	parse_texture(char *temp, e_tex DIR, t_app *cub3d)
{
	char *path;
	char *dup;

	path = ft_strchr(temp, '.');
	if (!path)
	{
		cub3d->mapdata->cbd_tex[DIR] = NULL;
		return ;
	}
	else
	{
		dup = ft_strdup(path);
		if (!dup)
			cbd_error(ERR_ALLOC); 
		cub3d->mapdata->cbd_tex[DIR] = dup;
	}
}

t_rgba	parse_color(char *temp)
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
