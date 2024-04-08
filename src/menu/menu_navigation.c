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
		else
		{
			set_menu_state(menu, MAP_LOAD);
			menu->current_position = menu->preview_positions[menu->select_menu.current_item];
		}
	}
	else if (menu->state == GAME_WON)
	{
		set_menu_state(menu, MAIN);
	}
	else if (menu->state == GAME_OVER)
	{
		set_menu_state(menu, OFF);
	}
}

void	display_preview(t_menu *menu, t_map *mapdata)
{
		if (menu->select_menu.current_item == BTN_BACK)
		{
			menu->select_menu.preview_img->instances->x = menu->preview_positions[mapdata->current_map].x;
			menu->select_menu.preview_img->instances->y = menu->preview_positions[mapdata->current_map].y;

		}
		if (menu->select_menu.current_item == BTN_DARK_SECRET)
		{
			menu->select_menu.preview_img->instances->x = menu->preview_positions[LVL_DARK_SECRET].x;
			menu->select_menu.preview_img->instances->y = menu->preview_positions[LVL_DARK_SECRET].y;
			menu->current_position = menu->preview_positions[LVL_DARK_SECRET];
		}
		if (menu->select_menu.current_item == BTN_THE_BUNKER)
		{
			menu->select_menu.preview_img->instances->x = menu->preview_positions[LVL_THE_BUNKER].x;
			menu->select_menu.preview_img->instances->y = menu->preview_positions[LVL_THE_BUNKER].y;
			menu->current_position = menu->preview_positions[LVL_THE_BUNKER];
		}
		if (menu->select_menu.current_item == BTN_RABBIT_HOLE)
		{
			menu->select_menu.preview_img->instances->x = menu->preview_positions[LVL_RABBIT_HOLE].x;
			menu->select_menu.preview_img->instances->y = menu->preview_positions[LVL_RABBIT_HOLE].y;
			menu->current_position = menu->preview_positions[LVL_RABBIT_HOLE];
		}
		if (menu->select_menu.current_item == BTN_SNOW_CRASH)
		{
			menu->select_menu.preview_img->instances->x = menu->preview_positions[LVL_SNOW_CRASH].x;
			menu->select_menu.preview_img->instances->y = menu->preview_positions[LVL_SNOW_CRASH].y;
			menu->current_position = menu->preview_positions[LVL_SNOW_CRASH];
		}
		if (menu->select_menu.current_item == BTN_CONFRONTATION)
		{
			menu->select_menu.preview_img->instances->x = menu->preview_positions[LVL_CONFRONTATION].x;
			menu->select_menu.preview_img->instances->y = menu->preview_positions[LVL_CONFRONTATION].y;
			menu->current_position = menu->preview_positions[LVL_CONFRONTATION];
		}
}

void	menu_escape(t_menu *menu)
{
	set_menu_state(menu, MAIN);
}
