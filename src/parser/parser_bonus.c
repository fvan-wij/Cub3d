#include <cbd_parser.h>
#include <cbd_error.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static bool	is_mapchar(char c)
{
	size_t		i;
	const char	map_content[20] = {"0123456789NWESeoi\t "};

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
	if (!line)
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

static char	*get_tex(char *temp)
{
	char *path;
	char *dup;

	path = ft_strchr(temp, '.');
	if (!path)
		return (NULL);
	else
	{
		dup = ft_strdup(path);
		if (!dup)
			return (cbd_error(ERR_ALLOC), NULL);
		return (dup);
	}
}

static t_rgba	get_col(char *temp)
{
	t_rgba color;

	color.color = 0;
	char **colors = ft_split(temp, ',');
	if (!colors)
	{
		cbd_error(ERR_ALLOC);
		return color;
	}
	if (ft_arrlen(colors) == 3)
	{
		color.r = (uint8_t) ft_atoi(colors[0]);
		color.g = (uint8_t) ft_atoi(colors[1]);
		color.b = (uint8_t) ft_atoi(colors[2]);
		color.a = (uint8_t) 255;
		ft_del_2d(colors);
	}
	return (color);
}

t_lst_cont	*append_node(t_lst_cont *head, char *line, uint8_t type)
{
	t_lst_cont *node;
	t_lst_cont *curr;

	node = ft_calloc(1, sizeof(t_lst_cont));
	if (!node)
		return (cbd_error(ERR_ALLOC), NULL);
	node->type = type;
	node->prev = NULL;
	node->next = NULL;
	if (type == CONT_WALL || type == CONT_ITEM || type == CONT_ENEMY)
	{
		node->tex_path = get_tex(line);
		ft_printf("Added WALL, ITEM or ENEMY TEXTURE node\n");
	}
	else if (type == CONT_COLC || type == CONT_COLF)
	{
		node->color = get_col(line);
		ft_printf("Added ceiling or floor color node\n");
	}
	else if (type == CONT_MAP)
	{
		if (!head)
			return (cbd_error(ERR_MAPCONTENT_SEQUENCE), NULL);
		curr = head;
		while (!curr->next)
		{
			if (curr->type == CONT_MAP)
			{
				curr->map = ft_add_2d(curr->map, line);
				ft_printf("Added mapcontent to CONT_MAP node\n");
				return (head);
			}
			curr = curr->next;
		}
		if (!curr->next)
		{
			node->map = ft_add_2d(node->map, line);
			ft_printf("Added mapcontent to new node\n");
		}
	}
	if (!head)
	{
		head = node;
		ft_printf("No head, creating new head!\n");
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

/*
** Reads the map, stores the given line in a node, returns linked list of all the elements
** Steps:
**	Initialize LL
**	Read line, identify element, store in node
**	If CONT_WALL
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
		if (type != CONT_UNKNOWN)
			head = append_node(head, line, type);
		else 
		{
			ft_printf("line: %s\n", line);
			return (cbd_error(ERR_UNKNOWN_ELEM), free(line), NULL);
		}
		free(line);
		line = get_next_line(fd);
	}
	exit(0);
	return (head);
}
