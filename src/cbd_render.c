#include <cub3d.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void	resolve_fx(mlx_image_t *img, t_particle *particles, t_wall_destruction *config)
{
	int i = 0;
	int j = 0;

	while (i < MAX_WALL_PARTICLES)
	{
		if (config->b_timer)
		{
			particles[i].size.x -= 1.50;
			particles[i].size.y -= 1.50;
			particles[i].p.x = particles[i].p.x + (particles[i].dir.x) * 5;
			particles[i].p.y = particles[i].p.y + (particles[i].dir.y) * 60;
			if (particles[i].size.x <= 0 || particles[i].size.y <= 0)
				j++;
			draw_square_centered(img, color_rgba(50, 0, 0, 255), vec_to_int(particles[i].p), vec_to_int(particles[i].size));
		}
		else if (!config->b_timer)
			init_wall_destruction_fx(config);
		i++;
	}
	if (j == MAX_WALL_PARTICLES)
		config->b_timer = false;
}

void	screenshake(t_render *render)
{
	if (render->b_timer)
	{
		render->hud->img[HUD_OVERLAY]->enabled = true;
		// draw_radial_overlay(render->hud->img[HUD_OVERLAY], );
	}
	else
		render->hud->img[HUD_OVERLAY]->enabled = false;
}

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
	// draw_background(cbd->render.img, cbd->mapdata->floor.color, cbd->render.map_peak);
	draw_background(cbd->hud->img[HUD_OVERLAY], color_rgba(255, 0, 0, 0), cbd->render.map_peak);
	draw_gradient_bg(cbd->render.img, cbd->mapdata->floor.color, cbd->mapdata->ceiling.color);
	cast_rays(cbd->mapdata->cbd_map, &cbd->render, &cbd->playerdata);
	draw_walls(cbd->render, cbd->mapdata);
	render_entities(&cbd->render, cbd->mapdata->entities, &cbd->playerdata);
	draw_minimap(cbd->hud->img[HUD_MAP], cbd->playerdata.pos, cbd->mapdata->cbd_map, cbd->mapdata->width, cbd->mapdata->height);
	draw_hud(cbd->hud, cbd->playerdata.inv);
	draw_equipped_weapon(cbd->playerdata.inv);
	draw_particles(cbd->render.img, cbd->particles);
	draw_radial_overlay(cbd->render.hud->img[HUD_OVERLAY], cbd);
	resolve_fx(cbd->render.hud->img[HUD_OVERLAY], cbd->render.fx.particles, &cbd->render.fx);
	cbd->render.img = dither_image(cbd->render.img);
	// cbd->render.hud->img[HUD_OVERLAY] = dither_image(cbd->render.hud->img[HUD_OVERLAY]);
	// screenshake(&cbd->render);
}
