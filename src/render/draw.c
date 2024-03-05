#include <cub3d.h>
#include <cbd_error.h>
#include <libft.h>
#include <MLX42.h>
#include <stdio.h>
#include <math.h>
#include <cbd_render.h>

void	draw_player(char **map, mlx_image_t *img, t_vec_f pos, t_vec_f dir, float scalar)
{
	t_vec	size;
	t_vec	p;
	t_vec	d;

	size.x = TILESIZE>>3;
	size.y = TILESIZE>>3;
	(void) map;
	(void) scalar;

	t_vec intersect = cast_ray(map, vec_to_int(pos), dir);
	intersect.x = intersect.x * TILESIZE;
	intersect.y = intersect.y * TILESIZE;
	// draw_line(img, BLUE, p, d);
	p.x = pos.x * TILESIZE;
	p.y = pos.y * TILESIZE;
	draw_line(img, RED, p, intersect);
	d.x = (pos.x + (scalar * dir.x)) * TILESIZE;
	d.y = (pos.y + (scalar * dir.y)) * TILESIZE;
	if (pos.x <= WIDTH && pos.x >= 0 && pos.y <= HEIGHT && pos.y >= 0)
	{
		pos.x = pos.x * TILESIZE;
		pos.y = pos.y * TILESIZE;
		draw_circle(img, BLUE, vec_to_int(pos), size);
	}
	(void) d;
	// t_vec intersect = cast_ray(map, vec_to_int(pos), dir);
	// intersect.x = intersect.x * TILESIZE;
	// intersect.y = intersect.y * TILESIZE;
	// draw_line(img, BLUE, p, d);
	draw_line(img, RED, p, intersect);
}

void	draw_grid(t_app *cbd, int width, int height)
{
	t_vec p;
	t_vec init = {0, 0};
	t_vec screen = {WIDTH, HEIGHT};
	int	i;
	int	j;

	draw_square(cbd->game, OFF_WHITE, init, screen);
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
				t_vec size = {TILESIZE - 1, TILESIZE - 1};
				if (cbd->mapdata->cbd_map[i][j] == '1')
					draw_square(cbd->game, RED, p, size);
				else
					draw_square(cbd->game, OFF_WHITE, p, size);
			}
			j++;
		}
		i++;
	}
	draw_player(cbd->mapdata->cbd_map, cbd->game, cbd->playerdata.pos, cbd->playerdata.dir, cbd->playerdata.scalar);
	printf("pos(%f, %f), dir(%f, %f)\n", cbd->playerdata.pos.x,cbd->playerdata.pos.y, cbd->playerdata.dir.x,cbd->playerdata.dir.y);
}
