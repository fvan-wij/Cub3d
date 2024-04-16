#include <cub3d.h>
#include <cbd_error.h>
#include <cbd_audio.h>

void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
	t_app	*cbd;
	t_audio	*audio;

	(void)mods;
	cbd = (t_app*)param;
	audio = cbd->audio;
	if (button == MLX_MOUSE_BUTTON_LEFT)
	{
		if (action == MLX_PRESS)
		{
			if (cbd->playerdata.inv->equipped == WPN_FIST)
			{
				play_sound(audio, SND_PUNCH, 0.5f, 1.0f);
				destroy_wall(cbd->mapdata, &cbd->playerdata, cbd->audio);
			}
			if (cbd->playerdata.inv->equipped == WPN_CHAINSAW && cbd->playerdata.inv->wpns[WPN_CHAINSAW].ammo <= 0)
				play_sound(audio, SND_NO_FUEL, 1.0f, 1.0f);
			cbd->playerdata.inv->wpns[cbd->playerdata.inv->equipped].use_anim->loop = true;
		}
		if (action == MLX_RELEASE && cbd->playerdata.inv->equipped == WPN_CHAINSAW)
		{
			cbd->playerdata.inv->wpns[WPN_CHAINSAW].use_anim->loop = false;
			stop_sound(audio, SND_SAW);
		}
	}
	else if (button == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS)
	{
		// change_tv_channel(cbd->audio, cbd->mlx->keydata);
	}
}