#include <cub3d.h>
#include <cbd_parser.h>
#include <cbd_error.h>
#include <libft.h>
#include <MLX42.h>

#include <stdio.h>

// void set_player

bool cbd_init(t_app *cbd)
{
	//Init player data;
	cbd->mapdata->cbd_map[(int)cbd->mapdata->start_pos.y][(int)cbd->mapdata->start_pos.x] = '0';
	cbd->playerdata.pos = cbd->mapdata->start_pos;

	cbd->playerdata.dir = cbd->mapdata->start_dir;
	cbd->playerdata.scalar = 1;
	cbd->playerdata.plane = vec_assign(0.0f, 0.66f);

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

	//Setup mlx hooks
	mlx_key_hook(cbd->mlx, navigate_menu, cbd);
	mlx_loop_hook(cbd->mlx, move_player, cbd);
	printf("test\n");
	return (SUCCESS);
}
