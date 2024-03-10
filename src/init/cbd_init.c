#include <cub3d.h>
#include <cbd_error.h>
#include <MLX42.h>
#include <math.h>
#include <stdlib.h>

mlx_image_t *cbd_init_menu_img(mlx_t *mlx, char *path)
{
	mlx_texture_t	*tmp;
	mlx_image_t		*img;

	tmp = mlx_load_png(path);
	if (!tmp)
		return (NULL);
	img = mlx_texture_to_image(mlx, tmp);
	mlx_delete_texture(tmp);
	return (img);
}

t_menu	*cbd_init_menu(mlx_t *mlx)
{
	t_menu 			*menu;

	menu = ft_calloc(1, sizeof(t_menu));
	if (!menu)
		return (NULL);

	// Main menu
	menu->main_menu.bg = cbd_init_menu_img(mlx, "./data/menu/menu_main.png");
		// menu->main_menu.map = cbd_init_menu_img(mlx, "CORRECT IMAGE PATH");

	// Select menu
	menu->select_menu.bg = cbd_init_menu_img(mlx, "./data/menu/menu_map_select.png");
		// menu->select_menu.map = cbd_init_menu_img(mlx, "CORRECT IMAGE PATH");
	menu->main_menu.cursor = cbd_init_menu_img(mlx, "./data/menu/selector_knife.png");
	menu->select_menu.cursor = menu->main_menu.cursor;

	mlx_image_to_window(mlx, menu->main_menu.bg, 0, 0);
		// mlx_image_to_window(mlx, menu->main_menu.map, 0, 0);
	mlx_image_to_window(mlx, menu->select_menu.bg, 0, 0);
	mlx_image_to_window(mlx, menu->main_menu.cursor, WIDTH / 2 +  64, HEIGHT / 2);
		// mlx_image_to_window(mlx, menu->select_menu.map, 0, 0);
	set_main_cursor_positions(menu);
	set_select_cursor_positions(menu);
	set_menu_state(menu, MAIN);
	return (menu);
}

bool cbd_init(t_app *cbd)
{
	//Init player data;
	cbd->mapdata->cbd_map[(int)cbd->mapdata->start_pos.y][(int)cbd->mapdata->start_pos.x] = '0';
	cbd->playerdata.pos = cbd->mapdata->start_pos;

	cbd->playerdata.dir = cbd->mapdata->start_dir;
	cbd->playerdata.scalar = 1;
	cbd->playerdata.plane = vec_rotate(cbd->playerdata.dir, M_PI / 2);
	cbd->playerdata.map_peak = 0;

	ft_memset(cbd->particles, 0, sizeof(t_particle[N_PARTICLES]));
	int i = 0;
	int step = WIDTH / N_PARTICLES;
	while (i < N_PARTICLES)
	{
		cbd->particles[i].dir.y = 1.0;
		cbd->particles[i].p.x = i * step;
		cbd->particles[i].p.y = ((float) rand() / (float)RAND_MAX) * HEIGHT;
		if (cbd->particles[i].p.x < (WIDTH>>1))
			cbd->particles[i].dir.x = -1.0;
		else
			cbd->particles[i].dir.x = 1.0;

		cbd->particles[i].size.x = (float) rand() / (float)RAND_MAX * 3;
		cbd->particles[i].size.y = cbd->particles[i].size.x;
		cbd->particles[i].reset = cbd->particles[i].size;
		i++;
	}

	//Init MLX
	cbd->mlx = mlx_init(WIDTH, HEIGHT, "Telestein 3D", true);
	if (!cbd->mlx)
		return (FAILURE);

	//Init game images
	cbd->hud = malloc(sizeof(t_hud));
	cbd->game = mlx_new_image(cbd->mlx, WIDTH, HEIGHT);
	cbd->hud->img[HUD_MAP] = mlx_new_image(cbd->mlx, RADARW, RADARH);

	mlx_texture_t *tex_radar;
	mlx_texture_t *tex_fist;
	mlx_texture_t *tex_saw;
	tex_radar = mlx_load_png("data/textures/player/radar2.png");
	tex_fist = mlx_load_png("data/textures/player/hands2.png");
	tex_saw = mlx_load_png("data/textures/player/chainsaw.png");
	cbd->hud->img[WPN_MAP] = mlx_texture_to_image(cbd->mlx, tex_radar);
	cbd->hud->img[WPN_FIST] = mlx_texture_to_image(cbd->mlx, tex_fist);
	cbd->hud->img[WPN_CHAINSAW] = mlx_texture_to_image(cbd->mlx, tex_saw);

	mlx_image_to_window(cbd->mlx, cbd->game, 0, 0);
	mlx_image_to_window(cbd->mlx, cbd->hud->img[HUD_MAP], (WIDTH>>1) - 90, HEIGHT/2 + 40);
	mlx_image_to_window(cbd->mlx, cbd->hud->img[WPN_MAP], (WIDTH/2) - (cbd->hud->img[WPN_MAP]->width / 2), HEIGHT - cbd->hud->img[WPN_MAP]->height);
	mlx_image_to_window(cbd->mlx, cbd->hud->img[WPN_FIST], (WIDTH/2) - (cbd->hud->img[WPN_FIST]->width / 2), HEIGHT - (cbd->hud->img[WPN_FIST]->height>>1));
	mlx_image_to_window(cbd->mlx, cbd->hud->img[WPN_CHAINSAW], (WIDTH/2) - (cbd->hud->img[WPN_CHAINSAW]->width / 2), HEIGHT - (cbd->hud->img[WPN_CHAINSAW]->height * 0.8));
	// cbd->hud->img[HUD_MAP]->enabled = false;
	// cbd->hud->img[WPN_MAP]->enabled = false;
	// cbd->hud->img[WPN_FIST]->enabled = false;
	// cbd->hud->img[WPN_CHAINSAW]->enabled = false;
	cbd->hud->equipped = WPN_FIST;
	if (!cbd->game)
		return (cbd_error(ERR_ALLOC), FAILURE);

	//Init menu images
	cbd->menudata = cbd_init_menu(cbd->mlx);
	if (!cbd->menudata)
		return (cbd_error(ERR_ALLOC), FAILURE);

	// Init Input
	// cbd_init_input(cbd);

	//Setup mlx hooks
	mlx_key_hook(cbd->mlx, cbd_input, cbd);
	mlx_loop_hook(cbd->mlx, cbd_loop, cbd);
	return (SUCCESS);
}

