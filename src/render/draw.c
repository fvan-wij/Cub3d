#include <cub3d.h>
#include <cbd_error.h>
#include <libft.h>
#include <MLX42.h>
#include <stdio.h>
#include <math.h>
#include <cbd_render.h>

void	draw_player(char **map, mlx_image_t *img, t_player p)
{
	t_vec	size;
	int		i;

	i = 0;
	size.x = TILESIZE>>3;
	size.y = TILESIZE>>3;
	t_vec_f world_dir = vec_assign((p.pos.x + p.dir.x) * TILESIZE, (p.pos.y + p.dir.y) * TILESIZE);
	t_vec_f world_pos = vec_assign(p.pos.x * TILESIZE, p.pos.y * TILESIZE);
	while (i < FOV)
	{
		p.rays[i] = cast_ray(map, p, i);
		// t_vec_f inter = vec_assign(p.pos.x + (p.rays[i].dir.x * p.rays[i].wall_dist) * TILESIZE, p.pos.y + (p.rays[i].dir.y * p.rays[i].wall_dist) * TILESIZE);
		// printf("inter(%f, %f)\n", inter.x, inter.y);
		// if (inter.x <= WIDTH && inter.x >= 0 && inter.y <= HEIGHT && inter.y >= 0)
		// 	draw_line(img, BLUE, vec_to_int(world_pos), vec_to_int(inter));
		if (p.rays[i].intersection.x <= WIDTH && p.rays[i].intersection.x >= 0 && p.rays[i].intersection.y <= HEIGHT && p.rays[i].intersection.y >= 0)
			draw_line(img, BLUE, vec_to_int(world_pos), vec_to_int(p.rays[i].intersection));
		i++;
	}
	if (world_dir.x <= WIDTH && world_dir.x >= 0 && world_dir.y <= HEIGHT && world_dir.y >= 0)
	{
		draw_circle(img, BLUE, vec_to_int(world_pos), size);
		// draw_line(img, BLUE, vec_to_int(world_pos), vec_to_int(world_dir));
	}
}

void	cast_rays(char **map, t_player *p)
{
	int		i;

	i = 0;
	while (i < FOV)
	{
		p->rays[i] = cast_ray(map, *p, i);
		i++;
	}
}

void	draw_walls(mlx_image_t *img, t_ray rays[FOV])
{
	int i;
(void) img;	
	i = 0;
	int step = WIDTH / FOV;
	while (i < FOV)
	{
		int line_height = (int)(HEIGHT / rays[i].wall_dist);
		int draw_start = -line_height / 2 + HEIGHT / 2;
		int draw_end = line_height / 2 + HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;
		t_vec strip_start;
		strip_start.x = i * step;
		strip_start.y = draw_start;
		t_vec strip_end;
		strip_end.x = i * step;
		strip_end.y = draw_end;
		// if (strip_start.x >= 0 && strip_start.x <= WIDTH && strip_end.x >= 0 && strip_end.x <= WIDTH)
		// 	draw_square(img, BLUE, strip_start, strip_end);
		t_rgba c;
		c.color = OFF_WHITE;
		c.b = rays[i].wall_dist;
		if (strip_start.x >= 0 && strip_start.x <= WIDTH && strip_end.x >= 0 && strip_end.x <= WIDTH)
			draw_line(img, BLUE, strip_start, strip_end);
		i++;
	}
}

void	draw_world(t_app *cbd)
{
	t_vec init = {0, 0};
	t_vec screen = {WIDTH, HEIGHT};

	draw_square(cbd->game, OFF_WHITE, init, screen);
	cast_rays(cbd->mapdata->cbd_map, &cbd->playerdata);
	draw_walls(cbd->game, cbd->playerdata.rays);
}

void	draw_grid(t_app *cbd, int width, int height)
{
	(void) width;
	(void) height;
	// t_vec p;
	// t_vec init = {0, 0};
	// t_vec screen = {WIDTH, HEIGHT};
	// int	i;
	// int	j;
	//
	// draw_square(cbd->game, OFF_WHITE, init, screen);
	// i = 0;
	// while (i < height)
	// {
	// 	j = 0;
	// 	while (j < width)
	// 	{
	// 		p.x = (j * TILESIZE);
	// 		p.y = (i * TILESIZE);
	// 		if (p.x <= WIDTH && p.x >= 0 && p.y <= HEIGHT && p.y >= 0)
	// 		{
	// 			t_vec size = {TILESIZE - 1, TILESIZE - 1};
	// 			if (cbd->mapdata->cbd_map[i][j] == '1')
	// 				draw_square(cbd->game, RED, p, size);
	// 			else
	// 				draw_square(cbd->game, OFF_WHITE, p, size);
	// 		}
	// 		j++;
	// 	}
	// 	i++;
	// }
	// draw_player(cbd->mapdata->cbd_map, cbd->game, cbd->playerdata);
	// printf("pos(%f, %f), dir(%f, %f), plane(%f, %f)\n", cbd->playerdata.pos.x,cbd->playerdata.pos.y, cbd->playerdata.dir.x,cbd->playerdata.dir.y, cbd->playerdata.plane.x ,cbd->playerdata.plane.y);
	draw_world(cbd);
}

