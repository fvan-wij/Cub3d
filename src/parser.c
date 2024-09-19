#include <libft.h>
#include <cbd_parser.h>
#include <cbd_error.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/*
** Opens map and returns the fd
** Needs:
** 		map file (path_to_map.cub)
** Returns:
**		int fd
*/
static int	open_map(const char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (cbd_error(ERR_OPEN), fd);
	return (fd);
}


/*
** Checks the file name of the map, and returns the LVL_ENUM
** Needs:
** 		map file (path_to_map.cub)
** Returns:
**		enum LVL_...
*/
uint8_t	set_current_map(const char *file, t_level *level)
{
	char *temp;

	temp = ft_strrchr(file, '/');
	if (ft_strncmp(temp, "/dark_secret.cub", ft_strlen(temp)) == 0)
	{
		*level = LVL_DARK_SECRET;
		return (LVL_DARK_SECRET);
	}
	if (ft_strncmp(temp, "/the_bunker.cub", ft_strlen(temp)) == 0)
	{
		*level = LVL_THE_BUNKER;
		return (LVL_THE_BUNKER);
	}
	if (ft_strncmp(temp, "/rabbit_hole.cub", ft_strlen(temp)) == 0)
	{
		*level = LVL_RABBIT_HOLE;
		return (LVL_RABBIT_HOLE);
	}
	if (ft_strncmp(temp, "/snow_crash.cub", ft_strlen(temp)) == 0)
	{
		*level = LVL_SNOW_CRASH;
		return (LVL_SNOW_CRASH);
	}
	if (ft_strncmp(temp, "/confrontation.cub", ft_strlen(temp)) == 0)
	{
		*level = LVL_CONFRONTATION;
		return (LVL_CONFRONTATION);
	}
	else
	{
		*level = LVL_UNKNOWN;
		return (LVL_UNKNOWN);
	}
}

/*
** Parses and validates all the necessary mapdata
** Needs:
** 		map file (path_to_map.cub)
** Returns:
**		t_map *mapdata
*/
t_map	*cbd_parse_map(const char *file)
{
	int 	fd;
	t_map	*mapdata;
	t_valid	is;

	ft_memset(&is, false, sizeof(t_valid));
	fd = open_map(file);
	if (fd < 0)
		return (NULL);
	mapdata = get_map_data(fd, &is);
	if (!mapdata)
		return (NULL);
	mapdata->valid = validate_map_data(mapdata, &is);
	if (!mapdata->valid)
		return (NULL);
	mapdata->current_map = set_current_map(file, &mapdata->current_map);
	return (mapdata);
}
