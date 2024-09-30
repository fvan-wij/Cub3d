#include <cub3d.h>
#include <stdlib.h>

static void	fade_blood(mlx_image_t *img)
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

#include <stdio.h>
void	draw_blood_splat(mlx_image_t *img, t_particle *splat, t_fx *fx)
{
	int i = 0;
	int j = 0;

	if (!fx->splat)
	{
		fade_blood(img);
		return (init_blood_splat(splat));
	}
	while (i < MAX_BLOOD_PARTICLES)
	{
		t_particle *particle = &splat[i];
		if (fx->splat)
		{
			particle->size.x -= 0.75;
			particle->size.y -= 0.75;
			particle->p.x = particle->p.x + (particle->dir.x) * 5;
			particle->p.y = particle->p.y + (particle->dir.y) * 20;
			if (particle->size.x <= 0 || particle->size.y <= 0)
				j++;
			draw_square_centered(img, color_rgba(125, 0, 0, 255), vec_to_int(particle->p), vec_to_int(particle->size));
		}
		else
			break ;
		i++;
	}
	if (j == MAX_BLOOD_PARTICLES)
		fx->splat = false;
}

void	draw_blood_particles(mlx_image_t *img, t_particle *blood_particle, t_fx *fx)
{
	int i = 0;
	int j = 0;

	while (i < MAX_BLOOD_PARTICLES)
	{
		t_particle *particle = &blood_particle[i];
		if (fx->blood)
		{
			particle->size.x -= 10.0;
			particle->size.y -= 10.0;
			particle->p.x = particle->p.x + (particle->dir.x) * 10;
			particle->p.y = particle->p.y + (particle->dir.y) * 10;
			if (particle->size.x <= 0 || particle->size.y <= 0)
				j++;
			draw_square_centered(img, color_rgba(rand(), 0, 0, 255), vec_to_int(particle->p), vec_to_int(particle->size));
		}
		else
			break ;
		i++;
	}
	if (j == MAX_BLOOD_PARTICLES)
	{
		fx->blood = false;
		init_blood_particles(blood_particle);
	}
}

