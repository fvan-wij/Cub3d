#include <cub3d.h>
#include <stdio.h>
#include <math.h>

void	print_2d(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_printf("%s", str[i]);
		i++;
	}
}

void	print_debug_info(t_app *cub3d)
{
	char c;

	if (cub3d->mapdata->is_bonus)
	{
		printf("[TEXTURES]\n");
		size_t i = 0;
		while (i < 255)
		{
			if (cub3d->mapdata->walls.w_path[i])
				printf("W%zu: %s\n",i + 1, cub3d->mapdata->walls.w_path[i]);
			i++;
		}
		i = 0;
		// while (i < cub3d->mapdata->walls.n_cw && cub3d->mapdata->walls.cw_path[i])
		// {
		// 	printf("W%zu: %s\n",i + 1, cub3d->mapdata->walls.cw_path[i]);
		// 	i++;
		// }
	}
	else
		ft_printf("[TEXTURES]\ntex_path[NO]: %s\ntex_path[SO]: %s\ntex_path[WE]: %s\ntex_path[EA]: %s\n", cub3d->mapdata->walls.w_path[NO],cub3d-> mapdata->walls.w_path[SO],cub3d->mapdata->walls.w_path[WE], cub3d->mapdata->walls.w_path[EA]);
	ft_printf("\n[COLORS]\nFloor color:  (%d, %d, %d)\nCeiling color: (%d, %d, %d)\n",cub3d->mapdata->floor.r, cub3d->mapdata->floor.g, cub3d->mapdata->floor.b, cub3d->mapdata->ceiling.r, cub3d->mapdata->ceiling.g, cub3d->mapdata->ceiling.b);
	if (cub3d->mapdata->cbd_map)
	{
		ft_printf("\n[MAP_CONTENT]\n");
		print_2d(cub3d->mapdata->cbd_map);
	}
	c = 'N';
	ft_printf("\n[MAP_DATA]\nStart_pos: (%d, %d, %c)\nMap-dimensions: (%d, %d)\n", cub3d->mapdata->start_pos.x, cub3d->mapdata->start_pos.y, c, cub3d->mapdata->width, cub3d->mapdata->height);

	if (cub3d->mapdata->valid)
		ft_printf("\n[VALID]\nYes\n\n");
	else
		ft_printf("\n[VALID]\nNo\n\n");
	print_entities(cub3d->mapdata->entities);
}

void	print_entities(t_entity *head)
{
	t_entity	*curr;
	size_t		i;

	curr = head;
	i = 0;
	printf("[ENTITIES]\n");
	while (curr)
	{
		if (curr->type == ENTITY_ITEM)
		{
			printf("[Item]: (%d, %d)\n", (int)curr->pos.x, (int)curr->pos.y);
		}
		else if (curr->type == ENTITY_ENEMY)
		{
			printf("[Enemy]: Pos(%d, %d), ", (int)curr->pos.x, (int)curr->pos.y);
			printf("Speed(%f), ", curr->speed);
			printf("Health(%d), ", curr->health);
			printf("Damage(%d)\n", curr->damage);
			size_t j = 0;
			printf("Patrol points: ");
			while ((int)curr->destinations[j].x != 0 || (int)curr->destinations[j].y != 0)
			{
				printf("->(%d, %d) ", (int)curr->destinations[j].x, (int)curr->destinations[j].y);
				j++;
			}
			printf("\n");
		}
		else if (curr->type == ENTITY_DECOR)
		{
			printf("[Decor]: (%d, %d)\n", (int)curr->pos.x, (int)curr->pos.y);
		}
		curr = curr->next;
		i++;
	}
}
