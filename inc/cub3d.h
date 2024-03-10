#ifndef CUB3D_H
# define CUB3D_H

# include <MLX42.h>
# include <libft.h>
# include <cbd_vec.h>
# include <cbd_render.h>
# include <cbd_menu.h>

# define SUCCESS 0
# define FAILURE 1

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
	t_inventory	*inv;
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

// 		Rendering
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

//		Init
mlx_image_t *cbd_init_texture_img(mlx_t *mlx, char *path);

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
