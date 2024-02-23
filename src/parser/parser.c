
#include <libft.h>
#include <cbd_parser.h>
#include <cbd_error.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

t_map	*cbd_parse_map(const char *file) 
{
	t_map	*mapdata;

	mapdata = init_map();
	if (!mapdata)
		return (NULL);
	mapdata = cbd_read_map(file, mapdata);
	if (!mapdata)
		return (NULL);

	return (mapdata);
}

