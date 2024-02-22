#include <cbd_parser.h>
#include <cbd_error.h>
#include <cub3d.h>
#include <stdlib.h>

bool init_map(t_app *cub3d)
{
	cub3d->mapdata = malloc(sizeof(t_map *));
	cub3d->mapdata->cbd_tex = malloc(sizeof(char *) * TEX_SIZE);
	if (!cub3d->mapdata || !cub3d->mapdata->cbd_tex)
		return (cbd_error(ERR_ALLOC), false);
	return (true);
}
