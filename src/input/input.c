#include <libft.h>
#include <MLX42.h>
#include <cub3d.h>
#include <cbd_error.h>
#include <cbd_audio.h>
#include <stdio.h>

static void	destroy_wall(t_map *mapdata, t_player *player, t_audio *audio)
{
	const char target = mapdata->cbd_map[(int)(player->pos.y + player->dir.y)][(int)(player->pos.x + player->dir.x)];

	if (target == '=')
	{
		mapdata->cbd_map[(int)(player->pos.y + player->dir.y)][(int)(player->pos.x + player->dir.x)] = '-';
		play_sound(audio, SND_WALL1, 0.5f);
	}
	else if (target == '-')
	{
		mapdata->cbd_map[(int)(player->pos.y + player->dir.y)][(int)(player->pos.x + player->dir.x)] = '_';
		play_sound(audio, SND_WALL2, 0.5f);
	}
	else if (target == '_')
	{
		mapdata->cbd_map[(int)(player->pos.y + player->dir.y)][(int)(player->pos.x + player->dir.x)] = '0';
		play_sound(audio, SND_WALL3, 0.5f);
		play_sound(audio, SND_IMPACT2, 0.2f);
	}
}
// Menu input handling
void	menu_input(mlx_key_data_t keydata, t_app *cbd, t_audio *audio)
{
	// UP/W key input
	if ((keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W) && keydata.action == MLX_PRESS)
	{
		ma_sound_set_pitch(audio->sound[SND_TICK], 3.0f);
		play_sound(audio, SND_TICK, 1.0f);
		menu_move_cursor(cbd->menudata, -1);
	}
	// DOWN/S key input
	if ((keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S) && keydata.action == MLX_PRESS)
	{
		ma_sound_set_pitch(audio->sound[SND_TICK], 3.0f);
		play_sound(audio, SND_TICK, 1.0f);
		menu_move_cursor(cbd->menudata, 1);
	}
	// Key ENTER/SPACE
	if ((keydata.key == MLX_KEY_ENTER || keydata.key == MLX_KEY_SPACE) && keydata.action == MLX_PRESS)
	{
		ma_sound_set_pitch(audio->sound[SND_TICK], 1.0f);
		play_sound(audio, SND_TICK, 1.0f);
		menu_enter(cbd->menudata);
	}
}
// Game input handling
void	game_input(mlx_key_data_t keydata, t_app *cbd, t_audio *audio)
{
	// Space key input
	if (keydata.key == MLX_KEY_SPACE)
	{
		if (keydata.action == MLX_PRESS)
		{
			if (cbd->playerdata.inv->equipped == WPN_FIST)
			{
				play_sound(audio, SND_PUNCH, 0.5f);
				destroy_wall(cbd->mapdata, &cbd->playerdata, cbd->audio);
			}
			cbd->playerdata.inv->weapons[cbd->playerdata.inv->equipped].fire_animation->loop = true;
		}
		if (mlx_is_key_down(cbd->mlx, MLX_KEY_SPACE))
		{
			if (cbd->playerdata.inv->equipped == WPN_CHAINSAW)
			{
				if (cbd->playerdata.target_entity != NULL && cbd->playerdata.target_entity->type == ENTITY_ENEMY)
				{
					dismember_enemy(cbd);
					play_sound(audio, SND_GUTS, 0.8f);
				}
			}
		}
		if (keydata.action == MLX_RELEASE && cbd->playerdata.inv->equipped == WPN_CHAINSAW)
		{
			cbd->playerdata.inv->weapons[WPN_CHAINSAW].fire_animation->loop = false;
			stop_sound(audio, SND_SAW);
		}
	}
	// Set chainsaw sound state
	if (cbd->playerdata.inv->weapons[cbd->playerdata.inv->equipped].fire_animation->loop && cbd->playerdata.inv->equipped == WPN_CHAINSAW)
		loop_sound(audio, SND_SAW, false);
	else
		stop_sound(audio, SND_SAW);
	if (cbd->playerdata.inv->equipped == WPN_CHAINSAW && cbd->playerdata.inv->weapons[WPN_CHAINSAW].fire_animation->loop == false)
		loop_sound(audio, SND_SAW_IDLE, false);
	else
		stop_sound(audio, SND_SAW_IDLE);
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
	// If animation loop is false, check if player selects new item
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
			play_sound(audio, SND_SEARCH, 3.5f);
	}
}
// Global input handling
void	app_input(mlx_key_data_t keydata, t_app *cbd, t_audio *audio)
{
	// Key Escape
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		ma_sound_set_pitch(audio->sound[SND_TICK], 1.0f);
		play_sound(audio, SND_TICK, 1.0f);
		menu_escape(cbd->menudata);
		cbd->render.img->instances[0].enabled = false;
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
	app_input(keydata, cbd, audio);
	// Update sound based on state
	if (audio->trigger1 && audio->trigger1->distance < 0.05 && !audio->t1)
	{
		play_sound(audio, SND_IMPACT, 1.0f);
		audio->t1 = true;
	}
	if (cbd->menudata->state != OFF)
	{
		stop_sound(audio, SND_MUSIC);
		stop_sound(audio, SND_AMBIENT_LAUGH);
		loop_sound(audio, SND_MENU, false);
	}
	else if (cbd->menudata->state == OFF)
	{
		stop_sound(audio, SND_MENU);
		loop_sound(audio, SND_MUSIC, false);
		loop_sound(audio, SND_TV_NOISE, false);
		loop_sound(audio, SND_AMBIENT_LAUGH, false);
	}
	if (cbd->playerdata.state == PLAYER_RUNNING && cbd->menudata->state == OFF)
	{
		ma_sound_set_pitch(audio->sound[SND_WALK_SOLID], 1.2f);
		if (cbd->mapdata->current_map == LVL_DARK_SECRET)
			loop_sound(audio, SND_WALK_GRASS, true);
		else
			loop_sound(audio, SND_WALK_SOLID, true);
	}
	if (cbd->playerdata.state == PLAYER_WALKING && cbd->menudata->state == OFF)
	{
		ma_sound_set_pitch(audio->sound[SND_WALK_SOLID], 1.0f);
		if (cbd->mapdata->current_map == LVL_DARK_SECRET)
			loop_sound(audio, SND_WALK_GRASS, true);
		else
			loop_sound(audio, SND_WALK_SOLID, true);
	}
	if (cbd->playerdata.state == PLAYER_IDLE && cbd->menudata->state == OFF)
	{
		if (cbd->mapdata->current_map == LVL_DARK_SECRET)
			stop_sound(audio, SND_WALK_GRASS);
		else
			stop_sound(audio, SND_WALK_SOLID);
	}
}
