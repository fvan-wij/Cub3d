#include <cub3d.h>
#include <cbd_parser.h>
#include <cbd_error.h>
#include <libft.h>
#include <stdio.h>
#include <MLX42.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.1415926535

#define WHITE 		0xFFFFFFFF
#define	OFF_WHITE	0xF0F0F0FF	
#define RED 		0xFF0000FF
#define GREEN 		0x00FF00FF
#define BLUE 		0x0000FFFF

#define TILES 		(16 + 16)
#define TILESIZE 	WIDTH / TILES

void	draw_player_pos(mlx_image_t *img, t_vec_f pos)
{
	t_vec dimension = {TILESIZE >> 2, TILESIZE >> 2};
	if (pos.x <= WIDTH && pos.x >= 0 && pos.y <= HEIGHT && pos.y >= 0)
		draw_square(img, BLUE, pos, dimension);
}

void	draw_grid(t_app *cbd, int width, int height)
{
	t_vec p;	
	t_vec_f init = {0, 0};
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
				t_vec dimension = {TILESIZE - 1, TILESIZE - 1};
				t_vec_f pf = {p.x, p.y};
				if (cbd->mapdata->cbd_map[i][j] == '1')
					draw_square(cbd->game, RED, pf, dimension);
				else
					draw_square(cbd->game, OFF_WHITE, pf, dimension);
			}
			j++;
		}
		i++;
	}
	draw_player_pos(cbd->game, cbd->playerdata.pos);
}

void	move_player(void *param)
{
	t_app *cbd;

	cbd = param;
	float move_speed = cbd->mlx->delta_time * 200;
	t_vec edge = {cbd->mapdata->width * TILESIZE, cbd->mapdata->height * TILESIZE};

	if (mlx_is_key_down(cbd->mlx, MLX_KEY_UP) && cbd->playerdata.pos.y >= 0) 
		cbd->playerdata.pos.y -= move_speed;
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_DOWN) && cbd->playerdata.pos.y <= edge.y)
		cbd->playerdata.pos.y += move_speed;
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_RIGHT) && cbd->playerdata.pos.x <= edge.x)
		cbd->playerdata.pos.x += move_speed;
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_LEFT) && cbd->playerdata.pos.x >= 0)
		cbd->playerdata.pos.x -= move_speed;
	draw_grid(cbd, cbd->mapdata->width, cbd->mapdata->height);
}

int32_t	main(int argc, char *argv[])
{
	t_app cbd;

	//Parsing & Validation
	ft_memset(&cbd, 0, sizeof(t_app));
	if (!arg_is_valid(argc, argv))
		return (FAILURE);
	cbd.mapdata = cbd_parse_map(argv[1], &cbd);
	if (!cbd.mapdata)
		return (FAILURE);
	print_debug_info(&cbd);

	//Init player data;
	cbd.playerdata.pos.x = ((cbd.mapdata->start_pos.x * (float) TILESIZE));
	cbd.playerdata.pos.y = ((cbd.mapdata->start_pos.y * (float) TILESIZE));


	//Init MLX
	cbd.mlx = mlx_init(WIDTH, HEIGHT, "Telestein 3D", true);
	if (!cbd.mlx)
		return (FAILURE);

	//Init game image
	cbd.game = mlx_new_image(cbd.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(cbd.mlx, cbd.game, 0, 0);
	if (!cbd.game)
		return (cbd_error(ERR_ALLOC), FAILURE);

	//Init menu images
	cbd.menudata = cbd_init_menu(cbd.mlx);
	if (!cbd.menudata)
		return (cbd_error(ERR_ALLOC), FAILURE);


	draw_grid(&cbd, cbd.mapdata->width, cbd.mapdata->height);

	//Mlx loops
	mlx_key_hook(cbd.mlx, navigate_menu, &cbd);
	mlx_loop_hook(cbd.mlx, move_player, &cbd);
	mlx_loop(cbd.mlx);
	mlx_terminate(cbd.mlx);
	return (SUCCESS);
}
