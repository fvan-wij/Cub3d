#include <cub3d.h>
#include <cbd_error.h>
#include <libft.h>
#include <MLX42.h>
#include <stdio.h>
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
	int x;
(void) img;	
	x = 0;
	int step = WIDTH / FOV;
	while (x < FOV)
	{
		int line_height = (int)(HEIGHT / rays[x].wall_dist);
		int draw_start = (-line_height / 2) + (HEIGHT / 2);
		int draw_end = (line_height / 2) + (HEIGHT / 2);
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;
		t_vec strip_start;
		strip_start.x = x * step;
		strip_start.y = draw_start;
		t_vec strip_end;
		strip_end.x = strip_start.x;
		strip_end.y = draw_end;
		// if (x == 0)
		// 	printf("strip_start(%d, %d), strip_end(%d, %d)", strip_start.x, strip_start.y, strip_end.x, strip_end.y);
		t_rgba c;
		c.color = 0;
		if (rays[x].side == 0)
			c.color = BLUE + 25;
		else if (rays[x].side == 1)
			c.color = BLUE;
		if (strip_start.x >= 0 && strip_start.x <= WIDTH && strip_end.x >= 0 && strip_end.x <= WIDTH && strip_start.y >= 0 && strip_end.y <= HEIGHT)
			draw_line(img, c.color, strip_start, strip_end);
		x++;
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

