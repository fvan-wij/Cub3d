#include <cub3d.h>
#include <stdio.h>

void	move_entities(t_entity *ent, t_app *cbd)
{
	if (ent->type == ENTITY_ENEMY)
	{
		ent->pos = vec_add(ent->pos, vec_mult(ent->dir, ent->speed * cbd->mlx->delta_time));
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
			printf("Changing current position to: %i\n", ent->current_dest);
			printf("New position: x:%f y:%f\n", ent->destinations[ent->current_dest].x, ent->destinations[ent->current_dest].y);
		}
		if (vec_distance(cbd->playerdata.pos, ent->pos) < 2)
		{
			ent->dir = vec_sub(cbd->playerdata.pos, ent->pos);
		}
		else
		{
			ent->dir = vec_sub(ent->destinations[ent->current_dest], ent->pos);
		}
		vec_normalize(&ent->dir);
		printf("Current position: x:%f y:%f\n Dir: x:%f y:%f\n", ent->pos.x, ent->pos.y, ent->dir.x, ent->dir.y);
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