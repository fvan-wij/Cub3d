#include <cbd_parser.h>
#include <cbd_error.h>

t_map	*parse_map_bonus(const char *file, int fd, t_map *mapdata)
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
