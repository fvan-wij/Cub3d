#include <cub3d.h>
#include <cbd_error.h>
#include <libft.h>
#include <MLX42.h>
#include <stdio.h>

void	update_timers(t_fx *fx, float dt)
{
	// Screen blood splatter timer
	if (fx->splat)
		fx->splat_timer -= dt * 1000;
	if (fx->splat_timer < 0)
	{
		fx->splat_timer = 100;
		fx->splat_timer = false;
	}

	//Pulse timer
	fx->pulse_timer -= dt * 2;
	if (fx->pulse_timer < 0)
		fx->pulse_timer = 1000;
	//Screenshake
	if (fx->crt)
		fx->crt_timer -= dt * 1000;
	if (fx->crt_timer < 0)
	{
		fx->crt_timer = 100;
		fx->crt = false;
	}
}

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
		if (cbd->playerdata.inv->equipped == WPN_CHAINSAW && cbd->playerdata.target_entity != NULL)
		{
			if (mlx_is_key_down(cbd->mlx, MLX_KEY_SPACE) && cbd->playerdata.target_distance < 0.5)
			{
				cbd->render.fx.crt = true;
				cbd->render.fx.blood = true;
			}
		}
		update_timers(&cbd->render.fx, cbd->mlx->delta_time);
		play_weapon_animation(cbd->mlx, cbd->playerdata.inv);
		cbd_render(cbd);
	}
	else if (cbd->menudata->state == MAP_SELECT)
		display_preview(cbd->menudata, cbd->mapdata);
	else if (cbd->menudata->state == MAP_LOAD)
		change_map(cbd);


}
