#include <cub3d.h>
#include <math.h>

int32_t	color(uint8_t r, uint8_t g, uint8_t b)
{
	t_rgba color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 255;
	return (color.color);
}

void	draw_hud(t_app *cbd, t_hud *hud)
{
	if (hud->equipped == WPN_FIST)
		hud->img[WPN_FIST]->enabled = true;
	else
		hud->img[WPN_FIST]->enabled = false;
	if (hud->equipped == WPN_MAP)
	{
		hud->img[WPN_MAP]->enabled = true;
		hud->img[HUD_MAP]->enabled = true;
	}
	else
	{
		hud->img[WPN_MAP]->enabled = false;
		hud->img[HUD_MAP]->enabled = false;
	}
	if (hud->equipped == WPN_CHAINSAW)
		hud->img[WPN_CHAINSAW]->enabled = true;
	else
		hud->img[WPN_CHAINSAW]->enabled = false;
	hud->img[hud->equipped]->instances[0].x = (cos(cbd->playerdata.headbob) * 2) + (WIDTH>>1) - (cbd->hud->img[hud->equipped]->width>>1);
}

void	cbd_render(t_app *cbd)
{
	draw_background(cbd->game, color(151, 0, 0));
	cast_rays(cbd->mapdata->cbd_map, &cbd->playerdata);
	draw_walls(cbd, cbd->playerdata.rays);
	draw_map(cbd, cbd->mapdata->width, cbd->mapdata->height);
	draw_player(cbd->mapdata->cbd_map, cbd->hud->img[HUD_MAP], cbd->playerdata);
	draw_hud(cbd, cbd->hud);
	draw_particles(cbd);

}
