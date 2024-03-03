#include <cub3d.h>
#include <cbd_error.h>
#include <libft.h>
#include <MLX42.h>

#define WHITE 		0xFFFFFFFF
#define	OFF_WHITE	0xF0F0F0FF	
#define RED 		0xFF0000FF
#define GREEN 		0x00FF00FF
#define BLUE 		0x0000FFFF

#define TILES 		(16 + 16)
#define TILESIZE 	WIDTH / TILES

// t_vec_f	cast_ray(char **map, t_vec_f pos, t_vec_f dir)
// {
// 	t_vec_f side_dist;
// 	t_vec_f delta_dist;
//
// }

void	draw_player(char **map, mlx_image_t *img, t_vec_f pos, t_vec_f dir)
{
	t_vec	size;
	t_vec	p;
	t_vec	d;
	(void) map;

	size.x = TILESIZE>>3;
	size.y = TILESIZE>>3;
	p.x = pos.x * TILESIZE;
	p.y = pos.y * TILESIZE;
	d.x = (pos.x + dir.x) * TILESIZE;
	d.y = (pos.y + dir.y) * TILESIZE;
	if (pos.x <= WIDTH && pos.x >= 0 && pos.y <= HEIGHT && pos.y >= 0)
	{
		pos.x = pos.x * TILESIZE;
		pos.y = pos.y * TILESIZE;
		draw_circle(img, BLUE, p, size);
	}
	// cast_ray(map, p, d);
	draw_line(img, BLUE, p, d);

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
	draw_player(cbd->mapdata->cbd_map, cbd->game, cbd->playerdata.pos, cbd->playerdata.dir);
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
	// normalize_vec(&cbd->playerdata.dir);

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
