#include "cbd_render.h"
#include <cbd_parser.h>
#include <cbd_error.h>
#include <cub3d.h>
#include <stdlib.h>
#include <stdio.h>

static bool	is_mapchar(char c)
{
	size_t		i;
	const char	map_content[20] = {"0123456789NWES=-_\t "};

	i = 0;
	while (map_content[i])
	{
		if (c == map_content[i] || is_wall(c))
			return (true);
		i++;
	}
	return (false);
}

bool	is_mapcontent(char *line)
{
	size_t	i;

	i = 0;
	if (!line || line[0] == '\n')
		return (false);
	while (line[i])
	{
		if (is_mapchar(line[i]))
			i++;
		else
			break;
	}
	if (line[i] == '\n')
		return (true);
	return (false);
}

/*
** Identifies the element of the given line
**	returns enum CONT_...
*/
uint8_t	identify_element(char *line)
{
	if (is_mapcontent(line))
		return (CONT_MAP);
	else if (line[0] == 'W' && (line[1] == '=' || line[1] == '-' || line[1] == '_'))
		return (CONT_CWALL);
	else if (line[0] == 'W')
		return (CONT_WALL);
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (CONT_COLF);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (CONT_COLC);
	else if (ft_strncmp(line, "e ", 2) == 0)
		return (CONT_ENEMY);
	else if (ft_strncmp(line, "o ", 2) == 0)
		return (CONT_OBJECT);
	else if (ft_strncmp(line, "i ", 2) == 0)
		return (CONT_ITEM);
	else
	 	return (CONT_UNKNOWN);
}

t_animation	load_animation(mlx_texture_t *texture, uint32_t frame_width, uint32_t frame_height)
{
	t_animation	animation;

	if (frame_width != texture->width)
		animation.n_frames = texture->width / frame_width;
	else
	 	animation.n_frames = 1;
	if (frame_height != texture->height)
		animation.n_animations = texture->height / frame_height;
	else
	 	animation.n_animations = 1;
	animation.enabled = true;
	animation.current_frame = 0;
	animation.current_animation = 0;
	animation.timer = 0;
	animation.duration = 0.1;
	animation.loop = true;
	// printf("Loaded animation with %d frames and %d animations\n", animation.n_frames, animation.n_animations);
	return (animation);
}

/*
** Extracts entity data from the given line and stores it in the t_entity list
**
*/
t_entity *append_entity(t_entity *entities, char *line, uint8_t type)
{
	t_entity 	*new_entity;
	t_entity	*curr;
	char		**temp;
	char 		p[2];
	size_t 		i;
	size_t		j;

	new_entity = ft_calloc(1, sizeof(t_entity));
	if (!new_entity)
		return (cbd_error(ERR_ALLOC), NULL);
	temp = ft_split(line, ' ');
	if (!temp)
		return (cbd_error(ERR_ALLOC), NULL);
	new_entity->enabled = true;
	new_entity->name = ft_strdup(temp[1]);
	new_entity->texture = mlx_load_png(temp[2]);
	new_entity->frame_width = ft_atoi(temp[3]);
	new_entity->frame_height = ft_atoi(temp[4]);
	new_entity->animation = load_animation(new_entity->texture, new_entity->frame_width, new_entity->frame_height);
	if (type == CONT_ENEMY)
	{
		new_entity->speed = (float) ft_atoi(temp[5]) + 0.5f;
		new_entity->health = (float) ft_atoi(temp[6]);
		new_entity->damage = (float) ft_atoi(temp[7]);
		new_entity->type = ENTITY_ENEMY;
		const size_t n = ft_arrlen(&temp[8]);
		new_entity->destinations = ft_calloc(n + 1, sizeof(t_vec2d));
		new_entity->n_dest = n;
		i = 8;
		j = 0;
		while (temp[i] && j < n)
		{
			char **temp2 = ft_split(temp[i], ',');
			new_entity->destinations[j].x = ft_atoi(temp2[0]) + .5;
			new_entity->destinations[j].y = ft_atoi(temp2[1]) + .5;
			ft_del_2d(temp2);
			i++;
			j++;
		}
		new_entity->pos.x = new_entity->destinations[0].x + .5;
		new_entity->pos.y = new_entity->destinations[0].y + .5;
	}
	else if (type == CONT_OBJECT || type == CONT_ITEM)
	{
		if (type == CONT_OBJECT)
			new_entity->type = ENTITY_DECOR;
		else
			new_entity->type = ENTITY_ITEM;
		i = 5;
		ft_strlcpy(p, temp[i], 3);
		new_entity->pos.x = (float) ft_atoi(p) + 0.5;
		ft_strlcpy(p, &temp[i][3], 3);
		new_entity->pos.y = (float) ft_atoi(p) + 0.5;
	}
	if (!entities)
		return (ft_del_2d(temp), new_entity);
	else
	{
		curr = entities;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = new_entity;
		return (ft_del_2d(temp), entities);
	}
}

/*
** Reads the map, stores the given line in a node, returns linked list of all the elements
** Steps:
**	Initialize lst
**	Read line, identify element, store in node
*/
t_map	*get_map_data_bonus(int fd, char *line)
{
	uint8_t		type;
	t_map		*mapdata;
	size_t		i;

	mapdata = alloc_map_bonus();
	if (!mapdata)
		return (NULL);
	free(line);
	line = get_next_line(fd);
	while (line)
	{
		type = identify_element(line);
		if (type == CONT_WALL)
			mapdata->walls.w_path[(unsigned char)line[1]] = ft_strtrim(&line[3], "\n");
		else if (type == CONT_CWALL)
			mapdata->walls.w_path[(unsigned char)line[1]] = ft_strtrim(&line[3], "\n");
		else if (type == CONT_MAP)
			mapdata->raw_data = ft_add_2d(mapdata->raw_data, line);
		else if (type == CONT_COLC)
			mapdata->ceiling = get_col(&line[2]);
		else if (type == CONT_COLF)
			mapdata->floor = get_col(&line[2]);
		else if (type == CONT_ENEMY || type == CONT_ITEM || type == CONT_OBJECT)
			mapdata->entities = append_entity(mapdata->entities, line, type);
		free(line);
		line = get_next_line(fd);
	}
	// i loops over the characters inside of the path jump table, if any of the characters (indexes) have a path string, load the corresponding texture and put it in the same index in the wall texture jump table
	i = 0;
	while (i < 255)
	{
		if (mapdata->walls.w_path[(unsigned char)i])
		{
			mapdata->walls.w_tex[(unsigned char)i] = mlx_load_png(mapdata->walls.w_path[(unsigned char)i]);
			if (!mapdata->walls.w_tex[(unsigned char)i])
				return (NULL);
		}
		i++;
	}
	return (mapdata);
}
