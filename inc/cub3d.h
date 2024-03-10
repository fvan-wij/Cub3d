#ifndef CUB3D_H
# define CUB3D_H

# include <MLX42.h>
# include <libft.h>
# include <cbd_vec.h>
# include <cbd_render.h>

# define SUCCESS 0
# define FAILURE 1

# define WIDTH 1280
# define HEIGHT 720

# define FOV 90

typedef struct s_bresenham
{
	int			error[2];
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			cx;
	int			cy;
	int			y;
	int			x;
}	t_bresenham;

typedef struct s_line
{
	int			x1;
	int			y1;
	int			x2;
	int			y2;
}	t_line;

typedef union s_rgba
{
	int32_t	color;
	struct
	{
		uint8_t	a;
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
	};
}	t_rgba;

typedef enum e_tex {
	NO,
	SO,
	WE,
	EA,
	TEX_SIZE,
} e_tex;

typedef enum e_dir {
	N,
	S,
	W,
	E,
	DIR_SIZE,
} e_dir;

typedef enum e_state {
	STATE_MENU,
	STATE_GAME,
} t_state;

typedef struct s_ray {
	t_vec2d	dir;
	t_vec2d intersection;
	double	wall_dist;
	uint8_t	side;
} t_ray;

enum e_action {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	ACTION_SIZE,
};

typedef struct s_action {
	bool	forward;
	bool	backward;
	bool	left;
	bool	right;
	bool	action[ACTION_SIZE];
} t_action;

typedef struct s_player {
	t_vec2d 	pos;
	t_vec2d		dir;
	t_vec2d		plane;
	float		scalar;
	float		headbob;
	float		map_peak;
	t_ray		rays[WIDTH];
	t_action	action;
}	t_player;

typedef struct s_map {
	char			**raw_data;
	char			**tex_path;
	char			**cbd_map;
	mlx_texture_t	**cbd_tex;
	t_rgba			floor;
	t_rgba			ceiling;
	t_vec2d			start_pos;
	t_vec2d			start_dir;
	int				width;
	int				height;
	bool			valid;
} 	t_map;

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

typedef enum e_menu_state {
	OFF,
	MAIN,
	MAP_SELECT,
} t_menu_state;

typedef struct s_menu {
	t_main_menu		main_menu;
	t_select_menu	select_menu;
	t_menu_state	state;
} t_menu;

typedef struct s_hud {
	enum e_hud_id {
		HUD_MAP,
		WPN_MAP,
		WPN_FIST,
		WPN_CHAINSAW,
		HUD_SIZE,
	} t_hud_id;
	mlx_image_t	*img[HUD_SIZE];
	int8_t equipped;
} t_hud;

typedef void (*t_input_handler)(mlx_key_data_t, void *);

typedef struct s_input {
	bool			key[348];
	t_input_handler	handler[348];
} t_input;

typedef struct s_app {
	t_particle 	particles[N_PARTICLES];
	t_player 	playerdata;
	t_menu		*menudata;
	t_map		*mapdata;
	t_hud		*hud;
	mlx_image_t	*game;
	t_state		state;
	mlx_t		*mlx;
	t_input		input;
}	t_app;



//		Utility
void	print_2d(char **str);
void	print_debug_info(t_app *cub3d);
void	cleanup(t_app *app);

//		Menu.c
// void	navigate_menu(mlx_key_data_t keydata, void *param);
// int		move_cursor_main_menu(t_app *cbd, int i);
void	menu_move_cursor(t_menu *menu, int dir);
void	menu_enter(t_menu *menu);
void	menu_escape(t_menu *menu);
void	set_menu_state(t_menu *menu, t_menu_state state);
int		move_cursor_map_select(t_app *cbd, int i);
t_menu 	*cbd_init_menu(mlx_t *mlx);

// 		Rendering
void	draw_map(t_app *cbd, int width, int height);
void	draw_walls(t_app *cbd, t_ray *rays);
void	draw_player(char **map, mlx_image_t *img, t_player p);
void	draw_particles(t_app *cbd);
void	cbd_render(t_app *cbd);

//		Raycaster
t_ray	cast_ray(char **map, t_player p, int x);
void	cast_rays(char **map, t_player *p);

//		Shapes
void	draw_background(mlx_image_t *img, int32_t color);
void	draw_line(mlx_image_t *image, uint32_t color, t_vec2i p1, t_vec2i p2);
void	draw_square(mlx_image_t *image, uint32_t color, t_vec2i pos, t_vec2i dimension);
void	draw_circle(mlx_image_t *image, uint32_t color, t_vec2i pos, float r);

//		Game
bool	cbd_main(t_app *cbd);
bool	cbd_init(t_app *cbd);
void	cbd_loop(void *param);
void	cbd_init_input(t_app *cbd);
void	cbd_input(mlx_key_data_t keydata, void *param);

//		Interaction
void	move_player(t_app *cbd);

//		Input_handlers
// void	default_handler(mlx_key_data_t keydata, void *param);
// void	forward_handler(mlx_key_data_t keydata, void *param);
// void	backward_handler(mlx_key_data_t keydata, void *param);;
// void	left_handler(mlx_key_data_t keydata, void *param);
// void	right_handler(mlx_key_data_t keydata, void *param);
// void	escape_handler(mlx_key_data_t keydata, void *param);
// void	enter_handler(mlx_key_data_t keydata, void *param);
// void	weapon_handler(mlx_key_data_t keydata, void *param);
// void	map_handler(mlx_key_data_t keydata, void *param);


#endif //CUB3D_H
