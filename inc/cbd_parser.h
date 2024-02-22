#ifndef CBD_PARSER_H
# define CBD_PARSER_H

# include <stdbool.h>
# include <cub3d.h>
# define SUCCESS 0
# define FAILURE 1

bool 	init_map(t_app *cub3d);
bool	cbd_parse_map(const char *file, t_app *cub3d);
bool	cbd_read_map(const char *file, t_app *cub3d);

//		Textures
void	parse_texture(char *temp, e_tex DIR, t_app *cub3d);
t_rgba	parse_color(char *temp);

#endif
