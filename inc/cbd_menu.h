#ifndef CBD_MENU_H
# define CBD_MENU_H
# include <MLX42.h>
# include <cbd_vec.h>
# include <cbd_parser.h>

typedef enum e_menu_state {
	OFF,
	MAIN,
	MAP_SELECT,
	MAP_LOAD,
	GAME_OVER,
	GAME_WON,
} t_menu_state;

typedef struct s_main_menu {
	enum e_m_main_items {
		BTN_PLAY,
		BTN_MAP_SELECT,
		BTN_EXIT,
		BTN_MAIN_COUNT,
	} t_m_main_items;
	mlx_image_t			*bg;
	mlx_image_t			*map;
	mlx_image_t			*cursor;
	mlx_image_t			*preview_img;
	t_vec2i				cursor_pos;
	t_vec2i				cursor_positons[4];
	enum e_m_main_items	current_item;
} t_main_menu;

typedef struct s_select_menu {
	enum e_m_select_items {
		BTN_DARK_SECRET,
		BTN_THE_BUNKER,
		BTN_RABBIT_HOLE,
		BTN_SNOW_CRASH,
		BTN_CONFRONTATION,
		BTN_BACK,
		BTN_SELECT_COUNT,
	} t_m_select_items;
	mlx_image_t			*bg;
	mlx_image_t			*map;
	mlx_image_t			*cursor;
	mlx_image_t			*preview_img;
	t_vec2i				cursor_pos;
	t_vec2i				cursor_positons[7];
	enum e_m_select_items	current_item;
} t_select_menu;

typedef struct s_game_over {
	mlx_image_t			*bg;
	mlx_image_t			*cursor;
	t_vec2i				cursor_pos;
} t_game_over;


typedef struct s_game_won {
	mlx_image_t			*bg;
	mlx_image_t			*cursor;
	t_vec2i				cursor_pos;
} t_game_won;

typedef struct s_menu {
	t_main_menu		main_menu;
	t_select_menu	select_menu;
	t_game_over		game_over;
	t_game_won		game_won;
	t_menu_state	state;
	t_vec2i			preview_positions[6];
	t_vec2i			current_position;
} t_menu;

//Setters
void	set_cursor(mlx_image_t *img, t_vec2i veci);
void	set_menu_state(t_menu *menu, t_menu_state state);
// void	set_menu_state(t_menu *menu, t_menu_state state, t_map *map);
void	set_main_cursor_positions(t_menu *menu);
void	set_select_cursor_positions(t_menu *menu);
void	set_map_preview_positions(t_menu *menu);

//Menu Navigation
size_t	move_cursor(mlx_image_t *cursor, int cur_item, int max, t_vec2i *positions, int dir);
void	move_cursor_main_menu(t_menu *menu, int dir);
void	move_cursor_select_menu(t_menu *menu, int dir);
void	menu_move_cursor(t_menu *menu, int dir);
// void	menu_enter(t_menu *menu, t_map *map);
void	menu_enter(t_menu *menu);
void	menu_escape(t_menu *menu);

//Preview img
void	display_preview(t_menu *menu, t_map *mapdata);


#endif
