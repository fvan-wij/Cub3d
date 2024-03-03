#include <libft.h>
#include <cbd_parser.h>
#include <cbd_error.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static int	open_map(const char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (cbd_error(ERR_OPEN), fd);
	return (fd);
}

t_map	*cbd_parse_map(const char *file)
{
	int 	fd;
	t_map	*mapdata;
	t_valid	is;

	ft_memset(&is, false, sizeof(t_valid));
	mapdata = alloc_map();
	if (!mapdata)
		return (NULL);
	fd = open_map(file);
	if (fd < 0)
		return (NULL);
	mapdata = get_map_data(fd, mapdata, &is);
	if (!mapdata)
		return (NULL);
	mapdata->valid = validate_map_data(mapdata, &is);
	if (!mapdata->valid)
		return (NULL);

	return (mapdata);
}

