#include <cub3d.h>
#include <stdio.h>
#include <stdlib.h>

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

// void	update_entity(t_entity *ent, t_app *cbd)
// {
// 	if (ent->health >= 1 || ent->type == ENTITY_DECOR)
// 		animate_entity(ent, cbd);
// 	if (ent->type == ENTITY_ENEMY)
// 	{
// 		if (vec_distance(ent->pos, ent->destinations[ent->current_dest]) < 0.1)
// 		{
// 			ent->state = ENTITY_IDLE;
// 			ent->current_dest++;
// 			if (ent->current_dest == ent->n_dest)
// 				ent->current_dest = 0;
// 		}
// 		if (vec_distance(cbd->playerdata.pos, ent->pos) < 2)
// 		{
// 			ent->state = ENTITY_AGROED;
// 			ent->dir = vec_sub(cbd->playerdata.pos, ent->pos);
// 		}
// 		else if (vec_distance(ent->destinations[ent->current_dest], ent->pos) > 0.05)
// 		{
// 			ent->dir = vec_sub(ent->destinations[ent->current_dest], ent->pos);
// 			ent->state = ENTITY_PATROL;
// 		}
// 		vec_normalize(&ent->dir);
// 		// Determine if the entity is moving away from the player
// 		if (vec_dot(ent->dir, vec_sub(cbd->playerdata.pos, ent->pos)) < 0)
// 			ent->animation.current_animation = (9 - ent->health + 1);
// 		else
// 			ent->animation.current_animation = (9 - ent->health);
// 	}
// }

void	update_enemy(t_entity *ent, t_app *cbd)
{
	if (vec_distance(ent->pos, ent->destinations[ent->current_dest]) < 0.1)
	{
		ent->state = ENTITY_IDLE;
		ent->current_dest++;
		if (ent->current_dest == ent->n_dest)
			ent->current_dest = 0;
	}
	if (vec_distance(cbd->playerdata.pos, ent->pos) < 2)
	{
		ent->state = ENTITY_AGROED;
		ent->dir = vec_sub(cbd->playerdata.pos, ent->pos);
	}
	else if (vec_distance(ent->destinations[ent->current_dest], ent->pos) > 0.05)
	{
		ent->dir = vec_sub(ent->destinations[ent->current_dest], ent->pos);
		ent->state = ENTITY_PATROL;
	}
	vec_normalize(&ent->dir);
	// Determine if the entity is moving away from the player
	if (vec_dot(ent->dir, vec_sub(cbd->playerdata.pos, ent->pos)) < 0)
		ent->animation.current_animation = (9 - (int)ent->health + 1);
	else
		ent->animation.current_animation = (9 - (int)ent->health);
	if (ent->health == 0)
		ent->animation.enabled = false;
}

void	update_item(t_entity *item, t_app *cbd)
{
	if (ft_strncmp(item->name, "chainsaw", 9) == 0 && item->enabled)
	{
		// printf("item->name: %s\n", item->name);
		if (vec_distance(item->pos, cbd->playerdata.pos) < 0.5 && !cbd->playerdata.inv->weapons[WPN_CHAINSAW].in_inventory)
		{
			printf("Picked up chainsaw\n");
			// Add [pickup sound]
			cbd->playerdata.inv->weapons[WPN_CHAINSAW].in_inventory = true;
			cbd->playerdata.inv->equipped = WPN_CHAINSAW;
			item->enabled = false;
		}
	}
}

void	update_entity(t_entity *ent, t_app *cbd)
{
	animate_entity(ent, cbd);
	// printf("ent->name: %s\n", ent->name);
	if (ent->type == ENTITY_ENEMY)
	{
		update_enemy(ent, cbd);
	}
	if (ent->type == ENTITY_ITEM)
	{
		update_item(ent, cbd);
	}
}

void	update_entities(t_app *cbd)
{
	t_entity *ent;

	ent = cbd->mapdata->entities;
	while (ent)
	{
		update_entity(ent, cbd);
		ent = ent->next;
	}
}
