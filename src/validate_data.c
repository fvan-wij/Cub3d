#include <cbd_parser.h>
#include <cbd_error.h>
#include <libft.h>
#include <cub3d.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/*
** Checks if the given character is the starting position.
** Needs:
**	char c (current character to check)
**	t_map *mapdata
**	t_valid (struct containing booleans of validated data)
** Returns:
**	true/false
*/
bool	is_player(char c, t_map *mapdata, t_valid *is)
{
	if (c == 'N')
	{
		mapdata->start_dir = vec_assign(0, -1);
		return (is->start[N] = true);
	}
	else if (c == 'E')
	{
		mapdata->start_dir = vec_assign(1, 0);
		return (is->start[E] = true);
	}
	else if (c == 'S')
	{
		mapdata->start_dir = vec_assign(0, 1);
		return (is->start[S] = true);
	}
	else if (c == 'W')
	{
		mapdata->start_dir = vec_assign(-1, 0);
		return (is->start[W] = true);
	}
	return (false);
}


/*
** Checks if there are duplicate start positions
** Needs:
**	t_map *mapdata
**	t_valid (struct containing booleans of validated data)
** Returns:
**	true/false
*/
bool	is_duplicate(t_valid *is, t_map *mapdata)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < DIR_SIZE)
	{
		if (is->start[i] == true)
			count++;
		i++;
	}
	if (count >= 1 && (mapdata->start_pos.x != -1 || mapdata->start_pos.y != -1))
		return (true);
	return (false);
}

/*
** Recursive funcction that checks if there are open walls (floodfill)
** Needs:
**	t_map *mapdata
**	int i (x location)
**	int j (y location)
** Returns:
**	true/false
*/
bool	wall_is_valid(t_map *mapdata, int i, int j)
{
	bool		err;
	const int 	len_w = ft_strlen(mapdata->raw_data[i]);
	const int 	len_h = ft_arrlen(mapdata->raw_data);

	err = true;
	if ((i < 0 || j < 0 || i >= len_h - 1 || j >= len_w - 1))
		return (false);
	if ((i == 0 || j == 0 || i == (len_h - 1) || j == (len_w - 1)) && !is_wall(mapdata->raw_data[i][j]))
		return (false);
	mapdata->raw_data[i][j] = FILL;
	if (err && (i + 1) <= (len_h - 1) && !is_wall(mapdata->raw_data[i + 1][j]) && mapdata->raw_data[i + 1][j] != FILL)
		err = wall_is_valid(mapdata, i + 1, j);
	if (err && (j + 1) <= (len_w - 1) && !is_wall(mapdata->raw_data[i][j + 1]) && mapdata->raw_data[i][j + 1] != FILL)
		err = wall_is_valid(mapdata, i, j + 1);
	if (err && (i - 1) >= 0 && !is_wall(mapdata->raw_data[i - 1][j]) && mapdata->raw_data[i - 1][j] != FILL)
		err = wall_is_valid(mapdata, i - 1, j);
	if (err && (j - 1) >= 0 && !is_wall(mapdata->raw_data[i][j - 1]) && mapdata->raw_data[i][j - 1] != FILL)
		err = wall_is_valid(mapdata, i, j - 1);
	return (err);
}

/*
** Recursive funcction that checks if there are open walls (floodfill)
** Needs:
**	t_map *mapdata
**	int i (x location)
**	int j (y location)
** Returns:
**	true/false
*/
bool	wall_is_valid_bonus(t_map *mapdata, int i, int j)
{
	bool		err;
	const int 	len_w = mapdata->width;
	const int 	len_h = mapdata->height;

	err = true;
	if ((i < 0 || j < 0 || i >= len_h - 1 || j >= len_w - 1))
		return (false);
	if ((i == 0 || j == 0 || i == (len_h - 1) || j == (len_w - 1)) && !is_wall_bonus(mapdata->raw_data[i][j]))
		return (false);
	mapdata->raw_data[i][j] = FILL;
	if (err && (i + 1) <= (len_h - 1) && !is_wall_bonus(mapdata->raw_data[i + 1][j]) && mapdata->raw_data[i + 1][j] != FILL)
		err = wall_is_valid(mapdata, i + 1, j);
	if (err && (j + 1) <= (len_w - 1) && !is_wall_bonus(mapdata->raw_data[i][j + 1]) && mapdata->raw_data[i][j + 1] != FILL)
		err = wall_is_valid(mapdata, i, j + 1);
	if (err && (i - 1) >= 0 && !is_wall_bonus(mapdata->raw_data[i - 1][j]) && mapdata->raw_data[i - 1][j] != FILL)
		err = wall_is_valid(mapdata, i - 1, j);
	if (err && (j - 1) >= 0 && !is_wall_bonus(mapdata->raw_data[i][j - 1]) && mapdata->raw_data[i][j - 1] != FILL)
		err = wall_is_valid(mapdata, i, j - 1);
	return (err);
}

/*
** Copies the validated raw_data
** Needs:
**	t_map *mapdata
** Returns:
**	copied map
*/
char	**get_map(t_map *mapdata)
{
	size_t	i;
	char	**cbd_map;

	i = 0;
	cbd_map = ft_calloc(sizeof(char *), (mapdata->height + 1));
	while (i < (size_t) mapdata->height)
	{
		cbd_map[i] = ft_calloc(sizeof(char), mapdata->width + 1);
		ft_strcpy(cbd_map[i], mapdata->raw_data[i]);
		i++;
	}
	return (cbd_map);
}

/*
** Checks if the start location is valid i.e. contains no duplicates
** Needs:
**	t_map *mapdata
**	t_valid *is (struct containing booleans with validated data)
** Returns:
**	true/false
*/
bool	start_is_valid(t_map *mapdata, t_valid *is)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (mapdata->raw_data[i])
	{
		j = 0;
		while (mapdata->raw_data[i][j])
		{
			if (is_player(mapdata->raw_data[i][j], mapdata, is) && !is_duplicate(is, mapdata))
			{
				mapdata->start_pos.x = j;
				mapdata->start_pos.y = i;
			}
			else if (is_player(mapdata->raw_data[i][j], mapdata, is) && is_duplicate(is, mapdata))
			{
				return (false);
			}
			if (j > mapdata->width)
				mapdata->width = j;
			j++;
		}
		i++;
	}
	mapdata->height = i;
	return (true);
}

/*
** Checks if texture is 64x64
** Needs:
**	t_map *mapdata
** Returns:
**	true/false
*/
bool	tex_size_is_valid(t_map *mapdata)
{
	int	i;

	i = 0;
	while (i < TEX_SIZE)
	{
		if (mapdata->walls.w_tex[i]->width != 64 && mapdata->walls.w_tex[i]->height != 64)
			return (false);
		i++;
	}
	return (true);
}

/*
** Validates the given map
** Checks if:
**	start is valid
**	walls are valid
**	texture size is valid
**
** Needs:
**	t_map *mapdata
** Returns:
**	true/false
*/
bool	validate_map_data(t_map *mapdata, t_valid *is)
{
	if (!start_is_valid(mapdata, is))
		return (cbd_error(ERR_INVALID_START), false);
	mapdata->cbd_map = get_map(mapdata);
	if (!mapdata->cbd_map)
		return (cbd_error(ERR_ALLOC), ft_del_2d(mapdata->raw_data), false);
	if (mapdata->is_bonus && !wall_is_valid_bonus(mapdata, mapdata->start_pos.y, mapdata->start_pos.x))
		return (cbd_error(ERR_INVALID_WALL), ft_del_2d(mapdata->raw_data), false);
	else if (!wall_is_valid(mapdata, mapdata->start_pos.y, mapdata->start_pos.x))
		return (cbd_error(ERR_INVALID_WALL), ft_del_2d(mapdata->raw_data), false);
	// if (!tex_size_is_valid(mapdata))
	// 	return (cbd_error(ERR_TEX_SIZE), ft_del_2d(mapdata->raw_data), false);
	return (true);
}
