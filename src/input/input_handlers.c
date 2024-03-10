// #include <stdio.h>
// #include <cub3d.h>

// void	default_handler(mlx_key_data_t keydata, void *param)
// {
// 	t_app *cbd;

// 	cbd = param;
// 	if (keydata.action == MLX_PRESS)
// 		cbd->input.key[keydata.key] = true;
// 	else if (keydata.action == MLX_RELEASE)
// 		cbd->input.key[keydata.key] = false;
// }

// void	forward_handler(mlx_key_data_t keydata, void *param)
// {
// 	t_app *cbd;

// 	cbd = param;
// 	if (cbd->state != STATE_GAME)
// 		return ;
// 	if (keydata.action == MLX_PRESS)
// 		cbd->playerdata.action.forward = true;
// 	else if (keydata.action == MLX_RELEASE)
// 		cbd->playerdata.action.forward = false;
// 	printf("Forward\n");
// }

// void	backward_handler(mlx_key_data_t keydata, void *param)
// {
// 	t_app *cbd;

// 	cbd = param;
// 	if (keydata.action == MLX_PRESS)
// 		cbd->playerdata.action.backward = true;
// 	else if (keydata.action == MLX_RELEASE)
// 		cbd->playerdata.action.backward = false;
// 	printf("Backward\n");
// }

// void	left_handler(mlx_key_data_t keydata, void *param)
// {
// 	t_app *cbd;

// 	cbd = param;
// 	if (keydata.action == MLX_PRESS)
// 		cbd->playerdata.action.left = true;
// 	else if (keydata.action == MLX_RELEASE)
// 		cbd->playerdata.action.left = false;
// 	printf("Left\n");
// }

// void	right_handler(mlx_key_data_t keydata, void *param)
// {
// 	t_app *cbd;

// 	cbd = param;
// 	if (keydata.action == MLX_PRESS)
// 		cbd->playerdata.action.right = true;
// 	else if (keydata.action == MLX_RELEASE)
// 		cbd->playerdata.action.right = false;
// 	printf("Right\n");
// }

// void	escape_handler(mlx_key_data_t keydata, void *param)
// {
// 	t_app *cbd;

// 	cbd = param;
// 	if (keydata.action == MLX_PRESS)
// 	{
// 		cbd->menudata->menu_img[M_MAIN]->instances->enabled = true;
// 		cbd->menudata->menu_img[M_MAP]->instances->enabled = true;
// 		cbd->menudata->menu_img[M_CURSOR]->instances->enabled = true;
// 		cbd->state = STATE_MAIN;
// 	}
// 	printf("Escape\n");
// }
