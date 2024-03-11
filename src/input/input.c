#include <libft.h>
#include <MLX42.h>
#include <stdlib.h>
#include <cub3d.h>
#include <cbd_error.h>
#include <math.h>

#include <stdio.h>

// void	cbd_init_input(t_app *cbd)
// {
// 	ft_bzero(cbd->input.handler, sizeof(t_input_handler) * 348);
// 	cbd->input.handler[MLX_KEY_W] = forward_handler;
// 	cbd->input.handler[MLX_KEY_S] = backward_handler;
// 	cbd->input.handler[MLX_KEY_A] = left_handler;
// 	cbd->input.handler[MLX_KEY_D] = right_handler;
// 	cbd->input.handler[MLX_KEY_LEFT] = left_handler;
// 	cbd->input.handler[MLX_KEY_RIGHT] = right_handler;
// 	cbd->input.handler[MLX_KEY_UP] = forward_handler;
// 	cbd->input.handler[MLX_KEY_DOWN] = backward_handler;
// 	cbd->input.handler[MLX_KEY_ESCAPE] = escape_handler;
// 	cbd->input.handler[MLX_KEY_ENTER] = enter_handler;
// 	cbd->input.handler[MLX_KEY_1] = weapon_handler;
// 	cbd->input.handler[MLX_KEY_2] = weapon_handler;
// 	cbd->input.handler[MLX_KEY_M] = map_handler;
// }

void	cbd_input(mlx_key_data_t keydata, void *param)
{
	t_app		*cbd;

	cbd = param;
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS && cbd->playerdata.inv->equipped != WPN_MAP)
		cbd->playerdata.inv->weapons[cbd->playerdata.inv->equipped].fire_animation->loop = true;
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		menu_move_cursor(cbd->menudata, -1);
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		menu_move_cursor(cbd->menudata, 1);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		menu_escape(cbd->menudata);
		cbd->game->instances->enabled = false;
	}
	if (keydata.key == MLX_KEY_ENTER && keydata.action == MLX_PRESS)
	{
		if (cbd->state == STATE_MENU)
			menu_enter(cbd->menudata);
	}
	if (!cbd->playerdata.inv->weapons[cbd->playerdata.inv->equipped].fire_animation->loop)
	{
		if (mlx_is_key_down(cbd->mlx, MLX_KEY_1))
			cbd->playerdata.inv->equipped = WPN_FIST;
		if (mlx_is_key_down(cbd->mlx, MLX_KEY_2))
			cbd->playerdata.inv->equipped = WPN_CHAINSAW;
		if (mlx_is_key_down(cbd->mlx, MLX_KEY_M))
			cbd->playerdata.inv->equipped = WPN_MAP;
	}
}
