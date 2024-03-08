#include <cub3d.h>
#include <cbd_error.h>
#include <libft.h>
#include <MLX42.h>
#include <stdio.h>
#include <cbd_render.h>
#include <math.h>
#include <stdlib.h>

bool cbd_init(t_app *cbd)
{
	//Init player data;
	cbd->mapdata->cbd_map[(int)cbd->mapdata->start_pos.y][(int)cbd->mapdata->start_pos.x] = '0';
	cbd->playerdata.pos = cbd->mapdata->start_pos;

	cbd->playerdata.dir = cbd->mapdata->start_dir;
	cbd->playerdata.scalar = 1;
	cbd->playerdata.plane = vec_rotate(cbd->playerdata.dir, M_PI / 2);
	cbd->playerdata.map_peak = 0;

	//Init MLX
	cbd->mlx = mlx_init(WIDTH, HEIGHT, "Telestein 3D", true);
	if (!cbd->mlx)
		return (FAILURE);

	//Init game images
	cbd->game = mlx_new_image(cbd->mlx, WIDTH, HEIGHT);
	cbd->hud = malloc(sizeof(t_hud));
	cbd->hud->img[HUD_MAP] = mlx_new_image(cbd->mlx, RADARW, RADARH);
	mlx_texture_t *tex_hands;
	tex_hands = mlx_load_png("data/textures/player/radar2.png");
	cbd->hud->img[HUD_HANDS] = mlx_texture_to_image(cbd->mlx, tex_hands);
	mlx_image_to_window(cbd->mlx, cbd->game, 0, 0);
	mlx_image_to_window(cbd->mlx, cbd->hud->img[HUD_MAP], (WIDTH>>1) - 90, HEIGHT/2 + 40);
	mlx_image_to_window(cbd->mlx, cbd->hud->img[HUD_HANDS], (WIDTH/2) - (cbd->hud->img[HUD_HANDS]->width / 2), HEIGHT - cbd->hud->img[HUD_HANDS]->height);
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

bool	cbd_main(t_app *cbd)
{
	printf("Init\n");
	if (cbd_init(cbd))
		return (FAILURE);
	printf("Init success\n");
	mlx_loop(cbd->mlx);
	mlx_terminate(cbd->mlx);
	cleanup(cbd);
	return (SUCCESS);
}
