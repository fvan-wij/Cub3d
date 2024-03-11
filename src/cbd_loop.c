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
	if (cbd->menudata->state == OFF)
	{
		cbd->game->instances->enabled = true;
		move_player(cbd);
		play_weapon_animation(cbd->mlx, cbd->playerdata.inv);
		cbd_render(cbd);
	}
	else if (cbd->menudata->state == MAP_SELECT)
		display_preview(cbd->menudata, cbd->mapdata);
}
