#ifndef CBD_PARSER_H
# define CBD_PARSER_H

# include <stdbool.h>
# include <cub3d.h>
# define SUCCESS 0
# define FAILURE 1

t_map 	*init_map(void);
t_map	*cbd_parse_map(const char *file);
t_map	*cbd_read_map(const char *file, t_map *mapdata);
char	*parse_texture(char *temp);
t_rgba	parse_color(char *temp);



#endif
