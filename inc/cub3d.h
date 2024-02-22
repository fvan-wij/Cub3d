#ifndef CUB3D_H
# define CUB3D_H

# include <MLX42.h>
# include <libft.h>

# define SUCCESS 0
# define FAILURE 1

typedef union s_rgba
{
	int32_t	color;
	struct
	{
		int8_t	a;
		int8_t	b;
		int8_t	g;
		int8_t	r;
	};
}	t_rgba;

typedef enum e_tex {
	NO,
	SO,
	WE,
	EA,
} e_tex;

typedef struct s_map {
	char **cbd_map;
	char **cbd_tex;
	t_rgba	floor;
	t_rgba	ceiling;
} 	t_map;

typedef struct s_player {

}	t_player;

typedef struct s_app {
	t_map		*mapdata;
	t_player 	*playerdata;
}	t_app;

#endif
