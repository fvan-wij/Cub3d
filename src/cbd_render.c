#include <cub3d.h>
#include <math.h>

/*
** Renders the game
	Needs:
	The image to render on
	The raycasting data
	The headbobbing data
	The map peak data
	The minimap data
	The HUD data
	The equipped weapon data
	The particles data

	Raycasting needs:
		The map
		The player position
		The player direction
		The player plane
	Each raycast itself needs:
		The Map
		A position
		A direction
		and returns: The raycast data
*/
void	cbd_render(t_app *cbd)
{
	// draw_gradient_bg(cbd->render.img,color_rgba(100, 10, 0, 255), color_rgba(0, 0, 0, 255));
	draw_background(cbd->render.img, color_rgba(100, 10, 0, 255), cbd->render.map_peak);
	cast_rays(cbd->mapdata->cbd_map, &cbd->render, &cbd->playerdata);
	draw_walls(cbd->render, cbd->mapdata);
	draw_minimap(cbd->hud->img[HUD_MAP], cbd->playerdata.pos, cbd->mapdata->cbd_map, cbd->mapdata->width, cbd->mapdata->height);
	draw_hud(cbd->hud, cbd->playerdata.inv);
	draw_equipped_weapon(cbd->playerdata.inv);
	draw_particles(cbd->render.img, cbd->particles);
	cbd->render.img = dither_image(cbd->render.img);
	// draw_radial_overlay(cbd->hud);
}
