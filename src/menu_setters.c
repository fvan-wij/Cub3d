#include <MLX42.h>
#include <cub3d.h>
#include <cbd_error.h>
#include <stdlib.h>
#include <stdio.h>

void	set_cursor(mlx_image_t *img, t_vec2i veci)
{
	img->instances->x = veci.x;
	img->instances->y = veci.y;
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
		menu->game_over.bg->instances->enabled = false;
		menu->game_won.bg->instances->enabled = false;
		menu->main_menu.preview_img->instances->enabled = true;
	}
	if (state == MAP_SELECT)
	{
		set_cursor(menu->select_menu.cursor, menu->select_menu.cursor_positons[0]);
		menu->state = MAP_SELECT;
		menu->select_menu.current_item = BTN_DARK_SECRET;
		menu->main_menu.bg->instances->enabled = false;
		menu->game_over.bg->instances->enabled = false;
		menu->main_menu.cursor->instances->enabled = true;
		menu->select_menu.bg->instances->enabled = true;
		menu->main_menu.preview_img->instances->enabled = true;
	}
	if (state == OFF)
	{
		menu->main_menu.bg->instances->enabled = false;
		menu->main_menu.cursor->instances->enabled = false;
		menu->select_menu.bg->instances->enabled = false;
		menu->select_menu.cursor->instances->enabled = false;
		menu->main_menu.preview_img->instances->enabled = false;
		menu->game_over.bg->instances->enabled = false;
		menu->state = OFF;
	}
	if (state == MAP_LOAD)
	{
		menu->state = MAP_LOAD;
	}
	if (state == GAME_OVER)
	{
		set_cursor(menu->game_over.cursor, menu->game_over.cursor_pos);
		// Turn on correct elements
		menu->game_over.bg->instances->enabled = true;
		menu->main_menu.cursor->instances->enabled = true;
		// Turn off other menu elements
		menu->main_menu.bg->instances->enabled = false;
		menu->main_menu.cursor->instances->enabled = false;
		menu->select_menu.bg->instances->enabled = false;
		menu->select_menu.cursor->instances->enabled = false;
		menu->main_menu.preview_img->instances->enabled = false;
		menu->state = GAME_OVER;
	}
	if (state == GAME_WON)
	{
		set_cursor(menu->game_won.cursor, menu->game_won.cursor_pos);
		// Turn on correct elements
		menu->game_won.bg->instances->enabled = true;
		menu->main_menu.cursor->instances->enabled = true;
		// Turn off other menu elements
		menu->main_menu.bg->instances->enabled = false;
		menu->main_menu.cursor->instances->enabled = false;
		menu->select_menu.bg->instances->enabled = false;
		menu->select_menu.cursor->instances->enabled = false;
		menu->main_menu.preview_img->instances->enabled = false;
		menu->state = GAME_WON;
	}
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

void	set_map_preview_positions(t_menu *menu)
{
	const int x_step = 993 / 3;
	const int y_step = 228;
	const t_vec2i positions[6] = {{195, 362},
								{195 - x_step, 362},
								{195 - (x_step * 2), 362},
								{195, 362 - y_step},
								{195 - x_step, 362 - y_step},
								{195 - (x_step * 2), 362 - y_step}};
	menu->preview_positions[0] = positions[0];
	menu->preview_positions[1] = positions[1];
	menu->preview_positions[2] = positions[2];
	menu->preview_positions[3] = positions[3];
	menu->preview_positions[4] = positions[4];
	menu->preview_positions[5] = positions[5];
	menu->current_position = positions[0];
}
