#ifndef CBD_PARSER_H
# define CBD_PARSER_H

# include <stdbool.h>
# include <cub3d.h>
# define SUCCESS 0
# define FAILURE 1
# define FILL 'X'

typedef struct s_valid {
	bool	start[DIR_SIZE];
	bool	tex[TEX_SIZE];
	bool	col_fl;
	bool	col_cl;
	bool	map;
} t_valid;

t_map 	*alloc_map(void);
t_map	*cbd_parse_map(const char *file);
t_map	*get_map_data(int fd, t_map *mapdata, t_valid *is);
bool	validate_map_data(t_map *mapdata, t_valid *is);


//		Bools.c
bool	is_tex(char *line, t_valid *is);
bool	is_col(char *line, t_valid *is);
bool	is_content(char *str);
bool	is_last_element(t_valid *is);

#endif
