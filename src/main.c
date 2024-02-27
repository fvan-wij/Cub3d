#include <cub3d.h>
#include <cbd_parser.h>
#include <cbd_error.h>
#include <libft.h>
#include <stdio.h>
#include <MLX42.h>
#include <stdlib.h>

#define WIDTH 1280
#define HEIGHT 720

t_menu *cbd_init_menu(mlx_t *mlx)
{
	t_menu 			*menu;
	
	menu = malloc(sizeof(t_menu));
	if (!menu)
		return (NULL);

	//Create images
	menu->menu_img[M_MAIN] = mlx_new_image(mlx, WIDTH, HEIGHT);
	menu->menu_img[M_MAP_SEL] = mlx_new_image(mlx, WIDTH, HEIGHT);
	menu->menu_img[M_SELECTOR] = mlx_new_image(mlx, 64, 64);
	//Load pngs
	menu->menu_tex[M_MAIN] = mlx_load_png("./data/menu/menu_main.png");
	menu->menu_tex[M_MAP_SEL] = mlx_load_png("./data/menu/menu_map_select.png");
	menu->menu_tex[M_SELECTOR] = mlx_load_png("./data/menu/selector_knife.png");
	if (!menu->menu_img[M_MAIN] || !menu->menu_img[M_MAP_SEL] || !menu->menu_img[M_SELECTOR])
		return (NULL);
	menu->menu_img[M_MAIN] = mlx_texture_to_image(mlx, menu->menu_tex[M_MAIN]);
	menu->menu_img[M_MAP_SEL] = mlx_texture_to_image(mlx, menu->menu_tex[M_MAP_SEL]);
	menu->menu_img[M_SELECTOR] = mlx_texture_to_image(mlx, menu->menu_tex[M_SELECTOR]);


	return (menu);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_app	*cbd;
	static int i;

	cbd = param;

	if (mlx_is_key_down(cbd->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cbd->mlx);
	(void)keydata;
	if (cbd->state == CBD_MAIN)
	{
		int select[3] = {HEIGHT / 2, HEIGHT / 2 + 64 + 16, HEIGHT / 2 + 128 + 32};

		if (mlx_is_key_down(cbd->mlx, MLX_KEY_UP))
			i--;
		if (mlx_is_key_down(cbd->mlx, MLX_KEY_DOWN))
			i++;
		if (i > 2)
			i = 0;
		if (i < 0)
			i = 2;
		cbd->menudata->menu_img[M_SELECTOR]->instances[0].y = select[i];
		cbd->menudata->menu_img[M_SELECTOR]->instances[0].y = select[i];
		if (i == 1 && mlx_is_key_down(cbd->mlx, MLX_KEY_ENTER))
		{
			mlx_delete_image(cbd->mlx, cbd->menudata->menu_img[M_MAP_SEL]);
			mlx_delete_image(cbd->mlx, cbd->menudata->menu_img[M_SELECTOR]);
			mlx_delete_image(cbd->mlx, cbd->menudata->menu_img[M_MAIN]);
			mlx_delete_texture(cbd->menudata->menu_tex[M_MAIN]);
			mlx_delete_texture(cbd->menudata->menu_tex[M_SELECTOR]);
			mlx_delete_texture(cbd->menudata->menu_tex[M_MAP_SEL]);
			cbd->menudata = cbd_init_menu(cbd->mlx);

			mlx_image_to_window(cbd->mlx, cbd->menudata->menu_img[M_MAP_SEL], 0, 0);
			mlx_image_to_window(cbd->mlx, cbd->menudata->menu_img[M_SELECTOR], WIDTH / 2 +  96, HEIGHT / 2);

			i = 0;
			cbd->state = CBD_MAP_SEL;
		}
		if (i == 2 && mlx_is_key_down(cbd->mlx, MLX_KEY_ENTER))
			mlx_close_window(cbd->mlx);
	}
	if (cbd->state == CBD_MAP_SEL)
	{
		int offset = (i * 45) - 8;
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
			mlx_delete_image(cbd->mlx, cbd->menudata->menu_img[M_MAP_SEL]);
			mlx_delete_image(cbd->mlx, cbd->menudata->menu_img[M_SELECTOR]);
			mlx_delete_image(cbd->mlx, cbd->menudata->menu_img[M_MAIN]);
			mlx_delete_texture(cbd->menudata->menu_tex[M_MAIN]);
			mlx_delete_texture(cbd->menudata->menu_tex[M_SELECTOR]);
			mlx_delete_texture(cbd->menudata->menu_tex[M_MAP_SEL]);

			cbd->menudata = cbd_init_menu(cbd->mlx);
			cbd->state = CBD_MAIN;
			mlx_image_to_window(cbd->mlx, cbd->menudata->menu_img[M_MAIN], 0, 0);
			mlx_image_to_window(cbd->mlx, cbd->menudata->menu_img[M_SELECTOR], WIDTH / 2 +  64, HEIGHT / 2);
		}
		cbd->menudata->menu_img[M_SELECTOR]->instances[0].y = HEIGHT / 2 + offset;
	}
}

int32_t	main(int argc, char *argv[])
{
	t_app cbd;

	ft_memset(&cbd, 0, sizeof(t_app));
	if (!arg_is_valid(argc, argv))
		return (FAILURE);
	cbd.mapdata = cbd_parse_map(argv[1], &cbd);
	if (!cbd.mapdata)
		return (FAILURE);
	print_debug_info(&cbd);

	//MLX
	cbd.mlx = mlx_init(WIDTH, HEIGHT, "Telestein 3D", true);
	if (!cbd.mlx)
		return (FAILURE);
	cbd.menudata = cbd_init_menu(cbd.mlx);
	mlx_image_to_window(cbd.mlx, cbd.menudata->menu_img[M_MAIN], 0, 0);
	mlx_image_to_window(cbd.mlx, cbd.menudata->menu_img[M_SELECTOR], WIDTH / 2 +  64, HEIGHT / 2);
	mlx_key_hook(cbd.mlx, key_hook, &cbd);
	mlx_loop(cbd.mlx);
	mlx_terminate(cbd.mlx);


	return (SUCCESS);
}
