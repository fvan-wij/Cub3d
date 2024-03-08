#include <libft.h>
#include <MLX42.h>
#include <stdlib.h>
#include <cub3d.h>
#include <math.h>

static int	move_cursor_main_menu(t_app *cbd, int i)
{
	const int select[3] = {(HEIGHT >> 1), (HEIGHT >> 1) + 80, (HEIGHT >>1) + 160};

	if (mlx_is_key_down(cbd->mlx, MLX_KEY_UP))
		i--;
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_DOWN))
		i++;
	if (i > 2)
		i = 0;
	if (i < 0)
		i = 2;
	cbd->menudata->menu_img[M_CURSOR]->instances[0].x = WIDTH / 2 +  64;
	cbd->menudata->menu_img[M_CURSOR]->instances[0].y = select[i];
	if (i == 0 && mlx_is_key_down(cbd->mlx, MLX_KEY_ENTER))
		cbd->state = STATE_GAME;
	if (i == 1 && mlx_is_key_down(cbd->mlx, MLX_KEY_ENTER))
	{
		mlx_set_instance_depth(cbd->menudata->menu_img[M_MAIN]->instances, -1);
		mlx_set_instance_depth(cbd->menudata->menu_img[M_MAP]->instances, 0);
		mlx_set_instance_depth(cbd->menudata->menu_img[M_CURSOR]->instances, 1);
		i = 0;
		cbd->state = STATE_MAP_SEL;
	}
	if (i == 2 && mlx_is_key_down(cbd->mlx, MLX_KEY_ENTER))
		mlx_close_window(cbd->mlx);
	return (i);
}

static int	move_cursor_map_select(t_app *cbd, int i)
{
	const int select[6] = {((HEIGHT >> 1) - 8), ((HEIGHT >> 1) - 8) + 45, ((HEIGHT >> 1) - 8) + 90, ((HEIGHT >> 1) - 8) + 135, ((HEIGHT >> 1) - 8) + 180, ((HEIGHT >> 1) - 8) + 225};

	if (mlx_is_key_down(cbd->mlx, MLX_KEY_UP))
		i--;
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_DOWN))
		i++;
	if (i > 5)
		i = 0;
	if (i < 0)
		i = 5;
	if (i == 5 && mlx_is_key_down(cbd->mlx, MLX_KEY_ENTER))
	{
		mlx_set_instance_depth(cbd->menudata->menu_img[M_MAP]->instances, -1);
		mlx_set_instance_depth(cbd->menudata->menu_img[M_MAIN]->instances, 0);
		mlx_set_instance_depth(cbd->menudata->menu_img[M_CURSOR]->instances, 1);
		cbd->state = STATE_MAIN;
	}
	cbd->menudata->menu_img[M_CURSOR]->instances[0].y = select[i];
	cbd->menudata->menu_img[M_CURSOR]->instances[0].x = WIDTH / 2 +  80;
	return (i);
}

void	navigate_menu(mlx_key_data_t keydata, void *param)
{
	t_app		*cbd;
	static int	i;
	(void)keydata;
	// float offset = 100;

	cbd = param;
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_ESCAPE))
	{
		cbd->menudata->menu_img[M_MAIN]->instances->enabled = true;
		cbd->menudata->menu_img[M_MAP]->instances->enabled = true;
		cbd->menudata->menu_img[M_CURSOR]->instances->enabled = true;
		cbd->state = STATE_MAIN;
	}
	if (cbd->state == STATE_MAIN)
	{
		cbd->game->instances->enabled = false;
		i = move_cursor_main_menu(cbd, i);
	}
	if (cbd->state == STATE_MAP_SEL)
	{
		cbd->game->instances->enabled = false;
		i = move_cursor_map_select(cbd, i);
	}
	if (cbd->state == STATE_GAME)
	{
		cbd->menudata->menu_img[M_MAIN]->instances->enabled = false;
		cbd->menudata->menu_img[M_MAP]->instances->enabled = false;
		cbd->menudata->menu_img[M_CURSOR]->instances->enabled = false;
		cbd->game->instances->enabled = true;
	}

	if (mlx_is_key_down(cbd->mlx, MLX_KEY_1))
		cbd->hud->equipped = WPN_FIST;
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_2))
		cbd->hud->equipped = WPN_CHAINSAW;
	if (mlx_is_key_down(cbd->mlx, MLX_KEY_M))
		cbd->hud->equipped = WPN_MAP;

}

t_menu *cbd_init_menu(mlx_t *mlx)
{
	t_menu 			*menu;

	menu = malloc(sizeof(t_menu));
	if (!menu)
		return (NULL);
	menu->menu_img[M_MAIN] = mlx_new_image(mlx, WIDTH, HEIGHT);
	menu->menu_img[M_MAP] = mlx_new_image(mlx, WIDTH, HEIGHT);
	menu->menu_img[M_CURSOR] = mlx_new_image(mlx, 64, 64);
	menu->menu_tex[M_MAIN] = mlx_load_png("./data/menu/menu_main.png");
	menu->menu_tex[M_MAP] = mlx_load_png("./data/menu/menu_map_select.png");
	menu->menu_tex[M_CURSOR] = mlx_load_png("./data/menu/selector_knife.png");
	if (!menu->menu_img[M_MAIN] || !menu->menu_img[M_MAP] || !menu->menu_img[M_CURSOR])
		return (NULL);
	menu->menu_img[M_MAIN] = mlx_texture_to_image(mlx, menu->menu_tex[M_MAIN]);
	menu->menu_img[M_MAP] = mlx_texture_to_image(mlx, menu->menu_tex[M_MAP]);
	menu->menu_img[M_CURSOR] = mlx_texture_to_image(mlx, menu->menu_tex[M_CURSOR]);
	mlx_image_to_window(mlx, menu->menu_img[M_MAP], 0, 0);
	mlx_image_to_window(mlx, menu->menu_img[M_MAIN], 0, 0);
	mlx_image_to_window(mlx, menu->menu_img[M_CURSOR], WIDTH / 2 +  64, HEIGHT / 2);
	return (menu);
}
