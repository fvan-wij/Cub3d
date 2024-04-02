#include <cub3d.h>
#include <cbd_error.h>
#include <libft.h>
#include <MLX42.h>
#include <stdio.h>

void	cbd_loop(void *param)
{
	t_app *cbd;

	cbd = param;
	if (cbd->menudata->state == OFF)
	{
		cbd->render.img->instances->enabled = true;
		cbd->render.sprite_img->instances->enabled = true;
		move_player(cbd);
		update_entities(cbd);
		move_entities(cbd->mapdata->entities, cbd);
		play_weapon_animation(cbd->mlx, cbd->playerdata.inv);
		cbd_render(cbd);
	}
	else if (cbd->menudata->state == MAP_SELECT)
		display_preview(cbd->menudata, cbd->mapdata);
	else if (cbd->menudata->state == MAP_LOAD)
		change_map(cbd);

	//Blood splat timer
	if (cbd->render.splat.b_timer)
		cbd->render.splat.timer -= cbd->mlx->delta_time * 1000;
	if (cbd->render.splat.timer < 0)
	{
		cbd->render.splat.timer = 100;
		cbd->render.splat.b_timer = false;
	}

	//Blood particles timer
	if (cbd->render.particles.b_timer)
		cbd->render.particles.timer -= cbd->mlx->delta_time * 1000;
	if (cbd->render.particles.timer < 0)
	{
		cbd->render.particles.timer = 10000;
		cbd->render.particles.b_timer = false;
	}
}
