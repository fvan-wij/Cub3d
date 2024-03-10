#include <MLX42.h>
#include <stdlib.h>
#include <cub3d.h>
#include <stdio.h>

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
