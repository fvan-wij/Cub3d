#include <cub3d.h>
#include <stdio.h>

void	move_entities(t_entity *ent, t_app *cbd)
{
	t_vec2d new_pos;

	if (ent->type == ENTITY_ENEMY)
	{
		if (vec_distance(cbd->playerdata.pos, ent->pos) < 0.5)
			return;
		new_pos = ent->pos;
		new_pos = vec_add(new_pos, vec_mult(ent->dir, ent->speed * cbd->mlx->delta_time));
		new_pos = resolve_collision(cbd->mapdata->cbd_map, ent->pos, ent->dir, new_pos);
		ent->pos = new_pos;
	}
}

void	update_entity(t_entity *ent, t_app *cbd)
{
	if (ent->type == ENTITY_ENEMY)
	{
		if (vec_distance(ent->pos, ent->destinations[ent->current_dest]) < 0.1)
		{
			ent->current_dest++;
			if (ent->current_dest == ent->n_dest)
			{
				ent->current_dest = 0;
			}
		}
		if (vec_distance(cbd->playerdata.pos, ent->pos) < 2)
		{
			ent->state = ENTITY_AGROED;
			ent->dir = vec_sub(cbd->playerdata.pos, ent->pos);
		}
		else if (vec_distance(ent->destinations[ent->current_dest], ent->pos) > 0.05)
		{
			ent->dir = vec_sub(ent->destinations[ent->current_dest], ent->pos);
		}
		vec_normalize(&ent->dir);
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