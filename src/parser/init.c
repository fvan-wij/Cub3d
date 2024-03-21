#include <cbd_parser.h>
#include <cbd_error.h>
#include <cub3d.h>
#include <stdlib.h>

t_map	*alloc_map(void)
{
	t_map	*mapdata;

	mapdata = malloc(sizeof(t_map));
	mapdata->tex_path 		= ft_calloc(sizeof(char *), TEX_SIZE + 1);
	mapdata->tex			= NULL;
	mapdata->cbd_map 		= NULL;
	mapdata->raw_data 		= NULL;
	mapdata->start_pos.x 	= -1;
	mapdata->start_pos.y 	= -1;
	mapdata->valid 			= false;
	mapdata->is_bonus		= false;
	mapdata->n_tex			= TEX_SIZE;
	if (!mapdata || !mapdata->tex_path)
		return (cbd_error(ERR_ALLOC), NULL);
	return (mapdata);
}

t_map	*alloc_map_bonus(void)
{
	t_map	*mapdata;

	mapdata = ft_calloc(1, sizeof(t_map));
	mapdata->start_pos.x 	= -1;
	mapdata->start_pos.y 	= -1;
	mapdata->valid 			= false;
	mapdata->is_bonus		= true;
	if (!mapdata)
		return (cbd_error(ERR_ALLOC), NULL);
	return (mapdata);
}
