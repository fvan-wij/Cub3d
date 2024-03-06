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

	size.x = TILESIZE>>3;
	size.y = TILESIZE>>3;
	(void) map;

	t_vec_f inter = cast_ray(map, p);
	p.dir.x = (p.pos.x + p.dir.x) * TILESIZE;
	p.dir.y = (p.pos.y + p.dir.y) * TILESIZE;
	if (p.pos.x <= WIDTH && p.pos.x >= 0 && p.pos.y <= HEIGHT && p.pos.y >= 0)
	{
		p.pos.x = p.pos.x * TILESIZE;
		p.pos.y = p.pos.y * TILESIZE;
		draw_circle(img, BLUE, vec_to_int(p.pos), size);
		// draw_line(img, BLUE, vec_to_int(p.pos), vec_to_int(p.dir));

		if (inter.x <= WIDTH && inter.x >= 0 && inter.y <= HEIGHT && inter.y >= 0)
			draw_line(img, BLUE, vec_to_int(p.pos), vec_to_int(inter));
	}
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
	draw_player(cbd->mapdata->cbd_map, cbd->game, cbd->playerdata);
	printf("pos(%f, %f), dir(%f, %f)\n", cbd->playerdata.pos.x,cbd->playerdata.pos.y, cbd->playerdata.dir.x,cbd->playerdata.dir.y);
}
