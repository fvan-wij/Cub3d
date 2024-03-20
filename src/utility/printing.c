#include <cub3d.h>

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

	ft_printf("[TEXTURES]\ntex_path[NO]: %s\ntex_path[SO]: %s\ntex_path[WE]: %s\ntex_path[EA]: %s\n", cub3d->mapdata->tex_path[NO],cub3d-> mapdata->tex_path[SO],cub3d->mapdata->tex_path[WE], cub3d->mapdata->tex_path[EA]);
	ft_printf("\n[COLORS]\nFloor color:  (%d, %d, %d)\nCeiling color: (%d, %d, %d)\n",cub3d->mapdata->floor.r, cub3d->mapdata->floor.g, cub3d->mapdata->floor.b, cub3d->mapdata->ceiling.r, cub3d->mapdata->ceiling.g, cub3d->mapdata->ceiling.b);
	if (cub3d->mapdata->cbd_map)
	{
		ft_printf("\n[MAP_CONTENT]\n");
		print_2d(cub3d->mapdata->cbd_map);
	}
	c = 'N';
	ft_printf("\n[MAP_DATA]\nStart_pos: (%d, %d, %c)\nMap-dimensions: (%d, %d)\n", cub3d->mapdata->start_pos.x, cub3d->mapdata->start_pos.y, c, cub3d->mapdata->width, cub3d->mapdata->height);

	if (cub3d->mapdata->valid)
		ft_printf("\n[VALID]\nYes\n");
	else
		ft_printf("\n[VALID]\nNo\n");
}

void	print_lst(t_lst_cont *head)
{
	t_lst_cont	*curr;
	size_t		i;

	curr = head;
	i = 0;
	while (curr->next != NULL)
	{
		if (curr->type == CONT_MAP)
		{
			ft_printf("[Node %d]:\n", i);
			print_2d(curr->map);
		}
		else if (curr->type == CONT_COLC)
		{
			ft_printf("[Node %d]:\n", i);
			ft_printf("Ceiling: (%d, %d, %d)\n", curr->color.r, curr->color.g, curr->color.b);
		}
		else if (curr->type == CONT_COLF)
		{
			ft_printf("[Node %d]:\n", i);
			ft_printf("Floor: (%d, %d, %d)\n", curr->color.r, curr->color.g, curr->color.b);
		}
		else if (curr->type == CONT_WALL)
		{
			ft_printf("[Node %d]:\n", i);
			ft_printf("Wall: %s\n", curr->tex_path);
		}
		else if (curr->type == CONT_ITEM)
		{
			ft_printf("[Node %d]:\n", i);
			ft_printf("Item: %s\n", curr->tex_path);
		}
		else if (curr->type == CONT_ENEMY)
		{
			ft_printf("[Node %d]:\n", i);
			ft_printf("Enemy: %s\n", curr->tex_path);
		}
		else if (curr->type == CONT_OBJECT)
		{
			ft_printf("[Node %d]:\n", i);
			ft_printf("Object: %s\n", curr->tex_path);
		}
		curr = curr->next;
		i++;
	}
	//Prints reverse
	// i--;
	// curr = curr->prev;
	// while (curr != NULL)
	// {
	// 	if (curr->type == CONT_MAP)
	// 	{
	// 		ft_printf("[Node %d]:\n", i);
	// 		print_2d(curr->map);
	// 	}
	// 	else if (curr->type == CONT_COLC)
	// 	{
	// 		ft_printf("[Node %d]:\n", i);
	// 		ft_printf("Ceiling: (%d, %d, %d)\n", curr->color.r, curr->color.g, curr->color.b);
	// 	}
	// 	else if (curr->type == CONT_COLF)
	// 	{
	// 		ft_printf("[Node %d]:\n", i);
	// 		ft_printf("Floor: (%d, %d, %d)\n", curr->color.r, curr->color.g, curr->color.b);
	// 	}
	// 	else if (curr->type == CONT_WALL)
	// 	{
	// 		ft_printf("[Node %d]:\n", i);
	// 		ft_printf("Wall: %s\n", curr->tex_path);
	// 	}
	// 	else if (curr->type == CONT_ITEM)
	// 	{
	// 		ft_printf("[Node %d]:\n", i);
	// 		ft_printf("Item: %s\n", curr->tex_path);
	// 	}
	// 	else if (curr->type == CONT_ENEMY)
	// 	{
	// 		ft_printf("[Node %d]:\n", i);
	// 		ft_printf("Enemy: %s\n", curr->tex_path);
	// 	}
	// 	else if (curr->type == CONT_OBJECT)
	// 	{
	// 		ft_printf("[Node %d]:\n", i);
	// 		ft_printf("Object: %s\n", curr->tex_path);
	// 	}
	// 	curr = curr->prev;
	// 	i--;
	// }
}
