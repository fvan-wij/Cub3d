#include <libft.h>
#include <MLX42.h>
#include <cub3d.h>
#include <cbd_error.h>
#include <cbd_audio.h>
#include <stdio.h>

void	destroy_wall(t_map *mapdata, t_player *player, t_audio *audio)
{
	const char target = mapdata->cbd_map[(int)(player->pos.y + player->dir.y)][(int)(player->pos.x + player->dir.x)];

	if (target == '=')
	{
		mapdata->cbd_map[(int)(player->pos.y + player->dir.y)][(int)(player->pos.x + player->dir.x)] = '-';
		play_sound(audio, SND_WALL2, 0.25f, 1.0f);
	}
	else if (target == '-')
	{
		mapdata->cbd_map[(int)(player->pos.y + player->dir.y)][(int)(player->pos.x + player->dir.x)] = '_';
		play_sound(audio, SND_WALL1, 0.25f, 1.0f);
	}
	else if (target == '_')
	{
		mapdata->cbd_map[(int)(player->pos.y + player->dir.y)][(int)(player->pos.x + player->dir.x)] = '0';
		play_sound(audio, SND_WALL3, 0.25f, 1.0f);
		if (mapdata->cbd_map[29][25] == '0' && !audio->secret)
		{
			play_sound(audio, SND_IMPACT2, 0.2f, 1.0f);
			audio->secret = true;
		}
	}
}

void change_tv_channel(t_audio *audio, mlx_key_data_t keydata)
{
	if (audio->tv && audio->tv->distance < 1 && keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
	{
		stop_sound(audio, (SND_TV_BYE + audio->channel));
		audio->tv->animation.current_animation++;
		if (audio->tv->animation.current_animation >= audio->tv->animation.n_animations)
			audio->tv->animation.current_animation = 0;
		audio->channel = audio->tv->animation.current_animation;
	}
}

// Menu input handling
void	menu_input(mlx_key_data_t keydata, t_app *cbd, t_audio *audio)
{
	// UP/W key input
	if ((keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W) && keydata.action == MLX_PRESS)
	{
		play_sound(audio, SND_TICK, 1.0f, 3.0f);
		menu_move_cursor(cbd->menudata, -1);
	}
	// DOWN/S key input
	if ((keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S) && keydata.action == MLX_PRESS)
	{
		play_sound(audio, SND_TICK, 1.0f, 3.0f);
		menu_move_cursor(cbd->menudata, 1);
	}
	// Key ENTER/SPACE
	if ((keydata.key == MLX_KEY_ENTER || keydata.key == MLX_KEY_SPACE) && keydata.action == MLX_PRESS)
	{
		play_sound(audio, SND_TICK, 1.0f, 1.0f);
		menu_enter(cbd->menudata);
		if (cbd->menudata->state == OFF)
		{
			cbd->state = STATE_GAME;
			// mlx_set_cursor_mode(cbd->mlx, MLX_MOUSE_DISABLED);
			// mlx_set_mouse_pos(cbd->mlx, cbd->prev_mouse.x, cbd->prev_mouse.y);
		}
	}}
// Game input handling
void	game_input(mlx_key_data_t keydata, t_app *cbd, t_audio *audio)
{
	// Space key input
	if (keydata.key == MLX_KEY_SPACE)
	{
		if (keydata.action == MLX_PRESS)
		{
			if (cbd->playerdata.inv->equipped == WPN_MAP)
				return ;
			if (cbd->playerdata.inv->equipped == WPN_FIST)
			{
				play_sound(audio, SND_PUNCH, 0.5f, 1.0f);
				destroy_wall(cbd->mapdata, &cbd->playerdata, cbd->audio);
				deal_fist_damage(cbd);
			}
			if (cbd->playerdata.inv->equipped == WPN_CHAINSAW && cbd->playerdata.inv->weapons[WPN_CHAINSAW].ammo <= 0)
				play_sound(audio, SND_NO_FUEL, 1.0f, 1.0f);
			cbd->playerdata.inv->weapons[cbd->playerdata.inv->equipped].fire_animation->loop = true;
		}
		if (keydata.action == MLX_RELEASE && cbd->playerdata.inv->equipped == WPN_CHAINSAW)
		{
			cbd->playerdata.inv->weapons[WPN_CHAINSAW].fire_animation->loop = false;
			stop_sound(audio, SND_SAW);
		}
	}

	if (cbd->render.fx.blood)
		play_sound(audio, SND_GUTS, 1.5f, 1.0f);

	// Player movement input
	cbd->playerdata.state = PLAYER_IDLE;
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_UP)
		|| mlx_is_key_down(cbd->mlx, MLX_KEY_DOWN)
		|| mlx_is_key_down(cbd->mlx, MLX_KEY_W)
		|| mlx_is_key_down(cbd->mlx, MLX_KEY_S)
		|| mlx_is_key_down(cbd->mlx, MLX_KEY_A)
		|| mlx_is_key_down(cbd->mlx, MLX_KEY_D))
		cbd->playerdata.state = PLAYER_WALKING;
	if (cbd->playerdata.state != PLAYER_IDLE && mlx_is_key_down(cbd->mlx, MLX_KEY_LEFT_SHIFT))
		cbd->playerdata.state = PLAYER_RUNNING;

	//Item select sound
	if (!cbd->playerdata.inv->weapons[cbd->playerdata.inv->equipped].fire_animation->loop)
	{
		int current_wpn = cbd->playerdata.inv->equipped;
		if (mlx_is_key_down(cbd->mlx, MLX_KEY_1))
			cbd->playerdata.inv->equipped = WPN_FIST;
		if (mlx_is_key_down(cbd->mlx, MLX_KEY_2) && cbd->playerdata.inv->weapons[WPN_CHAINSAW].in_inventory)
			cbd->playerdata.inv->equipped = WPN_CHAINSAW;
		if (mlx_is_key_down(cbd->mlx, MLX_KEY_M) && cbd->playerdata.inv->weapons[WPN_MAP].in_inventory)
			cbd->playerdata.inv->equipped = WPN_MAP;
		if (current_wpn != cbd->playerdata.inv->equipped)
			play_sound(audio, SND_SEARCH, 3.5f, 1.0f);
	}
}

// Global input handling
void	app_input(mlx_key_data_t keydata, t_app *cbd, t_audio *audio)
{
	// Key Escape
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		play_sound(audio, SND_TICK, 1.0f, 1.0f);
		menu_escape(cbd->menudata);
		cbd->render.img->instances[0].enabled = false;
		cbd->state = STATE_MENU;
	}
}

void	cbd_input(mlx_key_data_t keydata, void *param)
{
	t_app		*cbd;
	t_audio 	*audio;

	cbd = param;
	audio = (t_audio *) cbd->audio;
	if (cbd->menudata->state == OFF)
		game_input(keydata, cbd, audio);
	else
		menu_input(keydata, cbd, audio);
	change_tv_channel(audio, keydata);
	app_input(keydata, cbd, audio);
}
