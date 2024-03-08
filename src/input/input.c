#include <libft.h>
#include <MLX42.h>
#include <stdlib.h>
#include <cub3d.h>
#include <math.h>

#include <stdio.h>

void	cbd_input(mlx_key_data_t keydata, void *param)
{
	t_app		*cbd;
	static int	i;

	cbd = param;
	if (keydata.key == MLX_KEY_W)
	{
		if (keydata.action == MLX_PRESS)
			cbd->input.w = true;
		else if (keydata.action == MLX_RELEASE)
			cbd->input.w = false;
	}
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		cbd->menudata->menu_img[M_MAIN]->instances->enabled = true;
		cbd->menudata->menu_img[M_MAP]->instances->enabled = true;
		cbd->menudata->menu_img[M_CURSOR]->instances->enabled = true;
		cbd->state = STATE_MAIN;
	}
	if (cbd->state == STATE_MAIN)
	{
		cbd->game->instances->enabled = false;
		i = move_cursor_main_menu(cbd, i);
	}
	if (cbd->state == STATE_MAP_SEL)
	{
		cbd->game->instances->enabled = false;
		i = move_cursor_map_select(cbd, i);
	}
	if (cbd->state == STATE_GAME)
	{
		cbd->menudata->menu_img[M_MAIN]->instances->enabled = false;
		cbd->menudata->menu_img[M_MAP]->instances->enabled = false;
		cbd->menudata->menu_img[M_CURSOR]->instances->enabled = false;
		cbd->game->instances->enabled = true;
	}

	if (mlx_is_key_down(cbd->mlx, MLX_KEY_1))
		cbd->hud->equipped = WPN_FIST;
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_2))
		cbd->hud->equipped = WPN_CHAINSAW;
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_M))
		cbd->hud->equipped = WPN_MAP;

}
