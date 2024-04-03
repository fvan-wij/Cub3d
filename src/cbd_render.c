#include <cub3d.h>
#include <math.h>
#include <stdlib.h>

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
	draw_gradient_bg(cbd->render.img, cbd->mapdata->floor.color, cbd->mapdata->ceiling.color);
	cast_rays(cbd->mapdata->cbd_map, &cbd->render, &cbd->playerdata);
	draw_walls(cbd->render, cbd->mapdata);
	render_entities(&cbd->render, cbd->mapdata->entities, &cbd->playerdata);
	draw_minimap(cbd->hud->img[HUD_MAP], cbd->playerdata.pos, cbd->mapdata->cbd_map, cbd->mapdata->width, cbd->mapdata->height);
	draw_hud(cbd->hud, cbd->playerdata.inv);
	draw_equipped_weapon(cbd->playerdata.inv);
	draw_dust_particles(cbd->render.img, cbd->particles);
	cbd->render.img = dither_image(cbd->render.img);
	draw_blood_splat(cbd->render.hud->img[HUD_OVERLAY], cbd->render.splat, &cbd->render.fx);
	draw_blood_particles(cbd->render.sprite_img, cbd->render.blood, &cbd->render.fx);
	screenshake(&cbd->render);

	//Disabled the pulse due to performance impact

	// draw_radial_overlay(cbd->render.hud->img[HUD_PULSE], cbd);
	// cbd->render.hud->img[HUD_PULSE] = dither_image(cbd->render.hud->img[HUD_PULSE]);
}
