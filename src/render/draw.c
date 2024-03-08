#include <cub3d.h>
#include <cbd_error.h>
#include <libft.h>
#include <MLX42.h>
#include <stdio.h>
#include <cbd_render.h>
#include <math.h>

void	draw_background(mlx_image_t *img, int32_t color)
{
	const t_vec2i init = {0, 0};
	const t_vec2i screen = {WIDTH, HEIGHT};

	draw_square(img, color, init, screen);
}

void	draw_player(char **map, mlx_image_t *img, t_player p)
{
	const float r = TILESIZE>>1;
	int		i;

	i = 0;
	t_vec2d world_dir = vec_assign((p.pos.x + p.dir.x) * TILESIZE, (p.pos.y + p.dir.y) * TILESIZE);
	t_vec2d world_pos = vec_assign(p.pos.x * TILESIZE, p.pos.y * TILESIZE);
	while (i < WIDTH)
	{
		p.rays[i] = cast_ray(map, p, i);
		if (p.rays[i].intersection.x <= WIDTH && p.rays[i].intersection.x >= 0 && p.rays[i].intersection.y <= HEIGHT && p.rays[i].intersection.y >= 0)
		{
			draw_line(img, color(151, 0, 0), vec_to_int(world_pos), vec_to_int(p.rays[i].intersection));
		}
		i++;
	}
	if (world_dir.x <= WIDTH && world_dir.x >= 0 && world_dir.y <= HEIGHT && world_dir.y >= 0)
	{
		draw_circle(img, color(151, 0, 0), vec_to_int(world_pos), r);
		// draw_line(img, BLUE, vec_to_int(world_pos), vec_to_int(world_dir)); // Draws player looking direction
	}
}

void	draw_map(t_app *cbd, int width, int height)
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
				if (cbd->mapdata->cbd_map[i][j] == '1')
					draw_square(cbd->hud->img[HUD_MAP], color(200, 200, 200), p, size);
				else
					draw_square(cbd->hud->img[HUD_MAP], OFF_WHITE, p, size);
			}
			j++;
		}
		i++;
	}
	// printf("pos(%f, %f), dir(%f, %f), plane(%f, %f)\n", cbd->playerdata.pos.x,cbd->playerdata.pos.y, cbd->playerdata.dir.x,cbd->playerdata.dir.y, cbd->playerdata.plane.x ,cbd->playerdata.plane.y);
}

void	draw_wall_strip(t_app *cbd,
	uint32_t color, int height, int x)
{
	int y;
	int draw_start;
	int draw_end;

	draw_start = (-height / 2) + (HEIGHT / 2);
	draw_end = (height / 2) + (HEIGHT / 2);
	draw_start += (sin(cbd->playerdata.headbob) * 10) + cbd->playerdata.map_peak;
	draw_end += (sin(cbd->playerdata.headbob) * 10) + cbd->playerdata.map_peak;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	y = draw_start;
	while (y < height + draw_start)
	{
		if (y >= draw_start && y <= draw_end)
			mlx_put_pixel(cbd->game, x, y, color);
		y++;
	}
}

void	draw_walls(t_app *cbd, t_ray *rays)
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
		draw_wall_strip(cbd, c.color, line_height, x);
		x += 6;
		// if (x % 2 == 0)
		// 	x += 2;
	}
}
