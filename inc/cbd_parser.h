#ifndef CBD_PARSER_H
# define CBD_PARSER_H

# include <stdbool.h>
# include <cub3d.h>
# define SUCCESS 0
# define FAILURE 1

bool	cbd_parse_map(const char *file, t_app *cub3d);
bool	cbd_read_map(const char *file, t_app *cub3d);

#endif
