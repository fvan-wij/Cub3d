#include <cbd_parser.h>
#include <cbd_error.h>
#include <cub3d.h>
#include <stdlib.h>

t_map	*alloc_map(void)
{
	t_map	*mapdata;

	mapdata = malloc(sizeof(t_map ));
	mapdata->tex_path 		= ft_calloc(sizeof(char *), TEX_SIZE);
	mapdata->cbd_map 		= NULL;
	mapdata->raw_data 		= NULL;
	mapdata->cbd_tex		= NULL;
	mapdata->start_pos.x 	= -1;
	mapdata->start_pos.y 	= -1;
	mapdata->valid 			= false;
	if (!mapdata || !mapdata->tex_path)
		return (cbd_error(ERR_ALLOC), NULL);
	return (mapdata);
}
