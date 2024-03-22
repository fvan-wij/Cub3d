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
	// tmp = dither_texture(tmp);
	img = mlx_texture_to_image(mlx, tmp);
	mlx_delete_texture(tmp);
	return (img);
}

t_menu	*cbd_init_menu(mlx_t *mlx, t_map *map)
{
	t_menu 			*menu;

	menu = ft_calloc(1, sizeof(t_menu));
	if (!menu)
		return (NULL);

	// Main menu
	menu->main_menu.bg = cbd_init_texture_img(mlx, "./data/menu/menu_main.png");

	// Select menu
	menu->select_menu.bg = cbd_init_texture_img(mlx, "./data/menu/menu_map_select.png");
	menu->main_menu.cursor = cbd_init_texture_img(mlx, "./data/menu/selector_knife.png");
	menu->select_menu.cursor = menu->main_menu.cursor;

	menu->select_menu.preview_img = cbd_init_texture_img(mlx, "./data/textures/map_preview.png");
	menu->main_menu.preview_img = menu->select_menu.preview_img;
	mlx_image_to_window(mlx, menu->main_menu.preview_img, 0, 0);
	menu->main_menu.preview_img->instances->z = -1;
	mlx_image_to_window(mlx, menu->main_menu.bg, 0, 0);
	mlx_image_to_window(mlx, menu->select_menu.bg, 0, 0);
	mlx_image_to_window(mlx, menu->main_menu.cursor, WIDTH / 2 +  64, HEIGHT / 2);
	set_main_cursor_positions(menu);
	set_select_cursor_positions(menu);
	set_map_preview_positions(menu);
	set_menu_state(menu, MAIN);
	menu->main_menu.preview_img->instances->x = menu->preview_positions[map->current_map].x;
	menu->main_menu.preview_img->instances->y = menu->preview_positions[map->current_map].y;
	return (menu);
}

t_animation	*init_weapon_animation(mlx_t *mlx, char *path)
{
	t_animation	*animation;
	char 		*temp;
	int			n;
	int			i;
	int 		w;
	int 		h;

	animation = ft_calloc(1, sizeof(t_animation));
	if (!path && animation)
		return (animation);
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
	inv->weapons[WPN_MAP].fire_animation = init_weapon_animation(mlx, NULL);
	if (!inv->weapons[WPN_MAP].fire_animation)
		return (NULL);

	return (inv);
}

void	init_wall_destruction_fx(t_wall_destruction *fx)
{
	int i;

	i = 0;
	while (i < MAX_WALL_PARTICLES)
	{
		float dice = (rand() / (float) RAND_MAX);
		float rvalx = (rand() / (float) RAND_MAX);
		float rvaly = (rand() / (float) RAND_MAX);
		if (dice < 0.6)
			rvalx = -rvalx;
		if (dice < 0.2)
			rvaly = -rvaly;
		fx->particles[i].dir.x = rvalx;
		fx->particles[i].dir.y = rvaly;
		fx->particles[i].p.x = (WIDTH>>1) + (rvalx * 50);
		fx->particles[i].p.y = (HEIGHT>>1) + (rvaly * 50);
		fx->particles[i].size.x = dice * 20;
		fx->particles[i].size.y = fx->particles[i].size.x;
		fx->particles[i].reset = fx->particles[i].size;
		fx->particles[i].rp = fx->particles[i].p;
		i++;
	}
	fx->b_timer = false;
}

void	init_render(t_render *render, t_hud *hud, t_inventory *inv)
{
	render->hud = hud;
	render->inv = inv;
	render->sprite = malloc(sizeof(t_sprite) * 1);
	render->sprite[0].pos.x = 2.5;
	render->sprite[0].pos.y = 9;
	render->sprite[0].tex = mlx_load_png("./data/textures/sprites/chainsaw.png");
	render->timer = 100;

	init_wall_destruction_fx(&render->fx);

}

void	init_playerdata(t_player *playerdata, t_map *mapdata)
{
	mapdata->cbd_map[(int)mapdata->start_pos.y][(int)mapdata->start_pos.x] = '0';
	playerdata->pos = mapdata->start_pos;
	playerdata->dir = mapdata->start_dir;
	playerdata->pos.x += 0.5f;
	playerdata->pos.y += 0.5f;
	playerdata->scalar = 1;
	playerdata->plane = vec_rotate(playerdata->dir, M_PI / 2);
	printf("Plane: %f, %f\n", playerdata->plane.x, playerdata->plane.y);
	printf("Dir: %f, %f\n", playerdata->dir.x, playerdata->dir.y);
	playerdata->map_peak = 0;
}

void	init_particles(t_particle *particles)
{
	ft_memset(particles, 0, sizeof(t_particle[N_PARTICLES]));
	int i = 0;
	int step = WIDTH / N_PARTICLES;
	while (i < N_PARTICLES)
	{
		particles[i].dir.y = 1.0;
		particles[i].p.x = i * step;
		particles[i].p.y = ((float) rand() / (float)RAND_MAX) * HEIGHT;
		if (particles[i].p.x < (WIDTH>>1))
			particles[i].dir.x = -1.0;
		else
			particles[i].dir.x = 1.0;

		particles[i].size.x = (float) rand() / (float)RAND_MAX * 4;
		particles[i].size.y = particles[i].size.x;
		particles[i].reset = particles[i].size;
		i++;
	}
}

mlx_t	*cbd_init_window(void)
{
	mlx_t	*window;

	window = mlx_init(WIDTH, HEIGHT, "Telestein 3D", true);
	if (!window)
		return (NULL);
	return (window);
}

t_hud	*cbd_init_hud(mlx_t *mlx)
{
	t_hud *hud;

	hud = malloc(sizeof(t_hud));
	if (!hud)
		return (NULL);
	hud->img[HUD_MAP] = mlx_new_image(mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	hud->img[HUD_OVERLAY] = mlx_new_image(mlx, WIDTH, HEIGHT);
	hud->img[HUD_CRT] = mlx_new_image(mlx, WIDTH, HEIGHT);
	return (hud);
}

bool cbd_init(t_app *cbd)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	mlx_set_setting(MLX_MAXIMIZED, 1);
	cbd->mlx = cbd_init_window();
	if (!cbd->mlx)
		return(cbd_error(ERR_ALLOC), FAILURE);

	cbd->render.img = mlx_new_image(cbd->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(cbd->mlx, cbd->render.img, 0, 0);
	if (!cbd->render.img)
		return (cbd_error(ERR_ALLOC), FAILURE);
	cbd->render.sprite_img = mlx_new_image(cbd->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(cbd->mlx, cbd->render.sprite_img, 0, 0);
	if (!cbd->render.sprite_img)
		return (cbd_error(ERR_ALLOC), FAILURE);

	cbd->hud = cbd_init_hud(cbd->mlx);
	mlx_image_to_window(cbd->mlx, cbd->hud->img[HUD_OVERLAY], 0, 0);
	if (!cbd->hud)
		return (cbd_error(ERR_ALLOC), FAILURE);

	cbd->playerdata.inv = cbd_init_inventory(cbd->mlx);
	if (!cbd->playerdata.inv)
		return (cbd_error(ERR_ALLOC), FAILURE);

	mlx_image_to_window(cbd->mlx, cbd->hud->img[HUD_MAP], (WIDTH>>1) - (MINIMAP_WIDTH>>2) - 16, (HEIGHT>>1) + (MINIMAP_HEIGHT>>3) + 4);
	mlx_image_to_window(cbd->mlx, cbd->playerdata.inv->weapons[WPN_MAP].img, (WIDTH>>2), (HEIGHT>>3));
	mlx_image_to_window(cbd->mlx, cbd->playerdata.inv->weapons[WPN_FIST].img, (WIDTH>>1) - (cbd->playerdata.inv->weapons[WPN_FIST].img->width / 2), HEIGHT - (cbd->playerdata.inv->weapons[WPN_FIST].img->height>>1));
	mlx_image_to_window(cbd->mlx, cbd->playerdata.inv->weapons[WPN_CHAINSAW].img, (WIDTH>>1) - (cbd->playerdata.inv->weapons[WPN_CHAINSAW].img->width / 2), HEIGHT - (cbd->playerdata.inv->weapons[WPN_CHAINSAW].img->height * 0.8));
	mlx_image_to_window(cbd->mlx, cbd->hud->img[HUD_CRT], 0, 0);
	cbd->playerdata.inv->weapons[WPN_MAP].img->enabled = false;
	cbd->playerdata.inv->weapons[WPN_FIST].img->enabled = false;
	cbd->playerdata.inv->weapons[WPN_CHAINSAW].img->enabled = false;

	cbd->menudata = cbd_init_menu(cbd->mlx, cbd->mapdata);
	if (!cbd->menudata)
		return (cbd_error(ERR_ALLOC), FAILURE);

	initialize_jump_table(cbd->mapdata->walls.jump_table);
	init_playerdata(&cbd->playerdata, cbd->mapdata);
	init_render(&cbd->render, cbd->hud, cbd->playerdata.inv);
	init_particles(cbd->particles);

	//Setup mlx hooks
	mlx_key_hook(cbd->mlx, cbd_input, cbd);
	mlx_loop_hook(cbd->mlx, cbd_loop, cbd);
	return (SUCCESS);
}
