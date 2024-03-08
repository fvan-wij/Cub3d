#include <cub3d.h>
#include <cbd_error.h>
#include <libft.h>
#include <MLX42.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void	cbd_loop(void *param)
{
	t_app *cbd;

	cbd = param;
	move_player(cbd);
	cbd_render(cbd);
}
