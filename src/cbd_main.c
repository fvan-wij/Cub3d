#include <cub3d.h>
#include <cbd_error.h>
#include <cbd_render.h>
#include <libft.h>
#include <MLX42.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

bool	cbd_main(t_app *cbd)
{
	if (cbd_init(cbd))
		return (FAILURE);

	draw_gradient_bg(cbd->hud);
	mlx_loop(cbd->mlx);
	mlx_terminate(cbd->mlx);
	cleanup(cbd);
	return (SUCCESS);
}
