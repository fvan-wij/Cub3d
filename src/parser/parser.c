
#include <libft.h>
#include <cbd_parser.h>
#include <cbd_error.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void	print_2d(char **str)
{
	int i; 

	i = 0;
	while (str[i])
	{
		ft_printf("%s", str[i]);
		i++;
	}
}

int	cbd_open_map(const char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (cbd_error(ERR_OPEN), fd);
	return (fd);
}

char **cbd_read_map(const char *file, t_app *cub3d)
{
	int i;
	int 	fd;
	char 	*line;
	char	**temp;
	char	**raw_mapdata;

	raw_mapdata = NULL;
	fd = cbd_open_map(file);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);

	while (line	)
	{
		if (ft_containschar(line, '1') && !ft_containschar(line, 'F') && !ft_containschar(line, 'C'))
			raw_mapdata = ft_append_to_double_array(raw_mapdata, line);
		else
		{
			temp = ft_split(line, ' ');
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
		}
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	ft_printf("cbd_tex[NO]: %scbd_tex[SO]: %scbd_tex[WE]: %scbd_tex[EA]: %s\n", cub3d->mapdata->cbd_tex[NO], cub3d->mapdata->cbd_tex[SO], cub3d->mapdata->cbd_tex[WE], cub3d->mapdata->cbd_tex[EA]);
	ft_printf("Floor color:  (%d, %d, %d)\nCeiling color: (%d, %d, %d)\n\n", cub3d->mapdata->floor.r, cub3d->mapdata->floor.g,cub3d->mapdata->floor.b, cub3d->mapdata->ceiling.r, cub3d->mapdata->ceiling.g,cub3d->mapdata->ceiling.b);
	print_2d(raw_mapdata);
	return (raw_mapdata);
}


// bool	raw_mapdata_is_valid(char **raw_mapdata)
// {
//
// 	if ()
//
// 	return (false);
//
// 	return (true);
// }

// bool parse_mapdata(char **raw_mapdata, t_app *cub3d)
// {
// 	if (!raw_mapdata_is_valid(raw_mapdata))
// 		return (cbd_error(ERR_INVALID_MAP), false);
// 	return (true);
// }

bool	cbd_parse_map(const char *file, t_app *cub3d) 
{
	char **raw_mapdata;

	if (!init_map(cub3d))
		return (false);
	raw_mapdata = cbd_read_map(file, cub3d);
	if (!raw_mapdata)
		return (false);
	// if (!parse_mapdata(raw_mapdata, cub3d))
	// 	return (false);
	return (true);
}

