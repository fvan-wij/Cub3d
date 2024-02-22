#include <cub3d.h>
#include <libft.h>
#include <cbd_parser.h>
#include <cbd_error.h>
#include <stdlib.h>
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
	char	**temp;

	fd = cbd_open_map(file);
	if (fd < 0)
		return (false);
	line = get_next_line(fd);
	while (line)
	{
		temp = ft_split(line, ' ');
		int i;

		i = 0;
		while (temp[i])
		{
			if (ft_strncmp(temp[i], "NO", 2) == 0 && temp[i + 1])
				parse_texture(temp[i + 1], NO, cub3d);
			if (ft_strncmp(temp[i], "SO", 2) == 0 && temp[i + 1])
				parse_texture(temp[i + 1], SO, cub3d);
			if (ft_strncmp(temp[i], "WE", 2) == 0 && temp[i + 1])
				parse_texture(temp[i + 1], WE, cub3d);
			if (ft_strncmp(temp[i], "EA", 2) == 0 && temp[i + 1])
				parse_texture(temp[i + 1], EA, cub3d);
			if (ft_strncmp(temp[i], "F", ft_strlen(temp[i])) == 0 && temp[i + 1])
				cub3d->mapdata->floor = parse_color(temp[i + 1]);
			if (ft_strncmp(temp[i], "C", ft_strlen(temp[i])) == 0 && temp[i + 1])
				cub3d->mapdata->ceiling = parse_color(temp[i + 1]);
			i++;
		}
		free(line);
		ft_del_2d(temp);
		line = get_next_line(fd);
	}
	ft_printf("cbd_tex[NO]: %s\ncbd_tex[SO]: %s\ncbd_tex[WE]: %s\ncbd_tex[EA]: %s\n", cub3d->mapdata->cbd_tex[NO], cub3d->mapdata->cbd_tex[SO], cub3d->mapdata->cbd_tex[WE], cub3d->mapdata->cbd_tex[EA]);
	ft_printf("Floor colors -> R: %d, G: %d, B: %d\nCeiling colors -> R: %d, G: %d, B: %d\n", cub3d->mapdata->floor.r, cub3d->mapdata->floor.g,cub3d->mapdata->floor.b, cub3d->mapdata->ceiling.r, cub3d->mapdata->ceiling.g,cub3d->mapdata->ceiling.b);
	return (true);
}

bool	cbd_parse_map(const char *file, t_app *cub3d) 
{
	if (!init_map(cub3d))
		return (false);
	if (!cbd_read_map(file, cub3d))
		return (false);

	return (true);
}

