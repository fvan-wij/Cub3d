#ifndef CUB3D_H
# define CUB3D_H

# include <MLX42.h>
# include <libft.h>

# define SUCCESS 0
# define FAILURE 1

# define WIDTH 1280
# define HEIGHT 720


typedef struct 	s_vec {
	int	x;
	int y;
}	t_vec;

typedef struct 	s_vec_f {
	float	x;
	float	y;
}	t_vec_f;

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

typedef enum e_menu_elements {
	M_MAIN,
	M_MAP,
	M_CURSOR,
	M_SIZE,
} t_menu_elements;

typedef enum e_state {
	STATE_MAIN,
	STATE_MAP_SEL,
	STATE_GAME,
} t_state;

typedef struct s_ray {
	t_vec_f	camera;
	t_vec_f	ray_dir;
} t_ray;

typedef struct s_player {
	t_vec_f pos;
	t_vec_f	dir;
	float	angle;
}	t_player;

typedef struct s_map {
	char			**raw_data;
	char 			**tex_path;
	char 			**cbd_map;
	mlx_texture_t	**cbd_tex;
	t_rgba			floor;
	t_rgba			ceiling;
	t_vec			start_pos;
	e_dir			start_dir;
	int				width;
	int				height;
	bool			valid;
} 	t_map;

typedef struct s_menu {
	mlx_texture_t	*menu_tex[M_SIZE];
	mlx_image_t 	*menu_img[M_SIZE];
} t_menu;

typedef struct s_app {
	t_player 	playerdata;
	t_menu		*menudata;
	t_map		*mapdata;
	mlx_image_t	*game;
	t_state		state;
	mlx_t		*mlx;
}	t_app;


void	print_2d(char **str);
void	print_debug_info(t_app *cub3d);

//		Menu.c
void	navigate_menu(mlx_key_data_t keydata, void *param);
t_menu 	*cbd_init_menu(mlx_t *mlx);

//		Raycaster

//		Shapes
void	draw_line(mlx_image_t *image, uint32_t color, t_vec p1, t_vec p2);
void	draw_square(mlx_image_t *image, uint32_t color, t_vec pos, t_vec dimension);
void	draw_circle(mlx_image_t *image, uint32_t color, t_vec pos, t_vec size);

//		Game
bool	cbd_game_loop(t_app *cbd);

//		Vectors
void	vec_normalize(t_vec_f *vec);
t_vec_f	vec_assign(float x, float y);
void	vec_rotate(t_vec_f *direction, float angle);
t_vec	vec_to_int(t_vec_f vec);
t_vec_f	vec_to_float(t_vec vec);
float	vec_length(t_vec_f vec);
t_vec_f	vec_divide(t_vec_f vec, float denominator);
t_vec 	vec_divide_int(t_vec vec, float denominator);

#endif
