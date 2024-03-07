#include <cub3d.h>
#include <cbd_render.h>

void	cbd_render(t_app *cbd)
{
	draw_background(cbd->game, OFF_WHITE);
	cast_rays(cbd->mapdata->cbd_map, &cbd->playerdata);
	draw_walls(cbd->game, cbd->playerdata.rays);
	draw_map(cbd, cbd->mapdata->width, cbd->mapdata->height);
	draw_player(cbd->mapdata->cbd_map, cbd->game, cbd->playerdata);
}

