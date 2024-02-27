#include <cub3d.h>
#include <cbd_parser.h>
#include <cbd_error.h>
#include <libft.h>
#include <stdio.h>
#include <MLX42.h>
#include <stdlib.h>


int32_t	main(int argc, char *argv[])
{
	t_app cbd;

	ft_memset(&cbd, 0, sizeof(t_app));
	if (!arg_is_valid(argc, argv))
		return (FAILURE);
	cbd.mapdata = cbd_parse_map(argv[1], &cbd);
	if (!cbd.mapdata)
		return (FAILURE);
	print_debug_info(&cbd);

	//MLX
	cbd.mlx = mlx_init(WIDTH, HEIGHT, "Telestein 3D", true);
	if (!cbd.mlx)
		return (FAILURE);

	//Main loop
	cbd.menudata = cbd_init_menu(cbd.mlx);
	if (!cbd.menudata)
		return (cbd_error(ERR_ALLOC), FAILURE);

	mlx_key_hook(cbd.mlx, navigate_menu, &cbd);
	mlx_loop(cbd.mlx);
	mlx_terminate(cbd.mlx);
	return (SUCCESS);
}
