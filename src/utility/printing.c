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
	char c;

	ft_printf("[TEXTURES]\ntex_path[NO]: %s\ntex_path[SO]: %s\ntex_path[WE]: %s\ntex_path[EA]: %s\n", cub3d->mapdata->tex_path[NO],cub3d-> mapdata->tex_path[SO],cub3d->mapdata->tex_path[WE], cub3d->mapdata->tex_path[EA]);
	ft_printf("\n[COLORS]\nFloor color:  (%d, %d, %d)\nCeiling color: (%d, %d, %d)\n",cub3d->mapdata->floor.r, cub3d->mapdata->floor.g, cub3d->mapdata->floor.b, cub3d->mapdata->ceiling.r, cub3d->mapdata->ceiling.g, cub3d->mapdata->ceiling.b);
	if (cub3d->mapdata->cbd_map)
	{
		ft_printf("\n[MAP_CONTENT]\n");
		print_2d(cub3d->mapdata->cbd_map);
	}
	if (cub3d->mapdata->start_dir == N)
		c = 'N';
	if (cub3d->mapdata->start_dir == S)
		c = 'S';
	if (cub3d->mapdata->start_dir == W)
		c = 'W';
	if (cub3d->mapdata->start_dir == E)
		c = 'E';
	ft_printf("\n[MAP_DATA]\nStart_pos: (%d, %d, %c)\nMap-dimensions: (%d, %d)\n", cub3d->mapdata->start_pos.x, cub3d->mapdata->start_pos.y, c, cub3d->mapdata->width, cub3d->mapdata->height);

	if (cub3d->mapdata->valid)
		ft_printf("\n[VALID]\nYes\n");
	else
		ft_printf("\n[VALID]\nNo\n");
}
