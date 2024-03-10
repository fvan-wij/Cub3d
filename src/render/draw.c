#include <cub3d.h>
#include <cbd_error.h>
#include <libft.h>
#include <MLX42.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void	draw_hud(t_hud *hud)
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
}


void	draw_background(mlx_image_t *img, int32_t color)
{
	const t_vec2i init = {0, 0};
	const t_vec2i screen = {WIDTH, HEIGHT};

	draw_square(img, color, init, screen);
}

void	draw_player(char **map, mlx_image_t *img, t_vec2d pos, t_vec2d dir)
{
	const float r = TILESIZE>>1;
	(void) map;
	// int		i;

	// i = 0;
	t_vec2d world_dir = vec_assign((pos.x + dir.x) * TILESIZE, (pos.y + dir.y) * TILESIZE);
	t_vec2d world_pos = vec_assign(pos.x * TILESIZE, pos.y * TILESIZE);
	// while (i < WIDTH)
	// {
		// p.rays[i] = cast_ray(map, p, i);
		// if (p.rays[i].intersection.x <= WIDTH && p.rays[i].intersection.x >= 0 && p.rays[i].intersection.y <= HEIGHT && p.rays[i].intersection.y >= 0)
		// {
		// 	draw_line(img, color(151, 0, 0), vec_to_int(world_pos), vec_to_int(p.rays[i].intersection));
		// }
		// i++;
	// }
	if (world_dir.x <= WIDTH && world_dir.x >= 0 && world_dir.y <= HEIGHT && world_dir.y >= 0)
	{
		draw_circle(img, color(151, 0, 0), vec_to_int(world_pos), r);
		// draw_line(img, BLUE, vec_to_int(world_pos), vec_to_int(world_dir)); // Draws player looking direction
	}
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
	// printf("pos(%f, %f), dir(%f, %f), plane(%f, %f)\n", cbd->playerdata.pos.x,cbd->playerdata.pos.y, cbd->playerdata.dir.x,cbd->playerdata.dir.y, cbd->playerdata.plane.x ,cbd->playerdata.plane.y);
}

void	draw_wall_strip(mlx_image_t *game,
	uint32_t color, int height, int x, float headbob, float map_peak)
{
	int y;
	int draw_start;
	int draw_end;

	draw_start = (-height / 2) + (HEIGHT / 2);
	draw_end = (height / 2) + (HEIGHT / 2);
	draw_start += (sin(headbob) * 10) + map_peak;
	draw_end += (sin(headbob) * 10) + map_peak;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	y = draw_start;
	while (y < height + draw_start)
	{
		if (y >= draw_start && y <= draw_end)
			mlx_put_pixel(game, x, y, color);
		y++;
	}
}

void	draw_walls(mlx_image_t *game, t_ray *rays, float headbob, float map_peak)
{
	int x;
	x = 0;
	while (x < WIDTH)
	{
		int line_height = (int)(HEIGHT / rays[x].wall_dist);
		// if (x == 0)
		// 	printf("strip_start(%d, %d), strip_end(%d, %d)", strip_start.x, strip_start.y, strip_end.x, strip_end.y);
		t_rgba c;
		c.color = 0;
		if (rays[x].side == 0)
			c.color = 0xffffffff;
		else if (rays[x].side == 1)
			c.color = 0xaaaaaaff;
		draw_wall_strip(game, c.color, line_height, x, headbob, map_peak);
		x += 6;
		// if (x % 2 == 0)
		// 	x += 2;
	}
}

void	draw_particles(mlx_image_t *game, t_particle *particles)
{
	int i;

	i = 0;
	while (i < N_PARTICLES)
	{
		float y = ((float) rand() / (float)RAND_MAX / 4);

		particles[i].dir.y = y;
		particles[i].p.x = particles[i].p.x + particles[i].dir.x * 2;
		particles[i].p.y = particles[i].p.y + particles[i].dir.y * 2;
		if (particles[i].p.y > HEIGHT)
			particles[i].p.y = 0;
		if (particles[i].p.y < 0)
			particles[i].p.y = HEIGHT;

		if (particles[i].p.x > WIDTH)
			particles[i].p.x = y;
		if (particles[i].p.x < 0)
			particles[i].p.x = y;
		draw_square(game, color(175, 175, 175), vec_to_int(particles[i].p), vec_to_int(particles[i].size));
		i++;
	}
}
