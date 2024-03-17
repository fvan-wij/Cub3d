#include <cbd_parser.h>
#include <cbd_error.h>
#include <libft.h>
#include <cub3d.h>
#include <stdbool.h>
#include <stdlib.h>

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

bool	wall_is_valid(t_map *mapdata, int i, int j)
{
	bool		err;
	const int 	lenW = ft_strlen(mapdata->raw_data[i]);
	const int 	lenH = ft_arrlen(mapdata->raw_data);

	err = true;
	if ((i < 0 || j < 0 || i >= lenH - 1 || j >= lenW - 1))
		return (false);
	if ((i == 0 || j == 0 || i == (lenH - 1) || j == (lenW - 1)) && !is_wall(mapdata->raw_data[i][j]))
		return (false);
	mapdata->raw_data[i][j] = FILL;
	if (err && (i + 1) <= (lenH - 1) && !is_wall(mapdata->raw_data[i + 1][j]) && mapdata->raw_data[i + 1][j] != FILL)
		err = wall_is_valid(mapdata, i + 1, j);
	if (err && (j + 1) <= (lenW - 1) && !is_wall(mapdata->raw_data[i][j + 1]) && mapdata->raw_data[i][j + 1] != FILL)
		err = wall_is_valid(mapdata, i, j + 1);
	if (err && (i - 1) >= 0 && !is_wall(mapdata->raw_data[i - 1][j]) && mapdata->raw_data[i - 1][j] != FILL)
		err = wall_is_valid(mapdata, i - 1, j);
	if (err && (j - 1) >= 0 && !is_wall(mapdata->raw_data[i][j - 1]) && mapdata->raw_data[i][j - 1] != FILL)
		err = wall_is_valid(mapdata, i, j - 1);
	return (err);
}

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
				return (false);
			if (j > mapdata->width)
				mapdata->width = j;
			j++;
		}
		i++;
	}
	mapdata->height = i;
	return (true);
}

bool	tex_size_is_valid(t_map *mapdata)
{
	int	i;

	i = 0;
	return (true);
	while (i < TEX_SIZE)
	{
		if (mapdata->tex[i]->width != 64 && mapdata->tex[i]->height != 64)
			return (false);
		i++;
	}
	return (true);
}

bool	validate_map_data(t_map *mapdata, t_valid *is)
{
	if (!start_is_valid(mapdata, is))
		return (cbd_error(ERR_INVALID_START), false);
	mapdata->cbd_map = get_map(mapdata);
	if (!mapdata->cbd_map)
		return (cbd_error(ERR_ALLOC), ft_del_2d(mapdata->raw_data), false);
	if (!wall_is_valid(mapdata, mapdata->start_pos.y, mapdata->start_pos.x))
		return (cbd_error(ERR_INVALID_WALL), ft_del_2d(mapdata->raw_data), false);
	if (!tex_size_is_valid(mapdata))
		return (cbd_error(ERR_TEX_SIZE), ft_del_2d(mapdata->raw_data), false);
	return (true);
}
