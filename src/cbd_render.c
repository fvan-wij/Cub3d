#include <cub3d.h>
#include <cbd_render.h>
#include <stdio.h>

int32_t	color(uint8_t r, uint8_t g, uint8_t b)
{
	t_rgba color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 255;
	return (color.color);
}

void	cbd_render(t_app *cbd)
{
	draw_background(cbd->game, color(151, 0, 0));
	cast_rays(cbd->mapdata->cbd_map, &cbd->playerdata);
	draw_walls(cbd, cbd->playerdata.rays);
	draw_map(cbd, cbd->mapdata->width, cbd->mapdata->height);
	draw_player(cbd->mapdata->cbd_map, cbd->hud->img[HUD_MAP], cbd->playerdata);
}
