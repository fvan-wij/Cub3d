#include <stdio.h>
#include <cub3d.h>

void	forward_handler(mlx_key_data_t keydata, t_app *cbd)
{
	t_app	*cbd;

	if (keydata.action == MLX_PRESS)
		cbd->input.key[keydata.key] = true;
	else if (keydata.action == MLX_RELEASE)
		cbd->input.key[keydata.key] = false;
	printf("Forward\n");
}

void	backward_handler(mlx_key_data_t keydata, t_app *cbd)
{
	t_app	*cbd;

	if (keydata.action == MLX_PRESS)
		cbd->input.key[keydata.key] = true;
	else if (keydata.action == MLX_RELEASE)
		cbd->input.key[keydata.key] = false;
	printf("Backward\n");
}
