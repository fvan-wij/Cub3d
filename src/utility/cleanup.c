#include <cub3d.h>
#include <libft.h>
#include <MLX42.h>
#include <stdlib.h>

void	cleanup_map(t_map *map)
{
	int i;

	if (map->raw_data)
		ft_del_2d(map->raw_data);
	if (map->cbd_map)
		ft_del_2d(map->cbd_map);
	if (map->tex_path)
		ft_del_2d(map->tex_path);
	if (map->tex)
	{
		i = 0;
		while (i < TEX_SIZE)
		{
			mlx_delete_texture(map->tex[i]);
			i++;
		}
		free(map->tex);
	}
	free(map);
}

void	cleanup_menu(t_menu *menu)
{
	// int i;

	// i = 0;
	// while (i < M_SIZE)
	// {
	// 	// mlx_delete_texture(menu->menu_tex[i]);
	// 	i++;
	// }
	free(menu);
}

void	cleanup(t_app *app)
{
	if (app->mapdata)
		cleanup_map(app->mapdata);
	if (app->menudata)
		cleanup_menu(app->menudata);
}
