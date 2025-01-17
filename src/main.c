#include <cub3d.h>
#include <cbd_parser.h>
#include <cbd_error.h>
#include <libft.h>
#include <MLX42.h>

#include <stdio.h>

int32_t	main(int argc, char *argv[])
{
	t_app cbd;

	if (argc == 1)
	{
		ft_memset(&cbd, 0, sizeof(t_app));
		cbd.mapdata = cbd_parse_map("./data/maps/dark_secret.cub");
	}
	else if (!arg_is_valid(argc, argv))
		return (FAILURE);
	else
	{
		ft_memset(&cbd, 0, sizeof(t_app));
		cbd.mapdata = cbd_parse_map(argv[1]);
	}
	if (!cbd.mapdata)
		return (FAILURE);
	// print_debug_info(&cbd);
	if (cbd_main(&cbd))
		return (FAILURE);
	return (SUCCESS);
}
