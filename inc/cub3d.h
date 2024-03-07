#ifndef CUB3D_H
# define CUB3D_H

# include <MLX42.h>
# include <libft.h>

# define SUCCESS 0
# define FAILURE 1

# define WIDTH 1280
# define HEIGHT 720

# define FOV 120

typedef struct 	s_vec {
	int	x;
	int y;
}	t_vec;

typedef struct 	s_vec_f {
	double	x;
	double	y;
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
	}; }	t_rgba;

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
	t_vec_f	dir;
	t_vec_f intersection;
	double	wall_dist;
	uint8_t	side;
} t_ray;

typedef struct s_player {
	t_vec_f pos;
	t_vec_f	dir;
	t_vec_f	plane;
	float	scalar;
	t_ray	rays[FOV];
}	t_player;

typedef struct s_map {
	char			**raw_data;
	char 			**tex_path;
	char 			**cbd_map;
	mlx_texture_t	**cbd_tex;
	t_rgba			floor;
	t_rgba			ceiling;
	t_vec_f			start_pos;
	t_vec_f			start_dir;
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

//		Utility
void	print_2d(char **str);
void	print_debug_info(t_app *cub3d);
void	cleanup(t_app *app);

//		Menu.c
void	navigate_menu(mlx_key_data_t keydata, void *param);
t_menu 	*cbd_init_menu(mlx_t *mlx);

// 		Rendering
void	draw_map(t_app *cbd, int width, int height);
void	draw_walls(mlx_image_t *img, t_ray rays[FOV]);
void	draw_player(char **map, mlx_image_t *img, t_player p);
void	cbd_render(t_app *cbd);

//		Raycaster
t_ray	cast_ray(char **map, t_player p, int x);
void	cast_rays(char **map, t_player *p);

//		Shapes
void	draw_background(mlx_image_t *img, int32_t color);
void	draw_line(mlx_image_t *image, uint32_t color, t_vec p1, t_vec p2);
void	draw_square(mlx_image_t *image, uint32_t color, t_vec pos, t_vec dimension);
// void	draw_circle(mlx_image_t *image, uint32_t color, t_vec pos, t_vec size);
void	draw_circle(mlx_image_t *image, uint32_t color, t_vec pos, float r);

//		Game
bool	cbd_main(t_app *cbd);
bool	cbd_init(t_app *cbd);

//		Interaction
void	move_player(void *param);

//		Vectors
void	vec_normalize(t_vec_f *vec);
t_vec_f	vec_assign(double x, double y);
void	vec_rotate(t_vec_f *direction, double angle);
t_vec	vec_to_int(t_vec_f vec);
t_vec_f	vec_to_float(t_vec vec);
double	vec_length(t_vec_f vec);
t_vec_f	vec_divide(t_vec_f vec, double denominator);
t_vec 	vec_divide_int(t_vec vec, double denominator);
t_vec_f vec_min(t_vec_f a, t_vec_f b);
t_vec_f vec_max(t_vec_f a, t_vec_f b);
t_vec_f vec_sub(t_vec_f a, t_vec_f b);
t_vec_f vec_add(t_vec_f a, t_vec_f b);
t_vec_f vec_mult(t_vec_f a, float scalar);

#endif //CUB3D_H
