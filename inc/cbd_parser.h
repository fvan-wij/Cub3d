/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cbd_parser.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fvan-wij <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/07 12:26:15 by fvan-wij      #+#    #+#                 */
/*   Updated: 2024/05/07 19:32:38 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CBD_PARSER_H
# define CBD_PARSER_H

# include <stdbool.h>
# include <cbd_vec.h>
# include <MLX42.h>
# include <cbd_render.h>

# define SUCCESS 0
# define FAILURE 1
# define FILL 'X'
# define TEX_SIZE 255

typedef enum e_tex
{
	NO,
	SO,
	WE,
	EA,
}	t_tex;

typedef enum e_dir
{
	N,
	S,
	W,
	E,
	DIR_SIZE,
}	t_dir;

typedef enum e_cont
{
	CONT_MAP,
	CONT_WALL,
	CONT_CWALL,
	CONT_COLC,
	CONT_COLF,
	CONT_ITEM,
	CONT_OBJECT,
	CONT_ENEMY,
	CONT_UNKNOWN,
}	t_cont;

typedef enum e_level
{
	LVL_DARK_SECRET,
	LVL_THE_BUNKER,
	LVL_RABBIT_HOLE,
	LVL_SNOW_CRASH,
	LVL_CONFRONTATION,
	LVL_UNKNOWN,
}	t_level;

typedef struct s_valid
{
	bool	start[DIR_SIZE];
	bool	tex[TEX_SIZE];
	bool	col_fl;
	bool	col_cl;
	bool	map;
}	t_valid;

typedef enum e_entity_type
{
	ENTITY_ENEMY,
	ENTITY_ITEM,
	ENTITY_DECOR,
	ENTITY_SIZE,
}	t_entity_type;

typedef enum e_entity_state
{
	ENTITY_IDLE,
	ENTITY_PATROL,
	ENTITY_AGROED,
	ENTITY_ATTACK,
	ENTITY_DEATH,
}	t_entity_state;

typedef struct s_entity
{
	enum e_entity_type	type;
	enum e_entity_state	state;
	char				*name;
	t_vec2d				pos;
	t_vec2d				dir;
	t_vec2d				*destinations;
	int					health;
	int					damage;
	int					current_dest;
	int					n_dest;
	float				speed;
	float				audio_timer;
	mlx_texture_t		*texture;
	int					frame_width;
	int					frame_height;
	t_animation			animation;
	bool				enabled;
	bool				dead;
	float				distance;
	int					limb;
	struct s_entity		*next;
}	t_entity;

typedef struct s_map
{
	char			**raw_data;
	char			**cbd_map;
	t_wall			walls;
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
}	t_map;

t_map			*alloc_map(void);
t_map			*cbd_parse_map(const char *file);
t_map			*get_map_data(int fd, t_valid *is);
t_map			*parse_map_mandatory(const char *file, int fd, t_map *mapdata);
t_map			*get_map_data_mandatory(int fd, t_valid *is, char *line);
bool			validate_map_data(t_map *mapdata, t_valid *is);

//				Bonus
t_map			*parse_map_bonus(const char *file, int fd, t_map *mapdata);
t_map			*get_map_data_bonus(int fd, char *line);
t_map			*alloc_map_bonus(void);

//				Map select
t_map			*load_map(t_map *curr_map, uint8_t	map_id);
uint8_t			set_current_map(const char *file);
void			respawn(t_app *cbd);
t_entity		*append_entity(t_entity *entities, char *line, uint8_t type);

//				Bools.c
bool			is_tex(char *line, t_valid *is);
bool			is_col(char *line, t_valid *is);
bool			is_content(char *line);
bool			is_last_element(t_valid *is);
bool			is_wall(char c);
bool			is_wall_bonus(char c);
bool			is_bonus(int fd);
bool			tex_exists(char *path);
bool			is_mapcontent(char *line);

//				bools_validate.c
bool			wall_is_valid(t_map *mapdata, int i, int j);
bool			wall_is_valid_bonus(t_map *mapdata, int i, int j);
bool			is_duplicate(t_valid *is, t_map *mapdata);
bool			is_player(char c, t_map *mapdata, t_valid *is);
bool			start_is_valid(t_map *mapdata, t_valid *is);

//				Getters.c
char			*get_texpath(char *temp);
t_rgba			get_col(char *temp);
bool			get_mlx_tex(t_map *mapdata, uint8_t n);

t_animation		load_animation(mlx_texture_t *texture,
					uint32_t frame_width, uint32_t frame_height);

#endif
