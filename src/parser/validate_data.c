#include <cbd_parser.h>
#include <cbd_error.h>
#include <cub3d.h>

bool	is_player(char c, t_valid *is)
{
	if (c == 'N')
		return (is->start[N] = true);
	else if (c == 'E')
		return (is->start[E] = true);
	else if (c == 'S')
		return (is->start[S] = true);
	else if (c == 'W')
		return (is->start[W] = true);
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
	if (count > 1 && (mapdata->start_pos.x != -1 || mapdata->start_pos.y != -1))
		return (true);
	return (false);
}

bool	validate_map_data(t_map *mapdata, t_valid *is)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	mapdata->start_pos.x = -1;
	mapdata->start_pos.y = -1;
	while (mapdata->raw_data[i])
	{
		j = 0;
		while (mapdata->raw_data[i][j])
		{
			if (is_player(mapdata->raw_data[i][j], is) && !is_duplicate(is, mapdata))
			{
				mapdata->start_pos.x = j;
				mapdata->start_pos.y = i;
			}
			else
				return (cbd_error(ERR_INVALID_MAP), false);
			if (j > mapdata->width)
				mapdata->width = j;
			j++;
		}
		i++;
	}
	mapdata->height = i;
	return (true);
}
