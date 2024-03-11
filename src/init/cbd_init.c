#include <cub3d.h>
#include <cbd_error.h>
#include <MLX42.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

mlx_image_t *cbd_init_texture_img(mlx_t *mlx, char *path)
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
	menu->main_menu.bg = cbd_init_texture_img(mlx, "./data/menu/menu_main.png");
		// menu->main_menu.map = cbd_init_texture_img(mlx, "CORRECT IMAGE PATH");

	// Select menu
	menu->select_menu.bg = cbd_init_texture_img(mlx, "./data/menu/menu_map_select.png");
		// menu->select_menu.map = cbd_init_texture_img(mlx, "CORRECT IMAGE PATH");
	menu->main_menu.cursor = cbd_init_texture_img(mlx, "./data/menu/selector_knife.png");
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

t_animation	*init_weapon_animation(mlx_t	*mlx, char *path)
{
	t_animation	*animation;
	char 		*temp;
	int			n;
	int			i;
	int 		w;
	int 		h;

	animation = ft_calloc(1, sizeof(t_animation));
	n = ft_strchr_index(path, '0');
	if (!animation)
		return (NULL);
	temp = ft_strdup(path);
	if (!temp)
		return (NULL);
	i = 0;
	while (i < MAX_FRAMES)
	{
		animation->frames[i].img = cbd_init_texture_img(mlx, temp);
		if (!animation->frames[i].img)
			return (NULL);

		w = (WIDTH/2) - (animation->frames[i].img->width / 2);
		h = HEIGHT - (animation->frames[i].img->height>>1) - 100;
		mlx_image_to_window(mlx, animation->frames[i].img, w, h); 
		animation->frames[i].img->enabled = false;
		animation->frames[i].duration = 2;
		temp[n] = temp[n] + 1;
		i++;
	}
	animation->n_frames = MAX_FRAMES;
	free(temp);
	return (animation);
}

t_inventory *cbd_init_inventory(mlx_t *mlx)
{
	t_inventory	*inv;
	inv = ft_calloc(1, sizeof(t_inventory));
	if (!inv)
		return (NULL);
	inv->weapons[WPN_FIST].img = cbd_init_texture_img(mlx, "./data/textures/player/hands2.png");
	inv->weapons[WPN_MAP].img = cbd_init_texture_img(mlx, "./data/textures/player/radar3.png");
	inv->weapons[WPN_CHAINSAW].img = cbd_init_texture_img(mlx, "./data/textures/player/chainsaw.png");

	inv->weapons[WPN_FIST].type = WPN_FIST;
	inv->weapons[WPN_CHAINSAW].type = WPN_CHAINSAW;
	inv->weapons[WPN_FIST].fire_animation = init_weapon_animation(mlx, "./data/textures/player/animation/fist/frame_0.png");
	if (!inv->weapons[WPN_FIST].fire_animation)
		return (NULL);
	inv->weapons[WPN_CHAINSAW].fire_animation = init_weapon_animation(mlx, "./data/textures/player/animation/chainsaw/frame_0.png");
	if (!inv->weapons[WPN_CHAINSAW].fire_animation)
		return (NULL);
	return (inv);
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
	if (!cbd->game)
		return (cbd_error(ERR_ALLOC), FAILURE);
	// cbd->hud->img[HUD_MAP] = mlx_new_image(cbd->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	cbd->hud->img[HUD_OVERLAY] = mlx_new_image(cbd->mlx, WIDTH, HEIGHT);


	mlx_image_to_window(cbd->mlx, cbd->game, 0, 0);
	mlx_image_to_window(cbd->mlx, cbd->hud->img[HUD_OVERLAY], 0, 0);
	// mlx_image_to_window(cbd->mlx, cbd->hud->img[HUD_MAP], (WIDTH>>1) - (MINIMAP_WIDTH>>2) - 16, (HEIGHT>>1) + (MINIMAP_HEIGHT>>3) + 4);
	// mlx_image_to_window(cbd->mlx, cbd->hud->img[WPN_MAP], (WIDTH/2) - (cbd->hud->img[WPN_MAP]->width / 2), HEIGHT - cbd->hud->img[WPN_MAP]->height);
	cbd->playerdata.inv = cbd_init_inventory(cbd->mlx);
	if (!cbd->playerdata.inv)
		return (cbd_error(ERR_ALLOC), FAILURE);
	cbd->playerdata.inv->equipped = WPN_FIST;
	mlx_image_to_window(cbd->mlx, cbd->playerdata.inv->weapons[WPN_FIST].img, (WIDTH/2) - (cbd->playerdata.inv->weapons[WPN_FIST].img->width / 2), HEIGHT - (cbd->playerdata.inv->weapons[WPN_FIST].img->height>>1));
	mlx_image_to_window(cbd->mlx, cbd->playerdata.inv->weapons[WPN_CHAINSAW].img, (WIDTH/2) - (cbd->playerdata.inv->weapons[WPN_CHAINSAW].img->width / 2), HEIGHT - (cbd->playerdata.inv->weapons[WPN_CHAINSAW].img->height * 0.8));

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

