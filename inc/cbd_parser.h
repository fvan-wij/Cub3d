#ifndef CBD_PARSER_H
# define CBD_PARSER_H

# include <stdbool.h>
# include <cbd_vec.h>
# include <MLX42.h>
# include <cbd_render.h>
# define SUCCESS 0
# define FAILURE 1
# define FILL 'X'

typedef struct s_lst_cont {
	enum e_cont {
		CONT_COLF,
		CONT_COLC,
		CONT_WALL,
		CONT_ENEMY,
		CONT_OBJECT,
		CONT_ITEM,
		CONT_MAP,
		CONT_UNKNOWN,
	} t_cont;
	uint8_t				type;
	bool				valid;
	union {
		char			*tex_path;
		t_rgba			color;
		char			**map;
	};
	char				c;
	struct s_lst_cont	*prev;
	struct s_lst_cont	*next;
}	t_lst_cont;

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

typedef struct s_entity {
	enum e_entity_type {
	ENTITY_ENEMY,
	ENTITY_ITEM,
	ENTITY_DECOR,
	ENTITY_SIZE,
	} t_entity_type;
	enum e_entity_state {
	ENTITY_IDLE,
	ENTITY_PATROL,
	ENTITY_AGROED,
	ENTITY_DEATH,
	} t_entity_state;
	enum e_entity_type	type;
	t_vec2d				pos;
	t_vec2d				dir;
	t_vec2d				*positions;
	int					health;
	int					damage;
	int					current_position;
	float				speed;
	float				audio_timer;
	mlx_texture_t		*texture;
	enum e_entity_state	state;
	struct s_entity		*next;
}	t_entity;

typedef struct s_map {
	char			**raw_data;
	char			**tex_path;
	char			**cbd_map;
	mlx_texture_t	**tex;
	t_entity		*entities;
	t_rgba			floor;
	t_rgba			ceiling;
	t_vec2d			start_pos;
	t_vec2d			start_dir;
	int				width;
	int				height;
	bool			valid;
	uint8_t			current_map;
	uint8_t			n_tex;
	bool			is_bonus;
} 	t_map;

t_map	*alloc_map(void);
t_map	*cbd_parse_map(const char *file);
t_map	*get_map_data(int fd, t_valid *is);
t_map	*parse_map_mandatory(const char *file, int fd, t_map *mapdata);
t_map	*get_map_data_mandatory(int fd, t_valid *is, char *line);
bool	validate_map_data(t_map *mapdata, t_valid *is);

//		Bonus
t_map	*parse_map_bonus(const char *file, int fd, t_map *mapdata);
t_map	*get_map_data_bonus(int fd, char *line);
t_map	*alloc_map_bonus(void);

//		Map select
t_map	*load_map(t_map *curr_map, uint8_t	map_id);
uint8_t	set_current_map(const char *file);

//		Bools.c
bool	is_tex(char *line, t_valid *is);
bool	is_col(char *line, t_valid *is);
bool	is_content(char *line);
bool	is_last_element(t_valid *is);
bool	is_wall(char c);
bool	is_wall_bonus(char c);
bool	is_bonus(int fd);
bool	tex_exists(char *path);

//				Getters.c
char			*get_texpath(char *temp);
t_rgba			get_col(char *temp);
mlx_texture_t	**get_mlx_tex(char **tex_path, uint8_t n);

#endif
