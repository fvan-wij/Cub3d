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
uint8_t	set_current_map(const char *file)
{
	char *temp;

	temp = ft_strrchr(file, '/');
	if (ft_strncmp(temp, "/dark_secret.cub", ft_strlen(temp)) == 0)
		return (LVL_DARK_SECRET);
	if (ft_strncmp(temp, "/the_bunker.cub", ft_strlen(temp)) == 0)
		return (LVL_THE_BUNKER);
	if (ft_strncmp(temp, "/rabbit_hole.cub", ft_strlen(temp)) == 0)
		return (LVL_RABBIT_HOLE);
	if (ft_strncmp(temp, "/snow_crash.cub", ft_strlen(temp)) == 0)
		return (LVL_SNOW_CRASH);
	if (ft_strncmp(temp, "/confrontation.cub", ft_strlen(temp)) == 0)
		return (LVL_CONFRONTATION);
	else
		return (LVL_UNKNOWN);
}
//
// t_map	*parse_map(int fd, t_map *mapdata)
// {
// 	int 	fd;
// 	t_map	*mapdata;
// 	t_valid	is;
//
// 	ft_memset(&is, false, sizeof(t_valid));
// 	mapdata = alloc_map();
// 	if (!mapdata)
// 		return (NULL);
// 	fd = open_map(file);
// 	if (fd < 0)
// 		return (NULL);
// 	mapdata = get_map_data(fd, mapdata, &is);
// 	if (!mapdata)
// 		return (NULL);
// 	mapdata->valid = validate_map_data(mapdata, &is);
// 	if (!mapdata->valid)
// 		return (NULL);
// 	mapdata->current_map = set_current_map(file);
// 	return (mapdata);
// }

/*
** Parses and validates all the necessary mapdata
** Needs:
** 		map file (path_to_map.cub)
** Returns:
**		t_map *mapdata
*/
// t_map	*cbd_parse_map(const char *file)
// {
// 	int 	fd;
// 	t_map	*mapdata;
// 	t_valid	is;
//
// 	ft_memset(&is, false, sizeof(t_valid));
// 	mapdata = alloc_map();
// 	if (!mapdata)
// 		return (NULL);
// 	fd = open_map(file);
// 	if (fd < 0)
// 		return (NULL);
// 	mapdata = get_map_data(fd, mapdata, &is);
// 	if (!mapdata)
// 		return (NULL);
// 	mapdata->valid = validate_map_data(mapdata, &is);
// 	if (!mapdata->valid)
// 		return (NULL);
// 	mapdata->current_map = set_current_map(file);
// 	return (mapdata);
// }
//

t_map	*parse_map_mandatory(const char *file, int fd, t_map *mapdata)
{
	t_valid	is;

	ft_memset(&is, false, sizeof(t_valid));
	mapdata = get_map_data(fd, mapdata, &is);
	if (!mapdata)
		return (NULL);
	mapdata->valid = validate_map_data(mapdata, &is);
	if (!mapdata->valid)
		return (NULL);
	mapdata->current_map = set_current_map(file);
	return (mapdata);
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

	mapdata = alloc_map();
	if (!mapdata)
		return (NULL);
	fd = open_map(file);
	if (fd < 0)
		return (NULL);
	if (is_bonus(fd))
		mapdata = parse_map_bonus(file, fd, mapdata);
	else
		mapdata = parse_map_mandatory(file, fd, mapdata);
	if (!mapdata)
		return (NULL);
	return (mapdata);
}
