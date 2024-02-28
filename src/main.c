#include <cub3d.h>
#include <cbd_parser.h>
#include <cbd_error.h>
#include <libft.h>
#include <stdio.h>
#include <MLX42.h>
#include <stdlib.h>

#define WHITE 		0xFFFFFFFF
#define RED 		0xFF0000FF
#define GREEN 		0x00FF00FF

#define TILES 		50
#define TILESIZE 	(WIDTH + HEIGHT) / TILES

void	draw_player_pos(mlx_image_t *img, t_vec_f pos)
{
	if (pos.x <= WIDTH && pos.x >= 0 && pos.y <= HEIGHT && pos.y >= 0)
	{
		mlx_put_pixel(img, pos.x, pos.y, GREEN);
		mlx_put_pixel(img, pos.x, pos.y + 1, GREEN);
		mlx_put_pixel(img, pos.x - 1, pos.y, GREEN);
		mlx_put_pixel(img, pos.x + 1, pos.y, GREEN);
		mlx_put_pixel(img, pos.x, pos.y - 1, GREEN);
	}
}

void	draw_grid(t_app *cbd, int width, int height)
{
	t_vec p;	
	t_vec offset;
	int	i;
	int	j;

	ft_memset(cbd->game->pixels, WHITE, sizeof(uint8_t) * cbd->game->width * cbd->game->height * 4);
	offset.x = (WIDTH - ((width + 1) * TILESIZE)) / 2;
	offset.y = (HEIGHT - ((height + 1) * TILESIZE)) / 2;
	i = 0;
	while (i <= height)
	{
		j = 0;
		t_vec h1;
		t_vec h2;
		h1.x = offset.x;
		h1.y = (i * TILESIZE) + offset.y;
		h2.x = WIDTH - offset.x - TILESIZE;
		h2.y = (i * TILESIZE) + offset.y;
		draw_line(cbd->game, WHITE, h1, h2); 
		while (j <= width)
		{
			p.x = (j * TILESIZE) + offset.x;
			p.y = (i * TILESIZE) + offset.y;
			if (p.x <= WIDTH && p.x >= 0 && p.y <= HEIGHT && p.y >= 0)
			{
				if (i == 0)
				{
					t_vec v;
					v.x = p.x;
					v.y = HEIGHT - offset.y - TILESIZE;
					v.y = HEIGHT - offset.y - TILESIZE;
					draw_line(cbd->game, WHITE, p, v); 
				}
				mlx_put_pixel(cbd->game, p.x, p.y, RED);
				mlx_put_pixel(cbd->game, p.x, p.y + 1, RED);
				mlx_put_pixel(cbd->game, p.x - 1, p.y, RED);
				mlx_put_pixel(cbd->game, p.x + 1, p.y, RED);
				mlx_put_pixel(cbd->game, p.x, p.y - 1, RED);
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
	float move_speed = cbd->mlx->delta_time * 100;

	t_vec offset;
	offset.x = (WIDTH - (cbd->mapdata->width * TILESIZE)) / 2;
	offset.y = (HEIGHT - (cbd->mapdata->height * TILESIZE)) / 2;
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_UP) && cbd->playerdata.pos.y >= 0 + offset.y)
		cbd->playerdata.pos.y -= move_speed;
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_DOWN) && cbd->playerdata.pos.y <= HEIGHT - offset.y)
		cbd->playerdata.pos.y += move_speed;
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_RIGHT) && cbd->playerdata.pos.x <= WIDTH - offset.x)
		cbd->playerdata.pos.x += move_speed;
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_LEFT) && cbd->playerdata.pos.x >= 0 + offset.x)
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
	t_vec offset;
	offset.x = (WIDTH - (cbd.mapdata->width * TILESIZE)) / 2;
	offset.y = (HEIGHT - (cbd.mapdata->height * TILESIZE)) / 2;
	cbd.playerdata.pos.x = ((cbd.mapdata->start_pos.x * (float) TILESIZE)) + offset.x;
	cbd.playerdata.pos.y = ((cbd.mapdata->start_pos.y * (float) TILESIZE)) + offset.y;

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
