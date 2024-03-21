#include <libft.h>
#include <MLX42.h>
#include <stdlib.h>
#include <cub3d.h>
#include <cbd_error.h>
#include <math.h>
#include <stdio.h>
#include <cbd_audio.h>

void	cbd_input(mlx_key_data_t keydata, void *param)
{
	t_app		*cbd;
	t_audio 	*audio;

	cbd = param;
	audio = (t_audio *) cbd->audio;
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS && cbd->playerdata.inv->equipped != WPN_MAP)
	{
		if (cbd->playerdata.inv->equipped == WPN_FIST)
			play_sound(audio, SND_PUNCH);
		cbd->playerdata.inv->weapons[cbd->playerdata.inv->equipped].fire_animation->loop = true;
	}
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
	{
		if (cbd->menudata->state == OFF)
			loop_sound(audio, SND_WALK);
		if (cbd->menudata->state != OFF)
		{
			ma_sound_set_pitch(audio->sound[SND_TICK], 3.0f);
			play_sound(audio, SND_TICK);
			menu_move_cursor(cbd->menudata, -1);
		}
	}
	if (keydata.modifier == MLX_SHIFT)
		ma_sound_set_pitch(audio->sound[SND_WALK], 1.2f);
	else
		ma_sound_set_pitch(audio->sound[SND_WALK], 1.0f);
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_RELEASE)
		stop_sound(audio, SND_WALK);
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
	{
		if (cbd->menudata->state != OFF)
		{
			ma_sound_set_pitch(audio->sound[SND_TICK], 3.0f);
			play_sound(audio, SND_TICK);
			menu_move_cursor(cbd->menudata, 1);
		}
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		ma_sound_set_pitch(audio->sound[SND_TICK], 1.0f);
		play_sound(audio, SND_TICK);
		menu_escape(cbd->menudata);
		cbd->render.img->instances[0].enabled = false;
	}
	if (keydata.key == MLX_KEY_ENTER && keydata.action == MLX_PRESS)
	{
		if (cbd->state == STATE_MENU)
		{
			ma_sound_set_pitch(audio->sound[SND_TICK], 1.0f);
			play_sound(audio, SND_TICK);
			menu_enter(cbd->menudata);
		}
	}
	if (keydata.key == MLX_KEY_ENTER && keydata.action == MLX_RELEASE && cbd->menudata->state == OFF)
	{
		stop_sound(audio, SND_MENU);
		play_sound(audio, SND_MUSIC);
	}
	if (!cbd->playerdata.inv->weapons[cbd->playerdata.inv->equipped].fire_animation->loop)
	{
		int current_wpn = cbd->playerdata.inv->equipped;
		if (mlx_is_key_down(cbd->mlx, MLX_KEY_1))
			cbd->playerdata.inv->equipped = WPN_FIST;
		if (mlx_is_key_down(cbd->mlx, MLX_KEY_2))
			cbd->playerdata.inv->equipped = WPN_CHAINSAW;
		if (mlx_is_key_down(cbd->mlx, MLX_KEY_M))
			cbd->playerdata.inv->equipped = WPN_MAP;
		if (current_wpn != cbd->playerdata.inv->equipped)
			play_sound(audio, SND_SEARCH);
	}
}
