#include "cbd_audio.h"
#include <cub3d.h>
#include <stdio.h>

void	animate_entity(t_entity *ent, t_app *cbd)
{
	if (ent->animation.enabled == false)
		return ;
	if (ent->type == ENTITY_ENEMY || ent->type == ENTITY_DECOR)
	{
		if (ent->state != ENTITY_IDLE || ent->type == ENTITY_DECOR)
		{
			if (ent->animation.timer <= 0)
			{
				ent->animation.current_frame++;
				if (ent->animation.current_frame == ent->animation.n_frames)
					ent->animation.current_frame = 0;
				ent->animation.timer = ent->animation.duration;
			}
			else
				ent->animation.timer -= cbd->mlx->delta_time;
		}
	}
}

void	move_entities(t_entity *ent, t_app *cbd)
{
	t_vec2d		new_pos;
	t_entity	*tmp_ent;

	tmp_ent = ent;
	while (tmp_ent)
	{
		if (ent->type == ENTITY_ENEMY)
		{
			if (tmp_ent->state == ENTITY_IDLE)
				return;
			new_pos = tmp_ent->pos;
			new_pos = vec_add(new_pos, vec_mult(tmp_ent->dir, tmp_ent->speed * cbd->mlx->delta_time));
			new_pos = resolve_collision(cbd->mapdata->cbd_map, tmp_ent->pos, tmp_ent->dir, new_pos);
			tmp_ent->pos = new_pos;
		}
		tmp_ent = tmp_ent->next;
	}
}

void	update_enemy(t_entity *ent, t_app *cbd)
{
	t_audio *audio;

	audio = cbd->audio;
	if (vec_distance(ent->pos, ent->destinations[ent->current_dest]) < 0.1)
	{
		ent->state = ENTITY_IDLE;
		ent->current_dest++;
		if (ent->current_dest == ent->n_dest)
			ent->current_dest = 0;
	}
	if (vec_distance(cbd->playerdata.pos, ent->pos) < 10)
	{
		ent->state = ENTITY_AGROED;
		cbd->mapdata->cbd_map[2][14] = '4';
		cbd->checkpoint = true;
		audio->chase = true;
		ent->dir = vec_sub(cbd->playerdata.pos, ent->pos);
		if (vec_distance(cbd->playerdata.pos, ent->pos) < 0.25)
		{
			if (cbd->playerdata.i_time <= 0)
			{
				ent->state = ENTITY_ATTACK;
				audio->damage = true;
				attack_player(ent, &cbd->playerdata, &cbd->render.fx);
			}
			ent->state = ENTITY_IDLE;
		}
	}
	else if (vec_distance(ent->destinations[ent->current_dest], ent->pos) > 0.05)
	{
		ent->dir = vec_sub(ent->destinations[ent->current_dest], ent->pos);
		ent->state = ENTITY_PATROL;
	}
	vec_normalize(&ent->dir);
	// Determine if the entity is moving away from the player
	if (ent->health < 0)
		ent->enabled = false;
	// else if (vec_dot(ent->dir, vec_sub(cbd->playerdata.pos, ent->pos)) < 0)
	// 	ent->animation.current_animation = (11 - (int)ent->health + 1);
	// else
	// 	ent->animation.current_animation = (11 - (int)ent->health);
	// printf("health: %d\n", ent->health);
}

void	update_item(t_entity *item, t_app *cbd)
{
	t_audio *audio;

	audio = cbd->audio;
	if (ft_strncmp(item->name, "chainsaw", 9) == 0 && item->enabled)
	{
		if (vec_distance(item->pos, cbd->playerdata.pos) < 0.5 && !cbd->playerdata.inv->weapons[WPN_CHAINSAW].in_inventory)
		{
			// Add [pickup sound]
			cbd->playerdata.inv->weapons[WPN_CHAINSAW].in_inventory = true;
			cbd->playerdata.inv->equipped = WPN_CHAINSAW;
			item->enabled = false;
			audio->pickup = true;
		}
	}
	if (ft_strncmp(item->name, "fuel", 4) == 0 && item->enabled)
	{
		if (vec_distance(item->pos, cbd->playerdata.pos) < 0.5)
		{
			// Add [pickup sound]
			cbd->playerdata.inv->weapons[WPN_CHAINSAW].ammo+=25;
			item->enabled = false;
			audio->pickup = true;
		}
	}
	if (ft_strncmp(item->name, "po", 2) == 0 && item->enabled && item->health == 0)
	{
		if (vec_distance(item->pos, cbd->playerdata.pos) < 0.5 && !cbd->playerdata.inv->weapons[WPN_MAP].in_inventory)
		{
			// Add [pickup sound]
			cbd->playerdata.inv->weapons[WPN_CHAINSAW].fire_animation->loop = false;
			cbd->playerdata.inv->weapons[WPN_MAP].in_inventory = true;
			cbd->playerdata.inv->equipped = WPN_MAP;
			item->enabled = false;
			audio->pickup = true;
		}
	}
}

void	update_checkpoint(t_entity *ent, t_app *cbd)
{
	t_audio *audio;

	audio = cbd->audio;
	if (cbd->checkpoint)
		return ;
	if (ft_strncmp(ent->name, "checkpoint", 10) == 0)
	{
		if (vec_distance(ent->pos, cbd->playerdata.pos) < 0.5)
		{
			// Add [checkpoint sound]
			audio->checkpoint = true;
			cbd->mapdata->cbd_map[2][14] = '4';
			printf("Triggered checkpoint");
		}
	}
}

void	update_entity(t_entity *ent, t_app *cbd)
{
	if (!ent->enabled)
		return ;
	animate_entity(ent, cbd);
	if (ent->type == ENTITY_ENEMY && ent->enabled)
	{
		update_enemy(ent, cbd);
	}
	if (ent->type == ENTITY_ITEM || ent->type == ENTITY_ENEMY)
	{
		update_item(ent, cbd);
	}
	// if (ent->type == ENTITY_DECOR)
	// {
	// 	update_checkpoint(ent, cbd);
	// }
}

void	update_entities(t_app *cbd)
{
	t_entity 	*ent;
	t_audio		*audio;

	ent = cbd->mapdata->entities;
	audio = cbd->audio;
	while (ent)
	{
		update_entity(ent, cbd);
		if (ft_strncmp("tv", ent->name, 2) == 0)
			audio->tv = ent;
		if (ft_strncmp("trigger1", ent->name, 8) == 0)
			audio->trigger1 = ent;
		if (ft_strncmp("po", ent->name, 2) == 0)
			audio->enemy = ent;
		ent = ent->next;
	}
}
