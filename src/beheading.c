#include <cub3d.h>
#include <cbd_audio.h>

void	start_beheading(t_app *cbd)
{
	t_audio *audio = cbd->audio;

	cbd->beheading.active = true;
	cbd->beheading.timer = 10.0f;
	cbd->playerdata.inv->weapons[WPN_CHAINSAW].fire_animation->loop = true;
	cbd->playerdata.inv->weapons[WPN_CHAINSAW].fire_animation->current_x = cbd->beheading.chainsaw_pos.x;
	cbd->playerdata.inv->weapons[WPN_CHAINSAW].ammo = 50000;
	cbd->render.po_head->enabled = true;
	if (cbd->playerdata.target_entity != NULL)
	{
	cbd->playerdata.pos = vec_add(cbd->playerdata.target_entity->pos, vec_mult(cbd->playerdata.target_entity->dir, 0.5)); //Move player in front of target position
	// Rotate player to face target
	cbd->playerdata.dir = vec_sub(cbd->playerdata.target_entity->pos, cbd->playerdata.pos);
	vec_normalize(&cbd->playerdata.dir);
	}
	loop_sound(audio, SND_SAW_IDLE, false);
}

void	stop_beheading(t_app *cbd)
{
	t_audio *audio = cbd->audio;

	cbd->beheading.sawing = false;
	cbd->beheading.active = false;
	cbd->render.fx.blood = false;
	cbd->render.fx.crt = false;
	cbd->playerdata.inv->weapons[WPN_CHAINSAW].fire_animation->loop = false;
	cbd->playerdata.inv->weapons[WPN_CHAINSAW].fire_animation->current_x = cbd->playerdata.inv->weapons[WPN_CHAINSAW].fire_animation->reset_x;
	cbd->render.po_head->enabled = false;
	cbd->beheading.timer = 0;
	cbd->beheading.chainsaw_pos.x = WIDTH / 3 - 100;
	cbd->state = STATE_GAME;
	cbd->playerdata.target_entity->health = 0;
	stop_sound(audio, SND_SAW);
	stop_sound(audio, SND_GUTS);
	loop_sound(audio, SND_SAW_IDLE, false);
}

void	start_sawing(t_app *cbd)
{
	t_audio *audio = cbd->audio;

	cbd->beheading.sawing = true;
	stop_sound(audio, SND_SAW_IDLE);
	loop_sound(audio, SND_GUTS, false);
	loop_sound(audio, SND_SAW, false);
}

void	stop_sawing(t_app *cbd)
{
	t_audio *audio = cbd->audio;

	cbd->beheading.sawing = false;
	stop_sound(audio, SND_SAW);
	stop_sound(audio, SND_GUTS);
	loop_sound(audio, SND_SAW_IDLE, false);
}

void	behead(t_app *cbd)
{
	if (cbd->beheading.active == false)
		start_beheading(cbd);
	if (cbd->beheading.sawing == false && mlx_is_key_down(cbd->mlx, MLX_KEY_SPACE))
		start_sawing(cbd);
	if (cbd->beheading.sawing == true && mlx_is_key_down(cbd->mlx, MLX_KEY_SPACE) == false)
		stop_sawing(cbd);
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_SPACE))
	{
		cbd->render.fx.blood = true;
		cbd->render.fx.splat = true;
		// cbd->render.fx.crt = true;
		cbd->beheading.timer -= cbd->mlx->delta_time;
		cbd->beheading.chainsaw_pos.x += 30.0f * cbd->mlx->delta_time;
	}
	cbd->render.po_head->instances[0].y = cbd->render.y_offset;
	cbd->playerdata.inv->weapons[WPN_CHAINSAW].fire_animation->current_x = cbd->beheading.chainsaw_pos.x;
	if (cbd->beheading.chainsaw_pos.x >= WIDTH / 2 - 100)
	{
		stop_beheading(cbd);
	}
}
