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
		cbd->elapsed_time += cbd->mlx->delta_time;
		cbd->render.img->instances->enabled = true;
		cbd->render.sprite_img->instances->enabled = true;
		update_player(&cbd->playerdata, cbd);
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

	cbd->render.headache_timer -= cbd->mlx->delta_time * 2;
	if (cbd->render.headache_timer < 0)
	{
		cbd->render.headache_timer = 1000;
	}

	if (cbd->playerdata.inv->equipped == WPN_CHAINSAW && cbd->playerdata.target_entity != NULL)
	{
		if ( mlx_is_key_down(cbd->mlx, MLX_KEY_SPACE) && cbd->playerdata.target_distance < 0.5)
		{
			cbd->render.fx.crt = true;
			cbd->render.particles.b_timer = true;
		}
	}

	//CRT timer
	if (cbd->render.fx.crt)
		cbd->render.fx.crt_timer -= cbd->mlx->delta_time * 1000;
	if (cbd->render.fx.crt_timer < 0)
	{
		cbd->render.fx.crt_timer = 100;
		cbd->render.fx.crt = false;
		// cbd->render.headbob = 0;
	}

}
