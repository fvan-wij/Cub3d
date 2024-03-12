#include <cub3d.h>
#include <cbd_error.h>
#include <libft.h>
#include <MLX42.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void	draw_hud(t_hud *hud, t_inventory *inv)
{
	if (inv->equipped == WPN_MAP)
		hud->img[HUD_MAP]->enabled = true;
	else
		hud->img[HUD_MAP]->enabled = false;
}

void	draw_equipped_weapon(t_inventory *inv)
{
	if (inv->equipped == WPN_FIST && inv->weapons[WPN_FIST].fire_animation->loop != true)
		inv->weapons[WPN_FIST].img->enabled = true;
	else
		inv->weapons[WPN_FIST].img->enabled = false;
	if (inv->equipped == WPN_CHAINSAW && inv->weapons[WPN_CHAINSAW].fire_animation->loop != true)
		inv->weapons[WPN_CHAINSAW].img->enabled = true;
	else
		inv->weapons[WPN_CHAINSAW].img->enabled = false;
	if (inv->equipped == WPN_MAP && inv->weapons[WPN_CHAINSAW].fire_animation->loop != true)
		inv->weapons[WPN_MAP].img->enabled = true;
	else
		inv->weapons[WPN_MAP].img->enabled = false;
}

void	draw_background(mlx_image_t *img, int32_t color)
{
	const t_vec2i init = {0, 0};
	const t_vec2i screen = {WIDTH, HEIGHT};

	draw_square(img, color, init, screen);
}

void	draw_player(mlx_image_t *img)
{
	const float r = (TILESIZE)>>4;
	draw_circle(img, color(255, 255, 255), vec2i_assign((float) (img->width/2), (float)(img->height/2)), r);
}

void	draw_minimap(mlx_image_t *hud_map, t_vec2d pos, char **map, int width, int height)
{
	draw_noise_square(hud_map, vec2i_assign(0, 0), vec2i_assign(hud_map->width, hud_map->height));
	t_vec2d	offset;
	t_vec2i loc;

	float tileH = (float) MINIMAP_HEIGHT / 16;
	t_vec2i size;
	int y;
	int	x;
	y = 0;

	offset.x = -(((pos.x / MINIMAP_WIDTH) * MINIMAP_WIDTH) * tileH) + (MINIMAP_WIDTH>>1);
	offset.y = -(((pos.y / MINIMAP_HEIGHT) * MINIMAP_HEIGHT) * tileH) + (MINIMAP_HEIGHT>>1);
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			loc.x = (x * tileH) + offset.x;
			loc.y = (y * tileH) + offset.y;
			size.x = tileH + 1;
			size.y = tileH + 1;
			if (map[y][x] == '0' && loc.x < MINIMAP_WIDTH && loc.y < MINIMAP_HEIGHT && loc.x > 0 && loc.y > 0)
				draw_square(hud_map, color_rgba(0, 0, 0, 50), loc, size);
			x++;
		}
		y++;
	}
	draw_player(hud_map);
}


void	draw_map(char **map, t_hud *hud, int width, int height)
{
	t_vec2i p;
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			p.x = (j * TILESIZE);
			p.y = (i * TILESIZE);
			if (p.x <= WIDTH && p.x >= 0 && p.y <= HEIGHT && p.y >= 0)
			{
				t_vec2i size = {TILESIZE, TILESIZE};
				if (map[i][j] == '1')
					draw_square(hud->img[HUD_MAP], color(200, 200, 200), p, size);
				else
					draw_square(hud->img[HUD_MAP], OFF_WHITE, p, size);
			}
			j++;
		}
		i++;
	}
}

/* Takes a normalized x and y and returns the relative pixel color within the texture
*/
uint32_t	get_texture_pixel(mlx_texture_t *tex, double x, double y)
{
	t_rgba	color;
	int 	index;

	(void)y;
	// index = (int)((int)(x * tex->width) + (int)(y * tex->height * tex->width)) * tex->bytes_per_pixel;
	index = (int)(x * tex->width) * tex->bytes_per_pixel;
	// printf("bytes_per_pixel: %d\n", tex->bytes_per_pixel);
	// printf("index: %d\n", index);
	color.r = tex->pixels[(index)];
	color.g = tex->pixels[(index) + 1];
	color.b = tex->pixels[(index) + 2];
	color.a = tex->pixels[(index) + 3];
	return (color.color);
}

void	draw_wall_strip(t_render render, int x, mlx_texture_t *tex)
{
	int wl_height = (int)(HEIGHT / render.rays[x].wall_dist);
	int y;
	int draw_start;
	int draw_end;
	double	wall_x;
	double	wall_y;

	printf("intersection: %f, %f\n", render.rays[x].intersection.x, render.rays[x].intersection.y);
	if (render.rays[x].side == 0)
		wall_x = render.rays[x].intersection.y - floor(render.rays[x].intersection.y);
	else
		wall_x = render.rays[x].intersection.x - floor(render.rays[x].intersection.x);
	printf("wall_x: %f\n", wall_x);
	draw_start = (-wl_height / 2) + (HEIGHT / 2);
	draw_end = draw_start + wl_height;
	draw_start += (sin(render.headbob) * 10) + render.map_peak;
	draw_end += (sin(render.headbob) * 10) + render.map_peak;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	y = 0;
	while (y + draw_start < draw_end)
	{
			// uint8_t noise = rand();
			if (y >= 0 && y <= draw_end)
			{
				wall_y = (y / (double)wl_height);
				mlx_put_pixel(render.img, x, y + draw_start, get_texture_pixel(tex, wall_x, wall_y));
			}
		y++;
	}
}

/*
** Draws the walls
** 	Needs:
** 		The game image
** 		The raycasting data
** 		The headbobbing data
** 		The map peak data
**		The wall texture data
*/
void	draw_walls(t_render render, t_map *map)
{
	int x;
	x = 0;
	while (x < WIDTH)
	{
		t_rgba c;
		c.color = 0;
		if (render.rays[x].side == 0)
		{
			c.a = 255;
			draw_wall_strip(render, x, map->tex[0]);
		}
		else if (render.rays[x].side == 1)
		{
			c.a = 150;
			draw_wall_strip(render, x, map->tex[1]);
		}
		x++;
	}
}

void	draw_particles(mlx_image_t *game, t_particle *particles)
{
	int i;

	i = 0;
	while (i < N_PARTICLES)
	{
		float y = ((float) rand() / (float)RAND_MAX / 4);
		particles[i].dir.y = y - 0.05;
		particles[i].p.x = particles[i].p.x + particles[i].dir.x * 2;
		particles[i].p.y = particles[i].p.y + particles[i].dir.y * 2;
		particles[i].dir.x = 0.1 * -y;
		if (particles[i].p.y > HEIGHT)
			particles[i].p.y = 0;
		if (particles[i].p.y < 0)
			particles[i].p.y = HEIGHT;

		if (particles[i].p.x > WIDTH)
			particles[i].p.x = y;
		if (particles[i].p.x < 0)
			particles[i].p.x = WIDTH;
		draw_square(game, color(175, 175, 175), vec_to_int(particles[i].p), vec_to_int(particles[i].size));
		i++;
	}
}
