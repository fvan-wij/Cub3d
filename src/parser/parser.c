#include <cub3d.h>
#include <libft.h>
#include <cbd_parser.h>
#include <cbd_error.h>
#include <fcntl.h>

int	cbd_open_map(const char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (cbd_error(ERR_OPEN), fd);
	return (fd);
}


bool	cbd_read_map(const char *file, t_app *cub3d)
{
	int 	fd;
	char 	*line;

	(void) cub3d;
	fd = cbd_open_map(file);
	if (fd < 0)
		return (false);
	line = get_next_line(fd);
	while (line)
	{
		line = get_next_line(fd);

	}
	return (true);
}

bool	cbd_parse_map(const char *file, t_app *cub3d) 
{
	if (!cbd_read_map(file, cub3d))
		return (false);

	return (true);
}

