#include <cub3d.h>
#include <cbd_error.h>
#include <libft.h>
#include <MLX42.h>
#include <stdio.h>
#include <math.h>

#define WHITE 		0xFFFFFFFF
#define	OFF_WHITE	0xF0F0F0FF	
#define RED 		0xFF0000FF
#define GREEN 		0x00FF00FF
#define BLUE 		0x0000FFFF

#define TILES 		(16 + 16)
#define TILESIZE 	WIDTH / TILES

t_vec	cast_ray(char **map, t_vec pos, t_vec_f dir)
{
	t_vec wall;
	t_vec_f side_dist;
	t_vec_f delta_dist;
	t_vec_f step_size;
	t_vec	map_check;
	t_vec	step;
	t_vec_f ray_len;

	(void) map;
	(void) side_dist;
	(void) delta_dist;
	(void) dir;

	step_size.x = sqrt(1 + (dir.y / dir.x) * (dir.y / dir.x));
	step_size.y = sqrt(1 + (dir.x / dir.y) * (dir.x / dir.y));
	map_check = pos;
	if (dir.x < 0)
	{
		step.x = -1;
		ray_len.x = (pos.x - (float)map_check.x) * step_size.x;
	}
	else
	{
		step.x = 1;
		ray_len.x = (((float)map_check.x + 1) - pos.x) * step_size.x;
	}
	if (dir.y < 0)
	{
		step.y = -1;
		ray_len.y = (pos.y - (float)map_check.y) * step_size.y;
	}
	else
	{
		step.y = 1;
		ray_len.y = (((float)map_check.y + 1) - pos.y) * step_size.x;
	}


	bool wall_is_found = false;
	float max_dist = 100.0f;
	float dist = 0;
	while (!wall_is_found && dist < max_dist)
	{
		if (ray_len.x < ray_len.y)
		{
			map_check.x += step.x;
			dist = ray_len.x;
			ray_len.x += step_size.x;
		}
		else
		{
			map_check.y += step.y;
			dist = ray_len.y;
			ray_len.y += step_size.y;
		}
		
		if (map_check.y >= 0 && map_check.y < 16 && map_check.x >= 0 && map_check.x < 16)
		{
			if (map[map_check.y][map_check.x] == '1')
				wall_is_found = true;
		}
	}

	if (wall_is_found)
	{
		wall.x = pos.x + dir.x * dist;
		wall.y = pos.y + dir.y * dist;
		return (wall);
	}


	// while (map[pos.y][pos.x])
	// {
	// 	printf("pos(%d, %d)\n", pos.x, pos.y);
	// 	if (map[pos.y][pos.x] == '1')
	// 	{
	// 		wall.x = pos.x;
	// 		wall.y = pos.y;
	// 		printf("wall(%d, %d)\n", wall.x, wall.y);
	// 		return (wall);
	// 	}
	// 	pos.y--;
	// }
	return (pos);
}

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

void	move_player(void *param)
{
	t_app *cbd;

	cbd = param;
	float move_speed = cbd->mlx->delta_time * 2;

	t_vec_f pos;
	t_vec_f dir;

	pos = vec_assign(cbd->playerdata.pos.x, cbd->playerdata.pos.y);
	dir = vec_assign(cbd->playerdata.dir.x, cbd->playerdata.dir.y);

	if (mlx_is_key_down(cbd->mlx, MLX_KEY_UP)) 
	{
		int x = (pos.x + dir.x * move_speed);
		int y = (pos.y + dir.y * move_speed);
		if (cbd->mapdata->cbd_map[(int)pos.y][x] == '0')
			cbd->playerdata.pos.x += cbd->playerdata.dir.x * move_speed;
		if (cbd->mapdata->cbd_map[y][(int)pos.x] == '0')
			cbd->playerdata.pos.y += cbd->playerdata.dir.y * move_speed;
	}
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_DOWN))
	{
		int x = (pos.x - dir.x * move_speed);
		int y = (pos.y - dir.y * move_speed);
		if (cbd->mapdata->cbd_map[(int)pos.y][x] == '0')
			cbd->playerdata.pos.x -= cbd->playerdata.dir.x * move_speed;
		if (cbd->mapdata->cbd_map[y][(int)pos.x] == '0')
			cbd->playerdata.pos.y -= cbd->playerdata.dir.y * move_speed;
	}
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_RIGHT) && cbd->playerdata.pos.x <= cbd->mapdata->width)
		vec_rotate(&cbd->playerdata.dir, cbd->mlx->delta_time * 3);
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_LEFT) && cbd->playerdata.pos.x >= 0)
		vec_rotate(&cbd->playerdata.dir, -cbd->mlx->delta_time * 3);

	draw_grid(cbd, cbd->mapdata->width, cbd->mapdata->height);
}

bool	cbd_game_loop(t_app *cbd)
{
	//Init player data;
	cbd->mapdata->cbd_map[cbd->mapdata->start_pos.y][cbd->mapdata->start_pos.x] = '0';
	cbd->playerdata.pos.x = cbd->mapdata->start_pos.x;
	cbd->playerdata.pos.y = cbd->mapdata->start_pos.y;

	cbd->playerdata.dir.x = 0;
	cbd->playerdata.dir.y = -1;
	cbd->playerdata.angle = 0;
	cbd->playerdata.scalar = 0;

	//Init MLX
	cbd->mlx = mlx_init(WIDTH, HEIGHT, "Telestein 3D", true);
	if (!cbd->mlx)
		return (FAILURE);

	//Init game image
	cbd->game = mlx_new_image(cbd->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(cbd->mlx, cbd->game, 0, 0);
	if (!cbd->game)
		return (cbd_error(ERR_ALLOC), FAILURE);

	//Init menu images
	cbd->menudata = cbd_init_menu(cbd->mlx);
	if (!cbd->menudata)
		return (cbd_error(ERR_ALLOC), FAILURE);

	//Mlx loops
	mlx_key_hook(cbd->mlx, navigate_menu, cbd);
	mlx_loop_hook(cbd->mlx, move_player, cbd);
	mlx_loop(cbd->mlx);
	mlx_terminate(cbd->mlx);
	return (SUCCESS);
}
