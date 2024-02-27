#ifndef CUB3D_H
# define CUB3D_H

# include <MLX42.h>
# include <libft.h>

# define SUCCESS 0
# define FAILURE 1

typedef struct 	s_vec {
	int	x;
	int y;
}	t_vec;

typedef struct 	s_vec_f {
	float	x;
	float	y;
}	t_vec_f;

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

typedef struct s_player {
	t_vec_f pos;
}	t_player;

typedef enum e_m_select {
	M_MAIN,
	M_MAP_SEL,
	M_SELECTOR,
	M_SIZE,
} t_m_select;

typedef enum e_state {
	CBD_MAIN,
	CBD_MAP_SEL,
	CBD_GAME,
} t_state;

typedef struct s_menu {
	mlx_texture_t	*menu_tex[M_SIZE];
	mlx_image_t 	*menu_img[M_SIZE];
} t_menu;

typedef struct s_app {
	t_map		*mapdata;
	t_player 	*playerdata;
	t_menu		*menudata;
	mlx_t		*mlx;
	t_state		state;
}	t_app;


void	print_2d(char **str);
void	print_debug_info(t_app *cub3d);

#endif
