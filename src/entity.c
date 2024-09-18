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
		if (tmp_ent->state == ENTITY_AGROED && ft_strncmp(tmp_ent->name, "vc", 2) == 0)
		{
			new_pos = tmp_ent->pos;
			new_pos = vec_add(new_pos, vec_mult(tmp_ent->dir, tmp_ent->speed * cbd->mlx->delta_time));
			new_pos = resolve_collision(cbd->mapdata->cbd_map, tmp_ent->pos, tmp_ent->dir, new_pos);
			tmp_ent->pos = new_pos;
		}
		else if (cbd->checkpoint && tmp_ent->state == ENTITY_AGROED)
		{
			new_pos = tmp_ent->pos;
			new_pos = vec_add(new_pos, vec_mult(tmp_ent->dir, tmp_ent->speed * cbd->mlx->delta_time));
			new_pos = resolve_collision(cbd->mapdata->cbd_map, tmp_ent->pos, tmp_ent->dir, new_pos);
			tmp_ent->pos = new_pos;
		}
		tmp_ent = tmp_ent->next;
	}
}

void	update_foreshadowing(t_entity *ent, float dt)
{
	t_vec2d		new_pos;

	new_pos = ent->pos;
	ent->dir = vec_assign(-1.0, 0.0);
	new_pos = vec_add(new_pos, vec_mult(ent->dir, ent->speed * dt));
	ent->pos = new_pos;
}

void	update_enemy(t_entity *ent, t_app *cbd)
{
	t_audio *audio;

	audio = cbd->audio;


	if (audio->t2 && ft_strncmp("trigger2", ent->name, 8) == 0)
	{
		update_foreshadowing(ent, cbd->mlx->delta_time);
		if ((int) ent->pos.x < 21)
			ent->enabled = false;
	}
	if (vec_distance(ent->pos, ent->destinations[ent->current_dest]) < 0.1)
	{
		ent->state = ENTITY_IDLE;
		ent->current_dest++;
		if (ent->current_dest == ent->n_dest)
			ent->current_dest = 0;
	}
	if (vec_distance(cbd->playerdata.pos, ent->pos) < 10 && ft_strncmp("trigger2", ent->name, 8) != 0)
	{
		ent->state = ENTITY_AGROED;
		if (ft_strncmp(ent->name, "po", 2) == 0)
		{
			cbd->mapdata->cbd_map[2][14] = '4';
			cbd->checkpoint = true;
			audio->chase = true;
			if (!audio->boss_trigger)
			{
				play_sound(audio, SND_PO_TRIGGER, 0.25f, 1.0f);
				audio->boss_trigger = true;
			}
		}
		ent->dir = vec_sub(cbd->playerdata.pos, ent->pos);
		if (vec_distance(cbd->playerdata.pos, ent->pos) < 0.6)
		{
			if (cbd->playerdata.i_time <= 0)
			{
				ent->state = ENTITY_ATTACK;
				if (!ent->dead && cbd->state != STATE_BEHEAD)
				{
					audio->damage = true;
					attack_player(ent, &cbd->playerdata, &cbd->render.fx);
				}
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
			cbd->playerdata.inv->weapons[WPN_CHAINSAW].ammo+=20;
			item->enabled = false;
			audio->pickup = true;
		}
	}
	if (ft_strncmp(item->name, "po", 2) == 0 && item->enabled && item->dead)
	{
		if (vec_distance(item->pos, cbd->playerdata.pos) < 0.5 && !cbd->playerdata.inv->weapons[WPN_MAP].in_inventory)
		{
			// Add [pickup sound]
			cbd->playerdata.inv->weapons[WPN_CHAINSAW].fire_animation->loop = false;
			cbd->playerdata.inv->weapons[WPN_MAP].in_inventory = true;
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
			cbd->checkpoint_state.health = cbd->playerdata.health;
			cbd->checkpoint_state.ammo = cbd->playerdata.inv->weapons[WPN_CHAINSAW].ammo;
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
	update_checkpoint(ent, cbd);
}

void	update_entities(t_app *cbd)
{
	t_entity 	*ent;
	t_audio		*audio;

	ent = cbd->mapdata->entities;
	audio = cbd->audio;
	while (ent)
	{
		if (ft_strncmp("tv", ent->name, 2) == 0)
			audio->tv = ent;
		if (ft_strncmp("trigger1", ent->name, 8) == 0)
			audio->trigger1 = ent;
		if (ft_strncmp("trigger2", ent->name, 8) == 0)
			audio->trigger2 = ent;
		if (ft_strncmp("po", ent->name, 2) == 0)
			audio->enemy = ent;
		if (ft_strncmp("vc", ent->name, 2) == 0 && ent->distance < 20)
		{
			audio->vc = ent;
			if (ent->animation.current_animation == 2)
			{
				ent->dead = true;
				ent->speed = 0;
				ent->health = 0;
			}
		}
		update_entity(ent, cbd);
		ent = ent->next;
	}
}
