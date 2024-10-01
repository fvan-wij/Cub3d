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
	menu->main_menu.cursor = cbd_init_texture_img(mlx, "./data/menu/selector_knife.png");

	// Select menu
	menu->select_menu.bg = cbd_init_texture_img(mlx, "./data/menu/menu_map_select.png");
	menu->select_menu.cursor = menu->main_menu.cursor;

	// Game over
	menu->game_over.bg = cbd_init_texture_img(mlx, "./data/menu/game_over.png");
	menu->game_over.cursor = menu->main_menu.cursor;

	// Game won
	menu->game_won.bg = cbd_init_texture_img(mlx, "./data/menu/game_won.png");
	menu->game_won.cursor = menu->main_menu.cursor;

	menu->select_menu.preview_img = cbd_init_texture_img(mlx, "./data/textures/map_preview.png");
	menu->main_menu.preview_img = menu->select_menu.preview_img;
	mlx_image_to_window(mlx, menu->main_menu.preview_img, 0, 0);
	mlx_image_to_window(mlx, menu->main_menu.bg, 0, 0);
	mlx_image_to_window(mlx, menu->select_menu.bg, 0, 0);
	mlx_image_to_window(mlx, menu->game_over.bg, 0, 0);
	mlx_image_to_window(mlx, menu->game_won.bg, 0, 0);
	mlx_image_to_window(mlx, menu->main_menu.cursor, WIDTH / 2 + 64, HEIGHT / 2);
	menu->game_won.bg->instances->enabled = false;
	set_main_cursor_positions(menu);
	set_select_cursor_positions(menu);
	set_map_preview_positions(menu);
	menu->game_over.cursor_pos = vec2i_assign(WIDTH / 2 - 64, HEIGHT / 2);
	menu->game_won.cursor_pos = menu->game_over.cursor_pos;
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
	inv->weapons[WPN_MAP].img = cbd_init_texture_img(mlx, "./data/textures/player/radar4.png");
	inv->weapons[WPN_CHAINSAW].img = cbd_init_texture_img(mlx, "./data/textures/player/chainsaw.png");

	inv->weapons[WPN_FIST].type = WPN_FIST;
	inv->weapons[WPN_CHAINSAW].type = WPN_CHAINSAW;
	inv->weapons[WPN_FIST].fire_animation = init_weapon_animation(mlx, "./data/textures/player/animation/fist/frame_0.png");
	if (!inv->weapons[WPN_FIST].fire_animation)
		return (NULL);
	inv->weapons[WPN_CHAINSAW].fire_animation = init_weapon_animation(mlx, "./data/textures/player/animation/chainsaw/frame_0.png");
	if (!inv->weapons[WPN_CHAINSAW].fire_animation)
		return (NULL);
	inv->weapons[WPN_CHAINSAW].fire_animation->frames[1].img->instances->x +=150;
	inv->weapons[WPN_CHAINSAW].fire_animation->frames[1].img->instances->y -=100;
	mlx_delete_image(mlx, inv->weapons[WPN_CHAINSAW].fire_animation->frames[2].img);
	inv->weapons[WPN_CHAINSAW].fire_animation->frames[2] = inv->weapons[WPN_CHAINSAW].fire_animation->frames[0];
	inv->weapons[WPN_CHAINSAW].fire_animation->reset_x = inv->weapons[WPN_CHAINSAW].fire_animation->frames[1].img->instances->x;
	inv->weapons[WPN_CHAINSAW].fire_animation->current_x = inv->weapons[WPN_CHAINSAW].fire_animation->reset_x;
	inv->weapons[WPN_MAP].fire_animation = init_weapon_animation(mlx, NULL);
	if (!inv->weapons[WPN_MAP].fire_animation)
		return (NULL);

	inv->weapons[WPN_CHAINSAW].in_inventory = false;
	inv->weapons[WPN_MAP].in_inventory = false;
	return (inv);
}

void	init_blood_splat(t_particle *splat_particle)
{
	int i;

	i = 0;
	while (i < MAX_BLOOD_PARTICLES)
	{
		float dice = (rand() / (float) RAND_MAX);
		float rvalx = cos(rand());
		float rvaly = sin(rand());
		if (dice < 0.5)
			rvalx = -rvalx;
		if (dice < 0.3)
			rvaly = -rvaly;
		splat_particle[i].dir.x = rvalx;
		splat_particle[i].dir.y = rvaly;
		splat_particle[i].p.x = (WIDTH>>1) + (rvalx * 750);
		splat_particle[i].p.y = (HEIGHT>>1) + (rvaly * 750);
		splat_particle[i].size.x = dice * 10;
		splat_particle[i].size.y = splat_particle[i].size.x;
		splat_particle[i].reset = splat_particle[i].size;
		splat_particle[i].rp = splat_particle[i].p;
		i++;
	}
}

void	init_blood_particles(t_particle *blood_particle)
{
	int i;

	i = 0;
	while (i < MAX_BLOOD_PARTICLES)
	{
		float dice = (rand() / (float) RAND_MAX);
		float rvalx = cos(rand());
		float rvaly = sin(rand()) + 1;
		if (dice < 0.5)
			rvalx = -rvalx;
		if (dice < 0.2)
			rvaly = -rvaly;
		blood_particle[i].dir.x = rvalx * 10;
		blood_particle[i].dir.y = rvaly * 10;
		blood_particle[i].p.x = (WIDTH>>1) + (rvalx * 150);
		blood_particle[i].p.y = (HEIGHT>>1) + (rvaly * 150);
		blood_particle[i].size.x = dice * 75;
		blood_particle[i].size.y = blood_particle[i].size.x;
		blood_particle[i].reset = blood_particle[i].size;
		blood_particle[i].rp = blood_particle[i].p;
		i++;
	}
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
	init_blood_splat(render->splat);
	init_blood_particles(render->blood);
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
	playerdata->map_peak = 0;
	playerdata->target_distance = 0;
	playerdata->target_entity = NULL;
	playerdata->i_time = 0;
	playerdata->health = 5;
	playerdata->head_height = 0;
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

static void key_press(int keycode, t_app *app)
{
	(void) keycode;
	app->keys->w = mlx_is_key_down(app->mlx, MLX_KEY_W);
	app->keys->a = mlx_is_key_down(app->mlx, MLX_KEY_A);
	app->keys->s = mlx_is_key_down(app->mlx, MLX_KEY_S);
	app->keys->d = mlx_is_key_down(app->mlx, MLX_KEY_D);
	app->keys->space = mlx_is_key_down(app->mlx, MLX_KEY_SPACE);
	app->keys->one = mlx_is_key_down(app->mlx, MLX_KEY_1);
	app->keys->two = mlx_is_key_down(app->mlx, MLX_KEY_2);
	app->keys->map = mlx_is_key_down(app->mlx, MLX_KEY_M);
}

static void key_press_wrapper(mlx_key_data_t keydata, void *param)
{
	t_app *cbd = param;
	if (cbd->menudata->state == OFF)
		game_input(keydata, cbd, cbd->audio);
	else
		menu_input(keydata, cbd, cbd->audio);
	change_tv_channel(cbd->audio, keydata);
	app_input(keydata, cbd, cbd->audio);
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
	hud->img[HUD_PULSE] = mlx_new_image(mlx, WIDTH, HEIGHT);
	hud->img[HUD_FUEL] = mlx_new_image(mlx, 100, 100);
	hud->img[HUD_HEALTH] = mlx_new_image(mlx, 10, 10);
	return (hud);
}

void	cbd_init_beheading(t_app *cbd)
{
	cbd->beheading.active = false;
	cbd->beheading.timer = 0;
	cbd->beheading.chainsaw_pos = vec_assign(WIDTH / 3 - 100, 0);
	cbd->beheading.target_pos = vec_assign(0, 0);
	cbd->render.po_head->enabled = false;
}

void	cbd_init_images(t_app *cbd)
{
	mlx_image_to_window(cbd->mlx, cbd->hud->img[HUD_MAP], (WIDTH>>1) - (MINIMAP_WIDTH>>2) - 16, (HEIGHT>>1) + (MINIMAP_HEIGHT>>3) - 8);
	mlx_image_to_window(cbd->mlx, cbd->playerdata.inv->weapons[WPN_MAP].img, (WIDTH>>2), (HEIGHT>>3));
	mlx_image_to_window(cbd->mlx, cbd->playerdata.inv->weapons[WPN_FIST].img, (WIDTH>>1) - (cbd->playerdata.inv->weapons[WPN_FIST].img->width / 2), HEIGHT - (cbd->playerdata.inv->weapons[WPN_FIST].img->height>>1));
	mlx_image_to_window(cbd->mlx, cbd->playerdata.inv->weapons[WPN_CHAINSAW].img, (WIDTH>>1) - (cbd->playerdata.inv->weapons[WPN_CHAINSAW].img->width / 2), HEIGHT - (cbd->playerdata.inv->weapons[WPN_CHAINSAW].img->height * 0.8));
	mlx_image_to_window(cbd->mlx, cbd->hud->img[HUD_CRT], 0, 0);
	mlx_image_to_window(cbd->mlx, cbd->hud->img[HUD_PULSE], 0, 0);

	cbd->hud->img[HUD_FUEL] = cbd_init_texture_img(cbd->mlx, "./data/textures/sprites/fuel.png");
	cbd->hud->img[HUD_HEALTH] = cbd_init_texture_img(cbd->mlx, "./data/textures/sprites/health.png");
	mlx_image_to_window(cbd->mlx, cbd->hud->img[HUD_FUEL], WIDTH - 350, -5);
	mlx_image_to_window(cbd->mlx, cbd->hud->img[HUD_HEALTH], WIDTH - 300, 45);
	cbd->playerdata.inv->weapons[WPN_MAP].img->enabled = false;
	cbd->playerdata.inv->weapons[WPN_FIST].img->enabled = false;
	cbd->playerdata.inv->weapons[WPN_CHAINSAW].img->enabled = false;
	cbd->elapsed_time = 0;
}

bool cbd_init(t_app *cbd)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	mlx_set_setting(MLX_MAXIMIZED, 1);
	mlx_set_setting(MLX_FULLSCREEN, 1);

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

	cbd->render.po_head = cbd_init_texture_img(cbd->mlx, "./data/textures/sprites/po_head.png");
	mlx_image_to_window(cbd->mlx, cbd->render.po_head, 0, 0);
	if (!cbd->render.po_head)
		return (cbd_error(ERR_ALLOC), FAILURE);
	cbd_init_images(cbd);
	cbd->menudata = cbd_init_menu(cbd->mlx, cbd->mapdata);
	if (!cbd->menudata)
		return (cbd_error(ERR_ALLOC), FAILURE);

	init_playerdata(&cbd->playerdata, cbd->mapdata);
	init_render(&cbd->render, cbd->hud, cbd->playerdata.inv);
	init_particles(cbd->particles);
	cbd_init_beheading(cbd);

	cbd->keys = malloc(sizeof(t_keys));

	//Setup mlx hooks
	mlx_key_hook(cbd->mlx, key_press_wrapper, cbd);
	mlx_loop_hook(cbd->mlx, cbd_loop, cbd);
	return (SUCCESS);
}
