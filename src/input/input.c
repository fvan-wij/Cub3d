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
	}
}

t_entity *spawn_blood(t_entity *head, t_player *player, uint8_t limb)
{
	t_entity *node;
	t_entity *curr;

	node = ft_calloc(1, sizeof(t_entity));
	if (!node)
		return (cbd_error(ERR_ALLOC), head);
	curr = head;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = node;
	node->next = NULL;
	node->name = ft_strdup("blood");
	node->pos = vec_assign(player->pos.x + player->dir.x, player->pos.y + player->dir.y);
	node->type = ENTITY_DECOR;
	node->texture = mlx_load_png("./data/textures/sprites/limbs3.png");
	node->frame_width = 128;
	node->frame_height = 128;
	node->enabled = true;
	node->animation = load_animation(node->texture, node->frame_width, node->frame_height);
	node->animation.current_animation = limb;
	return (head);
}

void	dismember_enemy(t_app *cbd)
{
	static int	limb;
	static int	i;
	t_entity	*target;
	double		target_distance;

	target = cbd->playerdata.target_entity;
	target_distance = cbd->playerdata.target_distance;
	if (ft_strncmp(target->name, "po", 2) == 0 && target_distance < 0.5)
	{
		if (i % 25 == 0)
		{
			target->health-=2;
			target->speed-=0.2;
			if (limb <= 4)
				spawn_blood(cbd->mapdata->entities, &cbd->playerdata, limb);
			limb++;
		}
		if (target->health <= 0)
		{
			target->health = 0;
			target->speed = 0;
		}
		cbd->render.splat.b_timer = true;
		i++;
	}
}

void	cbd_input(mlx_key_data_t keydata, void *param)
{
	t_app		*cbd;
	t_audio 	*audio;

	cbd = param;
	audio = (t_audio *) cbd->audio;
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS && cbd->playerdata.inv->equipped != WPN_MAP)
	{
		if (cbd->playerdata.inv->equipped == WPN_FIST)
		{
			play_sound(audio, SND_PUNCH, 0.5f);
			destroy_wall(cbd->mapdata, &cbd->playerdata, cbd->audio);
		}
		cbd->playerdata.inv->weapons[cbd->playerdata.inv->equipped].fire_animation->loop = true;
	}
	if (cbd->playerdata.inv->equipped == WPN_CHAINSAW)
	{
		if (cbd->playerdata.target_entity != NULL && mlx_is_key_down(cbd->mlx, MLX_KEY_SPACE))
		{
			dismember_enemy(cbd);
			play_sound(audio, SND_GUTS, 0.5f);
		}
	}
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_RELEASE && cbd->playerdata.inv->equipped == WPN_CHAINSAW)
		cbd->playerdata.inv->weapons[cbd->playerdata.inv->equipped].fire_animation->loop = false;
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
	{
		if (cbd->menudata->state != OFF)
		{
			ma_sound_set_pitch(audio->sound[SND_TICK], 3.0f);
			play_sound(audio, SND_TICK, 1.0f);
			menu_move_cursor(cbd->menudata, -1);
		}
	}
	if (!mlx_is_key_down(cbd->mlx, MLX_KEY_UP)
		&& !mlx_is_key_down(cbd->mlx, MLX_KEY_DOWN)
		&& !mlx_is_key_down(cbd->mlx, MLX_KEY_W)
		&& !mlx_is_key_down(cbd->mlx, MLX_KEY_S)
		&& !mlx_is_key_down(cbd->mlx, MLX_KEY_A)
		&& !mlx_is_key_down(cbd->mlx, MLX_KEY_D))
		cbd->playerdata.state = PLAYER_IDLE;
	if ((keydata.key == MLX_KEY_DOWN
		|| keydata.key == MLX_KEY_UP
		|| keydata.key == MLX_KEY_W
		|| keydata.key == MLX_KEY_S
		|| keydata.key == MLX_KEY_A
		|| keydata.key == MLX_KEY_D)
		&& keydata.action == MLX_PRESS
		&& cbd->menudata->state == OFF && keydata.key != MLX_KEY_LEFT_SHIFT)
		cbd->playerdata.state = PLAYER_WALKING;

	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
	{
		if (cbd->menudata->state != OFF)
		{
			ma_sound_set_pitch(audio->sound[SND_TICK], 3.0f);
			play_sound(audio, SND_TICK, 1.0f);
			menu_move_cursor(cbd->menudata, 1);
		}
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		ma_sound_set_pitch(audio->sound[SND_TICK], 1.0f);
		play_sound(audio, SND_TICK, 1.0f);
		menu_escape(cbd->menudata);
		cbd->render.img->instances[0].enabled = false;
	}
	if (keydata.key == MLX_KEY_ENTER && keydata.action == MLX_PRESS)
	{
		if (cbd->state == STATE_MENU)
		{
			ma_sound_set_pitch(audio->sound[SND_TICK], 1.0f);
			play_sound(audio, SND_TICK, 1.0f);
			menu_enter(cbd->menudata);
		}
	}
	if (!cbd->playerdata.inv->weapons[cbd->playerdata.inv->equipped].fire_animation->loop)
	{
		int current_wpn = cbd->playerdata.inv->equipped;
		if (mlx_is_key_down(cbd->mlx, MLX_KEY_1))
			cbd->playerdata.inv->equipped = WPN_FIST;
		if (mlx_is_key_down(cbd->mlx, MLX_KEY_2) && cbd->playerdata.inv->weapons[WPN_CHAINSAW].in_inventory)
			cbd->playerdata.inv->equipped = WPN_CHAINSAW;
		if (mlx_is_key_down(cbd->mlx, MLX_KEY_M))
			cbd->playerdata.inv->equipped = WPN_MAP;
		if (current_wpn != cbd->playerdata.inv->equipped)
			play_sound(audio, SND_SEARCH, 3.5f);
	}

	if (cbd->menudata->state != OFF)
	{
		stop_sound(audio, SND_MUSIC);
		loop_sound(audio, SND_MENU, false);
	}
	else if (cbd->menudata->state == OFF)
	{
		stop_sound(audio, SND_MENU);
		loop_sound(audio, SND_MUSIC, false);
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
