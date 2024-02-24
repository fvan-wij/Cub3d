#include <cub3d.h>

void	print_2d(char **str)
{
	int i; 

	i = 0;
	while (str[i])
	{
		ft_printf("%s", str[i]);
		i++;
	}
}

void	print_debug_info(t_app *cub3d)
{
	ft_printf("cbd_tex[NO]: %scbd_tex[SO]: %scbd_tex[WE]: %scbd_tex[EA]: %s\n", cub3d->mapdata->cbd_tex[NO],cub3d-> mapdata->cbd_tex[SO],cub3d->mapdata->cbd_tex[WE], cub3d->mapdata->cbd_tex[EA]);
	ft_printf("Floor color:  (%d, %d, %d)\nCeiling color: (%d, %d, %d)\n\n",cub3d->mapdata->floor.r, cub3d->mapdata->floor.g, cub3d->mapdata->floor.b, cub3d->mapdata->ceiling.r, cub3d->mapdata->ceiling.g, cub3d->mapdata->ceiling.b);
	print_2d(cub3d->mapdata->raw_data);
	ft_printf("start_pos.x: %d, start_pos.y: %d, dir: %d, width: %d, height: %d\n", cub3d->mapdata->start_pos.x, cub3d->mapdata->start_pos.y, cub3d->mapdata->start_dir, cub3d->mapdata->width, cub3d->mapdata->height);
}
