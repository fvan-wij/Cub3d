#ifndef CBD_PARSER_H
# define CBD_PARSER_H

# include <stdbool.h>
# include <cbd_vec.h>
# include <MLX42.h>
# include <cbd_render.h>
# define SUCCESS 0
# define FAILURE 1
# define FILL 'X'

// Add characters to walls for character-based textures, WALLS_SIZE = n of characters + 1
# define WALLS "123456789\0"
# define WALLS_SIZE 10

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

typedef enum e_level {
	LVL_DARK_SECRET,
	LVL_THE_BUNKER,
	LVL_RABBIT_HOLE,
	LVL_SNOW_CRASH,
	LVL_CONFRONTATION,
	LVL_UNKNOWN,
} t_level;

typedef struct s_valid {
	bool	start[DIR_SIZE];
	bool	tex[TEX_SIZE];
	bool	col_fl;
	bool	col_cl;
	bool	map;
} t_valid;

typedef struct s_map {
	char			**raw_data;
	char			**tex_path;
	char			**cbd_map;
	mlx_texture_t	**tex;
	t_rgba			floor;
	t_rgba			ceiling;
	t_vec2d			start_pos;
	t_vec2d			start_dir;
	int				width;
	int				height;
	bool			valid;
	uint8_t			current_map;
} 	t_map;

t_map 	*alloc_map(void);
t_map	*cbd_parse_map(const char *file);
t_map	*get_map_data(int fd, t_map *mapdata, t_valid *is);
bool	validate_map_data(t_map *mapdata, t_valid *is);

//		Map select
t_map	*load_map(t_map *curr_map, uint8_t	map_id);


//		Bools.c
bool	is_tex(char *line, t_valid *is);
bool	is_col(char *line, t_valid *is);
bool	is_content(char *str);
bool	is_last_element(t_valid *is);
bool	is_wall(char c);

#endif
