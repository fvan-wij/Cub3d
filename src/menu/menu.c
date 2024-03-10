#include <libft.h>
#include <MLX42.h>
#include <stdlib.h>
#include <cub3d.h>
#include <math.h>

#include <stdio.h>

void	set_cursor(mlx_image_t *img, t_vec2i veci)
{
	img->instances->x = veci.x;
	img->instances->y = veci.y;
}

size_t	move_cursor(mlx_image_t *cursor, int cur_item, int max, t_vec2i *positions, int dir)
{
	if (cur_item + dir < 0)
		cur_item = max;
	else if (cur_item + dir > max)
		cur_item = 0;
	else
		cur_item += dir;
	set_cursor(cursor, positions[cur_item]);
	return (cur_item);
}

void	move_cursor_main_menu(t_menu *menu, int dir)
{
	menu->main_menu.current_item = move_cursor(menu->main_menu.cursor, menu->main_menu.current_item, BTN_MAIN_COUNT - 1, menu->main_menu.cursor_positons, dir);
}

void	move_cursor_select_menu(t_menu *menu, int dir)
{
	menu->select_menu.current_item = move_cursor(menu->select_menu.cursor, menu->select_menu.current_item, BTN_SELECT_COUNT - 1, menu->select_menu.cursor_positons, dir);
}

void	menu_move_cursor(t_menu *menu, int dir)
{
	if (menu->state == MAIN)
		move_cursor_main_menu(menu, dir);
	if (menu->state == MAP_SELECT)
		move_cursor_select_menu(menu, dir);
}

void	set_menu_state(t_menu *menu, t_menu_state state)
{
	if (state == MAIN)
	{
		set_cursor(menu->main_menu.cursor, menu->main_menu.cursor_positons[0]);
		menu->state = MAIN;
		menu->main_menu.current_item = BTN_PLAY;
		menu->main_menu.bg->instances->enabled = true;
		menu->main_menu.cursor->instances->enabled = true;
		menu->select_menu.bg->instances->enabled = false;
	}
	if (state == MAP_SELECT)
	{
		set_cursor(menu->select_menu.cursor, menu->select_menu.cursor_positons[0]);
		menu->state = MAP_SELECT;
		menu->select_menu.current_item = BTN_DARK_SECRET;
		menu->main_menu.bg->instances->enabled = false;
		menu->main_menu.cursor->instances->enabled = true;
		menu->select_menu.bg->instances->enabled = true;
	}
	if (state == OFF)
	{
		menu->main_menu.bg->instances->enabled = false;
		menu->main_menu.cursor->instances->enabled = false;
		menu->select_menu.bg->instances->enabled = false;
		menu->select_menu.cursor->instances->enabled = false;
		menu->state = OFF;
	}
}

void	menu_enter(t_menu *menu)
{
	if (menu->state == MAIN)
	{
		if (menu->main_menu.current_item == BTN_PLAY)
			set_menu_state(menu, OFF);
		if (menu->main_menu.current_item == BTN_MAP_SELECT)
			set_menu_state(menu, MAP_SELECT);
		if (menu->main_menu.current_item == BTN_EXIT)
			exit(0);
	}
	else if (menu->state == MAP_SELECT)
	{
		if (menu->select_menu.current_item == BTN_BACK)
			set_menu_state(menu, MAIN);
	}
}

void	menu_escape(t_menu *menu)
{
	set_menu_state(menu, MAIN);
}

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

void	set_main_cursor_positions(t_menu *menu)
{
	const t_vec2i	positions[4] =	{{(WIDTH / 2 + 64),(HEIGHT >> 1)},
							{(WIDTH / 2 + 64),(HEIGHT >> 1) + 80},
							{(WIDTH / 2 + 64),(HEIGHT >> 1) + 160}};
	menu->main_menu.cursor_positons[0] = positions[0];
	menu->main_menu.cursor_positons[1] = positions[1];
	menu->main_menu.cursor_positons[2] = positions[2];
}

void	set_select_cursor_positions(t_menu *menu)
{
	const t_vec2i	positions[7] =	{{(WIDTH / 2 + 80),((HEIGHT >> 1) - 8)},
									{(WIDTH / 2 + 80),((HEIGHT >> 1) - 8) + 45},
									{(WIDTH / 2 + 80),((HEIGHT >> 1) - 8) + 90},
									{(WIDTH / 2 + 80),((HEIGHT >> 1) - 8) + 135},
									{(WIDTH / 2 + 80),((HEIGHT >> 1) - 8) + 180},
									{(WIDTH / 2 + 80),((HEIGHT >> 1) - 8) + 225}};
	menu->select_menu.cursor_positons[0] = positions[0];
	menu->select_menu.cursor_positons[1] = positions[1];
	menu->select_menu.cursor_positons[2] = positions[2];
	menu->select_menu.cursor_positons[3] = positions[3];
	menu->select_menu.cursor_positons[4] = positions[4];
	menu->select_menu.cursor_positons[5] = positions[5];
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
