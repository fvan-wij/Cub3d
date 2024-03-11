#include <cub3d.h>
#include <math.h>

void	cbd_render(t_app *cbd)
{
	draw_background(cbd->game, color(151, 0, 0));
	cast_rays(cbd->mapdata->cbd_map, &cbd->playerdata);
	draw_walls(cbd->game, cbd->playerdata.rays, cbd->playerdata.headbob, cbd->playerdata.map_peak);
	draw_minimap(cbd->hud->img[HUD_MAP], cbd->playerdata.pos, cbd->mapdata->cbd_map, cbd->mapdata->width, cbd->mapdata->height);
	draw_hud(cbd->hud, cbd->playerdata.inv);
	draw_equipped_weapon(cbd->playerdata.inv);
	draw_particles(cbd->game, cbd->particles);
}
