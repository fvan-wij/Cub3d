#include <cbd_parser.h>
#include <cbd_error.h>
#include <cub3d.h>
#include <stdlib.h>

t_map	*alloc_map(void)
{
	t_map	*mapdata;

	mapdata = malloc(sizeof(t_map ));
	mapdata->cbd_tex = ft_calloc(sizeof(char *), TEX_SIZE);
	if (!mapdata || !mapdata->cbd_tex)
		return (cbd_error(ERR_ALLOC), NULL);
	return (mapdata);
}
