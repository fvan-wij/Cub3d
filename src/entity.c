#include <cub3d.h>\

void	move_entities(t_entity *ent, t_app *cbd)
{

}

void	update_entity(t_entity *ent, t_app *cbd)
{
	if (ent->type == ENTITY_ENEMY)
	{
		if (vec_distance(cbd->playerdata.pos, ent->pos) < 10)
		{
			ent->dir = vec_sub(cbd->playerdata.pos, ent->pos);
		}
		else
		{
			ent->dir = vec_sub(ent->positions[ent->current_position], ent->pos);
			vec_normalize(&ent->dir);
		}
		if (vec_distance(ent->pos, ent->positions[ent->current_position]) < 1)
		{
			ent->current_position++;
			if ((ent->positions) + ent->current_position == NULL)
			{
				ent->current_position = 0;
			}
		}
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