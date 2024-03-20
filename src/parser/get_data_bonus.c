#include "cbd_render.h"
#include <cbd_parser.h>
#include <cbd_error.h>
#include <cub3d.h>
#include <stdlib.h>

static bool	is_mapchar(char c)
{
	size_t		i;
	const char	map_content[20] = {"0123456789NWES\t "};

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

t_lst_cont *get_node(t_lst_cont *head, uint8_t type)
{
	t_lst_cont *curr;

	curr = head;
	while (curr->next != NULL)
	{
		if (curr->type == type)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

t_lst_cont	*append_node(t_lst_cont *head, char *line, uint8_t type)
{
	t_lst_cont *node;
	t_lst_cont *curr;

	if (type == CONT_UNKNOWN)
		return (head);
	node = ft_calloc(1, sizeof(t_lst_cont));
	if (!node)
		return (cbd_error(ERR_ALLOC), NULL);
	node->type = type;
	node->prev = NULL;
	node->next = NULL;
	if (type == CONT_WALL || type == CONT_ITEM || type == CONT_ENEMY || type == CONT_OBJECT)
		node->tex_path = get_texpath(&line[2]);
	else if (type == CONT_COLC || type == CONT_COLF)
		node->color = get_col(&line[2]);
	else if (type == CONT_MAP)
	{
		if (!head)
			return (cbd_error(ERR_MAPCONTENT_SEQUENCE), NULL);
		curr = head;
		while (curr->next != NULL)
		{
			if (curr->type == CONT_MAP)
			{
				curr->map = ft_add_2d(curr->map, line);
				free(node);
				return (head);
			}
			curr = curr->next;
		}
		if (curr->next == NULL && curr->type != CONT_MAP)
			node->map = ft_add_2d(node->map, line);
		else if (curr->type == CONT_MAP)
			curr->map = ft_add_2d(curr->map, line);
	}
	if (!head)
	{
		head = node;
		return (head);
	}
	else
	{
		curr = head;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = node;
		node->prev = curr;
		return (head);
	}
}

size_t count_nodes(t_lst_cont *head, uint8_t type)
{
	t_lst_cont *temp;
	size_t		i;

	temp = head;
	i = 0;
	while (temp->next != NULL)
	{
		if (temp->type == type)
			i++;
		temp = temp->next;
	}
	return (i);
}

t_map	*copy_data(t_lst_cont *head, t_map *mapdata)
{
	uint8_t wall_count;
	uint8_t entity_count;
	t_lst_cont *temp;

	temp = head;
	wall_count = count_nodes(head, CONT_WALL);
	entity_count = count_nodes(head, CONT_ENEMY);
	entity_count += count_nodes(head, CONT_ITEM);
	entity_count += count_nodes(head, CONT_OBJECT);
	if (mapdata->tex)
		free(mapdata->tex);
	mapdata = alloc_map(wall_count);
	if (!mapdata)
		return (NULL);
	mapdata->entities = malloc(sizeof(t_entity *) * entity_count);
	while (temp->next != NULL)
	{
		if (temp->type == CONT_MAP)
			mapdata->raw_data = temp->map;
		if (temp->type == CONT_COLC)
			mapdata->ceiling = temp->color;
		if (temp->type == CONT_COLF)
			mapdata->floor = temp->color;
		temp = temp->next;
	}
	return (mapdata);
}

/*
** Reads the map, stores the given line in a node, returns linked list of all the elements
** Steps:
**	Initialize lst
**	Read line, identify element, store in node
*/
t_lst_cont	*get_map_data_bonus(int fd, char *line)
{
	t_lst_cont *head;
	uint8_t		type;

	head = NULL;
	line = get_next_line(fd);
	while (line)
	{
		type = identify_element(line);	
		head = append_node(head, line, type);
		free(line);
		line = get_next_line(fd);
	}
	print_lst(head);
	return (head);
}
