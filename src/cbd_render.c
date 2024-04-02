#include <cub3d.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void	fade_blood(mlx_image_t *img)
{
	uint32_t x;
	uint32_t y;
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			int index = (x + y * img->width) * 4;
				if (img->pixels[index + 3] >= 10)
					img->pixels[index + 3] -= 0.5;
			x++;
		}
		y++;
	}
}

void	draw_blood_splat(mlx_image_t *img, t_blood *splat)
{
	int i = 0;
	int j = 0;

	if (!splat->b_timer)
	{
		fade_blood(img);
		return (init_blood_splat(splat));
	}
	while (i < MAX_BLOOD_PARTICLES)
	{
		t_particle *particle = &splat->particles[i];
		if (splat->b_timer)
		{
			particle->size.x -= 1.25;
			particle->size.y -= 1.25;
			particle->p.x = particle->p.x + (particle->dir.x) * 5;
			particle->p.y = particle->p.y + (particle->dir.y) * 20;
			if (particle->size.x <= 0 || particle->size.y <= 0)
				j++;
			draw_square_centered(img, color_rgba(125, 0, 0, 255), vec_to_int(particle->p), vec_to_int(particle->size));
		}
		i++;
	}
	if (j == MAX_BLOOD_PARTICLES)
	{
		splat->b_timer = false;
	}
}

void	draw_blood_particles(mlx_image_t *img, t_blood *particles)
{
	int i = 0;
	int j = 0;

	if (!particles->b_timer)
	{
		return (init_blood_particles(particles));
	}
	while (i < MAX_BLOOD_PARTICLES)
	{
		t_particle *particle = &particles->particles[i];
		if (particles->b_timer)
		{
			particle->size.x -= 1.25;
			particle->size.y -= 1.25;
			particle->p.x = particle->p.x + (particle->dir.x) * 10;
			particle->p.y = particle->p.y + (particle->dir.y) * 10;
			if (particle->size.x <= 0 || particle->size.y <= 0)
				j++;
			draw_square_centered(img, color_rgba(90, 0, 0, 255), vec_to_int(particle->p), vec_to_int(particle->size));
		}
		i++;
	}
	// if (j == MAX_BLOOD_PARTICLES)
	// 	particles->b_timer = false;
	// if (particles->timer < 0)
	// {
	// 	particles->b_timer = false;
	// 	particles->timer = 300;
	// }
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
	draw_background(cbd->render.hud->img[HUD_CRT], color_rgba(125, 0, 0, 0), 0);
	draw_gradient_bg(cbd->render.img, cbd->mapdata->floor.color, cbd->mapdata->ceiling.color);
	cast_rays(cbd->mapdata->cbd_map, &cbd->render, &cbd->playerdata);
	draw_walls(cbd->render, cbd->mapdata);
	render_entities(&cbd->render, cbd->mapdata->entities, &cbd->playerdata);
	draw_minimap(cbd->hud->img[HUD_MAP], cbd->playerdata.pos, cbd->mapdata->cbd_map, cbd->mapdata->width, cbd->mapdata->height);
	draw_hud(cbd->hud, cbd->playerdata.inv);
	draw_equipped_weapon(cbd->playerdata.inv);
	draw_dust_particles(cbd->render.img, cbd->particles);
	cbd->render.img = dither_image(cbd->render.img);
	screenshake(&cbd->render, cbd);
	draw_blood_splat(cbd->render.hud->img[HUD_OVERLAY], &cbd->render.splat);
	draw_blood_particles(cbd->render.hud->img[HUD_CRT], &cbd->render.particles);
	draw_radial_overlay(cbd->render.hud->img[HUD_PULSE], cbd);
	cbd->render.hud->img[HUD_PULSE] = dither_image(cbd->render.hud->img[HUD_PULSE]);
}
