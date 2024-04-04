#include <cub3d.h>
#include <cbd_error.h>
#include <libft.h>
#include <MLX42.h>
#include <stdio.h>
#include <cbd_audio.h>

static void loop_chainsaw(t_app *cbd)
{
	if (cbd->playerdata.inv->equipped == WPN_CHAINSAW && cbd->playerdata.target_entity != NULL)
	{
		if (mlx_is_key_down(cbd->mlx, MLX_KEY_SPACE) && cbd->playerdata.target_distance < 0.5)
		{
			cbd->render.fx.crt = true;
			cbd->render.fx.blood = true;
		}
	}
}

static void	update_timers(t_fx *fx, float dt)
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

static void	loop_dynamic_audio(t_audio *audio)
{
	float 		vol;
	t_entity 	*tv;

	tv = audio->tv;
	if (!tv || tv->distance > 1.0)
	{
		ma_sound_set_volume(audio->sound[SND_TV_NOISE], 0.0f);
		// ma_sound_set_volume(audio->sound[SND_AMBIENT_LAUGH], 0.0f);
		return ;
	}
	// printf("Hai\n");
	vol = 0.2f - tv->distance;
	if (vol < 0.0)
		vol = 0.0f;
	ma_sound_set_volume(audio->sound[SND_TV_NOISE], vol);
	// ma_sound_set_volume(audio->sound[SND_AMBIENT_LAUGH], vol + 0.5f);
}

void	cbd_loop(void *param)
{
	t_app 	*cbd;
	t_audio *audio;

	cbd = param;
	audio = cbd->audio;
	if (cbd->menudata->state == OFF)
	{
		cbd->elapsed_time += cbd->mlx->delta_time;
		cbd->render.img->instances->enabled = true;
		cbd->render.sprite_img->instances->enabled = true;
		update_player(&cbd->playerdata, cbd);
		move_player(cbd);
		update_entities(cbd);
		move_entities(cbd->mapdata->entities, cbd);
		loop_chainsaw(cbd);
		update_timers(&cbd->render.fx, cbd->mlx->delta_time);
		play_weapon_animation(cbd->mlx, cbd->playerdata.inv);
		loop_dynamic_audio(audio);
		cbd_render(cbd);
	}
	else if (cbd->menudata->state == MAP_SELECT)
		display_preview(cbd->menudata, cbd->mapdata);
	else if (cbd->menudata->state == MAP_LOAD)
		change_map(cbd);


}
